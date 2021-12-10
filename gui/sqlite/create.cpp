#include "create.h"


Table::Table(){

	//NB the 4 parameter in the sqlite3 is called the vfc is the os
	//  interface which provides protability across os...so it is 
	// recommended to be at default
	rs = sqlite3_open_v2("fileowner.db", &db, SQLITE_OPEN_CREATE | 
							SQLITE_OPEN_READWRITE, NULL);
	
	if( rs  ){
		// Show an error message
		std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
		// Close the connection
		sqlite3_close(db);
    }

	//initialize our variables
	sql = "CREATE TABLE IF NOT EXISTS owner ("  \
      "Id 			    TEXT  	PRIMARY KEY NOT NULL," \
      "Surname          TEXT    	       		NOT NULL," \
	  "Name        		TEXT            		NOT NULL," \
	  "Gender           TEXT                    NOT NULL," \
	  "Number           TEXT                    NOT NULL," \
	  "Account       	TEXT              		NOT NULL);"; 

	sql1 = "CREATE TABLE IF NOT EXISTS plot_info ("  \
	"OwnerId            TEXT              NOT NULL,"\
	"PlotId             TEXT  PRIMARY KEY NOT NULL," \
	"Name           	TEXT             NOT NULL," \
	"No_of_rooms        INT              NOT NULL," \
	"Location           TEXT             NOT NULL,"\
	"FOREIGN KEY(OwnerId) REFERENCES owner(Id) ON DELETE CASCADE);";

	sql2= "CREATE  TABLE IF NOT EXISTS Plotroom("  \
	"Plotid        TEXT                NOT NULL," \
	"Type          TEXT    			   NOT NULL," \
	"Rent          INT    			   NOT NULL," \
	"Units         INT    			   NOT NULL," \
	"FOREIGN KEY(plotid) REFERENCES plot_info(PlotId) ON DELETE CASCADE);";

	sql3= "CREATE  TABLE IF NOT EXISTS room("  \
	"plotid          TEXT             	    NOT NULL," \
	"Room_No         INT        PRIMARY KEY NOT NULL," \
	"Type            TEXT                   NOT NULL);";

	sql4 = "CREATE TABLE IF NOT EXISTS year("  \
	"Year           INT PRIMARY KEY     NOT NULL);";

	sql5 = "CREATE TABLE IF NOT EXISTS month("  \
	"Year          INT  			  NOT NULL, "\
	"Name          TEXT   PRIMARY KEY NOT NULL," \
	"FOREIGN KEY(Year) REFERENCES year(Year));";

	sql6 = "CREATE TABLE IF NOT EXISTS tenant ("  \
	"Plotid          TEXT                NOT NULL," \
	"EmpId           INT PRIMARY KEY     NOT NULL," \
	"Gender          TEXT                NOT NULL," \
	"Surname         TEXT                NOT NULL," \
	"Other           TEXT                NOT NULL,"\
	"Phone_number    TEXT                NOT NULL," \
	"Month           TEXT                NOT NULL,"\
	"Year            INT                 NOT NULL, " \
	"room_type       TEXT                NOT NULL, " \
	"room_num    	 INT                 NOT NULL," \
	"FOREIGN KEY(plotid) REFERENCES plot_info(PlotId) ON DELETE CASCADE,"\
	"FOREIGN KEY(Month) REFERENCES month(Name), "\
	"FOREIGN KEY(Year) REFERENCES  year(Year));";

	sql7 = "CREATE TABLE IF NOT EXISTS payment("  \
	"payment_id       TEXT   PRIMARY KEY NOT NULL," \
	"Room_No          INT                NOT NULL," \
	"emp_id           INT                NOT NULL," \
	"Year             INT  			     NOT NULL,"\
	"Month            TEXT               NOT NULL, "\
	"Amount   	  	  INT                NOT NULL," \
	"Balance    	  INT                NOT NULL," \
	"Status           TEXT               NOT NULL," \
	"FOREIGN KEY(Month) REFERENCES month(Name), "\
	"FOREIGN KEY(emp_id) REFERENCES tenant(EmpId), "\
	"FOREIGN KEY(Year) REFERENCES  year(Year));";
}


