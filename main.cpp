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
    
    int n;
    char* path;
    //printf("%d\n",argc);

    tcgetattr(fileno(stdin), &initialrsettings);

    newrsettings = initialrsettings;  // load initial setting of terminal and keep it safe because at the end 
                                    //we need to revert back those settings.
    newrsettings.c_lflag &= ~ICANON;  // Switch to non-canonical mode 
    newrsettings.c_lflag &= ~ECHO;    // Turn off displaying text

    struct dirent **namelist;
    //printf("%d\n",argc);

    if(argc < 1)
    {
        exit(EXIT_FAILURE);
    }
    else if (argc == 1)
    {
        n=scandir(".",&namelist,NULL,alphasort);
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
    }
    
    if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
            fprintf(stderr,"Could not set attributes\n");
    }
    else 
    {
        navigate(--n,path,namelist,newrsettings,root);
    }

    cls;
    cout<<"Thank You!!!"<<endl;
    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
    return 0;
}