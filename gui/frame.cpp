#include "frame.h"
#include "client.cpp"

static wxString GetSampleTitle()
{
    return "Font Sample";
}

MyFrame::MyFrame(const wxString &title, const wxPoint  &pos, const wxSize &size):
 wxFrame(NULL, wxID_ANY, title, pos, size){ 

    font = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

     #if USE_ASYNCHRONOUS_CLIPBOARD_REQUEST
        m_request = Idle;
        m_clipboardSupportsText = false;
    #endif

     menubar = new wxMenuBar;
     
    //creates a file submenu and appends some events
    file = new wxMenu;
    file->Append(wxID_NEW, wxT("&New"), wxT("Create new sticky notes"));
    file->Append(wxID_OPEN, wxT("&Open"), wxT("Open either receipt or report to view"));
    file->AppendSeparator();

            //creates another submenu 
        imp = new wxMenu;
        imp->Append(ID_BANK_PAY, wxT("&Bank payment....."), wxT("Enter Bank payment details"));
        imp->Append(ID_MPESA_PAY, wxT("&Mpesa Payment....."), wxT("Checks payment made by mpesa"));
        imp->Append(wxID_ANY, wxT("&Paypal..."), wxT("Enter payment details"));

    file->AppendSubMenu(imp, wxT("&Payment"), wxT("Payment"));
    file->Append(ID_BACKUP, wxT("Backup File"), wxT("Makes a backup to the server"));
    file->Append(ID_RESTORE, wxT("Restore File"), wxT("Restores backup date from the server"));
    file->AppendSeparator();

    //creates a quit submenu this is used to quit from the application
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    file->Append(quit);

    //creates an Edit menu, this allows one to edit files
    Edit = new wxMenu;
    Edit->Append(wxID_COPY, wxT("&Copy\tCtrl+c"));
    Edit->Append(wxID_CUT, wxT("&Cut\tCtrl+x"));
    Edit->Append(wxID_PASTE, wxT("&Paste\tCtrl+v"));
    Edit->Append(wxID_DELETE, wxT("&Delete\tCtrl+d"));
    Edit->AppendSeparator();
    Edit->Append(wxID_FIND, wxT("&Find"));
    Edit->Append(wxID_REPLACE, wxT("&Replace"));
    Edit->AppendSeparator();

        //toggle lines submenus
        toggle = new wxMenu();
        toggle->Append(Id_toggle_lp, wxT("&Plot panel"), wxT("Create separation lines on plot litst"));
        toggle->Append(Id_toggle_rp, wxT("&Tenant panel"), wxT("Create separation lines on Tenant list"));
    Edit->AppendSubMenu(toggle, wxT("&Toggle lines\tShift+Ctrl+l"), wxT("Create lines in the list on the screen"));

        //sort panels submenu
        sort = new wxMenu();
        sort->Append(Id_sort_lp, wxT("Plot panel"), wxT("Sorting Plot Items"));
        sort->Append(Id_sort_rp, wxT("Tenant panel"), wxT("Sorting Tenant Items"));
    
    Edit->AppendSubMenu(sort, wxT("&Sort Item\tShift+Ctrl+S"), wxT("Sorting Items of a list"));
    
    //creates view menu
    View = new wxMenu;
    View->Append(ID_TCHECK, wxT("&Toolbar\tCtrl+t"), wxT("Enabel or diable toolbar"), wxITEM_CHECK);
    View->Append(ID_SCHECK, wxT("&Statusbar\tShift+Ctrl+b"), wxT("Enable or diable statusbar"), wxITEM_CHECK);
    View->AppendSeparator();
        
        // a submenu for menu font changing
        fontimp = new wxMenu;
            fontimp->Append(Font_IncSize, "&Increase font size by 1 points\tCtrl-I", wxT("Increases the font size by 1"));
            fontimp->Append(Font_DecSize, "&Decrease font size by 1 points\tCtrl-D", wxT("Decreases the font size by 1"));
            fontimp->Append(Font_GetBaseFont, "Use &base version of the font\tCtrl-0", wxT("Restore font style to default"));
            fontimp->AppendSeparator();
            fontimp->AppendCheckItem(Font_Bold, "&Bold\tCtrl-B", "Toggle bold state");
            fontimp->AppendCheckItem(Font_Light, "&Light\tCtrl-L", "Toggle light state");
            fontimp->AppendSeparator();
            fontimp->AppendCheckItem(Font_Italic, "&Italic\tCtrl-O", "Toggle italic state");

            #ifndef __WXMSW__
                // under wxMSW slant == italic so there's no reason to provide another menu item for the same thing
                fontimp->AppendCheckItem(Font_Slant, "&Slant\tCtrl-S", "Toggle slant state");

            #endif
                fontimp->AppendSeparator();
                fontimp->AppendCheckItem(Font_Underlined, "&Underlined\tCtrl-U",
                                        "Toggle underlined state");

                fontimp->AppendSeparator();
                fontimp->Append(Font_SetFamily, "Set font family", "Sets the font type");

    View->AppendSubMenu(fontimp, wxT(" Change Font type\tCtrl+f"),  wxT("changes font type"));
    View->AppendSeparator();

    //background color
            bcolor = new wxMenu();

            bcolor->Append(ID_backML, wxT("Plot panel.."), wxT("Changes the background of the plot panel"));
            bcolor->Append(ID_backMR, wxT("Tenant panel.."), wxT("Changes the background of the Tenant panel"));
            bcolor->Append(ID_back, wxT("Plot List"), wxT("Changes the background of the plot list"));
            bcolor->Append(ID_backO, wxT("Tenant list"), wxT("Changes the background of the tenant list"));

    View->AppendSubMenu(bcolor, wxT("&Set Backgroundcolor"), wxT("Changes the background"));

    //foreground color
            fcolor= new wxMenu();
            fcolor->Append(ID_fore, wxT("Plot panel.."), wxT("Changes plot text colour"));
            fcolor->Append(ID_foreO, wxT("Tenant panel.."), wxT("Changes tenant text colour"));

    View->AppendSubMenu(fcolor, wxT("&Set Foregroundcolor"), wxT("Changes the text colour"));

    //creates a help submenu
    help = new wxMenu;
    help->Append(wxID_ANY, wxT("&Documentation"), wxT("Help on how to navigate the software"));
        lic = new wxMenu;
        lic->Append(ID_CHECK_LICENCE, wxT("&Check Licence"), wxT("Check if licence is valid"));
        lic->Append(ID_RENEW_LICENCE, wxT("&Renew Licence"), wxT("Renew the licence"));
    help->AppendSubMenu(lic, wxT("&Licence"), wxT("Licence"));
    help->Append(wxID_ANY, wxT("Download Updates"), wxT("Checks and Downloads update"));
    help->Append(wxID_ABOUT, wxT("About"), wxT("About the software"));

    menubar->Append(file, wxT("&File"));
    menubar->Append(Edit, wxT("&Edit"));
    menubar->Append(View, wxT("&View"));
    menubar->Append(help, wxT("&Help"));

    //menubar->Append(file, wxT("&File"));
    
    SetMenuBar(menubar);

    //toolbar->Set#include "printout.h"

    RecreateToolbar();
    CreateStatusBar();
    SetStatusText(wxT("Hello"));
 

    m_parent = new wxPanel(this, wxID_ANY);

    leftPanel = new LeftPanel(m_parent);
    rightPanel= new RightPanel(m_parent);
    // Main panels
    wxBoxSizer *mainsizer = new wxBoxSizer(wxHORIZONTAL);
    mainsizer->Add(leftPanel, 1, wxEXPAND | wxLEFT, 5);
    mainsizer->Add(rightPanel, 2, wxEXPAND| wxRIGHT, 5);

    m_parent->SetSizer(mainsizer);
    this->Center();

    /////Notification 
   // notify = new wxNotificationMessage("Notification", "Welcome , you have a new message", NULL);
  //  notify->Show(10);


    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnQuit));
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::NewFile, this, wxID_NEW);
    Bind(wxEVT_MENU, &MyFrame::Open, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MyFrame::Bankpay, this, ID_BANK_PAY);
    Bind(wxEVT_MENU, &MyFrame::Increase_Font_Size, this, Font_IncSize);
    Bind(wxEVT_MENU, &MyFrame::Decrease_Font_Size, this, Font_DecSize);
    Bind(wxEVT_MENU, &MyFrame::Base_Font_Version, this, Font_GetBaseFont);
    Bind(wxEVT_MENU, &MyFrame::Bold_Font, this, Font_Bold);
    Bind(wxEVT_MENU, &MyFrame::Light_Font, this, Font_Light);
    Bind(wxEVT_MENU, &MyFrame::Underline_Font, this, Font_Underlined);
    Bind(wxEVT_MENU, &MyFrame::Italic_Font, this, Font_Italic);
    Bind(wxEVT_MENU, &MyFrame::Oblique_Font, this, Font_Slant);
    Bind(wxEVT_MENU, &MyFrame::Face_Font, this, Font_SetFamily);
    Bind(wxEVT_MENU, &MyFrame::OnToggleToolbar, this, ID_TCHECK);
    Bind(wxEVT_MENU, &MyFrame::Toggle_Plot, this, Id_toggle_lp);
    Bind(wxEVT_MENU, &MyFrame::Toggle_Tenant, this, Id_toggle_rp);
    Bind(wxEVT_MENU, &MyFrame::Sort_Plot, this, Id_sort_lp);
    Bind(wxEVT_MENU, &MyFrame::Sort_Tenat, this, Id_sort_rp);
    Bind(wxEVT_MENU, &MyFrame::OnSetBgColour, this, ID_back);
    Bind(wxEVT_MENU, &MyFrame::OnSetFgColour, this, ID_fore);
    Bind(wxEVT_MENU, &MyFrame::OnSetBgColourO, this, ID_backO);
    Bind(wxEVT_MENU, &MyFrame::OnSetFgColourO, this, ID_foreO);
    Bind(wxEVT_MENU, &MyFrame::SetBgColourL, this, ID_backML);
    Bind(wxEVT_MENU, &MyFrame::SetBgColourR, this, ID_backMR);
    Bind(wxEVT_MENU, &MyFrame::OnStatusBarToggle, this, ID_SCHECK);
    Bind(wxEVT_MENU, &MyFrame::Backup, this, ID_BACKUP);
    Bind(wxEVT_MENU, &MyFrame::Restore_Data, this, ID_RESTORE);
}

