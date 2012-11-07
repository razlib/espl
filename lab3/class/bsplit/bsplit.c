#include <stdio.h>

int main(int argc, char **argv)
{
    int chunkSize = atoi(argv[1]);
    char *fileName = argv[2];
    FILE *file;
    char buffer[1024];
    file = fopen(fileName, "rb");
    int count = 0;
    int fileCounter = 1;
    char tmpbuf[15];	
    char newName[100];
    
    printf("Chunk Size: %d\n", chunkSize);
    while (1)
    {
      
      count = fread(buffer, 1, chunkSize, file);
      	printf("Count %d\n",count);
	
	//create a new file
	//char str[100];
	//strcpy(str,"Hello");
	
      
	sprintf(tmpbuf, "%d", fileCounter);
	snprintf(newName, 100, "%s%s%s",fileName,".", tmpbuf);
	FILE *fp = fopen(newName, "wb");		
	fwrite(buffer,count,1, fp);	
	fileCounter++;
	fclose(fp);

		
	
      if (count != chunkSize)
      {

	break;
      }   
    }
    
    
    fclose(file);
}
