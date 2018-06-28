#pragma once
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<string>

using namespace std;

class admin{
        int admin_id;
        string admin_name;
        string admin_email;
        string password;
public:

     admin();
     admin(int _id,string _name,string _email);
    int get_id();
    string get_name();
    string get_email();
    void addDepartment();
    void addTeacher();
    void admitStudent();
    void removeTeacher();
    void removeStudent();
    void listStudent();
    int Notification();
    void showprofile();
   void update_subjects_info();
    void update_students_semester();
    friend int user_admin();


};
