#include "shell.h"
#include "bufferrx.h"

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

void shell_execute(char dim) {
	char r=0;
	char num=0;
	while(r<dim && bufferrx_buff[r]-'0'>=0 && bufferrx_buff[r]-'0'<=9){
		//es un digito
		num=num*10;
		num+=bufferrx_buff[r];
		r++;		
	}
	if(r==dim){
		//todos digitos
		shell_num(num);
		return;
	}	
	//si no correspondia a un numero sigue
	
	switch (dim) {
	case 1:
		switch (bufferrx_buff[0]) {
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
		if (bufferrx_buff[0] == 'O' && bufferrx_buff[1] == 'N')
			shell_on();
		break;
	case 3:
		if (bufferrx_buff[0] == 'O' && bufferrx_buff[1] == 'F'
				&& bufferrx_buff[2] == 'F')
			shell_off();
		break;
	case 5:
		if (bufferrx_buff[0] == 'R' && bufferrx_buff[1] == 'E'
				&& bufferrx_buff[2] == 'S' && bufferrx_buff[3] == 'E'
				&& bufferrx_buff[4] == 'T')
			shell_reset();
		break;
	default:
		shell_error();
	}
}

// TODO: en estos casos, habria que setear el timer TPMC1V no?
void shell_A(void) {
	// PERIODO ==5seg
	// TPM1C1V=????
}

void shell_B(void) {
	// PERIODO ==10seg
	// TPM1C1V=????
}

void shell_C(void) {
	// PERIODO ==15seg
	// TPM1C1V=????
}

void shell_on(void) {

}

void shell_off(void) {

}

void shell_reset(void) {

}

void shell_error(void) {

}

void shell_num(void) {

}
