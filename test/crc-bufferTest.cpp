//
// Created by Marc Zahno on 09.05.20.
//

extern "C" {
    #include "crc-buffer.h"
}

#include "gtest/gtest.h"

namespace crcbuffer {
    using namespace std;

    class BufferInstance : public ::testing::Test {
    protected:
        void TearDown() override {
            CrcBuffer_DestroyAll();
        }
    };
    TEST_F(BufferInstance, GetBufferInstance) {
        CrcBuffer instance = NULL;
        instance = CrcBuffer_CreateInstance();

        ASSERT_NE(nullptr, instance);
    }
    TEST_F(BufferInstance, GetTwoBufferInstances) {
        CrcBuffer instance1, instance2 = NULL;
        instance1 = CrcBuffer_CreateInstance();
        instance2 = CrcBuffer_CreateInstance();

        ASSERT_NE(nullptr, instance1);
        ASSERT_NE(nullptr, instance2);
        ASSERT_NE(instance1, instance2);
    }
    TEST_F(BufferInstance, NoFreeInstanceAvialable) {

        CrcBuffer currentInstance = NULL;
        uint32_t bufferPoolSize = CrcBuffer_GetBufferPoolSize();

        // Use all available instances
        for (int i = 0; i < bufferPoolSize; i++) {
            currentInstance = CrcBuffer_CreateInstance();
            ASSERT_NE(nullptr, currentInstance);
        }

        // No instances should be free anymore
        currentInstance = CrcBuffer_CreateInstance();
        ASSERT_EQ(nullptr, currentInstance);
    }

    class AddDataToBuffer : public ::testing::Test {
    public:
        static AddDataToBuffer *CurrentTestClass;
        static void OnReceivedCallback(uint8_t *data, size_t length) {
            CurrentTestClass->AddActualData(data, length);
        }
        static vector<uint8_t> CreateByteVector(uint8_t *data, size_t length){
            vector<uint8_t> v;
            for(int i=0; i<length; i++)
                v.push_back(data[i]);

            return v;
        }

        CrcBuffer BufferUnderTest = CrcBuffer_CreateInstance();
        void AddActualData(uint8_t* data, size_t length){
            auto byteVector = CreateByteVector(data, length);
            actualDataAdded.push_back(byteVector);
        }
        void AddExpectedData(uint8_t data[], size_t length){
            auto byteVector = CreateByteVector(data, length);
            expectedDataAdded.push_back(byteVector);

            CrcBuffer_Add(BufferUnderTest, data, length);
        }
        void Check(){
            ASSERT_EQ(expectedDataAdded.size(), actualDataAdded.size());
            for(auto i=0; i<expectedDataAdded.size(); i++){
                ASSERT_EQ(expectedDataAdded[i], actualDataAdded[i]);
            }
        }

    protected:
        void SetUp() override {
            CurrentTestClass = this;
            CrcBuffer_RegisterOnReceived(
                    BufferUnderTest,
                    AddDataToBuffer::OnReceivedCallback);
        }
        void TearDown() override {
            CrcBuffer_DestroyAll();
        }

    private:
        vector<vector<uint8_t>> actualDataAdded;
        vector<vector<uint8_t>> expectedDataAdded;
    };
    AddDataToBuffer *AddDataToBuffer::CurrentTestClass = NULL;
    TEST_F(AddDataToBuffer, AddData) {
        uint8_t data[] = {1,2,3,4,5};

        CurrentTestClass->AddExpectedData(data, sizeof(data));

        Check();
    }
    TEST_F(AddDataToBuffer, AddDataTwice) {
        uint8_t data1[] = {0, 1, 2, 3, 4, 5};
        uint8_t data2[] = {0, 1, 2, 3, 4, 5};

        CurrentTestClass->AddExpectedData(data1, sizeof(data1));
        CurrentTestClass->AddExpectedData(data2, sizeof(data2));

        Check();
    }
    TEST_F(AddDataToBuffer, AddDataWithOverflow){
        uint8_t data[] = {1,2,3,4,5};

        for(auto i=0; i<= 100; i++)
            CurrentTestClass->AddExpectedData(data, sizeof(data));

        Check();
    }


}