#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<string>
#define F_NOT_FOUND -1
#define USN_NOT_FOUND -2
#define SUCCESS 0;
//#difine ADM_PASS "DUNNO"
using namespace std;
int flag;
inline void clrscr(){
    system("cls");
}
inline void title(){
    clrscr();
	cout<<"==============================================================================="<<endl;
	cout<<"**************           Student Information System           *****************"<<endl;
	cout<<"**************      Islamic University of Technology (IUT)    *****************"<<endl;
	cout<<"==============================================================================="<<endl;
}

void getdate(char *tday){
	time_t tim;
	tim=time(NULL);
	struct tm *d=localtime(&tim);
	sprintf(tday,"%02d/%02d/%d",d->tm_mday,d->tm_mon+1,d->tm_year+1900);
}
string department[8];
void setdepartment(){
   department[1]="Mechanical and Chemical Engineering (MCE)";
    department[2]="Electrical and Electronic Engineering(EEE)";
    department[3]="Technical and Vocational Education(TVE)";
    department[4]="Computer Science and Engineering (CSE)";
    department[5]="Civil and Environmental Engineering(EEE)";
    department[6]="Software Engineering (SWE)";
    department[7]="Business and Technology Management(BTM)";

}
class student;
class staff{
    protected:
        char staff_id[10];
        char staff_name[50];
        char email[30];
    public:
        staff(){
            staff_id[0]=staff_name[0]=email[0]='\0';
        }
        staff(char *id,char *name,char *mail){
            strcpy(staff_id,id);
            strcpy(staff_name,name);
            strcpy(email,mail);
        }
        char* getid(){
            return staff_id;
        }
        int init(char*);
        virtual void showProfile(){
        clrscr();
        title();
        cout<<"Profile...."<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        cout<<" Staff Name      \t :"<<staff_name<<endl;
        cout<<" Staff Id        \t :"<<staff_id<<endl;
        cout<<" Email id        \t :"<<email<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        fflush(stdin);
        cin.get();
        }
};
class admin;
class teacher:public staff{
        char password[10];
        int total_course;
        int course_code[10];
        int dept_id;
public:
        teacher(){
            staff_id[0]=staff_name[0]=email[0]=password[0]='\0';
            total_course=0;
            memset(course_code,0,sizeof(course_code));
            dept_id=0;
        }
        teacher(char *_id,char *_pass,char *_name,char *_email,int _dept_id){
            strcpy(staff_id,_id);
            strcpy(password,_pass);
            strcpy(staff_name,_name);
            strcpy(email,_email);
            dept_id=_dept_id;
        }
        void set_subject(){
            printf("Total course teacher id %s:",staff_id);
            scanf("%d",total_course);
            cout<<endl<<"Input course code(should be consist of 4 digit) "<<endl;
            for(int i=0;i<total_course;i++){
                int a;
                cin>>a;
                course_code[i]=a;

            }

        }
        char* getid(){
				return staff_id;
			}
		 int init(char*);
         int manageAttendence();
         int manageMarks();
         friend class admin;

};
class admin:public staff{
        char password[10];
public:
    int addstaff();
    int admitStudent();
    int removeStaff(char*);
    int removeStudent(char*);
    void viewMarks();
    void viewAttendence();
    int manageAttendence();
    int listStudent();
    int Notification();
    int complaint();
    int timetable();
    void showProfile();
    int update_teacher_info(char *);
    int update_subject();



};
class student{
    int admissionNo;
    char usn[11];
    char name[30];
    char email[30];
    char dob[11];
    struct sub{
        int subject_info[10][20];
    }marks,attendence;
public:
    char pass[10];
    student(){
        admissionNo=-1;
        strcpy(usn,"\0");
        strcpy(name,"\0");
        strcpy(email,"\0");
        strcpy(dob,"\0");
        memset(marks.subject_info,-1,sizeof(marks.subject_info));
        memset(attendence.subject_info,0,sizeof(attendence.subject_info));
    }
     int init(char*);
    void showProfile();
    void showAttendence();
    void showMarks();
    int Notification();
    int complaint();
    int paper();
    int timetable();
    friend class admin;
    friend class teacher;
    void operator++(int);
};
int student::init(char *u){
    bool flag=false;
    ifstream readfile("student.bin",ios::binary|ios::in);
     if(!readfile.is_open()){
              return F_NOT_FOUND;
    }
    student temp;
	readfile.seekg(0);
	 while(!readfile.eof()){
        readfile.read((char*)&temp,sizeof(temp));

		if(!strcmp(u,temp.usn)){
            flag=true;
            break;
		}
		if(temp.admissionNo==-1)
			break;

    }
    if(!flag){
  		return USN_NOT_FOUND;
    }
    *this=temp;
	return SUCCESS;

}

void student::showProfile(){

}

void student::showMarks(){

}

void student::showAttendence(){

}

int student::Notification(){

    return 0;//change while truly defined
}

int student::timetable(){
    return 0;
}


