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

int fileInfo(char*,char*);
int navigate(int ,char* ,struct dirent** ,struct termios ,struct termios ,string );
string commandMode(int,string,string);
int deleteFile(vector<string> &);
int createFile(vector<string> &);
int createDir(vector<string> &);
vector<string> deleteDir(vector<string> &);
int rename(vector<string> &);
string stringProcess(string fname);
void printDirectoryList(string ,string );
void deleteall(string);
int copyFile(vector<string> &);
int copyFile1(string,string);
void copyall(string,string);
int moveFile(vector<string> &);
int snapShot(vector<string> &);
void findall(string);
void findA(string ,string );
vector<string> search(vector<string> &);
void MoveCursor(int,int);
