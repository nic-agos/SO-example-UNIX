#include <stdio.h>
#include <stdlib.h>

#ifdef FLUSH                                      /* se FLUSH non è definito in compilaazione non avviene la ridefinizione */
#define fflush(stdin) while(getchar() != '\n')
#endif


int main(int a, char **b)
{

	int x;
	
	printf("%d\n",scanf("%d",&x));
	fflush(stdin);
	printf("%d\n",scanf("%d",&x));
	exit(0);

}
