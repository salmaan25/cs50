#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct trieblock node;

struct trieblock 
{
	char alphabet;
	char reply[5];
	node* pnt;
};
typedef node *node_pnt;

typedef struct 
{
	node_pnt first;
	int count;
}head;

void load(FILE* dict, head* header);
void init(node_pnt pointer);
int isCheck(char c);
void check(head* header, char key[], int len);

int main(int argc, char* argv[])
//int main(void)
{
	FILE* dict = fopen(argv[1], "r");
	
	head* header = malloc(sizeof(head));
	(*header).count = 0;
	(*header).first = NULL;
	/*node triehead = malloc(26 * sizeof(trieblock));
	init(triehead);*/
	load(dict, header);


	

	node_pnt tempo = header->first;
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
	char tocheck[50];
	scanf("%s", tocheck);
	check(header, tocheck, strlen(tocheck));

	return 0;
}

void load(FILE* dict, head* header)
{
	node_pnt current_node = NULL;
	node_pnt head_node = NULL;
	node_pnt temp_node = NULL;
	char temp_char;
	temp_char = fgetc(dict);
	char prev_char = temp_char;
	int counter = 0;
	head_node = malloc(26 * sizeof(node));
	init(head_node);
	(*header).first = head_node;
	while(isCheck(temp_char) == 1)
	{
		current_node = head_node;
		prev_char = temp_char;
		temp_char = fgetc(dict);

		while(temp_char != '\n')
		{
			if((current_node[prev_char - 'a']).pnt == NULL)
			{
				temp_node = malloc(26 * sizeof(node));
				init(temp_node);
				(current_node[prev_char - 'a']).pnt = temp_node;
				current_node = temp_node;
			}
			else
			{
				current_node = (current_node[prev_char - 'a']).pnt;
			}
			prev_char = temp_char;
			temp_char = fgetc(dict);
		}
		strcpy((current_node[prev_char - 'a']).reply, "yes");
		temp_char = fgetc(dict);
		counter++;
	}
	(*header).count = counter;
}


void init(node_pnt pointer)
{
	int i;
	for(i = 0; i < 26; i++)
	{
		(pointer[i]).alphabet = (char)('a' + i);
		(pointer[i]).pnt = NULL;
	}
	/*for(i = 0; i < 26; i++)
	{
		printf("%c ", (pointer[i]).alphabet);
	}
	printf("\n");*/
	//(pointer[26]).aphabet = "'";
}


int isCheck(char c)
{
	if((c < 'a' || c > 'z') && c != '\n')
		return 0;
	else
		return 1;
}



void check(head* header, char key[], int len)
{
	int i;
	node_pnt start = NULL;
	start = header->first; 
	for(i = 0; i < len; i++)
	{
		char cha = key[i];
		if(i != len - 1)
		{
			if((start[cha - 'a']).pnt == NULL)
			{
				printf("mis-spelled\n");
				break;
			}
			else
			{
				start = (start[cha - 'a']).pnt;
			}
		}
		else
		{
			if(strcmp(((start[cha - 'a']).reply), "yes") == 0)
			{
				printf("correctly spelled\n");
				break;
			}
			else
			{
				printf("mis-spelled\n");
			}
		}
	}
}