MyFrame::~MyFrame(){

    Unbind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Unbind(wxEVT_MENU, &MyFrame::NewFile, this, wxID_NEW);
    Unbind(wxEVT_MENU, &MyFrame::Open, this, wxID_OPEN);
    Unbind(wxEVT_MENU, &MyFrame::OnToggleToolbar, this, ID_TCHECK);
    Unbind(wxEVT_MENU, &MyFrame::Bankpay, this, ID_BANK_PAY);
   // Unbind(wxEVT_MENU, &MyFrame::OnCopy, this, wxID_COPY);
   // Unbind(wxEVT_MENU, &MyFrame::OnPaste, this, wxID_PASTE);

   // delete notify;

}


void MyFrame::NewFile(wxCommandEvent& WXUNUSED(event))
{
    newfrm = new wxFrame(this, wxID_ANY, wxT_2("Sticky Notes* "), wxDefaultPosition,
                wxSize(xpixel * 0.25, ypixel * 0.6), wxMINIMIZE_BOX |  wxCLOSE_BOX);
    newbk = new wxNotebook(newfrm, wxID_ANY);

    
    
    MainEditBox = new wxTextCtrl(newbk, TEXT_Main, _("Hi!"), wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
    
    newbk->AddPage(MainEditBox, wxT_2("New Doc"));
	// Clear the edit box
	MainEditBox->Clear();

    newfrm->Show();


}

void MyFrame::Open(wxCommandEvent& WXUNUSED(event)){

    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("Text files (*.html)|*.htm");

    wxTextFile file;


    openfrm = new wxFrame(this, wxID_ANY, wxT(" "), wxDefaultPosition, wxSize(550, 600));

    textctrl = new wxTextCtrl(openfrm, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);

    wxFileDialog dialog(openfrm, caption, wxEmptyString, wxEmptyString, wildcard, wxFD_OPEN);
    
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();
        //int filterIndex = dialog.GetFilterIndex();

        Myprint *printfile = new Myprint(this, ("Printing "), wxDefaultPosition,
                               wxSize(xpixel * 0.25, ypixel * 0.6), wxMINIMIZE_BOX | wxCLOSE_BOX, path);
        printfile->Show();

       
    }

}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    //notify->Close();
    Close(true);

}

