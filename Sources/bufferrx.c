#include "bufferrx.h"
#include "buffertx.h"
#include "derivative.h"

void bufferrx_send_command(void);

#define LEN 8
char bufferrx_buff[LEN];
char i=0;
void bufferrx_receive(void) {
	// en SCID esta el caracter a leer
	if(SCID=='\r') {
		bufferrx_send_command();
		i=0;
		return;
	}
	
	bufferrx_buff[i++]=SCID;
	if(i==LEN){
		i=0;
		buffertx_send_str("\r\nERROR");
	}
}

char j;
void bufferrx_send_command(){
	for(j=0;j<i;j++)
		buffertx_send_char(bufferrx_buff[j]);
}