int Table::create_table(){

    std::string data[8] = {sql, sql1, sql2, sql3, sql4, sql5, sql6, sql7};
   
    int rs;
	int count =1;

    for (auto x: data) {

		//sqlite3_exec(db, "PRAGMA foreign_keys = on", NULL, NULL, NULL);
		
		rs = sqlite3_exec(db, x.c_str(), NULL, 0, &messaggeError);

		if (rs != SQLITE_OK) {
			std::cerr << "Error Creating Table " << count << std::endl;
			sqlite3_free(messaggeError);
		}
    	else{
        	std::cout << "Table " << count << " created Successfully" << std::endl;
    		//sqlite3_close(db);
			
		}
		count +=1;
	}
	sqlite3_close(db);
	insert_year();
	insert_month();
    return (0);
}

void Table::open_db(){

	// it take database handle,  SQL text,
	// UTF-8 encoded */ Length of zSql in bytes.
	//OUT: Statement handle
	//OUT: Pointer to unused portion of zSql 
	//the sqlite3_prepare_v2 compiles the sql statement and allocates,
	//necessary memory

	rs = sqlite3_open("fileowner.db", &db);
	rs = sqlite3_prepare_v2(db, "PRAGMA foreign_keys = ON", -1, &stmt, &tail);
	rs = sqlite3_prepare_v2(db, sqlq.c_str(), -1, &stmt, &tail);


	if (rs != SQLITE_OK) {
		std::cerr << "Cant insert values to rows " << std::endl;
		sqlite3_free(messaggeError);
		flag = true;
	}

	//return 0;

}

void Table::insert_owner_info(const char* id, const char* num, const char* sur,
									 const char* nm, const char* gender, const char* account){

	sqlq = "INSERT INTO owner(Id, Surname, Name, Gender, Number, Account) VALUES (?, ?, ?, ?, ?, ?)";

	open_db();

	sqlite3_bind_text(stmt, 1, id, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, sur, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, nm, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, gender, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, num, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, account, -1, SQLITE_TRANSIENT);

	rs = sqlite3_step(stmt);
	rs = sqlite3_finalize(stmt);

	sqlite3_close(db);

}

void Table::insert_plot_info(const char * Id, const char * plotid, int num, std::string name, std::string loc){

	sqlq = "INSERT INTO plot_info(OwnerId, PlotId, Name, No_of_rooms, Location) VALUES (?, ?, ?, ?, ?)";

    const char *nm = name.c_str();
	const char  *lc = loc.c_str();

	open_db();

	sqlite3_bind_text(stmt, 1, Id, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, plotid, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, nm, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 4, num);
	sqlite3_bind_text(stmt, 5, lc, -1, SQLITE_TRANSIENT);

	rs = sqlite3_step(stmt);
	rs = sqlite3_finalize(stmt);
	sqlite3_close(db);

}

void Table::insert_room(const char* plotId, int num, const char* type){

	sqlq = "INSERT INTO room(plotid, Room_No, Type) VALUES (?, ?, ?)";


	open_db();

	sqlite3_bind_text(stmt, 1, plotId, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, num);
	sqlite3_bind_text(stmt, 3, type, -1, SQLITE_TRANSIENT);

	rs = sqlite3_step(stmt);
	rs = sqlite3_finalize(stmt);
	sqlite3_close(db);

}

void Table::insert_plotroom(const char* plotid, const char* type, double rent, int units){

	sqlq = "INSERT INTO Plotroom (Plotid, Type, Rent, Units) VALUES (?, ?, ?, ?)";

	open_db();

	sqlite3_bind_text(stmt, 1, plotid, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, type, -1, SQLITE_TRANSIENT);
	sqlite3_bind_double(stmt, 3, rent);
	sqlite3_bind_int(stmt, 4, units);

	rs = sqlite3_step(stmt);
	rs = sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Table::insert_year(){

    std::tm* now = get_curr_date(); 

	//now->tm_mon + 1

	sqlq = "INSERT INTO year (Year) VALUES (?)";
	for(int x = now->tm_year+1900; x < 2039; x++){
		
		//std::cout << x << std::endl;
		open_db();
		sqlite3_bind_int(stmt, 1, x);
		

		rs = sqlite3_step(stmt);
		rs = sqlite3_finalize(stmt);
	}
	sqlite3_close(db);
}



std::tm * get_curr_date(){
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);

	return now;
}

