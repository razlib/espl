#include <stdio.h>
#include "xsum.h"

int main(int argc, char **argv)
{
   FILE *newFile = fopen("NEWFILE.bin", "wb");	
   int i;
   char buffer[1];
   int count;
   for (i = 1; i < argc; i++)
   {
     printf("File Name: %s\n", argv[i]);
     FILE *file = fopen(argv[i], "rb");
    
     while (1)
     {
	count = fread(buffer, 1, 1, file);
	if (count == 0)
	{
	    break;
	}
	fwrite(buffer,1,1, newFile);

     }
     	fclose(file);
   }
    fclose(newFile);
     int crc = checksum("NEWFILE.bin");
      printf("Checksum: %d\n", crc);
     
    return 0;
}
