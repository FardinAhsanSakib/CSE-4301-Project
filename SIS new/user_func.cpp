#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include "user_func.h"
#include <SQLAPI.h>
#include <ora7API.h>
#include <oraAPI.h>
#include "title.h"
#include "get_time.h"
#include<string>
#include<vector>
#include "student.h"
#include "teacher.h"
#include "admin.h"


using namespace std;

int user_func::user_admin(){
    clrscr();
	title();
	int _id;
	cout<<"\tLogin type : Administrator"<<endl;
    cout<<"\n\tEnter admin id           : ";
	cin>>_id;
    fflush(stdin);
    cout<<"\n\tEnter admin password     : ";
	int i=0;
	char a;
	string pass;
    while (1) {
        a = _getch();
        if (a == 8) continue;
        if (a == 13) break;
        cout << "*";
        pass += a;
    }
    string true_pass=check_admin(_id);
    if(pass!=true_pass){
        cout<<"\n\tInvalid Password or Admin ID ... ";
		cin.get();
		return -1;
    }
    int _idh;
    int _courseh;
    string b;
    while(1){
         clrscr();
        title();

        cout<<"\tLogin type : Administrator  ["<<_id<<"]"<<endl;
        cout<<"\t\tMenu"<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        cout<<"\t\t1 : Admit student\n\t\t2 : Remove Student\n\t\t3 : Add Teacher\n\t\t4 : Remove Teacher\n\t\t5 : List Students\n\t\t6 : Add Department";
        cout<<"\n\t\t7 : View student attendance\n\t\t8 : View student marks \n\t\t9 : Notifications \n\t\t10: Update Course Information  \n\t\t11: Update Students semester";
        cout<<  "\n\t\t12: Show Admin Info  \n\t\t13: Exit"<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        cout<<"\n\tEnter your choice  : ";
        int choice;
        cin>>choice;
        char s[5];
        switch(choice){
            case 1 : clrscr();
		   			admitStudent();
                    break;
            case 2 : clrscr();
                    removeStudent();
                    break;
            case 3 :clrscr();
                    addTeacher()
                    break;
            case 4 :clrscr();
                    removeTeacher()
                    break;
            case 5 :clrscr();
		   			listStudent();
                    	break;
            case 6 :clrscr();
		   			addDepartment();
                    break;
            case 7 :clrscr();
                    cout<<"\n\tEnter the student ID : "; cin>>_idh;
                     cout<<"\n\tEnter the course ID : "; cin>>_courseh;
		   			showAttendence(_idh,_courseh);
                    break;
            case 8 :clrscr();
		   			cout<<"\n\tEnter the student ID : "; cin>>_idh;
                    cout<<"\n\tEnter the course ID : "; cin>>_courseh;
                    showMarks(_idh,_courseh);
                    break;
            case 9 :clrscr();
		   		   	Notification();
                    break;
            case 10 :clrscr();
		   		   	 update_subjects_info();
                    break;
            case 11 :clrscr();
                    update_students_semester();
                    break;
            case 12 :clrscr();
		   		   showprofile();
		   		   		break;

            case 13 :cout<<"Logging out...["<<_id<<"]";
		   			Sleep(1000);
                    	return 0;
             default : cout<<"Select valid choice : ";
					Sleep(1000);



        }
	}

}

