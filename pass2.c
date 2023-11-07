#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

struct symbol
{
	char sym[10];
	int addr;
} S[MAX] = { {"A", 103},{"B", 106},{"C", 107}};

char optab[][6] = {"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"};
char regtab[][5] = {"AREG", "BREG", "CREG", "DREG"};
char condtab[][4] = {"LT", "LE", "EQ", "GT", "GE", "ANY"};
char adtab[][7] = {"START", "END", "ORIGIN", "EQU", "LTORG"};

FILE *fs, *ft;
char source[20], buffer[80], tok1[10], tok2[10], tok3[10], tok4[10], tok5[10];
int lc, sc = 3;

void passtwo()
{
	int i, j, k, n, p;
	char temp[20];

	if ((fs = fopen("ic.txt", "r")) == NULL)
	{
		printf("\n\nError In Opening ic.txt");
		return;
	}
	if ((ft = fopen("target.txt", "w")) == NULL)
	{
		printf("\n\nError In Opening ic.txt");
		return;
	}

	lc = 0;

	while (fgets(buffer, 80, fs))
	{
		n = sscanf(buffer, "%s%s%s%s%s", tok1, tok2, tok3, tok4, tok5);
		switch (n)
		{
		case 4:
			if (strcmp(tok1, "(AD,") == 0)
			{
				tok4[strlen(tok4) - 1] = '\0';
				lc = atoi(tok4) - 1;
				break;
			}

			if (strcmp(tok1, "(DL,") == 0)
			{
				tok2[strlen(tok2) - 1] = '\0';
				tok4[strlen(tok4) - 1] = '\0';

				i = atoi(tok2);
				j = atoi(tok4);

				if (i == 2) // A DS 2
				{
					for (k = 0; k < j; k++)
					{
						fprintf(ft, "%d)\n", lc++);
					}
					lc--;
				}
				else // ONE DC 1
				{
					fprintf(ft, "%d) %d\n", lc, j);
				}
			}
			break;

		case 5:
			tok2[strlen(tok2) - 1] = '\0';
			tok5[strlen(tok5) - 1] = '\0';

			i = atoi(tok2);
			j = atoi(tok3);
			k = atoi(tok5);

			if (strcmp(tok4, "(S,") == 0)
			{
				fprintf(ft, "%d) %02d %d %03d\n", lc, i, j, S[k].addr);
			}
			break;
		} // switch
		lc++;
	} // while
}

void print_symb()
{
	int p = 0;
	printf("\n\tsymbol\taddress");
	for (int i = 0; i < sc; i++)
	{
		printf("\n\t%s\t%d", S[p].sym, S[p].addr);
	}
}

int main()
{
	printf("\n\n\tSYMBOL TABLE::::\n");
	print_symb();

	passtwo();

	return 0;
}



// (AD, 01) (C, 200)
// (IS, 04) 1 (S, 00)
// (IS, 05) 2 (S, 01)
// (IS, 01) 2 (S, 02)
// (AD, 05)
// (IS, 02) 3 (S, 03)
// (DL, 2) (C, 2)
// (DL, 2) (C, 2)
// (AD, 02)
