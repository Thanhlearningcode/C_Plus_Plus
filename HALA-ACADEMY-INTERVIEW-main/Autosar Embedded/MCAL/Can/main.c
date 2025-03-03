#include "CanIf.h"
#include "Std_Types.h"
#include "CanIf_Types.h"
#include "Can_GeneralTypes.h"

// Định nghĩa cấu hình cho các CAN Controllers và PDUs
CanIf_PduConfigType pduConfigs[] = {
    { .PduId = 0x01, .PduLength = 8, .PduMode = CANIF_ONLINE },
    { .PduId = 0x02, .PduLength = 8, .PduMode = CANIF_OFFLINE }
};

CanIf_ControllerConfigType controllerConfigs[] = {
    { .ControllerId = 0, .BaudRateConfigID = 500, .DefaultPduMode = CANIF_ONLINE, .isConfigured = TRUE },
    { .ControllerId = 1, .BaudRateConfigID = 250, .DefaultPduMode = CANIF_TX_OFFLINE, .isConfigured = TRUE }
};

// Định nghĩa cấu hình tổng thể cho CAN Interface
CanIf_ConfigType canIfConfig = {
    .ControllerConfig = controllerConfigs,
    .NumControllers = 2,
    .PduConfig = pduConfigs,
    .NumPdus = 2,
    .NotifStatus = NULL // Có thể khởi tạo thêm nếu cần thiết
};

int main(void) {
    // Khởi tạo CAN Interface với cấu hình canIfConfig
    CanIf_Init(&canIfConfig);
    
    // Thay đổi chế độ hoạt động của CAN Controller 0 sang chế độ STARTED
    if (CanIf_SetControllerMode(0, CAN_CS_STARTED) == E_OK) {
        // Thành công trong việc thay đổi chế độ
    } else {
        // Xử lý lỗi khi thay đổi chế độ
    }

    // Thay đổi chế độ PDU cho Controller 1 sang TX_OFFLINE_ACTIVE
    CanIf_SetPduMode(1, CANIF_TX_OFFLINE_ACTIVE);

    // Gửi một PDU qua CAN Interface
    PduInfoType pduInfo = { .SduDataPtr = "ExampleData", .SduLength = 8 };
    if (CanIf_Transmit(0x01, &pduInfo) == E_OK) {
        // PDU truyền thành công
    } else {
        // Xử lý lỗi khi truyền PDU
    }

    // Hủy khởi tạo CAN Interface khi không cần sử dụng
    CanIf_DeInit();

    while (1) {
        // Vòng lặp chính của chương trình
    }

    return 0;
}
