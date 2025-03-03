#ifndef __DMA_H__
#define __DMA_H__

#include "Register.h"
#include "APB_Bus.h"

#define SIZE_MEM 256
class DMA : public DMA_Register, public APB_Slaver
{
private:
    unsigned char* mMemory;
public:
    DMA();
    ~DMA();

    void Write(unsigned int addr, unsigned int data);
    unsigned int Read(unsigned int addr);
    void DMA_Controller(void);
    void ShowMemory(void);
};

#endif //__DMA_H__