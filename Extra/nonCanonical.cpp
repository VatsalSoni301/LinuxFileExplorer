
#include<termios.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{
        struct termios initialrsettings, newrsettings;  
        char ch;

        tcgetattr(fileno(stdin), &initialrsettings);

        newrsettings = initialrsettings;
        newrsettings.c_lflag &= ~ICANON;
        newrsettings.c_lflag &= ~ECHO;
        printf("Enter Key: ");

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
                	else
                		cout<<"ESC";
                }
                else if(ch==104 || ch==72)
                	cout<<"home";
                else if(ch==127)
                	cout<<"Back";
                else
                	cout<<ch;	
        }

        tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
        return 0;
}