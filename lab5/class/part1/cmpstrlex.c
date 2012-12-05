#include <stdio.h>
 
 int cmpstr(char *a, char *b)
 {
   
   int i = 0;
   while (1)
   {
      if (a[i] == 0)
      {
	  if (b[i] == 0)
	  {
	      return 0;
	  }
	  else
	  {
	      return 2;
	  }
      }
      
      if (b[i] == 0)
      {
	  if (a[i] == 0)
	  {
	      return 0;
	  }
	  else
	  {
	      return 1;
	  }
      }
      
      if (a[i] != b[i])
      {
	  if (a[i] > b[i])
	  {
	      return 1;
	  }
	  else
	  {
	    return 2;
	  }
      }
      
      i++;
     
   }
    return 0;
 }