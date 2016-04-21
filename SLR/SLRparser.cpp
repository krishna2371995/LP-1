#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<stack>
using namespace std;
string table[30][30];
string array[30][30];
int len[30];
string TR[9]={ "id","+","*","(",")","$","E","T","F"};

int ns,nt,nnt;

int getid(string a)
{
	for(int i=0;i<nt+nnt;i++)
	{
		if(TR[i].compare(a)==0)
		return i;
	}
	
}

string gettran(string a,string b)
{
	int p=atoi(a.data());

	int q=getid(b);
	return table[p][q];
}
string getgoto(string a,string b)
{
	int p=atoi(a.data());
	int q=getid(b);
	return table[p][q];
}

int main()
{
	ifstream in;
	int np;
	cout<<"Enter No.of productions:";
	cin>>np;
	 in.open("SLRprod.txt",ios::in);

    for(int i=1,j=0;i<=np;i++)
    {
       
        while(1)
        {
             in>>array[i][j];                                                                                                                                                                                                                                                                             
             if(array[i][j].compare("-1")==0)
             {
                 break;
             }
             j++;
        }
        len[i]=j;
        j=0;
    }
    in.close();
	
	
    in.open("SLRtable.txt",ios::in);
	cout<<"Enter no.of states:\n";
	cin>>ns;
	cout<<"Enter no.of terminals:\n";
	cin>>nt;
	cout<<"Enter no.of non-terminals:\n";
	cin>>nnt;
	
    for(int i=0,j=0;i<ns;i++)
    {
       
        while(1)
        {
             in>>table[i][j];                                                                                                                                                                                                                                                                             
             if(table[i][j].compare("-|")==0)
             {
                 break;
             }
             j++;
        }
        j=0;
    }
    in.close();
    
    int nip;
    stack<string> sp;
	string ip[100];
	cout<<"Enter no.of terminals in i/p string:";
	cin>>nip;
	cout<<"Enter the i/p string:\n";
	for(int i=0;i<nip;i++)
	{
		cin>>ip[i];
	}
	ip[nip]="$";
	int ptr=0;
	sp.push("0");
	printf("\n\n parsing\n\n");
	while(1)
	{
		string x=gettran(sp.top(),ip[ptr]);
		if(x.compare("-1")==0)
		{
			printf("string not accepted\n");
			break;
		}
		else if(x.compare("A")==0)
		{
			printf("string accepted\n");
			break;
		}
		else if(x[0]=='s')
		{
			for(int i=ptr;i<=nip;i++)
			{
				printf("%s",ip[i].data());
			}
			printf("\tshift ");
			sp.push(ip[ptr]);
			printf("s%s\n",(x.substr(1)).data());
			sp.push((x.substr(1)).data());
			ptr++;
		}
		else if(x[0]=='r')
		{
			for(int i=ptr;i<=nip;i++)
			{
				printf("%s",ip[i].data());
			}
			printf("\treduce ");
			
			
			int rprod=atoi((x.substr(1)).data());
			printf("r%s\n",(x.substr(1)).data());
			int rn=len[rprod]-2;
			
			for(int i=0;i<2*rn;i++)
			{
				string sd=sp.top();
			
				sp.pop();
			}
			
			string y=sp.top();
			sp.push(array[rprod][0]);
			sp.push(getgoto(y,array[rprod][0]));
		
		}
		
	}
	
	
	
	
	
	
	
	
	
	
}
