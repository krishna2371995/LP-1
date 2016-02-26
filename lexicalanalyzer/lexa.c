#include<stdio.h>
#include<ctype.h>
#include<unistd.h>
#include<fcntl.h>
#include<strings.h>
char def[20][100]={"int","char","float","double","long","for","while","do","continue","break","if","else","switch","case","void","bool","const","static","unsigned"};
int iskey(char buffer[100])
{
        for(int i=0;i<20;i++)
        {
                if(strcasecmp(def[i],buffer)==0)
                {
                        return 1;
                }
        }
        return 0;
}
void print(char buffer[100],int i)
{
        int f=0;
        if(!isdigit(buffer[0]))
        {
                if(iskey(buffer))
                {
                 printf("%s \t Keyword\n",buffer);

                }
                else
                printf("%s \t Identifier\n",buffer);
        }
        else
        {
                for(int k=0;k<i;k++)
                {
                        if(!isdigit(buffer[k]))
                        {
                                f=1;
                                break;
                        }
                }
                if(f==1)
                {
                        printf("%s \t Invalid token\n",buffer);
                }
                else
                {
                        printf("%s \t Number\n",buffer);
                }
        }
}

int ischar(char a)
{
        if((a>='a' && a<='z')||(a>='A' && a<='Z'))
        return 1;

        return 0;
}

int main()
{
        int fd=open("x.c",O_RDONLY);
        char c;int i=0;
        char buffer[100];
        bzero(buffer,100);
        while( read(fd,&c,1)!=0)
        {
 
                if(c=='#')
                {
                	   if(i!=0)
                        printf(buffer,i);
                         bzero(buffer,100);

                        char c2;char subbuf[100];
                        bzero(subbuf,100);
                        int j=0;
                        subbuf[j++]=c;
                        read(fd,&c2,1);
                      	subbuf[j++]=c2;
                      	
                        while(c2!='\n')
                        {
		                    read(fd,&c2,1);
		                    subbuf[j++]=c2;
                        }
                        subbuf[j-1]='\0';
                        printf("%s Macro\n",subbuf);
                        i=0;
                        continue;

                        
				}
                if(c==',')
                {
                         if(i!=0)
                        print(buffer,i);
                        printf(",       COMMA\n");
                        char c2;
                        read(fd,&c2,1);
                        while(c2=='\t'||c2==' ')
                         {read(fd,&c2,1);}
                        i=0;
                        buffer[i++]=c2;
                        continue;

                }
                if(c==';')
                {
                        if(i!=0)
                        print(buffer,i);
                        printf(";       SEMICOL\n");
                        char c2;
                        read(fd,&c2,1);
                        while(c2=='\t'||c2==' '||c2=='\n')
                         {read(fd,&c2,1);}
                        i=0;
                        buffer[i++]=c2;
                        continue;


                }
                  if(c=='/')
                {
                         if(i!=0)
                        printf(buffer,i);
                         bzero(buffer,100);
						//printf("...........");
                         char c2;char subbuf[100];
                        int j=0;
                        bzero(subbuf,100);
                        subbuf[j++]=c;
                        read(fd,&c2,1);
                        if(c2=='/')
                        {
                                 subbuf[j]=c2;j++;
                         read(fd,&c2,1);subbuf[j]=c2;j++;
                        while(c2!='\n')
                        {

                         read(fd,&c2,1);
                        subbuf[j++]=c2;
                        }
                        printf("%s COMMENT\n",subbuf);
                        i=0;
                        continue;

                        }
                        else if(c2=='*')
                        {
                        	
                        subbuf[j++]=c2;
                        while(!(c2=='/' && subbuf[j-2]=='*'))
                        {

                         read(fd,&c2,1);
                        subbuf[j++]=c2;
                        }
                        printf("%s COMMENT\n",subbuf);
                        i=0;
                        continue;
                        }
                      }
                 if(c=='\"')
                {
                         if(i!=0)
                        printf(buffer,i);
                         bzero(buffer,100);


                         char c2;char subbuf[100];
                         bzero(subbuf,100);
                        int j=0;
                        subbuf[0]=c;
                        j++;
                        read(fd,&c2,1);
                        subbuf[j]=c2;j++;
                        while(c2!='\"')
                        {

                         read(fd,&c2,1);
                        subbuf[j++]=c2;
                        }
                        printf("%s STRING\n",subbuf);
                        i=0;
                        continue;

                }
				 if(c=='['||c==']'||c=='('||c==')'|c=='{'||c=='}')
                {
                        if(i!=0)
                        print(buffer,i);
                        bzero(buffer,100);
                        printf("%c \t special sym\n",c);
                        i=0;
                        continue;
                }
                if(c=='\t'||c==' '||c=='\n')
                {
                     // printf("flushing\n");
                        if(i!=0)
                        print(buffer,i);
                        else
                        continue;
                        bzero(buffer,100);
        //              printf("%s this is buf\n",buffer);
                        char c2;
                        read(fd,&c2,1);
                        while(c2=='\t'||c2==' ')
                  {read(fd,&c2,1);}
                        i=0;
                        c=c2;
        //                printf("%s this is buf\n",buffer);

                        //continue;

                }
               
                if(c=='+'||c=='/'||c=='*'||c=='%'||c=='-')
                {
                        if(i!=0)
                        print(buffer,i);

                          bzero(buffer,100);
                        char lo[2];
                        lo[0]=c;read(fd,&lo[1],1);
                        if(lo[1]=='='||lo[1]==' '||(lo[0]=='+' && lo[1]=='+')||(lo[0]=='+' && lo[1]=='+'))
                        {
                                printf("%s \t Arithmatic OP\n",lo);
                                i=0;
                                continue;
                        }
                        if(isdigit(lo[1])||ischar(lo[1]))
                        {

                                buffer[0]=lo[1];
                                i=1;
                                lo[1]='\0';
                                printf("%s \t Arithmatic OP\n",lo);
                                continue;

                        }


                }
                if(c=='>'||c=='<'||c=='='||c=='!')
                {
                        if(i!=0)
                        print(buffer,i);
                         bzero(buffer,100);

                        char lo[2];
                        lo[0]=c;read(fd,&lo[1],1);
                        if(c=='=' && lo[1]!='=')
                        {
                                 buffer[0]=lo[1];
                                i=1;
                                lo[1]='\0';

                                 printf("%s \t Assignment OP\n",lo);
                                continue;

                        }
                        if(lo[1]=='='||lo[1]==' ')
                        {
                                printf("%s \t Relational OP\n",lo);
                                i=0;
                                continue;
                        }
                        if(isdigit(lo[1])||ischar(lo[1]))
                  {

                                buffer[0]=lo[1];
                                i=1;
                                lo[1]='\0';
                                printf("%s \t Relational OP\n",lo);
                                continue;

                        }

                }

               

                


                buffer[i]=c;
                i++;

        }
}

