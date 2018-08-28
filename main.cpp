#include "config.h"

#define esc 27
//int row=0,col=0;
//#define pos() printf("%c[%d;%dH",esc,row,col)
#define cls printf("\033[H\033[J")
string root;

int main(int argc,char **argv)
{
    cls;
    struct termios initialrsettings, newrsettings;  
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int n;
    char* path;
    //printf("%d\n",argc);

    tcgetattr(fileno(stdin), &initialrsettings);
    newrsettings = initialrsettings;  // load initial setting of terminal and keep it safe because at the end                               
    newrsettings.c_lflag &= ~ICANON;  //we need to revert back those settings. Switch to non-canonical mode 
    newrsettings.c_lflag &= ~ECHO;    // Turn off displaying text

    struct dirent **namelist;
    //printf("%d\n",argc);

    if(argc < 1)
    {
        exit(EXIT_FAILURE);
    }
    else if (argc == 1)
    {
        n=scandir(".",&namelist,NULL,alphasort); //store all files and dirctories into namelist from specified path
    }
    else
    {
        n = scandir(argv[1], &namelist, NULL,alphasort);
    }
    if(n < 0)
    {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    else
    {
        
        string s;
        if(argc==1)
        {
            s=".";
            path=new char[s.length()+1];
            strcpy(path, s.c_str());
        }
        else
        {
            s=argv[1];
            path=new char[s.length()+1];
            strcpy(path, s.c_str());
        }
        root=s;
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
                break;
            }
        }
        n--;
        int n1;
        if(n<=w.ws_row-2)
            n1=n-1;
        else
            n1=w.ws_row-2;
        /*cout<<n1<<endl;
        for(int i=0;i<n1;i++)
            cout<<i<<endl;*/
        for(int i=0;i<=n1;i++)
        {
            fileInfo(path,namelist[i]->d_name); //call file to display information of the file
        }
    }
    
    if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
            fprintf(stderr,"Could not set attributes\n");
    }
    else 
    {
        navigate(n,path,namelist,newrsettings,initialrsettings,root);
    }

    cls;
    cout<<"Thank You!!!"<<endl;
    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
    return 0;
}

// http://www.cse.psu.edu/~kxc104/class/cmpen472/11f/hw/hw7/vt100ansi.htm