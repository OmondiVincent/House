#ifndef LISTVIEWBOX_H
#define LISTVIEWBOX_H

    #include <wx/wx.h>
    #include <wx/listbox.h>
    #include <wx/listctrl.h>
    #include <sqlite3.h>
    #include "itemdata.h"
    #include "extern.h"
    #include "sqlite/create.h"


    class MyListCtrl : public wxListCtrl
    {
        public:
            MyListCtrl(wxWindow *parent,const wxWindowID id,const wxPoint& pos,const wxSize& size,long style);
            
            virtual wxString OnGetItemText(long index, long column) const  wxOVERRIDE;
            void RefreshAfterUpdate();

            mutable std::vector<plot_info> arr; 
            void populateview();
            void get();
            void click();
            int showflag;

        private:
            long m_updated;
            //std::string txt;
            sqlite3 *db;
            char* messaggeError;
            int rc, i, ncols;
           // sqlite3_stmt *stmt;
            std::string sqlq;
    };

    class NormaList : public wxListCtrl
    {
        public:
            NormaList(wxWindow *parent,const wxWindowID id,const wxPoint& pos,\
                                    const wxSize& size,long style);

            virtual wxString OnGetItemText(long index, long column) const  wxOVERRIDE;
            void set_num_rooms();
            void populateview(std::string pltid);
            void RefreshAfterUpdate();
            void clear_list();


        private:
           mutable std::vector<int> num_room;

    };


#endif

