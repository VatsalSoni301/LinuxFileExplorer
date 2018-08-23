#include "config.h"

int main()
{
	
    status = remove("abc.txt");
    
    if(status!=0)
    {
        printf("Unable to delete the filen");
        perror("Error");
    }

	exit(0);
}