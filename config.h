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
int navigate(int n,char* path,struct dirent **namelist,struct termios newrsettings,struct termios initialrsettings,string root);
int commandMode(int);
int deleteFile(vector<string> &commandSplit);
int createFile(vector<string> &commandSplit);
int createDir(vector<string> &commandSplit);
int deleteDir(vector<string> &commandSplit);
void MoveCursor(int,int);
