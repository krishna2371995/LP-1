#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<set>
#include<map>
#include<stack>
#define max 10
#define MAX 15
using namespace std;

void ffun(int,int);
void fun(int,int[]);
void follow(int i);
set<string> FT[max];
set<string> FL[max];
string TR[6]={"id","+","*","(",")","$"};
string array[max][MAX],temp[max][MAX];

int c,n,t;
int fun2(int i,int j,int p[],int key)
{
    int k;
    if(!key)
    {
        for(k=0;k<n;k++)
        if(array[i][j].compare(array[k][0])==0)
        break;
        p[0]=i;p[1]=j+1;
       // cout<<"propagating term %c\n",array[i][j]);
        fun(k,p);
        return 0;
    }
    else
    {
        for(k=0;k<=c;k++)
        {
            if(array[i][j].compare(temp[t][k])==0)
            break;
        }
       //  cout<<"k and  c are %d and %d\n",k,c);
        if(k>c)return 1;
        else return 0;
    }
}

void fun(int i,int p[])
{
    int j,k,key;
    for(j=2;array[i][j].compare("-1")!=0;j++)
    {
        if(array[i][j-1].compare("/")==0)
        {
            if(array[i][j][0]>='A'&&array[i][j][0]<='Z')
            {
                key=0;
                // cout<<"propagating NT to fun2\n");
                fun2(i,j,p,key);
            }
            else
            {
                key=1;
                if(fun2(i,j,p,key))
                {
                    temp[t][++c]=array[i][j];
                   // cout<<"an element %c added to first of %d",array[i][j],t);
                }
                if(array[i][j].compare("@")==0 && p[0]!=-1)
                { //@  as epsilon.
                    if(array[p[0]][p[1]][0]>='A'&&array[p[0]][p[1]][0]<='Z')
                    {
                        key=0;
                        fun2(p[0],p[1],p,key);
                    }
                    else if(array[p[0]][p[1]].compare("/")!=0 && array[p[0]][p[1]].compare("-1")!=0)
                    {
                        if(fun2(p[0],p[1],p,key))
                        temp[t][++c]=array[p[0]][p[1]];
                    }
                }
            }
        }
    }
}


string fol[max][MAX],ff[max];int f,l,ff0;
void follow(int i)
{
	//cout<<"follow "<<i<<endl;
    int j,k;
    for(j=0;j<=ff0;j++)
        if(array[i][0].compare(ff[j])==0)
            return;
        if(j>ff0)ff[++ff0]=array[i][0];
            if(i==0)fol[l][++f]="$";
        for(j=0;j<n;j++)
            for(k=2;array[j][k].compare("-1")!=0;k++)
                if(array[j][k].compare(array[i][0])==0)
                    ffun(j,k);
}
void ffun(int j,int k)
{
    int ii,null=0,tt,cc;
    if(array[j][k+1].compare("/")==0||array[j][k+1].compare("-1")==0)
        null=1;
    for(ii=k+1;array[j][ii].compare("/")!=0 && array[j][ii].compare("-1")!=0;ii++){
        if(array[j][ii][0]<='Z'&&array[j][ii][0]>='A')
        {
            for(tt=0;tt<n;tt++)
                if(temp[tt][0].compare(array[j][ii])==0)break;
                    for(cc=1;temp[tt][cc].compare("-1")!=0;cc++) //mark
                    {
                        if(temp[tt][cc].compare("@")==0)null=1;
                        else fol[l][++f]=temp[tt][cc];
                    }
        }
        else fol[l][++f]=array[j][ii];
    }
    if(null)follow(j);
}

void print(int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<array[i][0]<<"->";
        for(int j=1;array[i][j].compare("-1")!=0;j++)
        {
            cout<<array[i][j];
        }
        cout<<endl;
    }
}
void decode(int parse[][10],int n)
{

	cout<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<array[i][0]<<"->\t";
		for(int j=0;j<6;j++)
		{
			
			int r=parse[i][j];
			if(r>0)
			{
				cout<<"["<<TR[j]<<"]";
				while(array[i][r].compare("/")!=0 && array[i][r].compare("-1")!=0)
				{
					cout<<array[i][r];
					r++;
				}
				cout<<"  ";
			}
			
		}
		cout<<endl;
	}
}

int getid(string k)
{
	for(int i=0;i<6;i++)
	{
		if(TR[i].compare(k)==0)
		return i;
	}
}

int getnum(char k,int n)
{
	for(int i=0;i<n;i++)
	{
		if(array[i][0][0]==k)
		return i;
	}
}

