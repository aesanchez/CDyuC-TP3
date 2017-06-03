#include "sound.h"
#include "derivative.h"

//by default frequency=200
unsigned int nc=(unsigned int)(4000000/MIN);

void sound_on(void) {	
	//habilitar la interrupcion
	TPM1C1SC_CH1IE = 1;
}
void sound_off(void) {
	//deshabilitar la interrupcion para que no suene
	TPM1C1SC_CH1IE = 0;

}
void sound_handle_interrupt(void) {
	TPM1C1V += nc;
	TPM1C1SC_CH1F = 0;
}

//devuelve el error de representacion
char sound_set_frequency(unsigned int freq) {
	//Fclk=8MHz
	//Ciclo de trabajo 50%
	//f=frequencia deseada
	//nc= Fclk/(f*2)
	nc = (unsigned int) (4000000 / freq);
	//devolver error
	//f deseada - f obtenida
	//fobtenida=Fclk/((nc)*2)
	return (4000000 / nc) - freq;
}
void sound_seep(void) {
	//TODO
}
void sound_reset(void){
	//by default
	sound_set_frequency(MIN);
	TPM1C1SC_CH1IE = 0;
}
