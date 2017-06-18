#include "sound.h"
#include "derivative.h"

#define STEPS ((MAX-MIN)/STEP_FREQ) // cantidad de pasos para el barrido

unsigned int nc = (unsigned int) (4000000 / MIN); // por default
unsigned int sweep_freq;

// sound_set_nc setea la frecuencia deseada
void sound_set_nc(unsigned int freq){
	// Fclk=8MHz
	// Ciclo de trabajo 50%
	// f=frequencia deseada
	// nc= Fclk/(f*2)
	nc = (unsigned int) (4000000 / freq);
}

// sound_on prende el sonido mediante la habilitacion de la
// interrupcion. Este se llama desde `shell_on`
void sound_on(void) {
	// habilitar la interrupcion
	TPM1C1SC = 0x14U;
	TPM1C1SC_CH1IE = 1;
}

// sound_off apaga el sonido mediante la deshabilitacion de la
// interrupcion. Este se llama desde `shell_off`
void sound_off(void) {
	//deshabilitar la interrupcion para que no suene
	TPM1C1SC = 0x00U;
}

// sound_interrupt se llama desde la interrupcion de el CH1 del
// TPM para setear la frecuencia correspondiente
void sound_interrupt(void) {
	TPM1C1V += nc;
	TPM1C1SC_CH1F = 0;
}

// sound_set_frequency setea la frecuencia de sonido llamando
// a sound_set_nc, y calcula el error de dicha frecuencia.
// Recibe la frecuencia que se quiere setear y devuelve el error
// correspondiente.
char sound_set_frequency(unsigned int freq) {
	RTCSC_RTIE = 0;//deshabilitar sweep
	sound_set_nc(freq);
	// devolver error, esto se calcula de la siguiente manera:
	// f deseada - f obtenida
	// f obtenida = Fclk/((nc)*2)
	return (4000000 / nc) - freq;
}

// sound_sweep realiza un barrido de cierta cantidad de tiempo
// en pasos de 100 Hz.
// Recibe el periodo del barrido, en el caso de la shell va a ser
// 5, 10 o 15. El parametro se toma como segundos
void sound_sweep(char period) {
	unsigned int step_period;
	sweep_freq = MIN;
	sound_set_nc(sweep_freq);
	step_period = (period * 1000) / STEPS;
	RTCMOD = step_period - 1;
	RTCSC_RTIE = 1;// habilitar interrupcion
}

// sound_sweep_interrupt se llama dentro de la interrupcion
// RTC, esta va realizando en pasos incrementales el barrido
// correspondiente.
void sound_sweep_interrupt(void) {
	sweep_freq += STEP_FREQ;
	if (sweep_freq > MAX)
		sweep_freq = MIN;
	sound_set_nc(sweep_freq);
	RTCSC_RTIF = 1;// interrupcion atendida
}

// sound_reset deshabilita la interrupcion de barrido y apaga el sonido.
void sound_reset(void) {
	// por default se setea la minima
	sound_set_nc(MIN);
	// apagamos el sonido
	sound_off();
	RTCSC_RTIE = 0;// deshabilitar interrupcion sweep

}