void MyFrame::OnAbout(wxCommandEvent& e){
    wxMessageBox("HouMas\nVersion 1.0.1\nCross platform",
                "House Managemant System", wxOK| wxCANCEL | wxICON_INFORMATION);
}


void MyFrame::OnCopy(wxCommandEvent& event){
    if (wxTheClipboard->Open()){
        if (wxTheClipboard->IsSupported(wxDF_UNICODETEXT)){
            mtext->Clear();
            wxString str = m_textCtrl1->GetValue();
            wxTextDataObject *data = new wxTextDataObject(str);
            //data.SetText(str);
            wxTheClipboard->SetData(data);
        }
    }
    wxTheClipboard->Close();
    event.Skip();
}

void MyFrame::OnPaste(wxCommandEvent& event){
    if (wxTheClipboard->Open()){
        if (wxTheClipboard->IsSupported(wxDF_UNICODETEXT)){
            mtext->Clear();
            wxTextDataObject data;
            wxTheClipboard->GetData(data);
            mtext->SetValue(data.GetText());
        }
    }
    wxTheClipboard->Close();
    event.Skip();
}

void MyFrame::RecreateToolbar()
{
    // delete and recreate the toolbar
    wxToolBarBase *toolBar = GetToolBar();
    long style = toolBar ? toolBar->GetWindowStyle() : TOOLBAR_STYLE;

    if (toolBar && m_searchTool && m_searchTool->GetToolBar() == NULL)
    {
        // see ~MyFrame()
        toolBar->AddTool(m_searchTool);
    }
    m_searchTool = NULL;

    delete toolBar;

    SetToolBar(NULL);

    toolBar = CreateToolBar(style, ID_TCHECK);

    PopulateToolbar(toolBar);
}

