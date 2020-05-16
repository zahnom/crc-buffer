#ifndef CRC_BUFFER_CRC_BUFFER_H
#define CRC_BUFFER_CRC_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct CrcBuffer_s *CrcBuffer;

uint32_t CrcBuffer_GetBufferPoolSize();

CrcBuffer CrcBuffer_CreateInstance();
void CrcBuffer_DestroyAll();

void CrcBuffer_Add(CrcBuffer buffer, uint8_t *data, size_t length);

void CrcBuffer_RegisterOnReceived(CrcBuffer buffer, void (*callback)(uint8_t *data, size_t length));
void CrcBuffer_RegisterChecksumProvider(uint32_t (*callback)(uint8_t checksum[4]));
void CrcBuffer_RegisterLengthProvider(uint16_t (*callback)(uint8_t length[2]));



#endif //CRC_BUFFER_CRC_BUFFER_H
