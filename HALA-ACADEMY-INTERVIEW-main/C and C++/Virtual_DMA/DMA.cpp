#include "DMA.h"

/********************************************************
* @file DMA.cpp
* @brief Định nghĩa các phương thức điều khiển DMA và quản lý bộ nhớ.
* @version 1.0
* @date 2024-09-12
* @author Nguyễn Văn Thành
********************************************************/

DMA::DMA()
{
    mMemory = new unsigned char[SIZE_MEM]; // 64Kbytes
    std::fill(mMemory, mMemory + SIZE_MEM, 0); // Khởi tạo bộ nhớ với giá trị 0

    // SRC: Đặt giá trị 0xAA từ vị trí 16 đến 47
    for (unsigned int i = 16; i < 48; ++i)
    {
        mMemory[i] = 0xAA;
    }

    // DST: Đặt giá trị 0xFF từ vị trí 192 đến 223
    for (unsigned int i = 192; i < 224; ++i)
    {
        mMemory[i] = 0xFF;
    }
}

/// \brief Hủy DMA và giải phóng bộ nhớ.
DMA::~DMA()
{
    delete[] mMemory; // Sử dụng delete[] để giải phóng mảng động
}

/// \brief Ghi dữ liệu vào bộ nhớ thông qua DMA.
void DMA::Write(unsigned int addr, unsigned int data)
{
    this->WriteRegister(addr, data); // Ghi dữ liệu vào register
}

/// \brief Đọc dữ liệu từ bộ nhớ thông qua DMA.
unsigned int DMA::Read(unsigned int addr)
{
    return this->ReadRegister(addr); // Đọc dữ liệu từ register
}

/// \brief Hiển thị bộ nhớ của DMA.
void DMA::ShowMemory(void)
{
    std::cout << "-----------------------------------MEMORY-----------------------------------" << std::endl;
    uint32_t address = 0;
    uint32_t offset = 16;
    std::cout << "          ";

    // In các địa chỉ từ 0 đến 15
    for (unsigned int i = 0; i < 16; ++i)
    {
        printf("%0.2x ", i);
    }
    std::cout << std::endl;

    // In các dữ liệu bộ nhớ
    for (unsigned int i = 0; i < (SIZE_MEM / 16); ++i)
    {
        printf("%0.8x  ", address);
        for (unsigned int j = 0; j < 16; ++j)
        {
            printf("%0.2x ", mMemory[i * 16 + j]);
        }
        std::cout << std::endl;
        address += offset;
    }
}

/// \brief Điều khiển quá trình DMA.
void DMA::DMA_Controller(void)
{
    std::cout << "Start DMA ......................" << std::endl;
    
    unsigned char _dir   = this->ReadBit(CCR_OFFSET, "DIR");
    unsigned char _pnic  = this->ReadBit(CCR_OFFSET, "PINC");
    unsigned char _minc  = this->ReadBit(CCR_OFFSET, "MINC");
    unsigned char _psize = this->ReadBit(CCR_OFFSET, "PSIZE");
    unsigned char _msize = this->ReadBit(CCR_OFFSET, "MSIZE");
    unsigned char _m2m   = this->ReadBit(CCR_OFFSET, "MEM2MEM");
    unsigned int _size   = this->ReadBit(CNDTR_OFFSET, "NDT");
    unsigned int _src    = this->ReadBit(CPAR_OFFSET, "PA");
    unsigned int _dst    = this->ReadBit(CMAR_OFFSET, "MA");

    std::cout << "Source Address: " << _src << std::endl;
    std::cout << "Destination Address: " << _dst << std::endl;
    
    unsigned int srcIndex = 0;
    unsigned int dstIndex = 0;
    
    if (_dir == 0) // src to dst
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            *(mMemory + _dst + srcIndex) = *(mMemory + _src + dstIndex);
            if (_pnic != 0) 
            {
                ++srcIndex;
            }
            if (_minc != 0) 
            {
                ++dstIndex;
            }
        }
    }
    else // dst to src
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            *(mMemory + _src + i) = *(mMemory + _dst + i);
            if (_pnic != 0) 
            {
                ++srcIndex;
            }
            if (_minc != 0) 
            {
                ++dstIndex;
            }
        }
    }
}
