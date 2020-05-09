#ifndef CRC_BUFFER_CRC_BUFFER_H
#define CRC_BUFFER_CRC_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct CrcBuffer_s *CrcBuffer;

uint32_t CrcBuffer_GetBufferPoolSize();
CrcBuffer CrcBuffer_CreateInstance();
void CrcBuffer_DestroyAll();

#endif //CRC_BUFFER_CRC_BUFFER_H
