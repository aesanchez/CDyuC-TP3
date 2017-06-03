#include "bufferrx.h"
#include "buffertx.h"
#include "derivative.h"
#include "shell.h"
#include "bufferrx.h"

char bufferrx_buff[LEN];
//el buffer se comparte con shell para poder leer los comandos
char i = 0;
//TODO blocked state
void bufferrx_receive(void) {
	// en SCID esta el caracter a leer
	buffertx_send_char(SCID);
	if (SCID == '\r') {
		buffertx_send_str("\n > ");
		if (i > 0)
			shell_execute(i);
		i = 0;
		return;
	}
	push_filtered(SCID);
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
	//en este punto ya no son caracteres validos
	//por lo que no se lo pushea en el buffer
}
