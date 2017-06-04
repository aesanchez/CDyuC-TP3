#include "shell.h"
#include "bufferrx.h"
#include "sound.h"
#include "buffertx.h"

void shell_sweep_5(void);
void shell_sweep_10(void);
void shell_sweep_15(void);
void shell_on(void);
void shell_off(void);
void shell_reset(void);
void shell_error(void);
void shell_num(unsigned int, char);

const char NUMBER_OF_COMMANDS=6;
const char *COMMANDS[]={"on","off","reset","sweep 5","sweep 10","sweep 15"};
const char COMMANDS_LEN[]={2,3,5,7,8,8};
void (*COMMANDS_FUNC[])(void) = { shell_on, shell_off, shell_reset, shell_sweep_5, shell_sweep_10, shell_sweep_15};

//returns 1 if str=command on buff
//0 otherwise
char shell_compare(char * str,char length){
	char aux = 0;
	//considerando los strings con '\0' final
	while(aux < length && str[aux] != '\0' && bufferrx_buff[aux] == str[aux])
		aux++;
	if(aux == length && str[aux] == '\0') return 1;
	return 0;
}

void shell_execute(char command_length) {
	char r=0;
	unsigned int num = 0;
	if (shell_compare("f ",2)) {
		r = 2;
		while (r < command_length && bufferrx_buff[r] - '0' >= 0 && bufferrx_buff[r] - '0'
				<= 9) {
			//es un digito
			num=num*10;
			num+=bufferrx_buff[r]-'0';
			r++;
		}
		if (r == command_length) {
			//todos digitos
			shell_num(num, command_length);
			return;
		}
		shell_error();
	}	
	//si no corresponde a la instruccion de setear frecuencia sigue
	for(r=0;r<NUMBER_OF_COMMANDS;r++){
		if(COMMANDS_LEN[r]!=command_length) continue;
		if(shell_compare(COMMANDS[r],command_length)){
			(*COMMANDS_FUNC[r])();
			return;
		}	
	}
	shell_error();
}

void shell_sweep_5(void) {
	buffertx_send_str("\r\nBarriendo con T1 = 5s");
	sound_sweep(5);
}

void shell_sweep_10(void) {
	buffertx_send_str("\r\nBarriendo con T2 = 10s");
	sound_sweep(10);
}

void shell_sweep_15(void) {
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

void shell_show_commands(void){
	buffertx_send_str("\r\nLista de comandos:");
	buffertx_send_str("\r\n------------------");
	buffertx_send_str("\r\nON       >> prender el sonido");
	buffertx_send_str("\r\nOFF      >> apagar el sonido");
	buffertx_send_str("\r\nRESET    >> resetear");
	buffertx_send_str("\r\nSWEEP 5  >> barrido de 5seg");
	buffertx_send_str("\r\nSWEEP 10 >> barrido de 10seg");
	buffertx_send_str("\r\nSWEEP 15 >> barrido de 15seg");
	buffertx_send_str("\r\nF FREQ   >>");
	buffertx_send_str(" frecuencia fija entre 200-10000");
	buffertx_send_str("\r\n > ");
}

void shell_error(void) {
	buffertx_send_str("\r\nComando no reconocido");
}

void shell_num(unsigned int num, char command_length) {
	char error, j, i;
	char aux[3];
	if ((num < MIN) || (num > MAX)) {
		buffertx_send_str("\r\nSolo entre 200-10000 Hz");
		return;
	}
	buffertx_send_str("\r\nSeteando frecuencia ");
	//imprimo frecuencia ingresada
	for (j = 2; j < command_length; j++)
		buffertx_send_char(bufferrx_buff[j]);
	error = sound_set_frequency(num);
	//imprimo el error
	buffertx_send_str("\r\nCon error de ");
	//convertir a string
	if (error < 0) {
		buffertx_send_char('-');
		error *= -1;
	}
	if(error == 0) buffertx_send_char('0');
	else {
		j=0;
		while(error != 0){
			aux[j++] = error % 10;
			error /= 10;
		}

		for (i = j; i >0 ; i--)
			buffertx_send_char(aux[i-1]+'0');
	}
	buffertx_send_str("Hz");
}

