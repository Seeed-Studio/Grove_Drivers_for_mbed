

#include "suli2.h"
#include "grove_esp8266.h"



//local functions
static void _uart_rx_callback(void);
static bool esp8266_send_cmd(UART_T *uart, char *command, char *content, unsigned int timeout);
__weak static void esp8266_callback(char *msg, unsigned int len);


//local variables
static char content_buffer[CONTENT_BUF_LEN];
static char rx_buf[RX_BUF_LEN];
static unsigned int rx_buf_ptr = 0;//point to the next unused char of rx_buf
static char cmd[70];
static char cmd_buf[70];
static char *WaitForAnswer_cmd_Buffer;
static char *WaitForAnswer_ans_Buffer;
static char *WaitForAnswer_data_Buffer;
static ESP8266_RecvStateMachine recv_machine = RECV_DATA;
static bool flag_recved_cmd = false;
static bool flag_recved_end = false;
static bool flag_send_ok = false;

static UART_T *_uart;
static user_cb_fun_ptr user_cb_fun;
EVENT_T event_esp8266;

void grove_esp8266_init(UART_T *uart, int pintx, int pinrx)
{
    suli_uart_init(uart, pintx, pinrx, 115200);
}

bool grove_esp8266_write_setup(UART_T *uart)
{
	memset((void *)rx_buf, 0, RX_BUF_LEN);
	memset((void *)content_buffer, 0, CONTENT_BUF_LEN);
	_uart = uart;
	suli_uart_rx_event_attach(uart, (cb_fun_ptr)&_uart_rx_callback);
	grove_esp8266_write_setcbfun(esp8266_callback);
	
    return true;
}

void grove_esp8266_write_setcbfun(user_cb_fun_ptr fun)
{
	user_cb_fun = fun;
}

