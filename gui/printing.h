#ifndef EASYPRINTOUT_H
#define EASYPRINTOUT_H
    #include "wx/wxprec.h"
    #include <wx/string.h>
    #include <wx/wx.h>
    #include <wx/frame.h>
    #include <wx/menu.h>
    #include "wx/image.h"
    #include <wx/wxhtml.h>
    #include "wx/html/htmlwin.h"
    #include "wx/html/htmprint.h"


    enum
    {
    // menu items
        Minimal_Quit = 11000,
        Minimal_Print,
        Minimal_Preview,
        Minimal_PageSetup,
        Minimal_Open,
        Minimal_PrintSmall,
        Minimal_PrintNormal,
        Minimal_PrintHuge
    };

    

    class Myprint: public wxFrame
    {	
        public:
            Myprint(wxWindow *parent, const wxString& title, const wxPoint& pos,
                    const wxSize& size, long style, const wxString &name);
            virtual ~Myprint();
            void OnQuit(wxCommandEvent& WXUNUSED(event));

            void OnPageSetup(wxCommandEvent& WXUNUSED(event));
            void OnPrint(wxCommandEvent& WXUNUSED(event));
            void OnPreview(wxCommandEvent& WXUNUSED(event));
            void OnPrintSmall(wxCommandEvent& WXUNUSED(event));
            void OnPrintNormal(wxCommandEvent& WXUNUSED(event));
            void OnPrintHuge(wxCommandEvent& WXUNUSED(event));
            
        private:
            wxHtmlWindow *m_Html;
            wxHtmlEasyPrinting *m_Prn;
            wxString m_Name;

    };

#endif
