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
using namespace std;

int fileInfo(char*,char*);
int navigate(int n,char* path,struct dirent **namelist,struct termios newrsettings,string);