/*
* File: main.cpp
* Author: Nguyễn Văn Thành
* Date: 10/02/2024
* Description: This file demonstrates the use of DMA and CortexM3, including setting up DMA registers and displaying memory.
*/

#include "DMA.h"
#include "CortexM3.h"

int main(int argc, char* argv[])
{
    // Create DMA and CortexM3 objects
    DMA* DMA_Block = new DMA();
    CortexM3* Core = new CortexM3();

    // Set up DMA with CortexM3
    (*Core)(DMA_Block);

    // Display the initial memory state
    DMA_Block->ShowMemory();

    // Write DMA registers using CortexM3 core
    Core->Write(CNDTR_OFFSET, 32);  // Set transfer data register
    Core->Write(CPAR_OFFSET, 0x10); // Set peripheral address register
    Core->Write(CMAR_OFFSET, 0x70); // Set memory address register
    Core->Write(CCR_OFFSET, 0xC1);  // Set control register

    // Display the updated memory state
    DMA_Block->ShowMemory();

    // Clean up memory
    delete DMA_Block;
    delete Core;

    return 0;
}
