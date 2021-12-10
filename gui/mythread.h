#ifndef MYTHREAD_H
#define MYTHREAD_H

    #include <iostream>
    #include <wx/thread.h>

    class Mythread : public wxThread
    {
        public:
            Mythread(int *flag);
            //virtual ~Mythread();

            // thread execution starts here
            virtual void *Entry();

        private:
            int flag;

    };
#endif