bool grove_esp8266_attach_event_handler(CALLBACK_T handler)
{
    suli_event_init(&event_esp8266, handler);
//    pinMode(13, INPUT_PULLUP);
//    attachInterrupt(13, _trigger, FALLING);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool grove_esp8266_read_getversion(UART_T *uart)
{
    //read version information
	while(esp8266_send_cmd(uart, (char*)"AT+GMR", content_buffer, 200) != true)
	{
		printf("try again\r\n");
		wait(0.5);
	}
	printf("Version: %s\r\n", content_buffer);
	
    return true;
}

bool grove_esp8266_write_joinwifi(UART_T *uart, char *ssid, char *pwd)
{
    //set to station mode
	printf("set mode to STATION\r\n");
	wait(0.1);
	while(esp8266_send_cmd(uart, (char*)"AT+CWMODE=1", content_buffer, 200) != true)
	{
		printf("try again\r\n");
		wait(0.5);
	}
	printf("OK\r\n\r\n");
	
	//join router
	printf("joining specified router\r\n");
	wait(0.1);
	while(esp8266_send_cmd(uart, (char*)"AT+CWJAP=\"stu.se.private\",\"depot0510se\"", content_buffer, 5000) != true)
	{
		printf("try again\r\n");
		wait(0.5);
	}
	printf("joined\r\n");
	wait(0.1);
	while(esp8266_send_cmd(uart, (char*)"AT+CWJAP?", content_buffer, 1000) != true)
	{
		printf("try again\r\n");
		wait(0.5);
	}
	printf("joined indeed\r\n\r\n");
	
    return true;
}

bool grove_esp8266_write_socketasclient(UART_T *uart, char *ip, unsigned int port)
{
	//enable mux connection
	printf("enable mux connection\r\n");
	wait(0.1);
	while(esp8266_send_cmd(uart, (char*)"AT+CIPMUX=1", content_buffer, 200) != true)
	{
		printf("try again\r\n");
		wait(0.5);
	}
	printf("OK\r\n\r\n");
	
	//connect to tcp server
	printf("connect to tcp server\r\n");
	wait(0.1);
	while(esp8266_send_cmd(uart, (char*)"AT+CIPSTART=4,\"TCP\",\"192.168.21.159\",6320", content_buffer, 2000) != true)
	{
		printf("try again\r\n");
		wait(0.5);
	}
	printf("OK\r\n\r\n");
	
	return true;
}

bool grove_esp8266_read_aplist(UART_T *uart)
{
	//list all AP
	printf("list all AP around\r\n");
	wait(0.1);
	while(esp8266_send_cmd(uart, (char*)"AT+CWLAP", content_buffer, 10000) != true)
	{
		printf("try again\r\n");
		wait(0.5);
	}
	printf("%s\r\n", content_buffer);
	
	return true;
}

/*
function: internal function, uart callback
*/
static void _uart_rx_callback(void)
{
	unsigned int payload_len, header_len;
	unsigned int port;
	int res;
	char *payload_str;
	
	while(suli_uart_readable(_uart))
	{
		if(rx_buf_ptr < RX_BUF_LEN - 2)
		{
			rx_buf[rx_buf_ptr++] = suli_uart_read(_uart);
		}
	}
	//receiving state machine after recved all data for now
	switch(recv_machine)
	{
		case RECV_DATA:
			WaitForAnswer_data_Buffer = strstr(rx_buf, "\r\n+IPD");//check the "+IPD" response
			if(WaitForAnswer_data_Buffer != NULL)//user data recved
			{
				res = sscanf(rx_buf,"\r\n+IPD,%d,%d:", &port, &payload_len);
				payload_str = strtok(rx_buf, ":");
				header_len = strlen(payload_str) + 1;
				if((res == 2) && (payload_len == rx_buf_ptr - header_len))
				{
					memcpy(content_buffer, rx_buf + header_len, payload_len);
					user_cb_fun(content_buffer, payload_len);
					memset(rx_buf, 0, rx_buf_ptr);//clear the buffer for next recv
					rx_buf_ptr = 0;
				}
			}
			break;
		case RECV_CMD:
			WaitForAnswer_cmd_Buffer = strstr(rx_buf, cmd_buf);//check the cmd
			if(WaitForAnswer_cmd_Buffer != NULL)//right cmd
			{
				flag_recved_cmd = true;
				recv_machine = RECV_END;
			}
			break;
		case RECV_END:
			//check the "OK" response
			WaitForAnswer_ans_Buffer = strstr(WaitForAnswer_cmd_Buffer, "\r\nOK\r\n");
			if(WaitForAnswer_ans_Buffer != NULL)//"OK"recved
			{
				//recv cmd response
				flag_recved_end = true;
			}
			//check the "ERROR" response
			WaitForAnswer_ans_Buffer = strstr(WaitForAnswer_cmd_Buffer, "\r\nERROR\r\n");
			if(WaitForAnswer_ans_Buffer != NULL)//"ERROR"recved
			{
				flag_recved_end = true;
			}
			//check the "SEND OK" response
			WaitForAnswer_ans_Buffer = strstr(WaitForAnswer_cmd_Buffer, "\r\nSEND OK\r\n");
			if(WaitForAnswer_ans_Buffer != NULL)//"SEND OK"recved
			{
				flag_send_ok = true;
			}
			break;
		default:
			break;
	}
}

/*
function: send data through ESP8266
const char *command: AT command to be send
char *content: returned data from ESP8266
unsigned int timeout: timeout
*/
static bool esp8266_send_cmd(UART_T *uart, char *command, char *content, unsigned int timeout)
{
	volatile uint32_t TxWaitForResponse_TimeStmp;
	unsigned int len;
	
	//reset flags and state machine
	recv_machine = RECV_CMD;
	flag_recved_cmd = false;
	flag_recved_end = false;
	//clear the buffer
	memset(rx_buf, 0, rx_buf_ptr);//clear the buffer for next recv
	rx_buf_ptr = 0;
	//save the cmd just sent
	strcpy(cmd_buf, command);
	sprintf(cmd, "%s\r\n", command);
	//send cmd
	suli_uart_write_bytes(_uart, (uint8_t*)cmd, strlen(cmd));
	
	//wait for response
	TxWaitForResponse_TimeStmp = millis();
	while(millis() - TxWaitForResponse_TimeStmp < timeout)//timeout control
	{
		if(flag_recved_cmd == true)
		{
			if(flag_recved_end == true)
			{
				WaitForAnswer_ans_Buffer = strstr(WaitForAnswer_cmd_Buffer, "\r\nOK\r\n");//check the "OK" response
				if(WaitForAnswer_ans_Buffer != NULL)
				{
					len = WaitForAnswer_ans_Buffer - WaitForAnswer_cmd_Buffer - strlen(cmd_buf) - 3;
					memset(content, 0, CONTENT_BUF_LEN);
					memcpy(content, WaitForAnswer_ans_Buffer - len, len);
					memset(rx_buf, 0, rx_buf_ptr);//clear the buffer for next recv
					rx_buf_ptr = 0;
					recv_machine = RECV_DATA;
					return true;
				}
			}
		}
		wait(0.1);
	}
	memset(rx_buf, 0, rx_buf_ptr);//clear the buffer for next recv
	rx_buf_ptr = 0;
	recv_machine = RECV_DATA;
	return false;
}

/*
function: send data through ESP8266
char *data: data will be send
unsigned int len: data length in byte
*/
bool grove_esp8266_write_msg(UART_T *uart, char *msg, unsigned int len)
{
	volatile uint32_t TxWaitForResponse_TimeStmp;
	unsigned ptr = 0;
	
	if(len > 2048)
		return false;
	
	//send cmd
	sprintf(cmd, "AT+CIPSEND=4,%d", len);
	if(esp8266_send_cmd(uart, cmd, content_buffer, 200) != true)
	{
		return false;
	}
	//send user data
	while(len--)
	{
		suli_uart_write(uart, msg[ptr++]);
	}
	
	//reset flags and state machine
	recv_machine = RECV_END;
	flag_recved_cmd = false;
	flag_recved_end = false;
	flag_send_ok = false;
	
	//wait for response
	TxWaitForResponse_TimeStmp = millis();
	while(millis() - TxWaitForResponse_TimeStmp < 500)//timeout control
	{
		if(flag_send_ok == true)
		{
			memset(rx_buf, 0, rx_buf_ptr);//clear the buffer for next recv
			rx_buf_ptr = 0;
			recv_machine = RECV_DATA;
			return true;
		}
		wait(0.01);
	}
	memset(rx_buf, 0, rx_buf_ptr);//clear the buffer for next recv
	rx_buf_ptr = 0;
	recv_machine = RECV_DATA;
	return false;
}

/*
callback function when a piece of message arrived
this is a WEAK declaration
*/
__weak static void esp8266_callback(char *msg, unsigned int len)
{
	msg[len] = '\0';
	printf("esp8266 driver recv%3d bytes: %s\r\n", len, msg);
	printf("user can add his own callback function instead\r\n");
}


















