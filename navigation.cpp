#include "config.h"

#define esc 27
int row=1,col=0;
#define pos() printf("%c[%d;%dH",esc,row,col)
#define cls printf("\033[H\033[J")

int navigate(int n,char* path,struct dirent **namelist,struct termios newrsettings,string root)
{
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
                if(row>=1)
                    pos();
                else
                	row=1;
                //cout<<row;
            }
            else if(ch=='B')  // If down arrow key then cursor ++;
            {
                row++;
                if(row<=n)
                	pos();
                else
                {
                	row=1;
                	pos();
                }
                //cout<<n;
            }
            else if(ch=='C')  // If right arrow key then DS
            {
                /*if(forstk.size()>=1)
             	{
             		backstk.push(forstk.top());
             		string s=forstk.top();
             		cls;
             		forstk.pop();
	    			row=1;
	    			pos();
	    			char *root1=new char[s.length()+1];
	    			strcpy(root1,s.c_str());
	    			n = scandir(root1, &namelist, NULL,alphasort);
            		n1=n;
            		while (n1--)
            		{
            			if(string(namelist[n1]->d_name)!="..")
                			fileInfo(root1,namelist[n1]->d_name);
            		}
             	}*/
            }
            else if(ch=='D')  // If left arrow key then DS
            {
             	/*if(backstk.size()>=1)
             	{
             		forstk.push(backstk.top());
             		string s=backstk.top();
             		cls;
             		backstk.pop();
	    			
	    			char *root1=new char[s.length()+1];
	    			strcpy(root1,s.c_str());
	    			n = scandir(root1, &namelist, NULL,alphasort);
            		// need to implement
            		row=1;
	    			pos();
             	}*/  
            }
	    }
	    else if(ch==104 || ch==72)   // If h or H press then open root directory
	    {
	    	
	    	cls;
	    	//if(!rootMapping.empty())
	    		//backstk.push(rootMapping.top());
	    	while(!rootMapping.empty())
	    		rootMapping.pop();
	   
	    	char *root1=new char[root.length()+1];
	    	strcpy(root1,root.c_str());
	    	n = scandir(root1, &namelist, NULL,alphasort);
            
        	for(int i=0;i<n-1;i++)
        	{
        		if(string(namelist[i]->d_name)!="..")
        			fileInfo(root1,namelist[i]->d_name);
        		else
            	{
            		int x=i;
        			while(x<n-1)
        			{
            			namelist[x]=namelist[x+1];
            			x++;
        			}
        			i--;
            	}
        	}
        	n--;
           
            row=1;
            pos();
	    }
	    else if(ch==127)  // If BackSpace key then DS
	    {
	    	if(rootMapping.size()>=1)
	    	{
	    		//backstk.push(rootMapping.top());
	    		rootMapping.pop();
		    	cls;
		    	string s;
		    	if(rootMapping.empty())
		    		s=root;
		    	else
		        	s=rootMapping.top();
		        path=new char[s.length()+1];
		        strcpy(path,s.c_str());
	            n = scandir(path, &namelist, NULL,alphasort);
	            if(rootMapping.empty())
	            {
	            	for(int i=0;i<n-1;i++)
	            	{
	            		if(string(namelist[i]->d_name)!="..")
	            			fileInfo(path,namelist[i]->d_name);
	            		else
	                	{
	                		int x=i;
                			while(x<n-1)
                			{
                    			namelist[x]=namelist[x+1];
                    			x++;
                			}
                			i--;
	                	}
	            	}
	            	n--;
	            }
	            else
	            {
	            	for(int i=0;i<n;i++)
	            	{		
	            		fileInfo(path,namelist[i]->d_name);
	            	}
	            }
	            row=1;
	            pos();
	    	}
	    }
	    else if(ch==58)  // If colon(:) then command mode
	    {
	          newrsettings.c_lflag &= ICANON;
	    }
	    else if(ch==10)  // If enter key then open Dir or File
	    {
	        struct stat statObj;
	        
	        string temp,temp1;
	        char *temp2;
	        if(string(namelist[row-1]->d_name)=="..")
	        {
	        	//backstk.push(rootMapping.top());
	        	rootMapping.pop();
	        	if(rootMapping.empty())
	        		temp=root;
	        	else
	        		temp=rootMapping.top();
	        	
	        	temp2=new char[temp.length()+1];
	        }
	        else if(string(namelist[row-1]->d_name)!=".")
	        {
	        	
	        	temp="/";
	        	temp1=namelist[row-1]->d_name;
	        	temp1=temp+temp1;
	        	if(rootMapping.empty())
	        		temp=root;
	        	else
	       			temp=rootMapping.top();
	       		//backstk.push(temp);
	        	temp=temp+temp1;
	        	temp2=new char[temp.length()+1];
	        	rootMapping.push(temp);
	        }
	        else
	        	continue;
	        strcpy(temp2,temp.c_str());
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
	        else if(string(namelist[row-1]->d_name)!=".")
	        {
	            cls;
	            /*string s1="/";
	            string s=path;
	            s1=s+s1;
	            s=namelist[row-1]->d_name;
	            s1=s1+s;
	            
	            path=new char[s1.length()+1];
	            strcpy(path, s1.c_str());*/
	            n = scandir(temp2, &namelist, NULL,alphasort);
	            
	            //cout<<"*****"<<path;
	            if(rootMapping.empty())
	            {
	            	for(int i=0;i<n-1;i++)
	            	{
	            		if(string(namelist[i]->d_name)!="..")
	            			fileInfo(temp2,namelist[i]->d_name);
	            		else
	                	{
	                		int x=i;
                			while(x<n-1)
                			{
                    			namelist[x]=namelist[x+1];
                    			x++;
                			}
                			i--;
	                	}
	            	}
	            	n--;
	            }
	            else
	            {
	            	for(int i=0;i<n;i++)
	            	{		
	            		fileInfo(temp2,namelist[i]->d_name);
	            	}
	            }
	            row=1;
	            pos();
	        }
	    }

	}while(ch!=81 && ch!=113);
	return 0;
}