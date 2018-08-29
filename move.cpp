#include "config.h"

int moveFile(vector<string> &commandSplit)
{
    string destination=commandSplit[commandSplit.size()-1];
    vector<string> v;
	for(unsigned i=1;i<commandSplit.size()-1;i++)
    {
        v.clear();
        v.push_back("copy");
        v.push_back(commandSplit[i]);
        v.push_back(destination);
        copyFile(v);
        struct stat statObj;
        char *ss=new char[commandSplit[i].length()+1];
        strcpy(ss,commandSplit[i].c_str());
        if(stat(ss,&statObj) < 0)   
        {
            cout<<endl<<"No such directory exist"<<endl;
            //return 1;
        } 
        if(S_ISDIR(statObj.st_mode))
        {
            v.clear();
            v.push_back("delete");
            v.push_back(commandSplit[i]);
            vector<string> ans=deleteDir(v);
            if(ans.size()>0)
            {
                //cout<<endl<<endl;
                for(int j=ans.size()-1;j>=0;j--)
                {
                    //cout<<vc[i]<<endl;
                    char *p=new char[ans[j].length()+1];
                    strcpy(p,ans[j].c_str());
                    struct stat statObj;
                    stat(p,&statObj);
                    if(S_ISDIR(statObj.st_mode))
                    {
                        vector<string> v;
                        v.clear();
                        v.push_back("abc");
                        v.push_back(ans[j]);
                        deleteDir(v);
                    }
                    else
                    {
                        vector<string> v;
                        v.clear();
                        v.push_back("abc");
                        v.push_back(ans[j]);
                        deleteFile(v);
                    }
                }
            }
        }
        else
        {
            v.clear();
            v.push_back("delete");
            v.push_back(commandSplit[i]);
            deleteFile(v);
        }
    }
    return 0;
}