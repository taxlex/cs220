#include <stdio.h>

int main()
{
	int x;
	char str;
	x = 10;
	/* Count down to zero for liftoff */
	printf("Blasting off in... ");
	while(x >= 0){
		printf("%d,",x);
		x--;
	}
	printf(" ... Blast Off!\n");

	printf("New value of x is %d\n", x);

	/* Make sure the x value is what we expect */
	if(x == -1) {
		/* If x lies between 5 and 10, print so. */
		if( 5 < x && x < 10)
			printf("x is between 5 and 10\n");
		else
			printf("x is NOT between 5 and 10\n");

		/* Set x and str to 0, test them using the ternary operator, and print their equality. */
		x = str = 0;
		printf("x and str %s\n", ( x != str) ? "differ" : "are equal");

		printf("All Done!!\n");
	}
	return 0;
}



