#include "bufferrx.h"
#include "buffertx.h"
#include "derivative.h"
#include "shell.h"
#include "bufferrx.h"

char bufferrx_buff[LEN];
//el buffer se comparte con shell para poder leer los comandos
char i = 0;
// para asegurarnos que no se lean caracteres cuando estamos procesando
// un comando
char blocked=0;

void push_upper_to_lower_case(char);

void bufferrx_receive(void) {
	char aux;
	// en SCID esta el caracter a leer
	if(blocked==1) return;
	aux = SCID;
	if(aux!='\r') buffertx_send_char(aux);
	if (aux == '\r') {
		if (i > 0){
			blocked=1;
			shell_execute(i);
			blocked=0;
		}
		buffertx_send_str("\r\n > ");
		i = 0;
		return;
	}
	push_upper_to_lower_case(aux);
	if (i == LEN) {
		i = 0;
		buffertx_send_str("\r\nCOMANDO FUERA DE RANGO\r\n > ");
	}
}
void push_upper_to_lower_case(char c) {
	if (c >= 'A' && c <= 'Z') {
		//upper caso to lower case
		c = c + ('a' - 'A');		
	}
	bufferrx_buff[i++] = c;

}
