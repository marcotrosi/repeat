#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[])
{
   unsigned long NumOfRepitions = strtoul(argv[1], NULL, 10);
   unsigned long i = 0u;
   char String[1024] = {'\0'};
   FILE* fd = stdin;

   if(isatty(fileno(fd)))
   {
      /* is connected to terminal, string not coming from pipe
         take second arg */
      strcpy(String, argv[2]);
   }
   else
   {
      /* program used in pipe
         take string from pipe */
      fgets(String, 1024, stdin);
   }

   for(i=0u; i < NumOfRepitions ; i++)
   {
      printf("%s", String);
   }

   return 0;
}
