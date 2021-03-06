#include <stdio.h>
#include "xsum.h"

int checksum(FILE *file, int skip4bytes)
{
    int count;
   unsigned int checksum = 0;
   unsigned int word;
      
   rewind(file);
   if (skip4bytes)
   {
      //start calc the checksum from the fifth byte
      //because the first 4 are saved for the checksum
      fseek(file,4, SEEK_SET); 
   }
      
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


 
