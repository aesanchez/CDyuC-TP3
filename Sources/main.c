#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "buffertx.h"

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

volatile char rxchar = 0;
void main(void) {
	MCU_init(); /* call Device Initialization */

	buffertx_send_str("\r\nBIENVENIDOS AL PROGRAMA ECHO: >");

	for (;;) {
		if(rxchar!=0) {
			buffertx_send_str("\r\nUD. PRESIONO: ");
			buffertx_send_char(rxchar);
			rxchar=0;
		}
	}

}

