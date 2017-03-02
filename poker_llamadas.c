/* poker de formas de llamar al sistema desde C 
   comprobar con strace las llamadas que se realizan */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

main()
{
int res;
char * mensaje="Salida write con int 80h desde asm\n";  /* tamaño 35 caracteres */

/*Pinta por pantalla usando la librería de C stdio.h*/
printf("Salida printf() desde C\n");

/* para hacer flush:  fflush(stdout); */

/* pinta por pantalla usando el envoltorio de la llamada al sistema en unistd.h */
write(STDOUT_FILENO, "Salida write() desde C\n", 23);   /* STDOUT_FILENO = 1 */

/* ahora pinta usando la funcion de C en unistd.h que llama al sistema de forma genérica*/
res=syscall(SYS_write, STDOUT_FILENO, "Salida syscall() desde C\n", 25);  // SYS_write = 1

#ifdef __i386__
printf("Compilando para Intel..\n");
// por ultimo usa ensamblador para hacer la llamada al sistema con la interrupción 80 hex 
asm("mov $4,  %%eax \n\t"
    "mov $1,  %%ebx \n\t" 
    "mov %k0,  %%ecx \n\t" 
    "mov $35, %%edx \n\t"
    "int $0x80 \n\t" 
 	: // sin salida
	: "r" (mensaje)  // entrada mensaje en %0 para lectura 
	: "%eax", "%ebx", "%ecx", "%edx"   // registros usados para que el compilador lo sepa 
    );
#endif

#ifdef __arm__
printf("Compilando para ARM..\n");

#endif

exit(0);

}
