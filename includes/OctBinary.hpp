#pragma once

#include <vector>
#include <string>

class OctBinary{
public:
    /**
     * \brief Constructor.
     */
    OctBinary(){}
    /**
     * \brief Constructor.
     */
    OctBinary(std::vector<uint8_t> data);
    /**
     * \brief Constructor.
     */
    OctBinary(const std::string filepath);

    /**
     * \brief Load data from the file.
     * \param filepath Binary file path.
     */
    bool loadFile(std::string filepath);
    /**
     * \brief Store the binary data.
     * \param data Binary data.
     */
    void setData(std::vector<uint8_t> data);
    /**
     * \brief Set current byte to buffer.
     */
    void setCurrentBuffer();
    /**
     * \brief The index is setted to point the next data to read.
     * \param idx Index of data.
     */
    void setByteIndex(uint32_t idx);
    /**
     * \brief The number is setted as location of the read next bit.
     * \param idx Index of bit.
     */
    void setBitIndex(uint32_t idx);
    /**
     * \brief The index is incremented by one.
     */
    void setNextIndex();
    /**
     * \brief The bit index is incremented by one.
     */
    void setNextBit();

    /**
     * \brief This function return the adress of the binary data.
     * \return Address of the data.
     */
    std::vector<uint8_t>* getDataAdr();

    /**
     * \brief This function return the current bit as pointer.
     * \param out   Pointer to the variable for the output.
     * \param size  Size of specified variable as argument out.
     * \param lsb   Flag, specifying whether to read the least significant bit.
     * \param isInt Flag, specifying whether the variable out is integer.
     */
    void readBit(uint8_t* out, size_t size, bool lsb=false, bool isInt=false);
    /**
     * \brief This function return the specified number bits from current bit index as pointer.
     * \param nbit      Number of the output byte.
     * \param out       Pointer to the variable for the output.
     * \param size      Size of the variable out.
     * \param reverse   Flag, specifying whether to reverse the output bits.
     * \param isInt     Flag, specifying whether the variable out is integer.
     */
    void readBits(uint32_t nbit, uint8_t* out, size_t size, bool reverse=false, bool lsb=false, bool isInt=false);
    /**
     * \brief This function return the current byte as pointer.
     * \param out       Pointer to the variable for the output.
     * \param size      Size of the variable out.
     * \param reverse   Flag, specifying whether to reverse the outputbits.
     * \param lsb       Flag, specifying whether to read the least significant bit iterately.
     * \param isInt     Flag, specifying whether the variable out is integer.
     */
    void readByte(uint8_t* out, size_t size, bool reverse=false, bool lsb=false, bool isInt=false);
    /**
     * \brief This function return the specified number bytes from current index as pointer.
     * \param nbyte     The number of the byte to read.
     * \param out       Pointer to the variable for the output.
     * \param size      Size of the variable out.
     * \param reverse   Flag, specifying whether to reverse the outputbits.
     * \param lsb       Flag, specifying whether to read the least significant bit iterately.
     * \param isInt     Flag, specifying whether the variable out is integer.
     */
    void readBytes(uint32_t nbyte, uint8_t* out, size_t size, bool reverse=false, bool lsb=false, bool isInt=false);

    /**
     * \brief This function write the byte to the index of data.
     * \param idx   Index of the byte.
     * \param data  Input data to write.
     */
    void writeByte(uint32_t idx, uint8_t data);
    /**
     * \brief This function write the bytes to the index of data.
     * \param idx   Index of the byte.
     * \param nbyte Number of the input byte.
     * \param data  Input data to write.
     * \return Whether the data was wrote successfuly.
     */
    bool writeBytes(uint32_t idx, uint32_t nbyte, std::vector<uint8_t> data);

    /**
     * \brief This function print the current bit to standard output.
     * \param lsb   Flag, specifying whether to read the least significant bit.
     */
    void printBit(bool lsb=false);

    /**
     * \brief This function return whether the current index is end of the data.
     * \return Whether the end of the data is read, namely no data is available.
     */
    bool eod();

private:

    std::vector<uint8_t> m_data;
    unsigned char m_buffer;
    unsigned int m_byteIndex;
    unsigned int m_bitIndex;
    bool isEnd = false;
};
