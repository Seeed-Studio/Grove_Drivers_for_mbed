


#ifndef __GROVE_ESP8266_CLASS_H__
#define __GROVE_ESP8266_CLASS_H__

#include "grove_esp8266.h"

//GROVE_NAME        "Grove_Esp8266"
//IF_TYPE           UART
//IMAGE_URL         http://www.seeedstudio.com/depot/includes/templates/bootstrap/images/ico/grove.png

class GroveEsp8266
{
public:
    GroveEsp8266(int pintx, int pinrx);
    bool write_setup(void);
    bool read_lux(uint32_t *lux);
    bool attach_event_handler(CALLBACK_T handler);
	
	bool read_version(void);
	bool write_joinwifi(char *ssid, char *pwd);
	bool write_socketasclient(char *ip, unsigned int port);
	bool read_aplist(void);
	bool write_msg(char *msg, unsigned int len);
	

private:
    UART_T *uart;
};

#endif
