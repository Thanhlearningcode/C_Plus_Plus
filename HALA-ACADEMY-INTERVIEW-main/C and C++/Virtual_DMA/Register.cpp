#include "Register.h"

BitInfo::BitInfo()
{
    this->NameBit  = "";
    this->BitStart = 0;
    this->BitEnd   = 0;
    this->ValueBit = 0;
    this->pNext    = NULL;
}

BitInfo::BitInfo(const char* _name, unsigned int _bit_start, unsigned int _bit_end, unsigned int _val)
{
    this->NameBit  = _name;
    this->BitStart = _bit_start;
    this->BitEnd   = _bit_end;
    this->ValueBit = _val;
    this->pNext    = NULL;    
}

BitInfo::~BitInfo()
{
    //Nothing
}
//Default constructor
Register::Register()
{
    this->mNameReg = "";
    this->mOffset  = 0; 
    this->mValue   = 0;
    this->mBit     = NULL;
}
//Parameter constructor
Register::Register(const char* _name, unsigned int _offset, unsigned int _value)
{
    this->mNameReg = _name;
    this->mOffset  = _offset; 
    this->mValue   = _value;
    this->mBit     = NULL;
}
//Operator overloading to binding bit
void Register::operator()(BitInfo* _bit)
{
    if(this->mBit == NULL)
    {
        this->mBit = _bit;
    }
    else
    {
        BitInfo* tmp = this->mBit;
        while(tmp->pNext != NULL)
        {
            tmp = tmp->pNext;
        }
        tmp->pNext = _bit;
    }
}

void Register::BindingFunction(Register* reg, unsigned int _num_bit, ...)
{
    va_list args;
    va_start(args,_num_bit);
    for(unsigned int i=0;i<_num_bit;++i)
    {
        BitInfo* bit = va_arg(args,BitInfo*);
        (*reg)(bit);
    }
    va_end(args);
}

unsigned int Register::operator[](const char* name_bit)
{
    BitInfo* tmp = this->mBit;
    while(tmp != NULL)
    {
        if(0 == strcmp(name_bit,tmp->NameBit))
        {
            return tmp->ValueBit;
        }
        tmp = tmp->pNext;
    }
    std::cout<<"Bit "<<name_bit<<" did not found !" <<std::endl;
    return 0;
}

Register::~Register()
{
    //Nothing
}

DMA_Register::DMA_Register()
{
    //CCR
    static BitInfo EN("EN"          ,0,0,0);
    static BitInfo DIR("DIR"        ,4,4,0);
    static BitInfo PINC("PINC"      ,6,6,0);
    static BitInfo MINC("MINC"      ,7,7,0);
    static BitInfo PSIZE("PSIZE"    ,8,9,0);
    static BitInfo MSIZE("MSIZE"    ,10,11,0);
    static BitInfo MEM2MEM("MEM2MEM",14,14,0);
    CCR = new Register("CCR",0x0,0x0);
    CCR->BindingFunction(CCR,7,&EN,&DIR,&PINC,&MINC,&PSIZE,&MSIZE,&MEM2MEM);
    //CNDTR
    static BitInfo NDT("NDT"          ,0,15,0);
    CNDTR = new Register("CNDTR",0x4,0x0);
    CNDTR->BindingFunction(CNDTR,1,&NDT);
    //CPAR
    static BitInfo PA("PA"          ,0,31,0);
    CPAR = new Register("CPAR",0x8,0x0);
    CPAR->BindingFunction(CPAR,1,&PA);
    //CMAR
    static BitInfo MA("MA"          ,0,31,0);
    CMAR = new Register("CMAR",0xA,0x0);
    CMAR->BindingFunction(CMAR,1,&MA);
}

DMA_Register::~DMA_Register()
{
    delete CCR;
    delete CNDTR;
    delete CPAR;
    delete CMAR;
}

unsigned int DMA_Register::BitFilter(unsigned int val, unsigned int bit_start, unsigned int bit_end)
{
    val = val >> bit_start;
    unsigned int mask = ((unsigned long long)1 << (bit_end - bit_start + 1)) - 1;
    return val&mask;
}

void DMA_Register::ShowInfoReg(Register* reg)
{
    std::cout<<"REGISTER \""<<reg->mNameReg<<"\" = "<<"0x"<<std::hex<<reg->mValue<<std::endl;
    BitInfo* tmp = reg->mBit;
    while(tmp != NULL)
    {
        std::cout<<"["<<reg->mNameReg<<"]["<<tmp->NameBit<<"] = "<<"0x"<<std::hex<<tmp->ValueBit<<std::endl;
        tmp = tmp->pNext;
    }
}

void DMA_Register::BitUpdate(Register* reg, unsigned int val)
{
    reg->mValue = val;
    BitInfo* tmp = reg->mBit;
    while(tmp != NULL)
    {
        tmp->ValueBit = BitFilter(val,tmp->BitStart,tmp->BitEnd);
        tmp = tmp->pNext;
    }
}

void DMA_Register::WriteRegister(unsigned int offset, unsigned int value)
{
    std::cout<<"@@@@@@  Write register ["<<"0x"<<std::hex<<offset<<"] = "<<"0x"<<std::hex<<value<<"  @@@@@@"<<std::endl;
    switch (offset)
    {
    case 0x0:
        BitUpdate(CCR,value&0x4FD1);
        ShowInfoReg(CCR);
        if((*CCR)["EN"] == 1)
        {
            this->DMA_Controller();
        }
        break;
    case 0x4:
        BitUpdate(CNDTR,value&0xFFFF);
        ShowInfoReg(CNDTR);
        break;
    case 0x8:
        BitUpdate(CPAR,value&0xFFFFFFFF);
        ShowInfoReg(CPAR);
        break;
    case 0xA:
        BitUpdate(CMAR,value&0xFFFFFFFF);
        ShowInfoReg(CMAR);
        break;    
    default:
        std::cout<<"This register ["<<offset<<"] is not exist !"<<std::endl;
        break;
    }
}

unsigned int DMA_Register::ReadRegister(unsigned int offset)
{
    std::cout<<"@@@@@@  Read register ["<<"0x"<<std::hex<<offset<<"]   @@@@@@"<<std::endl;
    switch (offset)
    {
    case 0x0:
        ShowInfoReg(CCR);
        return CCR->mValue;
    case 0x4:
        ShowInfoReg(CNDTR);
        return CNDTR->mValue;
    case 0x8:
        ShowInfoReg(CPAR);
        return CPAR->mValue;
    case 0xA:
        ShowInfoReg(CMAR);
        return CMAR->mValue;  
    default:
        std::cout<<"This register ["<<offset<<"] is not exist !"<<std::endl;
        break;
    }
    return 0;
}

unsigned int DMA_Register::ReadBit(unsigned int offset, const char* name_bit)
{
    switch (offset)
    {
    case 0x0:
        return (*CCR)[name_bit];
    case 0x4:
        return (*CNDTR)[name_bit];
    case 0x8:
        return (*CPAR)[name_bit];
    case 0xA:
        return (*CMAR)[name_bit];
    default:
        std::cout<<"This register ["<<offset<<"] is not exist !"<<std::endl;
        break;
    }
    return 0;
}