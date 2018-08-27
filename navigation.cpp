#include "config.h"

#define esc 27
int row=1,col=0,cur_cursor=1;
#define pos() printf("%c[%d;%dH",esc,row,col)
#define pos1(point) printf("%c[%d;%dH",esc,point,col)
#define cls printf("\033[H\033[J")

int navigate(int n,char* path,struct dirent **namelist,struct termios newrsettings,struct termios initialrsettings,string root)
{
	char ch;
	stack<string> backstk,forstk;
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	pos();
	string current=root,display="Normal Mode";
	backstk.push(root);
	do
	{
		int last_cursor_point=w.ws_row;
		pos1(last_cursor_point);
		cout<<display;
		pos();
		ch=cin.get();
	    if(ch==27)
	    {
	    	ch=cin.get();
            ch=cin.get();
            if(ch=='A')   // If up arrow key then cursor --;
            {
                --row;
                if(row>=1)
                    pos();
                else if(cur_cursor>1 && row<1)
                {
                	cls;
                	cur_cursor--;
                	if(current==root)
		            {
		            	path=new char[root.length()+1];
		            	strcpy(path,root.c_str());
		            	int n1;
		            	n = scandir(path, &namelist, NULL,alphasort);
		            	if(n<=w.ws_row-2)
		            		n1=n-2;
		            	else
		            		n1=w.ws_row-2;
		            	for(int i=0;i<n-1;i++)
		            	{
		            		if(string(namelist[i]->d_name)=="..")
		            		{
		                		int x=i;
	                			while(x<n-1)
	                			{
	                    			namelist[x]=namelist[x+1];
	                    			x++;
	                			}
	                			i--;
	                			break;
		                	}
		            	}
		            	n--;
		            	for(int i=cur_cursor-1;i<=cur_cursor+n1-1 && i<n;i++)
		            	{
		            		fileInfo(path,namelist[i]->d_name);
		            	}
		            	
		            }
		            else
		            {
		            	string s=current;
		            	path=new char[s.length()+1];
		            	strcpy(path,s.c_str());	
		            	int n1;
		            	n = scandir(path, &namelist, NULL,alphasort);
		            	if(n<=w.ws_row-2)
		            		n1=n-1;
		            	else
		            		n1=w.ws_row-2;
		            	for(int i=cur_cursor-1;i<=cur_cursor+n1-1 && i<n;i++)
		            	{		
		            		fileInfo(path,namelist[i]->d_name);
		            	}
		            }
		            row=1;
		            pos();
                }
                else
                	row=1;
                //cout<<row<<"  "<<cur_cursor;
            }
            else if(ch=='B')  // If down arrow key then cursor ++;
            {
            	
    			//printf ("lines %d\n", w.ws_row);
    			//printf ("columns %d\n", w.ws_col);
    			
                row++;
                
                if(cur_cursor+row<=n+1 && row<=w.ws_row-1)
                	pos();
                else if(row>w.ws_row-1 && cur_cursor+row<=n+1)
                {
                	cls;
                	if(root==current)
		            {
		            	path=new char[root.length()+1];
		            	strcpy(path,root.c_str());
		            	int n1;
		            	n = scandir(path, &namelist, NULL,alphasort);
		            	if(n<=w.ws_row-2)
		            		n1=n-2;
		            	else
		            		n1=w.ws_row-2;
		            	for(int i=0;i<n-1;i++)
		            	{
		            		if(string(namelist[i]->d_name)=="..")
		            		{
		                		int x=i;
	                			while(x<n-1)
	                			{
	                    			namelist[x]=namelist[x+1];
	                    			x++;
	                			}
	                			i--;
	                			break;
		                	}
		            	}
		            	n--;
		            	for(int i=cur_cursor;i<=cur_cursor+n1 && i<n;i++)
		            	{
		            		fileInfo(path,namelist[i]->d_name);
		            	}
		            	
		            }
		            else
		            {
		            	string s=current;
		            	path=new char[s.length()+1];
		            	strcpy(path,s.c_str());	
		            	int n1;
		            	n = scandir(path, &namelist, NULL,alphasort);
		            	if(n<=w.ws_row-2)
		            		n1=n-1;
		            	else
		            		n1=w.ws_row-2;
		            	for(int i=cur_cursor;i<=cur_cursor+n1 && i<n;i++)
		            	{		
		            		fileInfo(path,namelist[i]->d_name);
		            	}
		            }

                	cur_cursor++;
                	
                	row--;
                	pos();

                }
                else
                	row--;
            }
            else if(ch=='C')  // If right arrow key then DS
            {
                if(forstk.size()>=1)
             	{
             		backstk.push(forstk.top());
             		current=forstk.top();
             		string s=forstk.top();
             		cls;
             		forstk.pop();
             		
	    			char *root1=new char[s.length()+1];
	    			strcpy(root1,s.c_str());
	    			n = scandir(root1, &namelist, NULL,alphasort);
	    			if(current==root)
	    			{
	    				int n1;
		            	if(n<=w.ws_row-2)
		            		n1=n-2;
		            	else
		            		n1=w.ws_row-2;
		            	for(int i=0;i<n-1;i++)
		            	{
		            		if(string(namelist[i]->d_name)=="..")
		            		{
		                		int x=i;
	                			while(x<n-1)
	                			{
	                    			namelist[x]=namelist[x+1];
	                    			x++;
	                			}
	                			i--;
	                			break;
		                	}
		            	}
		            	n--;
		            	for(int i=0;i<=n1 && i<n;i++)
		            	{
		            		fileInfo(root1,namelist[i]->d_name);
		            	}
	    			}
	    			else
	    			{
	    				int n1;
	            		if(n<=w.ws_row-2)
	            			n1=n-1;
	            		else
	            			n1=w.ws_row-2;
	            		for(int i=0;i<=n1;i++)
	            		{		
	            			fileInfo(root1,namelist[i]->d_name);
	            		}	
	    			}
            		
            		cur_cursor=1;
            		row=1;
            		pos();
             	}
            }
            else if(ch=='D')  // If left arrow key then DS
            {
             	if(backstk.size()>=2)
             	{
             		forstk.push(backstk.top());
             		cls;
             		backstk.pop();
	    			string s=backstk.top();
	    			current=s;
	    			char *root1=new char[s.length()+1];
	    			strcpy(root1,s.c_str());
	    			n = scandir(root1, &namelist, NULL,alphasort);
	    			if(current==root)
	    			{
	    				int n1;
		            	if(n<=w.ws_row-2)
		            		n1=n-2;
		            	else
		            		n1=w.ws_row-2;
		            	for(int i=0;i<n-1;i++)
		            	{
		            		if(string(namelist[i]->d_name)=="..")
		            		{
		                		int x=i;
	                			while(x<n-1)
	                			{
	                    			namelist[x]=namelist[x+1];
	                    			x++;
	                			}
	                			i--;
	                			break;
		                	}
		            	}
		            	n--;
		            	for(int i=0;i<=n1 && i<n;i++)
		            	{
		            		fileInfo(root1,namelist[i]->d_name);
		            	}
	    			}
	    			else
	    			{
	    				int n1;
	            		if(n<=w.ws_row-2)
	            			n1=n-1;
	            		else
	            			n1=w.ws_row-2;
	            		for(int i=0;i<=n1;i++)
	            		{		
	            			fileInfo(root1,namelist[i]->d_name);
	            		}
	    			}

            		cur_cursor=1;
            		row=1;
            		pos();
             	}
            }
	    }
	    else if(ch==104 || ch==72)   // If h or H press then open root directory
	    {
	    	
	    	cls;
	    	cur_cursor=1;
	    	backstk.push(root);

	    	while(!forstk.empty()){
	    		forstk.pop();
	    	}

	   		current=root;
	    	char *root1=new char[root.length()+1];
	    	strcpy(root1,root.c_str());
	    	n = scandir(root1, &namelist, NULL,alphasort);
            
        	int n1;
        	if(n<=w.ws_row-2)
        		n1=n-2;
        	else
        		n1=w.ws_row-2;
        	for(int i=0;i<n-1;i++)
        	{
        		if(string(namelist[i]->d_name)=="..")
        		{
            		int x=i;
        			while(x<n-1)
        			{
            			namelist[x]=namelist[x+1];
            			x++;
        			}
        			i--;
        			break;
            	}
        	}
        	n--;
        	for(int i=0;i<=n1 && i<n;i++)
        	{
        		fileInfo(root1,namelist[i]->d_name);
        	}
           
            row=1;
            pos();
	    }
	    else if(ch==127)  // If BackSpace key then DS
	    {
	    	if(current!=root)
	    	{
	    		while(!forstk.empty())
	    			forstk.pop();
	    		cur_cursor=1;
	    		int f=current.find_last_of("/\\");
	    		current=current.substr(0,f);
		    	cls;
		    	string s;
		    	s=current;
		        backstk.push(s);
		        path=new char[s.length()+1];
		        strcpy(path,s.c_str());
	            n = scandir(path, &namelist, NULL,alphasort);
	            if(s==root)
	            {
	            	
	            	int n1;
	            	if(n<=w.ws_row-2)
	            		n1=n-2;
	            	else
	            		n1=w.ws_row-2;
	            	for(int i=0;i<n-1;i++)
	            	{
	            		if(string(namelist[i]->d_name)=="..")
	            		{
	                		int x=i;
                			while(x<n-1)
                			{
                    			namelist[x]=namelist[x+1];
                    			x++;
                			}
                			i--;
                			break;
	                	}
	            	}
	            	n--;
	            	for(int i=0;i<=n1 && i<n;i++)
	            	{
	            		fileInfo(path,namelist[i]->d_name);
	            	}
	            	
	            }
	            else
	            {
	            	int n1;
	            	if(n<=w.ws_row-2)
	            		n1=n-1;
	            	else
	            		n1=w.ws_row-2;
	            	for(int i=0;i<=n1;i++)
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
	    	row=w.ws_row;
	    	
	    	pos();
	    	printf("%c[2K", 27);
	    	cout<<":";
	    	//newrsettings.c_lflag &= ECHO;
	    	newrsettings=initialrsettings;
	    	newrsettings.c_lflag &= ~ICANON;
    		tcgetattr(fileno(stdin), &newrsettings);
    		commandMode(w.ws_row);
    		printf("%c[2K", 27);
    		row=0;
    		pos();
    		newrsettings=initialrsettings;
    		newrsettings.c_lflag &= ~ICANON;
    		newrsettings.c_lflag &= ~ECHO;
			tcgetattr(fileno(stdin), &newrsettings);		
	    }
	    else if(ch==10)  // If enter key then open Dir or File
	    {
	        struct stat statObj;
	        
	        string temp,temp1;
	        char *temp2;
	        if(string(namelist[cur_cursor+row-2]->d_name)=="..")
	        {
	        	while(!forstk.empty())
	    			forstk.pop();
	    		
	    		int f=current.find_last_of("/\\");
	    		current=current.substr(0,f);
	        	temp=current;
	        	backstk.push(temp);
	        	temp2=new char[temp.length()+1];
	        }
	        else if(string(namelist[cur_cursor+row-2]->d_name)!=".")
	        {
	        	
	        	temp="/";
	        	temp1=namelist[cur_cursor+row-2]->d_name;
	        	temp1=temp+temp1;
	        	temp=current+temp1;
	       		current=temp;
	       		
	       		while(!forstk.empty())
	    			forstk.pop();
	        	
	        	temp2=new char[temp.length()+1];
	        	
	        	backstk.push(temp);
	        }
	        else
	        {
	        	continue;
	        }
	        strcpy(temp2,temp.c_str());
	        if(stat(temp2,&statObj) < 0)   
	        {
	        	cout<<"Error";
	        	//return 1;
	        } 
	        if(!S_ISDIR(statObj.st_mode))
	        {
	        	
	            char *char_array;
	            //string s1="xdg-mime"
	            string s="bash -c 'xdg-open "+ temp +"' 2> /dev/null";
	            //cout<<s<<"***";
	            //string s="xdg-open ";
	            //string s1=temp;   
	            //s=s+s1;
	            char_array=new char[s.length()+1];
	            strcpy(char_array, s.c_str()); 
	            system(char_array);
	            int f=current.find_last_of("/\\");
	    		current=current.substr(0,f);
	        }
	        else if(string(namelist[cur_cursor+row-2]->d_name)!=".")
	        {
	        	
	            cls;
	            cur_cursor=1;

            	if(root==current)
	            {
	            	int n1;
	            	n = scandir(temp2, &namelist, NULL,alphasort);
	            	if(n<=w.ws_row-2)
	            		n1=n-2;
	            	else
	            		n1=w.ws_row-2;
	            	for(int i=0;i<n-1;i++)
	            	{
	            		if(string(namelist[i]->d_name)=="..")
	            		{
	                		int x=i;
                			while(x<n-1)
                			{
                    			namelist[x]=namelist[x+1];
                    			x++;
                			}
                			i--;
                			break;
	                	}
	            	}
	            	n--;
	            	for(int i=0;i<=n1 && i<n;i++)
	            	{
	            		fileInfo(temp2,namelist[i]->d_name);
	            	}
	            	
	            }
	            else
	            {
	            	int n1;
	            	n = scandir(temp2, &namelist, NULL,alphasort);
	            	if(n<=w.ws_row-2)
	            		n1=n-1;
	            	else
	            		n1=w.ws_row-2;
	            	for(int i=0;i<=n1;i++)
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