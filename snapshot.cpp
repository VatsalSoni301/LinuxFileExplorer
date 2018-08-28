#include "config.h"

vector<string> findf;

int snapShot(vector<string> &commandSplit)
{
	char *create_argument= new char[commandSplit[2].length()+1];
	strcpy(create_argument,commandSplit[2].c_str());
	open(create_argument, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IXOTH);
	findf.push_back(commandSplit[1]);
	findall(commandSplit[1]);
	
    ofstream newfile;
  	newfile.open(create_argument);
  	for(unsigned i=0;i<findf.size();i++)
  	{
  		newfile<<findf[i]<<endl;
  	}
  	newfile.close();
	return 0;
}

void findall(string rm)
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
			findf.push_back(path);
			findall(path);
		}
		else
		{
			if(string(namelist[i]->d_name)!="." && string(namelist[i]->d_name)!="..")
				findf.push_back(path);
		}
	}
}