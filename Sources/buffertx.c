#include "derivative.h"
void buffertx_send_str(char * str) {
	while (*str != '\0') {
		while(SCIS1_TDRE==0);//si el transmisor esta ocupado no puedo escribir
		//==1 el transmisor esta listo para transmitir
		SCID=*str;
		str++;
	}
}
void buffertx_send_char(char c) {
	while (SCIS1_TDRE == 0);//si el transmisor esta ocupado no puedo escribir
	//==1 el transmisor esta listo para transmitir
	SCID = c;
}

