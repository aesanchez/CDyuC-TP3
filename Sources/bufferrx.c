#include "bufferrx.h"
#include "buffertx.h"
#include "derivative.h"

void bufferrx_send_command(void);

#define LEN 16
char bufferrx_buff[LEN];
char i=0;

void bufferrx_receive(void) {
	// en SCID esta el caracter a leer
	buffertx_send_char(SCID);
	if(SCID=='\r') {
		buffertx_send_str("\n > ");
		i=0;
		return;
	}
	
	bufferrx_buff[i++]=SCID;
	if(i==LEN){
		i=0;
		buffertx_send_str("\r\nERROR\r\n > ");
	}
}

void bufferrx_send_command(){
}
