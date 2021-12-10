#include "panel.h"

std::map<wxString, wxString> nm;


// left panel class methods
LeftPanel::LeftPanel(wxPanel *parent)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
    //creates table in our database
    plot.create_table();

    this->SetBackgroundColour(wxColour(128, 128, 128));

    //wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true);

    //this->SetFont(font);

    m_parent = parent;
    createbt = new wxButton(this, ID_CREATE, wxT_2("New Client"),
                            wxDefaultPosition);
    addbt = new wxButton(this, ID_ADD, wxT_2("Add plot"),
                         wxDefaultPosition);

    wxButton *refresh = new wxButton(this, ID_REF, wxT_2("Refresh list"),
                                     wxDefaultPosition);

  //  m_imageListNormal = new wxImageList(32, 32, true);
  //  m_imageListSmall = new wxImageList(16, 16, true);

    m_listCtrl = new wxListView(this, -1, wxPoint(-1, -1), wxSize(-1, -1));

    

    m_listCtrl->AppendColumn("Plotname");
    m_listCtrl->AppendColumn("Location");
    m_listCtrl->AppendColumn("Rooms");

    m_listCtrl->SetColumnWidth(0, (xpixel / 3) * 0.32);
    m_listCtrl->SetColumnWidth(1, (xpixel / 3) * 0.45);
    m_listCtrl->SetColumnWidth(2, (xpixel / 3) * 0.15);

    m_listCtrl->SetTextColour(*wxBLUE);

    add_plot_info();

    wxBoxSizer *btbox = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);

    btbox->Add(createbt, 1, wxRIGHT | wxLEFT | wxTOP | wxEXPAND, 10);
    btbox->AddSpacer(25);
    btbox->Add(addbt, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 10);
    btbox->AddSpacer(25);
    btbox->Add(refresh, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 10);
    //lbox->Add(listview, 1, wxEXPAND);
    box->Add(btbox, 0, wxRIGHT | wxLEFT | wxTOP | wxEXPAND, 10);
    box->AddSpacer(10);

    box->Add(m_listCtrl, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

    SetSizerAndFit(box);

    Bind(wxEVT_BUTTON, &LeftPanel::OnCreate, this, ID_CREATE);
    Bind(wxEVT_BUTTON, &LeftPanel::OnAdd, this, ID_ADD);
    Bind(wxEVT_BUTTON, &LeftPanel::update_list, this, ID_REF);
    Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &LeftPanel::rightclick, this);
    Bind(wxEVT_LIST_ITEM_SELECTED, &LeftPanel::onclick, this);
    Bind(wxEVT_MENU, &LeftPanel::onDelete, this, ID_POP_DEL);
    Bind(wxEVT_MENU, &LeftPanel::onedit, this, ID_EDIT_LIST);
    Bind(wxEVT_MENU, &LeftPanel::addtenant, this, ID_ADD);
    Bind(wxEVT_MENU, &LeftPanel::print_report, this, ID_PRINT_REPORT);

    //m_listCtrl->populateview();
}

LeftPanel::~LeftPanel()
{
    Unbind(wxEVT_BUTTON, &LeftPanel::OnCreate, this, ID_CREATE);
    Unbind(wxEVT_BUTTON, &LeftPanel::OnAdd, this, ID_ADD);
    Unbind(wxEVT_BUTTON, &LeftPanel::update_list, this, ID_REF);
    Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &LeftPanel::rightclick, this);
    Unbind(wxEVT_LIST_ITEM_SELECTED, &LeftPanel::onclick, this);
    Unbind(wxEVT_MENU, &LeftPanel::onDelete, this, ID_POP_DEL);
    Unbind(wxEVT_MENU, &LeftPanel::addtenant, this, ID_ADD);

    // delete createbt, addbt, view, m_parent, m_listCtrl;
}

//show a dialog for collection client information
//borrow from clall dialog which is derived from wxDialog
void LeftPanel::OnCreate(wxCommandEvent &event)
{
    double x, y;
    x = xpixel / 2;
    y = ypixel / 2.75;

    customd = new CustomDialog(wxT_2("Creating new Client"), FromDIP(x), FromDIP(y));
    customd->Show(true);

    nm = customd->getName();
}

