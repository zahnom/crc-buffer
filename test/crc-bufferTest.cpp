//
// Created by Marc Zahno on 09.05.20.
//

extern "C" {
    #include "crc-buffer.h"
}

#include "gtest/gtest.h"

class BufferInstance : public ::testing::Test {
protected:
    void TearDown() override {
        CrcBuffer_DestroyAll();
    }
};

TEST_F(BufferInstance, GetBufferInstance){
    CrcBuffer instance = NULL;
    instance = CrcBuffer_CreateInstance();

    ASSERT_NE(nullptr, instance);
}

TEST_F(BufferInstance, GetTwoBufferInstances){
    CrcBuffer instance1, instance2 = NULL;
    instance1 = CrcBuffer_CreateInstance();
    instance2 = CrcBuffer_CreateInstance();

    ASSERT_NE(nullptr, instance1);
    ASSERT_NE(nullptr, instance2);
    ASSERT_NE(instance1, instance2);
}

TEST_F(BufferInstance, NoFreeInstanceAvialable){

    CrcBuffer currentInstance = NULL;
    uint32_t bufferPoolSize = CrcBuffer_GetBufferPoolSize();

    // Use all available instances
    for(int i=0; i<bufferPoolSize; i++){
        currentInstance = CrcBuffer_CreateInstance();
        ASSERT_NE(nullptr, currentInstance);
    }

    currentInstance = CrcBuffer_CreateInstance();
    ASSERT_EQ(nullptr, currentInstance);
}

TEST(AddDataToBuffer, SimpleAdd) {

}