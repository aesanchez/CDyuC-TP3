#ifndef SHELL_H_
#define SHELL_H_

// shell_execute actua como dispatcher para los comandos. Esta consume el buffer
// que contiene los caracteres ingresados(sin incluir el enter), y ejecuta el
// comando correspondiente. Las funciones de los comandos estan almacenadas en un
// arreglo previamente definido.
void shell_execute(void);

// shell_reset muestra la lista de comandos y resetea todos las configuraciones
// Esto hace que no se escuche ningun sonido
// 	> reset
void shell_reset(void);

// shell_update chequea mediante el FLAG_RECEIVED si hay un caracter disponible
// en caso de que haya y el caracter sea "\r"(enter) entonces procede a ejecutar
// el comando. En caso de que no sea enter, guarda el caracter en el buffertx. Ademas
// chequea que la cantidad de caracteres que se ingreso previo a enter no supere el
// rango maximo.
void shell_update(void);

#endif
