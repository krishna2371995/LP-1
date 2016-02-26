#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
using namespace std;
int m=0;
string s[50][20];
int l[50];
int get(int a[],int i)
{
    int k=0;
    string d="A";
    char numstr[21]; // enough to hold all numbers up to 64-bits
    d = d + itoa(i, numstr, 10);
    for(int p=0;p<m;p++)
    {
        if(s[p][0].compare(d)==0)
        {
            a[k++]=p;
        }
    }
    return k;
}
void print()
{
    for(int i=0;i<m;i++)
    {
        cout<<s[i][0]<<"->";
        for(int j=1;j<l[i];j++)
        {
            cout<<s[i][j];
        }
        cout<<endl;
    }
}

void put(int k,string a[],int len)
{

    int g;
    if(k==-1)
    {
        g=m;
    }
    else
    {
        g=k;
    }
    l[g]=len;
    for(int i=0;i<len;i++)
    {
        s[g][i]=a[i];
    }
    if(k==-1)
    {
        m++;
    }
    else
    {
        m--;
    }

}
int find(string[] t,string a)
{
    for(int i=0;i<n;i++)
    {
        if(t[i].compare(a)==0)return i;
    }
    return -1;
}
int main()
{
    int n=0;
    cout<<"Enter no.of non terminals:\n";
    cin>>n;
    cout<<"Enter no.of prod:\n";
    cin>>m;
    ifstream in;
    in.open("prod2.txt",ios::in);


    for(int i=0,j=0;i<m;i++)
    {
        //cout<<"Enter production "<<i+1<<endl;
        l[i]=0;
        while(1)
        {
             in>>s[i][j];
             if(s[i][j].compare("-1")==0)
             {
                 break;
             }
             j++;
        }
        l[i]=j;
        j=0;
    }
    in.close();
    print();

    for(int i=1;i<=n;i++)
    {
        int g[20];
        int k=get(g,i);
        if(k==1)continue;
        string temp[20];
        int freq[20][10];int j;int len=0;
        for(int p=0;p<k;p++)
        {
            j=find(temp,s[g[p]][1],len);
            if(j==-1)
            {
                 temp[len]=s[g[p]][1];
                 freq[len][0]=1;
                 freq[len][1]=g[p];
                 len++;
            }
            else
            {
                freq[j][0]++;
                freq[len][freq[j][0]]=g[p];

            }

        }

        for(int q=0;q<len;q++)
        {
            if(freq[q][0]>=2)
            {
                for(int q2=2;q2<;q2++)
                {
                    check(freq[q],q2);
                }

            }

        }



    }





return 0;
}
