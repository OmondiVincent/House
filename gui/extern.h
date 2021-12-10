#ifndef EXTERN_H
#define EXTERN_H
    #include "sqlite/create.h"
    #include <condition_variable>
    #include <vector>
    #include <wx/string.h>

    extern Table plot;
    extern int value;
    extern std::vector<std::string> txt;
    extern int last_row_id;
    extern int num_of_rooms;
    extern int showflag;
    extern wxString ownername;
    extern wxString ownercont;
    extern std::string plotrmid;
    std::string replace(std::string str);
    std::string separate_string(std::string txt);
    extern double xpixel;
    extern double ypixel;

#endif

