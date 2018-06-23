#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include "admin.h"
#include <SQLAPI.h>
#include <ora7API.h>
#include <oraAPI.h>
#include "title.h"
#include "get_time.h"
#include<string>

using namespace std;

admin::admin()
{
	admin_id = 0;
	admin_name = "";
	admin_email="";
	password = "";
}

admin(int _id,string _name,string _email){
    admin_id=_id;
    admin_name=_name;
    admin_email=_email;
    password="";

}

int admin::get_id()
{
	return admin_id;
}

string admin::get_name()
{
	return admin_name;
}

string get_email(){
    return admin_email;
}

void admin::addDepartment(){
    clrscr();
    title();
    int did;
    string dname;
     cout<<" Please enter the following fields...[all fields are mandatory]"<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n Enter department id                            : "; cin>>did;
	fflush(stdin);
	cout<<"\n Enter department name                          : "; cin.getline(dname,30);
	fflush(stdin);
    cout<<endl<<"_______________________________________________________________________________"<<endl;
    cout<<"Press enter to proceed "; cin.get();

    SAConnection con; // create connection object

	cout << "adding department.......\n";
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
		SACommand cmd(&con, "insert into department(id, name) values(:1, :2)");

		// bind input to sql command
		cmd.Param(1).setAsLong() = did;
		cmd.Param(2).setAsString() = dname.c_str();// convert from c++ string to c_string

		cmd.Execute();
		cout << "department '" << dname << "' successfully added\n";
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

}

void admin::addTeacher()
{
    clrscr();
    title();
    int tid;
    string tname;
    string tpass;
    string temail;
    int tdept;
    cout<<" Please enter the following fields...[all fields are mandatory]"<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n Enter teacher id                            : "; cin>>tid;
	string pass = check_teacher(tid);
	if (!(pass == "not found")){
        cout<<"\nThis id is used,try again"<<endl;
        return 0;
	}
	fflush(stdin);
	cout<<"\n Enter teacher name                          : "; cin.getline(tname,30);
	fflush(stdin);
	cout<<"\n Enter a password for this teacher           : "; cin>>tpass;
	fflush(stdin);
	cout<<"\n Enter the mail id                           : "; cin>>temail;
	cout<<"\n Enter teacher's department code (1.MCE, 2.EEE, 3.TVE, 4.CSE, 5.CEE,6.SWE,7.BTM) : "; cin>>tdept;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
    cout<<"Press enter to proceed "; cin.get();

	SAConnection con; // create connection object

	cout << "adding teacher.......\n";
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
		SACommand cmd(&con, "insert into teacher(id, name,password,email,dept) values(:1, :2, :3, :4, :5)");

		// bind input to sql command
		cmd.Param(1).setAsLong() = tid;
		cmd.Param(2).setAsString() = tname.c_str();// convert from c++ string to c_string
		cmd.Param(3).setAsString() = tpass.c_str();
		cmd.Param(4).setAsString() = temail.c_str();
		cmd.Param(5).setAsLong() = tdept;

		cmd.Execute();
		cout << "teacher '" << tname << "' successfully added\n";
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
}

void admin::admitStudent(){
    clrscr();
    title();
    int sid;
    string sname;
    string sdob;
    string spass;
    string semail;
    int ssem;
    int sdept;
    cout<<"Please enter the following fields...[all fields are mandatory]"<<endl;
	fflush(stdin);
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n # Please enter student id               : "; cin>>sid;
	string pass = check_student(sid);
	if (!(pass == "not found")){
        cout<<"\nThis id is used,try again"<<endl;
        return 0;
	}
	fflush(stdin);
	cout<<"\n # Please enter full name of the student : "; cin.getline(sname,30);
	fflush(stdin);
	cout<<"\n # Please enter date of birth            : "; cin>>sdob;
	fflush(stdin);
	cout<<"\n # Please enter email id of the student  : "; cin>>semail;
	fflush(stdin);
	cout<<"\n # Please enter a password for the student: "; cin>>spass;
	fflush(stdin);
	cout<<"\n # Please enter which semester he is in    : "; cin>>ssem;
	fflush(stdin);
	cout<<"\n Enter teacher's department code (1.MCE, 2.EEE, 3.TVE, 4.CSE, 5.CEE,6.SWE,7.BTM) : "; cin>>sdept;
	fflush(stdin);
	cout<<"\n Press enter to proceed ";
	cin.get();
	SAConnection con; // create connection object

	cout << "adding student.......\n";
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
		SACommand cmd(&con, "insert into student(id, name,dob,email,password,semester,dept) values(:1, :2, :3, :4, :5, :6, :7)");

		// bind input to sql command
		cmd.Param(1).setAsLong() = sid;
		cmd.Param(2).setAsString() = sname.c_str();// convert from c++ string to c_string
		cmd.Param(3).setAsString() = sdob.c_str();
		cmd.Param(4).setAsString() = semail.c_str();
		cmd.Param(5).setAsString() = spass.c_str();
		cmd.Param(6).setAsLong() = ssem;
		cmd.Param(7).setAsLong() = sdept;

		cmd.Execute();
		cout << "student '" << sname << "' successfully added\n";
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



}

void admin::removeTeacher(){
    clrscr();
    title();
    int del_id;
	cout << "Enter ID of teacher to delete: ";
	cin >> del_id;

	string pass = check_teacher(del_id);
	if (!(pass == "not found"))
	{
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

			// delete teacher
			cmd.setCommandText("delete from teacher where id=:1");
			cmd.Param(1).setAsLong() = del_id;
			cmd.Execute();
			cout << "Teacher having id '" << del_id << "' deleted successfully";
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
		con.Disconnect();
	}

}

void admin::removeStudent(){
    clrscr();
    title();
    int del_id;
	cout << "Enter ID of student to delete: ";
	cin >> del_id;

	string pass = check_student(del_id);
	if (!(pass == "not found"))
	{
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

			// delete teacher
			cmd.setCommandText("delete from student where id=:1");
			cmd.Param(1).setAsLong() = del_id;
			cmd.Execute();
			cout << "Student having id '" << del_id << "' deleted successfully";
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
		con.Disconnect();
	}

}

void admin::listStudent(){
    clrscr();
    title();
    fflush(stdin);
    int sem_id;
    int dept_id;
    cout <<"Enter Semester and Department id to show student list "<<endl;
	cout << "Semester: ";
	fflush(stdin);
	cin >> sem_id;
	cout<<endl;
	fflush(stdin);
	cout<<"Department Id: ";
	cin>> dept_id;
	cout<<"\n Press enter to proceed ";
	cin.get();

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

		cmd.setCommandText("select * from student where semester=:1 and dept=:2 order by id"); // set command for selection
		cmd.Param(1).setAsLong() = sem_id;
		cmd.Param(2).setAsLong() = dept_id;
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No Student exists\n";
			return;
		}
		else
		{
			cout << "\tID\t\t" << "\tNAME\n";
			cout << "---------------\t" << "    " << "\t----------------\n";
			while (cmd.FetchNext())
			{
				cout <<"\t" << cmd[1].asLong() << "\t\t\t" << string(cmd[2].asString()) << "\n";
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











void admin::viewMarks(){

}
void admin::viewAttendence(){

}
void admin::manageAttendence(){

}




