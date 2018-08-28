#include "config.h"

int createFile(vector<string> &commandSplit)
{
	//struct stat fileStat,fileStat1;
	char *create_argument;
    for(unsigned i=1;i<commandSplit.size();i++)
    {
    	create_argument= new char[commandSplit[i].length()+1];
    	strcpy(create_argument,commandSplit[i].c_str());
    	open(create_argument, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
    }
    return 0;
}