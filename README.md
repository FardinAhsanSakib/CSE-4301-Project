# CSE-4301-Project
A Student Information Management System using C++.

## Project Team Members:
1.Fardin Ahsan Sakib (160041059) 
Github: fardin160041059

2.Md. Mumtahin Habib Ullah Mazumder (160041066) 
Github: mhrafi66

3.A. H. M. Rezaul Karim (160041022) 
Github: AHMRezaul

4.Ahmad Imam (160041054) 
Github: Ahmad-Imam

5.Mohammad Sabik Irbaz (160041004)
Github: msi1427

## Steps to run this program in local machine:

### For the file created using database and saved in the folder "SIS new":

1. Clone the project from the project containing folder

2. Download SQLapi library from http://www.sqlapi.com/Download/sqlapi_trial.exe

3.Use Microsoft Visual Studio

4. Go to the visual studio folder and copy paste all the .dll files inside bin folder to C:\Windows\System32 and the project folder which containing the source files.

5.Our compiler was Microsoft Visual Studio 2017 and the machine was 64-bit. So the bin folder was SQLAPI\vs2017\x86_64\bin

6.In "project properties" the file named "additional include directories" row add two file paths:
	i) To include folder in the sqlapi folder  (ex: ora_win )
	ii) To include corresponding database folder (ex: SQLAPI\include\ora_win)

7.Change the project platform to x64 from configuration manager if machine is 64-bit.

8.To make connection with databse:
 In "additional library directories" row add a file path corresponding to lib folder which was with the bin folder was mentioned above.(ex: SQLAPI\vs2017\x86_64\lib)

9. The connection between sqlapi library,c++ code and database has been made. Now follow the normal compilation process of Microsoft Visual Studio

### For the file created using file system only and saved as "SIS.cpp"

1.It has been created using file system of c++ under the header file of <fstream>

2.Since fstream is a built-in library,no additional library is needed.

3.Any IDE like Microsoft Visual Studio, Codeblocks and others who support C++ compilation can compile the code and run it.

4.Clone the project from the file and compile it following the process of that IDE.


