/***************************************** 

* File Name : getopt.c

* Creation Date : 02-10-2018

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

* License :

******************************************/

/**
 *  Purpose:
 *
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int clean(FILE *fp, int xchar) {
    int c, np;

    np = 0;
    while ((c = getc(fp)) != EOF) {
        if (isprint(c) 
            || (c == '\n') 
            || (c == '\t')
            || (c == xchar)) {
            putchar(c);
        } else {
            np++;
        }
    }

    return np;
}

void
main(int argc, char *argv[])
{
     int opt,clean_ret, i, err, verbose, xchar;
     FILE *fp;
     char *fname;

     opterr = err = verbose = 0;
     xchar = EOF;

     /*
      * Process command-line options.
      */
     while ((opt = getopt(argc, argv, "vx:")) != -1) {
         switch(opt) {
         case 'v':
             /*
              * Use verbose mode.
              */
             verbose++;
             printf("Using verbose %d.\n", verbose);
             break;

         case 'x':
             /*
              * Don't strip the specified character.
              * Only one exception is allowed.
              */
             if (xchar != EOF) {
                 fprintf(stderr, "%c.\n", xchar);
                 err++;
                 break;
             }
             //char a = optarg[0];
             //xchar = atoi(&a);
             xchar = atoi(optarg);
             printf("X character is: ");
             printf("%s to %d.\n", optarg, xchar);
             if ((xchar > 255) || (xchar < 0)) {
               fprintf(stderr, "-x value out of range\n");
               exit(1);
             }
             printf("Cleawning character %d.\n", xchar);
             break;

         default:
             /*
              * All other options constitute an error.
              */
             fprintf(stderr, "This option is not implemented.\n");
             err++;

         }
     }
     if (err) {
         fprintf(stderr,
           "usage: clean [-v] [-x char] [files]\n");
         exit(1);
     }

     /*
      * If no files were specified on the command line,
      * use stdin.
      */
     if (optind == argc) {
         printf("No files give, using stdin.\n");
         opt = clean(stdin, xchar);
         if (verbose) fprintf(stdout, "stdin: %d chars cleaned\n", opt);
         exit(0);
     }

     /*
      * Strip each file given on the command line.
      */
     for (i = optind; i < argc; i++) {
         /*
          * "-" is a special alias for stdin.
          */
         if ((argv[i][0] == '-') && (argv[i][1] == '\0')) {
             fp = stdin;
             fname = "stdin";
         } else {
             fname = argv[i];
             fp = fopen(fname, "r");
             if (fp == NULL) {
               fprintf(stderr, "Cannot open %s: %s\n",
                 fname, strerror(errno));
               err++;
               continue;
             }
         }
         clean_ret = clean(fp, xchar);
         if (verbose)
           fprintf(stdout, "%s: %d chars cleaned\n",
             fname, clean_ret);

         /*
          * Don't close stdin -- we might need it again.
          */
         if (fp != stdin)
             fclose(fp);
     }
     exit(err);
}