void LeftPanel::OnAdd(wxCommandEvent &event)
{
    double x, y;

    x = xpixel / 3;
    y = ypixel / 1.65;
    //PlotDialog(wxT("Plot"));
    FrameList *list = new FrameList("Client", wxDefaultPosition, wxSize(FromDIP(x), FromDIP(y)));
    list->Show(true);
}

void LeftPanel::add_plot_info()
{
    //if (arr.empty()){

    // arr = plot.get_owner_name();
    populateview();

    /* }else{
        arr.clear();
        populateview();

    }*/
}

void LeftPanel::populateview()
{
    arr.clear();
    m_listCtrl->DeleteAllItems();
    arr = plot.get_plot();

    for (size_t x = 0; x < arr.size(); x++)
    {
        m_listCtrl->InsertItem(x, arr[x].plotname);
        m_listCtrl->SetItem(x, 1, arr[x].location);
        m_listCtrl->SetItem(x, 2, wxString::Format("%d", arr[x].num_rooms));
    }

}

void LeftPanel::rightclick(wxListEvent &event)
{
    //EVT_LIST_ITEM_SELECTED

    item = event.GetItem();

    txt1 = m_listCtrl->GetItemText(item, 0);

    if (item != -1)
    {

        wxMenu *menu = new wxMenu(wxString::Format("Name : %s", txt1));
        wxMenuItem *add = new wxMenuItem(menu, ID_ADD, wxT("Add_Tenant"));
        wxMenuItem *edit = new wxMenuItem(menu, ID_EDIT_LIST, wxT("Edit"));
        wxMenuItem *report = new wxMenuItem(menu, ID_PRINT_REPORT, wxT("print report"));
        wxMenuItem *del = new wxMenuItem(menu, ID_POP_DEL, wxT("Delete"));

        wxBitmap addicon("../bitmaps/icons8-house-16.png");
        wxBitmap editicon("../bitmaps/icons8-edit-16.png");
        wxBitmap reporticon("../bitmaps/report-16.png");
        wxBitmap delicon("../bitmaps/icons8-delete-16.png");

        add->SetBitmap(addicon);
        edit->SetBitmap(editicon);
        report->SetBitmap(reporticon);
        del->SetBitmap(delicon);
        menu->Append(add);
        menu->Append(edit);
        menu->Append(report);
        menu->Append(del);

        PopupMenu(menu, event.GetPoint());
    }

}

void LeftPanel::update_list(wxCommandEvent &event)
{
    populateview();
}

void LeftPanel::force_update()
{

    // m_listCtrl->get();
}

//deletes plot from the database, for proper deletion
//process it incomparates key comparison
void LeftPanel::onDelete(wxCommandEvent &event)
{

    wxString txt = m_listCtrl->GetItemText(item, 0);
    wxString loc = m_listCtrl->GetItemText(item, 1);

    wxMessageDialog *dlg = new wxMessageDialog(NULL,
                                               wxString::Format("Your about to delete\n %s \n Are you sure..?", txt),
                                               wxT("Delete"), wxYES_NO | wxICON_QUESTION);

    int res = dlg->ShowModal();
    // std::string Id = std::string(id.mb_str());
    // std::string query = "Name = " + replace(std::string(txt.mb_str())) +
    //  " AND Location = " + replace(std::string(loc.mb_str()));

    std::string query = "Name = " + ("\'" + std::string(txt.mb_str()) + "\'") +
                        " AND Location = " + ("\'" + std::string(loc.mb_str()) + "\'");

    std::string sql = "DELETE FROM plot_info WHERE " + query;

    std::string tenanttxt = "";

    switch (res)
    {
    case wxID_YES:

        plot.delete_info(sql);
        m_listCtrl->DeleteItem(item);
        populateview();
        h_name->SetLabelText(wxEmptyString);
        num_of_rooms = 0;
        lview->populateview(strtxt);
        break;
    case wxID_NO:
        //Close(false);
        break;
    default:
        Close(false);
    };
}

