#include "config.h"

#define esc 27
//int row=0,col=0;
//#define pos() printf("%c[%d;%dH",esc,row,col)
#define cls printf("%c[2J",esc)
string root;

int main(int argc,char **argv)
{
    system("clear"); 
    struct termios initialrsettings, newrsettings;  
    
    int n,n1;
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
        n1=n;
        while (n1--)
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
            if(string(namelist[n1]->d_name)!="..")
                fileInfo(path,namelist[n1]->d_name);
        }
    }

    
    if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
            fprintf(stderr,"Could not set attributes\n");
    }
    else 
    {
        navigate(n,path,namelist,newrsettings,root);
    }

    system("clear");
    cout<<"Thank You!!!"<<endl;
    tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
    return 0;
}