char u1[11];
int student::complaint(){

}
int setup(){
	title();
	ifstream fp("student.bin",ios::binary|ios::in);
	if(fp.is_open())
		return 0;
	cout<<endl<<"Initiating required files for first time usage... ";
    fp.close();
	ofstream ofp("student.bin",ios::binary|ios::out);
// Store the initial data to the file.
	if(!ofp.is_open()) return -1;
	ofp.close();
	ofstream _ofp("staff.bin",ios::binary|ios::out);
	if(!_ofp.is_open()) return -1;
	_ofp.close();
	ofstream _o("work_date.bin",ios::out);
	_o.close();
	ofstream _f("notification.bin",ios::binary|ios::out);
	if(!_f.is_open()) return -1;
	_f.close();
	ofstream _fi("complaint.bin",ios::binary|ios::out);
	if(!_fi.is_open()) return -1;
	_fi.close();
	ofstream _fii("topic.bin",ios::binary|ios::out);
	if(!_fii.is_open()) return -1;
	_fii.close();
	ofstream _fiii("subject_code.bin",ios::binary|ios::out);
	if(!_fiii.is_open()) return -1;
	_fiii.close();
	Sleep(2000);
	cout<<" : DONE";
	cin.get();
	return 0;
}
int user_student(){
    static int error;
    char usn[11];
	clrscr();
    title();
    cout<<"\tLogin type : Student."<<endl;
	cout<<endl<<"\tEnter your usn number : ";
    cin>>usn;
    strupr(usn);
    cout<<endl<<"\tEnter the password    : ";
    char pass[15],c;
    int i=0;
     while((c=getch())!=13){ pass[i]=c;
                i++; cout<<'*';
			}
	pass[i]='\0';
	strupr(pass);
	int choice;
    student s;
	flag=s.init(usn);
    if(flag == USN_NOT_FOUND){
		cout<<"\n\tNo such usn assigned to student... ";
		cin.get();
		return 0;
	}
	else if(flag==F_NOT_FOUND){
		cerr<<"\n\tError in opening file...please try again";
					Sleep(2000);
					return 0;
	}
	char temp_pass[10];
	strcpy(temp_pass,s.pass);
	if(strcmp(temp_pass,pass)){
       cout<<"\n\tInavlid usn or password..."<<endl;
       return -1;
    }
    while(1) {
        clrscr();
		title();
		cout<<"\tLogin type : Student  ["<<usn<<"]"<<endl;
       	cout<<"\t\tMenu"<<endl;
       	cout<<"\t\t1 : View profile\n\t\t2 : View attendence\n\t\t3 : View marks\n\t\t4 : View Notifications \n\t\t5 : Give a Complaint \n\t\t6 : Exit"<<endl;
       	cout<<"\tEnter your choice  : ";
       	cin>>choice;
       	switch(choice){
           case 1 : fflush(stdin);
		   			clrscr();
		   			s.showProfile();
                    break;
           case 2 : fflush(stdin);
                    clrscr();
		            s.showAttendence();
                     break;
           case 3 : fflush(stdin);
		   			clrscr();
		   			s.showMarks();
                    break;
           case 4 : fflush(stdin);
		   			clrscr();
		   			s.Notification();
                    break;
           case 5 : fflush(stdin);
		   			clrscr();
		   			strcpy(u1,usn);
		   			s.complaint();
                    break;
		   case 6 : cout<<"Logging out...["<<usn<<"]";
		   			Sleep(1000);
		   			return SUCCESS;
            default : cout<<"Select valid choice : ";
		   		Sleep(1000);
       }
    }
};
int user_teacher(){
    return 0;
};
int user_admin(){
    return 0;
};
int main(){
    setdepartment();
    if(setup()) {
		cout<<"Files are missing and unable to create new files...\n Please try again..."; Sleep(2000);
		exit(1);
	}
    while(1){
        clrscr();
        title();
        cout<<"\n\t\tLogin Option for you"<<endl;
        cout<<"\t\t 1 : Student "<<endl;
        cout<<"\t\t 2 : Teacher   "<<endl;
        cout<<"\t\t 3 : Admin "<<endl;
        cout<<"\t\t 4 : Exit"<<endl;
        cout<<endl<<"\t\tEnter your choice : ";
        static int error;
        int your_choice;
        cin >> your_choice;
        switch(your_choice){
            case 1 : error=0;
					while(error<5) {  //Students are allowed to attemp for maximum 5 times
					        if(user_student())
							error++;
                  			else break;
								   }
					if(error>4)
							cout<<" Authentication failed...";
				 			cin.get();
					break;
            case 2 :error=0;
					while(error<5) {
                            if(user_teacher())
							error++;
                  			else break;
								   }
                    if(error>4)
                        cout<<" Authentication failed...";
                    cin.get();
					break;
            case 3 :user_admin();
                	break;
            case 4 :cout<<"Terminating..."; Sleep(1000);
                    exit(0);
            default:cout <<"Invalid choice : ";
                    Sleep(1000);
                    cin.get();

        }
    }

}
