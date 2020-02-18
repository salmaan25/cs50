#include <stdio.h>


int main(void)
{
	FILE* fp = fopen("dictionary.txt", "r");
	FILE* out = fopen("dictionary123.txt", "w");
	char c = fgetc(fp);
	while(c != EOF)
	{
		if((int)(c) > (int)('z') || (int)(c) < (int)('a') || c != '\n')
			break;
		while(c != '\n')
		{
			fwrite(&c, sizeof(char), 1, out);
			c = fgetc(fp);
		}
		if(c == '\n')
		{
			fprintf(out, " ");
			c = fgetc(fp);
		}
	}
	fclose(fp);
	fclose(out);
	return 0;
}