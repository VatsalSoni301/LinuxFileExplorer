//2018201005 Vatsal Soni
#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<bits/stdc++.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<termios.h>
#include<pwd.h>
#include<grp.h>
#include<fstream>
#include <sys/ioctl.h>
using namespace std;
extern vector<string> searchResult;	// For storing search result

int fileInfo(char*,char*,int);	// To display information about file
int navigate(int ,struct dirent** ,struct termios ,struct termios ,string ); //For normal mode up/down/left/right etc..handling
string commandMode(int,string,string); // To get into command mode
int deleteFile(vector<string> &);	// For file deletion
int createFile(vector<string> &);	// For file creation
int createDir(vector<string> &);	// For directory creation
vector<string> deleteDir(vector<string> &);	// For directory deletion
int rename(vector<string> &);	// For rename file/directory
string stringProcess(string fname);	// For processing string for relative path adjusment
void printDirectoryList(string ,string );	// For print directory/file list 
void deleteall(string);	// For delete directory recursion function
int copyFile(vector<string> &);	// For copy file to get arguments
int copyFile1(string,string);	// For copy file
void copyall(string,string);	// For copy directory recursive
int moveFile(vector<string> &);	// For move file
int snapShot(vector<string> &);	// For snapshot
void findall(string);	// For snapshot recursive function
void findA(string ,string );	// For search recursive function
vector<string> search(vector<string> &); // For search function to take arguments
void MoveCursor(int,int);	// For cursor movement
void printsearch();	// For printing search result
