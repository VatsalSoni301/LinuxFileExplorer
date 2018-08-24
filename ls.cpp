#include "config.h"

int fileInfo(char* path,char* name)
{
	struct stat statObj;
    char* fname;
    register uid_t uid;
    register gid_t gid;
    register struct group *g;
    register struct passwd *pw;
    //cout<<path;
    string s=string(path)+"/"+string(name);
    fname=new char[s.length()+1];
    strcpy(fname, s.c_str());
    //cout<<fname<<endl;
    if(stat(fname,&statObj) < 0)    
    {
        return 1;
    }

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

    uid = geteuid ();
    pw = getpwuid (uid);
    if (pw)
    {
      printf("   %s",pw->pw_name);
      
    }
    gid=statObj.st_gid;
    g=getgrgid(gid);
    printf("   %s",g->gr_name);

    printf("   %s", ctime(&statObj.st_mtime)); // last modified date of a file
    //printf("\n");
    return 0;
}
