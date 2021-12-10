#include "dialog.h"

inline wxCheckBox *fpasswd;

/* customDialog methods, its a dialog that collects infomation from the user
   about the client in the ownership of the plot, surname, lastname, gender,
   a phone number and account number.

   NB:: as per now account number is no mandatory, but other fields should
        be mandatory
*/
data file;

CustomDialog::CustomDialog(){
    //
}

CustomDialog::CustomDialog(const wxString & title, double x, double y)

       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(x, y))
{

  Init();
  wxPanel *panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(x, y), wxBORDER_SUNKEN);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox2= new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox3= new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox4= new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox5= new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox6= new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox7= new wxBoxSizer(wxHORIZONTAL);

  // A friendly message
  wxStaticText* descr = new wxStaticText( panel, wxID_STATIC,
        wxT("Please enter Owners information"), wxPoint(-1, -1), wxDefaultSize,0 );

  hbox->Add(descr, 0);

    //owner info
  wxStaticText* OwnerS = new wxStaticText( panel, wxID_STATIC, wxT("&Surname "), wxPoint(-1, -1), wxDefaultSize,54);

  wxStaticText* OwnerN = new wxStaticText( panel, wxID_STATIC, wxT("&Other name "), wxPoint(-1, -1), wxDefaultSize,54);

  hbox1->Add(OwnerS, 2, wxEXPAND);
  hbox1->AddSpacer(FromDIP(30));
  hbox1->Add(OwnerN, 3, wxEXPAND);

   wxTextCtrl * OwnN_entry_s = new wxTextCtrl(panel, ID_SURNAME, wxT(" "), 
      wxPoint(-1, -1), wxSize(-1, -1), 0,  wxTextValidator(wxFILTER_ALPHA, &surname)); 

    wxTextCtrl *OwnN_entry_n = new wxTextCtrl(panel, ID_LASTNAME, wxT(" "), 
      wxPoint(-1, -1), wxSize(-1, -1), 0, wxTextValidator(wxFILTER_NONE, &lstname)); 

    hbox2->Add(OwnN_entry_s, 2, wxEXPAND);
    hbox2->AddSpacer(FromDIP(30));
    hbox2->Add(OwnN_entry_n, 3, wxEXPAND);

   //Gender info
    wxStaticText* gender = new wxStaticText( panel, wxID_STATIC,
        wxT("&Gender: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxString sexStrings[] = {
        wxT("Male"),
        wxT("Female")
      };

   wxChoice * sexChoice = new wxChoice ( this, ID_SEX,
          wxPoint(-1, -1), wxSize(-1, -1), WXSIZEOF(sexStrings), sexStrings, 0);
    sexChoice->SetStringSelection(wxT(" "));

    hbox3->Add(gender, 0);
    hbox3->AddSpacer(FromDIP(5));
    hbox3->Add(sexChoice, 1, wxEXPAND);

  //Number and account number
    //get_contact(panel);

    wxStaticText* tc_p = new wxStaticText( panel, wxID_STATIC,
        wxT("&Contact: "), wxPoint(-1, -1), wxDefaultSize,13);

    wxTextCtrl *tc = new wxTextCtrl(panel, ID_NUM, wxT("+254"), 
      wxPoint(-1, -1), wxSize(100, -1), 0, wxTextValidator(wxFILTER_NUMERIC , &g_data));

    hbox3->AddSpacer(FromDIP(20));
    hbox3->Add(tc_p, 0);
    hbox3->Add(tc, 2, wxEXPAND);

    //Account Number 
   wxStaticText* Acc = new wxStaticText( panel, wxID_STATIC,
        wxT("&Account Number "), wxPoint(-1, -1), wxDefaultSize,54);

    hbox4->Add(Acc, 0);

    wxTextCtrl * Acc_N = new wxTextCtrl(panel, ID_ACCOUNT, wxT(" "), 
      wxPoint(-1, -1), wxSize(-1, -1), 0, wxGenericValidator(&account_num));

    hbox5->Add(Acc_N, 1, wxEXPAND);

    wxStaticLine* line = new wxStaticLine ( this, wxID_STATIC, 
      wxPoint(-1, -1), wxSize(-1, -1), wxLI_HORIZONTAL );

    hbox6->Add(line, 1, wxEXPAND);

    //Buttons

      wxButton *reset = new wxButton(panel, wxID_RESET, wxT("Reset"), 
        wxPoint(-1, -1));

      wxButton *save = new wxButton(panel, ID_SAVE, wxT("Save"), 
        wxPoint(-1, -1));

      wxButton *next = new wxButton(panel, wxID_FORWARD, wxT("Add plot"), 
        wxPoint(-1, -1));

      wxButton *quit = new wxButton(panel, ID_EXIT, wxT("Quit"), 
        wxPoint(-1, -1));

      hbox7->Add(save, 1, wxEXPAND);
      hbox7->AddSpacer(FromDIP(10));
      hbox7->Add(reset, 1, wxEXPAND);
      hbox7->AddSpacer(FromDIP(10));
      hbox7->Add(next, 1, wxEXPAND);
      hbox7->AddSpacer(FromDIP(10));
      hbox7->Add(quit, 1, wxEXPAND);

    Bind(wxEVT_BUTTON, &CustomDialog::OnExit, this, ID_EXIT);
    Bind(wxEVT_BUTTON, &CustomDialog::OnSave, this, ID_SAVE);
    Bind(wxEVT_BUTTON, &CustomDialog::Reset, this, wxID_RESET);
    Bind(wxEVT_BUTTON, &CustomDialog::Next, this, wxID_FORWARD);
    Bind(wxEVT_CLOSE_WINDOW, &CustomDialog::OnClose, this);
   // this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(CustomDialog::OnClose));

   //hbox->Add(descr, 0, wxALIGN_LEFT|wxALL, 5);
   // vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, FromDIP(15));
    vbox->AddSpacer(FromDIP(10));
    vbox->Add(hbox1, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, FromDIP(10));
    vbox->Add(hbox2, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, FromDIP(15));
    vbox->AddSpacer(FromDIP(20));
    vbox->Add(hbox3, 0, wxLEFT |wxTOP | wxRIGHT | wxEXPAND, FromDIP(15));
    vbox->AddSpacer(FromDIP(20));
    vbox->Add(hbox4, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, FromDIP(15));
    vbox->Add(hbox5, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, FromDIP(15));
    vbox->Add(hbox6, 0, wxTOP | wxEXPAND, 5);
  
    vbox->Add(hbox7, 0, wxLEFT | wxTOP | wxRIGHT | wxBOTTOM | wxEXPAND, FromDIP(5));

    SetSizerAndFit(vbox);

    Centre();
    ShowModal();

    Destroy(); 
}

CustomDialog::~CustomDialog(){
    
    Unbind(wxEVT_BUTTON, &CustomDialog::OnExit, this, wxID_EXIT);
    Unbind(wxEVT_BUTTON, &CustomDialog::OnSave, this, ID_SAVE);
    Unbind(wxEVT_BUTTON, &CustomDialog::Reset, this, wxID_RESET);
    Unbind(wxEVT_BUTTON, &CustomDialog::Next, this, wxID_FORWARD);
    Unbind(wxEVT_CLOSE_WINDOW, &CustomDialog::OnClose, this);

}

void CustomDialog::Init(){
    surname = wxEmptyString;
    lstname = wxEmptyString;
    gender = true;
    num = "+254";
    account_num = wxEmptyString;
}

bool CustomDialog::TransferDataToWindow(){
    wxTextCtrl *OwnN_entry_s = (wxTextCtrl*) FindWindow(ID_SURNAME);
    wxTextCtrl *OwnN_entry_n = (wxTextCtrl*) FindWindow(ID_LASTNAME);
    wxChoice *sexChoice = (wxChoice*) FindWindow(ID_SEX);

    wxTextCtrl *tc = (wxTextCtrl*) FindWindow(ID_NUM);
    wxTextCtrl *Acc_N = (wxTextCtrl*) FindWindow(ID_ACCOUNT);

    OwnN_entry_n->SetValue(surname);
    OwnN_entry_s->SetValue(lstname);
    sexChoice->SetSelection(gender);

    tc->SetValue(num);
    Acc_N->SetValue(account_num);

    return true;
}

bool CustomDialog::TransferDataFromWindow(){

   wxTextCtrl *OwnN_entry_s = (wxTextCtrl*) FindWindow(ID_SURNAME);
    wxTextCtrl *OwnN_entry_n = (wxTextCtrl*) FindWindow(ID_LASTNAME);
    wxChoice *sexChoice = (wxChoice*) FindWindow(ID_SEX);

    wxTextCtrl *tc = (wxTextCtrl*) FindWindow(ID_NUM);
    wxTextCtrl *Acc_N = (wxTextCtrl*) FindWindow(ID_ACCOUNT);

    surname = OwnN_entry_s->GetValue();
    lstname = OwnN_entry_n->GetValue();
    gender = sexChoice->GetSelection();

    num = tc->GetValue();
    account_num = Acc_N->GetValue();

   if (surname.IsEmpty() or lstname.IsEmpty() or num.IsEmpty()){
        wxLogError("Make sure \n all information \n are in the field");
        return false;

    } else {
      return true;
     
    }
    

    //return true;
}
  // converts wxstring to const char *
  const char *wxstring_to_char(wxString i){
      std::string s(i.mb_str());


      char * c =  new char(strlen(s.c_str()));
      strcpy(c, s.c_str());

      return c;
  }

 void CustomDialog::OnSave(wxCommandEvent& event){

      wxMessageDialog *dial = new wxMessageDialog(NULL,
      wxT("Are you sure to save\n the information ?"), wxT("Question"),
      wxYES_NO | wxICON_QUESTION);

      int res = dial->ShowModal();

      switch (res)
      {
        case wxID_YES:

          if (Validate() && TransferDataFromWindow()){
             flag = 1;
            const char *sn;
            const char *nm;
            const char *genderchar;
            const char *account_char;

            sn = wxstring_to_char(surname);
            nm = wxstring_to_char(lstname);
            account_char = wxstring_to_char(account_num);
            const char * numchar = wxstring_to_char(num);

            if(gender == 1){
                genderchar = "Female";
            }else{
                genderchar = "Male";
            }

           std::string Id = generateId(); 
 
            const char *ownerId = Id.c_str();

            plot.insert_owner_info(ownerId, numchar, sn, nm, genderchar, account_char);
            file.ownerId = Id;

            if (IsModal())
                EndModal(wxID_OK); // If modal
            else
            {
              SetReturnCode(wxID_OK);
              this->Show(false); // If modeless
            }
          }
          
          break;
        case wxID_NO:
            dial->Destroy();
            break;
        
        default:
        //
          break;
      }
     // event.Skip();
}


void CustomDialog::Next(wxCommandEvent& event){
    wxMessageDialog *dial = new wxMessageDialog(NULL, 
      wxT("You have to save\n the  message before\n proceeding..\n Save..?"), wxT("Exclamation"), 
      wxYES_NO | wxICON_EXCLAMATION);
      int res = dial->ShowModal();

      double x, y;
      x = xpixel / 3;
      y = ypixel / 1.35;

      if (res == wxID_YES){
          OnSave(event);
          if (flag == 1){
              PlotDialog(wxT("Plot"), x, y);
         }else{
           /// do nothing;
         }
      }else{
        dial->Destroy();
      }
}

