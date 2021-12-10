#include "listviewbox.h"


MyListCtrl::MyListCtrl(wxWindow *parent,
                const wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style)
            : wxListCtrl(parent, id, pos, size, style)
{
    m_updated = -1;
    

    #ifdef __POCKETPC__
                EnableContextMenu();
    #endif

    this->AppendColumn(wxT("Plot name"));
    this->AppendColumn(wxT("Location"));
    this->AppendColumn(wxT("Rooms"));

   // wxStopWatch sw;

    this->Show();

    this->SetTextColour(*wxBLUE);

    this->SetColumnWidth( 0, 160);
    this->SetColumnWidth( 1, 160);
    this->SetColumnWidth( 2, 90);

    populateview();

   // Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MyListCtrl::leftclick, this , wxID_ANY);
}

void MyListCtrl::get(){

    if (arr.empty()){

       // arr = plot.get_owner_name();
       populateview();

    }else{
        arr.clear();
        populateview();

    }
}

void MyListCtrl::populateview(){

    arr = plot.get_plot();

    RefreshAfterUpdate();
}


wxString MyListCtrl::OnGetItemText(long index, long column) const {

    switch(column){
        case 0: return arr[index].plotname;
            break;
        case 1: return arr[index].location;
            break;
        case 2: return std::to_string(arr[index].num_rooms);
            break;
            default: return "";
    
    }

}

void MyListCtrl::RefreshAfterUpdate(){
    SetItemCount(arr.size());
    Refresh();
}


/***************************************************************************************************************************/

NormaList::NormaList(wxWindow *parent,
                const wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style)
            : wxListCtrl(parent, id, pos, size, style)
{
    #ifdef __POCKETPC__
                EnableContextMenu();
    #endif

    this->AppendColumn(wxT("Room No"));
    this->AppendColumn(wxT("Type "));
    this->AppendColumn(wxT("Occupied "));
    this->AppendColumn(wxT("Tenant name "));
    this->AppendColumn(wxT("Phone number "));
    this->AppendColumn(wxT("Status "));
   // wxStopWatch sw;

    this->Show();

    this->SetTextColour(*wxBLUE);

    double a, b, c, d, e, f;
    double res = (xpixel /3) * 2;

    a = res * 0.1;
    b = res * 0.2;
    c = res * 0.08;
    d = res * 0.3;
    e = res * 0.2;
    f = res * 0.99;

    this->SetColumnWidth( 0, a);
    this->SetColumnWidth( 1, b);
    this->SetColumnWidth( 2, c);
    this->SetColumnWidth( 3, d);
    this->SetColumnWidth( 4, e);
    this->SetColumnWidth( 5, f);


   // populateview();
}

void NormaList::set_num_rooms(){
    if (showflag == 1){
      for (int x =1; x <=num_of_rooms; x++){
           num_room.push_back(x);
        }
   }
}

void NormaList::populateview(std::string pltid){

    std::tm *date = get_curr_date();

    std::string all_month[] = {"January", "February", "March",
                       "April", "May", "June",
                       "July", "August", "September",
                       "October", "November", "December"
                      };

    int yr = date->tm_year+1900;
    std::string month = all_month[date->tm_mon];


   if (num_room.empty()){

        set_num_rooms();
        plot.populate_Tenant(num_of_rooms);
       // plot.get_tenant_info(pltid);
        RefreshAfterUpdate();

   } else {

      num_room.clear();
      plot.delete_struct_arr();
      set_num_rooms();
      plot.populate_Tenant(num_of_rooms);
      plot.get_tenant_info(pltid);
      plot.get_tenant_status(yr, month, pltid);
      RefreshAfterUpdate();
      
   }
   showflag =0;
}

void NormaList::RefreshAfterUpdate(){
    SetItemCount(num_room.size());
    Refresh();
}

void NormaList::clear_list(){

    plot.ten.arr.clear();
    plot.ten.num.clear();
    plot.ten.ocp.clear();
    plot.ten.nm.clear();
    plot.ten.phone.clear();
    plot.ten.stats.clear();
    
    RefreshAfterUpdate();

}

wxString NormaList::OnGetItemText(long index, long column) const {

    switch (column)
    {
    case 0: return std::to_string(plot.ten.arr[index]);
        break;
    case 1: return plot.ten.num[index];
        break;

    case 2: return plot.ten.ocp[index];
        break;
    
    case 3: return plot.ten.nm[index];
        break;

    case 4: return plot.ten.phone[index];
        break;

    case 5: return plot.ten.stats[index];
    
    default: return " ";
        break;
    }
}
