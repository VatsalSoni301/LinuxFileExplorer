//2018201005 Vatsal Soni
#include "config.h"

int createFile(vector<string> &commandSplit)	// It accepts arg from commandFile and create a file
{
	//struct stat fileStat,fileStat1;
	string destination=commandSplit[commandSplit.size()-1];
	char *create_argument;
    for(unsigned i=1;i<commandSplit.size()-1;i++)
    {
    	string s=destination+"/"+commandSplit[i];
    	create_argument= new char[s.length()+1];
    	strcpy(create_argument,s.c_str());
    	int status=open(create_argument, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
    	if(status<0)
        {
    		cout<<endl<<"Invalid Path"<<endl;
        }
    }
    return 0;
}