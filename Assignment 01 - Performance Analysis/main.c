#include <stdio.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC 
#include "unistd.h" // for sleep()

int ackerman(int m, int n);

int main()
{
	// to store the execution time of code 
	double time_spent = 0.0;
	clock_t t_begin = clock();

	// input variable m & n
	int m, n; 

	// read input from stdin
	scanf_s("%d %d", &m, &n); 

	// output the final answer
	printf("%d\n", ackerman(m, n)); 

	clock_t t_end = clock();
	printf("\n");

	// calculate elapsed time by finding difference (end - begin) and  
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds  
	time_spent += (double)(t_end - t_begin) / CLOCKS_PER_SEC; 

	printf("The elapsed time is %f seconds", time_spent);
}

int ackerman(int m, int n)
{
	if (m == 0)
	{
		// if m = 0, A(m, n) = n + 1
		return n + 1;
	}
	else if (n == 0)
	{
		// if n = 0, A(m, n) = A(m - 1, 1)
		return ackerman(m - 1, 1);
	}
	else
	{
		// if (m != 0 && n != 0), A(m ,n) = A(m - 1, A(m, n - 1))
		return ackerman(m - 1, ackerman(m, n - 1));
	}
}
