#ifndef CORTEX_M3_H
#define CORTEX_M3_H

#include "APB_Bus.h"

/// \brief Lớp CortexM3 kế thừa từ APB_Master.
class CortexM3 : public APB_Master
{
public:
    /// \brief Hàm khởi tạo mặc định cho CortexM3.
    /// \details Khởi tạo đối tượng CortexM3, kế thừa từ APB_Master.
    CortexM3() = default;

    /// \brief Hàm hủy mặc định cho CortexM3.
    /// \details Không cần dọn dẹp đặc biệt cho CortexM3.
    ~CortexM3() = default;
};

#endif // CORTEX_M3_H
