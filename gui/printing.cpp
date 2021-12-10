#include "printing.h"


Myprint::Myprint(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString &name)
        : wxFrame(parent, wxID_ANY, title, pos, size, style)
{

    wxWindow::SetMinSize(wxSize(400, 500));

    // create a menu bar
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(Minimal_PageSetup, _("Page &Setup"));
    menuFile->Append(Minimal_Preview, _("Print pre&view..."));
    menuFile->Append(Minimal_Print, _("Print...\tCtrl-P"));
    menuFile->AppendSeparator();
    menuFile->AppendSeparator();
    menuFile->Append(Minimal_Quit, _("&Exit"));

    wxMenu *menuFonts = new wxMenu;
    menuFonts->AppendRadioItem(Minimal_PrintSmall, _("&Small Printer Fonts"));
    menuFonts->AppendRadioItem(Minimal_PrintNormal, _("&Normal Printer Fonts"));
    menuFonts->AppendRadioItem(Minimal_PrintHuge, _("&Huge Printer Fonts"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _("&File"));
    menuBar->Append(menuFonts, _("F&onts"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

////#if wxUSE_STATUSBAR
    CreateStatusBar(1);
//#endif // wxUSE_STATUSBAR

     m_Html = new wxHtmlWindow(this);
     //m_Html -> SetRelatedFrame(this, _("HTML : %s"));
//#if wxUSE_STATUSBAR
     //m_Html -> SetRelatedStatusBar(0);
//#endif // wxUSE_STATUSBAR
    m_Name = name;
    m_Html -> LoadPage(m_Name);

    m_Prn = new wxHtmlEasyPrinting(_("Preview"), this);
   // m_Prn -> SetHeader(m_Name + "(@PAGENUM@/@PAGESCNT@)<hr>", wxPAGE_ALL);


    Bind(wxEVT_MENU, &Myprint::OnPageSetup, this, Minimal_PageSetup);
    Bind(wxEVT_MENU, &Myprint::OnPreview, this, Minimal_Preview);
    Bind(wxEVT_MENU, &Myprint::OnPrint, this, Minimal_Print);
    Bind(wxEVT_MENU, &Myprint::OnQuit, this, Minimal_Quit);

    Bind(wxEVT_MENU, &Myprint::OnPrintSmall, this, Minimal_PrintSmall);
    Bind(wxEVT_MENU, &Myprint::OnPrintNormal, this, Minimal_PrintNormal);
    Bind(wxEVT_MENU, &Myprint::OnPrintHuge, this, Minimal_PrintHuge);

   // To specify where the AFM files are kept on Unix,
    // you may wish to do something like this
    // m_Prn->GetPrintData()->SetFontMetricPath("/home/julians/afm");
}

// frame destructor
Myprint::~Myprint()
{
    wxDELETE(m_Prn);

    Unbind(wxEVT_MENU, &Myprint::OnPageSetup, this, Minimal_PageSetup);
    Unbind(wxEVT_MENU, &Myprint::OnPreview, this, Minimal_Preview);
    Unbind(wxEVT_MENU, &Myprint::OnPrint, this, Minimal_Print);
    Unbind(wxEVT_MENU, &Myprint::OnQuit, this, Minimal_Quit);

    Unbind(wxEVT_MENU, &Myprint::OnPrintSmall, this, Minimal_PrintSmall);
    Unbind(wxEVT_MENU, &Myprint::OnPrintNormal, this, Minimal_PrintNormal);
    Unbind(wxEVT_MENU, &Myprint::OnPrintHuge, this, Minimal_PrintHuge);
}

void Myprint::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void Myprint::OnPageSetup(wxCommandEvent& WXUNUSED(event))
{
    m_Prn -> PageSetup();
}


void Myprint::OnPrint(wxCommandEvent& WXUNUSED(event))
{
    m_Prn -> PrintFile(m_Name);
}


void Myprint::OnPreview(wxCommandEvent& WXUNUSED(event))
{
    m_Prn -> PreviewFile(m_Name);
}


void Myprint::OnPrintSmall(wxCommandEvent& WXUNUSED(event))
{
    m_Prn->SetStandardFonts(8);
}

void Myprint::OnPrintNormal(wxCommandEvent& WXUNUSED(event))
{
    m_Prn->SetStandardFonts(12);
}

void Myprint::OnPrintHuge(wxCommandEvent& WXUNUSED(event))
{
    m_Prn->SetStandardFonts(28);
}