void LeftPanel::onclick(wxListEvent &event)
{
   long item = -1;

    wxString txt, str1;

    for(;;){

        item = m_listCtrl->GetNextItem(item, wxLIST_NEXT_ALL,  wxLIST_STATE_SELECTED);

        if (item == -1){

            break;
        }

        showflag = 1;

        txt = m_listCtrl->GetItemText(item, 2);
        txtpltnm = m_listCtrl->GetItemText(item, 0);
        str1 = m_listCtrl->GetItemText(item, 1);

    }


        wxString s1 = "\'" + txtpltnm + "\'";
        wxString s2 = "\'" + str1 + "\'";

        finalstr12 = std::string(wxString::Format("%s AND Location = %s ", s1, s2).mb_str());

        strtxt = plot.get_Id("SELECT PlotId FROM plot_info WHERE Name = ", finalstr12);

        num_of_rooms = wxAtoi(txt);
        h_name->SetLabelText(txtpltnm);

        lview->populateview(strtxt);

        lview->SetItemState(-1, 0, wxLIST_STATE_SELECTED);

    

        showflag = 0;

    
}

void LeftPanel::onedit(wxCommandEvent &event)
{
    double x, y;

    x = xpixel / 5;
    y = ypixel / 5.5;

    wxString str = m_listCtrl->GetItemText(val, 0);
    wxString str1 = m_listCtrl->GetItemText(val, 1);
    EditPlotDialog *dlg = new EditPlotDialog("Edit", "plot_info", "Name", str, str1, "Location", "Plot name", "Situated", x, y);
    dlg->Show(true);
}

void LeftPanel::addtenant(wxCommandEvent &event)
{

    wxString str = m_listCtrl->GetItemText(val, 0);
    wxString str1 = m_listCtrl->GetItemText(val, 1);

    wxString t1 = "\'" + str + "\'";
    wxString t2 = "\'" + str1 + "\'";

    //std::string finalstr = std::string(wxString::Format("%s AND Location = %s ", t1, t2).mb_str());

    std::string strtxt12 = plot.get_Id("SELECT PlotId FROM plot_info WHERE Name = ", finalstr12);

    std::string Idstr = "\'" + strtxt12 + "\'";

    wxArrayString array;

    plot.room_flag = true;
    std::string np = plot.get_Id("SELECT Type FROM Plotroom WHERE Plotid = ", Idstr);


    for (auto x : plot.house_room_type)
    {
        array.push_back(x);
    }

    double x, y;

    x = xpixel / 3;
    y = ypixel / 2.45;

    Tenant *tenantdlg = new Tenant(txtpltnm, array, strtxt, FromDIP(x), FromDIP(y), num_of_rooms);
    tenantdlg->Show(true);
    plot.house_room_type.clear();
    plot.room_flag = false;

}

void LeftPanel::print_report(wxCommandEvent &event)
{
    std::tm* now = get_curr_date(); 
	int yr = now->tm_year+1900;
    int month = now->tm_mon +1;

    wxString date = wxString::Format("%d -  %d", month, yr);

    create_report(strtxt, date, txtpltnm);

    double x = xpixel / 2.4;
    double y = ypixel / 1.2;

    printfile = new Myprint(this, txtpltnm, wxDefaultPosition,
                            wxSize(x, y), wxMINIMIZE_BOX | wxCLOSE_BOX, "report.htm");
    printfile->Show();
}


/*********************************************************************************************************************************/

