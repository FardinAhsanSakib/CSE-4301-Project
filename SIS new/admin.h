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
    void viewMarks();
    void viewAttendence();
    void manageAttendence();
    void listStudent();
    int Notification();
    int complaint();
    int timetable();
    void showProfile();
    int update_teacher_info(char *);
    int update_subjects_info();
    int update_students_semester(char *);
    friend int user_admin();


};
