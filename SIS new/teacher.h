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

class teacher{
       int teacher_id;
        string teacher_name;
        string teacher_email;
        string password;
        int dept;
public:
        teacher();
        void manageAttendence(int _id,int _course);
        void manageMarks(int _id,int _course);
         friend class admin;

};