void CustomDialog::OnExit(wxCommandEvent& event){
   wxMessageDialog *dial = new wxMessageDialog(NULL,
      wxT("Are you sure to quit?"), wxT("Question"),
      wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

      int res;
      res = dial->ShowModal();

      switch (res)
      {
      case wxID_YES:
        Destroy();
        break;
      default:
        event.Skip();
        break;
      }
}



void CustomDialog::Reset(wxCommandEvent& event){
      Init();
      TransferDataToWindow();
      event.Skip();
}

// return a map dictionary of surname and lastname
std::map<wxString, wxString> CustomDialog::getName(){
    std::map<wxString, wxString> name;

    name.insert(std::pair<wxString, wxString>(surname, lstname));

    if (name.empty()){
      std::cout<< "No information provided " << std::endl;
    }
    return name;
    
}

void CustomDialog::OnClose(wxCloseEvent& event)
{
    if ( wxMessageBox(wxT("The information \nhas not been saved\n...continue closing?"),
                          wxT("Please confirm"),
                          wxICON_QUESTION | wxYES_NO) != wxYES )
        {
            event.Veto();
            return;
        }

   Destroy();  // you may also do:  event.Skip();
                // since the default event handler does call Destroy(), too
}


/*****************************************************************************************************************************/
/* plogDialog methods, its a dialog that collects infomation from the user
   about the information of the specified plot, either single, double, one
   bedroom and also its rent, it has methods of returning such value
*/


PlotDialog::PlotDialog(){
    //
}


PlotDialog::PlotDialog(const wxString & title, double x, double y)
       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(x, y))
{   
    Init();
    wxPanel *panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(x, y), wxBORDER_SUNKEN);

    vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);

    //name of house plot
    wxStaticText* descr = new wxStaticText( panel, wxID_STATIC, wxT("Please enter Plot details"));

    wxStaticText* plotname = new wxStaticText( panel, wxID_STATIC, wxT("&Plot name "));

    wxTextCtrl *plotname_entry = new wxTextCtrl(panel, ID_PLOT, wxT(" "), 
      wxPoint(-1, -1), wxSize(-1, -1), 0,  wxTextValidator(wxFILTER_NONE, &plot_name));

    hbox->Add(descr, 0);
    hbox1->Add(plotname, 0);
    hbox2->Add(plotname_entry, 1, wxEXPAND);

    //location
    wxStaticText* loc = new wxStaticText( panel, wxID_STATIC,
      wxT("&location  "), wxPoint(-1, -1), wxDefaultSize,54);

    wxTextCtrl *loc_entry = new wxTextCtrl(panel, ID_LOC, wxT(" "), 
      wxPoint(-1, -1), wxSize(-1, -1));

    hbox1->AddSpacer(240);
    hbox1->Add(loc);
    hbox2->AddSpacer(20);
    hbox2->Add(loc_entry, 1, wxEXPAND);

    // number of houses
    wxStaticText* numH = new wxStaticText( panel, wxID_STATIC,
      wxT("&Number of rooms: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxTextCtrl *numH_entry = new wxTextCtrl(panel, ID_NH, wxT(" "), 
      wxPoint(-1, -1), wxSize(70, -1), 0, wxGenericValidator(&num_of_rooms));
    
    wxStaticLine* line1 = new wxStaticLine ( this, wxID_STATIC, 
      wxPoint(-1, -1), wxSize(-1, -1), wxLI_HORIZONTAL );


    hbox3->Add(numH, 0);
    hbox3->AddSpacer(6);
    hbox3->Add(numH_entry, 0);
    hbox4->Add(line1, 1, wxEXPAND);

    vbox->Add(hbox, 0, wxLEFT | wxTOP , 20);
    vbox->Add(hbox1, 0, wxLEFT | wxTOP , 20);
    vbox->AddSpacer(5);
    vbox->Add(hbox2, 0, wxLEFT| wxRIGHT | wxEXPAND,20);
    vbox->Add(hbox3, 0, wxLEFT | wxTOP, 20);
    vbox->AddSpacer(15);
    vbox->Add(hbox4,0, wxTOP | wxEXPAND, 20);


    create_plot_info(panel);

    Bind(wxEVT_BUTTON, &PlotDialog::OnSave, this, wxID_SAVE);
    Bind(wxEVT_BUTTON, &PlotDialog::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &PlotDialog::OnReset, this, wxID_RESET);



    panel->SetSizer(vbox);

    Centre();
    ShowModal();

    Destroy(); 

}

PlotDialog::~PlotDialog(){
    Unbind(wxEVT_BUTTON, &PlotDialog::OnSave, this, wxID_SAVE); 
   // Unbind(wxEVT_BUTTON, &PlotDialog::OnExit, this, wxID_EXIT);
}

