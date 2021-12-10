#ifndef DIALOG_H
#define DIALOG_H
    #include <wx/wx.h>
    #include <wx/fontdlg.h> 
    #include <wx/numdlg.h>
    #include <wx/choice.h>
    #include <wx/string.h>
    #include <wx/textctrl.h>
    #include <wx/statline.h>
    #include <wx/valgen.h>
    #include <algorithm>
    #include <map>
    #include <iterator>
    #include <wx/checkbox.h>
    #include <wx/spinctrl.h>
    #include <wx/window.h>
    #include <wx/utils.h> 
    #include <locale>
    #include <functional>
    #include <iostream>
    #include "extern.h"
    #include <filesystem>
    #include <boost/uuid/uuid.hpp>            // uuid class
    #include <boost/uuid/uuid_generators.hpp> // generators
    #include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
    #include <boost/lexical_cast.hpp>
    #include <wx/statline.h>
    #include <sqlite3.h>
    #include <iomanip>
    #include <iterator>
    #include <fstream>
    #include "openssl/sha.h"
    #include <wx/calctrl.h>



    using namespace std::placeholders;
    namespace fs = std::filesystem;

    const char * wxstring_to_char(wxString i);
    std::string generateId();

    std::string convertToString(const char* a);
    void create_login();
    std::string sha256(const std::string str);

    enum {
        TEXT_Main = wxID_HIGHEST + 1,
        ID_EXIT = 231,
        ID_PERSONAL_RECORD = 10000,
        ID_SURNAME = 10001,
        ID_LASTNAME = 10002, 
        ID_AGE = 10003,
        ID_SEX = 10004,
        ID_NUM = 10005,
        ID_RESET = 10006,
        ID_ACCOUNT = 10007,
        ID_SRM = 2000,
        ID_SAVE = 3000,
        ID_PLOT = 4000,
        ID_LOC = 4001,
        ID_NH = 4002,
        ID_SR = 4003,
        ID_DR = 4004,
        ID_OBR = 4005,
        ID_TBR = 4006,
        ID_THBR = 4007,
        ID_BBR = 4008,
        ID_SRT = 5000,
        ID_DRT = 5001,
        ID_OBRT = 5002,
        ID_TBRT = 5003,
        ID_THBRT = 5004,
        ID_BBRT = 5005,
        ID_CB1 = 601,
        ID_CB2 = 602,
        ID_CB3 = 603,
        ID_CB4 = 604,
        ID_CB5 = 605,
        ID_CB6 = 606,
        ID_LIST_SAVE = 700,
        ID_NAME = 710,
        ID_NAME1 = 711,
        ID_LIST_DLG_CLOSE = 712,
        ID_EMAIL = 900,
        ID_HOUSE_NO = 910,
        ID_HOUSE_TYPE = 911,
        ID_MONTH = 920,
        ID_YEAR = 921
    };

    typedef struct{

        std::string ownerId;
        std::string plotId;
        std::string tenantId;

    } data;



    class CustomDialog : public wxDialog
    {
    public:
        CustomDialog();
        CustomDialog(const wxString& title, double x, double y);
        ~CustomDialog();
        bool TransferDataToWindow();
        bool TransferDataFromWindow();
        void OnSave(wxCommandEvent &event);
        void OnExit(wxCommandEvent& event);
        void Init();
        void Next(wxCommandEvent &event);
        void Reset(wxCommandEvent &event);
        void OnClose(wxCloseEvent& event );

        //void check();


        std::map<wxString, wxString> getName();
        
        int getGender();
        int get_num();
        int get_acc();


    protected:
   
    private:
        wxString g_data, m_bFileNotSaved ;
        wxString surname, lstname;
        int gender;
        wxString account_num;
        wxString num;
        int flag = 0;

    };


    class PlotDialog : public wxDialog
    {
        public:
            PlotDialog();
            PlotDialog(const wxString & title, double x, double y);
            ~PlotDialog();

            std::map<double, int> GetSingle();
            std::map<double, int> GetDouble();
            std::map<double, int> GetOneBedrm();
            std::map<double, int> GetTwoBedrm();
            std::map<double, int> GetBedSitter();
            std::map<double, int> GetThrBedrm();
            void set(std::string Id);
        

            //CustomDialog Cdlg;

        protected:
            void Init();
            bool TransferDataToWindow();
            bool TransferDataFromWindow();
            void create_plot_info(wxPanel *panel);
            void OnSave(wxCommandEvent& event);
            void OnBack();
            void OnReset(wxCommandEvent& event);
            void OnExit(wxCommandEvent& event);
        
        private:
            wxBoxSizer *vbox;

            wxString plot_name;
            wxString location;
            int num_of_rooms, nsingle,
                     ndouble, n_onebdrm,
                     nbedsitter, ntwobdrm,
                     nthreebdrm;
            bool Single, Double,
                      One_bedrm, bedsitter,
                      two_bedrm, three_bedrm;
            double single_rent,
                   Double_rent,
                   One_bedrm_rent;
            double bedsitter_rent,
                   three_bedrm_rent,
                   two_bedrm_rent;
    };


    class NewFileDialog: public wxDialog
    {   public:
            NewFileDialog(const wxString& title);
            void NewFile(wxCommandEvent& WXUNUSED(event));
            //~NewFiledialog();

            wxTextCtrl *MainEditBox;
            wxString CurrentDocPath;

    };


    class Tenant : public wxDialog
    {
        public:
            Tenant(const wxString& title,  const wxArrayString& room_type, std::string plotId, double x, double y, int num_of_rooms);
            ~Tenant();
            void init();
            bool TransferDataToWindow();
            bool TransferDataFromWindow();
            void save(wxCommandEvent& event);
            void quit(wxCommandEvent& event);
            void Reset(wxCommandEvent& event);
            void check();
            std::string plotid;
            
            
        private:
            wxString surname;
            wxString lstname;
            wxString g_data, Id_num, gender;
            wxString phone, house_type, monthstr;
            int month, year, house_no;
            int max_room;
            

    };

    class EditPlotDialog : public wxDialog
    {
        public:
            EditPlotDialog(const wxString& title, wxString tb, wxString acc, wxString var,
                                 wxString var1, wxString lc, wxString varname1, wxString varname2, double x, double y);
            ~EditPlotDialog();
            void onsave(wxCommandEvent& event);
            void onclose(wxCommandEvent &event);
            bool TransferDataFromWindow();


        private:
            wxString name;
            wxString name1;
            wxString varnm;
            wxString varloc;
            wxString tbstr;
            wxString lcstr;
            wxString acct;
    };

