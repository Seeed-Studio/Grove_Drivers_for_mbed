

#include "grove_fingerprint_class.h"

GroveFingerprint::GroveFingerprint(int pintx, int pinrx)
{
    this->uart = (UART_T *)malloc(sizeof(UART_T));
    grove_fingerprint_init(this->uart, pintx, pinrx);
}

bool GroveFingerprint::write_setup(void)
{
    return grove_fingerprint_write_setup(this->uart);
}

bool GroveFingerprint::verifyPassword(void)
{
    return grove_fingerprint_verifyPassword(this->uart);
}

bool GroveFingerprint::getImage(uint8_t *res)
{
    return grove_fingerprint_getImage(this->uart, res);
}

bool GroveFingerprint::image2Tz(uint8_t slot, uint8_t *res)
{
    return grove_fingerprint_image2Tz(this->uart, slot, res);
}

bool GroveFingerprint::createModel(uint8_t *res)
{
    return grove_fingerprint_createModel(this->uart, res);
}

bool GroveFingerprint::storeModel(uint16_t id, uint8_t *res)
{
    return grove_fingerprint_storeModel(this->uart, id, res);
}

bool GroveFingerprint::deleteModel(uint16_t id, uint8_t *res)
{
    return grove_fingerprint_deleteModel(this->uart, id, res);
}

bool GroveFingerprint::emptyDatabase(uint8_t *res)
{
    return grove_fingerprint_emptyDatabase(this->uart, res);
}

bool GroveFingerprint::fingerFastSearch(uint8_t *res)
{
    return grove_fingerprint_fingerFastSearch(this->uart, res);
}

bool GroveFingerprint::getTemplateCount(uint8_t *res)
{
    return grove_fingerprint_getTemplateCount(this->uart, res);
}