RightPanel::RightPanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(-1, -1), wxBORDER_SUNKEN)
{
    this->SetBackgroundColour(wxColour(193, 193, 193));
    search = new wxSearchCtrl(this, ID_SEARCH, wxT(""),
                              wxDefaultPosition, wxSize(200, -1));

    //creating a custom font
    wxFont font = wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                         wxFONTWEIGHT_NORMAL, false);

    h_name = new wxStaticText(this, ID_HNAME, wxEmptyString);

    h_name->SetFont(font);

    // dataview = new  wxListCtrl (this, wxID_ANY, wxDefaultPosition,
    //wxDefaultSize, wxLC_REPORT | wxLC_EDIT_LABELS | wxBORDER_THEME);

    lview = new NormaList(this, wxID_ANY,
                          wxDefaultPosition, wxDefaultSize,
                          wxLC_REPORT | wxLC_VIRTUAL |
                              wxBORDER_THEME | wxLC_EDIT_LABELS);

    wxBoxSizer *searchsizer = new wxBoxSizer(wxVERTICAL);

    searchsizer->Add(search, 0, wxALIGN_RIGHT | wxRIGHT | wxTOP, 10);
    searchsizer->Add(h_name, 0, wxLEFT, 30);
    searchsizer->Add(lview, 1, wxEXPAND | wxALL, 10);
    SetSizerAndFit(searchsizer);

    //  lview->populateview();

    Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &RightPanel::rightclick, this);
    //Bind(wxEVT_LIST_ITEM_SELECTED, &LeftPanel::onclick, this);
    //Bind(wxEVT_MENU, &LeftPanel::onDelete, this, ID_POP_DEL);
    Bind(wxEVT_MENU, &RightPanel::onedit, this, ID_EDIT_LIST);
    Bind(wxEVT_MENU, &RightPanel::print_receipt, this, ID_PRINT_RECEIPT);
    Bind(wxEVT_MENU, &RightPanel::onDelete, this, ID_TENANT_DELETE);
    Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &RightPanel::onfind, this, ID_SEARCH);
}

void RightPanel::rightclick(wxListEvent &event)
{
    //EVT_LIST_ITEM_SELECTED
    val = event.GetItem();

    long item = -1;

    for (;;)
    {
        item = lview->GetNextItem(item,
                                  wxLIST_NEXT_ALL,
                                  wxLIST_STATE_SELECTED);

        if (item == -1)
            break;

        txt1name = lview->GetItemText(item, 3);

        wxMenu *menu = new wxMenu(wxString::Format("Name : %s", txt1name));
        wxMenuItem *receipt = new wxMenuItem(menu, ID_PRINT_RECEIPT, wxT("Print receipt"));
        wxMenuItem *edit = new wxMenuItem(menu, ID_EDIT_LIST, wxT("Edit"));
        wxMenuItem *del = new wxMenuItem(menu, ID_TENANT_DELETE, wxT("Delete"));

        wxBitmap receipticon("../bitmaps/receipt.png");
        wxBitmap editicon("../bitmaps/icons8-edit-16.png");
        wxBitmap delicon("../bitmaps/icons8-delete-16.png");

        receipt->SetBitmap(receipticon);
        edit->SetBitmap(editicon);
        del->SetBitmap(delicon);
        menu->Append(receipt);
        menu->Append(edit);
        menu->Append(del);

        PopupMenu(menu);

        lview->SetItemState(item, 0, wxLIST_STATE_SELECTED);
    }
}

void RightPanel::onedit(wxCommandEvent &event)
{

    double x, y;

    x = xpixel / 5;
    y = ypixel / 5;

    wxString str = lview->GetItemText(val, 3);
    wxString str1 = lview->GetItemText(val, 4);

    std::string strstr = std::string(str.mb_str());

    std::string strtxt = separate_string(strstr);
    wxString strmod(strtxt);

    EditPlotDialog *dlg = new EditPlotDialog("Edit", "tenant", "Name", strmod, str1, "Phone_number", "Client name", "Contact", x, y);
    dlg->Show(true);
}

void RightPanel::print_receipt(wxCommandEvent &event)
{
    wxString str = lview->GetItemText(val, 5);
    wxString room_no = lview->GetItemText(val, 0);
    wxString name = lview->GetItemText(val, 3);

    wxString nm = h_name->GetLabelText();

    if (txt1name.size() == 1)
    {
        wxMessageBox("No Tenant!",
                     wxEmptyString, wxOK | wxICON_ERROR);
    }
    else if (str.size() == 1)
    {
        wxMessageBox("Unable to process\nreceipt for this month\npayment has not\n been made",
                     wxEmptyString, wxOK | wxICON_ERROR);
    }
    else
    {

#if wxUSE_LIBPNG
        wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
        wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
        wxImage::AddHandler(new wxGIFHandler);
#endif

        std::tm *now = get_curr_date();

        int day = now->tm_mday;
        int month = now->tm_mon + 1;
        int year = now->tm_year + 1900;

        wxString date = wxString::Format("%d / %d / %d ", day, month, year);
        wxString rec_no = wxString::Format("%d%d%s", year, month, room_no);

        create_receipt(nm, "0723223233", date, wxAtoi(rec_no), name,
                       6500, wxAtoi(room_no), "June", 2100, "japsonm limited");

        printfile = new Myprint(this, ("Printing"), wxDefaultPosition,
                                wxSize(400, 500), wxMINIMIZE_BOX | wxCLOSE_BOX, "receipt.htm");
        printfile->Show();
    }
}

