#include "config.h"

int copyFile(vector<string> &commandSplit)
{
	struct stat fileStat,fileStat1;
    char block[1024];
    int in, out;
    int nread;
    string destination=commandSplit[commandSplit.size()-1];
    string destination_file;
    char *copy_argument;
    for(unsigned i=1;i<commandSplit.size()-1;i++)
    {
        copy_argument=new char[commandSplit[i].length()+1];
        strcpy(copy_argument,commandSplit[i].c_str());
        in = open(copy_argument, O_RDONLY);
        int f=commandSplit[i].find_last_of("/\\");
        commandSplit[i]=commandSplit[i].substr(f+1,commandSplit[i].length());
        destination_file=destination+"/"+commandSplit[i];
        char *paste_argument=new char[destination_file.length()+1];
        strcpy(paste_argument,destination_file.c_str());
        out = open(paste_argument, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
        while((nread = read(in,block,sizeof(block))) > 0)
            write(out,block,nread);

        if(stat(copy_argument,&fileStat) < 0) 
        {
            cout<<"Error";
            //return 1;
        }   

       if(stat(paste_argument,&fileStat1) < 0)    
       {
            cout<<"Error";
            //return 1;
       }

        //const char *path="abc1.txt";
        
        int status=chown(paste_argument, fileStat.st_uid, fileStat.st_gid);
        if(status!=0)
            cout<<"Error";

        status=chmod(paste_argument, fileStat.st_mode);
        if(status!=0)
            cout<<"Error";
    }
	return 0;
}