#include "config.h"

int rename(vector<string> &commandSplit)
{
	char *old=new char[commandSplit[1].length()+1];
	char *_new=new char[commandSplit[2].length()+1];
	strcpy(old,commandSplit[1].c_str());
	strcpy(_new,commandSplit[2].c_str());
   	
   	rename(old,_new);

	return 0;
}