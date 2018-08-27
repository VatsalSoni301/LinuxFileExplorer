#include "config.h"

int deleteFile(vector<string> &commandSplit)
{
	int status;
    char *remove_argument;
    for(unsigned i=1;i<commandSplit.size();i++)
    {
    	remove_argument= new char[commandSplit[i].length()+1];
    	strcpy(remove_argument,commandSplit[i].c_str());
    	status = remove(remove_argument);
	    if(status!=0)
	    {
	        printf("Unable to delete the filen");
	        perror("Error");
	    }
    }
    
	return 0;
}