int main()
{
    int p[2],i,j;
    //clrscr();
    cout<<"Enter the no. of productions(taken from file prod.txt : so enter number 5) :";
    cin>>n;
    cout<<"Enter the productions :\n";


    ifstream in;
    in.open("prod.txt",ios::in);


    for(int i=0,j=0;i<n;i++)
    {
        //cout<<"Enter production "<<i+1<<endl;
      //  l[i]=0;
        while(1)
        {
             in>>array[i][j];
             
             if(array[i][j].compare("-1")==0)
             {
                 break;
             }
             j++;
        }
     //   l[i]=j;
        j=0;
    }
    in.close();

	print(n);
	cout<<endl<<endl;
	
    for(i=0,t=0;i<n;i++,t++)
    {
        c=0,p[0]=-1,p[1]=-1;
        temp[t][0]=array[i][0];
        fun(i,p);
        temp[t][++c]="-1";
        cout<<"First "<<temp[t][0]<<" [";
        for(j=1;j<c;j++)
        {
            //cout<<temp[t][j]<<",";
            FT[i].insert(temp[t][j]);
        }
        
       set<string>::iterator lp=FT[i].begin();
        while(lp!=FT[i].end())
        {
        	cout<<*lp<<",";
			lp++;	
        }
        
        cout<<"\b ].\n";
    }
    
/* Follow Finding */
    for(i=0,l=0;i<n;i++,l++)
    {
        f=-1;ff0=-1;
        fol[l][++f]=array[i][0];
        follow(i);
        fol[l][++f]="-1";
    }
    for(i=0;i<n;i++)
    {
        cout<<"\nFollow "<<fol[i][0] <<" [";
        for(j=1;fol[i][j].compare("-1")!=0;j++)
        {
           // cout<<fol[i][j]<<",";
            FL[i].insert(fol[i][j]);
        }
        
        
        set<string>::iterator lp=FL[i].begin();
        while(lp!=FL[i].end())
        {
        	cout<<*lp<<",";
			lp++;	
        }
        cout<<"\b ]";
        //FL[i].
    }  
	
	/* start construction of Parse Table */
	
	cout<<endl<<endl;
	int parse[10][10]={-1};
	for(int i=0;i<n;i++)
	{
		for(int j=2;array[i][j].compare("-1")!=0;)
		{
			
			//cout<<j<<" "<<array[i][j]<<endl;
				//if non terminal or epsilon enter
				if(isupper(array[i][j][0]) || array[i][j].compare("@")==0)
				{
					int pp;
					set<string>::iterator ii;
					if(array[i][j].compare("@")!=0)
					{
					
				
					 pp=getnum(array[i][j][0],n);
					//cout<<pp<<" ";
					ii=FT[pp].find("@");
					}
					//if epsilon in first(alpha) case:add A->alpha for  each of Follow of(A)
					if(ii!=FT[pp].end() || array[i][j].compare("@")==0)
					{
						
						set<string>::iterator it=FL[i].begin();
						int size=FL[i].size();
						 while(size>0)
				        {
				        	//cout<<*it<<",";
				        	parse[i][getid(*it)]=j;
				        
							it++;	
							size--;
						 
				        }
						
			
					}
					else
					{
						//if epsilon not in first(alpha) case:add A->alpha for  each of First of(A)	
						set<string>::iterator it=FT[pp].begin();
						int size=FT[pp].size();
					 	while(size>0)
				        {
				        	//cout<<*it<<",";
				        	parse[i][getid(*it)]=j;
				        	size--;	
				        	if(size>0)
							it++;
							
				        }
				     
					}
				
					
				
				}
				else
				{
					//if prod starts with term then first(a)=a; add prod A->a to parse table
					parse[i][getid(array[i][j])]=j;
			
				}
				
				while(array[i][j].compare("/")!=0 && array[i][j].compare("-1")!=0)
				{
				//	loop until next alternate production of Ai
					j++;
				}
				
				if(array[i][j].compare("-1")==0)
				{
					//end of prod of Ai so go to A(i+1)
					break;
				}
				else
				{
					//goto first symbol in next alternate prod of Ai
					j++;
					
				}
			}
		
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	
	cout<<endl<<endl;
	cout<<"Parse Table:\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<6;j++)
		{
			cout<<parse[i][j]<<" ";
		}
		cout<<endl;
	}
	decode(parse,n);
	/*start parsing of given input string  using parse table*/
	cout<<endl<<endl;
	int nip;
	string ip[20];
	cout<< "Enter no.of terminals in i/p string:";
	cin>>nip;
	cout<<"Enter string to be parsed(enter each terminal in i/p one by one)\n";
	for(int i=0;i<nip;i++)
	{
		cin>>ip[i];
	}
	ip[nip]="$";
	
	
	stack<string> sp;
	int ptr=0;
	sp.push("$");
	sp.push(array[0][0]);
	cout<<"\nOutput:\n";
	//mark : try to implement other case
	while(1)
	{
		if(sp.top().compare("$")==0 && ip[ptr].compare("$")==0)
		{
			//if stack contains $ and i/p symbol also $ then string accepted
				cout<<"String accepted\n";
				break;
		}
		else if(sp.top().compare(ip[ptr])==0)
		{
			//if stack top X  and i/p symbol match pop stack and advance i/p pointer
			sp.pop();
			cout<<"matched"<<ip[ptr]<<endl;
			ptr++;
		}
		else
		{
			
			if(sp.top().compare("$")==0 && ip[ptr].compare("$")!=0)
			{
				//if stack top is $ and i/p not $ then error occured
				cout<<"Error parsing\n";
				break;
			}
			int p=getnum((sp.top())[0],n);
			int q=getid(ip[ptr]);
			int r=parse[p][q];
			if(r==0)
			{
				//if no entry in parse table for that combination error occurs
				cout<<"Error parsing\n";
				break;
			}
			int r2=r;
			//start display of prod 
			cout<<sp.top()<<"->";
			while(array[p][r2].compare("/")!=0 && array[p][r2].compare("-1")!=0)
			{
				cout<<array[p][r2];
				r2++;
			}
			cout<<endl;
			r2--;
			sp.pop();
			if(array[p][r2].compare("@")!=0)
			while(r2>=r)
			{
				//push symbols of that prod into stack
				
				//cout<<array[p][r2]<<" ";
				sp.push(array[p][r2]);
				r2--;
			}
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
    return 0;
}
