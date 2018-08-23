#include "config.h"

#define esc 27
int row=0,col=0;
#define pos() printf("%c[%d;%dH",esc,row,col)
#define cls printf("\033[H\033[J")

int navigate(int n,char* path,struct dirent **namelist,struct termios newrsettings,string root)
{
	int n1;
	char ch;
	stack<string> rootMapping,backstk,forstk;
	pos();
	do
	{
		ch=cin.get();
	    if(ch==27)
	    {
	    	ch=cin.get();
            ch=cin.get();
            if(ch=='A')   // If up arrow key then cursor --;
            {
                row--;
                if(row>=0)
                    pos();
                else
                    row=0;

            }
            else if(ch=='B')  // If down arrow key then cursor ++;
            {
                row++;
                if(row<=n)
                	pos();
                else
                	row=n;
            }
            else if(ch=='C')  // If right arrow key then DS
            {
                if(forstk.size()>=1)
                {
                	backstk.push(forstk.top());
                	forstk.pop();
                }
            }
            else if(ch=='D')  // If left arrow key then DS
            {
             	if(backstk.size()>=1)
             	{
             		forstk.push(backstk.top());
             		backstk.pop();
             	}   
            }
	    }
	    else if(ch==104 || ch==72)   // If h or H press then open root directory
	    {
	    	strcpy(path,root.c_str());
	    	cls;
	    	row=0;
	    	while(!rootMapping.empty())
	    		rootMapping.pop();
	    	pos();
	    	char *root1=new char[root.length()+1];
	    	strcpy(root1,root.c_str());
	    	n = scandir(root1, &namelist, NULL,alphasort);
            n1=n;
            while (n1--)
            {
            	if(string(namelist[n1]->d_name)!="..")
                	fileInfo(root1,namelist[n1]->d_name);
            }
	    }
	    else if(ch==127)  // If BackSpace key then DS
	    {
	    	if(rootMapping.size()>=1)
	    	{
	    		rootMapping.pop();
		    	cls;
		    	string s;
		    	if(rootMapping.size()==0)
		    		s=root;
		    	else
		        	s=rootMapping.top();
		        path=new char[s.length()+1];
		        strcpy(path,s.c_str());
	            n = scandir(path, &namelist, NULL,alphasort);
	            n1=n;
	            row=0;
	            pos();
	            //cout<<"*****"<<path;
	            while (n1--)
	            {
	            	if(rootMapping.empty())
	            	{
	            		if(string(namelist[n1]->d_name)!="..")
	            			fileInfo(path,namelist[n1]->d_name);
	            	}
	            	else
	                	fileInfo(path,namelist[n1]->d_name);
	            }
	    	}
	    }
	    else if(ch==58)  // If colon(:) then command mode
	    {
	          newrsettings.c_lflag &= ICANON;
	    }
	    else if(ch==10)  // If enter key then open Dir or File
	    {
	        struct stat statObj;
	        string temp="/";
	        string temp1=namelist[n-row]->d_name;
	        temp1=temp+temp1;
	        temp=path;
	        temp=temp+temp1;
	        char *temp2=new char[temp.length()+1];
	        strcpy(temp2,temp.c_str());

	        if(string(namelist[n-row]->d_name)=="..")
	        {
	        	rootMapping.pop();
	        	forstk.push(backstk.top());
	        	backstk.pop();
	        }
	        else if(string(namelist[n-row]->d_name)!=".")
	        {
	        	rootMapping.push(temp);
	        	backstk.push(temp);
	        }

	        if(stat(temp2,&statObj) < 0)   
	        {
	        	cout<<"Err"<<temp2;
	        	return 1;
	        } 
	        if(!S_ISDIR(statObj.st_mode))
	        {
	        	rootMapping.pop();
	            char *char_array;
	            string s="xdg-open ";
	            string s1=temp;   
	            s=s+s1;
	            char_array=new char[s.length()+1];
	            strcpy(char_array, s.c_str()); 
	            system(char_array);
	        }
	        else
	        {
	            cls;
	            string s1="/";
	            string s=path;
	            s1=s+s1;
	            s=namelist[n-row]->d_name;
	            s1=s1+s;
	            path=new char[s1.length()+1];
	            strcpy(path, s1.c_str());
	            n = scandir(path, &namelist, NULL,alphasort);
	            n1=n;
	            row=0;
	            pos();
	            //cout<<"*****"<<path;
	            while (n1--)
	            {
	            	if(rootMapping.empty())
	            	{
	            		if(string(namelist[n1]->d_name)!="..")
	            			fileInfo(path,namelist[n1]->d_name);
	            	}
	            	else
	                	fileInfo(path,namelist[n1]->d_name);
	            }
	        }
	    }

	}while(ch!=81 && ch!=113);
	return 0;
}