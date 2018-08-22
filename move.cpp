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
	struct stat fileStat;
    
	char block[1024];
	int in, out;
	int nread;
	in = open("abc.txt", O_RDONLY);
	out = open("abc1.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while((nread = read(in,block,sizeof(block))) > 0)
		write(out,block,nread);

	if(stat("abc.txt",&fileStat) < 0)    
        return 1;

    if(stat("/another/abc.txt",&fileStat1) < 0)    
        return 1;

    int status=chown("/another/abc.txt", fileStat.st_uid, fileStat.st_gid);
    if(status!=0)
        cout<<"Error";

    status=chmod("/another/abc.txt", fileStat.st_mode);
    if(status!=0)
        cout<<"Error";

    status = remove("abc.txt");
    
    if(status!=0)
    {
        printf("Unable to delete the filen");
        perror("Error");
    }

	exit(0);
}