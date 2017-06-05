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

void push_filtered(char);

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
		buffertx_send_str("\n > ");
		i = 0;
		return;
	}
	push_filtered(aux);
	if (i == LEN) {
		i = 0;
		buffertx_send_str("\r\nCOMMAND OUT OF BOUND\r\n > ");
	}
}
void push_filtered(char c) {
	if (c >= '0' && c <= '9') {
		//es un digito >> no hacer nada
		bufferrx_buff[i++] = c;
		return;
	}
	if (c >= 'A' && c <= 'Z') {
		//upper caso to lower case
		bufferrx_buff[i++] = c + ('a' - 'A');
		return;
	}
	if (c >= 'a' && c <= 'z') {
		//lower case >> no hacer nada
		bufferrx_buff[i++] = c;
		return;
	}
	if(c==' ')
		bufferrx_buff[i++] = c;
	//en este punto ya no son caracteres validos
	//por lo que no se lo pushea en el buffer
}
