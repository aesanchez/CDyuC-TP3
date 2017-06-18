#include "bufferrx.h"
#include "derivative.h"

volatile char FLAG_RECEIVED=0;
char car;

// bufferrx_receive_interrupt es llamado desde la interrupcion
// de recepcion, un llamado a esta funcion indica que se ingreso
// un caracter. Dicho caracter va a estar disponible en el SCID,
// el cual se almacena en la variable car. Luego mediante el
// FLAG_RECEIVED se le avisa a los que escuchan que se recibio un caracter
void bufferrx_receive_interrupt(){
	car=SCID;
	FLAG_RECEIVED=1;
}

// bufferrx_get_char devuelve el ultimo caracter leido
char bufferrx_get_char(void){
	return car;
}
