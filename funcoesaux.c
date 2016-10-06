#include <stdio.h>

#define TRUE 1
#define FALSE 0

void init_vec_0(int *vec, int size)
{	
	int i = 0;
	while (i < size)
	{
		vec[i] = 0;
		i++;
	}
}

void push_pid(int *vec, int size, int pid)
{
	int i = 0;
	while(i < size)
	{
		if (vec[i] == 0)
		{
			vec[i] = pid;
		}
		i++;
	}
}

int list_full(int *vec, int size)
{
	int i = 0;
	while(i < size)
	{
		if (vec[i] == 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}