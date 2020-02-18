#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct trieblock123;
typedef struct trieblock123 trieblock;
typedef trieblock *node;
struct trieblock123 
{
	char alphabet;
	char reply[5];
	node pnt;
};


typedef struct 
{
	node first;
	int count;
}head;

void load(FILE* dict, head* header);
void init(node pointer);
//int main(int argc, char* argv[])
int main(void)
{
	FILE* dict = fopen("large", "r");
	
	head* header = malloc(sizeof(head));
	(*header).count = 0;
	(*header).first = NULL;
	/*node triehead = malloc(26 * sizeof(trieblock));
	init(triehead);*/
	//load(dict, header);


	node curtrie = NULL;
	node temptrie = NULL;
	node temptrie1 = NULL;
	char temp;
	temp = fgetc(dict);
	//printf("%c\n", temp);
	int counter = 0;
	temptrie = (node)(malloc(26 * sizeof(trieblock)));
	int i;
	for(i = 0; i < 26; i++)
	{
		(temptrie[i]).alphabet = (char)(((int)('a')) + i);
		(temptrie[i]).pnt = NULL;
	}
	if(counter == 0)
	{
		(*header).first = temptrie;
	}
	while(((int)(temp) <= (int)('z') && (int)(temp) >= (int)('a')) || temp == '\n')
	{
		if(((int)(temp) > (int)('z') || (int)(temp) < (int)('a')) && temp != '\n')
			break;
		curtrie = temptrie;

		while(temp != '\n')
		{
			char temp1;
			temp1 = fgetc(dict);
			if((curtrie[(int)(temp) - (int)('a')]).pnt == NULL) //&& (int)(temp1) <= (int)('z') && (int)(temp1) >= (int)('a') && temp1 != '\n')
			{
				    
				//fseek(dict, -1 * sizeof (char), SEEK_CUR);
				if(temp1 != '\n')
				{
					//printf("%c\n", temp);
					temptrie1 = (node)(malloc(26 * sizeof(trieblock)));
					for(i = 0; i < 26; i++)
					{
						(temptrie1[i]).alphabet = (char)(((int)('a')) + i);
						(temptrie1[i]).pnt = NULL;
					}
					/*for(i = 0; i < 26; i++)
					{
						printf("%c ", (temptrie1[i]).alphabet);
					}
					printf("\n");*/
					(curtrie[(int)(temp) - (int)('a')]).pnt = temptrie1;
					curtrie = temptrie1;
				}
				else
				{
					strcpy((curtrie[(int)(temp) - (int)('a')]).reply, "yes");
				}
			}
			/*else if((((int)(temp1) > (int)('z') || (int)(temp1) < (int)('a')) && temp1 != '\n'))  //searches for EOF
			{
				break;
			}*/
			else if((curtrie[(int)(temp) - (int)('a')]).pnt != NULL) //&& (int)(temp1) <= (int)('z') && (int)(temp1) >= (int)('a') && temp1 != '\n')
			{
				curtrie = (curtrie[(int)(temp) - (int)('a')]).pnt;
			}
			/*else if(temp1 == '\n')
			{
				strcpy((curtrie[(int)(temp) - (int)('a')]).reply, "yes");
				//printf("%s\n", (curtrie[(int)(temp) - (int)('a')]).reply);
			}*/
			//if((curtrie[(int)(temp) - (int)('a')]).pnt != NULL || (int)(temp1) > (int)('z') || (int)(temp1) < (int)('a') || temp1 == '\n')
			fseek(dict, -1 * sizeof(char), SEEK_CUR);	
			//prevtrie = curtrie;
			temp = fgetc(dict);
		}
		

		if(temp == '\n')
		{
			temp = fgetc(dict);
		}

		counter++;
	}
	(*header).count = counter;


	node tempo = temptrie;
	printf("%c", (tempo[(int)('h') - (int)('a')]).alphabet);
	tempo = (tempo[(int)('h') - (int)('a')]).pnt;
	printf("%c", (tempo[(int)('e') - (int)('a')]).alphabet);
	tempo = (tempo[(int)('e') - (int)('a')]).pnt;
	printf("%c", (tempo[(int)('l') - (int)('a')]).alphabet);
	tempo = (tempo[(int)('l') - (int)('a')]).pnt;
	printf("%c", (tempo[(int)('l') - (int)('a')]).alphabet);
	tempo = (tempo[(int)('l') - (int)('a')]).pnt;
	printf("%c", (tempo[(int)('o') - (int)('a')]).alphabet);
	printf("%s", (tempo[(int)('o') - (int)('a')]).reply);
	tempo = (tempo[(int)('o') - (int)('a')]).pnt;
	printf("%c\n", (tempo[(int)('s') - (int)('a')]).alphabet);
	printf("%s", (tempo[(int)('s') - (int)('a')]).reply);
	tempo = (tempo[(int)('s') - (int)('a')]).pnt;
	if(tempo == NULL)
		printf("NULL\n");
	char tocheck[100];
	scanf("%s", tocheck);
	printf("%s\n", tocheck);
	i = 0;
	node start = NULL;
	start = temptrie;
	/*char tmpop = tocheck[0];
	while(tmpop != '\n')
	{
		
		if((start[(int)(tmpop) - (int)('a')]).pnt == NULL)
		{
			if(strcmp(((start[(int)(tmpop) - (int)('a')]).reply), "yes") == 0)
			{
				printf("correctly spelled\n");
				break;
			}
			else
			{
				printf("misspelled\n");
				break;
			}
		}
		else
		{
			start = (start[(int)(tmpop) - (int)('a')]).pnt;
		}
		i++;
		tmpop = tocheck[i];
	}*/
	for(i = 0; i < strlen(tocheck); i++)
	{
		char cha = tocheck[i];
		if(i != strlen(tocheck) - 1)
		{
			if((start[(int)(cha) - (int)('a')]).pnt == NULL)
			{
				printf("missspelled\n");
				break;
			}
			else
			{
				start = (start[(int)(cha) - (int)('a')]).pnt;
			}
		}
		else
		{
			if(strcmp(((start[(int)(cha) - (int)('a')]).reply), "yes") == 0)
			{
				printf("correctly spelled\n");
				break;
			}
		}
	}
	return 0;
}
/*
void load(FILE* dict, head* header)
{
	//node prevtrie = NULL; 
	node curtrie = NULL;
	node temptrie = NULL;
	node temptrie1 = NULL;
	char temp;
	temp = fgetc(dict);
	int counter = 0;
	temptrie = (node)(malloc(26 * sizeof(trieblock)));
	init(temptrie);
	if(counter == 0)
	{
		(*header).first = temptrie;
	}
	while(temp != EOF)
	{
		if((int)(temp) > (int)('z') || (int)(temp) < (int)('a') || temp != '\n')
			break;
		curtrie = temptrie;

		while(temp != '\n')
		{
			char temp1;
			temp1 = fgetc(dict);
			if((curtrie[(int)(temp) - (int)('a')]).pnt == NULL && temp1 != '\n' && ((int)(temp1) < (int)('z') && (int)(temp1) > (int)('a') && temp1 != '\n'))
			{
				fseek(dict, -1 * sizeof(char), SEEK_CUR);
				temptrie1 = (node)(malloc(26 * sizeof(trieblock)));
				init(temptrie1);
				(curtrie[(int)(temp) - (int)('a')]).pnt = temptrie1;
				curtrie = temptrie1;
			}
			else if(((int)(temp1) > (int)('z') || (int)(temp1) < (int)('a') || temp1 != '\n'))
			{
				break;
			}
			else if(temp1 == '\n')
			{
				strcpy((curtrie[(int)(temp) - (int)('a')]).reply, "yes");
				printf("%s\n", (curtrie[(int)(temp) - (int)('a')]).reply);
			}
			if((curtrie[(int)(temp) - (int)('a')]).pnt != NULL || temp1 == '\n' || ((int)(temp1) > (int)('z') || (int)(temp1) < (int)('a') || temp1 != '\n'))
				fseek(dict, -1 * sizeof(char), SEEK_CUR);	
			//prevtrie = curtrie;
			temp = fgetc(dict);
		}
		

		if(temp == '\n')
		{
			temp = fgetc(dict);
		}

		counter++;
	}
	(*header).count = counter;
}


void init(node pointer)
{
	int i;
	for(i = 0; i < 26; i++)
	{
		(pointer[i]).alphabet = (char)(((int)('a')) + i);
		(pointer[i]).pnt = NULL;
	}
	for(i = 0; i < 26; i++)
	{
		printf("%c ", (pointer[i]).alphabet);
	}
	printf("\n");
	//(pointer[26]).aphabet = "'";
}
*/