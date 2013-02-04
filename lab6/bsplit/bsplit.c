#include <stdio.h>
#include "xsum.h"

int main(int argc, char **argv)
{
  
  
   int chunkSize = 10;
   char *fileName;;
   char buffer[1024];
   int count = 0;
   int fileCounter = 1; //helps to set the files names
   char tmpbuf[15];	
   char newName[100];
   unsigned int mychceksum = 0;
   //unsigned int bigChecksum = 0;


  fileName = argv[1];
  
  
    FILE *bigFile = fopen(fileName, "rb"); 
   
    /*if (xFlag)
    {
      bigChecksum = checksum(bigFile, 0);
      printf("Checksum: %d\n", bigChecksum);
      rewind(bigFile);
    }*/
    
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
      //mychceksum = checksum(smallFile, 1); 
      rewind(smallFile);
      //fwrite(&mychceksum,4,1, smallFile);

   
      if (count != chunkSize)
      {

	break;
      } 
      
       fclose(smallFile);
    }
    

    
   fclose(bigFile);

     

}