void PlotDialog::create_plot_info(wxPanel *panel){

   //first row
   //single room

    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox5a = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox5b = new wxBoxSizer(wxHORIZONTAL);

    wxCheckBox *sr = new wxCheckBox(panel, ID_CB1, wxT_2("&Single Room"), 
    wxPoint(-1, -1), wxDefaultSize, 0);
  
  //double room
    wxCheckBox * dr = new wxCheckBox(panel, ID_CB2, wxT_2("&Double Room"), 
      wxPoint(-1, -1), wxDefaultSize, 0);

    hbox5->Add(sr, 1, wxEXPAND);
    hbox5->AddStretchSpacer(0);

    hbox5->Add(dr, 1, wxEXPAND);

   //second
   //single room
   wxStaticText* srt = new wxStaticText( panel, ID_SRM,
     wxT("&Total: "), wxPoint(-1, 1), wxDefaultSize,54);

     hbox5a->Add(srt, 0);
    hbox5a->AddSpacer(10);
    
    wxSpinCtrl * srtCtr = new wxSpinCtrl (panel, ID_SRT, wxEmptyString,
       wxPoint(-1, -1), wxDefaultSize, wxSP_HORIZONTAL , 0, 120, 0);

      hbox5a->Add(srtCtr, 1, wxEXPAND);
      hbox5a->AddSpacer(20);

    // double room
    wxStaticText* drt = new wxStaticText( panel, ID_SRM,
      wxT("&Total: "), wxPoint(-1, -1), wxDefaultSize,54);

      hbox5a->Add(drt, 0);
      hbox5a->AddSpacer(10);

    wxSpinCtrl * drtCtr = new wxSpinCtrl (panel, ID_DRT, wxEmptyString,
       wxPoint(-1, -1), wxDefaultSize, wxSP_HORIZONTAL , 0, 120, 0);

      hbox5a->Add(drtCtr, 1, wxEXPAND);

    

   wxStaticText* srtc = new wxStaticText( panel, ID_SRM,
      wxT("&Rent: "), wxPoint(-1, -1), wxDefaultSize,54);

      hbox5b->Add(srtc, 0);
      hbox5b->AddSpacer(15);

    wxTextCtrl *sr_entry = new wxTextCtrl(panel, ID_SR, wxT(" "), 
      wxPoint(-1, -1), wxDefaultSize, 0, wxGenericValidator(&nsingle));

      hbox5b->Add(sr_entry, 1, wxEXPAND);
      hbox5b->AddSpacer(20);

    // Double room codes 

    wxStaticText* drtc = new wxStaticText( panel, ID_SRM,
      wxT("&Rent: "), wxPoint(-1, -1), wxDefaultSize,54);

      hbox5b->Add(drtc, 0);
      hbox5b->AddSpacer(10);

    wxTextCtrl *dr_entry = new wxTextCtrl(panel, ID_DR, wxT(" "), 
      wxPoint(-1, -1), wxDefaultSize, 0, wxGenericValidator(&ndouble));

      hbox5b->Add(dr_entry, 1, wxEXPAND);

    vbox->Add(hbox5, 0, wxLEFT | wxTOP | wxEXPAND, 20);
    vbox->Add(hbox5a, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 20);
    vbox->Add(hbox5b, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);


   //SECOND 

    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox6a = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox6b = new wxBoxSizer(wxHORIZONTAL);

    wxCheckBox * obr = new wxCheckBox(panel, ID_CB3, wxT("&One bed Room"), 
      wxPoint(-1, -1), wxDefaultSize, 0);

    wxCheckBox * tbr = new wxCheckBox(panel, ID_CB4, wxT_2("&Two bed Room"), 
      wxPoint(-1, -1), wxDefaultSize, 0);

    hbox6->Add(obr, 1, wxEXPAND);
    hbox6->AddStretchSpacer(0);

    hbox6->Add(tbr, 1, wxEXPAND);
    
    //
    wxStaticText* obrt = new wxStaticText( panel, ID_SRM,
      wxT("&Total: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxSpinCtrl * obrtCtr = new wxSpinCtrl (panel, ID_OBRT, wxEmptyString,
       wxPoint(-1, -1), wxDefaultSize, wxSP_HORIZONTAL , 0, 120, 0);


    wxStaticText* tbrt = new wxStaticText( panel, ID_SRM,
      wxT("&Total: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxSpinCtrl * tbrtCtr = new wxSpinCtrl (panel, ID_TBRT, wxEmptyString,
       wxPoint(-1, -1), wxDefaultSize, wxSP_HORIZONTAL , 0, 120, 0);

    hbox6a->Add(obrt, 0);
    hbox6a->AddSpacer(10);
    hbox6a->Add(obrtCtr, 1, wxEXPAND);

    hbox6a->AddSpacer(20);
    hbox6a->Add(tbrt, 0);
    hbox6a->AddSpacer(10);
    hbox6a->Add(tbrtCtr, 1, wxEXPAND);


    // 
    wxStaticText* obrtc = new wxStaticText( panel, ID_SRM,
      wxT("&Rent: "), wxPoint(10, 341), wxDefaultSize,54);

    wxTextCtrl *obr_entry = new wxTextCtrl(panel, ID_OBR, wxT(" "), 
      wxPoint(50, 335), wxDefaultSize, 0, wxGenericValidator(&n_onebdrm));

    wxStaticText* tbrtc = new wxStaticText( panel, ID_SRM,
      wxT("&Rent: "), wxPoint(210, 341), wxDefaultSize,54);

    wxTextCtrl *tbr_entry = new wxTextCtrl(panel, ID_TBR, wxT(" "), 
      wxPoint(250, 335), wxDefaultSize, 0, wxGenericValidator(&nbedsitter));

    hbox6b->Add(obrtc, 0);
    hbox6b->AddSpacer(10);
    hbox6b->Add(obr_entry, 1, wxEXPAND);

    hbox6b->AddSpacer(20);
    hbox6b->Add(tbrtc, 0);
    hbox6b->AddSpacer(10);
    hbox6b->Add(tbr_entry, 1, wxEXPAND);

    vbox->AddSpacer(10);
    vbox->Add(hbox6, 0, wxLEFT | wxTOP| wxEXPAND, 20);
    vbox->Add(hbox6a, 0, wxLEFT | wxTOP | wxRIGHT| wxEXPAND, 20);
    vbox->Add(hbox6b, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);

   //THIRD

    wxBoxSizer *hbox7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox7a = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox7b = new wxBoxSizer(wxHORIZONTAL);


     // Three bed room
    wxCheckBox * thbr = new wxCheckBox(panel, ID_CB5, wxT_2("&Three Bed Room"), 
      wxPoint(-1, -1), wxDefaultSize, 0);

    wxCheckBox * bbr = new wxCheckBox(panel, ID_CB6, wxT_2("&BedSitter"), 
      wxPoint(-1, -1), wxDefaultSize, 0);

    hbox7->Add(thbr, 1, wxEXPAND);
    hbox7->AddStretchSpacer(0);

    hbox7->Add(bbr, 1, wxEXPAND);

    wxStaticText* thbrt = new wxStaticText( panel, ID_SRM,
      wxT("&Total: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxSpinCtrl * thbrtCtr = new wxSpinCtrl (panel, ID_THBRT, wxEmptyString,
       wxPoint(-1, -1), wxDefaultSize, wxSP_HORIZONTAL , 0, 120, 0);

    wxStaticText* bbrt = new wxStaticText( panel, ID_SRM,
      wxT("&Total: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxSpinCtrl * bbrtCtr = new wxSpinCtrl (panel, ID_BBRT, wxEmptyString,
       wxPoint(-1, -1), wxDefaultSize, wxSP_HORIZONTAL , 0, 120, 0);

    hbox7a->Add(thbrt, 0);
    hbox7a->AddSpacer(10);
    hbox7a->Add(thbrtCtr, 1, wxEXPAND);

    hbox7a->AddSpacer(20);
    hbox7a->Add(bbrt, 0);
    hbox7a->AddSpacer(10);
    hbox7a->Add(bbrtCtr, 1, wxEXPAND);

    wxStaticText* thbrtc = new wxStaticText( panel, ID_SRM,
      wxT("&Rent: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxTextCtrl *thbr_entry = new wxTextCtrl(panel, ID_THBR, wxT(" "), 
      wxPoint(-1, -1), wxDefaultSize, 0, wxGenericValidator(&nthreebdrm));

    //bedsitter

    wxStaticText* bbrtc = new wxStaticText( panel, ID_SRM,
      wxT("&Rent: "), wxPoint(-1, -1), wxDefaultSize,54);

    wxTextCtrl *bbr_entry = new wxTextCtrl(panel, ID_BBR, wxT(" "), 
      wxPoint(-1, -1), wxDefaultSize, 0, wxGenericValidator(&nthreebdrm));

    
    hbox7b->Add(thbrtc, 0);
    hbox7b->AddSpacer(10);
    hbox7b->Add(thbr_entry, 1, wxEXPAND);

    hbox7b->AddSpacer(20);
    hbox7b->Add(bbrtc, 0);
    hbox7b->AddSpacer(10);
    hbox7b->Add(bbr_entry, 1, wxEXPAND);

    vbox->Add(hbox7, 0, wxLEFT | wxTOP | wxEXPAND, 20);
    vbox->Add(hbox7a, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 20);
    vbox->Add(hbox7b, 0, wxLEFT | wxTOP | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);

    wxBoxSizer *hboxline = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hboxbutton = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticLine* line2 = new wxStaticLine ( this, wxID_STATIC, 
        wxPoint(-1, -1), wxSize(-1, -1), wxLI_HORIZONTAL );

    hboxline->Add(line2, 1, wxEXPAND);

    wxButton *quit = new wxButton(panel, wxID_EXIT, wxT("Quit"), 
        wxPoint(-1, -1), wxSize(-1, -1));

    wxButton *reset = new wxButton(panel, wxID_RESET, wxT("Reset"), 
        wxPoint(-1, -1));

    wxButton *save = new wxButton(panel, wxID_SAVE, wxT("Save"), 
        wxPoint(-1, -1));

    hboxbutton->Add(save, 1, wxEXPAND);
    hboxbutton->AddSpacer(10);
    hboxbutton->Add(reset, 1, wxEXPAND);
    hboxbutton->AddSpacer(10);
    hboxbutton->Add(quit, 1, wxEXPAND);

    vbox->Add(hboxline, 0, wxTOP | wxEXPAND, 10);
    vbox->Add(hboxbutton, 0, wxALL | wxEXPAND, 20);

}

bool PlotDialog::TransferDataToWindow(){

   wxTextCtrl * plotname_entry = (wxTextCtrl*) FindWindow(ID_PLOT);
    wxTextCtrl *loc_entry = (wxTextCtrl*) FindWindow(ID_LOC);
    wxTextCtrl *numH_entry = (wxTextCtrl *) FindWindow(ID_NH);

    wxTextCtrl *sr_entry = (wxTextCtrl *) FindWindow(ID_SR);
    wxTextCtrl *dr_entry = (wxTextCtrl *) FindWindow(ID_DR);

    wxTextCtrl *obr_entry = (wxTextCtrl *) FindWindow(ID_OBR);
    wxTextCtrl *tbr_entry = (wxTextCtrl *) FindWindow(ID_TBR);
    wxTextCtrl *thbr_entry = (wxTextCtrl *) FindWindow(ID_THBR);
    wxTextCtrl *bbr_entry = (wxTextCtrl *) FindWindow(ID_BBR);

    plotname_entry->SetValue(plot_name);
    loc_entry->SetValue(location);
    numH_entry->SetValue(wxString::Format(wxT("%i"), num_of_rooms));

    sr_entry->SetValue(wxString::Format(wxT("%.2f"), single_rent));
    dr_entry->SetValue(wxString::Format(wxT("%.2f"), Double_rent));

    obr_entry->SetValue(wxString::Format(wxT("%.2f"), One_bedrm_rent));
    tbr_entry->SetValue(wxString::Format(wxT("%.2f"), two_bedrm_rent));
    thbr_entry->SetValue(wxString::Format(wxT("%.2f"), three_bedrm_rent));
    bbr_entry->SetValue(wxString::Format(wxT("%.2f"), bedsitter_rent));

    return true;

}

bool PlotDialog::TransferDataFromWindow(){

    wxTextCtrl * plotname_entry = (wxTextCtrl*) FindWindow(ID_PLOT);
    wxTextCtrl *loc_entry = (wxTextCtrl*) FindWindow(ID_LOC);
    wxTextCtrl *numH_entry = (wxTextCtrl *) FindWindow(ID_NH);

    wxTextCtrl *sr_entry = (wxTextCtrl *) FindWindow(ID_SR);
    wxTextCtrl *dr_entry = (wxTextCtrl *) FindWindow(ID_DR);

    wxTextCtrl *obr_entry = (wxTextCtrl *) FindWindow(ID_OBR);
    wxTextCtrl *tbr_entry = (wxTextCtrl *) FindWindow(ID_TBR);
    wxTextCtrl *thbr_entry = (wxTextCtrl *) FindWindow(ID_THBR);
    wxTextCtrl *bbr_entry = (wxTextCtrl *) FindWindow(ID_BBR);

    plot_name = plotname_entry->GetValue();
    location = loc_entry->GetValue();
    num_of_rooms = wxAtoi(numH_entry->GetValue());

    sr_entry->GetValue().ToDouble(&single_rent);
    dr_entry->GetValue().ToDouble(&Double_rent);

    obr_entry->GetValue().ToDouble(&One_bedrm_rent);
    tbr_entry->GetValue().ToDouble(&two_bedrm_rent);
    thbr_entry->GetValue().ToDouble(&three_bedrm_rent);
    bbr_entry->GetValue().ToDouble(&bedsitter_rent);

    wxSpinCtrl *srtCtr = (wxSpinCtrl*) FindWindow(ID_SRT);
    wxSpinCtrl *drtCtr = (wxSpinCtrl*) FindWindow(ID_DRT);
    wxSpinCtrl *obrtCtr = (wxSpinCtrl*) FindWindow(ID_OBRT);
    wxSpinCtrl *tbrtCtr = (wxSpinCtrl*) FindWindow(ID_TBRT);
    wxSpinCtrl *thbrtCtr = (wxSpinCtrl*) FindWindow(ID_THBRT);
    wxSpinCtrl *bbrtCtr = (wxSpinCtrl*) FindWindow(ID_BBRT);

    nsingle = srtCtr->GetValue();
    ndouble = drtCtr->GetValue();
    n_onebdrm = obrtCtr->GetValue();
    ntwobdrm = tbrtCtr->GetValue();
    nthreebdrm = thbrtCtr->GetValue();
    nbedsitter = bbrtCtr->GetValue();

    wxCheckBox *sr = (wxCheckBox*) FindWindow(ID_CB1);
    wxCheckBox *dr = (wxCheckBox *) FindWindow(ID_CB2);
    wxCheckBox *obr = (wxCheckBox *) FindWindow(ID_CB3);
    wxCheckBox *tbr = (wxCheckBox *) FindWindow(ID_CB4);
    wxCheckBox *thbr = (wxCheckBox *) FindWindow(ID_CB5);
    wxCheckBox *br = (wxCheckBox *) FindWindow(ID_CB6);

    Single = sr->IsChecked();
    Double = dr->IsChecked();
    One_bedrm = obr->IsChecked();
    two_bedrm = tbr->IsChecked();
    three_bedrm = thbr->IsChecked();
    bedsitter = br->IsChecked();

    if (plot_name.IsEmpty() or location.IsEmpty() or num_of_rooms == 0){
        wxLogError("Make sure\nplot name, location\n number of rooms \n are in the field");
        return false;

    } else {

      return true;
     
    }
}

void PlotDialog::Init(){
    plot_name = wxEmptyString;
    location = wxEmptyString;
    num_of_rooms = 0;
    nsingle = 0;
    ndouble = 0;
    n_onebdrm = 0;
    nbedsitter = 0;
    ntwobdrm = 0;
    nthreebdrm = 0;
    
    //rent
    single_rent = 0;
    Double_rent = 0;
    One_bedrm_rent = 0;
    two_bedrm_rent = 0;
    bedsitter_rent = 0;
    three_bedrm_rent = 0;
}

void PlotDialog::OnReset(wxCommandEvent& event){
    Init();
    TransferDataToWindow();
    event.Skip();
}

void PlotDialog::set(std::string Id){
    if (Single==true){

        plot.insert_plotroom(Id.c_str(), "Single Room", single_rent, nsingle);
      
    }if (Double==true){

        plot.insert_plotroom(Id.c_str(), "Double Room", Double_rent, ndouble);

    }if (One_bedrm == true){

        plot.insert_plotroom(Id.c_str(), "One Bed Room", One_bedrm_rent, n_onebdrm);

    }if (two_bedrm == true){
      
        plot.insert_plotroom(Id.c_str(), "Two Bed Room", two_bedrm_rent ,ntwobdrm);

    }if(three_bedrm == true) {

      plot.insert_plotroom(Id.c_str(), "Three Bed Room", three_bedrm_rent, nthreebdrm);

    } if (bedsitter == true){

      plot.insert_plotroom(Id.c_str(), "Bedsitter", bedsitter_rent , nbedsitter);

    } else{
      ////
    }
    
}

void PlotDialog::OnSave(wxCommandEvent& event){

      wxMessageDialog *dial = new wxMessageDialog(NULL,
      wxT("Are you sure you want to\n add the plot to.. ?"), wxT("Question"),
      wxYES_NO | wxICON_QUESTION);

      int res = dial->ShowModal();

      switch (res)
      {
        case wxID_YES:

          if (Validate() && TransferDataFromWindow()){
              const char *plt;
              const char *loc;

              plt = wxstring_to_char(plot_name);
              loc = wxstring_to_char(location);

              std::string Id = generateId();

              const char *plotid = Id.c_str();

              std::string changetxt = "\'" + std::string(ownercont.mb_str()) + "\'";

              std::string strId = plot.get_Id("SELECT Id FROM owner WHERE Number = ", changetxt);

             if (file.ownerId.empty()){

                  plot.insert_plot_info(strId.c_str(), plotid, num_of_rooms, plt, loc);
                  set(Id);


              }else{
                  plot.insert_plot_info(file.ownerId.c_str(), plotid, num_of_rooms, plt, loc);
                  set(Id);
              }
             // } else{
                 // wxLogMessage(wxT("An Error occured!"));
             // }
            

            if (IsModal())
                EndModal(wxID_OK); // If modal
            else
            {
              SetReturnCode(wxID_OK);
              this->Show(false); // If modeless
            }
          }
          break;
        case wxID_NO:
            dial->Destroy();
            break;
        
        default:
        //
          break;
      }
      event.Skip();
}

void PlotDialog::OnExit(wxCommandEvent& event){
   wxMessageDialog *dial = new wxMessageDialog(NULL,
      wxT("Are you sure to quit?"), wxT("Question"),
      wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

      int res;
      res = dial->ShowModal();

      switch (res)
      {
      case wxID_YES:
        Destroy();
        break;
      default:
        event.Skip();
        break;
      }
}

std::map<double, int> PlotDialog::GetSingle(){
    std::map<double, int> details;
    details.insert(std::pair<double, int >(single_rent, nsingle));
    return details;
}

std::map<double, int> PlotDialog::GetDouble(){
    std::map<double, int> details;
    details.insert(std::pair<double, int >(Double_rent, ndouble));
    return details;
}

std::map<double, int> PlotDialog::GetOneBedrm(){
    std::map<double, int> details;
    details.insert(std::pair<double, int >(One_bedrm_rent, n_onebdrm));
    return details;
}

std::map<double, int> PlotDialog::GetTwoBedrm(){
    std::map<double, int> details;
    details.insert(std::pair<double, int >(two_bedrm_rent, ntwobdrm));
    return details;
}
std::map<double, int> PlotDialog::GetBedSitter(){
    std::map<double, int> details;
    details.insert(std::pair<double, int >(bedsitter_rent, nbedsitter));
    return details;
}
std::map<double, int> PlotDialog::GetThrBedrm(){
    std::map<double, int> details;
    details.insert(std::pair<double, int >(three_bedrm_rent, nthreebdrm));
    return details;
}

/*******************************************************************************************************************************/
NewFileDialog::NewFileDialog(const wxString& title):
      wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(400, 600))
{ 
    wxPanel *panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(400, 600), wxBORDER_SUNKEN);

	  MainEditBox = new wxTextCtrl(panel, TEXT_Main, _("Hi!"), wxDefaultPosition, wxDefaultSize, 
		          wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);

	  Maximize();

    MainEditBox->Clear();

    CurrentDocPath = wxT("/home/Peter/Documents");
    // Set the Title to reflect the file open
    SetTitle(_("Edit - untitled *"));

    
    
}

void NewFileDialog::NewFile(wxCommandEvent& WXUNUSED(event))
{
    wxDialog *newdlg = new wxDialog();
	// Clear the edit box
    MainEditBox->Clear();
    // reset the path of our current open file
      //std::string path = fs::current_path();
    CurrentDocPath = wxT("/home/Peter/Documents");
    // Set the Title to reflect the file open
    SetTitle(_("Edit - untitled *"));
    newdlg->Show();
}


/*******************************************************************************************************************/

Tenant::Tenant(const wxString& title, const wxArrayString& room_type, std::string plotId, double x, double y, int num_of_rooms)
       :  wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(x, y))
{
   
    init();
    plotid = plotId;
    max_room = num_of_rooms;
    wxPanel *panel = new wxPanel(this, -1, wxPoint(-1, -1), FromDIP(wxSize(x, y)), wxBORDER_SUNKEN);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox8 = new wxBoxSizer(wxHORIZONTAL);


    // A friendly message
    wxStaticText* descr = new wxStaticText( panel, wxID_STATIC,
          wxT("Please enter Tenant information"), wxDefaultPosition, wxDefaultSize,0 );

    hbox->Add(descr, 0);

      //owner info
    wxStaticText* TS = new wxStaticText( panel, wxID_STATIC,
          wxT("&Surname "), wxDefaultPosition, wxDefaultSize);

    wxStaticText* TN = new wxStaticText( panel, wxID_STATIC,
          wxT("&Other name "), wxDefaultPosition, wxDefaultSize);

    hbox1->Add(TS, 1, wxEXPAND);
    hbox1->AddSpacer(FromDIP(20));
    hbox1->Add(TN, 2, wxEXPAND);

   wxTextCtrl * t_s = new wxTextCtrl(panel, ID_SURNAME, wxT(" "), 
      wxDefaultPosition, wxDefaultSize, 0,  wxTextValidator(wxFILTER_ALPHA, &surname)); 

    wxTextCtrl * t_n = new wxTextCtrl(panel, ID_LASTNAME, wxT(" "), 
      wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &lstname)); 

    hbox2->Add(t_s, 1, wxEXPAND);
    hbox2->AddSpacer(FromDIP(20));
    hbox2->Add(t_n, 2, wxEXPAND);
   //Gender info
    wxStaticText* gender = new wxStaticText( panel, wxID_STATIC,
        wxT("&Gender: "), wxDefaultPosition, wxDefaultSize);

    wxString sexStrings[] = {
        wxT("Male"),
        wxT("Female")
      };


   wxChoice * sexChoice = new wxChoice ( this, ID_SEX,
          wxDefaultPosition, wxDefaultSize, WXSIZEOF(sexStrings), sexStrings, 0);
    sexChoice->SetStringSelection(wxT(" "));

    hbox3->Add(gender, 0);
    hbox3->AddSpacer(FromDIP(10));
    hbox3->Add(sexChoice, 1, wxEXPAND);

    //Number and account number
    //get_contact(panel);

    wxStaticText* tc_p = new wxStaticText( panel, wxID_STATIC,
        wxT("&Contact :"), wxDefaultPosition, wxDefaultSize);

    wxTextCtrl *tc = new wxTextCtrl(panel, ID_NUM, wxT("+254"), 
      wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE , &phone));

    hbox3->AddSpacer(FromDIP(20));
    hbox3->Add(tc_p, 0);
    hbox3->AddSpacer(FromDIP(10));
    hbox3->Add(tc, 2, wxEXPAND);

    //email
    wxStaticText* Acc = new wxStaticText( panel, wxID_STATIC,
        wxT("&Id Number :"), wxDefaultPosition, wxDefaultSize);

    wxTextCtrl * Acc_N = new wxTextCtrl(panel, ID_EMAIL, wxT(" "), 
      wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &Id_num));

    hbox4->Add(Acc, 0);
    hbox4->AddSpacer(FromDIP(10));
    hbox4->Add(Acc_N, 2, wxEXPAND);

    //House Number
    wxStaticText* house_number = new wxStaticText( panel, wxID_STATIC,
        wxT("&House No:"), wxDefaultPosition, wxDefaultSize);

    wxSpinCtrl * house_no_entry = new wxSpinCtrl(panel,ID_HOUSE_NO, wxT(" "), 
      wxPoint(-1, -1), wxDefaultSize, 0, 1, num_of_rooms);

    hbox5->Add(house_number);
    hbox5->AddSpacer(FromDIP(10));
    hbox5->Add(house_no_entry, 1, wxEXPAND);

    //House Type
    wxStaticText* htype = new wxStaticText( panel, wxID_STATIC,
       wxT("&House Type:"), wxDefaultPosition, wxDefaultSize);


    wxChoice * hytpechoice = new wxChoice (panel, ID_HOUSE_TYPE,
          wxDefaultPosition, wxDefaultSize, room_type);
    hytpechoice->SetStringSelection(wxT(" "));

    hbox5->AddSpacer(FromDIP(10));
    hbox5->Add(htype, 0);
    hbox5->AddSpacer(FromDIP(10));
    hbox5->Add(hytpechoice, 3, wxEXPAND);

    //wxTextCtrl * htype_entry = new wxTextCtrl(panel, ID_HOUSE_TYPE, wxT(" "), 
     // wxPoint(280, 180), wxSize(120, -1), 0, wxTextValidator(wxFILTER_NONE, &house_type));


    //month and year
    wxStaticText* month = new wxStaticText( panel, wxID_STATIC,
        wxT("&month: "), wxDefaultPosition, wxDefaultSize);

    wxStaticText* year = new wxStaticText( panel, wxID_STATIC,
        wxT("&year: "), wxDefaultPosition, wxDefaultSize);

    wxString monthStrings[] = {
        wxT("January"),wxT("February"), wxT("March"),
        wxT("April"), wxT("May"), wxT("June"),
        wxT("July"), wxT("August"), wxT("September"),
        wxT("October"), wxT("November"), wxT("December")
    };

    wxChoice * monthChoice = new wxChoice (panel, ID_MONTH,
          wxDefaultPosition, wxDefaultSize, WXSIZEOF(monthStrings), monthStrings, 0);
    monthChoice->SetStringSelection(wxT(" "));

    wxString yearstring[] = {
        wxT("2020"), wxT("2021"), wxT("2022"),wxT("2023"),
        wxT("2024"), wxT("2025"), wxT("2026"), wxT("2027"),
    };

    wxChoice * yearChoice = new wxChoice (panel, ID_YEAR,
          wxDefaultPosition, wxDefaultSize, WXSIZEOF(yearstring), yearstring, 0);
    yearChoice->SetStringSelection(wxT(" "));

    hbox6->Add(month, 0);
    hbox6->AddSpacer(FromDIP(10));
    hbox6->Add(monthChoice, 2, wxEXPAND);
    hbox6->AddSpacer(FromDIP(10));
    hbox6->Add(year, 0);
    hbox6->AddSpacer(FromDIP(10));
    hbox6->Add(yearChoice, 1, wxEXPAND);


   wxStaticLine* line = new wxStaticLine ( this, wxID_STATIC, 
      wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );

    hbox7->Add(line, 1, wxEXPAND);

    //Buttons

   wxButton *reset = new wxButton(panel, ID_RESET, wxT("Reset"), 
        wxDefaultPosition);

    wxButton *quit = new wxButton(panel, ID_EXIT, wxT("quit"), 
        wxDefaultPosition);


    wxButton *save = new wxButton(panel, ID_SAVE, wxT("Save"), 
      wxDefaultPosition);

    hbox8->Add(save, 1, wxEXPAND);
    hbox8->AddSpacer(FromDIP(10));
    hbox8->Add(reset, 1, wxEXPAND);
    hbox8->AddSpacer(FromDIP(10));
    hbox8->Add(quit, 1, wxEXPAND);

    Bind(wxEVT_BUTTON, &Tenant::Reset, this, ID_RESET);
    Bind(wxEVT_BUTTON, &Tenant::quit, this, ID_EXIT);
    Bind(wxEVT_BUTTON, &Tenant::save, this, ID_SAVE);

   // vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxLEFT| wxTOP, FromDIP(20));
    vbox->Add(hbox1, 0, wxLEFT| wxTOP | wxEXPAND, FromDIP(20));
    vbox->Add(hbox2, 0, wxLEFT | wxRIGHT | wxEXPAND, FromDIP(20));
    vbox->AddSpacer(FromDIP(10));
    vbox->Add(hbox3, 0, wxLEFT| wxTOP | wxRIGHT | wxEXPAND, FromDIP(20));
    vbox->AddSpacer(FromDIP(10));
    vbox->Add(hbox4, 0, wxLEFT| wxTOP | wxRIGHT | wxEXPAND, FromDIP(20));
    vbox->AddSpacer(FromDIP(10));
    vbox->Add(hbox5, 0, wxLEFT| wxTOP | wxRIGHT | wxEXPAND, FromDIP(20));
    vbox->AddSpacer(FromDIP(10));
    vbox->Add(hbox6, 0, wxLEFT| wxTOP | wxRIGHT | wxEXPAND, FromDIP(20));
    vbox->Add(hbox7, 0, wxTOP | wxEXPAND, FromDIP(10));
    vbox->AddSpacer(FromDIP(10));
    vbox->Add(hbox8, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, FromDIP(5));
    

    SetSizer(vbox);

    Centre();
    ShowModal();
    Destroy();

}

