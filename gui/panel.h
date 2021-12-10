#ifndef PANEL_H
#define PANEL_H
    #include <wx/wx.h>
    #include <wx/panel.h>
    #include <wx/srchctrl.h>
    #include <wx/button.h>
    #include "dialog.h"
    #include <wx/listctrl.h>
    #include <wx/colour.h>
    #include <wx/stattext.h>
    #include <wx/font.h>
    #include <iterator>
    #include <fstream>
    #include "itemdata.h"
    #include "listviewbox.h"
    #include "mythread.h"
    #include <string>
    #include <memory>
    #include <wx/arrstr.h>
    #include "printing.h"
    #include <bits/stdc++.h>

    inline NormaList *lview;
    inline wxStaticText *h_name;

    void create_receipt(const wxString &title, const wxString &num, const wxString& date, int receipt_no,
				const wxString &name, int paid, int bal, const wxString& month, int room_no,
				const wxString& agent_name);

    void create_report(std::string strtxt,  wxString date, wxString txte);


    class LeftPanel : public wxPanel
    {
        public:
            LeftPanel(wxPanel *parent);
            ~LeftPanel();
            void OnCreate(wxCommandEvent& event);
            void OnAdd(wxCommandEvent& event);
            void ViewList(wxCommandEvent& event);
            void InitWithReportItems();
            
            CustomDialog *customd;

           // void leftclick(wxMouseEvent& event);
            void Createreport();
            int m_numListItems;

            void rightclick(wxListEvent& event);
            void onDelete(wxCommandEvent& event);
            void onclick(wxListEvent& event);
            void onedit(wxCommandEvent& event);
            void addtenant(wxCommandEvent& event);
            void print_report(wxCommandEvent& event);
            void force_update();
            void add_plot_info();
            wxListView *m_listCtrl;


            //wxDialog *list;
            

        private:
            //wxListCtrl *listview;
            wxButton *createbt;
            wxButton *addbt;
            wxButton *view;
            wxPanel *m_parent;
            int count;

            wxImageList *m_imageListNormal;
            wxImageList *m_imageListSmall;

           // wxListView *m_listCtrl;
            wxTextCtrl *m_logWindow;
            long val;
            long item;
            wxString txtpltnm;
            Myprint *printfile;
            std::string strtxt;
           
            void print(wxCommandEvent& event);
            void populateview();
            void update_list(wxCommandEvent& event);
            std::vector<plot_info> arr;

            //tenants
            std::string finalstr12;

        protected:
            wxString txt1;
    

    };

    class RightPanel : public wxPanel
    {
        public:
            RightPanel(wxPanel *parent);
            wxSearchCtrl *search;
            NormaList *getlistview();
            void rightclick(wxListEvent& event);
            void onDelete(wxCommandEvent& event);
            void onedit(wxCommandEvent& event);
            void print_receipt(wxCommandEvent& event);
            void onfind(wxCommandEvent& event);

        private:
            wxListCtrl *dataview;
            int val;
            wxString txt1name, status;
            Myprint *printfile;
    };

    class MyExtraPanel : public wxPanel
    {
    public:
        MyExtraPanel(wxWindow *parent);
        wxString GetInfo() const;

    private:
        void OnCheckBox(wxCommandEvent& event);
        void OnUpdateLabelUI(wxUpdateUIEvent& event);
        wxButton *m_btn;
        wxCheckBox *m_cb;
        wxStaticText *m_label;
};

   class FrameList : public wxDialog
    {
        public:
            FrameList(const wxString &title, const wxPoint &pos, const wxSize &size);
            ~FrameList();
            void addinfo();
            void onclick(wxListEvent& event);
            void rightclick(wxListEvent& event);
            void onDelete(wxCommandEvent& event);
            void onedit(wxCommandEvent& event);
            void get_info();
            void Add_plot(wxCommandEvent& event);

        private:
            wxListView *listbox;
            std::vector<owner_info> arr;
            int item;
            wxString txt;
            

    };

enum {
    ID_CREATE = 300,
    ID_ADD=301,
    ID_EDIT_LIST = 302,
    ID_SEARCH=310,
    ID_HNAME=320,
    ID_LIST=305,
    ID_POP_DEL=303,
    ID_REF = 304,
    ID_LISTBOX_RIGHT_CLICK = 399,
    ID_LEFTPANEL_LIST_R_CLICK = 306,
    ID_CLICK = 307,
    ID_PRINT_RECEIPT = 308,
    ID_PRINT_REPORT = 309,
    ID_TENANT_DELETE,
};

#endif
