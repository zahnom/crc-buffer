#include "crc-buffer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 512
#define BUFFER_POOL_SIZE 5

struct CrcBuffer_s {
    bool isInUse;
    uint8_t data[BUFFER_SIZE];
};

static struct CrcBuffer_s BufferPool[BUFFER_POOL_SIZE];

static void OnNoFreeInstanceAvailable(){

}
static void ForEachInstance(void (*f)(CrcBuffer buffer)){
    for(uint32_t i=0; i<BUFFER_POOL_SIZE; i++){
        CrcBuffer currentBuffer = &BufferPool[i];
        f(currentBuffer);
    }
}
static void ResetData(CrcBuffer instance){
    for(uint32_t i=0; i<BUFFER_SIZE; i++){
        instance->data[i] = 0;
    }
}
static void DestroyInstance(CrcBuffer instance){
    instance->isInUse = false;
    ResetData(instance);

}
static CrcBuffer FindFreeInstance(){

    // Search for a free buffer in the buffer pool.
    for(uint32_t i=0; i<BUFFER_POOL_SIZE; i++){
        CrcBuffer currentBuffer = &BufferPool[i];

        if(currentBuffer->isInUse == false)
            return currentBuffer;
    }

    // No free buffers available, sorry!
    return NULL;
}
CrcBuffer CrcBuffer_CreateInstance(){
    CrcBuffer instance = FindFreeInstance();

    if(instance == NULL)
        OnNoFreeInstanceAvailable();
    else
        instance->isInUse = true;
    
    return instance;
}
void CrcBuffer_DestroyAll(){
    ForEachInstance(DestroyInstance);
}

uint32_t CrcBuffer_GetBufferPoolSize(){
    return BUFFER_POOL_SIZE;
}
