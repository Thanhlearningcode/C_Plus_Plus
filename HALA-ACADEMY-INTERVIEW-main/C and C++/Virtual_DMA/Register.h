#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <iostream>
#include <stdarg.h>
#include <string.h>

typedef enum
{
    CCR_OFFSET   = 0x0,
    CNDTR_OFFSET = 0x4,
    CPAR_OFFSET  = 0x8,
    CMAR_OFFSET  = 0xA,
}OffsetRegDMA;
struct BitInfo
{
    const char*  NameBit;   //! Name of bit 
    unsigned int BitStart;  //! Address start of bit
    unsigned int BitEnd;    //! Address end of bit
    unsigned int ValueBit;  //! Value of bit
    // Link to next bit
    BitInfo*     pNext;

    BitInfo();
    BitInfo(const char* _name, unsigned int _bit_start, unsigned int _bit_end, unsigned int _val);
    ~BitInfo();
};

class Register
{
friend class DMA_Register;
private:
    const char*  mNameReg;
    unsigned int mOffset;
    unsigned int mValue;
    BitInfo*     mBit;
private:
    void BindingFunction(Register* reg, unsigned int _num_bit, ...);
public:
    Register();
    Register(const char* _name, unsigned int _offset, unsigned int _value);
    void operator()(BitInfo* _bit);
    unsigned int operator[](const char* name_bit);
    ~Register();
};

class DMA_Register
{
private:
    Register* CCR;
    Register* CNDTR;
    Register* CPAR;
    Register* CMAR;

    unsigned int BitFilter(unsigned int val, unsigned int bit_start, unsigned int bit_end);
    void ShowInfoReg(Register* reg);
    void BitUpdate(Register* reg, unsigned int val);
public:
    DMA_Register();
    ~DMA_Register();
    void WriteRegister(unsigned int offset, unsigned int value);
    unsigned int ReadRegister(unsigned int offset);
    unsigned int ReadBit(unsigned int offset, const char* name_bit);
    virtual void DMA_Controller(void) = 0;
};
#endif //__REGISTER_H__