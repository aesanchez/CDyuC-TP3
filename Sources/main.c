#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#include "play.h"

void MCU_init(void); /* Device initialization function declaration */


void main(void) {
  MCU_init();	/* call Device Initialization */

  PTCDS=0xFF;

  for(;;) {
	  
	  reproductor ();    
	  
  } /* loop forever */
  /* please make sure that you never leave main */
}
