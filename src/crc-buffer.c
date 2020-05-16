#include "crc-buffer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 512
#define BUFFER_POOL_SIZE 5

struct CrcBuffer_s {
    bool isInUse;
    void (*onReceived)(uint8_t *data, size_t length);
    uint8_t data[BUFFER_SIZE];
    uint16_t index;
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
static uint16_t IncrementIndex(uint16_t index){
    auto nextIndex = (index + 1) % BUFFER_SIZE;
    return nextIndex;
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

    if(instance == NULL){
        OnNoFreeInstanceAvailable();
    }
    else {
        instance->isInUse = true;
        instance->index = 0;
        ResetData(instance);
    }

    return instance;
}
void CrcBuffer_Add(CrcBuffer buffer, uint8_t *data, size_t length){
    auto startIndex = buffer->index;

    for(uint32_t i=0; i<length; i++){
        buffer->data[buffer->index] = data[i];
        buffer->index = IncrementIndex(buffer->index);
    }

    buffer->onReceived(&buffer->data[startIndex], length);
}
void CrcBuffer_DestroyAll(){
    ForEachInstance(DestroyInstance);
}

uint32_t CrcBuffer_GetBufferPoolSize(){
    return BUFFER_POOL_SIZE;
}

void CrcBuffer_RegisterOnReceived(CrcBuffer buffer, void (*callback)(uint8_t *data, size_t length)){
    buffer->onReceived = callback;
}
void CrcBuffer_RegisterChecksumProvider(uint32_t (*callback)(uint8_t checksum[4])){

}
void CrcBuffer_RegisterLengthProvider(uint16_t (*callback)(uint8_t length[2])) {

}

