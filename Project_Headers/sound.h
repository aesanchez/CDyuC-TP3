#ifndef SOUND_H_
#define SOUND_H_

#define MIN 200
#define MAX 10000
#define STEP 100//solo se usa para los barridos

void sound_handle_interrupt(void);
char sound_set_frequency(unsigned int);
void sound_on(void);
void sound_off(void);
void sound_reset(void);

#endif
