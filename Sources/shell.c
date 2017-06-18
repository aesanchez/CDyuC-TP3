#include "shell.h"
#include "bufferrx.h"
#include "sound.h"
#include "buffertx.h"

#define LEN 16
char buff[LEN];
char ibuff = 0;

void push_upper_to_lower_case(char);

// comando: sweep 5
void shell_sweep_5(void);
// comando: sweep 10
void shell_sweep_10(void);
// comando: sweep 15
void shell_sweep_15(void);
// comando: on
void shell_on(void);
// comando: off
void shell_off(void);
// comando: f 300
void shell_num(unsigned int);

void shell_error(void);
void shell_show_commands(void);

const char NUMBER_OF_COMMANDS = 6;
const char *COMMANDS[] = { "on", "off", "reset", "sweep 5", "sweep 10",
		"sweep 15" };
const char COMMANDS_LEN[] = { 2, 3, 5, 7, 8, 8 };
void (*COMMANDS_FUNC[])(void) = { shell_on, shell_off, shell_reset,
		shell_sweep_5, shell_sweep_10, shell_sweep_15 };

// devuelve 1 si str=command dentro de buff
// 0 caso contrario
char shell_compare(char * str, char length) {
	char aux = 0;
	// considerando los strings con '\0' final
	while (aux < length && str[aux] != '\0' && buff[aux] == str[aux])
		aux++;
	if (aux == length && str[aux] == '\0')
		return 1;
	return 0;
}

// shell_execute actua como dispatcher para los comandos. Esta consume el buffer
// que contiene los caracteres ingresados(sin incluir el enter), y ejecuta el
// comando correspondiente. Las funciones de los comandos estan almacenadas en un
// arreglo previamente definido.
void shell_execute(void) {
	char r = 0;
	unsigned int num = 0;
	if (shell_compare("f ", 2)) {
		// si el primer caracter es f, entonces se llama al comando
		// de frecuencia
		r = 2;
		while (r < ibuff && buff[r] - '0' >= 0 && buff[r] - '0' <= 9) {
			// es un digito
			num=num*10;
			num+=buff[r]-'0';
			r++;
		}
		if (r == ibuff) {
			// todos digitos, entonces llamamos al comando
			shell_num(num);
			return;
		}
		// si llegamos aca algo salio mal, por ejemplo no es un numero lo
		// que se paso, entonces mostramos error
		shell_error();
		return;
	}
	// si no corresponde a la instruccion de setear frecuencia sigue
	// COMMANDS_FUNC es un array de funciones de todos los comandos que quedan, sin
	// incluir el comando de setear frecuencia
	for (r = 0; r < NUMBER_OF_COMMANDS; r++) {
		if(COMMANDS_LEN[r]!=ibuff) continue;
		if(shell_compare(COMMANDS[r],ibuff)) {
			(*COMMANDS_FUNC[r])();
			return;
		}
	}
	// si llegamos aca quiere decir que no reconocemos el comando
	shell_error();
}

// shell_update chequea mediante el FLAG_RECEIVED si hay un caracter disponible
// en caso de que haya y el caracter sea "\r"(enter) entonces procede a ejecutar
// el comando. En caso de que no sea enter, guarda el caracter en el buffertx. Ademas
// chequea que la cantidad de caracteres que se ingreso previo a enter no supere el
// rango maximo.
void shell_update(void) {
	char car;
	// FLAG_RECEIVED se setea a uno dentro de la interrupcion de recepcion
	if (FLAG_RECEIVED == 0)
		return;
	car = bufferrx_get_char();
	FLAG_RECEIVED = 0;
	if (car != '\r')
		buffertx_send_char(car);
	if (car == '\r') {
		if (ibuff > 0) {
			shell_execute(); // se llama a la funcion que ejecuta el comando
		}
		ibuff = 0;
		return;
	}
	push_upper_to_lower_case(car);
	if (ibuff == LEN) {
		ibuff = 0;
		buffertx_send_str("\r\nCOMANDO FUERA DE RANGO");
		buffertx_send_str("\r\n > ");
	}
}

