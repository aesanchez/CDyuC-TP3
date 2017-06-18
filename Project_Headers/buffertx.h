#ifndef BUFFERTX_H_
#define BUFFERTX_H_

// buffertx_send_str recibe un string y lo envia caracter por
// caracter a la pantalla para que sea impreso.
// Recibe str, el cula debe tener el indicador de fin de string
void buffertx_send_str(char *);

// buffertx_send_char recibe un caracter, lo coloca en el buffer
// de impresion y avisa al SCI que hay un caracter que debe ser impreso
void buffertx_send_char(char);

// buffertx_transmit es llamado desde la interrupcion de transmision
// su fin es enviar a la pantalla un caracter
void buffertx_transmit(void);

#endif
