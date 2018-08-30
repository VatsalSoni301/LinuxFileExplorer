//2018201005 Vatsal Soni
#include "config.h"

vector<string> findk;
vector<string> search(vector<string> &commandSplit)	// It accepts arg from commandFile and return result.
{
	string key=commandSplit[1];
	string from=commandSplit[2];
	findk.clear();
	
	findA(from,key);
	/*for(unsigned i=0;i<findk.size();i++)
	{
		cout<<findk[i];
	}*/
	return findk;
}
void findA(string source,string key)	// It recursively go till depth and store all matches result in vector.
{
	char *path=new char[source.length()+1];
	strcpy(path,source.c_str());
	struct dirent **namelist;
	struct stat statObj;
	int total=scandir(path,&namelist,NULL,alphasort);
	for(int i=0;i<total;i++)
	{
		string new_path=source+"/"+namelist[i]->d_name;
		char *const_new_path=new char[new_path.length()+1];
		strcpy(const_new_path,new_path.c_str());
		if(stat(const_new_path,&statObj) < 0)   
	    {
	        cout<<endl<<"No such directory exist"<<endl;
	        //return 1;
	    } 
		if(S_ISDIR(statObj.st_mode) && string(namelist[i]->d_name)!="." && string(namelist[i]->d_name)!="..")
		{
			if(string(namelist[i]->d_name)==key)
				findk.push_back(new_path);
			findA(new_path,key);
		}
		else
		{
			if(string(namelist[i]->d_name)!="." && string(namelist[i]->d_name)!="..")
			{
				if(string(namelist[i]->d_name)==key)
					findk.push_back(new_path);
			}
		}
	}
}