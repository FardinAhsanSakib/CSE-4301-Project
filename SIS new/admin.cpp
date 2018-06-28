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
#include<vector>

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

 void admin::update_subjects_info(){
    clrscr();
    title();
    fflush(stdin);
    cout<<"Choose one"<<endl;
	fflush(stdin);
    cout<<"1.Adding new course \n2.Updating info of existing course"<<endl;
    int a;
    cin>>a;
    if(a==1){
        int b;
        cout<<"\n # How much course do you want to add?       : "; cin>>b;
         clrscr();
        title();
        fflush(stdin);
        for(int k=0;k<b;k++){
        int c_id,sem_id,dep_id,ins_id,credit;
        string c_name;
        cout<<"\n # Please enter course ID(should be unique)   : "; cin>>c_id;
        fflush(stdin);
        cout<<"\n # Please enter full name of the course       : "; cin.getline(c_name,50);
        fflush(stdin);
        cout<<"\n # Please enter department id                 : "; cin>>dep_id;
        fflush(stdin);
        cout<<"\n # Please enter semester                      : "; cin>>sem_id;
        fflush(stdin);
        cout<<"\n # Please enter its instructor id             : "; cin>>ins_id;
        fflush(stdin);
        cout<<"\n # Please enter course credit                 : "; cin>>credit;
        fflush(stdin);
        SAConnection con; // create connection object

        cout << "adding course.......\n";
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
		SACommand cmd(&con, "insert into subject(scode, name,semester,dept,instid,credit) values(:1, :2, :3, :4, :5, :6)");

		// bind input to sql command
		cmd.Param(1).setAsLong() = c_id;
		cmd.Param(2).setAsString() = c_name.c_str();// convert from c++ string to c_string
		cmd.Param(3).setAsLong() = sem_id;
		cmd.Param(4).setAsLong() = dep_id;
		cmd.Param(5).setAsLong() = ins_id;
		cmd.Param(6).setAsLong() = credit;

		cmd.Execute();
		cout << "course '" << c_name << "' successfully added\n";
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
    }


    if(a==2){
        int b;
        cout<<"\n # How much course do you want to edit?       : "; cin>>b;
        clrscr();
        title();
        fflush(stdin);
        for(int k=0;k<b;k++){
        int c_id,sem_id,dep_id,ins_id,credit;
        string c_name;
        cout<<"\n # Please enter course ID(should be unique)   : "; cin>>c_id;
        fflush(stdin);
        cout<<"\n # Please enter full name of the course       : "; cin.getline(c_name,50);
        fflush(stdin);
        cout<<"\n # Please enter department id                 : "; cin>>dep_id;
        fflush(stdin);
        cout<<"\n # Please enter semester                      : "; cin>>sem_id;
        fflush(stdin);
        cout<<"\n # Please enter its instructor id             : "; cin>>ins_id;
        fflush(stdin);
        cout<<"\n # Please enter course credit                 : "; cin>>credit;
        fflush(stdin);
        SAConnection con; // create connection object

        cout << "updating course.......\n";
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
		SACommand cmd(&con, "update subject(scode, name,semester,dept,instid,credit) values(:1, :2, :3, :4, :5, :6)");
		SACommand cmd(&con, "update subject set name= :2,semester= :3,dept= :4,instid= :5,credit= :6 where scode= :1");

		// bind input to sql command
		cmd.Param(1).setAsLong() = c_id;
		cmd.Param(2).setAsString() = c_name.c_str();// convert from c++ string to c_string
		cmd.Param(3).setAsLong() = sem_id;
		cmd.Param(4).setAsLong() = dep_id;
		cmd.Param(5).setAsLong() = ins_id;
		cmd.Param(6).setAsLong() = credit;

		cmd.Execute();
		cout << "course '" << c_name << "' successfully added\n";
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
    }
 }

void admin::update_students_semester(){
    clrscr();
    title();
    fflush(stdin);
    int a,b;
    cout<<"\n # Please enter the department ID of students that you want to edit   : "; cin>>a;
	fflush(stdin);
    cout<<"\n # Please enter the current semester of students that you want to edit: "; cin>>b;
	fflush(stdin);
	vector<int>stid;
	vector<int>subid;
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

		cmd.setCommandText("select * from student where semester= :1 and dept= :2"); // set command for selection
		cmd.Param(1).setAsLong() = b;
		cmd.Param(2).setAsLong() = a;
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
			cout << "\tID\t\t" << "\tNAME\n";
			cout << "---------------\t" << "    " << "\t----------------\n";
			while (cmd.FetchNext())
			{
				cout <<"\t" << cmd[1].asLong() << "\t\t\t" << string(cmd[2].asString()) << "\n";
				cout<< "\t Is he promoted(y/n)?"
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
    cout<<"updating semester of students.........."<<endl;
    b=b+1;
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

		cmd.setCommandText("update student set semester=:1 where id=:2");
		cmd.Param(1).setAsLong() = b;
		cmd.Param(2).setAsLong() = stid[i];

		cmd.Execute();
		cout << "\nsemester updated successfully for "<<stid[i] << "\n";
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
    cout<<"\nupdating courses of students which are gonna offer in new semester.........."<<endl;
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

		cmd.setCommandText("select scode from subject where semester= :1 and dept= :2"); // set command for selection
		cmd.Param(1).setAsLong() = b;
		cmd.Param(2).setAsLong() = a;
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No subject exists\n";
			return;
		}
		else
		{
			while (cmd.FetchNext())
			{

                    int x=cmd[1].asLong();
                    subid.push_back(x);
			}
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
	for(int i=0;i<stid.size();i++){
        for(int j=0;j<subid.size();j++){

            SAConnection con; // create connection object

	//cout << "adding admin.......\n";
	try
	{
		// connect to database
		con.Connect(
			"XE",     // database name
			"cpp_proj",   // user name
			"test123",   // password
			SA_Oracle_Client);

		//cout << "connected!\n";

		// create a command object
		SACommand cmd(&con, "insert into marks_attendance(sid,scode,semester,dept,marks,tot_cls,attend) values(:1, :2, :3, :4, :5, :6, :7)");

		// bind input to sql command
		cmd.Param(1).setAsLong() = stid[i];
		cmd.Param(2).setAsLong() = subid[j];
		cmd.Param(3).setAsLong() = b;
		cmd.Param(4).setAsLong() = a;
		cmd.Param(5).setAsLong() = 0;
		cmd.Param(6).setAsLong() = 0;
		cmd.Param(7).setAsLong() = 0;

		cmd.Execute();
		cout << "student id '" << stid[i] << "for subject code " << subid[j] << "' successfully added\n";
		con.Commit(); // commit on success

		// Disconnect is optional
		// autodisconnect will ocur in destructor if needed
		con.Disconnect();
		//cout << "We are disconnected!\n";
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
}





