//2018201005 Vatsal Soni
#include "config.h"

int deleteFile(vector<string> &commandSplit)	// It accepts arg from commandFile and delete file/files.
{
    char *remove_argument;
    for(unsigned i=1;i<commandSplit.size();i++)
    {
    	remove_argument= new char[commandSplit[i].length()+1];
    	strcpy(remove_argument,commandSplit[i].c_str());
    	int status=remove(remove_argument);
	    if(status!=0)
	    {
	        cout<<endl<<"No such file exists"<<endl;
	    }
    }
    
	return 0;
}