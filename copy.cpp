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
	struct stat fileStat,fileStat1;
    
	/*int c;
	FILE *in, *out;
	in = fopen("abc.txt","r");
	out = fopen("abc1.txt","w");
	while((c = fgetc(in)) != EOF)
	fputc(c,out);*/

	char block[1024];
	int in, out;
	int nread;
	in = open("abc.txt", O_RDONLY);
	out = open("abc1.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while((nread = read(in,block,sizeof(block))) > 0)
		write(out,block,nread);

	if(stat("abc.txt",&fileStat) < 0)    
        return 1;

    //string lastDate=ctime(&fileStat.st_mtime);
    //cout<<lastDate;

    /*const char *ru=(fileStat.st_mode & S_IRUSR) ? "r" : "-";
    const char *wu=(fileStat.st_mode & S_IWUSR) ? "w" : "-";
    const char *xu=(fileStat.st_mode & S_IXUSR) ? "x" : "-";
    const char *rg=(fileStat.st_mode & S_IRGRP) ? "r" : "-";
    const char *wg=(fileStat.st_mode & S_IWGRP) ? "w" : "-";
    const char *xg=(fileStat.st_mode & S_IXGRP) ? "x" : "-";
    const char *ro=(fileStat.st_mode & S_IROTH) ? "r" : "-";
    const char *wo=(fileStat.st_mode & S_IWOTH) ? "w" : "-";
    const char *xo=(fileStat.st_mode & S_IXOTH) ? "x" : "-";
    cout<<*ru<<*wu<<*xu<<endl;*/


    //cout<<fileStat.st_uid<<" "<<fileStat.st_gid;

   if(stat("abc1.txt",&fileStat1) < 0)    
        return 1;

    //const char *path="abc1.txt";
    
    int status=chown("abc1.txt", fileStat.st_uid, fileStat.st_gid);
    if(status!=0)
    	cout<<"Error";

    status=chmod("abc1.txt", fileStat.st_mode);
    if(status!=0)
    	cout<<"Error";

	exit(0);
}