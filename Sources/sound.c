#include "sound.h"
#include "derivative.h"

#define STEP_FREQ 100 //solo se usa para los barridos
#define STEPS ((MAX-MIN)/STEP_FREQ) //cantidad de pasos para el barrido

unsigned int nc = (unsigned int) (4000000 / MIN);//by default
unsigned int sweep_freq;

void sound_set_nc(unsigned int freq){
	//Fclk=8MHz
	//Ciclo de trabajo 50%
	//f=frequencia deseada
	//nc= Fclk/(f*2)
	nc = (unsigned int) (4000000 / freq);
}

void sound_on(void) {
	//habilitar la interrupcion
	//TODO: no hace falta hacer doble asignacion, habria que
	// 	chequear cual es el valor para el TPM1C1SC con el
	// 	CH1IE seteado en 1
	TPM1C1SC = 0x14U;
	TPM1C1SC_CH1IE = 1;
}

void sound_off(void) {
	//deshabilitar la interrupcion para que no suene
	TPM1C1SC = 0x00U;
}

void sound_interrupt(void) {
	TPM1C1V += nc;
	TPM1C1SC_CH1F = 0;
}

//devuelve el error de representacion
char sound_set_frequency(unsigned int freq) {
	RTCSC_RTIE = 0;//deshabilitar sweep
	sound_set_nc(freq);
	//devolver error
	//f deseada - f obtenida
	//fobtenida=Fclk/((nc)*2)
	return (4000000 / nc) - freq;
}

//periodo en segundos
void sound_sweep(char period) {
	unsigned int step_period;
	sweep_freq = MIN;
	sound_set_nc(sweep_freq);
	step_period = (period * 1000) / STEPS;
	RTCMOD = step_period - 1;
	RTCSC_RTIE = 1;//habilitar interrupcion
}

void sound_sweep_interrupt(void) {
	sweep_freq += STEP_FREQ;
	if (sweep_freq > MAX)
		sweep_freq = MIN;
	sound_set_nc(sweep_freq);
	RTCSC_RTIF = 1;//interrupcion atendida
}

void sound_reset(void) {
	//by default
	sound_set_nc(MIN);
	sound_off();
	RTCSC_RTIE = 0;//deshabilitar interrupcion sweep

}
