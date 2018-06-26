#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include "student.h"
#include <SQLAPI.h>
#include <ora7API.h>
#include <oraAPI.h>
#include "title.h"
#include "get_time.h"
#include<string>
#include<vector>

using namespace std;

student::student(){
    student_id=0;
    student_name="";
    student_dob="";
    student_email="";
    password="";
    student_dept=0;
    student_semester=0;
}

void student::showProfile(int _id){
    clrscr();
    title();

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

		cmd.setCommandText("select * from student where id=:1"); // set command for selection
		cmd.Param(1).setAsLong() = _id;
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No Such Student exists\n";
			return;
		}
		else
		{
			cout<<"Student proifile...."<<endl;
            cout<<endl<<"_______________________________________________________________________________"<<endl;
			while (cmd.FetchNext())
			{
			    cout<<" Name                :"<<string(cmd[2].asString())<<endl;
                cout<<" Student ID          :"<<cmd[1].asLong()<<endl;
                cout<<" Date of birth       :"<<string(cmd[3].asString())<<endl;
                cout<<" Email id            :"<<string(cmd[4].asString())<<endl;
                cout<<" Department          :"<<cmd[7].asLong()<<endl;
                cout<<" Semester            :"<<cmd[6].asLong()<<endl;
			}
			cout << "\n";
			cout<<endl<<"_______________________________________________________________________________"<<endl;
            cout<<"Press any key to exit :";
            cin.get();
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


}

void student::showAttendence(int _id,int _course){
    fflush(stdin);
	clrscr();
	title();
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

		cmd.setCommandText("select ma.scode,ma.tot_cls,ma.attend,su.name from marks_attendance ma,subject su where ma.scode=su.scode and ma.sid=:1 and ma.scode=:2"); // set command for selection
		cmd.Param(1).setAsLong() = _id;
		cmd.Param(2).setAsLong() = _course;
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No Result exists\n";
			return;
		}
		else
		{
			while (cmd.FetchNext())
			{
			    cout<<" Student ID          : "<<_id<<endl;
			    cout<<" Course code         : "<<cmd[1].asLong()<<endl;
			    cout<<" Course Name         : "<<string(cmd[4].asString())<<endl;
			    cout<<" Total Class         : "<<cmd[2].asLong()<<endl;
			    cout<<" Total Attendance    : "<<cmd[3].asLong()<<endl;
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

}

void student::showMarks(int _id,int _course){
    fflush(stdin);
	clrscr();
	title();
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

		cmd.setCommandText("select ma.scode,ma.marks,su.name from marks_attendance ma,subject su where ma.scode=su.scode and ma.sid=:1 and ma.scode=:2"); // set command for selection
		cmd.Param(1).setAsLong() = _id;
		cmd.Param(2).setAsLong() = _course;
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No Result exists\n";
			return;
		}
		else
		{
			while (cmd.FetchNext())
			{
			    cout<<" Student ID          : "<<_id<<endl;
			    cout<<" Course code         : "<<cmd[1].asLong()<<endl;
			    cout<<" Course Name         : "<<string(cmd[3].asString())<<endl;
			    cout<<" Mark in this course : "<<cmd[2].asLong()<<endl;
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



}
