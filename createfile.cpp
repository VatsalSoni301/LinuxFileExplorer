#include "config.h"

int createFile(vector<string> &commandSplit)
{
	//struct stat fileStat,fileStat1;
	string destination=commandSplit[commandSplit.size()-1];
	char *create_argument;
    for(unsigned i=1;i<commandSplit.size()-1;i++)
    {
    	string s=destination+"/"+commandSplit[i];
    	create_argument= new char[s.length()+1];
    	strcpy(create_argument,s.c_str());
    	open(create_argument, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
    }
    return 0;
}