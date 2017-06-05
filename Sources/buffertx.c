#include "derivative.h"
#define LEN 32
char buffertx_buff[LEN];
unsigned char w, r;
char empty=1;
void buffertx_send_str(char * str) {
	while(empty==0);
	while (*str != '\0') {
		buffertx_buff[(w++)%LEN]=*str;
		str++;
		SCIC2_TIE=1;
	}
}
void buffertx_send_char(char c) {
	buffertx_buff[(w++) % LEN] = c;
	SCIC2_TIE = 1;
}
void buffertx_transmit() {
	SCID = buffertx_buff[(r++) % LEN];
}

char buffertx_ready(void) {
	if (SCIS1_TDRE == 0)
		return 0;
	//TODO peor de los casos que se vaya de la representacion
	if (r == w) {//buffer empty
		empty=1;
		SCIC2_TIE = 0;
		return 0;
	} else {
		return 1;
	}
}