void MyFrame::OnToggleToolbar(wxCommandEvent& WXUNUSED(event))
{
    wxToolBar *tbar = GetToolBar();

    if ( !tbar )
    {
        RecreateToolbar();
    }
    else
    {
        delete tbar;
    }
}


void MyFrame::PopulateToolbar(wxToolBarBase* toolBar){

    wxBitmap openicon("../icon/open.png");
    wxBitmap newicon("../icon/new.png");
    wxBitmap bankicon("../icon/bank.png");
    wxBitmap mpesaicon("../icon/mpesa5.png");
    wxBitmap copyicon("../icon/copy.png");
    wxBitmap cuticon("../icon/cut.png");
    wxBitmap pasteicon("../icon/paste.png");
    wxBitmap backup("../icon/backup.png");
    wxBitmap restore("../icon/restore.png");
    wxBitmap check_licence("../icon/check_licence.png");
    wxBitmap renew_licence("../icon/renew_licence.png");
    wxBitmap helpicon("../icon/help.png");
    wxBitmap quiticon("../icon/exit.png");

    //creates toolbar and appends tools
    toolBar->AddTool(wxID_NEW, wxT("&New"), newicon, wxT_2("New file"));
    toolBar->AddTool(wxID_OPEN,wxT("&Open"), openicon, wxT_2("Open file"));
    toolBar->AddTool(ID_BANK_PAY, wxT("Bank payment"), bankicon, wxT_2("Bank payment"));
    toolBar->AddTool(ID_MPESA_PAY, wxT("Mpesa payment"), mpesaicon, wxT_2("Mpesa payment"));
    toolBar->AddTool(wxID_COPY, wxT("Copy"), copyicon, wxT_2("Copy"));
    toolBar->AddTool(wxID_CUT, wxT("Cut"), cuticon, wxT("Cut"));
    toolBar->AddTool(wxID_PASTE, wxT("Paste"), pasteicon, wxT("Paste"));
    toolBar->AddTool(ID_BACKUP, wxT("Backup"), backup, wxT("Backup"));
    toolBar->AddTool(ID_RESTORE, wxT("Restore"), restore, wxT("Restore"));
    toolBar->AddTool(ID_CHECK_LICENCE, wxT("Check licence"), check_licence, wxT("check licence"));
    toolBar->AddTool(ID_RENEW_LICENCE, wxT("renew licence"), renew_licence, wxT("renew licence"));
    toolBar->AddTool(wxID_HELP, wxT("help"), helpicon, wxT("help"));
    toolBar->AddTool(wxID_EXIT, wxT("exit"), quiticon, wxT("exit"));
}

