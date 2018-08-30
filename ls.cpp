//2018201005 Vatsal Soni
#include "config.h"

int fileInfo(char* path,char* name) // It prints all file info like permission/name etc..
{
	struct stat statObj;
    char* fname;
    register uid_t uid;
    register gid_t gid;
    register struct group *g;
    register struct passwd *pw;
    double size;
    //cout<<path;
    string s=string(path)+"/"+string(name);
    fname=new char[s.length()+1];
    strcpy(fname, s.c_str());
    //cout<<fname<<endl;
    if(stat(fname,&statObj) < 0)    
    {
        cout<<"Error";
        //return 1;
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

    size=statObj.st_size/1024.0;
    printf("\t%10.4f KB",size); // size of a file

    uid = geteuid ();
    pw = getpwuid (uid);
    if (pw)
    {
      printf("\t%s",pw->pw_name);
      
    }
    gid=statObj.st_gid;
    g=getgrgid(gid);
    printf("\t%s",g->gr_name);

    string dt=ctime(&statObj.st_mtime);
    //printf("   %s", ctime(&statObj.st_mtime)); // last modified date of a file
    printf("\t");
    for(unsigned int i=0;i<dt.length()-1;i++)
            printf("%c",dt[i]);

    //strcpy(date,dt.c_str());

    printf("   %s",name); // name of a file
    printf("\n");
    return 0;
}