void RightPanel::onfind(wxCommandEvent &event)
{
    lview->SetItemState(-1, 0, wxLIST_STATE_SELECTED);
    int found = -1;
    wxString txt = event.GetString();

    std::vector<std::string>::iterator it;

    if (plot.ten.nm.empty())
    {
        wxMessageBox("Empty");
    }
    else
    {
        it = std::find(plot.ten.nm.begin(), plot.ten.nm.end(), std::string(txt.mb_str()));

        wxString result;

        if (it != plot.ten.nm.end())
        {
            int x = it - plot.ten.nm.begin() + 1;
            // wxMessageBox(wxString::Format("Found at index %d", x));

            while ((found = lview->FindItem(found + 1, wxString::Format("%d", x), false)) >= 0)
            {
                result += lview->GetItemText(found, 3);
                result += wxT("\r\n");

                lview->SetItemState(found, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
            }
        }
        else
        {
            wxMessageBox(" Item Not Found!!");
        }
    }
}

void RightPanel::onDelete(wxCommandEvent &event)
{

    long item = lview->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (item != -1)
    {
        wxString txtT = lview->GetItemText(item, 3);
        wxString contact = lview->GetItemText(item, 4);

        wxMessageDialog *dlg = new wxMessageDialog(NULL,
                                                   wxString::Format("Your about to delete\n %s \n Are you sure..?", txtT),
                                                   wxT("Delete"), wxYES_NO | wxICON_QUESTION);

        int res = dlg->ShowModal();
        std::string query = "\'" + std::string(contact.mb_str()) + "\'";

        std::string sql = "DELETE FROM tenant WHERE Phone_number = " + query;
        std::cout << sql << std::endl;

        switch (res)
        {
        case wxID_YES:
            //m_listCtrl->DeleteItem(6);
            plot.delete_info(sql);
            //->populateview();

            // Close(true);
            break;
        case wxID_NO:
            Close(false);
            break;
        default:
            Close(false);
        };
    }
    else
    {
        wxLogMessage("Deleting item in index\n %ld failed.", item);
    }
}

/*******************************************************************************************************/
MyExtraPanel::MyExtraPanel(wxWindow *parent) : wxPanel(parent)
{
    m_btn = new wxButton(this, -1, wxT("Custom Button"));
    m_btn->Enable(false);
    m_cb = new wxCheckBox(this, -1, wxT("Enable Custom Button"));
    m_cb->Connect(wxEVT_CHECKBOX,
                  wxCommandEventHandler(MyExtraPanel::OnCheckBox), NULL, this);
    m_label = new wxStaticText(this, wxID_ANY, "Nothing selected");
    m_label->Connect(wxEVT_UPDATE_UI,
                     wxUpdateUIEventHandler(MyExtraPanel::OnUpdateLabelUI),
                     NULL, this);

    wxBoxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);
    sizerTop->Add(m_cb, wxSizerFlags().Centre().Border());
    sizerTop->AddStretchSpacer();
    sizerTop->Add(m_btn, wxSizerFlags().Centre().Border());
    sizerTop->AddStretchSpacer();
    sizerTop->Add(m_label, wxSizerFlags().Centre().Border());

    SetSizerAndFit(sizerTop);
}

wxString MyExtraPanel::GetInfo() const
{
    return wxString::Format("checkbox value = %d", (int)m_cb->GetValue());
}

void MyExtraPanel::OnCheckBox(wxCommandEvent &event)
{
    m_btn->Enable(event.IsChecked());
}

void MyExtraPanel::OnUpdateLabelUI(wxUpdateUIEvent &event)
{
    wxFileDialog *const dialog = wxStaticCast(GetParent(), wxFileDialog);
    const wxString fn = dialog->GetCurrentlySelectedFilename();

    wxString msg;
    if (fn.empty())
        msg = "Nothing";
    else if (wxFileName::FileExists(fn))
        msg = "File";
    else if (wxFileName::DirExists(fn))
        msg = "Directory";
    else
        msg = "Something else";

    event.SetText(msg + " selected");
}

