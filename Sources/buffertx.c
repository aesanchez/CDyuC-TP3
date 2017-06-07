#include "derivative.h"
#define LEN 32
char buffertx_buff[LEN];
unsigned char w, r;
volatile char empty=1;

void buffertx_send_str(char * str) {
	while(empty==0);
	while (*str != '\0') {
		buffertx_send_char(*str);
		str++;		
	}
}
void buffertx_send_char(char c) {
	buffertx_buff[(w++) % LEN] = c;
	empty=0;
	SCIC2_TIE = 1;
}
void buffertx_transmit() {
	SCID = buffertx_buff[(r++) % LEN];
	if(r == w){
		empty=1;
		SCIC2_TIE=0;
	}	
}

