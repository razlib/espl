#include <stdio.h>
#include <string.h>
#include "fgetname.h"
#include "namelist.h"

char* KEY_WORDS[] = {"auto", "else", "long", "switch", "break", "enum", "typedef", "case", "return", "union", "char", "float", "short", "unsigned", "const", "for", "signed", "void", "countinue","goto","sizeof","default", "if", "static", "while", "do", "int", "struct", "double"};

namelist NAME_LIST;

void printFileWords(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    NAME_LIST = make_namelist();
    char buffer[128];
    while (fgetname(buffer, 128, file) != NULL)
    {
      if (!isKeyWord(buffer))
      {
	  printf("%s\n", buffer);
	  add_name(NAME_LIST, buffer);  
      }
    }
    
    int i;
    for (i = 0; i < NAME_LIST->size; i++)
    {
	printf("NAME: %s  ", NAME_LIST->names[i].name);
	printf("COUNT: %d\n", NAME_LIST->names[i].count);
    }
    fclose(file);
    
    
}

int isKeyWord(char *word)
{
    int i;
    for (i = 0; i < 29; i++)
    {
	if (strcmp(word, KEY_WORDS[i]) == 0)
	{
	    return 1;
	}
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    for (i = 1; i < argc; i++)
    {
      printFileWords(argv[i]);
    }
    return 0;
}