/***********************************************************************************************************/
// a constructor of class FrameList, this list constructs a list that
// shows The name of the client owning the plot, their contacts and the
// account number required during cash deposits

FrameList::FrameList(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxDialog(NULL, wxID_ANY, title, pos, size)
{
    wxPanel *panel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
    listbox = new wxListView(panel, ID_LIST, wxPoint(-1, -1), wxSize(-1, -1));
    wxBoxSizer *sz = new wxBoxSizer(wxVERTICAL);

    int x, y, z, res;
    res = xpixel / 3;

    x = (res / 3.2) ;
    y = res / 3.75;
    z = res / 2.35;

    listbox->AppendColumn("Name");
    listbox->AppendColumn("Contact");
    listbox->AppendColumn("Account Number");
    listbox->SetColumnWidth(0, x);
    listbox->SetColumnWidth(1, y);
    listbox->SetColumnWidth(2, z);

    sz->Add(listbox, 1, wxEXPAND | wxALL, 2);
    panel->SetSizerAndFit(sz);

    addinfo();
    //Bind(wxEVT_LIST_ITEM_SELECTED, &FrameList::onclick, this , wxID_ANY);
    // Bind(wxEVT_LEFT_DOWN, &FrameList::onclick, this , wxID_ANY);
    Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &FrameList::rightclick, this);
    Bind(wxEVT_MENU, &FrameList::onDelete, this, ID_POP_DEL);
    Bind(wxEVT_MENU, &FrameList::Add_plot, this, ID_ADD);
    Bind(wxEVT_MENU, &FrameList::onedit, this, ID_EDIT_LIST);

    ShowModal();

    Destroy();
}

FrameList::~FrameList()
{

    /*   Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &FrameList::rightclick, this);
     Unbind(wxEVT_MENU, &FrameList::onDelete, this, ID_POP_DEL);
     Unbind(wxEVT_MENU, &FrameList::Add_plot, this, ID_ADD);
     delete listbox;*/
}

//insert items into the list
// this function receives data from the databse
//and updates the list
void FrameList::addinfo()
{

    arr = plot.get_owner_name();
    unsigned long int a = arr.size();
    std::stringstream ss;
    ss << a;
    std::string str = ss.str();
    int i = atoi(str.c_str());

    for (int x = 0; x < i; x++)
    {

        listbox->InsertItem(x, arr[x].name);
        listbox->SetItem(x, 1, arr[x].number);
        listbox->SetItem(x, 2, arr[x].account);
    }
}

//a bind events function, that checkes if a particular item(name of client),
// has been selected by the user and returns an inter >= 0 if
// selected or -1 if otherwise, if yes it calls a dialog box that
//allows the user to register plot info on the selected owner

void FrameList::rightclick(wxListEvent &event)
{

    item = event.GetItem();

    txt = listbox->GetItemText(item, 0);
    wxString txt1 = listbox->GetItemText(item, 1);

    ownername = txt;
    ownercont = txt1;

    if (item != -1)
    {

        wxMenu *menu1 = new wxMenu(wxString::Format("Name : %s", txt));
        wxMenuItem *add = new wxMenuItem(menu1, ID_ADD, wxT("Add_plot"));
        wxMenuItem *edit = new wxMenuItem(menu1, ID_EDIT_LIST, wxT("Edit"));
        wxMenuItem *del = new wxMenuItem(menu1, ID_POP_DEL, wxT("Delete"));

        wxBitmap addicon("../bitmaps/icons8-house-16.png");
        wxBitmap editicon("../bitmaps/icons8-edit-16.png");
        wxBitmap delicon("../bitmaps/icons8-delete-16.png");

        add->SetBitmap(addicon);
        edit->SetBitmap(editicon);
        del->SetBitmap(delicon);
        menu1->Append(add);
        menu1->Append(edit);
        menu1->Append(del);
        PopupMenu(menu1, event.GetPoint());
    }
}

