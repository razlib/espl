#include <stdio.h>
#include "xsum.h"

int checksum(char *fileName)
{
    int count;
   unsigned int checksum = 0;
   unsigned int word;
      FILE *file = fopen(fileName, "r");
   while (1)
    {
      word = 0;
      count = fread(&word, 1, 4, file);
      checksum =  checksum ^ word;
      if (count != 4)
      {
	break;
      } 
    }
    return checksum;
}
 
