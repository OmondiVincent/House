#ifndef FRAME_H
#define FRAME_H
    #include <wx/wx.h>
    #include <wx/wxprec.h>
    #include <experimental/filesystem>
    #include "wx/fdrepdlg.h"
    #include "wx/filedlg.h"
    #include "wx/textfile.h"
    #include <string>
    #include <wx/toolbar.h>
    #include <wx/artprov.h>
    #include <wx/notebook.h>
    #include <wx/cmndata.h>
    #include "wx/printdlg.h"
    #include <cmath>
    #include <wx/msgdlg.h>
    #include <wx/clipbrd.h>
    #include <wx/menu.h>
    #include <wx/toplevel.h>
    #include <string>
    #include <wx/filename.h>
    #include <wx/srchctrl.h>
    #include <wx/stc/stc.h> 
    #include <wx/button.h>
    #include <wx/dataobj.h>
    #include <wx/window.h>
    #include <wx/stdpaths.h>
    #include "panel.h"
    #include <wx/notifmsg.h>
   // #include "printing.h"
    #include "wx/clipbrd.h"
    #include "wx/font.h"
    #include "wx/colordlg.h"
    #include <wx/progdlg.h>
    

    class MyFrame: public wxFrame
    {
        public:
            MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
            ~MyFrame();
            void OnQuit(wxCommandEvent & event);
            void OnHello(wxCommandEvent& e);
            void OnAbout(wxCommandEvent& e);
            void Open(wxCommandEvent& event);
            void NewFile(wxCommandEvent& WXUNUSED(event));
            void SaveFIle(wxCommandEvent& WXUNUSED(event));
            void OnCopy(wxCommandEvent& event);
            void OnPaste(wxCommandEvent& event);
            void Printout(wxCommandEvent& event);
            void OnPrintPreview(wxCommandEvent& WXUNUSED(event));

            void NewPage(wxCommandEvent& event);
            wxBookCtrlBase *GetCurrentBook() const { return m_bookCtrl; }

            void RecreateToolbar();
            void OnToggleToolbar(wxCommandEvent& WXUNUSED(event));
            void PopulateToolbar(wxToolBarBase* toolBar);
            void Bankpay(wxCommandEvent& WXUNUSED(event));

            //font functions
            void Increase_Font_Size(wxCommandEvent& event);
            void Decrease_Font_Size(wxCommandEvent& event);
            void Base_Font_Version(wxCommandEvent& event);
            void Bold_Font(wxCommandEvent& event);
            void Italic_Font(wxCommandEvent& event);
            void Light_Font(wxCommandEvent& event);
            void Oblique_Font(wxCommandEvent& event);
            void Underline_Font(wxCommandEvent& event);
            void Face_Font(wxCommandEvent& event);
            void Backup(wxCommandEvent& event);
            void Restore_Data(wxCommandEvent& event);


            wxFont font;
            int font_size;
            wxWindow *fontwindow;
            wxFontFamily GetFamilyFromUser();
            void DoChangeFont(const wxFont& font, const wxColour& col);

            //toggle, color && sort
            void Toggle_Plot(wxCommandEvent& event);
            void Toggle_Tenant(wxCommandEvent& event);
            void Sort_Plot(wxCommandEvent& event);
            void Sort_Tenat(wxCommandEvent& event);

            void OnSetFgColour(wxCommandEvent& event);
            void OnSetBgColour(wxCommandEvent& event);

            void OnSetFgColourO(wxCommandEvent& event);
            void OnSetBgColourO(wxCommandEvent& event);

            void SetBgColourL(wxCommandEvent& event);
            void SetBgColourR(wxCommandEvent& event);

            void OnStatusBarToggle(wxCommandEvent& WXUNUSED(event));

            
        private:
            LeftPanel *leftPanel;
            RightPanel *rightPanel;
            wxPanel *m_parent;

            //toolbar
            wxMenuBar *menubar;
            wxMenu *file;
            wxMenu *Edit;
            wxMenu *View;
            wxMenu *help;
            wxMenu *lic;
            wxMenu *imp;
            wxMenu *fontimp;
            wxMenu *toggle;
            wxMenu *sort;
            wxMenu *bcolor;
            wxMenu *fcolor;

            wxMenuItem *quit;
            BankDialog *bankp;

            bool m_showTooltips,
                 m_horzText;

            wxToolBarToolBase *m_searchTool;

            wxTextCtrl *MainEditBox;
            wxTextCtrl *m_textCtrl1, *mtext;
	        wxString CurrentDocPath;
            wxNotebook *newbk;
            wxFrame *newfrm;
            wxFrame *openfrm;
            wxTextCtrl *textctrl;
            wxToolBar *toolbar;
            //wxStandardPaths stdPath;

            wxBookCtrlBase *m_bookCtrl;
            wxFrame *CreateNewPage() const;

            wxString text, text1;
            wxPreviewFrameModalityKind m_previewModality;

            #if wxUSE_FINDREPLDLG
                wxFindReplaceData m_findData;

                wxFindReplaceDialog *m_dlgFind, *m_dlgReplace;

            #endif
            wxSearchCtrl *search;

            wxPrintDialogData g_printDialogData;
            wxPageSetupDialogData  m_pageSetupData;
            wxPrintData g_printData;
            wxNotificationMessage *notify;

            enum StatusBarKind
            {
                StatBar_Default,
                StatBar_Custom,
                StatBar_Max
            } m_statbarKind;

    };

    static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;


    enum {
        //ID_SEARCH,
        //ID_ADD,
        //TEXT_Main = wxID_HIGHEST + 1,
        DIALOGS_FIND,
        DIALOGS_REPLACE,
       // ID_CREATE,
        ID_TCHECK,
        ID_SCHECK,
        ID_TOOLBAR,
        ID_NEW_PAGE,
        ID_BANK_PAY,
        ID_MPESA_PAY,
        ID_FONT,
        Font_IncSize,
        Font_DecSize,
        Font_GetBaseFont,
        Font_Bold,
        Font_Light,
        Font_Italic,
        Font_Slant,
        Font_Underlined,
        Font_SetFamily,
        ID_Toggle_lines,
        ID_Sort,
        Id_toggle_lp,
        Id_toggle_rp,
        Id_sort_lp,
        Id_sort_rp,
        ID_back,
        ID_fore,
        ID_backO,
        ID_foreO,
        ID_backML,
        ID_backMR,
        ID_BACKUP,
        ID_RESTORE,
        ID_RENEW_LICENCE,
        ID_CHECK_LICENCE
    };
    
#endif

#define ADDED_PAGE_NAME                 wxT("Added ")