//This fuction gets the selected item, and
// constructs a string which is passed to another fuction
// that take the string a paremeter and execute a query to the
// database to delete the selected item
void FrameList::onDelete(wxCommandEvent &event)
{
    // wxString sql = event.GetString();
    wxString id = listbox->GetItemText(item, 1);

    wxString strid = "\'" + id + "\'";

    wxMessageDialog *dlg = new wxMessageDialog(NULL,
                                               wxString::Format("Your about to delete\n %s \n Are you sure..?", txt),
                                               wxT("Delete"), wxYES_NO | wxICON_QUESTION);

    int res = dlg->ShowModal();

    std::string query = "Number = " + std::string(strid.mb_str());

    std::string sql = "DELETE FROM owner WHERE " + query;

    switch (res)
    {
    case wxID_YES:

        plot.delete_info(sql);
        listbox->DeleteItem(item);
        break;
    case wxID_NO:
        //Close(false);
        break;
    default:
        Close(false);
    };
}

void FrameList::Add_plot(wxCommandEvent &event)
{
    double x, y;

    x = xpixel / 3;
    y = ypixel / 1.35;


    if (item != -1)
    {
        PlotDialog *plotdlg = new PlotDialog("Add new plot",x, y);
        plotdlg->Show(true);
    }
    else
    {
        //Do nothing
    }
}

void FrameList::onedit(wxCommandEvent &event)
{

    double x, y;

    x = xpixel / 5;
    y = ypixel / 5.5;

    wxString str = listbox->GetItemText(item, 0);
    wxString str1 = listbox->GetItemText(item, 1);
    wxString str2 = listbox->GetItemText(item, 2);

    wxString fin = "Edit - " + str;

    EditPlotDialog *dlg = new EditPlotDialog(fin, "owner", "Account", str2, str1, "Number", "Account number", "Contact", x, y);

    dlg->Show(true);
}
/********************************************************************************************************************************/
//functions

void create_receipt(const wxString &title, const wxString &num, const wxString &date, int receipt_no,
                    const wxString &name, int paid, int bal, const wxString &month, int room_no,
                    const wxString &agent_name)
{

    std::ofstream html;
    html.open("receipt.htm");

    html << wxString::Format("<!DOCTYPE html>\
			 \n<html>\
			 \n\t<head>\
			\n\t\t<title>'hhjhjehja'</title>\
			\n\t</head>\
			\n\t<body>\
			\n\t\t<style>\
			\n\t\t\t.rectangle {\
	           \n\t\t\t\theight:300px;\
	            \n\t\t\t\twidth:550px;\
                \n\t\t\t\tborder:1px solid #000;\
                \n\t\t\t\tpadding-left:1%;\
                \n\t\t\t\tpadding-right:1%;\
                \n\t\t\t}\
                \n\t\t\t.date{\
                \n\t\t\t\tfloat:Right;\
                \n\t\t\t}\
                \n\t\t\t.under{\
                \n\t\t\t\ttext-decoration: underline dotted 1px;\
                \n\t\t\t}\
				\n\t\t\t.receipt2{\
                \n\t\t\t\tfloat:right;\
				\n\t\t\t}\
		 \n\t\t</style>\
		 \n\t\t<center>\
		 \n\t\t<div class='rectangle'>\
         \n\t\t<h3 style=text-align:center>%s</h3>\
         \n\t\t<p style=font-size:12px>Tel : %s </p>\
         \n\t\t<p class='date'> Date : <span class='under'> %s </span> &nbsp;&nbsp; Receipt No : <span class='under'>%d</span></p>\
        \n\t\t<br>\
        \n\t\t<P style='float: left'> Received From : <span class='under'>%s</span> </p>\
        \n\t\t<P style='float: Right'> Amount Kshs <span class='under'> %d </span> </p>\
		\n\t\t<br>\
		\n\t\t<p style='float: left'> For the month of :<span class='under'> %s </span> &nbsp; Room No :  <span class='under'> %d </span> </p>\
        \n\t\t<p style='float: right'> &nbsp; Balance Kshs <span class='under'>%d</span></p>\
        \n\t\t<p style='float: left'> Received by : <span class='under'>%s </span></p>\
        \n\t\t</div>\
        \n\t\t</center>\
	\n\t</body>\
	\n</html>\n",
                             title, num, date, receipt_no, name, paid, month, room_no, bal, agent_name);

    html.close();
}