// shell_sweep_5 realiza un barrido de 5 segundos de duracion. La logica del barrido
// esta dentro de la funcion sound_sweep definida en la libreria sound
// 	> sweep 5
void shell_sweep_5(void) {
	buffertx_send_str("\r\nBarriendo con T1 = 5s");
	buffertx_send_str("\r\n > ");
	sound_sweep(5);
}

// shell_sweep_10 realiza un barrido de 10 segundos de duracion. La logica del barrido
// esta dentro de la funcion sound_sweep definida en la libreria sound
// 	> sweep 10
void shell_sweep_10(void) {
	buffertx_send_str("\r\nBarriendo con T2 = 10s");
	buffertx_send_str("\r\n > ");
	sound_sweep(10);
}

// shell_sweep_15 realiza un barrido de 15 segundos de duracion. La logica del barrido
// esta dentro de la funcion sound_sweep definida en la libreria sound
// 	> sweep 15
void shell_sweep_15(void) {
	buffertx_send_str("\r\nBarriendo con T3 = 15s");
	buffertx_send_str("\r\n > ");
	sound_sweep(15);
}

// shell_on habilita el sonido. Va a sonar lo que se habia ejecutado previamente,
// es decir, si se hizo un `sweep 5` y luego un `on` se va a escuchar el barrido
// de 5 segundos
// 	> on
void shell_on(void) {
	buffertx_send_str("\r\nPrendiendo sonido...");
	buffertx_send_str("\r\n > ");
	sound_on();
}

// shell_off apaga el sonido, pero los barridos o el sonido de frecuencia sigue
// corriendo, simplemente no se escucha
// 	> off
void shell_off(void) {
	buffertx_send_str("\r\nApagando sonido...");
	buffertx_send_str("\r\n > ");
	sound_off();
}

// shell_reset muestra la lista de comandos y resetea todos las configuraciones
// Esto hace que no se escuche ningun sonido
// 	> reset
void shell_reset(void) {
	shell_show_commands();
	sound_reset();
}

// shell_show_commands muestra la lista de comandos disponibles
void shell_show_commands(void) {
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
	buffertx_send_str(" con pasos de 100 Hz");
	buffertx_send_str("\r\n > ");
}

// shell_error simplemente imprime "Comando no reconocido" y el caracter
// de terminal
void shell_error(void) {
	buffertx_send_str("\r\nComando no reconocido");
	buffertx_send_str("\r\n > ");
}

// shell_num recibe por parametro un numero que indica la frecuencia que
// se desea setear. Ademas realiza los chequeos necesarios para que la
// frecuencia provista sea solo de pasos de 100 entre 200 y 10000 Hz.
// 	> f 500
// 	> f 540 => error
void shell_num(unsigned int num) {
	char error, j, i;
	char aux[3];
	if ((num < MIN) || (num > MAX)) {
		buffertx_send_str("\r\nSolo entre 200-10000 Hz");
		buffertx_send_str("\r\n > ");
		return;
	}
	if (num % STEP_FREQ != 0) {
		buffertx_send_str("\r\nSolo en pasos de 100 Hz");
		buffertx_send_str("\r\n > ");
		return;
	}

	buffertx_send_str("\r\nSeteando frecuencia ");
	// imprimo frecuencia ingresada
	for (j = 2; j < ibuff; j++)
		buffertx_send_char(buff[j]);
	error = sound_set_frequency(num);
	// imprimo el error
	buffertx_send_str("\r\nCon error de ");
	// convertir a string
	if (error < 0) {
		buffertx_send_char('-');
		error *= -1;
	}
	if (error == 0)
		buffertx_send_char('0');
	else {
		j = 0;
		while (error != 0) {
			aux[j++] = error % 10;
			error /= 10;
		}
		for (i = j; i > 0; i--)
			buffertx_send_char(aux[i - 1] + '0');
	}
	buffertx_send_str("Hz");
	buffertx_send_str("\r\n > ");
}

void push_upper_to_lower_case(char c) {
	if (c >= 'A' && c <= 'Z') {
		// mayusculas a minusculas
		c = c + ('a' - 'A');
	}
	buff[ibuff++] = c;
}

