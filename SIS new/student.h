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

class student{
    int student_id;
    string student_name;
    string student_dob;
    string student_email;
    string password;
    int student_dept;
    int student_semester;
public:

    student();
    void showProfile(int _id);
    void showAttendence(int _id,int _course);
    void showMarks(int _id,int _course);
    void Notification();
    void complaint();
    friend class admin;
    friend class teacher;
};
