#include "shell.h"
#include "bufferrx.h"
#include "sound.h"
#include "buffertx.h"

void shell_A(void);
void shell_B(void);
void shell_C(void);
void shell_on(void);
void shell_off(void);
void shell_reset(void);
void shell_error(void);
void shell_num(unsigned int, char);

// TODO(agus): refactor para usar matriz en la comparacion
// 	       de comandos

void shell_execute(char dim) {
	char r = 0;
	unsigned int num = 0;
	while (r < dim && bufferrx_buff[r] - '0' >= 0 && bufferrx_buff[r] - '0'
			<= 9) {
		//es un digito
		num=num*10;
		num+=bufferrx_buff[r]-'0';
		r++;
	}
	if (r == dim) {
		//todos digitos
		shell_num(num, dim);
		return;
	}
	//si no correspondia a un numero sigue

	switch (dim) {
	case 1:
		switch (bufferrx_buff[0]) {
		case 'a':
			shell_A();
			break;
		case 'b':
			shell_B();
			break;
		case 'c':
			shell_C();
			break;
		default:
			shell_error();
		}
		break;
	case 2:
		if (bufferrx_buff[0] == 'o' && bufferrx_buff[1] == 'n')
			shell_on();
		break;
	case 3:
		if (bufferrx_buff[0] == 'o' && bufferrx_buff[1] == 'f'
				&& bufferrx_buff[2] == 'f')
			shell_off();
		break;
	case 5:
		if (bufferrx_buff[0] == 'r' && bufferrx_buff[1] == 'e'
				&& bufferrx_buff[2] == 's' && bufferrx_buff[3] == 'e'
				&& bufferrx_buff[4] == 't')
			shell_reset();
		break;
	default:
		shell_error();
	}
}

void shell_A(void) {
	buffertx_send_str("\r\nBarriendo con T1 = 5s");
	sound_sweep(5);
}

void shell_B(void) {
	buffertx_send_str("\r\nBarriendo con T2 = 10s");
	sound_sweep(10);
}

void shell_C(void) {
	buffertx_send_str("\r\nBarriendo con T3 = 15s");
	sound_sweep(15);
}

void shell_on(void) {
	buffertx_send_str("\r\nPrendiendo sonido...");
	sound_on();
}

void shell_off(void) {
	buffertx_send_str("\r\nApagando sonido...");
	sound_off();
}

void shell_reset(void) {
	buffertx_send_str("\r\nReseteando...");
	shell_show_commands();
	sound_reset();
}
//TODO ver el nombre
void shell_show_commands(void){
	buffertx_send_str("\r\nLista de comandos:");
	buffertx_send_str("\r\nON   >> prender el sonido");
	buffertx_send_str("\r\nOFF  >> apagar el sonido");
	buffertx_send_str("\r\nRESET>> resetear");
	buffertx_send_str("\r\nA    >> barrido de 5seg");
	buffertx_send_str("\r\nB    >> barrido de 10seg");
	buffertx_send_str("\r\nC    >> barrido de 15seg");
	buffertx_send_str("\r\nFREQ >> frecuencia fija entre 200-10000");
}

void shell_error(void) {
	buffertx_send_str("\r\nComando no reconocido");
}

void shell_num(unsigned int num, char dim) {
	char error,j;
	if ((num < MIN) || (num > MAX)) {
			buffertx_send_str("\r\nSolo entre 200-10000 Hz");
		return;
	}	
	buffertx_send_str("\r\nSeteando frecuencia ");
	//imprimo frecuencia ingresada

	for (j = 0; j < dim; j++)
		buffertx_send_char(bufferrx_buff[j]);
	error = sound_set_frequency(num);
	//imprimo el error
	buffertx_send_str("\r\nCon error de ");
	//convertir a string
	if (error < 0) {
		buffertx_send_char('-');
		error *= -1;
	}
	//TODO imprimir valor abosuluto de error	
	buffertx_send_str("Hz");
}

