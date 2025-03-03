# GPIO REGISTER
================

## 1. Tạo Project KeliC

Để bắt đầu, bạn cần tạo một project trong KeliC hoặc IDE mà bạn đang sử dụng cho lập trình vi điều khiển (MCU). Sau khi tạo project, bạn có thể viết các chương trình liên quan đến cấu hình và thao tác với GPIO, ngắt và Timer.

## 2. Viết chương trình liên quan đến thanh ghi GPIO

Mọi hoạt động trong vi điều khiển (MCU) đều phụ thuộc vào **xung Clock**. Để GPIO hoạt động, chúng ta cần cấp xung Clock cho các ngoại vi GPIO.

### Cấp xung Clock cho GPIO

- **GPIOC** sử dụng đường bus **APB2** (Advanced Peripheral Bus 2) để nhận xung Clock. Để cấu hình cho GPIOC hoạt động, ta cần cấu hình xung Clock cho **Port C** thông qua thanh ghi của đường bus **APB2**.
- Việc cấp xung Clock là rất quan trọng, vì nếu không cấp Clock, các chân GPIO không thể hoạt động.

### Cấu hình chân GPIO

- **GPIO** có rất nhiều chân (pins), và mỗi chân có thể được cấu hình cho một mục đích sử dụng khác nhau. Chúng ta cần chỉ định các chân sẽ sử dụng cho chức năng đầu vào hoặc đầu ra.
- Có hai chế độ chính cho GPIO:
  + **Input Mode**: Dùng để nhận tín hiệu vào từ các thiết bị khác.
    - **Analog Mode**: Chân GPIO nhận tín hiệu analog, thường sử dụng cho các cảm biến hoặc tín hiệu điều khiển.
    - **Floating Input**: Chân không có điện áp xác định, có thể thả nổi ở mức giữa 0V và 3.3V. Không xác định mức logic.
    - **Input with Pull-up/Pull-down**: Chân đầu vào có thể được kéo lên (Pull-up) hoặc kéo xuống (Pull-down), giúp đảm bảo mức tín hiệu ổn định (3.3V hoặc 0V).
  
  + **Output Mode**: Dùng để xuất tín hiệu từ MCU ra ngoài.
    - **General Purpose Output Push-Pull**: Tín hiệu xuất ra có thể là 3.3V (HIGH) hoặc 0V (LOW), và có thể đẩy (push) hoặc kéo (pull) dòng điện. Thường dùng cho việc điều khiển các thiết bị như LED, động cơ, v.v.
    - **Open-drain Output**: Output kiểu mở (có thể kết nối chung với nguồn 3.3V hoặc GND).

---

# NGẮT VÀ TIMER
================

## 1. Ngắt (Interrupt)

Ngắt là cơ chế cho phép MCU tạm dừng chương trình hiện tại và chuyển sang xử lý sự kiện khẩn cấp. Sau khi ngắt hoàn tất, chương trình sẽ quay lại tiếp tục thực hiện phần còn lại.

### Cơ chế ngắt

Khi có ngắt xảy ra, **Program Counter (PC)** sẽ thay đổi để trỏ đến **Vector Table** (bảng địa chỉ ngắt). Việc này giúp MCU biết được vị trí mã lệnh để xử lý ngắt.

#### Các loại ngắt:

- **Reset**: Là ngắt hệ thống, dùng để khởi động lại MCU khi gặp sự cố.
- **Ngắt ngoài**: Xảy ra khi có thay đổi trạng thái ở các chân GPIO.
- **Ngắt Timer**: Xảy ra khi bộ đếm Timer tràn.
- **Ngắt truyền thông**: Xảy ra khi có sự kiện truyền nhận dữ liệu giữa các thiết bị.

### Các loại ngắt ngoài

- **LOW**: Ngắt kích hoạt khi chân GPIO có điện áp thấp (0V).
- **HIGH**: Ngắt kích hoạt khi chân GPIO có điện áp cao.
- **Rising Edge**: Ngắt kích hoạt khi điện áp thay đổi từ thấp lên cao (0V -> 3.3V).
- **Falling Edge**: Ngắt kích hoạt khi điện áp thay đổi từ cao xuống thấp (3.3V -> 0V).

### Ngắt Timer

- **Timer** là bộ đếm có thể đếm lên hoặc đếm xuống sau mỗi chu kỳ xung. Khi giá trị của Timer tràn (overflow), một ngắt Timer sẽ được kích hoạt.
- Ví dụ, nếu chúng ta cấu hình Timer đếm sau mỗi 1ms và sau 200ms giá trị tràn, khi đó ngắt sẽ được kích hoạt mỗi khi Timer tràn.

