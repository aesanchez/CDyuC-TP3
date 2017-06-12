#ifndef SOUND_H_
#define SOUND_H_

#define MIN 200
#define MAX 10000
#define STEP_FREQ 100

void sound_interrupt(void);
void sound_sweep_interrupt(void);
char sound_set_frequency(unsigned int);
void sound_on(void);
void sound_off(void);
void sound_reset(void);
void sound_sweep(char);

#endif
