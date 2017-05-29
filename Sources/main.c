#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

void SCI_send_string(char * cadena) {
	while (*cadena != '\0') {
		while(SCIS1_TDRE==0);//si el transmisor esta ocupado no puedo escribir
		//==1 el transmisor esta listo para transmitir
		SCID=*cadena;
		cadena++;
	}
}

volatile char rxchar = 0;
void main(void) {
	MCU_init(); /* call Device Initialization */

	SCI_send_string("\r\nBIENVENIDOS AL PROGRAMA ECHO: >");
	//el registro scid actua como buffer para el receptor y el transmisor.
	//creo que del punto de vista del programador es un solo registro pero en HW no


	for (;;) {
		while(SCIS1_RDRF==0);
		rxchar=SCID;
		if(rxchar!=0) {
			SCI_send_string("\r\nUD. PRESIONO: ");
			while(SCIS1_TDRE==0);
			SCID=rxchar;
			rxchar=0;
		}
	}

}