class Sign : public wxDialog
{
    public:
        Sign(const wxString& title, double x, double y);

        virtual ~Sign();
        void onquit(wxCommandEvent& event);
        bool check_res();


    private:
        wxStaticText *ag_name;
        wxStaticText *fname_t;
        wxStaticText *sname_t;
        wxStaticText *phone_t;
        wxStaticText *phonet_2;
        wxStaticText *loc_t;
        wxStaticText *pass_t;
        wxStaticText *pass2_t;
        wxStaticText *username;
        wxStaticText *usermax;
        wxStaticText *email;
        wxStaticText *web;

        wxTextCtrl *ag_name_entry;
        wxTextCtrl *fname_entry;
        wxTextCtrl *sname_entry;
        wxTextCtrl *phone_entry;
        wxTextCtrl *phone_entry2;
        wxTextCtrl *loc_entry;
        wxTextCtrl *pass_entry;
        wxTextCtrl *pass2_entry;
        wxTextCtrl *username_entry;
        wxTextCtrl *email_entry;
        wxTextCtrl *web_entry;

        wxStaticLine *line;
        wxButton *reg;
        wxButton *quit;
        bool res;


    enum
    {
        BUTTON_save = wxID_HIGHEST + 10,
        BUTTON_quit = wxID_HIGHEST + 11
    };

        void OnSave(wxCommandEvent& event);

};


