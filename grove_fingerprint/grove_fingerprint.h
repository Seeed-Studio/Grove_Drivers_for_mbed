


#ifndef __GROVE_FINGERPRINT_H__
#define __GROVE_FINGERPRINT_H__

#include "suli2.h"

#define FINGERPRINT_OK 0x00
#define FINGERPRINT_PACKETRECIEVEERR 0x01
#define FINGERPRINT_NOFINGER 0x02
#define FINGERPRINT_IMAGEFAIL 0x03
#define FINGERPRINT_IMAGEMESS 0x06
#define FINGERPRINT_FEATUREFAIL 0x07
#define FINGERPRINT_NOMATCH 0x08
#define FINGERPRINT_NOTFOUND 0x09
#define FINGERPRINT_ENROLLMISMATCH 0x0A
#define FINGERPRINT_BADLOCATION 0x0B
#define FINGERPRINT_DBRANGEFAIL 0x0C
#define FINGERPRINT_UPLOADFEATUREFAIL 0x0D
#define FINGERPRINT_PACKETRESPONSEFAIL 0x0E
#define FINGERPRINT_UPLOADFAIL 0x0F
#define FINGERPRINT_DELETEFAIL 0x10
#define FINGERPRINT_DBCLEARFAIL 0x11
#define FINGERPRINT_PASSFAIL 0x13
#define FINGERPRINT_INVALIDIMAGE 0x15
#define FINGERPRINT_FLASHERR 0x18
#define FINGERPRINT_INVALIDREG 0x1A
#define FINGERPRINT_ADDRCODE 0x20
#define FINGERPRINT_PASSVERIFY 0x21

#define FINGERPRINT_STARTCODE 0xEF01

#define FINGERPRINT_COMMANDPACKET 0x1
#define FINGERPRINT_DATAPACKET 0x2
#define FINGERPRINT_ACKPACKET 0x7
#define FINGERPRINT_ENDDATAPACKET 0x8

#define FINGERPRINT_TIMEOUT 0xFF
#define FINGERPRINT_BADPACKET 0xFE

#define FINGERPRINT_GETIMAGE 0x01
#define FINGERPRINT_IMAGE2TZ 0x02
#define FINGERPRINT_REGMODEL 0x05
#define FINGERPRINT_STORE 0x06
#define FINGERPRINT_DELETE 0x0C
#define FINGERPRINT_EMPTY 0x0D
#define FINGERPRINT_VERIFYPASSWORD 0x13
#define FINGERPRINT_HISPEEDSEARCH 0x1B
#define FINGERPRINT_TEMPLATECOUNT 0x1D

//#define FINGERPRINT_DEBUG 

#define DEFAULTTIMEOUT 5000  // milliseconds

#define CMD_LENGTH 20

void grove_fingerprint_init(UART_T *uart, int pintx, int pinrx);
bool grove_fingerprint_write_setup(UART_T *uart);
bool grove_fingerprint_verifyPassword(UART_T *uart);
bool grove_fingerprint_getImage(UART_T *uart, uint8_t *res);
bool grove_fingerprint_image2Tz(UART_T *uart, uint8_t slot, uint8_t *res);
bool grove_fingerprint_createModel(UART_T *uart, uint8_t *res);
bool grove_fingerprint_storeModel(UART_T *uart, uint16_t id, uint8_t *res);
bool grove_fingerprint_deleteModel(UART_T *uart, uint16_t id, uint8_t *res);
bool grove_fingerprint_emptyDatabase(UART_T *uart, uint8_t *res);
bool grove_fingerprint_fingerFastSearch(UART_T *uart, uint8_t *res);
bool grove_fingerprint_getTemplateCount(UART_T *uart, uint8_t *res);

#endif

