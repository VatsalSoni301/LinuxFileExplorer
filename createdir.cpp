#include "config.h"

int createDir(vector<string> &commandSplit)
{
	//struct stat fileStat,fileStat1;
	char *create_dir_argument;
    for(unsigned i=1;i<commandSplit.size();i++)
    {
    	create_dir_argument= new char[commandSplit[i].length()+1];
    	strcpy(create_dir_argument,commandSplit[i].c_str());
    	int status= mkdir(create_dir_argument, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
    	if(status!=0)
	    {
	        printf("Unable to create directory");
	        perror("Error");
	    }
    }
    return 0;
}