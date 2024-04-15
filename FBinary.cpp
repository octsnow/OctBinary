#include <iostream>
#include <fstream>

#include "FBinary.hpp"

using namespace std;

namespace{
#if __cplusplus__ < 201703L
#include <sys/types.h>
#include <sys/stat.h>

bool checkFileExist(const string& filepath){
    struct stat buffer;
    return stat(filepath.c_str(), &buffer) == 0;
}

#else
#include <filesystem>

bool checkFileExist(const string& filepath){
    return std::filesystem::is_regular(filepath);
}
#endif
}

FBinary::FBinary(vector<uint8_t> data) : m_data(data){
    this->setByteIndex(0);
    this->setBitIndex(0);
}

FBinary::FBinary(const string filepath){
    this->loadFile(filepath);
}

bool FBinary::loadFile(string filepath){
    ifstream ifs(filepath, ios::in | ios::binary);
    ifs.unsetf(ios::skipws);

    if(!ifs){
        return false;
    }

    vector<uint8_t> buffer;
    streampos filesize;

    ifs.seekg(0, ios::end);
    filesize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    buffer.reserve(filesize);
    buffer.insert(buffer.begin(), istream_iterator<uint8_t>(ifs), istream_iterator<uint8_t>());

    ifs.close();

    this->setData(buffer);
    this->setByteIndex(0);
    this->setBitIndex(0);

    return true;
}

void FBinary::setData(vector<uint8_t> data){
    this->m_data = data;
    this->isEnd = false;
}

void FBinary::setCurrentBuffer(){
    this->m_buffer = this->m_data[this->m_byteIndex];
}

void FBinary::setByteIndex(uint32_t idx){
    if(idx < this->m_data.size()){
        this->m_byteIndex = idx;
        this->setCurrentBuffer();
    }
}

void FBinary::setBitIndex(uint32_t nbits){
    if(nbits < sizeof(this->m_buffer) * 8){
        this->m_bitIndex = nbits;
    }
}

void FBinary::setNextIndex(){
    this->m_byteIndex++;
    if(this->m_byteIndex < this->m_data.size()){
        this->setCurrentBuffer();
    }else{
        this->m_byteIndex--;
        this->isEnd = true;
    }
}

void FBinary::setNextBit(){
    this->m_bitIndex++;
    if(this->m_bitIndex >= sizeof(this->m_buffer) * 8){
        this->setBitIndex(0);
        this->setNextIndex();
    }
}

vector<uint8_t>* FBinary::getDataAdr(){
    return &this->m_data;
}

void FBinary::readBit(uint8_t* out, size_t size, bool lsb, bool isInt){
    int cb = 0;
    for(int i = 0; i < size; i++){
        int idx = isInt ? i : (size - i - 1);
        int tcb = (out[idx] & (1 << 7)) >> 7;
        out[idx] <<= 1;
        out[idx] |= cb;
        cb = tcb;
    }
    if(!isInt){
        out += size - 1;
    }
    if(lsb){
        *out |= (this->m_buffer & 1);
        this->m_buffer >>= 1;
    }else{
        *out |= (this->m_buffer >> (sizeof(this->m_buffer) * 8 - this->m_bitIndex - 1)) & 1;
    }
    this->setNextBit();
}

void FBinary::readBits(uint32_t nbit, uint8_t* out, size_t size, bool reverse, bool lsb, bool isInt){
    if(nbit == 0) return;
    if(nbit > size * 8){
        cerr << "nbit > size * 8." << endl;
        return;
    }

    this->readBit(out, size, lsb, isInt);
    this->readBits(nbit - 1, out, size, false, lsb, isInt);

    if(reverse){
        for(int i = 0; i < nbit / 2; i++){
            int bi = ((i - nbit % 8) + 8) / 8;
            int nim = (nbit - i - 1) / 8; // n index most;
            int nsm = (nbit - i - 1) % 8; // n shift most;
            int nil = i / 8; // n index least;
            int nsl = i % 8; // n shift least;
            int tmp = (out[nim] & (1 << nsm)) >> nsm;
            out[nim] = (out[nim] & ~(1 << nsm)) | (((out[nil] & (1 << nsl)) >> nsl) << nsm);
            out[nil] = (out[nil] & ~(1 << nsl)) | (tmp << nsl);
        }
    }
}

void FBinary::readByte(uint8_t* out, size_t size, bool reverse, bool lsb, bool isInt){
    this->readBits(8, out, size, reverse, lsb, isInt);
}

void FBinary::readBytes(uint32_t nbyte, uint8_t* out, size_t size, bool reverse, bool lsb, bool isInt){
    this->readBits(nbyte * 8, out, size, reverse, lsb, isInt);
}

void FBinary::writeByte(uint32_t idx, uint8_t data){
    if(idx < this->m_data.size()){
        this->m_data[idx] = data;
    }
}

bool FBinary::writeBytes(uint32_t idx, uint32_t nbyte, vector<uint8_t> data){
    if(nbyte >= data.size()){
        cerr << "FBinary::writeBytes(): nbyte >= data.size()." << endl;
        return false;
    }
    for(int i = 0; i < nbyte; i++){
        uint8_t _data = data[i];
        this->writeByte(idx + i, _data);
    }

    return true;
}

void FBinary::printBit(bool lsb){
    if(lsb){
        cout << (int)(this->m_buffer & 1) << " ";
    }else{
        cout << (int)((this->m_buffer >> (sizeof(this->m_buffer) * 8 - this->m_bitIndex - 1)) & 1) << " ";
    }
}

bool FBinary::eod(){
    return this->isEnd;
}

