#include "bufferrx.h"
#include "derivative.h"

volatile char FLAG_RECEIVED=0;
char car;

void bufferrx_receive_interrupt(){
	car=SCID;
	FLAG_RECEIVED=1;
}

char bufferrx_get_char(void){
	return car;
}