#include "config.h"

int createDir(vector<string> &commandSplit)
{
	//struct stat fileStat,fileStat1;
	string destination=commandSplit[commandSplit.size()-1];
	char *create_dir_argument;
    for(unsigned i=1;i<commandSplit.size()-1;i++)
    {
    	string s=destination+"/"+commandSplit[i];
    	create_dir_argument= new char[s.length()+1];
    	strcpy(create_dir_argument,s.c_str());
    	int status= mkdir(create_dir_argument, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
    	if(status!=0)
	    {
	        printf("Unable to create directory");
	        perror("Error");
	    }
    }
    return 0;
}