void Table::insert_month(){

	std::tm* now = get_curr_date(); 
	int yr = now->tm_year+1900;

	const char *month[] = {"January", "February", "March",
                       "April", "May", "June",
                       "July", "August", "September",
                       "October", "November", "December"
                      };

	
	sqlq = "INSERT INTO month (Year, Name) VALUES (?, ?)";				  

	for(auto x: month) {
	
		open_db();
		sqlite3_bind_int(stmt, 1, yr);
		sqlite3_bind_text(stmt, 2, x, -1, SQLITE_TRANSIENT);
		//sqlite3_bind_int(stmt, 3, 1);

		rs = sqlite3_step(stmt);
		rs = sqlite3_finalize(stmt);

	}
	sqlite3_close(db);
	
}

void Table::insert_tenant(const char *plotid, int Id, const char* gender,
						 const char* sname, const char *other,const char *num,
						const char* month, int year, const char* type, int room_num){

	sqlq = "INSERT INTO tenant(Plotid, EmpId, Gender, Surname, Other, Phone_number, Month, Year, room_type, room_num) \
							VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

	open_db();

	sqlite3_bind_text(stmt, 1, plotid, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, Id);
	sqlite3_bind_text(stmt, 3, gender, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, sname, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, other, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 6, num, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 7, month, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 8, year);
	sqlite3_bind_text(stmt, 9, type, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 10, room_num);

	rs = sqlite3_step(stmt);
	rs = sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void Table::get_month(){

	int rc, year, rent;
	const unsigned char *name;
	sqlq = "SELECT  * FROM month";
	
	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, sqlq.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {
		name = sqlite3_column_text(stmt, 0);
		year = sqlite3_column_int(stmt, 1);
		rent = sqlite3_column_int(stmt, 2);

		if(name != NULL){
			std::cout << name << ", "<< year<< ", "<<rent<< std::endl;
		}
		rc = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}

std::vector<owner_info> Table::get_owner_name(){
	const  char *surname;
	const  char *lstname;
	const char *id;
	const char *num_char;
	const char *acc_char;

	std::string name;
	std::string Id;
	std::string num;
	std::string acc;

	std::vector<owner_info> owner;
	

	sqlq = "SELECT  * FROM owner";

	//sqlq = "SELECT * FROM owner ORDER BY rowid DESC LIMIT 1;";
	
	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, sqlq.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {

		//cast const insigned char to const char, 
		//NB C++ does not uses const unsigned char bcoz standard streams are meant for reading
		// and/or writing streams of characters, represented by char objects,
		 // not integers (signed char and unsigned char). 
		
		id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		lstname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		surname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		num_char= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		acc_char = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));


		if(lstname != NULL && surname != NULL){

			std::string s_a = convertToString(surname);
    		//std::string s_b = convertToString(lstname);
			Id = convertToString(id);
			num = convertToString(num_char);
			acc = convertToString(acc_char);
			name = s_a; //+ " " + s_b;
		}
		rc = sqlite3_step(stmt);

		owner.push_back({name, num, Id, acc});
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return owner;
}

std::vector<plot_info> Table::get_plot(){
	const  char *plotname;

	std::string name, loc;
	int vac;

	std::vector<plot_info> own;
	

	sqlq = "SELECT  * FROM plot_info";

	//sqlq = "SELECT * FROM owner ORDER BY rowid DESC LIMIT 1;";
	
	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, sqlq.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {

		//cast const insigned char to const char, 
		//NB C++ does not uses const unsigned char bcoz standard streams are meant for reading
		// and/or writing streams of characters, represented by char objects,
		 // not integers (signed char and unsigned char). 

		plotname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		loc = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

		vac = sqlite3_column_int(stmt, 3);

		if(plotname != NULL ){

			name = convertToString(plotname);

		}
		rc = sqlite3_step(stmt);

		own.push_back({vac, loc, name});
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return own;
}

void Table::populate_Tenant(int num_of_rooms){

	for (int x=1; x<=num_of_rooms; x++){

		ten.arr.push_back(x);
		ten.nm.push_back(" ");
		ten.num.push_back(" ");
		ten.ocp.push_back("No");
		ten.phone.push_back(" ");
		ten.stats.push_back(" ");

	}
	
}

void Table::delete_struct_arr(){
	ten.arr.clear();
	ten.nm.clear();
	ten.num.clear();
	ten.ocp.clear();
	ten.phone.clear();
	ten.stats.clear();
}

bool Table::check_struct(){
	if (ten.num.empty() && ten.nm.empty() && ten.phone.empty()){
		return true;
	}else{
		return false;
	}
}

void Table::get_tenant_info(std::string plotid){

	const char *sn;
	const char *ln;
	const char *num;
	const char *htype;
	int room_num;

	std::string ssn;
	std::string sln;
	std::string snum;
	std::string shtype;

	std::string t_name;

	std::string Idstr = "\'" + plotid + "\'";
	
	sqlq = "SELECT  * FROM tenant WHERE Plotid = " + Idstr ;
	//+ Idstr;

	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, sqlq.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {

		//cast const insigned char to const char, 
		//NB C++ does not uses const unsigned char bcoz standard streams are meant for reading
		// and/or writing streams of characters, represented by char objects,
		 // not integers (signed char and unsigned char). 

		sn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		ln = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		num = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		htype = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
		room_num = sqlite3_column_int(stmt, 9);

		if(sn != NULL && ln != NULL){

			ssn = convertToString(sn);
			sln = convertToString(ln);
			snum = convertToString(num);
			shtype = convertToString(htype);

		}
		rc = sqlite3_step(stmt);
		t_name = ssn + " " + sln;
		//ten.arr.insert(ten.nm.begin()+5, room_num);
		room_num = room_num -1;
		ten.nm.at(room_num) = t_name;
		ten.num.at(room_num) = shtype;
		ten.phone.at(room_num) = snum;
		ten.ocp.at(room_num) = "Yes";
		ten.stats.at(room_num) = "Not paid";

	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}

void Table::get_tenant_status(int year, std::string month, std::string pltid){

	const char* status;
	std::string status_edit;
	int room_num;


	std::string month_name = "\'" + month + "\'";
	std::string year_name = std::to_string(2021);
	std::string plottxt = "\'" + pltid + "\'";
	std::string last_txt = " AND tenant.plotid = " + plottxt;

	std::string Idstr = "month.Name = " + month_name + " AND year.Year = " + year_name;

	std::string txt1 = "SELECT year.Year, month.Name, tenant.Surname, tenant.Other, payment.Room_No, payment.Status FROM year, month, tenant ";

	std::string txt2 = "INNER JOIN payment On year.Year=payment.year AND month.Name=payment.month AND tenant.Empid=payment.emp_id WHERE " + Idstr ;

	sqlq = txt1 + txt2 + last_txt;
	
	//+ Idstr;

	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, sqlq.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {

		//cast const insigned char to const char, 
		//NB C++ does not uses const unsigned char bcoz standard streams are meant for reading
		// and/or writing streams of characters, represented by char objects,
		 // not integers (signed char and unsigned char). 
		
		room_num = sqlite3_column_int(stmt, 4);
		status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

		if(status != NULL && room_num !=0){

			status_edit = convertToString(status);

		}
		rc = sqlite3_step(stmt);
	
		//ten.arr.insert(ten.nm.begin()+5, room_num);
		room_num = room_num -1;
		ten.stats.at(room_num) = status_edit;

	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}


/******************************************************************************************************************************************/

tenant_info Table::print_tenant_report(std::string plotid){

	tenant_info ten_report;

	const char *sn;
	const char *ln;
	const char *num;
	const char *htype;
	int room_num;

	std::string ssn;
	std::string sln;
	std::string snum;
	std::string shtype;

	std::string t_name;

	std::string Idstr = "\'" + plotid + "\'";
	
	sqlq = "SELECT  * FROM tenant WHERE Plotid = " + Idstr ;
	//+ Idstr;

	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, sqlq.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {

		//cast const insigned char to const char, 
		//NB C++ does not uses const unsigned char bcoz standard streams are meant for reading
		// and/or writing streams of characters, represented by char objects,
		 // not integers (signed char and unsigned char). 

		sn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		ln = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		num = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		htype = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
		room_num = sqlite3_column_int(stmt, 9);

		if(sn != NULL && ln != NULL){

			ssn = convertToString(sn);
			sln = convertToString(ln);
			snum = convertToString(num);
			shtype = convertToString(htype);

		}
		rc = sqlite3_step(stmt);
		t_name = ssn + " " + sln;
		//ten.arr.insert(ten.nm.begin()+5, room_num);
		//room_num = room_num -1;
		ten_report.arr.push_back(room_num);
		ten_report.nm.push_back(t_name);
		ten_report.num.push_back(shtype);
		ten_report.phone.push_back(snum);
		ten_report.ocp.push_back("yes");

		//=         push_back(t_name);
		//ten.num.at(room_num) = shtype;
		//ten.phone.at(room_num) = snum;
		//ten.ocp.at(room_num) = "Yes";

	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return ten_report;

}

// converst char into strings
std::string convertToString(const char* a)
{
    std::string s1(a);
    return a;
}

void Table::delete_info(std::string sql){

	if (!sql.empty()){

		sqlite3_open("fileowner.db", &db);
		rs = sqlite3_prepare_v2(db, "PRAGMA foreign_keys = ON", -1, &stmt, &tail);
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);


		if(rc != SQLITE_OK){
			dial = new wxMessageDialog(NULL, wxT("Deleting the info \n was unsuccesful"), wxT("Error"), wxOK | wxICON_ERROR);
				dial->ShowModal();
		} else {
				
			dial = new wxMessageDialog(NULL, wxT("Deletion succesfull"), wxT("Done"), wxOK);
				dial->ShowModal();
		}

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
	}
}

std::string Table::get_Id(std::string query, std::string x){
   // std::string str = "SELECT Id FROM owner WHERE Number = 87";

	const char *Id;
	std::string strquery = query + x;
	std::string strId;
	
	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, strquery.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {
		
		Id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		
		if (Id != NULL){
			strId = convertToString(Id);
	
		}else{
			break;
		}
		
		sqlite3_step(stmt);
		if (room_flag==true){
			house_room_type.push_back(strId);
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return strId;

}

void Table::update_info(std::string str){
	
	if (sqlite3_open("fileowner.db", &db) == SQLITE_OK)
	{
		sqlite3_prepare_v2( db, str.c_str(), -1, &stmt, NULL);//preparing the statement
		sqlite3_step( stmt );
		
		
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

int Table::get_room_no(std::string plotid){

	int room_no;

	sqlite3_open("fileowner.db", &db);

	sqlite3_prepare_v2(db, plotid.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {
		
		room_no = sqlite3_column_int64(stmt, 3);
		break;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return room_no;

}

agent Table::Agent_info(){

	const char *agent_n;
	const char *loc;
	const char *cont;
	const char *mail;
	const char *web;

	std::string sagent_n;;
	std::string sloc;
	std::string scont;
	std::string smail;
	std::string sweb;

	std::string t_name;

	std::string sql_agent = "SELECT  * FROM deta";
	//+ Idstr;

	sqlite3_open("/home/alan/project/House/gui/build/deta.db", &db);

	sqlite3_prepare_v2(db, sql_agent.c_str(), -1, &stmt, NULL);

	ncols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);

	while(rc == SQLITE_ROW) {

		//cast const insigned char to const char, 
		//NB C++ does not uses const unsigned char bcoz standard streams are meant for reading
		// and/or writing streams of characters, represented by char objects,
		 // not integers (signed char and unsigned char). 

		cont = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		loc = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
		agent_n = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
		mail = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
		web = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));

		if(web!=NULL){
			user.agent_name = convertToString(agent_n);
			user.loc = convertToString(loc);
			user.contact = convertToString(cont);
			user.email = convertToString(mail);
			user.web = convertToString(web);

		} else {

			user.agent_name = convertToString(agent_n);
			user.loc = convertToString(loc);
			user.contact = convertToString(cont);
			user.email = convertToString(mail);
			user.web = "";

		}
		rc = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return user;

}

/************************************************************************************************************/



