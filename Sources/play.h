/*
 * play.h
 *
 *  Created on: 20/05/2015
 *      Author: Jose
 */

#ifndef PLAY_H_
#define PLAY_H_


void sound(unsigned int freq, unsigned int dur);
void play_song(char *song);
void reproductor (void);
void Tpm1CH0_Handler(void);
void Tpm1CH1_Handler(void);

#endif /* PLAY_H_ */
