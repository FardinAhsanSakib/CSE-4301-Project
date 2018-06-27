#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include "teacher.h"
#include <SQLAPI.h>
#include <ora7API.h>
#include <oraAPI.h>
#include "title.h"
#include "get_time.h"
#include<string>
#include<vector>

using namespace std;

teacher::teacher(){
    teacher_id = 0;
	teacher_name = "";
	teacher_email="";
	password = "";
	dept=0;
}

void teacher::manageAttendence(int _id,int _course){
    clrscr();
    title();
    fflush(stdin);
    string b;
    cout<<"\n # Please enter the current semester of students that you want to edit: "; c cin.getline(b,30);
	fflush(stdin);

}
