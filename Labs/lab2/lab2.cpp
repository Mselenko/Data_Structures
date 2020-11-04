/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: Margarita Selenko                       */
/*  Student number: 147393169                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/


unsigned int factorial (unsigned int n)
{
	unsigned int rc = 1;

	if (n > 1)
	{
		rc = n * factorial(n - 1);
	}
	return rc;
}

double power (double base, unsigned int n)
{
	double rc = 1.0;

	if (n != 0)
	{
		rc = base * power(base, n - 1);
	}
	else
	{
		rc = 1;
	}

	return rc;
}

unsigned int fibonacci (unsigned int n)
{
	unsigned int rc = 1;

	if (n <= 1)
	{
		rc = n;

	}else
	{
		rc = fibonacci(n - 1) + fibonacci(n - 2);
	}
	return rc;
}
