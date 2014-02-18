#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"
//#include "enc_mem.h"

#define USAGE_UPDATE 		"* >> update [target name]         *\n"
#define USAGE_DELETE 		"* >> delete [target name]         *\n"
#define USAGE_ISSUE_TOKEN 	"* >> issue_token [target name]    *\n"

void print_usage() {
	printf("************** usage **************\n");
	printf("* >> help                         *\n");
	//printf(USAGE_UPDATE);
	//printf(USAGE_DELETE);
	//printf(USAGE_ISSUE_TOKEN);
	printf("* >> ls [absolute dir path]       *\n");
	printf("* >> cat [absolute file path]     *\n");
	printf("* >> touch [absolute file path]   *\n");
	printf("* >> exit                         *\n");
	printf("***********************************\n");
	printf("\n");
}

unsigned char* _ptr = NULL;

int main(int argc, char *argv[])
{

	printf("pid= %d\n",getpid());
	printf("helloworld is running !!! \n");
	print_usage();
	int ret = -1;
	printf(">> ");
	char input[128];
	while(gets(input)){

		char* command[16];
		int num_command = parse_input(input, command, ' ');

		if(strcmp(command[0],"help")==0) {
			print_usage();
		}

		else if(strcmp(command[0],"cp")==0) {
			my_copy(command[1], command[2]);
		}

		else if(strcmp(command[0],"ls")==0) {
			if(num_command>=2) {
				my_ls_all(command[1]);
			}
			else  printf("less args\n");
		}

		else if(strcmp(command[0],"touch")==0) {
			if(num_command>=2) {
				printf("%s\n",command[1]);
				my_touch(command[1]);
			}
			else  printf("less args\n");
		}
		else if(strcmp(command[0],"cat")==0) {
			if(num_command>=2) {
				my_cat(command[1]);
			}
			else  printf("less args\n");
		}
		else if(strcmp(command[0],"exec")==0) {
			if(num_command<2) printf("less args\n");
			command[num_command]=0;
			printf("before vfork pid = %d\n",getpid());
			pid_t child_pid = vfork();
			if(child_pid==0) {
				printf("child pid = %d\n", getpid());
				execv(command[1], command+1);
				exit(0);
			}
			else {
				waitpid(child_pid, NULL, 0);
				printf("after fork pid = %d\n",getpid());
			}
		}

		else if(strcmp(command[0],"exit")==0) {
			break;
		}

__func_end: 
		printf(">> ");
	}

	return 0;
}

