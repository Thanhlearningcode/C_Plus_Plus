Address sanitizer

1. Giới thiệu 

![image](https://github.com/user-attachments/assets/27282be8-eac8-4fb9-b283-8f3feecab141)

Các Thành Phần của Address sanitizer

![image](https://github.com/user-attachments/assets/f1878f9a-9627-45c9-990a-3a7d07e2da7e)

Shadown Memory

Shadow Memory là thành phần cốt lõi trong AddressSanitizer (ASan), được sử dụng để theo dõi trạng thái của bộ nhớ chính trong quá trình thực thi chương trình.

1 Granule = 8 bytes

![image](https://github.com/user-attachments/assets/f4286126-e429-48f6-afb5-07affdb166a1)

Các trạng thái của Shadown Memory :

1. **00 - Fully Addressable:**  
   - Toàn bộ 8 byte trong granule của bộ nhớ chính có thể truy cập an toàn.

2. **0N - Partially Addressable:**  
   - Chỉ có N byte trong 8 byte của granule hợp lệ; phần còn lại không hợp lệ.

3. **xx - Poisoned:**  
   - Toàn bộ granule không hợp lệ, có thể là lỗi hoặc các trạng thái của redzone.

4. **Trạng thái lỗi [f3]:**  
   - Biểu thị địa chỉ bị lỗi.

![image](https://github.com/user-attachments/assets/67c0ebdd-54f1-4e62-b865-b623b25908ef)

Dưới đây là nội dung trích xuất từ ảnh:

---

### **Redzone**  
Redzone là **vùng bộ nhớ đặc biệt** được AddressSanitizer (ASAN) tạo ra xung quanh vùng bộ nhớ hợp để **phát hiện các truy cập bộ nhớ trái phép**, như **buffer overflow** hoặc **underflow**.

### **Chức Năng của Redzone**  
- Bảo vệ các vùng bộ nhớ khỏi việc ghi đè ngoài phạm vi.  
- Được đánh dấu là "poisoned" (không hợp lệ) trong shadow memory.  
- Giúp ASAN phát hiện các lỗi bộ nhớ như:  
  - **Buffer Overflow:** Ghi đè vượt quá kích thước bộ nhớ được cấp phát.  
  - **Buffer Underflow:** Ghi đè vào vùng bộ nhớ nằm trước vùng được cấp phát.  
  - **Use-After-Free:** Truy cập vào bộ nhớ đã giải phóng.  

---

### **Các loại Redzone**  

| Tên                    | Mô Tả                                      | Shadow Byte |
|------------------------|------------------------------------------|-------------|
| **Stack Left Redzone**  | Bảo vệ vùng bên trái của stack frame.   | f1          |
| **Stack Mid Redzone**   | Bảo vệ khoảng trống giữa các biến.      | f2          |
| **Stack Right Redzone** | Bảo vệ vùng bên phải của stack frame.   | f3          |
| **Heap Left Redzone**   | Bảo vệ vùng trước bộ nhớ heap.          | fa          |
| **Heap Right Redzone**  | Bảo vệ vùng sau bộ nhớ heap.            | fa          |
| **Freed Heap Region**   | Đánh dấu bộ nhớ đã giải phóng.          | fd          |

Cách AddressSanitizer hoạt động
AddressSanitizer hoạt động dựa trên quy tắc thêm Shadow Memory và Instrumentation vào mã nguồn trong quá trình biên dịch.

![image](https://github.com/user-attachments/assets/804ee1ec-bfbd-4f88-b98c-e53aacb6ffa4)

Ảnh trên hướng dẫn cách sử dụng **AddressSanitizer (ASAN)** để phát hiện lỗi truy cập bộ nhớ trong C/C++ với **GCC**.

### **Hướng dẫn sử dụng AddressSanitizer**  

- **Yêu cầu hệ thống**:  
  - Trình biên dịch phải là **GCC** (hỗ trợ ASAN).  

- **Biên dịch chương trình với AddressSanitizer**:  
  - Sử dụng lệnh GCC sau:  
    ```bash
    gcc -fsanitize=address -g -o my_program my_program.c
    ```
  - **Giải thích lệnh**:
    - `-fsanitize=address`: Bật AddressSanitizer để phát hiện lỗi bộ nhớ.  
    - `-g`: Thêm thông tin debug để dễ dàng theo dõi lỗi.  
    - `-o my_program`: Tạo file thực thi có tên `my_program`.  
    - `my_program.c`: Tên file mã nguồn C cần biên dịch.  

📌 **Lưu ý**:  
- Khi chạy chương trình (`./my_program`), nếu có lỗi truy cập bộ nhớ, ASAN sẽ báo lỗi chi tiết, bao gồm loại lỗi, địa chỉ bộ nhớ lỗi, và stack trace.  
- AddressSanitizer tiêu tốn thêm tài nguyên (RAM, CPU) do cơ chế kiểm tra bộ nhớ.

  Demo

  Dưới đây là mã nguồn chi tiết cho cả hai chương trình **Stack-Buffer-Overflow** và **Heap-Buffer-Overflow**, kèm theo hướng dẫn biên dịch và chạy với **AddressSanitizer (ASAN)**.

---

## **1. Chương trình Stack-Buffer-Overflow**
📌 **Mô tả**:  
- Khai báo một mảng tĩnh `arr[3]`, nhưng cố truy cập `arr[4]`, gây lỗi **truy cập ngoài phạm vi bộ nhớ stack**.

📌 **Mã nguồn (stack_overflow.c)**:
```c
#include <stdio.h>

int main() {
    int arr[3] = {1, 2, 3}; // Mảng chỉ có 3 phần tử
    int i;

    // Truy cập hợp lệ vào mảng
    printf("Accessing array elements:\n");
    for (i = 0; i < 3; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Lỗi: Truy cập ngoài phạm vi mảng
    printf("\nAccessing out-of-bounds element:\n");
    printf("arr[4] = %d\n", arr[4]); // Lỗi xảy ra ở đây

    return 0;
}
```

📌 **Biên dịch & chạy với ASAN**:
```bash
gcc -fsanitize=address -g -o stack_overflow stack_overflow.c
./stack_overflow
```

📌 **Kết quả mong đợi**:
- AddressSanitizer sẽ báo lỗi **Stack-Buffer-Overflow** khi truy cập `arr[4]`.

---

## **2. Chương trình Heap-Buffer-Overflow**
📌 **Mô tả**:  
- Cấp phát động một mảng `arr` có 5 phần tử nhưng cố truy cập `arr[10]`, gây lỗi **truy cập ngoài phạm vi bộ nhớ heap**.

📌 **Mã nguồn (heap_overflow.c)**:
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Demo heap-buffer-overflow\n");

    // Cấp phát bộ nhớ động cho mảng 5 phần tử
    int *arr = (int *)malloc(5 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Gán giá trị hợp lệ cho mảng
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    // In các phần tử hợp lệ
    printf("Accessing valid elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Lỗi: Truy cập vượt quá phạm vi cấp phát
    printf("\nAccessing out-of-bounds element:\n");
    arr[10] = 100; // Lỗi Heap-Buffer-Overflow xảy ra ở đây

    // Giải phóng bộ nhớ
    free(arr);

    return 0;
}
```

📌 **Biên dịch & chạy với ASAN**:
```bash
gcc -fsanitize=address -g -o heap_overflow heap_overflow.c
./heap_overflow
```

📌 **Kết quả mong đợi**:
- AddressSanitizer sẽ báo lỗi **Heap-Buffer-Overflow** khi truy cập `arr[10]`.

---

## **Giải thích AddressSanitizer (ASAN)**
- **ASAN** giúp phát hiện lỗi truy cập bộ nhớ như **Buffer Overflow, Use-After-Free, Double-Free**.
- Khi chương trình chạy, ASAN sẽ **dừng ngay lập tức** nếu phát hiện lỗi, in ra báo cáo lỗi cùng vị trí cụ thể.

🔥 **Lưu ý**: AddressSanitizer chỉ hỗ trợ **GCC** và **Clang**. Nếu dùng trên **Windows**, hãy cài MinGW hoặc WSL để biên dịch.

### **Giải thích từng câu lệnh khi sử dụng AddressSanitizer (ASAN)**
---

## **1. Câu lệnh biên dịch với AddressSanitizer**
```bash
gcc -g -fsanitize=address -o asan_example asan.c
```
📌 **Giải thích từng phần:**
- `gcc` → Trình biên dịch GNU Compiler Collection.
- `-g` → Thêm thông tin debug để giúp AddressSanitizer hiển thị dòng lỗi chính xác hơn.
- `-fsanitize=address` → Kích hoạt **AddressSanitizer**, công cụ phát hiện lỗi bộ nhớ.
- `-o asan_example` → Đặt tên file thực thi là `asan_example`.
- `asan.c` → File mã nguồn chứa chương trình C.

✅ **Mục đích**: Biên dịch chương trình với AddressSanitizer để kiểm tra lỗi bộ nhớ trong quá trình chạy.

---

## **2. Chạy chương trình**
```bash
./asan_example
```
📌 **Giải thích**:
- `./asan_example` → Chạy chương trình đã biên dịch.
- Nếu chương trình có lỗi truy cập bộ nhớ, **AddressSanitizer sẽ phát hiện và hiển thị cảnh báo**.

---

## **3. Output khi chạy chương trình**
```
Accessing array elements:
arr[0] = 1
arr[1] = 2
arr[2] = 3

Accessing out-of-bounds element:
```
📌 **Giải thích**:
- Chương trình in ra các giá trị hợp lệ của mảng.
- Sau đó cố gắng truy cập **ngoài phạm vi mảng**, dẫn đến lỗi.

---

## **4. Lỗi AddressSanitizer phát hiện**
```
==4455==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffc0e7419c0 at pc 0x55fefa25f47e bp 0x7ffc0e741906 sp 0x7ffc0e741906
```
📌 **Giải thích**:
- `ERROR: AddressSanitizer: stack-buffer-overflow` → Lỗi **tràn bộ đệm trên stack**.
- `address 0x7ffc0e7419c0` → Địa chỉ bộ nhớ bị truy cập sai.
- `pc 0x55fefa25f47e` → Giá trị của **Program Counter**, chỉ vị trí lệnh gây lỗi.
- `bp 0x7ffc0e741906` → Base Pointer, chỉ địa chỉ đầu của stack frame.
- `sp 0x7ffc0e741906` → Stack Pointer, chỉ vị trí hiện tại của stack.

✅ **Mục đích**: Thông báo lỗi và vị trí xảy ra lỗi trong bộ nhớ.

---

## **5. Lệnh truy cập bộ nhớ sai**
```
READ of size 4 at 0x7ffc0e7419c0 thread T0
```
📌 **Giải thích**:
- `READ of size 4` → Chương trình cố đọc **4 byte** (tương ứng với kiểu `int`).
- `thread T0` → Lỗi xảy ra trong **thread chính (T0)**.

✅ **Mục đích**: Xác định lỗi do truy cập **ngoài phạm vi mảng** trên stack.

---

## **6. Truy vết lỗi (Backtrace)**
```
#0 0x55fefa25f47e in main /home/bbb/workspace/asan.c:15
#1 0x7f7094f3f082 in __libc_start_main ../csu/libc-start.c:308
#2 0x55fefa25f14d in _start (/home/bbb/workspace/asan_example+0x114d)
```
📌 **Giải thích**:
- **Dòng 15 trong `asan.c` gây lỗi**.
- **`__libc_start_main`** → Chương trình được gọi từ thư viện C chuẩn.
- **`_start`** → Điểm bắt đầu của chương trình.

✅ **Mục đích**: Xác định vị trí chính xác gây lỗi.

---

## **7. Thông tin biến bị lỗi**
```
Address 0x7ffc0e7419c0 is located in stack of thread T0 at offset 48 in frame
#0 0x55fefa25f278 in main /home/bbb/workspace/asan.c:3

This frame has 1 object(s):
[32, 44] 'arr' (line 4) <== Memory access at offset 48 overflows this variable
```
📌 **Giải thích**:
- **Biến `arr` được khai báo tại dòng 4**.
- **Vùng bộ nhớ hợp lệ của `arr` từ 32 đến 44**, nhưng chương trình cố đọc tại **địa chỉ 48**.

✅ **Mục đích**: Chỉ rõ biến nào bị truy cập sai.

---

## **8. Shadow Memory hiển thị lỗi**
```
0x100031cc2e0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
...
0x100031cc350: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 f3 f3
```
📌 **Giải thích**:
- `f3 f3` → Giá trị đặc biệt của **AddressSanitizer** để phát hiện truy cập ngoài phạm vi.

✅ **Mục đích**: Hiển thị vùng bộ nhớ lỗi.

---

## **Kết luận**
### **Câu lệnh quan trọng khi dùng ASAN**
| Câu lệnh | Chức năng |
|----------|------------|
| `-fsanitize=address` | Kích hoạt AddressSanitizer |
| `gcc -g` | Thêm debug symbols để ASAN hiển thị dòng lỗi chính xác |
| `./asan_example` | Chạy chương trình, nếu có lỗi, ASAN sẽ báo cáo |
| `READ of size 4` | Chương trình cố đọc 4 byte ngoài phạm vi |
| `stack-buffer-overflow` | Lỗi tràn bộ đệm trên stack |
| `Backtrace` | Hiển thị dòng gây lỗi trong chương trình |

✅ **ASAN giúp phát hiện lỗi bộ nhớ ngay khi chạy chương trình**, giúp lập trình viên dễ dàng sửa lỗi hơn!
