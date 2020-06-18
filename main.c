#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buff[500];
char head_vol[] = "volume:";

int main()
{
	int len;
	char *p;
	double vol;
	int buff_len, head_len;

	memset(buff, 0, sizeof(buff));

	fprintf(stdout, "Start \n");
	
	while(NULL != fgets(buff, sizeof(buff), stdin)) {
		p = buff;
		buff_len = strlen(buff);
		head_len = strlen(head_vol);
		if (buff_len > head_len && 0 == strncmp(head_vol, buff, head_len)) {
			p += head_len;
			vol = atof(p);
			fprintf(stdout, "%.3f\n", vol);
		} else {
			fprintf(stdout, "Invalid %s \n", buff);
		}

		fflush(stdout);
	}

	fprintf(stdout, "End \n");
	
	return 0;
}
