#pragma once

#include <vector>
#include <string>

class FBinary{
public:
    FBinary(){}
    FBinary(std::vector<uint8_t> data);
    FBinary(const std::string filepath);

    /**
     * This function load data from the file.
     */
    bool loadFile(std::string filepath);
    /**
     * The binary data is stored.
     */
    void setData(std::vector<uint8_t> data);
    /**
     * The index is setted to point the next data to read.
     */
    void setByteIndex(uint32_t idx);
    /**
     * The number is setted to point the next bit to read.
     */
    void setBitIndex(uint32_t idx);
    /**
     * The index is incremented by one.
     */
    void setNextIndex();
    /**
     * The bit index is incremented by one.
     */
    void setNextBit();

    /**
     * This function return the adress of the binary data.
     */
    std::vector<uint8_t>* getDataAdr();

    /**
     * This function return the current bit as pointer.
     */
    void readBit(uint8_t* out, size_t size, bool lsb=false, bool isInt=false);
    /**
     * This function return the specified number bits from current bit index as pointer.
     */
    void readBits(uint32_t nbit, uint8_t* out, size_t size, bool reverse=false, bool lsb=false, bool isInt=false);
    /**
     * This function return the current byte as pointer.
     */
    void readByte(uint8_t* out, size_t size, bool reverse=false, bool lsb=false, bool isInt=false);
    /**
     * This function return the specified number bytes from current index as pointer.
     */
    void readBytes(uint32_t nbyte, uint8_t* out, size_t size, bool reverse=false, bool lsb=false, bool isInt=false);

    /**
     * This function write the byte to the index of data.
     */
    void writeByte(uint32_t idx, uint8_t data);
    /**
     * This function write the bytes to the index of data.
     */
    bool writeBytes(uint32_t idx, uint32_t nbyte, std::vector<uint8_t> data);

    /**
     * This function print the current bit to standard output.
     */
    void printBit(bool lsb=false);

    /**
     * This function return whether the current index is end of the data.
     */
    bool eod();

private:
    std::vector<uint8_t> m_data;
    unsigned char m_buffer;
    unsigned int m_byteIndex;
    unsigned int m_bitIndex;
    bool isEnd = false;
};
