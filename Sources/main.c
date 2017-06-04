#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "shell.h"
#include "bufferrx.h"

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

extern volatile char FLAG_RECIEVED;

void main(void) {
	MCU_init();
	TPM1C1SC = 0x00U;
	shell_show_commands();
	
	for (;;) {
		if(FLAG_RECIEVED)
			bufferrx_recieve_handler();
	}

}

