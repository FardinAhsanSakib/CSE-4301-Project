#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include "check_functions.h"

using namespace std;

string check_functions::check_admin(int _id)
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

		// check if admin exists and return password
		// prototype: check_admin(ad_name in varchar2, passwd out varchar2)
		cmd.setCommandText("check_admin");
		cmd.Param("ad_id").setAsLong() = _id; // pass parameters

		cmd.Execute();

		// get the pass from the check procedure if admin exists
		// procedure will return "not found" if admin doesn't exist
		string pass = string(cmd.Param("passwd").asString());

		if (pass == "not found")
		{
			cout << "admin doesn't exist\n";
			con.Disconnect(); // disconnect before return
			return pass;
		}
		else
		{
			con.Disconnect();
			return pass;
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
		return 0;
	}
}

string check_functions::check_teacher(int _id)
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

		// check if admin exists and return password
		// prototype: check_admin(ad_name in varchar2, passwd out varchar2)
		cmd.setCommandText("check_teacher");
		cmd.Param("ad_id").setAsLong() = _id; // pass parameters

		cmd.Execute();

		// get the pass from the check procedure if admin exists
		// procedure will return "not found" if admin doesn't exist
		string pass = string(cmd.Param("passwd").asString());

		if (pass == "not found")
		{
			cout << "teacher doesn't exist\n";
			con.Disconnect(); // disconnect before return
			return pass;
		}
		else
		{
			con.Disconnect();
			return pass;
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
		return 0;
	}
}

string check_functions::check_student(int _id)
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

		// check if admin exists and return password
		// prototype: check_admin(ad_name in varchar2, passwd out varchar2)
		cmd.setCommandText("check_student");
		cmd.Param("ad_id").setAsLong() = _id; // pass parameters

		cmd.Execute();

		// get the pass from the check procedure if admin exists
		// procedure will return "not found" if admin doesn't exist
		string pass = string(cmd.Param("passwd").asString());

		if (pass == "not found")
		{
			cout << "student doesn't exist\n";
			con.Disconnect(); // disconnect before return
			return pass;
		}
		else
		{
			con.Disconnect();
			return pass;
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
		return 0;
	}
}
int check_attendance(int _stuid,int _course,string _b){
    int to_return;
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

		cmd.setCommandText("select attend from marks_attendance where scode= :1 and aca_year= :2 and sid= :3"); // set command for selection
		cmd.Param(1).setAsLong() = _course;
		cmd.Param(2).setAsString() = b.c_str();
		cmd.Param(3).setAsLong() = _stuid;
		cmd.Execute();

		// check if result exists
		bool isResult = cmd.isResultSet();
		if (!isResult)
		{
			cout << "No result exists\n";
			return;
		}
		else
		{
			while (cmd.FetchNext())
			{
				to_return=cmd[1].asLong();
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
    return to_return;
}
int check_functions::check_edit(int _id,int _course)
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

		// check if admin exists and return password
		// prototype: check_admin(ad_name in varchar2, passwd out varchar2)
		cmd.setCommandText("check_edit");
		cmd.Param(1).setAsLong() = _id; // pass parameters
        cmd.Param(2).setAsLong() = _course;
		cmd.Execute();

		// get the pass from the check procedure if admin exists
		// procedure will return "not found" if admin doesn't exist
		string pass = string(cmd.Param("passwd").asString());

		if (pass == "not found")
		{
			con.Disconnect(); // disconnect before return
			return 0;
		}
		else
		{
			con.Disconnect();
			return 1;
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
		return 0;
	}
}

