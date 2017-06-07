#ifndef BUFFERRX_H_
#define BUFFERRX_H_

extern volatile char FLAG_RECEIVED;

void bufferrx_get_char(void);
void bufferrx_receive_interrupt(void);

#endif
