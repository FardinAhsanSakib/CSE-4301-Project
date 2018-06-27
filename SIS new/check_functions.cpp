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

