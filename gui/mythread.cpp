#include "mythread.h"

Mythread::Mythread(int *flag) : wxThread(){
    flag = flag;
}

wxThread::ExitCode Mythread::Entry(){

    if (flag == 1){
        
        for(int x=0; x < 15 ; x++){

            std::cout << "at .... " << flag << std::endl;
       }
    }

    return NULL;
}

