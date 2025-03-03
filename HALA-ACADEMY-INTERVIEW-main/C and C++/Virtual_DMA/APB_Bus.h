#ifndef APB_BUS_H
#define APB_BUS_H

#include <iostream>

/// \brief Tiền khai báo lớp APB_Slaver cho lớp APB_Master.
class APB_Slaver;

/// \brief Lớp APB_Master đại diện cho APB Master.
class APB_Master
{
private:
    APB_Slaver* mSlaveObj; ///< Con trỏ đến đối tượng APB_Slaver.

public:
    /// \brief Hàm khởi tạo mặc định.
    /// \details Khởi tạo APB_Master và gán mSlaveObj là nullptr.
    APB_Master() : mSlaveObj(nullptr) {}

    /// \brief Hàm hủy mặc định.
    ~APB_Master() = default;

    /// \brief Ghi dữ liệu vào APB_Slaver.
    /// \param addr Địa chỉ cần ghi.
    /// \param data Dữ liệu cần ghi.
    void Write(uint32_t addr, uint32_t data);

    /// \brief Đọc dữ liệu từ APB_Slaver.
    /// \param addr Địa chỉ cần đọc.
    /// \return Dữ liệu đã đọc.
    uint32_t Read(uint32_t addr);

    /// \brief Kết nối Master với Slaver.
    /// \param obj Con trỏ tới APB_Slaver.
    void ConnectSlave(APB_Slaver* obj);
};

/// \brief Lớp trừu tượng APB_Slaver cho việc giao tiếp với các thiết bị Slave.
class APB_Slaver
{
public:
    /// \brief Hàm khởi tạo mặc định.
    APB_Slaver() = default;

    /// \brief Hàm hủy mặc định.
    virtual ~APB_Slaver() = default;

    /// \brief Ghi dữ liệu vào APB_Slaver.
    /// \param addr Địa chỉ cần ghi.
    /// \param data Dữ liệu cần ghi.
    virtual void Write(uint32_t addr, uint32_t data) = 0;

    /// \brief Đọc dữ liệu từ APB_Slaver.
    /// \param addr Địa chỉ cần đọc.
    /// \return Dữ liệu đã đọc.
    virtual uint32_t Read(uint32_t addr) = 0;
};

#endif // APB_BUS_H
