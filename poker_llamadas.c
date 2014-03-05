/* poker de formas de llamar al sistema desde C 
   comprobar con strace las llamadas que se realizan */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


main()
{
char * mensaje="Salida write con int 80h desde asm\n";  /* tamaño 35 caracteres */

/*Pinta por pantalla usando la librería de C stdio.h*/
printf("Salida printf() desde C\n");

/* para hacer flush:  fflush(stdout); */

/* pinta por pantalla usando el envoltorio de la llamada al sistema en unistd.h */
write(STDOUT_FILENO, "Salida write() desde C\n", 23);   /* STDOUT_FILENO = 1 */

/* ahora pinta usando la funcion de C en unistd.h que llama al sistema de forma genérica*/
#define __NR_write  4   /* la llamada al sistema write es la 4 */
syscall(__NR_write, STDOUT_FILENO, "Salida syscall() desde C\n", 25);

/* por ultimo usa ensamblador para hacer la llamada al sistema con la interrupción 80 hex */
asm("mov $4,%%eax; mov $1,%%ebx; mov %0,%%ecx; mov $35,%%edx; int $0x80;" 
 	: /* sin salida */
	: "r" (mensaje)  /* entrada mensaje en %0 para lectura */
	: "%eax", "%ebx", "%ecx", "%edx"   /* registros usados para que el compilador lo sepa */
    );

exit(0);

}
