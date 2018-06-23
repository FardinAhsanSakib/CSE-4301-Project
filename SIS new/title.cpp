#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<string>
#include"title.h"

using namespace std;


void title::title(){
    clrscr();
	cout<<"==============================================================================="<<endl;
	cout<<"**************           Student Information System           *****************"<<endl;
	cout<<"**************      Islamic University of Technology (IUT)    *****************"<<endl;
	cout<<"==============================================================================="<<endl;
}
void title::clrscr(){
    system("cls");
}
