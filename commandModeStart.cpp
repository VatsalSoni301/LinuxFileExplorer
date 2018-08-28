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
			if(flag==1 && commandSplit[0]!="create_dir" && commandSplit[0]!="create_file")
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
				//copy(commandSplit);
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="move")
			{
				//move(commandSplit);
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="rename")
			{
				rename(commandSplit);
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="create_file")
			{
				s=stringProcess(commandSplit[commandSplit.size()-1]);
				commandSplit.pop_back();
				commandSplit.push_back(s);
				createFile(commandSplit);
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="create_dir")
			{
				s=stringProcess(commandSplit[commandSplit.size()-1]);
				commandSplit.pop_back();
				commandSplit.push_back(s);
				createDir(commandSplit);
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="delete_file")
			{
				deleteFile(commandSplit);
				MoveCursor(row,col);	
			}
			else if(commandSplit[0]=="delete_dir")
			{
				deleteDir(commandSplit);
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="goto")
			{
				string path=commandSplit[1];
				return path;
				//MoveCursor(row,col);
			}
			else if(commandSplit[0]=="search")
			{
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="snapshot")
			{
				MoveCursor(row,col);
			}						
			else
			{
				cout<<"Invalid Command";
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
		fname=home+fname;
	}
	else
	{
		fname=current+"/"+fname;
	}
	cout<<"***"<<fname<<"***";
	return fname;
}