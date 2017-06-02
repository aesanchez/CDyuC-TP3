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
		shell_execute(i);
		i = 0;
		return;
	}
	bufferrx_buff[i++] = SCID;
	if (i == LEN) {
		i = 0;
		buffertx_send_str("\r\nERROR\r\n > ");
	}
}
