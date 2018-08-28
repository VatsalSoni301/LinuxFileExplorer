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
#include <sys/ioctl.h>
using namespace std;

int fileInfo(char*,char*);
int navigate(int ,char* ,struct dirent** ,struct termios ,struct termios ,string );
int commandMode(int);
int deleteFile(vector<string> &);
int createFile(vector<string> &);
int createDir(vector<string> &);
int deleteDir(vector<string> &);
void printDirectoryList(string ,string );
void MoveCursor(int,int);
