#include "config.h"

int commandMode()
{
	string str="";
	char ch;
	
  	while((ch=cin.get())!=27 && (ch!=10))
  	{
  		cout<<ch;
  		str+=ch;
  	}
  	if(ch==27)
  		return 0;
  	else
  	{
  		
  		return 0;
  	}
}