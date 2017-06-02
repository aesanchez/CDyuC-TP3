#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "buffertx.h"

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

void main(void) {
	MCU_init(); /* call Device Initialization */

	buffertx_send_str("\r\nBIENVENIDOS\r\n > ");

	for (;;) {
	}

}

