/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name:  Margarita Selenko                      */
/*  Student number: 147393169                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

unsigned int factorial (unsigned int n)
{
	unsigned int i, fact = 1;

	for (i = 2;i <= n; i++)
	{
		fact *= i;
	}

	return fact;
}

double power (double base, unsigned int n)
{
	double result = 1;

	while (n != 0)
	{
		result *= base;
		--n;
	}

	return result;
}

unsigned int fibonacci (unsigned int n)
{
	unsigned int first = 0, second = 1, next = 0;

	for (int i = 0; i < n; i++) 
	{
		next = first;
		first = first + second;
		second = next;
	}

	return first;       
}
						 
