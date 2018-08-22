#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<bits/stdc++.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
using namespace std;
int main()
{
	
    int status=rename(old1,new1);
    if(status!=0)
    	cout<<"Error";

	exit(0);
}