Tenant::~Tenant(){
  ///
}

void Tenant::init(){

    std::tm *now = get_curr_date();

    surname = wxEmptyString;
    lstname = wxEmptyString;
    Id_num = wxEmptyString;
    phone = "+254";
    house_no = 0;
    month = now->tm_mon + 1;
    year = now->tm_year + 1900;

}

bool Tenant::TransferDataToWindow(){
    wxTextCtrl *OwnN_entry_s = (wxTextCtrl*) FindWindow(ID_SURNAME);
    wxTextCtrl *OwnN_entry_n = (wxTextCtrl*) FindWindow(ID_LASTNAME);
  //  wxChoice *sexChoice = (wxChoice*) FindWindow(ID_SEX);

    wxTextCtrl *tc = (wxTextCtrl*) FindWindow(ID_NUM);
    wxTextCtrl *t_email = (wxTextCtrl*) FindWindow(ID_EMAIL);

    wxSpinCtrl *h_no = (wxSpinCtrl*) FindWindow(ID_HOUSE_NO);
//  wxChoice *h_type = (wxChoice*) FindWindow(ID_HOUSE_TYPE);

    wxChoice *t_month = (wxChoice*) FindWindow(ID_MONTH);
    wxChoice *t_year = (wxChoice*) FindWindow(ID_YEAR);  

    OwnN_entry_n->SetValue(surname);
    OwnN_entry_s->SetValue(lstname);

    tc->SetValue(phone);
    t_email->SetValue(Id_num);

    h_no->SetValue(house_no);

    t_month->SetSelection(month -1 );
    wxString yearstr = wxString::Format(wxT("%i"), year);

    t_year->SetStringSelection(yearstr);

    return true;
}

