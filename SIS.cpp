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
int flag,subject_no=0,dept_code=0,semester_no=0;

char subject_array[9][10][20][50];

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
class teacher;
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
       // friend int teacher::init(char *id);
};
class admin;
class teacher:public staff{
        int total_course;
        int course_code[10];
        int class_taken[10];
        int dept_id;
public:
        char password[10];
        teacher(){
            staff_id[0]=staff_name[0]=email[0]=password[0]='\0';
            total_course=0;
            memset(course_code,0,sizeof(course_code));
            memset(class_taken,0,sizeof(class_taken));
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
            cout<<endl<<"Input course code(must be consist of 4 digit) "<<endl;
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
        void showProfile(){
        clrscr();
        title();
        cout<<"Profile...."<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        cout<<" Staff Name      \t :"<<staff_name<<endl;
        cout<<" Staff Id        \t :"<<staff_id<<endl;
        cout<<" Email id        \t :"<<email<<endl;
        cout<<" Department      \t :"<<department[dept_id] <<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        fflush(stdin);
        cin.get();
        }
         friend class admin;

};
class admin:public staff{

public:
     char password[10];
     admin(){
        staff_id[0]=staff_name[0]=email[0]=password[0]='\0';
     }
     admin(char *_id,char *_pass,char *_name,char *_email){
            strcpy(staff_id,_id);
            strcpy(password,_pass);
            strcpy(staff_name,_name);
            strcpy(email,_email);
        }