class FormLogin :  public wxDialog
{
    public:
        FormLogin(const wxString& title, double x, double y);
    
        // Destructor
        virtual ~FormLogin();
        bool check_res();
    
    private:
        wxStaticText* m_usernameLabel;
        wxStaticText* m_passwordLabel;
        wxTextCtrl* m_usernameEntry;
        wxTextCtrl* m_passwordEntry;
        wxButton* m_buttonLogin;
        wxButton* m_buttonQuit;
        wxButton* signup;
        wxMessageDialog *dlg;
        wxCheckBox *checkbox;
        wxStaticText *fpwd;
        wxStaticText *checktxt;
        wxStaticLine  *line;
        Sign *formsign;
        int rows;
        bool res;
        double xdim, ydim;
    
    private:
        void OnQuit(wxCommandEvent& event);
        void OnLogin(wxCommandEvent& event);
        void OnSign(wxCommandEvent& event);
        void OnReset(wxCommandEvent& event);
        void check();
    // void OnRem(wxCommandEvent& event);
        //bool checkpasscode();
        //std::string namecode;
        //std::string passwordcode;

        std::map<std::string, std::string> get_details();

        sqlite3_stmt *stmt;
        char* messaggeError;
        const char* tail;
        sqlite3 *db;
        int rc;
        std::string sql;
    
    private:
        DECLARE_EVENT_TABLE()
    
        enum
        {
            BUTTON_Login = wxID_HIGHEST + 1,
            BUTTON_Sign = wxID_HIGHEST + 2,
            CHECKBOX_id = wxID_HIGHEST + 3,
            REM_id = wxID_HIGHEST + 4
        };
};


class ForgetPassword : public wxDialog
{
    public:
        ForgetPassword(const wxString& title, double x, double y);

        virtual ~ ForgetPassword();
        void onsave(wxCommandEvent& event);
        std::map<std::string, std::string> get_details();
        void update_details(std::string username, std::string phone, std::string pass);
        void onquit(wxCommandEvent& event);

    private:
        sqlite3_stmt *stmt;
        char* messaggeError;
        const char* tail;
        sqlite3 *db;
        int rc;

        wxStaticText *newpasswd;
        wxStaticText *repasswd;
        wxStaticText *phone;
        wxStaticText *username;

        wxTextCtrl *newpasswd_entry;
        wxTextCtrl *repasswd_entry;
        wxTextCtrl *phone_entry;
        wxTextCtrl *username_entry;

        wxStaticLine *line;
        wxButton *change;
        wxButton *quit;

    enum
    {
        BUTTON_save = wxID_HIGHEST + 20,
        BUTTON_quit = wxID_HIGHEST + 21
    };

};

    class BankDialog : public wxDialog
    {
        public:
            BankDialog(const wxString& title, double x, double y);
            virtual ~ BankDialog();
            void onsave(wxCommandEvent& event);
            void onclose(wxCommandEvent &event);
            bool TransferDataFromWindow();
            void Init();
           // bool TransferDataToWindow();
            bool checkvalues();


        private:
            wxTextCtrl *name_entry, 
                        *amount, *transaction_id,
                        *balance, *room_no,
                        *idnum_entry;
            
            wxChoice *plotname;
            wxArrayString plotchoicetxt;

            wxCalendarCtrl *cal;
            wxButton *quit;
            wxButton *ok;
            wxString name, trans_id,
                     plotnametext, month;

            int rent_amount, rent_bal;
            int day, year, rmno, zId_Num; 

            //database variables
            sqlite3 *db;
            char* MError;
            std::string sqltxt;
            int rs;
            const char *tail;
            sqlite3_stmt *stmt;

            std::vector<plot_info> bank_array;

        enum
        {
            ID_BT_OK,
            ID_BT_CLOSE,
            ID_RECEIV,
            ID_TRANS,
            ID_AMT,
            ID_BAL,
            ID_PLOT,
            ID_RM,
            ID_DY,
            NUM_ID
        };
    };


#endif