bool Tenant::TransferDataFromWindow(){
    wxTextCtrl *OwnN_entry_s = (wxTextCtrl*) FindWindow(ID_SURNAME);
    wxTextCtrl *OwnN_entry_n = (wxTextCtrl*) FindWindow(ID_LASTNAME);
    wxChoice *sexChoice = (wxChoice*) FindWindow(ID_SEX);

    wxTextCtrl *tc = (wxTextCtrl*) FindWindow(ID_NUM);
    wxTextCtrl *t_email = (wxTextCtrl*) FindWindow(ID_EMAIL);

    wxSpinCtrl *h_no = (wxSpinCtrl*) FindWindow(ID_HOUSE_NO);
    wxChoice *h_type = (wxChoice*) FindWindow(ID_HOUSE_TYPE);

    wxChoice *t_month = (wxChoice*) FindWindow(ID_MONTH);
    wxChoice *t_year = (wxChoice*) FindWindow(ID_YEAR);

    surname = OwnN_entry_s->GetValue();
    lstname = OwnN_entry_n->GetValue();
    gender = sexChoice->GetStringSelection();
   // sexChoice->SetSelection(gender);

    phone = tc->GetValue();
    Id_num = t_email->GetValue();

    house_no = h_no->GetValue();
    house_type = h_type->GetStringSelection();

    monthstr = t_month->GetStringSelection();
    year = wxAtoi(t_year->GetStringSelection());

    std::tm *now = get_curr_date();

    if (surname.IsEmpty() or lstname.IsEmpty() or phone.IsEmpty()
          or Id_num.IsEmpty() or house_type.IsEmpty()){
        wxLogError("Make sure \n all information \n are in the field");
        return false;

    if (house_no > max_room || house_no < 1){

                wxMessageBox(wxT("The room number\nis not availabel"), wxT("Room Error"), wxICON_ERROR);
    }

    }if((month != now->tm_mon + 1) or (year != now->tm_year + 1900)){

        wxLogError("Make sure \n you enter \n current time");
        return false;

    } else {

      return true;
     
    }
}


void Tenant::Reset(wxCommandEvent& event){
    init();
    TransferDataToWindow();
    event.Skip();
}

void Tenant::quit(wxCommandEvent& event){
       wxMessageDialog *dial = new wxMessageDialog(NULL,
      wxT("Are you sure\n to quit?"), wxT("Question"),
      wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

      int res;
      res = dial->ShowModal();

      switch (res)
      {
      case wxID_YES:
        Destroy();
        break;
      default:
        event.Skip();
        break;
      }
}

 void Tenant::save(wxCommandEvent& event){

      wxMessageDialog *dial = new wxMessageDialog(NULL,
      wxT("Are you sure to save\n the information ?"), wxT("Question"),
      wxYES_NO | wxICON_QUESTION);

      int res = dial->ShowModal();

      switch (res)
      {
        case wxID_YES:

          if (Validate() && TransferDataFromWindow()){
            // flag = 1;
            const char *sn;
            const char *nm;
            const char *phone_num;
            const char *mnth;
            const char *gen;
            const char *htype;

            sn = wxstring_to_char(surname);
            nm = wxstring_to_char(lstname);
            phone_num = wxstring_to_char(phone);
            mnth = wxstring_to_char(monthstr);
            gen = wxstring_to_char(gender);
            htype = wxstring_to_char(house_type);


            plot.insert_tenant(plotid.c_str(), wxAtoi(Id_num), gen, sn, nm, phone_num, mnth, year, htype, house_no);

            if (IsModal()){

                EndModal(wxID_OK); // If modal

            }else{

              SetReturnCode(wxID_OK);
              this->Show(false); // If modeless
            }
              
          }
          
          break;
        case wxID_NO:
            dial->Destroy();
            break;
        
        default:
        //
          break;
      }
     // event.Skip();
}




/**************************************************************************************************************************/
//generate universal unique Id (uuid) which is 
// converted to string and used in the database as
// primary key
std::string  generateId(){
	boost::uuids::random_generator generator;
	boost::uuids::uuid uuid = generator();
  std::string tmp = boost::lexical_cast<std::string>(uuid);

	return tmp;
	
}

/*************************************************************************************************************************/

EditPlotDialog::EditPlotDialog(const wxString& title, wxString tb, wxString acc, wxString var,
                 wxString var1, wxString lc, wxString varname1, wxString varname2, double x, double y)
                :wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(x, y))
{

    wxPanel *panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(x, y), wxBORDER_SUNKEN);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *old = new wxStaticText(panel, -1, varname1, wxPoint(-1, -1),
                        wxDefaultSize);

    hbox->Add(old, 0);

    wxTextCtrl *oldtext = new wxTextCtrl(panel, ID_NAME, wxEmptyString, wxPoint(-1, -1), 
                             wxSize(170, -1), 0, wxDefaultValidator, name);

   hbox1->Add(oldtext, 1, wxEXPAND);

    wxStaticText *old1 = new wxStaticText(panel, -1, varname2, wxPoint(-1, -1),
                    wxDefaultSize);

    hbox2->Add(old1, 0);
    
    wxTextCtrl *oldtext1 = new wxTextCtrl(panel, ID_NAME1, wxEmptyString, wxPoint(-1, -1), 
                             wxSize(170, -1), 0, wxDefaultValidator, name1);
    
    hbox3->Add(oldtext1, 1, wxEXPAND);

    wxButton *okButton = new wxButton(this, ID_LIST_SAVE, wxT("Change"), 
      wxDefaultPosition, wxDefaultSize);
    wxButton *closeButton = new wxButton(this, ID_LIST_DLG_CLOSE, wxT("Close"), 
       wxDefaultPosition, wxDefaultSize);

    hbox4->Add(okButton, 1, wxEXPAND);
    hbox4->AddSpacer(20);
    hbox4->Add(closeButton, 1, wxEXPAND);

    varnm = var;
    varloc = var1;
    tbstr = tb;
    lcstr = lc;
    acct = acc;

    Bind(wxEVT_BUTTON, &EditPlotDialog::onsave, this, ID_LIST_SAVE);
    Bind(wxEVT_BUTTON, &EditPlotDialog::onclose, this, ID_LIST_DLG_CLOSE);


    vbox->Add(hbox, 0, wxLEFT | wxTOP, 10);
    vbox->Add(hbox1, 0, wxLEFT | wxRIGHT | wxEXPAND, 10);
    vbox->Add(hbox2, 0, wxLEFT | wxTOP , 10);
    vbox->Add(hbox3, 0, wxLEFT | wxRIGHT| wxEXPAND, 10);
    vbox->AddSpacer(5);
    vbox->Add(hbox4, 0, wxLEFT | wxTOP | wxRIGHT| wxEXPAND, 10);

    SetSizer(vbox);

    Centre();
    ShowModal();

    Destroy();
    
}

EditPlotDialog::~EditPlotDialog(){
    Unbind(wxEVT_BUTTON, &EditPlotDialog::onsave, this, ID_LIST_SAVE);
    Unbind(wxEVT_BUTTON, &EditPlotDialog::onclose, this, ID_LIST_DLG_CLOSE);
}

void EditPlotDialog::onsave(wxCommandEvent& event){
    std::string sql;
   
    TransferDataFromWindow();

    std::string varstr = "\'"+ varnm.ToStdString() + "\'";
    std::string varstr1 = "\'" + varloc.ToStdString() + "\'";

    std::string namestr = "\'"+ name.ToStdString() + "\'";
    std::string name1str = "\'" + name1.ToStdString() + "\'";

    if (name.IsEmpty() && !name1.IsEmpty()){

        wxString strf = wxString::Format("UPDATE %s SET %s = %s WHERE %s = %s AND %s = %s ",
                                        tbstr, lcstr, name1str, acct, varstr,  lcstr, varstr1);


        plot.update_info(strf.ToStdString());
  

    }else if(name1.IsEmpty() && !name.IsEmpty() ){

        wxString strf = wxString::Format("UPDATE %s SET %s = %s WHERE %s = %s AND %s = %s ",
                                         tbstr, acct, namestr, acct, varstr, lcstr, varstr1);

        std::cout << strf << std::endl;

       plot.update_info(strf.ToStdString());

    } else if (!name.IsEmpty() && !name1.IsEmpty()){


        wxString strf = wxString::Format("UPDATE %s SET Name = %s, %s = %s WHERE Name = %s AND %s = %s ",
                                         tbstr, namestr, lcstr, name1str, varstr, lcstr, varstr1);

       plot.update_info(strf.ToStdString());
  
    }else{
        ///
    }
}

bool EditPlotDialog::TransferDataFromWindow(){
    wxTextCtrl *oldtext = (wxTextCtrl*) FindWindow(ID_NAME);
    wxTextCtrl *oldtext1 = (wxTextCtrl*) FindWindow(ID_NAME1);

    name = oldtext->GetValue();
    name1 = oldtext1->GetValue();

    return true;
}

void EditPlotDialog::onclose(wxCommandEvent &event){
    event.Skip();
    Close(true);
}

/************************************************************************************************************************/

