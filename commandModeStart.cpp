#include "config.h"

string home,current; 

string commandMode(int row,string currentPath,string root)
{
	string command="";
	home=root;
	current=currentPath;
	int col=0;
	char ch;
	vector<string> commandSplit;
	string s="";
	do
	{
		command="";
		while((ch=cin.get())!=27 && (ch!=10))
		{
			cout<<ch;
			if(ch==127)
			{
				if(command.length()<=1)
				{
					command="";
					MoveCursor(row,col);
					cout<<command;
				}
				else
				{
					command=command.substr(0,command.length()-1);
					MoveCursor(row,col);
					cout<<command;
				}
			}
			else
				command+=ch;
		}
		if(ch==27)
			return "";
		else
		{
			unsigned int i=0;
			int flag=0;
			
			while(i<command.length())
			{
				flag=0;
				if(command[i]==32 && commandSplit.size()==0)
				{
					//s=stringProcess(s);
					commandSplit.push_back(s);
					s="";
				}
				else if(command[i]==32 && commandSplit.size()>=1)
				{
					if(s!="" && s!=" " && (commandSplit[0]=="create_file" || commandSplit[0]=="create_dir"))
					{
						commandSplit.push_back(s);
					}
					else if(s!="" && s!=" ")
					{
						s=stringProcess(s);
						commandSplit.push_back(s);
					}
					s="";
				}
				else
				{
					s=s+command[i];
					flag=1;
				}
				i++;
			}
			if(commandSplit.size()==0)
			{
				cout<<endl<<"Invalid Command"<<endl;
				cout<<":";
				commandSplit.clear();
				s="";
				continue;
			}
			else if(flag==1 && commandSplit[0]!="create_dir" && commandSplit[0]!="create_file")
			{
				s=stringProcess(s);
				commandSplit.push_back(s);
			}
			else if(flag==1)
			{
				commandSplit.push_back(s);
			}
			if(commandSplit[0]=="copy")
			{
				if(commandSplit.size()>=3)
				{
					copyFile(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="move")
			{
				if(commandSplit.size()>=3)
				{
					moveFile(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="rename")
			{
				if(commandSplit.size()==3)
				{
					rename(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="create_file")
			{
				if(commandSplit.size()>=3)
				{
					s=stringProcess(commandSplit[commandSplit.size()-1]);
					commandSplit.pop_back();
					commandSplit.push_back(s);
					createFile(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="create_dir")
			{
				if(commandSplit.size()>=3)
				{
					s=stringProcess(commandSplit[commandSplit.size()-1]);
					commandSplit.pop_back();
					commandSplit.push_back(s);
					createDir(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="delete_file")
			{
				if(commandSplit.size()>=2)
				{
					deleteFile(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";	
			}
			else if(commandSplit[0]=="delete_dir")
			{
				if(commandSplit.size()>=2)
				{
					vector<string> vc=deleteDir(commandSplit);
					if(vc.size()>0)
					{
						//cout<<endl<<endl;
						for(int i=vc.size()-1;i>=0;i--)
					    {
					    	//cout<<vc[i]<<endl;
					    	char *p=new char[vc[i].length()+1];
					    	strcpy(p,vc[i].c_str());
					    	struct stat statObj;
					    	stat(p,&statObj);
							if(S_ISDIR(statObj.st_mode))
							{
								vector<string> v;
								v.clear();
								v.push_back("abc");
								v.push_back(vc[i]);
								deleteDir(v);
							}
							else
							{
								vector<string> v;
								v.clear();
								v.push_back("abc");
								v.push_back(vc[i]);
								deleteFile(v);
							}
					    }
					}
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="goto")
			{
				if(commandSplit.size()==2)
				{
					string path=commandSplit[1];
					DIR *d;
					char *temp2=new char[path.length()+1];
					strcpy(temp2,path.c_str());
					d=opendir(temp2);
					if(!d)
					{
						cout<<endl<<"Invalid path"<<endl<<":";
					}
					else
						return path;
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="search")
			{
				if(commandSplit.size()==2)
				{
					search(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}
			else if(commandSplit[0]=="snapshot")
			{
				if(commandSplit.size()==3)
				{
					snapShot(commandSplit);
					MoveCursor(row,col);
				}
				else
					cout<<endl<<"Argument Missing"<<endl<<":";
			}						
			else
			{
				cout<<endl<<"Invalid Command"<<endl;
			}
		}
		commandSplit.clear();
		s="";
  	}while(true);
}

void MoveCursor(int row,int col)
{
	printf("%c[2K", 27);
	printf("%c[%d;%dH",27,row,col);
	cout<<":";
}

string stringProcess(string fname)
{
	if(fname[0]=='.')
	{
		fname=fname.substr(1,fname.length());
		fname=current+fname;
	}
	else if(fname[0]=='~')
	{
		fname=fname.substr(1,fname.length());
		fname=home+fname;
	}
	else if(fname[0]=='/')
	{
		if(fname=="/")
		{
			fname=fname.substr(1,fname.length());
			fname=home+fname;
		}
		else
			fname=home+fname;
	}
	else
	{
		fname=current+"/"+fname;
	}
	//cout<<"***"<<fname<<"***";
	return fname;
}