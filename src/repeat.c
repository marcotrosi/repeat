#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef char bool;
#define true ((bool)1)
#define false ((bool)0)
#define MAX_STR_LEN 4096
#define MAX_SEP_LEN  512

/* functions <<< */
void printHelp(void)
{
   printf("USAGE: repeat [-v] [-h] [-n] [-s <sep>] repetitions [string]\n");
   printf("\n");
   printf("OPTIONS:\n");
   printf("  -s <sep>  optional separator string\n");
   printf("  -n        do not output the trailing newline\n");
   printf("  -v        print version info\n");
   printf("  -h        print help text\n");
   printf("\n");
   printf("EXAMPLES:\n");
   printf("  repeat 2 foo\n");
   printf("    => foofoo\n");
   printf("  repeat -s ',' 3 foo\n");
   printf("    => foo,foo,foo\n");
   printf("  repeat -- -2 foo\n");
   printf("    => oofoof\n");
}

void printUsage(void)
{
   fprintf(stderr, "USAGE: repeat [-v] [-h] [-n] [-s <sep>] repetitions [string]\n");
   fprintf(stderr, "run 'repeat -h' for more information\n");
}

void printVersion(void)
{
   printf("VERSION: 0.2\n");
}

void reverseString(char* str)
{
    char tmp;
    unsigned long i;
    unsigned long n = strlen(str);

    for(i = 0u; i < n / 2; i++)
    {
        tmp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = tmp;
    }
}
/* >>> */

int main(int argc, char * const argv[])
{
   
   signed long num_of_repititions = 0u;
   unsigned long i;
   unsigned long len;
   char string[MAX_STR_LEN] = {'\0'};
   char separator[MAX_SEP_LEN] = {'\0'};
   FILE* fd = stdin;
   bool version = false;
   bool help    = false;
   bool sep     = false;
   bool addlf   = true;
   int opt;

   while((opt = getopt(argc, argv, ":vhns:")) != -1) /* <<< */
   {
      switch(opt)
      {
         case 'v':
            {
               version = true;
               break;
            }
         case 'h':
            {
               help = true;
               break;
            }
         case 'n':
            {
               addlf = false;
               break;
            }
         case 's':
            {
               strncpy(separator, optarg, MAX_SEP_LEN-1); /* strncpy does not append \0 */
               sep = true;
               break;
            }
         case ':':
            {
               fprintf(stderr, "repeat error: option -s (separator) needs a string value\n");
               return 1;
               break;
            }
         case '?':
            {
               fprintf(stderr, "repeat error: unknown option => '%c'\n", optopt);
               return 2;
               break;
            }
      }
   } /* >>> */

   if(help)
   {
      printHelp();
      return 0;
   }

   if(version)
   {
      printVersion();
      return 0;
   }

   if(isatty(fileno(fd))) /* is connected to terminal, string not coming from pipe take second arg */
   {
      if((argc - optind) < 2)
      {
         fprintf(stderr, "repeat error: too few arguments\n");
         printUsage();
         return 3;
      }

      strncpy(string, argv[optind+1], MAX_STR_LEN-1); /* strncpy does not append \0 */
   }
   else /* program used in pipe take string from pipe */
   {
      if((argc - optind) < 1)
      {
         fprintf(stderr, "repeat error: too few arguments\n");
         printUsage();
         return 4;
      }

      fgets(string, MAX_STR_LEN, stdin); /* fgets appends \0 */
   }

   len = strlen(string);

   if((len > 0) && (string[len-1] == '\n'))
   {
      string[len-1] = '\0';
   }

   errno = 0;
   num_of_repititions = strtol(argv[optind], NULL, 10);
   if(errno != 0)
   {
      perror("repeat error: repitition value is not a number");
      return 5;
   }

   if(num_of_repititions < 0)
   {
      reverseString(string);
      num_of_repititions = labs(num_of_repititions);
   }

   for(i=0u; i < num_of_repititions ; i++)
   {
      printf("%s", string);
      if(sep && (i < (num_of_repititions-1)))
      {
         printf("%s", separator);
      }
   }

   if(addlf) /* add line feed to output */
   {
      printf("\n");
   }

   return 0;
}

/* vim: fmr=<<<,>>> fdm=marker
 */
