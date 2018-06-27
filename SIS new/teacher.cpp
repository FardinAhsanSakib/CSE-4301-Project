#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include "teacher.h"
#include <SQLAPI.h>
#include <ora7API.h>
#include <oraAPI.h>
#include "title.h"
#include "get_time.h"
#include<string>
#include<vector>

using namespace std;

teacher::teacher(){
    teacher_id = 0;
	teacher_name = "";
	teacher_email="";
	password = "";
	dept=0;
}

void teacher::manageAttendence(int _id,int _course){
    clrscr();
    title();
    fflush(stdin);
    string b;
    cout<<"\n # Please enter the academic year of students that you want to edit: "; cin.getline(b,30);
	fflush(stdin);
    vector<int>stid;
	vector<int>subid;
	int tot_cls;
    SAConnection con;

	try
	{
		// connect to database
		con.Connect(
			"XE",     // database name
			"cpp_proj",   // user name
			"test123",   // password
			SA_Oracle_Client);
		SACommand cmd(&con);

		cmd.setCommandText("select sid,scode,tot_cls from marks_attendance where scode= :1 and aca_year= :2"); // set command for selection
		cmd.Param(1).setAsLong() = _course;
		cmd.Param(2).setAsString() = b.c_str();
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No student exists\n";
			return;
		}
		else
		{
			cout << "\tID\t\t\n";
			cout << "---------------\t" << "    " << "\t----------------\n";
			while (cmd.FetchNext())
			{
				cout <<"\t" << cmd[1].asLong() << "\n";
				tot_cls=cmd[3].asLong();
				cout<< "\t Is he present(y/n)?"
				fflush(stdin);
				char z;
				cin>>z;
				if(z=='Y'|| z=='y'){
                    int x=cmd[1].asLong();
                    stid.push_back(x);
				}
			}
			cout << "\n";
		}
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

	cout<<"\nUpdating total class taken for this course"<<endl;
	tot_cls=tot_cls+1;

    SAConnection con;
	try
	{
		// connect to database
		con.Connect(
			"XE",     // database name
			"cpp_proj",   // user name
			"test123",   // password
			SA_Oracle_Client);
		SACommand cmd(&con);

		cmd.setCommandText("update marks_attendance set tot_cls=:1 where scode= :2 and ay= :3");
		cmd.Param(1).setAsLong() = tot_cls;
		cmd.Param(2).setAsLong() = _course;
		cmd.Param(3).setAsString() = b.c_str();

		cmd.Execute();
		cout << "\nTotal class updated successfully for "<<_course<<"in the academic year"<<b<< "\n";
		con.Commit();
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
    cout<<"\nUpdating the attendance for this course"<<endl;
    for(int i=0;i<stid.size();i++){
    int attend=check_attendance(int stid[i],int _course,string b);
    SAConnection con;
	try
	{

		// connect to database
		con.Connect(
			"XE",     // database name
			"cpp_proj",   // user name
			"test123",   // password
			SA_Oracle_Client);
		SACommand cmd(&con);

		cmd.setCommandText("update marks_attendance set attend=:1 where scode= :2 and ay= :3 and sid= :4");
		cmd.Param(1).setAsLong() = attend+1;
		cmd.Param(2).setAsLong() = _course;
		cmd.Param(3).setAsString() = b.c_str();
		cmd.Param(4).setAsLong() = stid[i];

		cmd.Execute();
		cout << "\nAttendance updated successfully for "<<stid[i] << "\n";
		con.Commit();
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


    }
}
void teacher::manageMarks(int _id,int _course){
    clrscr();
    title();
    fflush(stdin);
    string b;
    cout<<"\n # Please enter the academic year of students that you want to edit: "; cin.getline(b,30);
	fflush(stdin);
    vector<int>stid;
	vector<int>marks;
	int tot_cls;
    SAConnection con;

	try
	{
		// connect to database
		con.Connect(
			"XE",     // database name
			"cpp_proj",   // user name
			"test123",   // password
			SA_Oracle_Client);
		SACommand cmd(&con);

		cmd.setCommandText("select sid from marks_attendance where scode= :1 and aca_year= :2"); // set command for selection
		cmd.Param(1).setAsLong() = _course;
		cmd.Param(2).setAsString() = b.c_str();
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No student exists\n";
			return;
		}
		else
		{
			cout << "\tID\t\t\n";
			cout << "---------------\t\n";
			while (cmd.FetchNext())
			{
				cout <<"\t" << cmd[1].asLong() <<  "\n";
				cout<< "\t Input his marks";
				fflush(stdin);
				int z;
				cin>>z;
                int x=cmd[1].asLong();
                stid.push_back(x);
                marks.push_back(z);
			}
			cout << "\n";
		}
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
	cout<<"updating........"<<endl;
    for(int i=0;i<stid.size();i++){
        SAConnection con;
	try
	{
		// connect to database
		con.Connect(
			"XE",     // database name
			"cpp_proj",   // user name
			"test123",   // password
			SA_Oracle_Client);
		SACommand cmd(&con);

		cmd.setCommandText("update marks_attendance set marks=:1 where sid=:2 and scode= :3 and aca_year= :4");
		cmd.Param(1).setAsLong() = marks[i];
		cmd.Param(2).setAsLong() = stid[i];
		cmd.Param(3).setAsLong() = _course;
		cmd.Param(4).setAsString() = b.c_str();

		cmd.Execute();
		cout << "\nMarks updated successfully for "<<stid[i] << "\n";
		con.Commit();
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


    }

}

