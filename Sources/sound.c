#include "sound.h"

int nc;

void sound_init(void){
	// TODO(matipan): deshabilitar la interrupcion, chequear
	// cuall es la TPM para deshabilitarla
	TPM1C1V+=nc;
}

void sound_frequency(int freq){
}
