%{
%}
ID [a-zA-Z]
W [ \t]
FL	\.[0-9]*
EX 	E[+\-][0-9]+	
%%
auto|break |case|char|const|continue|do|double|else|enum|extern|float |
for|goto|if|int|long|register|return|short|signed|sizeof|static|struct |
switch|typedef|union|unsigned|void|volatile|while|printf|scanf		printf("%s \t KEYWORD\n",yytext);	
{W}*#.*		printf("%s \t MACRO \n",yytext);
[ \t\n] 	;
[a-zA-Z][a-zA-Z0-9]*		printf("%s \t IDENTIFIER\n",yytext);
[0-9]+[a-zA-Z]+ 			printf("%s \t UNDEFINED TOKEN\n",yytext);
[+\-]?([1-9][0-9]*|0){FL}?{EX}?	printf("%s \t INTEGER \n",yytext);
[<>!](=)?				printf("%s \t RELATIONAL OP\n",yytext);
==						printf("%s \t RELATIONAL OP\n",yytext);
=						printf("%s \t ASSIGNMENT OP\n",yytext);
<<<<<<< HEAD
\-\- | ++		printf("%s \t ARITHMATIC OP\n",yytext);
[+\-*/](=)?			printf("%s \t ARITHMATIC OP\n",yytext);
(\(|\)|\[|\]|\{|\})		printf("%s \t PAREN \n",yytext);
\"(.|\n)*\" 	 				printf("%s \t STRING \n",yytext);
\/\*(.|\n)*\*\/|\/\/.*$				printf("%s \t COMMENT \n",yytext);
=======
[+\-*/](=)?			printf("%s \t ARITHMATIC OP\n",yytext);
(\(|\)|\[|\]|\{|\})		printf("%s \t PAREN \n",yytext);
\".*\" 	 				printf("%s \t STRING \n",yytext);
\/\*.*\*\/|\/\/.*$				printf("%s \t COMMENT \n",yytext);
>>>>>>> b6825b6da1d91d1240a442b7bb459a4f1259af2d
,						printf("%s \t COMMA \n",yytext);
[~&\|^]|(\&\&)|(\|\|)	printf("%s \t LOGICAL OP \n",yytext);
.  				ECHO;
%%
int main(int argc,char* argv[])
{
	if(argc>1)
	{
	yyin=fopen(argv[1],"r");
	yylex();
	fclose(yyin);
	}
	else
	{
		yylex();
	}
	return 0;
}