void create_report(std::string strtxt, wxString date, wxString txte)
{

    //tenant_info ten_report = plot.print_tenant_report(strtxt);

    agent user = plot.Agent_info();

    //plot.get_tenant_info(strtxt);

    std::ofstream html;
    html.open("report.htm");

    html << wxString::Format("<!DOCTYPE html>\
    \n<html>\
    \n\t<body>\
    \n\t<H3 style='text-align:Center'> %S </H3>\
    \n\t<H6 style='text-align:Center'> Location: %s <br> Contact : %s <br> Email : %s ", 
             user.agent_name, user.loc, user.contact, user.email);

    if (user.web.empty()){
        //Do nothing
    } else {
        html << wxString::Format("<br> Website: %s  </H6>", user.web);
    }
    html << wxString::Format("\n\t<H6 style='text-align:Center'><b>%s Monthly report </b> </H6>\
    \n\t<center> \
     \n\t<font type='arial' size=3>\
     \n\t\t<table  border=1 cellspacing=0 border=1>\
         \n\t\t\t<tr>\
           \n\t\t\t<td> <b> Submitted By </b>:</td>\
            \n\t\t\t<td colspan=6>thhhh gcdycgdycgd hdhjdhcdhcdhcdokcdyccd jksijsijsiuidjidu skjsdidjidd </td>\
            \n\t\t\t</tr>\
            \n\t\t\t<tr>\
                \n\t\t\t<td> <b> Submitted On: </b></td>\
                \n\t\t\t<td colspan=6>Table cell 2</td>\
            \n\t\t\t</tr>\
            \n\t\t\t<tr>\
            \n\t\t\t<td> <b> Description of Report:</b></td>\
            \n\t\t\t<td colspan=6>A report for the month of October , detailing payment of rent as from date 12-09-2021 to 12-10-2021</td>\
            \n\t\t\t</tr>\
            \n\t\t\t<tr>\
            \n\t\t\t<th colspan=7> <b>Tenant payment record</b> </th>\
                \n\t\t\t<tr>\
                \n\t\t\t<td><b> Date </b> </td>\
                \n\t\t\t<td><b>ID Number</b> </td>\
                \n\t\t\t<td><b> Full name </b> </td>\
                \n\t\t\t<td><b> Contact </b> </td>\
                \n\t\t\t<td><b> Room number </b> </td>\
                \n\t\t\t<td><b> Amount paid </b> </td>\
                \n\t\t\t<td><b> Balance </b> </td>\
            \n\t\t\t</tr>\
            \n\t\t\t</tr>", "june");

            for(int x=0; x<15; x++){

            html << wxString::Format("\n\t\t\t<tr>\
                                \n\t\t\t<td>%s</td>\
						        \n\t\t\t<td>%s</td>\
						        \n\t\t\t<td>%s</td>\
						        \n\t\t\t<td>%s</td>\
						        \n\t\t\t<td>%s</td>\
						        \n\t\t\t<td>%s</td>\
						        \n\t\t\t<td>%s</td>\
						        \n\t\t\t</tr>", "22-10-2020", "233234", "Jane Akoth Wairimu", "+254723137632", "23", "6500", "100");
        }
        
        html << wxString::Format("\n\t\t</table>\
        \n\t\t</font>\
        \n\t\t</center>\
        \n\t<br>\
        \n\t<br>\
        \n\t<center>\
        \n\t<font type='arial' size=3>\
        \n\t<table border=1 cellpadding=4 cellspacing=0>\
        \n\t<tr>\
            \n\t\t<th> <b> Reviewed by: </b> </th>\
        \n\t</tr>\
             \n\t<tr> <td width=100%> <b> Comments </b> <br /> <br /> <br /> <br />  </td></tr>\
        \n\t</table>\
        \n\t</font>\
        \n\t</center>\
        \n\t<br>\
        \n\t<br>\
        \n\t<font type='arial' size=3>\
        \n\t<table border=1 align='right' cellspacing=0>\
            \n\t<tr> <td ><br /> <hr> <b> Authorized Signature<b> </td> </tr> \
        \n\t</table>\
        \n\t</font>\
        \n</body>\
         \n</html>");

    html.close();
           
}