### Ngắt truyền thông

- **Ngắt truyền thông** xảy ra khi có sự truyền nhận dữ liệu giữa vi điều khiển và các thiết bị ngoại vi. Mục đích của ngắt này là để đảm bảo việc truyền nhận dữ liệu chính xác mà không bị mất mát.

### Độ ưu tiên ngắt

- Các ngắt có thể có độ ưu tiên khác nhau. Việc này giúp xác định thứ tự xử lý khi có nhiều ngắt xảy ra cùng lúc. Ngắt có độ ưu tiên cao sẽ được xử lý trước.

---

# CÁC CHUẨN GIAO TIẾP
====================

## 1. Truyền nhận dữ liệu

Trong giao tiếp giữa các vi điều khiển (MCU), tín hiệu điện áp được sử dụng để biểu diễn các bit:
- **0V** biểu thị bit 0.
- **3.3V (hoặc 5V)** biểu thị bit 1.

Các vi điều khiển sẽ truyền một chuỗi các bit thông qua các chân GPIO, các chuẩn giao tiếp sẽ giúp MCU phân biệt được các bit liên tiếp trong chuỗi.

## 2. SPI (Serial Peripheral Interface)

**SPI** là một chuẩn giao tiếp nối tiếp đồng bộ, cho phép truyền và nhận dữ liệu đồng thời (song công) giữa một Master và nhiều Slave.

### Cấu trúc giao tiếp SPI

- **SCK (Serial Clock)**: Dây xung đồng hồ, do Master tạo ra.
- **MOSI (Master Out Slave In)**: Dây truyền dữ liệu từ Master đến Slave.
- **MISO (Master In Slave Out)**: Dây truyền dữ liệu từ Slave đến Master.
- **SS (Slave Select)**: Dây chọn Slave, giúp Master chỉ định Slave nào sẽ nhận hoặc gửi dữ liệu.

### Các chế độ hoạt động của SPI:

SPI có 4 chế độ hoạt động dựa trên các bit **CPOL** (Clock Polarity) và **CPHA** (Clock Phase):
- **CPOL** xác định mức điện áp của SCK khi không có tín hiệu.
- **CPHA** xác định thời điểm mà dữ liệu được truyền trong mỗi chu kỳ clock.

---

## 3. I2C (Inter-Integrated Circuit)

**I2C** là chuẩn giao tiếp nối tiếp đồng bộ sử dụng 2 dây **SDA** (Data) và **SCL** (Clock). I2C hỗ trợ một Master và nhiều Slave.

### Cấu trúc giao tiếp I2C

- **SDA**: Dây dữ liệu, truyền thông qua giao tiếp 2 chiều.
- **SCL**: Dây xung đồng hồ, do Master điều khiển.
- Địa chỉ của các Slave được truyền trong quá trình giao tiếp I2C. Mỗi Slave có một địa chỉ duy nhất.
  
I2C sử dụng **Start condition** để bắt đầu một giao tiếp, và **Stop condition** để kết thúc.

---

## 4. UART (Universal Asynchronous Receiver Transmitter)

**UART** là giao thức truyền thông nối tiếp không đồng bộ, sử dụng 2 dây **RX** (nhận) và **TX** (truyền). Không có dây Clock, thay vào đó, UART sử dụng một bộ hẹn giờ (timer) để đồng bộ hóa việc truyền và nhận dữ liệu.

### Cấu trúc giao tiếp UART

- **Start bit**: Được truyền khi bắt đầu một frame dữ liệu.
- **Data bits**: Thường có 5 đến 9 bits dữ liệu.
- **Parity bit**: Được sử dụng để kiểm tra lỗi trong dữ liệu.
- **Stop bit**: Được sử dụng để đánh dấu sự kết thúc của một frame dữ liệu.

### Data Frame trong UART:
1. **Start bit**: 1 bit, có giá trị 0.
2. **Data bits**: 5-9 bits dữ liệu.
3. **Parity bit**: 1 bit (tùy chọn).
4. **Stop bit**: 1-2 bits (tùy chọn).

---

### Lời kết

Đây là những kiến thức cơ bản về GPIO, ngắt, Timer và các chuẩn giao tiếp trong hệ thống nhúng. Việc hiểu rõ các khái niệm này là cơ sở để lập trình hiệu quả và tối ưu cho các dự án sử dụng vi điều khiển. Càng nắm vững các cơ chế hoạt động và cách cấu hình chúng, bạn sẽ càng dễ dàng phát triển các ứng dụng nhúng phức tạp hơn trong tương lai.

---

# README
