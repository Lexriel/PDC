#include <stdio.h>

int main() {
	int i, espace = 0, indent=0, com = 0;
	char c;

	do { 
		c = getchar();
		if(c!='\t'){		
			if(c==123){			
				printf("\n");
				for(i = 0; i<indent; i++)
					printf("\t");
				printf("%c",123);
				indent++;		
				printf("\n");
				for(i = 0; i<indent; i++)
					printf("\t");
			}	
			else if(c==125){
				indent--;
				printf("\n");
				for(i = 0; i<indent; i++)
					printf("\t");
				printf("%c",125);
				printf("\n");
				for(i = 0; i<indent; i++)
					printf("\t");
			}
			else if(c==10){
				espace=0;
				if(com==1)
					printf(" */");												
				printf("\n");
				for(i = 0; i<indent; i++)
					printf("\t");
				if(com==1)
					printf("/* ");
			}
			else
			{ 
				if(c==47)
				{
					if((c = getchar()) == 42)
					{
						com=1;
						espace=1;
						printf("\n");
						for(i = 0; i<indent; i++)
							printf("\t");
						printf("/*");
					}
					else
					{
						espace=1;
						printf("/%c",c);
					}		
				}
				else if(c==42) 
				{
						if((c = getchar()) == 47)
						{
 							com=0;
							espace=1;
							printf("*/\n");				
						}
						else 
						{
							espace=1;
							printf("*%c",c);
						}
					}	
				else if(c==32 && espace == 0){}	
				else if(c==32 && espace != 0)
				printf("%c",c);				

				else if(espace == 0 &&  c!=32)
				{
					 espace = 1;
					 printf("%c",c);
				}
				else 
					printf("%c",c);
			}
		}

	}	while(c != EOF);
			return 0;
}	

	
