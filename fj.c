#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "fj.h"

int main(int argc, char** argv)
{
    int oc; //option character
    char* b_opt_arg;
	
    if(argc == 1)
    {
	system("ls --color=auto");
	return 0;
    }
    else if(argc == 2)
    {
	fj_editor(argv);
	return 0;
    }

    while( (oc = getopt(argc, argv, "alr:b:")) != -1)
    {
        switch(oc)
        {
	    case 'a' :
	        printf("option a has been recognized\n"); 
	        break;
	    case 'b' :
	        // handle -b, getr arg value from optarg
	        b_opt_arg = optarg;
	        printf("option argument passed was: %s\n", b_opt_arg);
		break;
	    case 'l' :
		system("ls -l --color=auto");
		break;
	    case 'r' :
		printf(" -r recognized\n");
		fj_remove(optarg);
		break;
	    case ':' :
		printf(": error\n");
	        //err handling
	    case '?' :
		printf("? error\n");
	    default :
		printf("default error\n");
	        //err handling
        }
    }

    return 0;
}

int fj_editor(char** argv)
{
    char* command;
    char* editor_string = "vi ";
    if( (command = malloc(strlen(editor_string) + strlen(argv[1]) + 1)) != NULL)
    {
        strcat(command, editor_string);
        strcat(command, argv[1]);
        system(command);
        return 0;
    }
    else
    {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
}
 
int fj_remove(char* optarg)
{
    char* b_opt_arg;
    b_opt_arg = optarg;

    struct stat s;
    int err = stat(b_opt_arg, &s);
    if(-1 == err)
    {
        printf("this dir D.N.E.\n");
    }
    else
    {
        char* rm_string = "rm -r";
        char* command;
        if( (command = malloc(strlen(rm_string) + strlen(b_opt_arg) + 1)) != NULL )
        {
            command[0] = '\0'; //insurance
            strcat(command, "rm -r ");
            strcat(command, b_opt_arg);
        }
        else
        {
            fprintf(stderr, "malloc failed!\n");
        }

        if(S_ISDIR(s.st_mode))
	{
            system(command);
	}
	else if(S_ISREG(s.st_mode))
	{
	    system(command);
	}
    }

    return 0;
}