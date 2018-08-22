#include<bits/stdc++.h>
#include<dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<time.h>
using namespace std;

int fileInfo(char* name)
{
	struct stat statObj;
    if(stat(name,&statObj) < 0)    
        return 1;

    // permission of a file (r-w-x of user,group and other)

    printf( (S_ISDIR(statObj.st_mode)) ? "d" : "-");
    printf( (statObj.st_mode & S_IRUSR) ? "r" : "-");
    printf( (statObj.st_mode & S_IWUSR) ? "w" : "-");
    printf( (statObj.st_mode & S_IXUSR) ? "x" : "-");
    printf( (statObj.st_mode & S_IRGRP) ? "r" : "-");
    printf( (statObj.st_mode & S_IWGRP) ? "w" : "-");
    printf( (statObj.st_mode & S_IXGRP) ? "x" : "-");
    printf( (statObj.st_mode & S_IROTH) ? "r" : "-");
    printf( (statObj.st_mode & S_IWOTH) ? "w" : "-");
    printf( (statObj.st_mode & S_IXOTH) ? "x" : "-");

    printf("   %s",name); // name of a file
    printf("   %ld bytes",statObj.st_size); // size of a file

    printf("   %s", ctime(&statObj.st_mtime)); // last modified date of a file
    //printf("\n");
 
}


int main(int argc,char **argv)
{
    struct dirent **namelist;
    int n;
    //printf("%d\n",argc);

    if(argc < 1)
    {
        exit(EXIT_FAILURE);
    }
    else if (argc == 1)
    {
        n=scandir(".",&namelist,NULL,NULL);
    }
    else
    {
        n = scandir(argv[1], &namelist, NULL,NULL);
    }
    if(n < 0)
    {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    else
    {
        while (n--)
        {
            //printf("%s",namelist[n]->d_name);
            fileInfo(namelist[n]->d_name);
            //printf("\n");
            free(namelist[n]);
        }
        free(namelist);
    }
    return 0;
}