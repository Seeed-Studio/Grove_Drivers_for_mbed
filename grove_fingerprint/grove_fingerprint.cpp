

#include "suli2.h"
#include "grove_fingerprint.h"

//local functions
static void grove_fingerprint_writePacket(UART_T *uart, uint32_t addr, uint8_t packettype, 
				       uint16_t len, uint8_t *packet);
static uint8_t grove_fingerprint_getReply(UART_T *uart, uint8_t packet[], uint16_t timeout);

//local variables
static uint32_t thePassword;
static uint32_t theAddress;
static uint16_t fingerID, confidence, templateCount;
static unsigned char cmd[CMD_LENGTH];



void grove_fingerprint_init(UART_T *uart, int pintx, int pinrx)
{
    suli_uart_init(uart, pintx, pinrx, 57600);
}

bool grove_fingerprint_write_setup(UART_T *uart)
{
	thePassword = 0;
	theAddress = 0xFFFFFFFF;
	
    return true;
}

bool grove_fingerprint_verifyPassword(UART_T *uart) {
  uint8_t packet[20] = {FINGERPRINT_VERIFYPASSWORD, 
                      (thePassword >> 24), (thePassword >> 16),
                      (thePassword >> 8), thePassword};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 5+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len == 1) && (packet[0] == FINGERPRINT_ACKPACKET) && (packet[1] == FINGERPRINT_OK))
    return true;

/*
  Serial.print("\nGot packet type "); Serial.print(packet[0]);
  for (uint8_t i=1; i<len+1;i++) {
    Serial.print(" 0x");
    Serial.print(packet[i], HEX);
  }
  */
  return false;
}

bool grove_fingerprint_getImage(UART_T *uart, uint8_t *res) {
  uint8_t packet[20] = {FINGERPRINT_GETIMAGE};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 1+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;
   else
   {
	*res = packet[1];
	return true;
   }
}

bool grove_fingerprint_image2Tz(UART_T *uart, uint8_t slot, uint8_t *res) {
  uint8_t packet[20] = {FINGERPRINT_IMAGE2TZ, slot};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 2+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;
   else
   {
	*res = packet[1];
	return true;
   }
}

bool grove_fingerprint_createModel(UART_T *uart, uint8_t *res) {
  uint8_t packet[20] = {FINGERPRINT_REGMODEL};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 1+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;
   else
   {
	*res = packet[1];
	return true;
   }
}


bool grove_fingerprint_storeModel(UART_T *uart, uint16_t id, uint8_t *res) {
  uint8_t packet[20] = {FINGERPRINT_STORE, 0x01, id >> 8, id & 0xFF};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 4+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;
   else
   {
	*res = packet[1];
	return true;
   }
}

bool grove_fingerprint_deleteModel(UART_T *uart, uint16_t id, uint8_t *res) {
    uint8_t packet[20] = {FINGERPRINT_DELETE, id >> 8, id & 0xFF, 0x00, 0x01};
    grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 5+2, packet);
    uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
        
   if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;
   else
   {
	*res = packet[1];
	return true;
   }
}

bool grove_fingerprint_emptyDatabase(UART_T *uart, uint8_t *res) {
  uint8_t packet[20] = {FINGERPRINT_EMPTY};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 1+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;
   else
   {
	*res = packet[1];
	return true;
   }
}

bool grove_fingerprint_fingerFastSearch(UART_T *uart, uint8_t *res) {
  fingerID = 0xFFFF;
  confidence = 0xFFFF;
  // high speed search of slot #1 starting at page 0x0000 and page #0x00A3 
  uint8_t packet[20] = {FINGERPRINT_HISPEEDSEARCH, 0x01, 0x00, 0x00, 0x00, 0xA3};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 6+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;

  fingerID = packet[2];
  fingerID <<= 8;
  fingerID |= packet[3];
  
  confidence = packet[4];
  confidence <<= 8;
  confidence |= packet[5];
  
  *res = packet[1];
	return true;
}

bool grove_fingerprint_getTemplateCount(UART_T *uart, uint8_t *res) {
  templateCount = 0xFFFF;
  // get number of templates in memory
  uint8_t packet[20] = {FINGERPRINT_TEMPLATECOUNT};
  grove_fingerprint_writePacket(uart, theAddress, FINGERPRINT_COMMANDPACKET, 1+2, packet);
  uint8_t len = grove_fingerprint_getReply(uart, packet, 500);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return false;

  templateCount = packet[2];
  templateCount <<= 8;
  templateCount |= packet[3];
  
  *res = packet[1];
	return true;
}

static void grove_fingerprint_writePacket(UART_T *uart, uint32_t addr, uint8_t packettype, 
				       uint16_t len, uint8_t *packet) {
	uint8_t i = 0;
 

	cmd[0] = (uint8_t)(FINGERPRINT_STARTCODE >> 8);
	cmd[1] = (uint8_t)FINGERPRINT_STARTCODE;
	cmd[2] = (uint8_t)(addr >> 24);
	cmd[3] = (uint8_t)(addr >> 16);
	cmd[4] = (uint8_t)(addr >> 8);
	cmd[5] = (uint8_t)(addr);
	cmd[6] = (uint8_t)packettype;
	cmd[7] = (uint8_t)(len >> 8);
	cmd[8] = (uint8_t)(len);

  uint16_t sum = (len>>8) + (len&0xFF) + packettype;
  for (i=0; i< len-2; i++) {
	cmd[9+i] = packet[i];
    sum += packet[i];
  }

	cmd[9+i] = (uint8_t)(sum>>8);
	cmd[9+i+1] = (uint8_t)sum;
	
	suli_uart_write_bytes(uart, (uint8_t*)cmd, 9+i+1+1);
}


static uint8_t grove_fingerprint_getReply(UART_T *uart, uint8_t packet[], uint16_t timeout) {
  uint8_t reply[20], idx;
  uint16_t timer=0;
  
  idx = 0;
#ifdef FINGERPRINT_DEBUG
  Serial.print("<--- ");
#endif
while (true) {
	while (!suli_uart_readable(uart))
	{
	  suli_delay_ms(1);
      timer++;
      if (timer >= timeout) return FINGERPRINT_TIMEOUT;
    }
    
	reply[idx] = suli_uart_read(uart);

    if ((idx == 0) && (reply[0] != (FINGERPRINT_STARTCODE >> 8)))
      continue;
    idx++;
    
    // check packet!
    if (idx >= 9) {
      if ((reply[0] != (FINGERPRINT_STARTCODE >> 8)) ||
          (reply[1] != (FINGERPRINT_STARTCODE & 0xFF)))
          return FINGERPRINT_BADPACKET;
      uint8_t packettype = reply[6];
      
      uint16_t len = reply[7];
      len <<= 8;
      len |= reply[8];
      len -= 2;
      
      if (idx <= (len+10)) continue;
      packet[0] = packettype;      
      for (uint8_t i=0; i<len; i++) {
        packet[1+i] = reply[9+i];
      }

      return len;
    }
  }
}










