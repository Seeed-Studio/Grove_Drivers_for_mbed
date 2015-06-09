

#include "grove_esp8266_class.h"

GroveEsp8266::GroveEsp8266(int pintx, int pinrx)
{
    this->uart = (UART_T *)malloc(sizeof(UART_T));
    grove_esp8266_init(this->uart, pintx, pinrx);
}

bool GroveEsp8266::write_setup(void)
{
    return grove_esp8266_write_setup(this->uart);
}

bool GroveEsp8266::attach_event_handler(CALLBACK_T handler)
{
    return grove_esp8266_attach_event_handler(handler);
}

bool GroveEsp8266::read_version(void)
{
    return grove_esp8266_read_getversion(this->uart);
}

bool GroveEsp8266::write_joinwifi(char *ssid, char *pwd)
{
    return grove_esp8266_write_joinwifi(this->uart, ssid, pwd);
}

bool GroveEsp8266::write_socketasclient(char *ip, unsigned int port)
{
    return grove_esp8266_write_socketasclient(this->uart, ip, port);
}

bool GroveEsp8266::read_aplist(void)
{
    return grove_esp8266_read_aplist(this->uart);
}

bool GroveEsp8266::write_msg(char *msg, unsigned int len)
{
    return grove_esp8266_write_msg(this->uart, msg, len);
}
