#include <unistd.h>
#include <stdio.h>

int main(int a ,char** b){

	uid_t id;

	id = getuid();
	printf("I'm running on behalf of user %d\n",(int)id);
	printf(".. who would you like to become? ");
	scanf("%d",&id);
	/*per utilizzare la setuid() devo essere un utente root o super user*/
	setuid(id);
	id = getuid();
	printf("I'm now running on behalf of user %d\n",(int)id);
	pause();

}