    int addTeacher();
    int admitStudent();
    int removeTeacher(char*);
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
    int update_subjects_info();
    int update_students_semester(char *);
    friend int user_admin();


};
class student{
    int admissionNo;
    char usn[11];
    char name[30];
    char email[30];
    char dob[11];
    struct sub{
        int subject_info[20][20];
    }marks,attendence;
public:
    int semester;
    int dept_id;
    char pass[10];
    student(){
        admissionNo=-1;
        strcpy(usn,"\0");
        strcpy(name,"\0");
        strcpy(email,"\0");
        strcpy(dob,"\0");
        memset(marks.subject_info,-1,sizeof(marks.subject_info));
        memset(attendence.subject_info,0,sizeof(attendence.subject_info));
        semester=0;
        dept_id=0;
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
    void operator++();
};

void admin::showProfile(){
	clrscr();
	title();
    cout<<" Admin profile...."<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
    cout<<" Admin Name      \t :"<<staff_name<<endl;
    cout<<" Admin Id        \t :"<<staff_id<<endl;
    cout<<" Email Id        \t :"<<email<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
	fflush(stdin);
	cin.get();
}
void admin::viewMarks(){
    char usn[15];
	clrscr();
	title();
	cout<<endl<<"Please enter the student USN : "; cin>>usn;
	strupr(usn);
	student s;
	fflush(stdin);
	if(s.init(usn)){
		cout<<" Enter valid USN...";
		cin.get();
		return;
		}
	s.showMarks();
}

void admin::viewAttendence(){
    char u[15];
	clrscr();
	title();
	cout<<"Please enter student USN : "; cin>>u;
	strupr(u);
	student s;
	fflush(stdin);
	if(s.init(u)){
		cout<<" Enter valid USN...";
		cin.get();
		return;
	}
	s.showAttendence();
}



int admin::removeStudent(char *u){
    bool flag=false;
	long pos;
    fstream readfile("student.bin",ios::binary|ios::in|ios::out);
    if(!readfile){
        cout<<"Error in opening the file...please try again";
        cin.get();
		return F_NOT_FOUND;
     }
     student temp;
     while(!readfile.eof()){
		pos=readfile.tellg(); //replace object with null bytes
        readfile.read((char*)&temp,sizeof(temp));
			if(!strcmp(u,temp.usn)){
            	flag=true;
            	break;
        	}
    }
    if(!flag){
        cout<<"\tInvalid user "<<endl;
        return USN_NOT_FOUND;
		cin.get();
    }
        temp.admissionNo=-1;
        strcpy(temp.usn,"\0");
        strcpy(temp.name,"\0");
        strcpy(temp.email,"\0");
        strcpy(temp.dob,"\0");
        memset(temp.marks.subject_info,-1,sizeof(temp.marks.subject_info));
        memset(temp.attendence.subject_info,0,sizeof(temp.attendence.subject_info));
        temp.semester=0;
        temp.dept_id=0;
        	readfile.seekp(pos);
	readfile.write((char*)&temp,sizeof(temp));
	fflush(stdin);
	cout<<"Student record removed successfully...";
	cin.get();
	return SUCCESS;

}

int admin::addTeacher(){
    char name[40],pass[10],email[30],id[10];
    int d_id;
    clrscr();
	ofstream putf("staff.bin",ios::binary|ios::out|ios::app);
    if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
	title();
	cout<<" Please enter the following fields...[all fields are mandatory]"<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n Enter teacher id                            : "; cin>>id;
	strupr(id);
	fflush(stdin);
	cout<<"\n Enter teacher name                          : "; cin.getline(name,30);
	fflush(stdin);
	cout<<"\n Enter a password for this teacher           : "; cin>>pass;
	strupr(pass);
	fflush(stdin);
	cout<<"\n Enter the mail id                           : "; cin>>email;
	cout<<"\n Enter teacher's department code (1.MCE, 2.EEE, 3.TVE, 4.CSE, 5.CEE,6.SWE,7.BTM) : "; cin>>d_id;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	teacher temp(id,pass,name,email,d_id);
	fflush(stdin);
	cout<<"Press enter to proceed "; cin.get();
	clrscr();
	temp.showProfile();
	putf.write((char*)&temp,sizeof(temp));
	putf.close();
	cout<<endl<<" Staff member added successfully...";
	cout<< "\nTo allocate Mr."<<name<<" courses, follow the option UPDATE TEACHER INFO from admin panel";
	cin.get();
	return SUCCESS;

}

int admin::Notification(){
    	clrscr();
	ofstream putf("notification.bin",ios::binary|ios::out|ios::app);
	if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
	title();
	char today[11],note[500];
	getdate(today);
	 cout<<"\t\t\t\t\t\t\t    Today : "<<today;
	cout<<"\nEnter Notifications: \n";
	fflush(stdin);
	cin.getline(note,500);
    putf<<"\n_________________________________________________________________   "<<today<<"\n"<<note<<"\n\n\n";
	putf.close();
	cout<<endl<<" Notification added successfully..."; cin.get();

}

int admin::complaint(){
    clrscr();
	char ch;
	cout<<"\n\tCOMPLAINT:\n\n";
    ifstream readfile1("complaint.bin",ios::binary|ios::in);
    if(!readfile1.is_open()){
              return F_NOT_FOUND;
    }
	fflush(stdin);
	title();
	readfile1.seekg(0);
	cout<<"\n ";
	 while(!readfile1.eof()){
    readfile1.get(ch);
    cout<<ch;
    }
    cout<<"\nPress any key to return...";
	cin.get();
	readfile1.close();
}

int admin::timetable(){
    clrscr();
	ofstream pf("table.bin",ios::binary|ios::out);
	if(!pf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
	title();
	char today[11],note[20],start[10],end[10];
	getdate(today);
	 cout<<"\t\t\t\t\t\t\t    Today : "<<today;
	cout<<"\nEnter exam starting and ending time: \n";
	cin>>start>>end;
	fflush(stdin);
	pf<<"\n\n_______________________________________________________________     "<<today<<"\n\n\n";
	cout<<"Enter exam date for following subject :\n";
	   pf<<'|'<<" SUBJECT   "<<'|'<<"\t"<<"DATE     "<<'|'<<"\t"<<"START TIME "<<'|'<<"\t"<<"END TIME "<<" "<<'|'<<endl;
    cout<<"OOP     : ";
	cin>>note;
	   pf<<'|'<<"       OOP "<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;
    cout<<"MATHS   : ";
    cin>>note;
       pf<<'|'<<"     MATHS "<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;
    cout<<"CO      : ";
    cin>>note;
       pf<<'|'<<"        CO "<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;
    cout<<"MP      : ";
    cin>>note;
       pf<<'|'<<"        MP "<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;

	pf.close();
	cout<<endl<<" Exam time table updated successfully..."; cin.get();
	cin.get();
}

int admin::removeTeacher(char *u){
    bool flag=false;
	long pos;
    fstream readfile("staff.bin",ios::binary|ios::in|ios::out);
	if(!readfile){
        cerr<<"Error in opening file...please try again";
        return F_NOT_FOUND;
     }
    teacher temp;
    while(!readfile.eof()){
		pos=readfile.tellg(); //replace object with null bytes
        readfile.read((char*)&temp,sizeof(temp));
			if(!strcmp(u,temp.getid())){
            	flag=true;
            	break;
        	}
    }
	if(!flag){
        cerr<<"\tInvalid user "<<endl;
        return USN_NOT_FOUND;
    	}
    readfile.seekp(pos);
    teacher del;
    readfile.write((char*)&del,sizeof(teacher));
	fflush(stdin);
	cout<<"Staff  removed successfully...";
	cin.get();
	return SUCCESS;

}

int admin::manageAttendence(){
    //have to work later
    return 0;
}

int admin::listStudent(){
    title();
	char prev[12];
	ifstream readF("student.bin",ios::binary|ios::in);
	student temp;
	fflush(stdin);
	cout<<"\tUSN\t\tNAME"<<endl;
    int full=0;
    while(!readF.eof()){
        readF.read((char*)&temp,sizeof(temp));
		if(temp.admissionNo==-1){ cout<<endl<<"End of list";
			break;
		}
		full++;
		if(full>10){
                cout<<"Press enter to continue...";
                cin.get();
                full=0;
                title();
                cout<<"\tUSN\t\tNAME"<<endl;
               }
        if(!strcmp(prev,temp.usn)) continue;
        strcpy(prev,temp.usn);
		cout<<"\t"<<temp.usn<<"\t"<<temp.name<<endl;

    }
	cout<<"\nPress any key to return...";
	cin.get();
	readF.close();
}

int admin::admitStudent(){
    clrscr();
	fstream putf("student.bin",ios::binary|ios::out|ios::app);
	if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
    student temp;
    putf.seekp(ios::end);
	title();
	cout<<"Please enter the following fields...[all fields are mandatory]"<<endl;
	fflush(stdin);
	student t;
    int status=0;
    cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n # Please enter usn number               : "; cin>>temp.usn;
	fflush(stdin);
	strupr(temp.usn);
	if(USN_NOT_FOUND!=t.init(temp.usn)){
		cout<<"This USN number is already assigned to : "<<t.name;
		Sleep(1000);
		if(++status<3)
		admitStudent();
		else return 0;
	}
	fflush(stdin);
	cout<<"\n # Please enter full name of the student : "; cin.getline(temp.name,30);
	fflush(stdin);
	cout<<"\n # Please enter date of birth            : "; cin>>temp.dob;
	fflush(stdin);
	cout<<"\n # Please enter new admission number     : "; cin>>temp.admissionNo;
	fflush(stdin);

	fflush(stdin);
	cout<<"\n # Please enter email id of the student  : "; cin>>temp.email;
	fflush(stdin);
	cout<<"\n # Please enter a password for the student: "; cin>>temp.pass;
	strupr(temp.pass);
	fflush(stdin);
	cout<<"\n # Please enter which semester he is in    : "; cin>>temp.semester;
	fflush(stdin);
	cout<<"\n Enter teacher's department code (1.MCE, 2.EEE, 3.TVE, 4.CSE, 5.CEE,6.SWE,7.BTM) : "; cin>>temp.dept_id;
	fflush(stdin);
	cout<<"\n Press enter to proceed ";
	cin.get();
	clrscr();
	title();
	cout<<"\n The new student details are as given below... "<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;

	cout<<"\n # Admission Number       : "<<temp.admissionNo<<endl;
	cout<<" # Student name           : "<<temp.name<<endl;
	cout<<" # University Seat Number : "<<temp.usn<<endl;
	cout<<" # Date of birth          : "<<temp.dob<<endl;
	cout<<" # Email id               : "<<temp.email<<endl;
	cout<<" # Password               : "<<temp.pass<<endl;
	cout<<" # Semester               : "<<temp.semester<<endl;
	cout<<" # Department ID          : "<<temp.dept_id<<endl;
    memset(temp.marks.subject_info,-1,sizeof(temp.marks.subject_info));
    memset(temp.attendence.subject_info,0,sizeof(temp.attendence.subject_info));
    cout<<" Are the above details correct?  [Y/N] : ";
	char yes;
	cin.get(yes); fflush(stdin);
	if(yes=='Y'||yes=='y') {

		putf.write((char*)&temp,sizeof(temp));
	cout<<"New student added successfully..."<<endl;
	cin.get();
	putf.close();
	}
	else {

		cout<<" Student details weren't added ";
		Sleep(800);
		return -1;
	}
	clrscr();
}

int admin::update_teacher_info(char *u){
    bool flag=false;
	long pos;
    fstream readfile("staff.bin",ios::binary|ios::in|ios::out);
    if(!readfile){
        cout<<"Error in opening the file...please try again";
        cin.get();
		return F_NOT_FOUND;
     }
     teacher temp;
      while(!readfile.eof()){
		pos=readfile.tellg(); //replace object with null bytes
        readfile.read((char*)&temp,sizeof(temp));
			if(!strcmp(u,temp.staff_id)){
            	flag=true;
            	break;
        	}
    }
    if(!flag){
        cout<<"\tInvalid user "<<endl;
        return USN_NOT_FOUND;
		cin.get();
    }
    int t;
    cout<<"\n Enter the teacher "<<u<<" current total course   : "; cin>>t;
	fflush(stdin);
	temp.total_course=t;
	int temp_c;
    cout<<"\n Enter his courses id(must be consist of 4 digits)   : ";
	for(int i=0;i<t;i++){
        scanf("%d",&temp_c);
        temp.course_code[i]=temp_c;
	}
	memset(temp.class_taken,0,sizeof(temp.class_taken));
	readfile.seekp(pos);
	readfile.write((char*)&temp,sizeof(temp));
	fflush(stdin);
	cout<<"Teachers courses record updated successfully...";
	cin.get();
	return SUCCESS;
}

int admin::update_subjects_info(){
    clrscr();
	fstream putf("subject_code.bin",ios::binary|ios::out);
	if(!putf){
		cerr<<"Unable to open subject record file ";
		return F_NOT_FOUND;
	}
	//putf.seekp(ios::begin);
	while(1){
	title();
    cout<<"Please enter the following fields...[all fields are mandatory]"<<endl;
	fflush(stdin);
	 int status=0;
	 int temp_status;
	 char sub[50];
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n # Please enter subject code(consist of 4 digit)               : "; cin>>status;
	temp_status=status;
	subject_no=(int)status%100;
	status/=100;
	semester_no=status%10;
	status/=10;
	dept_code=status;
	fflush(stdin);
	cout<<"\n # Please enter subject name                                   : "; cin>>sub;
	strcpy(subject_array[dept_code][semester_no][subject_no],sub);
	cout<<"\n Press enter to proceed ";
	cin.get();
	clrscr();
	title();
	cout<<"\n The new subject details are as given below... "<<endl;
	cout<<"\n Course for dept "<< department[dept_code] << " in the semester "<<semester_no << " having code no "<<temp_status<<"\nCourse Name: "<<subject_array[dept_code][semester_no][subject_no] <<endl;
	cout<<"New subject added successfully..."<<endl;
	cin.get();
	cout<<" \n Do you want to add more subject?  [Y/N] : ";
	char yes;
	cin.get(yes); fflush(stdin);
	if(yes=='Y'||yes=='y')
        continue;
    else
        break;
	}
	putf.write((char*)&subject_array,sizeof(subject_array));
	putf.close();
	clrscr();

}

int admin::update_students_semester(char *u){
    bool flag=false;
	long pos;
	 fstream readfile("student.bin",ios::binary|ios::in|ios::out);
	if(!readfile){
        cerr<<"Error in opening the file...please try again";
        cin.get();
		return F_NOT_FOUND;
     }
    student temp;
    while(!readfile.eof()){
		pos=readfile.tellg(); //replace object with null bytes
        readfile.read((char*)&temp,sizeof(temp));
			if(!strcmp(u,temp.usn)){
            	flag=true;
            	break;
        	}
    }
    if(!flag){
        cerr<<"\tInvalid user "<<endl;
        return USN_NOT_FOUND;
		cin.get();
    }
    int t;
    cout<<"\n Enter the student "<<u<<" current semester     : "; cin>>t;
	fflush(stdin);
	temp.semester=t;
	int ct;
	cout<<"\n How much course he is being offered in this semester ?    :";cin>>ct;
    clrscr();
	title();
	cout<<"\n Enter the courses ID (must be of 4 digits)  :"<<endl;
	int te;
	for(int i=0;i<ct;i++){
        cin>>te;
        int code;
        code=(int)te%100;
        temp.marks.subject_info[temp.semester][code]=0;
	}
	readfile.seekp(pos);
	readfile.write((char*)&temp,sizeof(temp));
	fflush(stdin);
	cout<<"Student record updated successfully...";
	cin.get();
	return SUCCESS;

}

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
    clrscr();
    title();
    cout<<"My proifile...."<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<" Name                :"<<name<<endl;
    cout<<" Admission number    :"<<admissionNo<<endl;
    cout<<" USN                 :"<<usn<<endl;
    cout<<" Date of birth       :"<<dob<<endl;
    cout<<" Email id            :"<<email<<endl;
    cout<<" Department          :"<<department[dept_id] <<endl;
    cout<<" Semester            :"<<semester<<endl;
    cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"Press any key to exit :";
	cin.get();

}

void student::showMarks(){
    clrscr();
	title();
	cout<<"\tWhat do you want? \t1.Result of a semester \t2.Result of particular course"<<endl;
	int choice;
	cin>>choice;
    clrscr();
	title();
	if(choice==1){
        cout<<"\n\tResult of which semester?"<<endl;
        int st;
        cin>>st;
        clrscr();
        title();
        cout<<" Test Result     : "<<name<<endl;
        cout<<endl<<"_______________________________________________________________________________"<<endl;
        cout<<" COURSE NAME                          : MARKS "<<endl;
        cout<<endl<<"_______________________________________________________________________________"<<endl;
        for(int i=1;i<20;i++){
            if(marks.subject_info[st][i]==-1)
                continue;
            else if(marks.subject_info[st][i]==0){
                cout<< subject_array[dept_id][st][i] <<"              : "<<"Not Entered"<<endl;
            }
            else if(marks.subject_info[st][i]>0){
                cout<< subject_array[dept_id][st][i] <<"              : "<<marks.subject_info[st][i]<<endl;
            }
        }
        cout<<endl<<"_______________________________________________________________________________"<<endl;
        cout<<"Press any key to exit :";
        cin.get();

	}
	else if(choice==2){
        int st;
        cout<<"\n\tResult of which course?"<<endl;
        cin>>st;
        int ct;
        ct=(int)st%100;
        st=st/100;
        st=st%10;
        cout<<" Test Result     : "<<name<<endl;
        cout<<endl<<"_______________________________________________________________________________"<<endl;
        cout<<" COURSE NAME                          : MARKS "<<endl;
        cout<<endl<<"_______________________________________________________________________________"<<endl;
        cout<< subject_array[dept_id][st][ct] <<"              : "<<marks.subject_info[st][ct]<<endl;
        cout<<endl<<"_______________________________________________________________________________"<<endl;
        cout<<"Press any key to exit :";
        cin.get();
	}
}

void student::showAttendence(){
 //it will be shown later
}

int student::Notification(){

  clrscr();
	char ch;

    ifstream readfile("notification.bin",ios::binary|ios::in);
    if(!readfile.is_open()){
              return F_NOT_FOUND;
    }

	title();
	cout<<"\n\tNOTIFICATIONS: \n\n";
	readfile.seekg(0);
	cout<<"\n ";
    while(!readfile.eof()){
    readfile.get(ch);
    cout<<ch;
    }

    cout<<"\nPress any key to return...";
	cin.get();
	readfile.close();
}

int student::timetable(){
    clrscr();
	char ch;
    ifstream readfile1("table.bin",ios::binary|ios::in);
    if(!readfile1.is_open()){
              return F_NOT_FOUND;
    }

	title();
	cout<<"\t\t\tExam Time Table\n";
	readfile1.seekg(0);
	cout<<"\n ";
    while(!readfile1.eof()){
    readfile1.get(ch);
    cout<<ch;
    }
    cout<<"\n________________________________________________________________________ ";
    cout<<"\nPress any key to return...";
	cin.get();
	readfile1.close();
}


char u1[11];
int student::complaint(){
    clrscr();
    ofstream putf("complaint.bin",ios::binary|ios::out|ios::app);
	if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}

