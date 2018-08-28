#include "config.h"
 

int commandMode(int row)
{
	string command="";
	int col=0;
	char ch;
	do
	{
		while((ch=cin.get())!=27 && (ch!=10))
		{
			cout<<ch;
			command+=ch;
		}
		if(ch==27)
			return 0;
		else
		{
			vector<string> commandSplit;
			string s="";
			unsigned int i=0;
			int flag=0;
			
			while(i<command.length())
			{
				flag=0;
				if(command[i]==32)
				{
					commandSplit.push_back(s);
					s="";
				}
				else
				{
					s=s+command[i];
					flag=1;
				}
				i++;
			}
			if(flag==1)
				commandSplit.push_back(s);
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
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="create_file")
			{
				createFile(commandSplit);
				MoveCursor(row,col);
			}
			else if(commandSplit[0]=="create_dir")
			{
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
				MoveCursor(row,col);
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

  	}while(true);
}

void MoveCursor(int row,int col)
{
	printf("%c[2K", 27);
	printf("%c[%d;%dH",27,row,col);
	cout<<":";
}
