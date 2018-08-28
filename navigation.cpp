#include "config.h"

int row=1,col=0,cur_cursor=1,n;
struct dirent **namelist;
#define esc 27
#define pos() printf("%c[%d;%dH",esc,row,col)
#define pos1(point) printf("%c[%d;%dH",esc,point,col)
#define cls printf("\033[H\033[J")

int navigate(int n,char* path,struct dirent **namelist1,struct termios newrsettings,struct termios initialrsettings,string root)
{
	char ch;
	stack<string> backstk,forstk;	//backward stack and forward stack
	namelist=namelist1;
	struct winsize w;	// To get terminal property
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	string current=root,display="Normal Mode";	//current string to store current directory and root for root directory
	backstk.push(root);
	do
	{
		int last_cursor_point=w.ws_row;
		pos1(last_cursor_point);
		cout<<display;
		pos();
		ch=cin.get();	// when user press key like up/down/left/right/enter/backspace/h
	    if(ch==27)
	    {
	    	ch=cin.get();
            ch=cin.get();
            if(ch=='A')   // If up arrow key 
            {
                --row;
                if(row>=1)    // If cursor is not present at first position
                    pos();	// set cursor position
                else if(cur_cursor>1 && row<1) // If cursor is at first position and current is not at first window.
                {
                	cls;	// clear screen
                	cur_cursor--;	//set window position
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
		            //printDirectoryList(current,root);
		            row=1;
		            pos();	//set cursor position
                }
                else		// If cursor is at first position and current window is first only.
                	row=1;
                //cout<<row<<"  "<<cur_cursor;
            }
            else if(ch=='B')  // If down arrow key 
            {
            	
    			//printf ("lines %d\n", w.ws_row);	Terminal height
    			//printf ("columns %d\n", w.ws_col);	Terminal width
                row++;
                if(cur_cursor+row<=n+1 && row<=w.ws_row-1)  // if cursor is not at last position
                	pos();
                else if(row>w.ws_row-1 && cur_cursor+row<=n+1) // if cursor is at last position and cursor is not at last window.
                {
                	cls;	//clear screen
                	//printDirectoryList(current,root);
                	if(root==current)
		            {
		            	path=new char[root.length()+1];
		            	strcpy(path,root.c_str());
		            	int n1;
		            	n = scandir(path, &namelist, NULL,alphasort);//store all files and dirctories into namelist from specified path
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
		            	n = scandir(path, &namelist, NULL,alphasort);//store all files and dirctories into namelist from specified path
		            	if(n<=w.ws_row-2)
		            		n1=n-1;
		            	else
		            		n1=w.ws_row-2;
		            	for(int i=cur_cursor;i<=cur_cursor+n1 && i<n;i++)
		            	{		
		            		fileInfo(path,namelist[i]->d_name);
		            	}
		            }
                	cur_cursor++;	//set window position
                	row--;
                	pos();	//set cursor position
                }
                else	// if cursor is at last position and also at last window.
                	row--;
            }
            else if(ch=='C')  // If right arrow key then DS
            {
                if(forstk.size()>=1)
             	{
             		backstk.push(forstk.top());
             		current=forstk.top();
             		cls;	// clear screen
             		forstk.pop();
             		
	    			//char *root1=new char[s.length()+1];
	    			//strcpy(root1,s.c_str());
	    			//n = scandir(root1, &namelist, NULL,alphasort);
            		printDirectoryList(current,root);	// Print directory and files
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
	    			//char *root1=new char[s.length()+1];
	    			//strcpy(root1,s.c_str());
	    			//n = scandir(root1, &namelist, NULL,alphasort);	
	    			printDirectoryList(current,root);	// Print directory and files
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
           	printDirectoryList(root,root);	// Print directory and files
            row=1;
            pos();
	    }
	    else if(ch==127)  // If BackSpace key then 
	    {
	    	if(current!=root)
	    	{
	    		while(!forstk.empty())
	    			forstk.pop();
	    		cur_cursor=1;
	    		int f=current.find_last_of("/\\");
	    		current=current.substr(0,f);
		    	cls;
		        backstk.push(current);
	            printDirectoryList(current,root);	// Print directory and files
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
	    	newrsettings.c_lflag &= ~ICANON;	// change settings
    		tcgetattr(fileno(stdin), &newrsettings);
    		commandMode(w.ws_row);
    		printf("%c[2K", 27);
    		cls;
    		row=0;
    		pos();
    		newrsettings=initialrsettings;	
    		newrsettings.c_lflag &= ~ICANON;	// change settings
    		newrsettings.c_lflag &= ~ECHO;
			tcgetattr(fileno(stdin), &newrsettings);	// load newsettings
			printDirectoryList(current,root);		// Print directory and files
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
	        	
	        	temp2=new char[current.length()+1];
	        	backstk.push(current);  	
	        }
	        else
	        {
	        	continue;
	        }
	        strcpy(temp2,current.c_str());
	        if(stat(temp2,&statObj) < 0)   
	        {
	        	cout<<"Error";
	        	//return 1;
	        } 
	        if(!S_ISDIR(statObj.st_mode))
	        {	
	            char *char_array;
	            string s="bash -c 'xdg-open "+ temp +"' 2> /dev/null";
	            char_array=new char[s.length()+1];
	            strcpy(char_array, s.c_str()); 
	            system(char_array);
	            int f=current.find_last_of("/\\");
	    		current=current.substr(0,f);
	    		backstk.pop();
	        }
	        else if(string(namelist[cur_cursor+row-2]->d_name)!=".")
	        {
	            cls;
	            cur_cursor=1;
	            printDirectoryList(current,root);	// Print directory and files
	            row=1;
	            pos();
	        }  
	    }
	}while(ch!=81 && ch!=113);
	return 0;
}

void printDirectoryList(string current,string root) // For printing list of files and directories
{
	char *path=new char[current.length()+1];
    strcpy(path,current.c_str());
    int n1;
    struct winsize w;	//to get terminal property
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
	if(current==root)
    {
    	n = scandir(path, &namelist, NULL,alphasort);	//store all files and dirctories into namelist from specified path
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
    	for(int i=0;i<=n1;i++)
    	{
    		fileInfo(path,namelist[i]->d_name);
    	}
    }
    else
    {
    	n = scandir(path, &namelist, NULL,alphasort);	//store all files and dirctories into namelist from specified path
    	if(n<=w.ws_row-2)
    		n1=n-1;
    	else
    		n1=w.ws_row-2;
    	for(int i=0;i<=n1;i++)
    	{		
    		fileInfo(path,namelist[i]->d_name);
    	}
    }
}