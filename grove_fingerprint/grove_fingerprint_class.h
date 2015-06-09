


#ifndef __GROVE_FINGERPRINT_CLASS_H__
#define __GROVE_FINGERPRINT_CLASS_H__

#include "grove_fingerprint.h"

//GROVE_NAME        "Grove_Fingerprint"
//IF_TYPE           UART
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:Print_Sensor.jpg

class GroveFingerprint
{
public:
    GroveFingerprint(int pintx, int pinrx);
    bool write_setup(void);
	bool verifyPassword(void);
	bool getImage(uint8_t *res);
	bool image2Tz(uint8_t slot, uint8_t *res);
	bool createModel(uint8_t *res);
	bool storeModel(uint16_t id, uint8_t *res);
	bool deleteModel(uint16_t id, uint8_t *res);
	bool emptyDatabase(uint8_t *res);
	bool fingerFastSearch(uint8_t *res);
	bool getTemplateCount(uint8_t *res);

private:
    UART_T *uart;
};

#endif