void MyFrame::NewPage(wxCommandEvent& event){

    wxBookCtrlBase *currBook = GetCurrentBook();

    if ( currBook )
    {
        static unsigned s_pageAdded = 0;
        //wxTextCtrl *othebox;
           MainEditBox = new wxTextCtrl(m_bookCtrl, TEXT_Main, _("Hi!"), wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
    
        currBook->AddPage(MainEditBox,
                          wxString::Format(
                            ADDED_PAGE_NAME wxT("%u"),
                            ++s_pageAdded), true);
                          //GetIconIndex(currBook));
    }
}

void MyFrame::OnStatusBarToggle(wxCommandEvent& WXUNUSED(event))
{
    wxStatusBar *statbarOld = GetStatusBar();
    if ( statbarOld )
    {
        SetStatusBar(NULL);
        delete statbarOld;
    }
    else
    {
        CreateStatusBar();
    }
}



void MyFrame::Bankpay(wxCommandEvent& WXUNUSED(event)){

    bankp = new BankDialog("Bank Payment", 537.6 , 702);
    bankp->Show(true);

}

/**************************************************************************************************************************************************************/
//font faunctions starts here

void MyFrame::Increase_Font_Size(wxCommandEvent& event){

    font_size = font.GetPointSize();

    font.SetPointSize(font_size + 2);

    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);
}

void MyFrame::Decrease_Font_Size(wxCommandEvent& event){

    font_size = font.GetPointSize();

    if (font_size <= 6 ){
        //Do nothing
    } else{

        font.SetPointSize(font_size - 2);

        this->SetFont(font);
        m_parent->SetFont(font);
        leftPanel->m_listCtrl->SetOwnFont(font);
        lview->SetOwnFont(font);
        h_name->SetOwnFont(font);
    }
}

void MyFrame::Base_Font_Version(wxCommandEvent& event){

    font = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
    
    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);

}

void MyFrame::Bold_Font(wxCommandEvent& event){

    font.SetWeight(wxFONTWEIGHT_BOLD);

    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);

}

void MyFrame::Light_Font(wxCommandEvent& event){

    font.SetWeight(wxFONTWEIGHT_BOLD);

    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);

}

void MyFrame::Oblique_Font(wxCommandEvent& event){

    font.SetStyle(wxFONTSTYLE_SLANT);

    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);

}

void MyFrame::Italic_Font(wxCommandEvent& event){

    font.SetStyle(wxFONTSTYLE_ITALIC);

    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);

}

void MyFrame::Underline_Font(wxCommandEvent& event){

    font.SetUnderlined(true);

    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);

}

