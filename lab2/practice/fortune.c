#include <stdio.h>

int main (int argc, char** argv)
{
    int count = 0;
    int i = 0;
    int randomLineNumber;
    FILE *file;
    char buffer[128];
    char *fileName = argv[1];
    file = fopen(fileName, "r");
    
    while (fgets(buffer, 128, file) != NULL)
    {
      count++;
    }
    
    fclose(file);
    
    
    srand(time(NULL));
    randomLineNumber = rand() % count;
    file = fopen(fileName, "r");  
    
    for (i = 0; i < randomLineNumber; i++)
    {
	fgets(buffer, 128, file);
    }
    
    fclose(file);
    printf("%d:  %s",i, buffer);
    return 0;
}
