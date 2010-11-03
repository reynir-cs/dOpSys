#include <stdio.h>
#include <stdlib.h>

void get_args(int argc, char** argv, int* a_value, float* b_value)
{
    int i;

    /* Start at i == 1 to skip the command name. */
    for (i = 1; i < argc; i++) {

	/* Check for a switch (leading "-"). */
	if (argv[i][0] == '-') {

	    /* Use the next character to decide what to do. */
	    switch (argv[i][1]) {
		case 'a': *a_value = atoi(argv[++i]);
		case 'b': *b_value = atof(argv[++i]);
	    }
	}
    }
}

int main(int argc, char** argv)
{
    int *a;
    float b = 0.0;

    get_args(argc, argv, a, &b);
    printf("a = %d\n", *a);
    printf("b = %f\n", b);
    return 0;
}
