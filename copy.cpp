#include "config.h"

int copyFile(vector<string> &commandSplit)
{
    string destination=commandSplit[commandSplit.size()-1];
    struct stat statObj;
    for(unsigned i=1;i<commandSplit.size()-1;i++)
    {
        string source=commandSplit[i];
        char *ss=new char[source.length()+1];
        strcpy(ss,source.c_str());
        if(stat(ss,&statObj) < 0)   
        {
            cout<<endl<<"No such directory exist"<<endl;
            //return 1;
        }

        if(S_ISDIR(statObj.st_mode))
        {
            int f=source.find_last_of("/\\");
            string source1=source.substr(f+1,source.length());
            string s=destination+"/"+source1;
            char *create_dir_argument=new char[s.length()+1];
            strcpy(create_dir_argument,s.c_str());
            mkdir(create_dir_argument, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
            string destination1=destination+"/"+source1;
            copyall(source,destination1);
        }
        else
        {
            int f=commandSplit[i].find_last_of("/\\");
            commandSplit[i]=commandSplit[i].substr(f+1,commandSplit[i].length());
            string destination_file=destination+"/"+commandSplit[i];
            copyFile1(source,destination_file);   
        }
    }
    return 0;
}

int copyFile1(string source,string destination)
{
	struct stat fileStat,fileStat1;
    char block[1024];
    int in, out;
    int nread;
    char *copy_argument;
    
    copy_argument=new char[source.length()+1];
    strcpy(copy_argument,source.c_str());
    in = open(copy_argument, O_RDONLY);
    char *paste_argument=new char[destination.length()+1];
    strcpy(paste_argument,destination.c_str());
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
    {
        cout<<"Error";
    }

    status=chmod(paste_argument, fileStat.st_mode);
    if(status!=0)
    {
        cout<<"Error";
    }
    
	return 0;
}

void copyall(string source,string destination)
{   
    char* sourceconst=new char[source.length()+1];
    strcpy(sourceconst,source.c_str());
    struct dirent **namelist;
    int total = scandir(sourceconst,&namelist, NULL,alphasort);
    //cout<<source;
    struct stat statObj;
    for(int i=0;i<total;i++)
    {
        string ts=source+"/"+namelist[i]->d_name;
        char* ts1=new char[ts.length()+1];
        strcpy(ts1,ts.c_str());
        if(stat(ts1,&statObj) < 0)   
        {
            cout<<endl<<"No such directory exist"<<endl;
            //return 1;
        } 
        //cout<<"**"<<sourceconst<<"**";
        if(S_ISDIR(statObj.st_mode) && string(namelist[i]->d_name)!="." && string(namelist[i]->d_name)!="..")
        {
            
            string s=destination+"/"+namelist[i]->d_name;
            char *create_dir_argument=new char[s.length()+1];
            strcpy(create_dir_argument,s.c_str());
            mkdir(create_dir_argument, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);

            copyall(source+"/"+namelist[i]->d_name,destination+"/"+namelist[i]->d_name);
        }
        else
        {
            //cout<<"FF"<<namelist[i]->d_name<<"FF";
            if(string(namelist[i]->d_name)!="." && string(namelist[i]->d_name)!="..")
                copyFile1(source+"/"+namelist[i]->d_name,destination+"/"+namelist[i]->d_name);
        }
    }
    
}