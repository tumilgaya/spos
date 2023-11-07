#include <iostream>
#include <string.h>
#define MAX 20
using namespace std;

struct Symbol{
    char sym[10];
    int add;
}S[MAX];

struct LitTab {
    char lit[10];
    int add;
}L[MAX];

char optab[][7] = {"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char regtab[][7] = {"AREG","BREG","CREG","DREG"};
char adtab[][7] = {"START","END","ORIGIN","EQU","LTORG"};
char condtab[][7] = {"LT","LE","EQ","GT","GE","ANY"};


FILE *fs,*ft;
char buffer[80],source[80],tok1[80],tok2[80],tok3[80],tok4[80],tok5[80];
int lc = 0, sc = 0, poolcnt = 0, litcnt = 0;
int pooltab[10];

int search_optab(char *s) {
    for (int i = 0; i < 11; i++)
    {
        if(strcmp(optab[i],s) == 0) {
            return i+1;
        }
    }
    return -1;
}

int search_adtab(char *s) {
    for (int i = 0; i < 5; i++)
    {
        if(strcmp(adtab[i],s) == 0) {
            return i+1;
        }
    }
    return -1;
}

int search_regtab(char *s) {
    for (int i = 0; i < 4; i++)
    {
        if(strcmp(regtab[i],s) == 0) {
            return i+1;
        }
    }
    return -1;
}

int search_condtab(char *s) {
    for (int i = 0; i < 6; i++)
    {
        if(strcmp(condtab[i],s) == 0) {
            return i+1;
        }
    }
    return -1;
}

int search_symtab(char *s) {
    for (int i = 0; i < sc; i++)
    {
        if(strcmp(S[i].sym,s) == 0) {
            return i+1;
        }
    }
    return -1;
}

int search_littab(char *s) {
    for (int i = pooltab[poolcnt]; i < litcnt; i++)
    {
        if(strcmp(L[i].lit, s) == 0) {
            return i+1;
        }
    }
    return -1;
}

void pass1() {
    int p;
    int numberOfTokens,i = 0, j = 0, k = 0;

    fs = fopen(source,"r");

    if(fs == NULL) {
        printf("FILE DOESN'T EXIST...");
        return;
    }

    ft = fopen("IC.txt","w");

    while(fgets(buffer,80,fs)) {
        numberOfTokens = sscanf(buffer,"%s%s%s%s",tok1,tok2,tok3,tok4);
        // printf("%d ", numberOfTokens);

        switch(numberOfTokens) {
            case 1: //LITORG END
                i = search_adtab(tok1);

                if(i == 2 || i == 5) {  //i = 2 means END and i = 5 means LITORG
                    for (j = pooltab[poolcnt]; j < litcnt; j++)
                    {
                        L[j].add = lc++;
                    }

                    lc--;

                    pooltab[++poolcnt] = litcnt;

                    //AD = assemblyDirectiveTable
                    //(AD, positionInArrTable)
                    fprintf(ft,"(AD, %02d)\n",i);
                    break;
                }

            case 2: //START
                i = search_adtab(tok1);

                if(i == 1) {
                    lc = atoi(tok1) - 1;

                    //tok1 = START, tok2 = 200
                    //(AD,positionInArrTable) (C,200)
                    fprintf(ft,"(AD, %02d) (C, %s)\n",i,tok2);
                    break;
                }

            case 3:
                i = search_optab(tok1);

                if(i >= 1 && i <= 8) {  //movem or mover add sub 

                    //for movem areg, '=5'
                    tok2[ strlen(tok2) - 1 ] = '\0'; //removing ','
                    //search reg
                    k = search_regtab(tok2);

                    if(tok3[0] == '=') {    //if value is there then store

                        j = search_littab(tok3);

                        if(j == -1) {   //if value not present in littab then entry

                            strcpy( L[litcnt].lit, tok3 );
                            fprintf(ft, "(IS, %02d) %d (L, %02d)\n",i,k,litcnt);
                            litcnt++;

                        } else {
                            fprintf(ft,"(IS, %02d) %d (L, %02d)\n",i,k,j);
                        }
                        break;
                    } else {    //movem areg, B

                        p = search_symtab(tok3);
                        if(p == -1) {   //if '=5' not present in symtab
                            //add
                            strcpy(S[sc].sym,tok3);
                            fprintf(ft,"(IS, %02d) %d (S, %02d)\n",i,k,sc);
                            sc++;

                        } else {
                            fprintf(ft,"(IS, %02d) %d (S, %02d)\n", i,k,p);
                        }
                        break;
                    }
                }

                //A DS 2
                if(strcmp(tok2, "DS") == 0) {

                    p = search_symtab(tok1);

                    if(p == -1){ //not found the register that means it's not in symtab
                        strcpy(S[sc].sym, tok1);
                        S[sc].add = lc;
                        
                        fprintf(ft, "(DL, 2) (C, %s)\n", tok3);
                        sc++;
                    } else {
                        S[p].add = lc;
                        fprintf(ft,"(DL, 2) (C, %s)\n", tok3);
                    }

                    lc = lc + atoi(tok3) - 1;
                    break;
                }
        }
        lc++;
    }
    fclose(ft);
}

void printFile(char *target) {
    FILE *fp;
    fp = fopen(target, "r");

    if(fp == NULL) {
        printf("Cannot open file, File doesn't exist");
        return;
    }

    printf("\n\n");
    while (fgets(buffer,80,fp))
    {
        printf("%s",buffer);
    }
    
    fclose(fp);
}

void print_littab() {
    printf("LITERAL\tTABLE:\n");

    for (int i = 0; i < litcnt; i++)
    {
        printf("%s\t\t%d\n",L[i].lit,L[i].add);
    }
}

void print_symtab() {
    printf("SYBMOL\tTABLE:\n");

    for (int i = 0; i < sc; i++)
    {
        printf("%s\t\t%d\n",S[i].sym,S[i].add);
    }   
}

int main()
{
    printf("Enter source file: ");
    scanf("%s", source);

    printf("Source file is: ");
    printFile(source);

    pass1();

    printf("\n\nliteral table: \n");
    print_littab();

    printf("\n\nsymbol table: \n");
    print_symtab();

    return 0;
}