#include "gui_main.h"
#include "frame.h"
#include <wx/display.h>

//#include <wx/msw/wx.rc>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {

    wxDisplay *dp = new wxDisplay();

    wxRect sz = dp->GetGeometry();
    double x, y;

    x = (sz.GetWidth() / 3) * 1.5;
    y = (sz.GetHeight() / 3) * 2;

    xpixel = sz.GetWidth();
    ypixel = sz.GetHeight();


  // FormLogin *formLogin = new FormLogin(wxT("House"), x, y);
    //formLogin->ShowModal();
   // y = formLogin->check_res();
   // formLogin->SetIcon(wxIcon("/home/pita/Videos/allan.png"));
  //  formLogin->ShowModal();
  //  bool loginInfo = formLogin->check_res();

  //  formLogin->Destroy();

  //  if (loginInfo == true){

        MyFrame *frame = new MyFrame(wxT("Toolbar"), wxDefaultPosition, wxSize(x, y));
        //frame->SetIcon(wxIcon("/home/pita/Videos/allan.png")); // To Set Application Icon
        frame->Show(true);

        SetTopWindow(frame);

        return true;

  //  }else{
   //     return false;
   // }

   /* wxDisplay *dp = new wxDisplay();

    wxRect sz = dp->GetGeometry();

    std::cout << sz.GetHeight() << std::endl;
    std::cout << sz.GetWidth() << std::endl; */
}

