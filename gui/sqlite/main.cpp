#include "create.h"
#include <thread>

int main()
{
    Table *one = new Table;
    /*one->create_table();
    one->insert_owner_info();
    one->insert_plot_info();
    one->plotroom();
    one->insert_room();
    one->insert_year();
    one->insert_month();
    one->insert_tenant();*/


    

    std::string name = one->get_owner_name();
    std::cout << name << std::endl;
    delete one;

}