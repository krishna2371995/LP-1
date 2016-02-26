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
int geti(int a[],int i)
{
    int k=0;
    string d="A";
    char numstr[21]; // enough to hold all numbers up to 64-bits
    d = d + itoa(i, numstr, 10);
    for(int p=0;p<m;p++)
    {
        if(s[p][0].compare(d)==0 && s[p][1].compare(d)!=0)
        {
            a[k++]=p;
        }
    }
    return k;
}
int get(int a[],int i,int j)
{
    int k=0;
    string d="A";
    char num1[21]; // enough to hold all numbers up to 64-bits
    d = d + itoa(i, num1, 10);
    string b="A";
    char num2[21]; // enough to hold all numbers up to 64-bits
    b= b + itoa(j, num2, 10);


    for(int p=0;p<m;p++)
    {
        if(s[p][0].compare(d)==0 && s[p][1].compare(b)==0)
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
        for(int j=1;j<i;j++)
        {
            int g[10],h[10];
            int k2=get(h,i,j);

            if(k2==0)continue;
            int k1=get(g,j);


            for(int p=0;p<k2;p++)
            {

                int flg=0,lp=l[h[p]];
                for(int q=0;q<k1;q++)
                {
                    string temp[20];
                    temp[0]=s[h[p]][0];
                    int c=1,lq=l[g[q]];

                    while(c<lq)
                    {
                        temp[c]=s[g[q]][c];
                        cout<<temp[c]<<endl;
                        c++;
                    }
                    cout<<"ji";
                    while(c-lq<lp-2)
                    {
                        cout<<h[p]<<" "<<c-lq+2;
                        temp[c]=s[h[p]][c-lq+2];
                        cout<<temp[c]<<endl;
                        c++;
                    }
                    flg=1;
                    put(-1,temp,c);
                    cout<<endl;
                   print();
                 //   break;
                }
                if(flg==1)
                {
                   put(h[p],s[m-1],l[m-1]);
                }

            }

            cout<<endl<<endl;
            print();

        }

        int g[10],h[10];
        int k2=get(h,i,i);

        if(k2==0)continue;
        int k1=geti(g,i);


        for(int p=0;p<k1;p++)
        {
            s[g[p]][l[g[p]]]=s[g[p]][0]+"\'";
            l[g[p]]++;
        }

         string temp[20];

        for(int q=0;q<k2;q++)
        {
            s[h[q]][0]=s[h[q]][0]+"\'";
            temp[0]=s[h[q]][0];
            for(int i1=1;i1<l[h[q]];i1++)
            {
                swap(s[h[q]][i1],s[h[q]][i1+1]);
            }
            s[h[q]][l[h[q]]-1]=s[h[q]][0];

        }

        temp[1]="e";
        put(-1,temp,2);

         cout<<endl<<endl;
            print();
    }





return 0;
}
