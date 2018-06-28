#pragma once
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include<string>

using namespace std;

string check_admin(int );
string check_teacher(int );
string check_student(int );
int check_attendance(int _stuid,int _course,string _b);
int check_edit(int _id,int _course);
