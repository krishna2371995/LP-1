#include<iostream>
#include<cstring>
#include<cstdlib>
#define max 10
#define MAX 15

void ffun(int,int);
void fun(int,int[]);
void follow(int i);
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
                { //taking ,@, as null symbol.
                    if(array[p[0]][p[1]][0]>='A'&&array[p[0]][p[1]][0]<='Z')
                    {
                        key=0;
                        fun2(p[0],p[1],p,key);
                    }
                    else if(array[p[0]][p[1]].compare("/")!=0 && array[p[0]][p[1]].comapre("-1")!=0)
                    {
                        if(fun2(p[0],p[1],p,key))
                        temp[t][++c]=array[p[0]][p[1]];
                    }
                }
            }
        }
    }
}

/*
string fol[max][MAX],ff[max];int f,l,ff0;
void follow(int i)
{
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
                    for(cc=1;temp[tt][cc]!='\0';cc++) //mark
                    {
                        if(temp[tt][cc].compare("@")==0)null=1;
                        else fol[l][++f]=temp[tt][cc];
                    }
        }
        else fol[l][++f]=array[j][ii];
    }
    if(null)follow(j);
}
*/
int main()
{
    int p[2],i,j;
    //clrscr();
    cout<<"Enter the no. of productions :");
    cin>>n;
    cout<<"Enter the productions :\n");


    ifstream in;
    in.open("prod2.txt",ios::in);


    for(int i=0,j=0;i<m;i++)
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


    for(i=0,t=0;i<n;i++,t++)
    {
        c=0,p[0]=-1,p[1]=-1;
        temp[t][0]=array[i][0];
        fun(i,p);
        temp[t][++c]='\0';
        cout<<"First(%c) : [ "<<temp[t][0];
        for(j=1;j<c;j++)
            cout<<","<<temp[t][j];
        cout<<"\b ].\n";
    }
/* Follow Finding
    for(i=0,l=0;i<n;i++,l++)
    {
        f=-1;ff0=-1;
        fol[l][++f]=array[i][0];
        follow(i);
        fol[l][++f]='\0';
    }
    for(i=0;i<n;i++)
    {
        cout<<"\nFollow[%c] : [ "<<fol[i][0];
        for(j=1;fol[i][j]!='\0';j++)
            cout<<","<<fol[i][j];
        cout<<"\b ]";
    }
*/
    return 0;
}
