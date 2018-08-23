#include "config.h"

int main()
{
	
    int status=rename(old1,new1);
    if(status!=0)
    	cout<<"Error";

	exit(0);
}