FormLogin::FormLogin(const wxString& title, double x, double y)
: wxDialog(NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY),wxSize(x, y))
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    SetBackgroundColour(wxColor(173,223,173));
 
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
 
     m_usernameLabel = new wxStaticText(panel, wxID_ANY, wxT("Username: "), wxPoint(-1, -1), wxSize(-1, -1));
     hbox1->Add(m_usernameLabel, 0);
     hbox1->AddSpacer(20);
 
    m_usernameEntry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(280, -1));
    hbox1->Add(m_usernameEntry, 1, wxEXPAND);
 
    m_passwordLabel = new wxStaticText(panel, wxID_ANY, wxT("Password: "), wxPoint(-1, -1), wxSize(-1, -1));
    hbox2->Add(m_passwordLabel, 0);
    hbox2->AddSpacer(20);
 
    m_passwordEntry = new wxTextCtrl(panel, wxID_ANY, wxString(""), wxPoint(-1, -1), wxSize(280, -1), wxTE_PASSWORD);
    hbox2->Add(m_passwordEntry, 1, wxEXPAND);
    
    //checkbox = new wxCheckBox(panel, REM_id, wxT("Remember me ") ,wxPoint(240, 200), wxSize(-1, -1));
    //checktxt = new wxStaticText(panel, wxID_ANY, wxT("Remember me "), wxPoint(260, 201), wxSize(-1, -1));

    line = new wxStaticLine(panel, wxID_ANY, wxPoint(-1, -1), wxSize(380, -1));
    hbox3->Add(line, 1, wxEXPAND);
    //slink = new wxHyperlinkCtrl(panel, wxID_ANY, wxT("Sign up"), wxEmptyString, wxPoint(170, 240), wxSize(-1, -1));


    fpasswd = new wxCheckBox(panel, CHECKBOX_id, wxT("Forget password"), wxPoint(-1, -1), wxSize(-1, -1));
    hbox4->Add(fpasswd, 1, wxEXPAND);
   // hbox4->AddSpacer(100);
   // fpwd = new wxStaticText(panel, wxID_ANY, wxT("Forget password"), wxPoint(180, 244), wxSize(-1, -1));
   // hbox4->Add(fpwd, 0);
   rows = 0;

   check();

   std::ifstream ifile;
   ifile.open("deta.db");
   if(ifile) {

       if(rows == 0){

            signup = new wxButton(panel, BUTTON_Sign, wxT("Register"), wxPoint(-1, -1), wxSize(-1, -1));
            hbox4->AddSpacer(25);
            hbox4->Add(signup, 0);
            hbox4->AddSpacer(5);


        }else{
            hbox4->AddSpacer(130);
            //
        }
    }else {
        //
    }

   m_buttonLogin = new wxButton(panel, BUTTON_Login, wxT("Login"), wxPoint(-1, -1), wxSize(-1, -1));
   hbox4->Add(m_buttonLogin, 0);
 
   //m_buttonQuit = new wxButton(panel, wxID_EXIT, ("Quit"));
   // hbox3->Add(m_buttonQuit);
    //vbox->Add(panel, 0 | wxALL, 10);

    create_login();
 
    Centre();

    vbox->Add(hbox1, 0, wxLEFT | wxRIGHT |wxTOP | wxEXPAND, 200);
    vbox->AddSpacer(20);
    vbox->Add(hbox2, 0, wxLEFT | wxRIGHT | wxEXPAND, 200);
    vbox->AddSpacer(20);
    vbox->Add(hbox3, 0, wxLEFT | wxRIGHT | wxEXPAND, 200);
    vbox->AddSpacer(20);
    vbox->Add(hbox4, 0, wxLEFT | wxRIGHT | wxEXPAND, 200);
    panel->SetSizerAndFit(vbox);
   // ShowModal();

    //Destroy();

    xdim = (x / 1.5) *3;
    ydim = (y / 2) *3;
}
 
void FormLogin::OnQuit(wxCommandEvent& event)
{
    Close(true);
}
 
void FormLogin::OnLogin(wxCommandEvent& event)
{

    wxString username = m_usernameEntry->GetValue();
    wxString password = m_passwordEntry->GetValue();

    std::string nm;
    std::string ps;
 
    if (username.empty() || password.empty()) {

        wxMessageBox(wxT("Username or\npassword\nmust not empty"), wxT("Warning!"), wxICON_WARNING);

    }
    else {
        
        std::map<std::string, std::string> ans = get_details();

        std::map<std::string, std::string>::iterator itr;

        for (itr = ans.begin(); itr != ans.end(); ++itr) {

            nm = itr->first;
            ps = itr->second;
        }
        
        

        if(nm.empty() != true || ps.empty() != true){

            std::string passcode = sha256(std::string(password.mb_str()));

           
            if ((std::string(username.mb_str()) == nm) && (passcode == ps)){

                wxMessageBox(wxT("Welcome"), wxT("Message!"), wxICON_INFORMATION);

                res = true;

                Close(true);

            }else{

                wxMessageBox(wxT("Incorrent details"), wxT("Warning!"), wxICON_WARNING);
            }

        }else{

            wxMessageBox(wxT("No such user"), wxT("Warning!"), wxICON_WARNING);
        }
        
    }
}

void FormLogin::OnSign(wxCommandEvent& event)
{
    double sx, sy;
    sx = (xdim / 3) * 1;
    sy = (ydim / 3) * 2.25;

    formsign = new Sign(wxT("Signup"), sx, sy);
    formsign->Show();
    res = formsign->check_res();

    check();
 
    if (rows == 1){
        Close(true);
    }
}


void FormLogin::OnReset(wxCommandEvent& event)
{
    double xf, yf;
    xf = (xdim / 3) * 0.9;
    yf = (ydim / 3) * 1.2;


    if (fpasswd->IsChecked() == true){
        ForgetPassword *forget= new ForgetPassword("Reset password", xf, yf);
        forget->Show();
    }
}

/*void FormLogin::OnRem(wxCommandEvent& event)
{
    if (checkbox->IsChecked()){

        std::ifstream ifile;
        ifile.open("deta.db");
        if(ifile) {

            std::map<std::string, std::string> ans = get_details();

            std::map<std::string, std::string>::iterator itr;

            for (itr = ans.begin(); itr != ans.end(); ++itr) {
                namecode = itr->first;
                passwordcode = itr->second;
            }

        } else {

          std::cout<<"file doesn't exist" << std::endl;
        }
    }
}*/

std::map<std::string, std::string>FormLogin::get_details(){

    std::string nm;
    std::string ps;

    const char *sn;
    const char *ln;

    std::map<std::string, std::string> res;

    std::string sql = "SELECT  * FROM deta";
        
    sqlite3_open("deta.db", &db);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    rc = sqlite3_step(stmt);

    while(rc == SQLITE_ROW) {

        sn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        ln = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 1));

        if(sn != NULL || ln !=NULL){

            nm = convertToString(sn);
            ps = convertToString(ln );

        }
        rc = sqlite3_step(stmt);

        res.insert(std::pair<std::string, std::string>(nm, ps));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return res;

}

void FormLogin::check(){

    std::string str = "select count(*) from deta";

    if (sqlite3_open("deta.db", &db) == SQLITE_OK)
    {
        sqlite3_prepare_v2( db, str.c_str(), -1, &stmt, NULL);//preparing the statement
        
        if (sqlite3_step(stmt) == SQLITE_ERROR) {

            std::cout << "Error" << sqlite3_errmsg(db) << std::endl;

        } else {

            rows = sqlite3_column_int(stmt, 0);

        }
        
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

}

bool FormLogin::check_res(){

   // bool signres = formsign->check_res();

    //std::cout << signres << std::endl;

    if (res == true){

        return true;


    }else{

        return false;

    }
}

 
FormLogin::~FormLogin() {}
 
BEGIN_EVENT_TABLE(FormLogin, wxDialog)
EVT_BUTTON(wxID_EXIT, FormLogin::OnQuit)
EVT_BUTTON(BUTTON_Login, FormLogin::OnLogin)
EVT_BUTTON(BUTTON_Sign, FormLogin::OnSign)
EVT_CHECKBOX(CHECKBOX_id, FormLogin::OnReset)
//EVT_CHECKBOX(REM_id, FormLogin::OnRem)
END_EVENT_TABLE()


/************************************************************************************************************************/

Sign::Sign(const wxString& title, double x, double y)
: wxDialog(NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY),wxSize(x, y))
{

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2a = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox8 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox9 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox10 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox11 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox12 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox13 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox14 = new wxBoxSizer(wxHORIZONTAL);

    ag_name = new wxStaticText(panel, wxID_ANY, wxT("Agent Name: "), wxPoint(-1, -1), wxSize(-1, -1));
    ag_name_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));

    hbox1->Add(ag_name, 0);
    hbox1->AddSpacer(20);
    hbox1->Add(ag_name_entry, 1, wxEXPAND);


    SetBackgroundColour(wxColor(192,192,192));

    //names
    fname_t = new wxStaticText(panel, wxID_ANY, wxT("Surname: "), wxPoint(-1, -1), wxSize(-1, -1));
    fname_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox2->Add(fname_t, 0);
    hbox2->AddSpacer(10);
    hbox2->Add(fname_entry, 1, wxEXPAND);

    sname_t = new wxStaticText(panel, wxID_ANY, wxT("name: "), wxPoint(-1, -1), wxSize(-1, -1));
    sname_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox2a->Add(sname_t, 0);
    hbox2a->AddSpacer(20);
    hbox2a->Add(sname_entry, 1, wxEXPAND);

    //username
    username = new wxStaticText(panel, wxID_ANY, wxT("Enter Username "), wxPoint(-1, -1), wxSize(-1, -1));
    username_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox3->Add(username, 0);
    hbox4->Add(username_entry, 1, wxEXPAND);


    //password
    pass_t = new wxStaticText(panel, wxID_ANY, wxT("Password "), wxPoint(-1, -1), wxSize(-1, -1));
    pass_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1), wxTE_PASSWORD);
    hbox5->Add(pass_t, 0);
    hbox6->Add(pass_entry, 1, wxEXPAND);


    pass2_t = new wxStaticText(panel, wxID_ANY, wxT("Re type password "), wxPoint(-1, -1), wxSize(-1, -1));
    pass2_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(230, -1), wxTE_PASSWORD);
    hbox7->Add(pass2_t, 0);
    hbox8->Add(pass2_entry, 1, wxEXPAND);

    //details
    phone_t = new wxStaticText(panel, wxID_ANY, wxT("Contact 1"), wxPoint(-1, -1), wxSize(-1, -1));
    phone_entry = new wxTextCtrl(panel, wxID_ANY, wxT("+254"), wxPoint(-1, -1), wxSize(-1, -1));
    hbox9->Add(phone_t, 0);
    hbox9->AddSpacer(10);
    hbox9->Add(phone_entry, 1, wxEXPAND);
    hbox9->AddSpacer(20);

    phonet_2 = new wxStaticText(panel, wxID_ANY, wxT("Contact 2"), wxPoint(-1, -1), wxSize(-1, -1));
    phone_entry2 = new wxTextCtrl(panel, wxID_ANY, wxT("+254"), wxPoint(-1, -1), wxSize(-1, -1));
    hbox9->Add(phonet_2, 0);
    hbox9->AddSpacer(10);
    hbox9->Add(phone_entry2, 1, wxEXPAND);

    loc_t = new wxStaticText(panel, wxID_ANY, wxT("Location "), wxPoint(-1, -1), wxSize(-1, -1));
    loc_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox10->Add(loc_t, 0);
    hbox10->AddSpacer(30);
    hbox10->Add(loc_entry, 1, wxEXPAND);

    email  = new wxStaticText(panel, wxID_ANY, wxT("Email "), wxPoint(-1, -1), wxSize(-1, -1));
    email_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox11->Add(email, 0);
    hbox11->AddSpacer(30);
    hbox11->Add(email_entry, 1, wxEXPAND);

    web  = new wxStaticText(panel, wxID_ANY, wxT("Website "), wxPoint(-1, -1), wxSize(-1, -1));
    web_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox12->Add(web, 0);
    hbox12->AddSpacer(30);
    hbox12->Add(web_entry, 1, wxEXPAND);

    //usermax = new wxStaticText(panel, wxID_ANY, wxT("Maxixum user required <=3 "), wxPoint(200, 350), wxSize(-1, -1));
    //usermax_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(200, 370), wxSize(150, -1));

    line = new wxStaticLine(panel, wxID_ANY, wxPoint(-1, -1), wxSize(y, -1));
    hbox13->Add(line, 1, wxEXPAND);

    reg = new wxButton(panel, BUTTON_save, wxT("Register"), wxPoint(-1, -1), wxSize(-1, -1));
    quit = new wxButton(panel, BUTTON_quit, wxT("quit"), wxPoint(-1, -1), wxSize(-1, -1));

    hbox14->Add(reg, 1, wxEXPAND);
    hbox14->AddSpacer(30);
    hbox14->Add(quit, 1, wxEXPAND);

    vbox->Add(hbox1, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 30);
    vbox->Add(hbox2, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 30);
    vbox->Add(hbox2a, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 30);
    vbox->Add(hbox3, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 30);
    vbox->AddSpacer(20);
    vbox->Add(hbox4, 0, wxLEFT | wxRIGHT |  wxEXPAND, 30);
    vbox->AddSpacer(20);
    vbox->Add(hbox5, 0, wxLEFT | wxRIGHT | wxEXPAND, 30);
    vbox->AddSpacer(20);
    vbox->Add(hbox6, 0, wxLEFT | wxRIGHT | wxEXPAND, 30);
    vbox->AddSpacer(20);
    vbox->Add(hbox7, 0, wxLEFT | wxRIGHT | wxEXPAND, 30);
    vbox->AddSpacer(20);
    vbox->Add(hbox8, 0, wxLEFT | wxRIGHT | wxEXPAND, 30);
    vbox->AddSpacer(30);
    vbox->Add(hbox9, 0, wxLEFT | wxRIGHT  | wxEXPAND, 30);
    vbox->AddSpacer(2);
    vbox->Add(hbox10, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 30);
    vbox->AddSpacer(2);
    vbox->Add(hbox11, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 30);
    vbox->AddSpacer(2);
    vbox->Add(hbox12, 0, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 30);
    vbox->AddSpacer(2);
    vbox->Add(hbox13, 0, wxTOP | wxEXPAND, 30);
    vbox->AddSpacer(20);
    vbox->Add(hbox14, 0, wxLEFT | wxRIGHT | wxEXPAND, 30);

    panel->SetSizerAndFit(vbox);

    Bind(wxEVT_BUTTON, &Sign::OnSave, this, BUTTON_save);
    Bind(wxEVT_BUTTON, &Sign::onquit, this, BUTTON_quit);

    ShowModal();
    Destroy();
}

