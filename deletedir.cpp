#include "config.h"
vector<string> deletefilesfolders;
vector<string> deleteDir(vector<string> &commandSplit)
{
	int status;
    char *remove_argument;
    deletefilesfolders.clear();
    for(unsigned i=1;i<commandSplit.size();i++)
    {
    	remove_argument= new char[commandSplit[i].length()+1];
    	strcpy(remove_argument,commandSplit[i].c_str());
    	DIR *d;
    	d=opendir(remove_argument);
    	if(d)
    	{
    		status = rmdir(remove_argument);
		    if(status!=0)
		    {
		        deletefilesfolders.push_back(commandSplit[i]);
		        deleteall(commandSplit[i]);
		    }
    	}
    	else
    		cout<<endl<<"No such directory exist"<<endl;  
    }
    /*for(unsigned i=0;i<deletefilesfolders.size();i++)
    {
    	cout<<"***"<<deletefilesfolders[i]<<"***"<<endl;
    }
    char x;
    cin>>x;*/
	return deletefilesfolders;
}

void deleteall(string rm)
{
	struct dirent **namelist;
	int i;
	struct stat statObj;
	string path;
	char *rm1=new char[rm.length()+1];
	strcpy(rm1,rm.c_str());
	char *rm2;
	int total = scandir(rm1,&namelist, NULL,alphasort);

	for(i=0;i<total;i++)
	{
		path=rm+"/"+namelist[i]->d_name;
		rm2=new char[path.length()+1];
		strcpy(rm2,path.c_str());
		//stat(rm2,&statObj);
		if(stat(rm2,&statObj) < 0)   
	    {
	        cout<<endl<<"No such directory exist"<<endl;
	        //return 1;
	    } 
		if(S_ISDIR(statObj.st_mode) && string(namelist[i]->d_name)!="." && string(namelist[i]->d_name)!="..")
		{
			//int f=current.find_last_of("/\\");
	    	//current=current.substr(0,f);
			//path=rm+"/"+namelist[i]->d_name;
			deletefilesfolders.push_back(path);
			deleteall(path);
		}
		else
		{
			if(string(namelist[i]->d_name)!="." && string(namelist[i]->d_name)!="..")
				deletefilesfolders.push_back(path);
		}
	}
}