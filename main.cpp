#include<bits/stdc++.h>
#include<termios.h>
using namespace std;



int main(int argc,char **argv)
{
    struct termios initialrsettings, newrsettings;  
    struct dirent **namelist;
    char ch;
    int n;
    //printf("%d\n",argc);

    tcgetattr(fileno(stdin), &initialrsettings);

    newrsettings = initialrsettings;  // load initial setting of terminal and keep it safe because at the end 
                                    //we need to revert back those settings.
    newrsettings.c_lflag &= ~ICANON;  // Switch to non-canonical mode 
    newrsettings.c_lflag &= ~ECHO;    // Turn off displaying text

    if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
                fprintf(stderr,"Could not set attributes\n");
        }
        else {
                ch=cin.get();
                if(ch==27)
                {
                   ch=cin.get();
                    ch=cin.get();
                    if(ch=='A')
                        cout<<"UP";
                    else if(ch=='B')
                        cout<<"Down";
                    else if(ch=='C')
                        cout<<"Right";
                    else if(ch=='D')
                        cout<<"Left";
                }
                else if(ch==104 || ch==72)
                    cout<<"home";
                else if(ch==127)
                    cout<<"Back";   
        }

        tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
        return 0;
    return 0;
}