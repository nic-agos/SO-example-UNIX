#include<stdio.h>

int x;
double *y;

void main(void){
	y = &x;
 	printf("x adress is %p - y is %p | x address+1 is %p - y+1 is %p\n",&x,y,&x+1,y+1); /* y è già una variabile pointer quindi non serve & */
}
