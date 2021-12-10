#ifndef TABLE_H
#define TABLE_H

    #include <iostream>
    #include <sqlite3.h>
    #include <string>
    #include <mutex>
    #include <chrono>
    #include <ctime>
    #include <stdio.h>
    #include <atomic>
    #include <condition_variable>
    #include <thread>
    #include <iterator>
    #include <map>
    #include <vector>
    #include <wx/msgdlg.h>
    
    using namespace std::chrono_literals;


    typedef struct{
        
        std::string name;
        std::string number;
        std::string Id;
        std::string account;
        
    } owner_info;

    typedef struct{

        int num_rooms;
        std::string location;
        std::string plotname;

    } plot_info;

    typedef struct{

		std::vector<int> arr;
		std::vector<std::string> nm;
		std::vector<std::string> num;
		std::vector<std::string> ocp;
		std::vector<std::string> phone;
        std::vector<std::string> stats;

    } tenant_info;

    typedef struct {
        std::string agent_name;
        std::string loc;
        std::string contact;
        std::string email;
        std::string web;

    } agent;

    std::tm * get_curr_date();
    std::string convertToString(const char* a);
    
    void check();
    void set_flag();



    class Table{
        public:
            Table();

            int create_table();
            int plot_detail();
            void insert_owner_info(const char* id, const char* num, const char* sur,
                                         const char* nm, const char* gender, const char* account);
            void insert_plot_info(const char *Id, const char * plotid, int num, std::string name, std::string loc);
            void open_db();
            void insert_room(const char* plotId, int num, const char* type);
            void insert_plotroom(const char* plotid, const char* type, double rent, int units);
            void insert_year();
            void insert_month();
            void insert_tenant(const char *plotid, int Id, const char* gender,
                                const char* sname,const char *other, const char *num,
							    const char* month, int year, const char* type, int room_num);
            std::string get_Id(std::string query, std::string x);
            void get_month();
            void get_tenant_info(std::string plotid);
            void update_info(std::string str);

            void delete_info(std::string sql);


            void delete_struct_arr();
            bool check_struct();

           // std::vector<std::string> get_owner_name();
            
            std::vector<owner_info> get_owner_name();
            std::vector<plot_info> get_plot();
            std::vector<std::string> v;
            std::vector<std::string> house_room_type;
            tenant_info print_tenant_report(std::string plotid);
            int get_room_no(std::string plotid);

            bool flag = false;
            bool room_flag = false;
            tenant_info ten;
            void populate_Tenant(int num_of_room);

            void get_tenant_status(int year, std::string month, std::string pltid);

            agent Agent_info();
            agent user;


        private:
            sqlite3 *db;
            int rs;
            char* messaggeError;
            int rc, i, ncols;
            sqlite3_stmt *stmt;
            
            std::string sqlq;
            const char *tail;
            std::string sql, sql1,
                        sql2, sql3,
                        sql4, sql5,
                        sql6, sql7;
                        
            wxMessageDialog *dial;

    };

   
    
#endif