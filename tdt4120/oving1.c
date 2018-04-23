

#include <stdio.h>

#define MAX_LINE_LENGTH 10

typedef struct Record_t {
	int 				value;
	struct Record_t* 	next;
} Record;

int ipow(int base, int expo)
{
    int result = 1;
    while (expo)
    {
        if (expo & 1)
            result *= base;
        expo >>= 1;
        base *= base;
    }

    return result;
}


int main(){

	Record* head;


	char raw_line[MAX_LINE_LENGTH] = {0};
	char raw_in = NULL;
	size_t current_line_length = 0;
	while (EOF != (raw_in = getchar())) {
		if (raw_in == '\n'){
			// turn raw_line into an entry in Record
			
			int result = 0;
			for (int i=0; i < current_line_length; ++i){
				result += raw_line[i]*ipow(10, current_line_length - i);
			}
			


			current_line_length = 0;
			memset(raw_line, 0, MAX_LINE_LENGTH);




		} else{
			raw_line[current_line_length] = raw_in;
			++current_line_length;
		}



	}


	printf("Hey world\n");

	return 0;
}