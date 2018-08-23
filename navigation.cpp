#include "config.h"

#define esc 27
int row=0,col=0;
#define pos() printf("%c[%d;%dH",esc,row,col)
#define cls printf("%c[2J",esc)

int navigate(int n,char* path,struct dirent **namelist,struct termios newrsettings,string root)
{
	int n1;
	char ch;
	
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
                pos();
            }
            else if(ch=='C')  // If right arrow key then DS
                cout<<"Right";
            else if(ch=='D')  // If left arrow key then DS
                cout<<"Left";
	    }
	    else if(ch==104 || ch==72)   // If h or H press then open root directory
	    {
	    	system("clear");
	    	char *root1=new char[root.length()+1];
	    	strcpy(root1,root.c_str());
	    	n = scandir(root1, &namelist, NULL,alphasort);
            n1=n;
            while (n1--)
            {

                fileInfo(root1,namelist[n1]->d_name);
            }
	    }
	    else if(ch==127)  // If BackSpace key then DS
	        cout<<"Back"; 
	    else if(ch==58)  // If colon(:) then command mode
	          newrsettings.c_lflag &= ICANON;
	    else if(ch==10)  // If enter key then open Dir or File
	    {
	        struct stat statObj;
	        if(stat(namelist[n-row]->d_name,&statObj) < 0)   
	        {
	        	return 1;
	        } 
	        if(!S_ISDIR(statObj.st_mode))
	        {
	            char *char_array;
	            string s="xdg-open ";
	            string s1=namelist[n-row]->d_name;   
	            s=s+s1;
	            char_array=new char[s.length()+1];
	            strcpy(char_array, s.c_str()); 
	            system(char_array);
	        }
	        else
	        {
	            system("clear");
	            string s1="/";
	            string s=path;
	            s1=s+s1;
	            s=namelist[n-row]->d_name;
	            s1=s1+s;
	            path=new char[s1.length()+1];
	            strcpy(path, s1.c_str());
	            free(namelist);
	            n = scandir(path, &namelist, NULL,alphasort);
	            n1=n;

	            while (n1--)
	            {
	                fileInfo(path,namelist[n1]->d_name);
	            }
	        }
	    }

	}while(ch!=81 && ch!=113);
	return 0;
}