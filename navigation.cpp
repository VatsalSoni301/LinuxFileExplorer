#include "config.h"

#define esc 27
int row=0,col=0;
#define pos() printf("%c[%d;%dH",esc,row,col)
#define cls printf("%c[2J",esc);
s
int navigate(int n)
{
	char ch;
	ch=cin.get();
    if(ch==27)
    {
    	ch=cin.get();
            ch=cin.get();
            if(ch=='A')
            {
                row--;
                if(row>=0)
                    pos();
                else
                    row=0;

            }
            else if(ch=='B')
            {
                row++;
                pos();
            }
            else if(ch=='C')
                cout<<"Right";
            else if(ch=='D')
                cout<<"Left";
    }
    else if(ch==104 || ch==72)
        cout<<"home";
    else if(ch==127)
        cout<<"Back"; 
    else if(ch==58)
          newrsettings.c_lflag &= ICANON;
    else if(ch==10)
    {
        struct stat statObj;
        if(stat(namelist[n-row]->d_name,&statObj) < 0)    
            return 1;
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
    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
	return 0;
}