wxFontFamily MyFrame::GetFamilyFromUser()
{
    wxArrayString names;
    wxArrayInt families;

    families.push_back(wxFONTFAMILY_DECORATIVE);
    families.push_back(wxFONTFAMILY_ROMAN);
    families.push_back(wxFONTFAMILY_SCRIPT);
    families.push_back(wxFONTFAMILY_SWISS);
    families.push_back(wxFONTFAMILY_MODERN);
    families.push_back(wxFONTFAMILY_TELETYPE);

    names.push_back("DECORATIVE");
    names.push_back("ROMAN");
    names.push_back("SCRIPT");
    names.push_back("SWISS");
    names.push_back("MODERN");
    names.push_back("TELETYPE");

    int i = wxGetSingleChoiceIndex
            (
                "Choose the family",
                GetSampleTitle(),
                names,
                this
            );

    return i == -1 ? wxFONTFAMILY_DEFAULT : (wxFontFamily)families[i];
}

void MyFrame::Face_Font(wxCommandEvent& event){

    wxFontFamily f = GetFamilyFromUser();
    wxColor color=  this->GetForegroundColour();
    font.SetFamily(f);
    DoChangeFont(font, color);

}

void MyFrame::DoChangeFont(const wxFont& font, const wxColour& col)
{
    
    this->SetFont(font);
    m_parent->SetFont(font);
    leftPanel->m_listCtrl->SetOwnFont(font);
    lview->SetOwnFont(font);
    h_name->SetOwnFont(font);

    // update the state of the bold/italic/underlined menu items
    wxMenuBar *mbar = GetMenuBar();
    if ( mbar )
    {
        mbar->Check(Font_Light, font.GetWeight() == wxFONTWEIGHT_LIGHT);
        mbar->Check(Font_Bold, font.GetWeight() == wxFONTWEIGHT_BOLD);

        mbar->Check(Font_Italic, font.GetStyle() == wxFONTSTYLE_ITALIC);
        #ifndef __WXMSW__
            mbar->Check(Font_Slant, font.GetStyle() == wxFONTSTYLE_SLANT);
        #endif

        mbar->Check(Font_Underlined, font.GetUnderlined());
    }
}

static const int NUM_ICONS = 9;

int wxCALLBACK
MyCompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
    // inverse the order
    if (item1 < item2)
        return 1;
    if (item1 > item2)
        return -1;

    return 0;
}


void MyFrame::Toggle_Plot(wxCommandEvent& event){

    leftPanel->m_listCtrl->SetSingleStyle(wxLC_HRULES | wxLC_VRULES, event.IsChecked());
}

void MyFrame::Toggle_Tenant(wxCommandEvent& event){


    lview->SetSingleStyle(wxLC_HRULES | wxLC_VRULES, event.IsChecked());
}

void MyFrame::Sort_Plot(wxCommandEvent& event){

    leftPanel->m_listCtrl->SortItems(MyCompareFunction, 0);
}

void MyFrame::Sort_Tenat(wxCommandEvent& event){

    lview->SortItems(MyCompareFunction, 0);
}

void MyFrame::OnSetFgColour(wxCommandEvent& event)
{

    leftPanel->m_listCtrl->SetForegroundColour(wxGetColourFromUser(this));
    leftPanel->m_listCtrl->Refresh();

}

void MyFrame::OnSetFgColourO(wxCommandEvent& event)
{

    lview->SetForegroundColour(wxGetColourFromUser(this));
    lview->Refresh();
}

void MyFrame::OnSetBgColour(wxCommandEvent& event)
{

    leftPanel->m_listCtrl->SetBackgroundColour(wxGetColourFromUser(this));
    leftPanel->m_listCtrl->Refresh();
}

void MyFrame::OnSetBgColourO(wxCommandEvent& event)
{

    lview->SetBackgroundColour(wxGetColourFromUser(this));
    lview->Refresh();

}

void MyFrame::SetBgColourL(wxCommandEvent& event)
{

    leftPanel->SetBackgroundColour(wxGetColourFromUser(this));
    leftPanel->Refresh();
}

void MyFrame::SetBgColourR(wxCommandEvent& event)
{

    rightPanel->SetBackgroundColour(wxGetColourFromUser(this));
    rightPanel->Refresh();

}

void MyFrame::Backup(wxCommandEvent& event){


    process_data(9765);


}

void MyFrame::Restore_Data(wxCommandEvent& event){

    process_data(9766);

}