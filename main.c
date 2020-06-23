#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

#define HEAD "volume:"
char buff[500];
char head_vol[] = HEAD;

double vol;
double vol_pre;
long cnt = 0;

static int read_buff()
{
	int len;
	char *p;
	int buff_len, head_len;

	memset(buff, 0, sizeof(buff));

	//fprintf(stdout, "Start \n");

	if (NULL != fgets(buff, sizeof(buff), stdin)) {
		p = buff;

		while(*p == ' ')
			p++;

		buff_len = strlen(p);
		head_len = strlen(head_vol);
		if (buff_len > head_len && 0 == strncmp(head_vol, p, head_len)) {
			p += head_len;
			vol = atof(p);
			cnt++;
			//fprintf(stdout, HEAD "%.3f\n", vol);
		} else {
			//fprintf(stdout, "Invalid %s \n", buff);
		}

		//fflush(stdout);
	}

	//fprintf(stdout, "End \n");
	
	return 0;
}


int main()
{
	fd_set fds;
	struct timeval timeout;
	int selectRetVal;

	while(1) {	
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		selectRetVal = select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout);
		if (selectRetVal == -1) {
			printf("select failed\n");
		} else if (FD_ISSET(STDIN_FILENO, &fds)) { 
			read_buff();
		} else {
			if (cnt < 4) {
				if (vol != vol_pre) {
					vol_pre = vol;
					fprintf(stdout, HEAD " %.3f\n", vol);
					fflush(stdout);
				}
			}

			cnt = 0;	
		}
	}	
}
