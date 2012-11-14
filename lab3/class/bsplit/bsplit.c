#include <stdio.h>
#include "xsum.h"

int main(int argc, char **argv)
{
  
  
   const char *optString = "hb:x";
   int hFlag = 0;
   int bFlag = 0;
   int xFlag = 0;
   int bSIZE = 0;
   extern char *optarg;
  
   int chunkSize = 1024;
   char *fileName;;
   char buffer[1024];
   int count = 0;
   int fileCounter = 1; //helps to set the files names
   char tmpbuf[15];	
   char newName[100];
   unsigned int mychceksum = 0;
   unsigned int bigChecksum = 0;

      //getopt
  int opt = 0;
  while (opt != -1)
  {
      opt = getopt(argc, argv, optString);
      
      switch (opt)
      {
	case 'h':
	  hFlag = 1;
	  break;
	case 'b':
	  bFlag = 1;
	  bSIZE = atoi(optarg);
	  break;
	case 'x':
	  xFlag = 1;
	  break;
      };
  }
   
  
  if (hFlag)
  {
      printf("-b SIZE put at most SIZE bytes per output file\n-x print the checksum of FILE on the standard output\n");

      return;
  }
  
  if (bFlag)
  {
      chunkSize = bSIZE;
  }
  fileName = argv[argc - 1];
  
  
  
    FILE *bigFile = fopen(fileName, "rb"); 
   
    if (xFlag)
    {
      bigChecksum = checksum(bigFile, 0);
      printf("Checksum: %d\n", bigChecksum);
      rewind(bigFile);
    }
    
    while (1)
    {
     
		  
      //read chunk from the original file
      count = fread(buffer, 1, chunkSize, bigFile); 
      
      //set new name
      sprintf(tmpbuf, "%d", fileCounter);
      snprintf(newName, 100, "%s%s%s",fileName,".", tmpbuf);
      
      //create a new file
      FILE *smallFile = fopen(newName, "w+");
      
	    
      //save 4 bytes for checksum
      fwrite(&mychceksum,4,1,smallFile);
      
      //write the chunk to the file 
      fwrite(buffer,count,1, smallFile);
      
      fileCounter++;			
   
       //calc checksum
      mychceksum = checksum(smallFile, 1); 
      rewind(smallFile);
      fwrite(&mychceksum,4,1, smallFile);

   
      if (count != chunkSize)
      {

	break;
      } 
      
       fclose(smallFile);
    }
    

    
   fclose(bigFile);

     

}
