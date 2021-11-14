
# the security problem related to this example can be also tackled by using 
# the"-fstack-protector-all" gcc option for compiling exploit.c as in the 
# 'stack-protect' target of this makefile

all:
	gcc exploit.c -fomit-frame-pointer #compila con l'omissione dell'uso dello stack
	gcc print-string.c -o print-string

position-independent:
	gcc exploit.c -fomit-frame-pointer -pie -fPIE  #genera codice indipendente dalla posizione
	gcc print-string.c -o print-string

stack-protect:
	gcc exploit.c -fomit-frame-pointer -fstack-protector-all #Inserts a guard variable onto the stack frame for for all functions.
	gcc print-string.c -o print-string
