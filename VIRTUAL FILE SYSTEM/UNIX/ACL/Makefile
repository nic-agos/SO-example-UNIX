/*è un makefile con comandi gestione delle ACL*/

/*viene restituito l'ACL legato al file pippo*/
getACL:
	getfacl pippo 
/*-m inserisce una nuova entry nella tabella ACL del file*/
setACL:
	setfacl -m u:8765:r pippo 
	setfacl -m g:8765:r pippo 

maskACL:
	chmod 000 pippo 

resetACL:
	setfacl -b pippo 
