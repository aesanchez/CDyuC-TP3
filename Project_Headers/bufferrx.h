#ifndef BUFFERRX_H_
#define BUFFERRX_H_

#define LEN 16
extern char bufferrx_buff[LEN];
extern volatile char FLAG_RECEIVED;

void bufferrx_receive_handler(void);
void bufferrx_receive_interrupt(void);


#endif