int user_func::user_student(){
    clrscr();
    title();
    int _id;
    cout<<"\tLogin type : Student."<<endl;
	cout<<endl<<"\tEnter your student ID : ";
    cin>>_id;
    fflush(stdin);
    cout<<"\n\tEnter your password     : ";
	int i=0;
	char a;
	string pass;
	int _idh;
    int _courseh;
    while (1) {
        a = _getch();
        if (a == 8) continue;
        if (a == 13) break;
        cout << "*";
        pass += a;
    }
    string true_pass=check_student(_id);
    if(pass!=true_pass){
        cout<<"\n\tInvalid Password or Student ID ... ";
		cin.get();
		return -1;
    }
       while(1) {
        clrscr();
		title();
		cout<<"\tLogin type : Student  ["<<_id<<"]"<<endl;
       	cout<<"\t\tMenu"<<endl;
       	cout<<"\t\t1 : View profile\n\t\t2 : View attendence\n\t\t3 : View marks\n\t\t4 : Exit"<<endl;
       	cout<<"\tEnter your choice  : ";
       	cin>>choice;
       	switch(choice){
           case 1 : fflush(stdin);
		   			clrscr();
		   			showProfile(_id);
                    break;
           case 2 : fflush(stdin);
                    clrscr();
                     cout<<"\n\tEnter the course ID : "; cin>>_courseh;
		   			showAttendence(_id,_courseh);
                     break;
           case 3 : fflush(stdin);
		   			clrscr();
                    cout<<"\n\tEnter the course ID : "; cin>>_courseh;
                    showMarks(_id,_courseh);
                    break;
		   case 4 : cout<<"Logging out...["<<_id<<"]";
		   			Sleep(1000);
		   			return SUCCESS;
            default : cout<<"Select valid choice : ";
		   		Sleep(1000);
       }
    }

}
int user_func::user_teacher(){
    clrscr();
    title();
    int _id;
    cout<<"\tLogin type : Teacher"<<endl;
    fflush(stdin);
    cout<<endl<<"\tEnter teacher id      : ";
    cin>>_id;
    fflush(stdin);
    cout<<"\tEnter the password  : ";
    int i=0;
	char a;
	string pass;
	int _idh;
    int _courseh;
    while (1) {
        a = _getch();
        if (a == 8) continue;
        if (a == 13) break;
        cout << "*";
        pass += a;
    }
    string true_pass=check_student(_id);
    if(pass!=true_pass){
        cout<<"\n\tInvalid Password or Teacher ID ... ";
		cin.get();
		return -1;
    }
        while(1){
        clrscr();
        title();
        cout<<"\tLogin type : Teacher  ["<<_id<<"]"<<endl;
        cout<<"\t\tMenu"<<endl;
        cout<<"\t\t1 : Manage attendence\n\t\t2 : Manage marks\n\t\t3 : Exit"<<endl;
        cout<<"\n\tEnter your choice  : ";
        int choice;
        int f;
        cin>>choice;
        switch(choice){
            case 1 : fflush(stdin);
                    clrscr();
                    cout<<"\n\tEnter the course ID : "; cin>>_courseh;
                    f=check_edit(_id,_courseh);
                    if(f==1){
                         manageAttendence(int _id,int _courseh);
                    }
                    else if(f==0){
                         cout<<"You are not allowed"<<endl;
                    }
                    break;

           case 2 : fflush(stdin);
                    clrscr();
                    cout<<"\n\tEnter the course ID : "; cin>>_courseh;
                    f=check_edit(_id,_courseh);
                    if(f==1){
                         manageMarks(int _id,int _courseh);
                    }
                    else if(f==0){
                         cout<<"You are not allowed"<<endl;
                    }
                    break;
           case 3 : cout<<"Logging out...["<<_id<<"]";
		   			Sleep(1000);
                    return SUCCESS;
            default : cout<<"Select valid choice : ";
		  Sleep(1000);
		         }
    }

}

int user_func::setup(){
    title();
	ifstream fp("notification.bin",ios::binary|ios::in);
	if(fp.is_open())
		return 0;
    fp.close();
    ofstream _f("notification.bin",ios::binary|ios::out);
	if(!_f.is_open()) return -1;
	_f.close();
	clrscr();
	title();
	cout<<"\t\tThis is your first installation "<<endl;
	cout<<"\t\tSo you have to make an admin ID"<<endl;
	int ad_id;
	string ad_name;
	string ad_pass;
	string ad_email;
	//admin tempad;
	cout<<"\t\tEnter your admin ID: ";
	cin>>ad_id;
	fflush(stdin);
	cout<<endl<<"\t\tEnter your name: ";
	cin.getline(ad_name,50);
	fflush(stdin);
	cout<<endl<<"\t\tEnter your Email address: ";
	cin>>ad_email;
	fflush(stdin);
	cout<<endl<<"\t\tEnter a password for you: ";
	cin>>ad_pass;
	fflush(stdin);
	cout<<"Press enter to proceed "; cin.get();
	clrscr();
    	SAConnection con; // create connection object

	cout << "adding new admin.......\n";
	try
	{
		// connect to database
		con.Connect(
			"XE",     // database name
			"cpp_proj",   // user name
			"test123",   // password
			SA_Oracle_Client);

		cout << "connected!\n";

		// create a command object
		SACommand cmd(&con, "insert into admin(id, name,password,email) values(:1, :2, :3, :4)");

		// bind input to sql command
		cmd.Param(1).setAsLong() = ad_id;
		cmd.Param(2).setAsString() = ad_name.c_str();// convert from c++ string to c_string
		cmd.Param(3).setAsString() = ad_pass.c_str();
		cmd.Param(4).setAsString() = ad_email.c_str();

		cmd.Execute();
		cout << "admin '" << ad_name << "' successfully added\n";
		//cout << "Default password is: 'hello'\n" << "It has to be changed when logging in for first time\n";
		con.Commit(); // commit on success

		// Disconnect is optional
		// autodisconnect will ocur in destructor if needed
		con.Disconnect();
		cout << "We are disconnected!\n";
	}
	catch (SAException &x)
	{
		// SAConnection::Rollback()
		try
		{
			// on error rollback changes
			cout << "rolling back.....";
			con.Rollback();
		}
		catch (SAException &)
		{
		}
		// print error message
		printf("%s\n", (const char*)x.ErrText());
	}
	Sleep(2000);
	cout<<" : DONE";
	cin.get();
	return 0;

}