Sign::~Sign() {}

void Sign::OnSave(wxCommandEvent& event){

    sqlite3_stmt *stmt;
    char* messaggeError = nullptr;
    const char* tail;
    sqlite3 *db;

    wxString Agent_name, fname, sname,
                 phon_number, phone2, location,
                 password, password2, usermail, userweb;


    wxString username = username_entry->GetValue();
    wxString pass1 = pass_entry->GetValue();
    wxString pass2 = pass2_entry->GetValue();
    fname = fname_entry->GetValue();
    sname = sname_entry->GetValue();
    phon_number = phone_entry->GetValue();
    phone2 = phone_entry2->GetValue();
    location = loc_entry->GetValue();
    //wxString userm = usermax_entry->GetValue();
    Agent_name = ag_name_entry->GetValue();
    usermail = email_entry->GetValue();
    userweb = web_entry->GetValue();

    wxString cont = phon_number + "/" + phone2;

    if (pass1 == pass2){

        wxString password = pass1;

        if (username.IsEmpty() != true  && pass1.IsEmpty() != true && pass2.IsEmpty() != true){

            std::string pass = sha256(std::string(password.mb_str()));
            std::string user = std::string(username.mb_str());

            std::string sql;
            int rs;
            sql = "INSERT INTO deta(username, password, surname, name, phone, location, Agentname, Email, Website)\
             VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

            rs = sqlite3_open("deta.db", &db);
            rs = sqlite3_prepare_v2(db, "PRAGMA foreign_keys = OFF", -1, &stmt, &tail);
            rs = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);


            if (rs != SQLITE_OK) {
                std::cerr << "Cant insert values to rows " << std::endl;
                sqlite3_free(messaggeError);
            }

            sqlite3_bind_text(stmt, 1, user.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, pass.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, std::string(sname.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 4, std::string(fname.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 5, std::string(cont.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 6, std::string(location.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 7, std::string(Agent_name.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt,  8, std::string(usermail.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt,  9, std::string(userweb.mb_str()).c_str(), -1, SQLITE_TRANSIENT);


            rs = sqlite3_step(stmt);
            rs = sqlite3_finalize(stmt);
            sqlite3_close(db);
            res = true;
            //wxMessageBox(wxT("Welcome"), wxT("Message!"), wxICON_INFORMATION);

            this->Destroy();

        }else{
            wxMessageBox("Make sure all\n values are entered", wxT("Warning!"), wxICON_WARNING);
        }
    }else{
        wxMessageBox("password dont\nmatch", wxT("Warning!"), wxICON_WARNING);
    }

}

void Sign::onquit(wxCommandEvent& event){

    Close(true);

}

bool Sign::check_res(){

    if (res == true){

        return true;
    }
    else{

        return false;

    }

}

/************************************************************************************************************************/

ForgetPassword::ForgetPassword(const wxString& title, double x, double y)
: wxDialog(NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY),wxSize(x, y))
{
     wxPanel *panel = new wxPanel(this, wxID_ANY);

     SetBackgroundColour(wxColor(192,192,192));

     wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
     wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer *hbox7 = new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer *hbox8 = new wxBoxSizer(wxHORIZONTAL);

    username = new wxStaticText(panel, wxID_ANY, wxT("Enter Username:"), wxPoint(-1, -1), wxSize(-1, -1));
    username_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox1->Add(username,0);
    hbox1->AddSpacer(10);
    hbox1->Add(username_entry, 1, wxEXPAND);

    phone = new wxStaticText(panel, wxID_ANY, wxT("Contact used for registration"), wxPoint(-1, -1), wxSize(-1, -1));
    phone_entry = new wxTextCtrl(panel, wxID_ANY, wxT("+254"), wxPoint(-1, -1), wxSize(-1, -1));
    hbox2->Add(phone, 0);
    hbox2->AddSpacer(10);
    hbox2->Add(phone_entry, 1, wxEXPAND);

    newpasswd = new wxStaticText(panel, wxID_ANY, wxT("Enter new password"), wxPoint(-1, -1), wxSize(-1, -1));
    newpasswd_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(200, -1), wxTE_PASSWORD);

    hbox3->Add(newpasswd, 0);
    hbox4->Add(newpasswd_entry, 1, wxEXPAND);

    repasswd= new wxStaticText(panel, wxID_ANY, wxT("Re-type password"), wxPoint(-1, -1), wxSize(-1, -1));
    repasswd_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(-1, -1), wxSize(200, -1), wxTE_PASSWORD);

    hbox5->Add(repasswd, 0);
    hbox6->Add(repasswd_entry, 1, wxEXPAND);

    line = new wxStaticLine(panel, wxID_ANY, wxPoint(-1, -1), wxSize(350, -1));
    hbox7->Add(line, 1, wxEXPAND);

    change = new wxButton(panel, BUTTON_save, wxT("Save changes"), wxPoint(-1, -1), wxSize(190, -1));
    quit = new wxButton(panel, BUTTON_quit, wxT("quit"), wxPoint(-1, -1), wxSize(190, -1));

    hbox8->Add(change, 1, wxEXPAND);
    hbox8->AddSpacer(50);
    hbox8->Add(quit, 1, wxEXPAND);

    vbox->Add(hbox1, 0, wxLEFT | wxTOP | wxRIGHT |wxEXPAND, 20);
    vbox->AddSpacer(40);
    vbox->Add(hbox2, 0, wxLEFT | wxRIGHT |wxEXPAND, 20);
    vbox->AddSpacer(40);
    vbox->Add(hbox3, 0, wxLEFT, 20);
    vbox->Add(hbox4, 0, wxLEFT | wxRIGHT |wxEXPAND, 20);
    vbox->AddSpacer(40);
    vbox->Add(hbox5, 0, wxLEFT, 20);
    vbox->Add(hbox6, 0, wxLEFT | wxRIGHT |wxEXPAND, 20);
    vbox->AddSpacer(20);
    vbox->Add(hbox7, 0, wxEXPAND);
    vbox->AddSpacer(10);
    vbox->Add(hbox8, 0, wxLEFT | wxRIGHT |wxEXPAND, 20);
    
    panel->SetSizerAndFit(vbox);

    Bind(wxEVT_BUTTON, &ForgetPassword::onsave, this, BUTTON_save);
    Bind(wxEVT_BUTTON, &ForgetPassword::onquit, this, BUTTON_quit);


    Center();
    ShowModal();
    Destroy();
}

ForgetPassword::~ForgetPassword(){}

//retrieve details from the database and strore in a map,
// the function returns map in the pair <string, string>
std::map<std::string, std::string>ForgetPassword::get_details(){

    std::string nm;
    std::string ps;

    const char *sn;
    const char *ln;

    std::map<std::string, std::string> res;

    std::string sql = "SELECT  * FROM deta";
        
    sqlite3_open("deta.db", &db);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);


    rc = sqlite3_step(stmt);

    while(rc == SQLITE_ROW) {

        sn = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        ln = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 4));

        if(sn != NULL || ln !=NULL){

            nm = convertToString(sn);
            ps = convertToString(ln );

        }
        rc = sqlite3_step(stmt);

        res.insert(std::pair<std::string, std::string>(nm, ps));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return res;

}

