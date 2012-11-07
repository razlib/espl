 
#include <stdio.h>

int main(int argc, char ** argv)
{
 
  /*int c;
  int hflag = 0;
  int xflag = 0;
  while ((c = getopt (argc, argv, "hx")) != -1)
  {
    switch (c)
    {
      case 'h':
	hflag = 1;
	printf("H\n");
	break;
      case 'x':
	printf("X\n");
	xflag = 1;
	break;
      default:
	printf("Invalid Argument.\n");
	break;
    }
  }*/
  

    int i = 0;
    FILE *file;
    unsigned int checksum = 0;
    unsigned int word;
    char *fileName = argv[1];
    int count;
    file = fopen(fileName, "r");
    while (1)
    {
      word = 0;
      count = fread(&word, 1, 4, file);
      checksum ^= word;
      if (count != 4)
      {
	printf("Count %d\n",count);
	break;
      }
      
    }
 
 printf("CHECKSUM: %d\n", checksum);
 return 0; 
}