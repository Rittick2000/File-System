#include<bits/stdc++.h>

using namespace std;

//File Structure
struct file{
	vector<string> blocks;
	string FileName;
};

//Storing all the files
vector<file> Files;

//File Creationg
void CreateFile(string command)
{
	string filename="";
	file File;
	int n=command.length();
	int i=3;
	
	//File name extraction by parsing command
	while(command[i]!=' ')
	{
		filename+=command[i];
		i++;
	}
	
	//check for file with same name already exist or not
	for(auto &j:Files)
	{
		if(j.FileName==filename)
		{
			cout<<"File with same name already exist"<<endl;
			return;
		}
	}
	
	//text extraction by file parsing
	i+=2;
	string text="";
	for(;i<n-1;i++)
	{
		text+=command[i];
	}
	ofstream op;
	vector<string> temp_block;
	
	//creating blocks of size 4 from text
	int ptr=0;
	for(int i=0;i<text.length();)
	{
		string block=filename+to_string(ptr)+".txt";
		temp_block.push_back(block);
		op.open(block);
		if(i+3<text.length())
		{
			int count=4;
			while(count)
			{
				op<<text[i];
				i++;
				count--;
			}
		}
		else
		{
			while(i<text.length())
			{
				op<<text[i];
				i++;
			}
		}
		ptr++;
		op.close();
	}
	
	//string filename and blocks in a variable of type file
	File.FileName=filename;
	File.blocks=temp_block;
	
	Files.push_back(File);
	
	cout<<"File Created..."<<endl<<endl;
}

//Deletion of file
void DeleteFile(string command)
{
	string filename="";
	
	//extracting file name for deletion
	for(int i=3;i<command.length();i++)
		filename+=command[i];
		
	//check if file exist or not
	int flag=1;
	file File;
	int count=0;
	for(auto &i:Files)
	{
		if(i.FileName==filename)
		{
			flag=0;
			File=i;
			break;
		}
		count++;
	}
	if(flag)
	{
		cout<<"File does not exist!"<<endl;
		return;
	}
	
	//deleting all the .txt files from system
	vector<string> temp_block;
	temp_block=File.blocks;
	for(string block : temp_block){
        remove(block.c_str());
    }
    
    //deleting the file 
    Files.erase(Files.begin()+count);
    
    cout<<"File Deleted!"<<endl<<endl;
}

//print the file content
void PrintFile(string command)
{
	string filename="";
	
	//extracting file name
	for(int i=3;i<command.length();i++)
		filename+=command[i];
		
	// check if file with that name exist or not
	int flag=1;
	file File;
	for(auto &i:Files)
	{
		if(i.FileName==filename)
		{
			flag=0;
			File=i;
			break;
		}
	}
	if(flag)
	{
		cout<<"File does not exist!"<<endl;
		return;
	}
	
	//printing file content
	string text="";
	ifstream in;
	vector<string> temp_block=File.blocks;
    for(string s: temp_block){
        in.open(s);
        string str;
        getline(in, str);
        text += str;
        in.close();
    }
	cout<<text<<endl;
}

// Rename the file with another name
void RenameFile(string command)
{
	
	//extracting previous file name
	int i=3;
	string filename="";
	while(command[i]!=' ')
	{
		filename+=command[i];
		i++;
	}
	i++;
	
	//extracting  new file name
	string rename="";
	while(i<command.length())
	{
		rename+=command[i];
		i++;
	}
	
	//replace the file name
	int flag=1;
	for(auto &i:Files)
	{
		if(i.FileName==filename)
		{
			flag=0;
			i.FileName=rename;
			break;
		}
	}
	
	//if file with same name does not exist
	if(flag)
	{
		cout<<"File does not exist!"<<endl;
		return;
	}
}


//list of all the file in the directory
void List()
{
	
	//if file is empty
	if(Files.size()==0)
	{
		cout<<"Empty Directory"<<endl<<endl;
		return;
	}
	
	//printing all the files
	for(auto &i:Files)
	{
		cout<<i.FileName<<" ";
	}
	cout<<endl<<endl;
}

int main()
{
	
	// All the instruction
	cout<<"   Command Type                  Command"<<endl;
	cout<<"   ------------                  -------"<<endl;
	cout<<"1  Create File           ";
	cout<<"mf file-name \"file-contents\""<<endl;
	cout<<"2  Delete File                 ";
	cout<<"df file-name"<<endl;
	cout<<"3  Rename File            ";
	cout<<"rf file-name1 file-name2"<<endl;
	cout<<"4  Print File                  ";
	cout<<"pf file-name"<<endl;
	cout<<"5  All File names           ";
	cout<<"       ls"<<endl<<endl;
	
	//Run this until user want
	while(1)
	{
		
		// User input of command line
		string command;
		cout<<"Command$ ";
		getline(cin,command); 
		
		//extracting the instruction
		string ins="";
		ins+=command[0];
		ins+=command[1];
		
		//checking for wrong instruction
		if(command.length()==2 or command[2]==' ')
		{
			
			//for create file
			if(ins=="mf")
			{
				CreateFile(command);
			}
			
			//for delete file
			else if(ins=="df")
			{
				DeleteFile(command);
			}
			
			//for print file
			else if(ins=="pf")
			{
				PrintFile(command);
			}
			
			//for rename file
			else if(ins=="rf")
			{
				RenameFile(command);
			}
			
			//list of all the files
			else if(ins=="ls")
			{
				List();
			}
			else
			{
				cout<<"Wrong Input"<<endl;
			}
		}
		else
		{
			cout<<"Wrong Command"<<endl;
		}
		char ch;
		cout<<"Do you want to Continue?[Y/N]";
		cin>>ch;
		if(ch=='N' or ch=='n')
			break;
		cin.ignore();
	}
	return 0;
}
