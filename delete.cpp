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
	
    status = remove("abc.txt");
    
    if(status!=0)
    {
        printf("Unable to delete the filen");
        perror("Error");
    }

	exit(0);
}