#include "extern.h"

Table plot;
int  value;
int last_row_id;
std::vector<std::string> txt;

int num_of_rooms;
int showflag;

wxString ownername;
wxString ownercont;
std::string plotrmid;

double xpixel;
double ypixel;


std::string replace(std::string str){
	std::string x = "'";

   str = " " + str + " ";
	
	size_t n = 0;
	
	while ((n = str.find(" ", n)) != std::string::npos )
    {
        str.replace(n, 1, x);
        n += x.length();
    }
    return str;
	
}

std::string separate_string(std::string txt){
	std::string s = txt + " ";

	std::vector < std::string> word;
	
	std::string space_delimiter = " ";
	
	size_t pos = 0;
	while ((pos = s.find(space_delimiter)) != s.npos){
		word.push_back(s.substr(0, pos));
		s.erase(0, pos + space_delimiter.length());
	}
	
	if (word.size() == 2){
		return word[1];
	}else{
		return word[1] + " " + word[2];
	}
}