//This function is used with conjuction with save function forgetpassword dialog 
//class to update the details in the database
void ForgetPassword::update_details(std::string username, std::string phone, std::string pass){

    std::string name = "\'" + username + "\'";  //sqlite3 statement requires arguments to be in ''
    std::string pho = "\'" + phone + "\'";
    std::string new_pass = "\'" + pass + "\'";

    std::string str = "UPDATE deta SET password =  " + new_pass + " WHERE username = " + name + " AND phone = " + pho;


    if (sqlite3_open("deta.db", &db) == SQLITE_OK)
    {
        sqlite3_prepare_v2( db, str.c_str(), -1, &stmt, NULL);//preparing the statement
        sqlite3_step( stmt );
        
        
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// used to reset password, which stores it into the database
//this function first retrieve the required information 
//from the user , then does a comparison with the information
// at the application end, if information provided is true ,
// it resets the password
void ForgetPassword::onsave(wxCommandEvent& event){

    std::map<std::string, std::string> ans = get_details();

    std::map<std::string, std::string>::iterator itr;

    std::string str1, str2;
    std::string nm1, nm2;

    for (itr = ans.begin(); itr != ans.end(); ++itr) {
            str1 = itr->first;
            str2 = itr->second;
    }


    nm1 = std::string(username_entry->GetValue().mb_str());
    nm2 = std::string(phone_entry->GetValue().mb_str());

    if (nm1.empty() == true || nm1.empty() == true ){

        wxMessageBox("Insert all values", wxT("Warning!"), wxICON_WARNING);

    }else{

        if (nm1 != str1 || nm2 != str2){

            wxMessageBox("No such details", wxT("Warning!"), wxICON_WARNING);

        }else{

            std::string pas1 =std::string(newpasswd_entry->GetValue().mb_str());
            std::string pas2 = std::string(repasswd_entry->GetValue().mb_str());

            if (pas1 != pas2){

                wxMessageBox("password dont match", wxT("Warning!"), wxICON_WARNING);

            }else{

                std::string pass= sha256(pas1);
                update_details(str1, str2, pass);

                wxMessageBox("update was \n a success", wxT("reset"));

                Destroy();

            }

        }
    }


}

//closing the dialog frame
void ForgetPassword::onquit(wxCommandEvent& event){

    Close(true);

    bool checkstate;

    checkstate = fpasswd->IsChecked();

    if (checkstate == true){

        fpasswd->SetValue(false);

    } else{
       //Do nothing
    }

}

/**************************************************************************************************************************************/

BankDialog::BankDialog(const wxString& title, double x, double y)
: wxDialog(NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY),wxSize(x, y))
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    Init();

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox8 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox9 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox10 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *details = new wxStaticText(this, wxID_ANY, wxT("Enter Payment details "), wxPoint(-1, -1), wxSize(-1, -1));
    hbox1->Add(details, 0);
    wxStaticText *nametxt = new wxStaticText(this, wxID_ANY, wxT("Received from "), wxPoint(-1, -1), wxSize(-1, -1));
    wxStaticText *idnumtxt = new wxStaticText(this, wxID_ANY, wxT("ID Number"), wxPoint(-1, -1), wxSize(-1, -1));
    hbox2->Add(nametxt, 2, wxEXPAND);
    hbox2->Add(idnumtxt, 1, wxEXPAND);

    name_entry = new wxTextCtrl(this, ID_RECEIV, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    idnum_entry = new wxTextCtrl(this, NUM_ID, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));
    hbox3->Add(name_entry, 2, wxEXPAND);
    hbox3->AddSpacer(10);
    hbox3->Add(idnum_entry, 1, wxEXPAND);

     wxStaticText *transaction_id_text = new wxStaticText(this, wxID_ANY, wxT("Transaction ID : "), wxPoint(-1, -1), wxSize(-1, -1));
    transaction_id = new wxTextCtrl(this, ID_TRANS, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));

    hbox4->Add(transaction_id_text, 0);
    hbox4->AddSpacer(20);
    hbox4->Add(transaction_id, 1, wxEXPAND);


    wxStaticText *amount_text = new wxStaticText(this, wxID_ANY, wxT("Amount in Ksh : "), wxPoint(-1, -1), wxSize(-1, -1));
    amount = new wxTextCtrl(this, ID_AMT, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));

    hbox5->Add(amount_text, 0);
    hbox5->AddSpacer(20);
    hbox5->Add(amount, 1, wxEXPAND);

    wxStaticText *balance_text = new wxStaticText(this, wxID_ANY, wxT("Balance in Ksh : "), wxPoint(-1, -1), wxSize(-1, -1));
    balance = new wxTextCtrl(this, ID_BAL, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));

    hbox6->Add(balance_text, 0);
    hbox6->AddSpacer(20);
    hbox6->Add(balance, 1, wxEXPAND);

    wxStaticText *plot_text = new wxStaticText(this, wxID_ANY, wxT("Plot name : "), wxPoint(-1, -1), wxSize(-1, -1));
    plotname = new wxChoice(this, ID_PLOT,  wxPoint(-1, -1), wxSize(-1, -1), plotchoicetxt);

    hbox7->Add(plot_text, 0);
    hbox7->AddSpacer(20);
    hbox7->Add(plotname, 2, wxEXPAND);
    hbox7->AddSpacer(20);

    wxStaticText *room_text = new wxStaticText(this, wxID_ANY, wxT("Room No : "), wxPoint(-1, -1), wxSize(-1, -1));
    room_no = new wxTextCtrl(this, ID_RM, wxEmptyString, wxPoint(-1, -1), wxSize(-1, -1));

    hbox7->Add(room_text, 0);
    hbox7->AddSpacer(20);
    hbox7->Add(room_no, 1, wxEXPAND);

    wxStaticText *date = new wxStaticText(this, wxID_ANY, wxT("Date Transacted : "), wxPoint(-1, -1), wxSize(-1, -1));
    hbox8->Add(date, 0);

    cal = new wxCalendarCtrl(this, ID_DY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize);
    hbox9->Add(cal, 1, wxEXPAND);

    quit = new wxButton(this, ID_BT_CLOSE, "quit", wxDefaultPosition, wxDefaultSize);
    ok = new wxButton(this, ID_BT_OK, "Ok", wxDefaultPosition, wxDefaultSize);

    hbox10->Add(ok, 1, wxEXPAND);
    hbox10->Add(quit, 1, wxEXPAND);

    vbox->Add(panel, 1);

    vbox->Add(hbox1, 0, wxTOP | wxLEFT, 20);
    vbox->Add(hbox2, 0, wxTOP | wxLEFT | wxEXPAND, 20);
    vbox->AddSpacer(10);
    vbox->Add(hbox3, 0, wxLEFT | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);
    vbox->Add(hbox4, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);
    vbox->Add(hbox5, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);
    vbox->Add(hbox6, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);
    vbox->Add(hbox7, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(20);
    vbox->Add(hbox8, 0, wxLEFT, 20);
    vbox->AddSpacer(10);
    vbox->Add(hbox9, 0, wxLEFT | wxRIGHT | wxEXPAND, 20);
    vbox->AddSpacer(10);
    vbox->Add(hbox10, 0, wxLEFT | wxRIGHT | wxEXPAND, 20);

    SetSizer(vbox);

    SetBackgroundColour(wxColor(192,192,192));


    Bind(wxEVT_BUTTON, &BankDialog::onsave, this, ID_BT_OK);
    Bind(wxEVT_BUTTON, &BankDialog::onclose, this, ID_BT_CLOSE);

    Center();
    ShowModal();
    Destroy();
}

BankDialog::~BankDialog(){}

void BankDialog::Init(){

    bank_array = plot.get_plot();

    for (auto x: bank_array){
        plotchoicetxt.push_back(x.plotname);
    }

}

bool BankDialog::TransferDataFromWindow(){
    wxTextCtrl *rec = (wxTextCtrl*) FindWindow(ID_RECEIV);
    wxTextCtrl *tid = (wxTextCtrl*) FindWindow(ID_TRANS);

    wxTextCtrl *amt = (wxTextCtrl*) FindWindow(ID_AMT);
    wxTextCtrl *ba = (wxTextCtrl*) FindWindow(ID_BAL);

    wxChoice *recplot = (wxChoice*) FindWindow(ID_PLOT);
    wxTextCtrl *rmrec = (wxTextCtrl*) FindWindow(ID_RM);
    wxTextCtrl *numidrec = (wxTextCtrl*) FindWindow(NUM_ID);

    wxCalendarCtrl *calend = (wxCalendarCtrl*) FindWindow(ID_DY);

    name = rec->GetValue();
    trans_id = tid->GetValue();

    if (numidrec->GetValue().IsEmpty()){
        zId_Num = 0;
    } else{
        zId_Num = wxAtoi(numidrec->GetValue());
    }

    if (amt->GetValue().IsEmpty()){
        rent_amount = 0;
    } else{
        rent_amount = wxAtoi(amt->GetValue());
    }
    
    rent_bal = wxAtoi(ba->GetValue());

    plotnametext= recplot->GetStringSelection();

    if (rmrec->GetValue().IsEmpty()){
        rmno = 0;
    } else{
        rmno = wxAtoi(rmrec->GetValue());
    }

    wxDateTime date = calend->GetDate();

    month  = date.GetMonthName(date.GetMonth());
    day = date.GetDay();

    year = date.GetYear();

    return true;
}

bool BankDialog::checkvalues(){

 if (name.IsEmpty() || trans_id.IsEmpty() || rent_amount == 0 || 
      plotnametext.IsEmpty()|| zId_Num ==0 || rmno == 0){
        
      wxMessageBox(wxT("Ensure all values\nare in the fields"), wxT("ERROR"), wxICON_ERROR);
      return false;

  }else{

      return true;

  }

}

void BankDialog::onclose(wxCommandEvent& event){

    Close(true);

}

void BankDialog::onsave(wxCommandEvent& event){

    TransferDataFromWindow();


    if (checkvalues()){

        std::string valueid = std::to_string(zId_Num);

        std::string xytext = plot.get_Id("SELECT EmpId FROM Tenant WHERE EmpId = ", valueid);

        if (xytext.empty()){

            wxMessageBox(wxT("No such user"), wxT("Error"), wxICON_ERROR);

        }else{

            sqltxt = "INSERT INTO payment(payment_id, Room_No, emp_id, Year, Month, Amount, Balance, Status) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
            
            	rs = sqlite3_open("fileowner.db", &db);
	            rs = sqlite3_prepare_v2(db, "PRAGMA foreign_keys = ON", -1, &stmt, &tail);
	            rs = sqlite3_prepare_v2(db, sqltxt.c_str(), -1, &stmt, &tail);

            if (rs != SQLITE_OK) {
              std::cerr << "Cant insert values to rows " << std::endl;
              sqlite3_free(MError);
            }

            sqlite3_bind_text(stmt, 1, std::string(trans_id.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, rmno);
            sqlite3_bind_int(stmt, 3, zId_Num);
            sqlite3_bind_int(stmt, 4, year);
            sqlite3_bind_text(stmt, 5, std::string(month.mb_str()).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 6, rent_amount);
            sqlite3_bind_int(stmt, 7, rent_bal);
            sqlite3_bind_text(stmt,  8, "Paid", -1, SQLITE_TRANSIENT);

            rs = sqlite3_step(stmt);
            rs = sqlite3_finalize(stmt);
            sqlite3_close(db);   

            Close(true);       

        }
    } else{
        //Do nothing
    }
}

/*********************************************************************************************************************/
// reate a small sqlite database, 
void create_login(){

    sqlite3 *db;
    int rs;
    char* messaggeError;

    std::string sql;

    rs = sqlite3_open_v2("deta.db", &db, SQLITE_OPEN_CREATE | 
                            SQLITE_OPEN_READWRITE, NULL);
    
    if( rs  ){
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        // Close the connection
        sqlite3_close(db);
    }

    sql = "CREATE TABLE IF NOT EXISTS deta ("  \
      "username             TEXT  PRIMARY KEY NOT NULL," \
      "password             TEXT              NOT NULL," \
      "surname              TEXT              NOT NULL," \
      "name                 TEXT              NOT NULL," \
      "phone                TEXT              NOT NULL," \
      "location             TEXT              NOT NULL," \
      "Agentname            TEXT              NOT NULL," \
      "Email                TEXT              NOT NULL," \
      "Website              TEXT              NOT NULL);";


    rs = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);

    if (rs != SQLITE_OK) {
        std::cerr << "Error Creating Table " << std::endl;
        sqlite3_free(messaggeError);
    }
    else{
        
        std::cout << "Table created Successfully" << std::endl;
        //sqlite3_close(db);
        
    }
}

// The below function generates password hashing 
//SHA-256 is the most popular hash function in the SHA-2 family.
// It provides 128 bits of security for digital signatures and hash-only 
//applications
std::string sha256(const std::string str){

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;

    for(int i=0; i < SHA256_DIGEST_LENGTH; i++){

        ss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
    }

    return ss.str();
}

std::string convertToString(const char* a)
{
    std::string s1(a);
    return a;
}

