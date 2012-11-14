#include <stdio.h>
#include "xsum.h"



int main(int argc, char **argv)
{
  
  FILE *stam = fopen("raz.bin" , "r");	
  int tmp = checksum(stam,0);
  printf("CHECK: %d\n",tmp);
  const char *optString = "hx:o:";
  int hFlag = 0;
  int oFlag = 0;
  int xFlag = 0;
  char *output;
  char *newPrefix;
  unsigned int CHECKSUM = 0;
  extern char *optarg;
  
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
	case 'x':
	  xFlag = 1;
	  CHECKSUM = atoi(optarg);
	  break;
	case 'o':
	  oFlag = 1;
	  output = optarg;
	  break;
      };
  }
  
  
  if (hFlag)
  {
      printf("-o OUTPUT   write the output into OUTPUT instead of PREFIX\n-x CHECKSUM verify that the checksum of the produced file is CHECKSUM\n");

      return;
  }
  
  newPrefix = argv[argc - 1];
  
  //create a new file
  FILE *newFile = fopen(oFlag == 0? newPrefix:output , "wb");	
   
   int i;
   char buffer[1];
   int count;
   unsigned int checksum1; //the real sum of a file
   unsigned int checksum2; //the checksum value which appears at the begin of the file   
   int isFirstFileFlag = 0;
   int fileCounter = 1;
   char tmpbuf[15];
   char newName[100];
   
   
   while (1)
   {
     
      //get new name
      sprintf(tmpbuf, "%d", fileCounter);
      snprintf(newName, 100, "%s%s%s",newPrefix,".", tmpbuf);
      
     FILE *file = fopen(newName, "rb");
     if (file == 0)
     {
	break;
     }
     fileCounter++;
    
     //skip 4 bytes
     fseek(file,4, SEEK_SET); 
     
     //write the small file content to the new file
     while (1)
     {
	count = fread(buffer, 1, 1, file);
	if (count == 0)
	{
	    break;
	}
	fwrite(buffer,1,1, newFile);

     }
     
     //checksum validation (small files)
     checksum1 = checksum(file, 1);
     rewind(file);
     fread(&checksum2, 1,4,file);
     if (checksum1 != checksum2)
     {
	printf("Invalid Checksum in file number: %d\n", i);
	fclose(file);
	remove(newPrefix);
	break;
     }
          
     	fclose(file);
   }
   
    
    //checksum validation (new large file)
    int crc;
    if (xFlag)
    {
      
	fclose(newFile);
	newFile = fopen(oFlag == 0? newPrefix:output , "r");
	if (checksum(newFile, 0) != CHECKSUM)
	{
	    printf("X: Invalid Chcksum.\n");
	}
	else
	{
	    printf("X: Checksum is Valid.\n");
	}
    }
    
    fclose(newFile);
     
    return 0;
}
