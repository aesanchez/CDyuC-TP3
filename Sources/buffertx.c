#include "derivative.h"
#include "buffertx.h"
#define LEN 32

// buffertx_buff contiene los caracteres que se van transmitiendo
// este es un buffer circular
char buffertx_buff[LEN];

// w indica la posicion en la que se escribio el ultimo caracter
// en el buffer
// w nunca se resetea, se usan modulos de la longitud del buffer
// para no irse de rango
unsigned char w;

// r indica la posicion en la que se debe leer un caracter, esta es
// actualizada desde el buffertx_transmit, es decir, desde la interrupcion
// de transmision
// r nunca se resetea, se usan modulos de la longitud del buffer
// para no irse de rango
unsigned char r;

// indica que ya se leyo todo lo que habia para leer
volatile char empty=1;

// buffertx_send_str recibe un string y lo envia caracter por
// caracter a la pantalla para que sea impreso.
// Recibe str, el cula debe tener el indicador de fin de string
void buffertx_send_str(char * str) {
	while(empty==0);
	while (*str != '\0') {
		buffertx_send_char(*str);
		str++;
	}
}

// buffertx_send_char recibe un caracter, lo coloca en el buffer
// de impresion y avisa al SCI que hay un caracter que debe ser impreso
void buffertx_send_char(char c) {
	buffertx_buff[(w++) % LEN] = c;
	empty=0;
	SCIC2_TIE = 1;
}

// buffertx_transmit es llamado desde la interrupcion de transmision
// su fin es enviar a la pantalla un caracter
void buffertx_transmit() {
	SCID = buffertx_buff[(r++) % LEN];
	if(r == w){
		empty=1;
		SCIC2_TIE=0;
	}
}

