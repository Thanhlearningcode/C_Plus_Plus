#include "APB_Bus.h"

/// \brief Represents the APB Master class for interacting with an APB Slaver.
/// \author Nguyen Van Thanh
class APB_Master
{
private:
    APB_Slaver* mSlaveObj = nullptr; ///< Pointer to the connected slave object.

public:
    /// \brief Connects the master to a slave object.
    /// \param obj Pointer to the slave object to be connected.
    void operator()(APB_Slaver* obj);

    /// \brief Writes data to a specified address on the connected slave.
    /// \param addr Address to write the data to.
    /// \param data Data to be written.
    void Write(unsigned int addr, unsigned int data);

    /// \brief Reads data from a specified address on the connected slave.
    /// \param addr Address to read data from.
    /// \return The data read from the specified address, or a default value if no slave is connected.
    unsigned int Read(unsigned int addr);
};

/// \brief Default value returned when no slave is connected.
constexpr unsigned int DEFAULT_READ_VALUE = 0;

void APB_Master::operator()(APB_Slaver* obj)
{
    mSlaveObj = obj;
}

void APB_Master::Write(unsigned int addr, unsigned int data)
{
    if (mSlaveObj != nullptr)
    {
        mSlaveObj->Write(addr, data);
    }
    else
    {
        std::cerr << "Error: The master is not connected to any slave!" << std::endl;
    }
}

unsigned int APB_Master::Read(unsigned int addr)
{
    if (mSlaveObj != nullptr)
    {
        return mSlaveObj->Read(addr);
    }
    std::cerr << "Error: The master is not connected to any slave!" << std::endl;
    return DEFAULT_READ_VALUE;
}
