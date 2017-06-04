#include "bufferrx.h"
#include "buffertx.h"
#include "derivative.h"
#include "shell.h"
#include "bufferrx.h"

volatile char FLAG_RECIEVED=0;

char bufferrx_buff[LEN];
//el buffer se comparte con shell para poder leer los comandos
char i = 0;
// para asegurarnos que no se lean caracteres cuando estamos procesando
// un comando
char blocked=0;

char car;

void push_upper_to_lower_case(char);

void bufferrx_receive_interrupt(){
	car=SCID;
	FLAG_RECIEVED=1;
}

void bufferrx_receive_handler(void) {
	if(car!='\r') buffertx_send_char(car);
	if (car == '\r') {
		if (i > 0){
			shell_execute(i);
		}
		buffertx_send_str("\r\n > ");
		i = 0;
		FLAG_RECIEVED=0;
		return;
	}
	push_upper_to_lower_case(car);
	if (i == LEN) {
		i = 0;
		buffertx_send_str("\r\nCOMANDO FUERA DE RANGO\r\n > ");
	}
	FLAG_RECIEVED=0;
}
void push_upper_to_lower_case(char c) {
	if (c >= 'A' && c <= 'Z') {
		//upper caso to lower case
		c = c + ('a' - 'A');		
	}
	bufferrx_buff[i++] = c;
}
