#ifndef SOUND_H_
#define SOUND_H_

#define MIN 200
#define MAX 10000
#define STEP_FREQ 100

// sound_interrupt se llama desde la interrupcion de el CH1 del
// TPM para setear la frecuencia correspondiente
void sound_interrupt(void);

// sound_sweep_interrupt se llama dentro de la interrupcion
// RTC, esta va realizando en pasos incrementales el barrido
// correspondiente.
void sound_sweep_interrupt(void);

// sound_set_frequency setea la frecuencia de sonido llamando
// a sound_set_nc, y calcula el error de dicha frecuencia.
// Recibe la frecuencia que se quiere setear y devuelve el error
// correspondiente.
char sound_set_frequency(unsigned int);

// sound_on prende el sonido mediante la habilitacion de la
// interrupcion. Este se llama desde `shell_on`
void sound_on(void);

// sound_off apaga el sonido mediante la deshabilitacion de la
// interrupcion. Este se llama desde `shell_off`
void sound_off(void);

// sound_reset deshabilita la interrupcion de barrido y apaga el sonido.
void sound_reset(void);

// sound_sweep realiza un barrido de cierta cantidad de tiempo
// en pasos de 100 Hz.
// Recibe el periodo del barrido, en el caso de la shell va a ser
// 5, 10 o 15. El parametro se toma como segundos
void sound_sweep(char);

#endif
