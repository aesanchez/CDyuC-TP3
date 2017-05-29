#include "derivative.h"
#define LEN 32
char buffer[LEN];
char w, r;
void buffertx_send_str(char * str) {
	while (*str != '\0') {
		buffer[(w++)%LEN]=*str;
		str++;
		SCIC2_TIE=1;
	}
}
void buffertx_send_char(char c) {
	buffer[(w++) % LEN] = c;
	SCIC2_TIE = 1;
}
void buffertx_transmit() {
	SCID = buffer[(r++) % LEN];
}

char buffertx_ready(void) {
	if (SCIS1_TDRE == 0)
		return 0;
	//TODO peor de los casos que se vaya de la representacion
	if (r == w) {//buffer empty
		SCIC2_TIE = 0;
		return 0;
	} else {
		return 1;
	}

}

