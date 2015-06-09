


#ifndef __GROVE_ESP8266_H__
#define __GROVE_ESP8266_H__

#include "suli2.h"


#define RX_BUF_LEN 			1500//the maximum message length of ESP8266 is 1460
#define CONTENT_BUF_LEN 	1500//the maximum message length of ESP8266 is 1460

#define millis()   (us_ticker_read()/1000)

typedef enum
{
	RECV_DATA,
	RECV_CMD,
	RECV_END,
}ESP8266_RecvStateMachine;

typedef void (*user_cb_fun_ptr)(char *, unsigned int);//jacly add

void grove_esp8266_init(UART_T *uart, int pintx, int pinrx);
bool grove_esp8266_write_setup(UART_T *uart);
void grove_esp8266_write_setcbfun(user_cb_fun_ptr fun);
bool grove_esp8266_attach_event_handler(CALLBACK_T handler);
bool grove_esp8266_read_getversion(UART_T *uart);
bool grove_esp8266_write_joinwifi(UART_T *uart, char *ssid, char *pwd);
bool grove_esp8266_write_socketasclient(UART_T *uart, char *ip, unsigned int port);
bool grove_esp8266_read_aplist(UART_T *uart);
bool grove_esp8266_write_msg(UART_T *uart, char *msg, unsigned int len);


#endif
