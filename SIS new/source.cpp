#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<string>
#include <SQLAPI.h>
#include <ora7API.h>
#include <oraAPI.h>
#include "admin.h"
#include "check_functions"
#include "get_time.h"
#include "student.h"
#include "teacher.h"
#include "title.h"
#include "user_func.h"
#define F_NOT_FOUND -1
#define USN_NOT_FOUND -2
#define SUCCESS 0;
//#difine ADM_PASS "DUNNO"
using namespace std;

int main(){
    setdepartment();
    setsubject();
    //cout<<subject_info[4][3][1]<<endl;
    if(setup()) {
		cout<<"Files are missing and unable to create new files...\n Please try again..."; Sleep(2000);
		exit(1);
	}
    while(1){
        clrscr();
        title();
        cout<<"\n\t\tLogin Option for you"<<endl;
        cout<<"\t\t 1 : Student "<<endl;
        cout<<"\t\t 2 : Teacher   "<<endl;
        cout<<"\t\t 3 : Admin "<<endl;
        cout<<"\t\t 4 : Exit"<<endl;
        cout<<endl<<"\t\tEnter your choice : ";
        static int error;
        int your_choice;
        cin >> your_choice;
        switch(your_choice){
            case 1 : error=0;
					while(error<5) {  //Students are allowed to attemp for maximum 5 times
					        if(user_student())
							error++;
                  			else break;
								   }
					if(error>4)
							cout<<" Authentication failed...";
				 			cin.get();
					break;
            case 2 :error=0;
					while(error<5) {
                            if(user_teacher())
							error++;
                  			else break;
								   }
                    if(error>4)
                        cout<<" Authentication failed...";
                    cin.get();
					break;
            case 3 :user_admin();
                	break;
            case 4 :cout<<"Terminating..."; Sleep(1000);
                    exit(0);
            default:cout <<"Invalid choice : ";
                    Sleep(1000);
                    cin.get();

        }
    }



}

