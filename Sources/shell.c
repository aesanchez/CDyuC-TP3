#include "shell.h"

void shell_A(void);
void shell_B(void);
void shell_C(void);
void shell_on(void);
void shell_off(void);
void shell_reset(void);
void shell_error(void);
void shell_num(void);

// TODO(check que onda): aca habria que llamar a sound_enable o algo asi
// para que se habilite la interrucion del toggle de la salida?? Osea del
// C1??

// TODO(agus): refactor para usar matriz en la comparacion
// 	       de comandos
void shell_execute(char * command){
	// TODO: agregar lib con funcion is_num
	/* while(SEA NUMERO) */
	/* } */

	/* if(ES TRUE){ */
	/* llamo a shell con num */
	/* return */
	/* } */

	// ESTO ES HERMOSO
	switch (length(command)) {
		case 1:
			switch (command[0]) {
				case 'A':
					shell_A();
					break;
				case 'B':
					shell_B();
					break;
				case 'C':
					shell_C();
					break;
				default:
					shell_error();
			}
			break;
		case 2:
			if(command[0]=='O' && command[1]=='N') shell_on();
			break;
		case 3:
			if(command[0]=='O' && command[1]=='F' && command[2]=='F') shell_off();
			break;
		case 5:
			if(command[0]=='R' && command[1]=='E' && command[2]=='S' && command[3]=='E' && command[4]=='T') shell_reset();
			break;
		default:
			shell_error();
	}
}

// TODO: en estos casos, habria que setear el timer TPMC1V no?
void shell_A(void){
	// PERIODO ==5seg
	// TPM1C1V=????
}

void shell_B(void){
	// PERIODO ==10seg
	// TPM1C1V=????
}

void shell_C(void){
	// PERIODO ==15seg
	// TPM1C1V=????
}

void shell_on(void){

}

void shell_off(void){

}

void shell_reset(void){

}

void shell_error(void){

}

void shell_num(void){

}
