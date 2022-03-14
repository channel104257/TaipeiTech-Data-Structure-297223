#include <stdio.h>

int ackerman(int m, int n);

int main()
{
	// input variable m & n
	int m, n; 

	// read input from stdin
	scanf_s("%d %d", &m, &n); 

	// output the final answer
	printf("%d", ackerman(m, n)); 
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