	title();
	char today[11],note[500];
	getdate(today);
	 cout<<"\t\t\t\t\t\t\t    Today : "<<today;
	cout<<"\nEnter Complaint: \n";
	fflush(stdin);
	cin.getline(note,500);
		putf<<"\n\n__________________________________________________________       "<<today<<"\n"<<note<<"\t -"<<u1<<"\n\n\n";

	putf.close();
	cout<<endl<<" Complaint given successfully..."; cin.get();
}

int teacher::init(char *id){
    bool flag=false;
    ifstream readfile("staff.bin",ios::binary|ios::in);
        if(!readfile.is_open()){
            cerr<<"\nError opening the record... please try again."<<endl;
            Sleep(3000);
			return F_NOT_FOUND;
        }
    teacher temp;
    while(!readfile.eof()){

    readfile.read((char*)&temp,sizeof(temp));
		if(!strcmp(id,temp.staff_id)){
            flag=true;
            break;
		}
    }
    if(!flag){
        cout<<"\nStaff with staff id : ["<<id<<"] not found. Enter valid id"<<endl;
		Sleep(1000);
    return USN_NOT_FOUND;
    }
    *this=temp;
     return SUCCESS;
}

int teacher::manageMarks(){
    title();
    int c=0;
	int m;
	student temp;
	fstream readfile("student.bin",ios::binary|ios::in|ios::out);
    if(!readfile.is_open()){
		cout<<"Error : Student database file missing...";
		return F_NOT_FOUND;
	}
	clrscr();
	title();
	int su;
	cout<<endl<<"Enter the subject code you want to edit (must be consist of 4 digit) : ";
	cin>>su;
	int fg=0;
	for(int i=0;i<total_course;i++){
        if(course_code[i]==su){
            fg=1;
            break;
        }
	}
	if(fg==0){
        cout<<endl<<"You are not allowed to change marks of this course"<<endl;
        return 0;
	}
	subject_no=(int)su%100;
	su/=100;
	semester_no=su%10;
	dept_code=su/10;
	cout<<endl<<"Now edit the marks of students who took the course "<<subject_array[dept_code][semester_no][subject_no] << "from the department " << department[dept_code] <<endl;
    readfile.seekg(0);
    while(!readfile.eof()){
        fflush(stdin);
        readfile.read((char*)&temp,sizeof(temp));
        if(temp.dept_id==dept_code && temp.semester==semester_no && temp.marks.subject_info[semester_no][subject_no]!=-1){
            int m;
            cout<<temp.admissionNo << " :";
            cin>>m;
            temp.marks.subject_info[semester_no][subject_no]=m;

        }
        readfile.seekp((long)readfile.tellg()-sizeof(temp));
		readfile.write((char*)&temp,sizeof(temp));
		c++;
		if(c>15) {
			clrscr();
			title();
    		c=0;
		}
		fflush(stdin);
		cin.get();

    }
    cout<<" Marks have been updated succesfully..."; Sleep(3000);
	return SUCCESS;

}

int teacher::manageAttendence(){
    char day[10];
	clrscr();
	fflush(stdin);
	title();
	getdate(day);
	student temp;
	int c=0;
	fstream readfile("student.bin",ios::binary|ios::in|ios::out);
    if(!readfile.is_open()){
		cout<<"Error : Student database file missing...";
		return F_NOT_FOUND;
	}
	int su;
	int youtake;
	cout<<endl<<"Enter your subject code which attendance you want to give (must be consist of 4 digit) : ";
	cin>>su;
	int fg=0;
	for(int i=0;i<total_course;i++){
        if(su==course_code[i]){
            fg=1;
            youtake=i;
            break;
        }
	}
	if(fg==0){
        cout<<endl<<"Sorry,you are not allowed"<<endl;
        return 0;
	}
	class_taken[youtake]++;
	subject_no=(int)su%100;
	su/=100;
	semester_no=su%10;
	dept_code=su/10;
	cout<<endl<<"Now edit the students of students who took the course "<<subject_array[dept_code][semester_no][subject_no] << "from the department " << department[dept_code] <<endl;
    readfile.seekg(0);
    while(!readfile.eof()){
        fflush(stdin);
        readfile.read((char*)&temp,sizeof(temp));
          if(temp.dept_id==dept_code && temp.semester==semester_no && temp.marks.subject_info[semester_no][subject_no]!=-1){
            char ch;
            cout<<"student ID" << temp.admissionNo <<endl;
            cout<<"present? (Y/N) "<<endl;
            fflush(stdin);
            cin>>ch;
            fflush(stdin);
            if(ch=='y' || ch=='Y')
                ++temp;


          }
        readfile.seekp((long)readfile.tellg()-sizeof(temp));
		readfile.write((char*)&temp,sizeof(temp));
		c++;
		if(c>15) {
			clrscr();
			title();
    		c=0;
		}
		fflush(stdin);
		cin.get();

    }
    cout<<" Attendance have been updated succesfully..."; Sleep(3000);
	return SUCCESS;
}
void student::operator++(){
    this->attendence.subject_info[semester_no][subject_no]+=1;
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
	ofstream _o("log.bin",ios::out);
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
	ofstream _fiiiad("admin_file.bin",ios::binary|ios::out);
	if(!_fiiiad.is_open()) return -1;
	clrscr();
	title();
	cout<<"\t\tThis is your first installation "<<endl;
	cout<<"\t\tSo you have to make an admin ID"<<endl;
	char _stid[10];
	char _stname[50];
	char _stemail[30];
	char _stpass[10];
	//admin tempad;
	cout<<"\t\tEnter your staff ID: ";
	cin>>_stid;
	strupr(_stid);
	fflush(stdin);
	cout<<endl<<"\t\tEnter your name: ";
	cin.getline(_stname,50);
	fflush(stdin);
	cout<<endl<<"\t\tEnter your Email address: ";
	cin>>_stemail;
	fflush(stdin);
	cout<<endl<<"\t\tEnter a password for you: ";
	cin>>_stpass;
	strupr(_stpass);
	fflush(stdin);
	admin temp(_stid,_stpass,_stname,_stemail);
    fflush(stdin);
	cout<<"Press enter to proceed "; cin.get();
	clrscr();
	temp.showProfile();
	_fiiiad.write((char*)&temp,sizeof(temp));
	_fiiiad.close();
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
		cout<<"\n\tError in opening file...please try again";
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
    char staffid[10];
	title();
	cout<<"\tLogin type : Staff"<<endl;
    fflush(stdin);
    cout<<endl<<"\tEnter staff id      : ";
    cin>>staffid;
    fflush(stdin);
    cout<<"\tEnter the password  : ";
    char pass[15],c;
	short i=0;
    while((c=getch())!=13){
			pass[i]=c; i++; cout<<'*';
		}
	pass[i]='\0';
	strupr(pass);
	strupr(staffid);
	//int choice;
	teacher staf;
	flag=staf.init(staffid);
	 if(flag == USN_NOT_FOUND){
		cout<<"\n\tNo such usn assigned to teacher... ";
		cin.get();
		return 0;
	}
	else if(flag==F_NOT_FOUND){
		cout<<"\n\tError in opening file...please try again";
					Sleep(2000);
					return 0;
	}
    char temp_pass[10];
	strcpy(temp_pass,staf.password);
	if(strcmp(temp_pass,pass)){
       cout<<"\n\tInavlid usn or password..."<<endl;
       return -1;
    }

    while(1){
        clrscr();
        title();
        cout<<"\tLogin type : Staff  ["<<staffid<<"]"<<endl;
        cout<<"\t\tMenu"<<endl;
        cout<<"\t\t1 : View profile\n\t\t2 : Manage attendence\n\t\t3 : Manage marks\n\t\t4 : Exit"<<endl;
        cout<<"\n\tEnter your choice  : ";
        int choice;
        cin>>choice;
        switch(choice){
           case 1 :fflush(stdin);
                    clrscr();
                    staf.showProfile();
		   			break;

           case 2 : fflush(stdin);
                    clrscr();
                    staf.manageAttendence();
                    break;

           case 3 : fflush(stdin);
                    clrscr();
                    staf.manageMarks();
                    break;
           case 4 : cout<<"Logging out...["<<staffid<<"]";
		   			Sleep(1000);
                    return SUCCESS;
            default : cout<<"Select valid choice : ";
		  Sleep(1000);
		         }
    }


};
int user_admin(){
    char id[10];
    char pass[15],c;
	clrscr();
	title();
	cout<<"\tLogin type : Administrator"<<endl;
    cout<<"\n\tEnter admin id           : ";
	cin>>id;
	fflush(stdin);
	strupr(id);
	 cout<<"\n\tEnter admin password     : ";
	int i=0;
    while((c=getch())!=13){ pass[i]=c; i++; cout<<'*';
	  }
	pass[i]='\0';
	strupr(pass);
	admin ad;
	 bool flag=false;
    ifstream readfile("admin_file.bin",ios::binary|ios::in);
        if(!readfile.is_open()){
            cout<<"\nError opening the record... please try again."<<endl;
            Sleep(3000);
			return 0;
        }
    readfile.seekg(0);
    while(!readfile.eof()){

    readfile.read((char*)&ad,sizeof(ad));
		if(!strcmp(id,ad.staff_id)){
            flag=true;
            break;
		}
    }
    if(!flag){
      cout<<"\n\tNo such Admin found ... ";
		cin.get();
		return 0;
    }
    readfile.close();
    char temp_pass[10];
	strcpy(temp_pass,ad.password);
	if(strcmp(temp_pass,pass)){
       cout<<"\r\tAuthentication error..."<<pass<<endl;
      	cin.get();
    	exit(0);
    }
	while(1){
         clrscr();
        title();
        cout<<"\tLogin type : Administrator  ["<<id<<"]"<<endl;
        cout<<"\t\tMenu"<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        cout<<"\t\t1 : Admit student\n\t\t2 : Remove Student\n\t\t3 : Add Teacher\n\t\t4 : Remove Teacher\n\t\t5 : List Students\n\t\t6 : Manage attendance";
        cout<<"\n\t\t7 : View student attendance\n\t\t8 : View student marks \n\t\t9 : Notifications \n\t\t10: Check Complaints \n\t\t11: Update Courses of Teachers \n\t\t12: Update Course Information  \n\t\t13: Update Students semester";
        cout<<  "\n\t\t14: Set Exam Time\n\t\t15: Show Admin Info  \n\t\t16: Exit"<<endl;
        cout<<"_______________________________________________________________________________"<<endl;
        cout<<"\n\tEnter your choice  : ";
        int choice;
        cin>>choice;
        char s[5];
        switch(choice){
            case 1 : clrscr();
		   			ad.admitStudent();
		   				break;
            case 2 : cout<<"\n\tEnter the valid USN : "; cin>>pass;
					strupr(pass);
                    ad.removeStudent(pass);
		   				break;
            case 3 : ad.addTeacher();
		   				break;
            case 4 :cout<<"\n\tEnter the staff id : "; cin>>pass;
					strupr(pass);
					ad.removeTeacher(pass);
						break;
            case 5 :clrscr();
		   			ad.listStudent();
                    	break;
            case 6 :clrscr();
		   			ad.manageAttendence();
                    break;
            case 7 :clrscr();
		   			ad.viewAttendence();
                    break;
            case 8 :clrscr();
		   			ad.viewMarks();
                    break;
            case 9 :clrscr();
		   		   	ad.Notification();
                    break;
            case 10 :clrscr();
		   		   	ad.complaint();
                    break;
            case 11 :clrscr();
                    cout<<"\n\tEnter the teacher id : "; cin>>pass;
					strupr(pass);
		   		   	ad.update_teacher_info(pass);
                    break;
            case 12 :clrscr();
		   		   	ad.update_subjects_info();
		   		   		break;
            case 13 :clrscr();
                    cout<<"\n\tEnter the valid USN : "; cin>>pass;
					strupr(pass);
		   		   	ad.update_students_semester(pass);
		   		   		break;
            case 14 :clrscr();
		   		   	ad.timetable();
		   		   		break;
            case 15 :
					ad.showProfile();
            case 16 :cout<<"Logging out...["<<id<<"]";
		   			Sleep(1000);
                    	return 0;
             default : cout<<"Select valid choice : ";
					Sleep(1000);



        }
	}

};
void setsubject(){
    ifstream readF("subject_code.bin",ios::binary|ios::in);
     readF.read((char*)&subject_array,sizeof(subject_array));
     readF.close();

}
int main(){
    setdepartment();
    setsubject();
    //cout<<subject_info[4][3][1]<<endl;
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
