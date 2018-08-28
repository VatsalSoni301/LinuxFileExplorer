#include "config.h"

int deleteDir(vector<string> &commandSplit)
{
	int status;
    char *remove_argument;
    for(unsigned i=1;i<commandSplit.size();i++)
    {
    	remove_argument= new char[commandSplit[i].length()+1];
    	strcpy(remove_argument,commandSplit[i].c_str());
    	status = rmdir(remove_argument);
	    if(status!=0)
	    {
	        printf("Unable to delete directory");
	        perror("Error");
	    }
    }
	return 0;
}