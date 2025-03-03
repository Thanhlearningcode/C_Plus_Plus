![image](https://github.com/user-attachments/assets/14a37cb3-0ef9-4c93-bccc-3f577f445bbb)


**Bash là gì**  
+ Bash là viết tắt của Born Again Shell.  
+ Bash dựa trên shell cũ hơn nhiều gọi là The Bourne Shell, hay SH, được tạo bởi Stephen  
+ Shell Bash là shell được sử dụng phổ biến nhất và do tính đa dạng của các hệ thống Linux  
+ Bằng cách viết kịch bản cho chương trình hay nhất, bạn có thể khá tự tin rằng kịch bản của mình sẽ hiệu quả khi bạn **chuyển nó sang các máy khác, điều này có thể giúp bạn tiết kiệm rất nhiều công việc.**
+ Shell đọc tập lệnh và thực thi từng lệnh một, như thế ta đã nhập chúng vào lệnh  
+ **Do đó, một tập lệnh bash chỉ đơn giản là một tập lệnh được viết cho shell.**  
+ Viết kịch bản cho phép tự động hóa.

**Kịch bản**  
+ Một kịch bản gồm 3 phần: Mở đầu, phần giữa và phần cuối  

```
#!/bin/bash

echo "Hello VanThanh"
exit 0
```

+ Dòng đầu cho biết Shell sử dụng trình thông dịch nào để đọc  
+ Phải có 1 dòng cách ra giữa dòng đầu vào code  
+ Ghi `exit 0` là thành công, còn từ `1-255` là không thành công  
+ `chmod +x name_file`: Cấp quyền thực thi

**Quyền**  
+ `chmod 744 Name_file`  
+ `chmod o+r test.txt`: thêm quyền read.  
+ `chmod u-r test.txt`: bỏ quyền read.  

Hình minh họa cho quyền trong Linux:  
- **Owner**: Read ✅, Write ✅, Execute ✅  
- **Group**: Read ✅, Write ❌, Execute ❌  
- **Public**: Read ✅, Write ❌, Execute ❌  

Trang web tham khảo: [https://chmod-calculator.com/](https://chmod-calculator.com/)

**PATH**  
+ Bình thường ta muốn chạy lệnh thì phải vào folder đó để cmd  
+ Giờ có cách nào để bất kể chỗ nào cũng chạy được không  
+ Khi ta gõ lệnh thì Shell sẽ chạy tất cả folder trong PATH để xem có lệnh nào như vậy không để chạy, gặp cái đầu tiên nó sẽ chạy luôn  
+ Xem Path: `echo "$PATH"`

+ **Thêm tạm thời**, khi tắt máy bật lại thì mất  
  ```bash
  Export PATH=$PATH:/home/thonv12/Desktop/bash_shell
  ```

+ **Thêm trọn đời**  
  ```bash
  vim ~/.profile
  ```
  - Thêm dòng sau vào file `.profile`:  
    ```bash
    export PATH="$PATH:$HOME/Desktop/bash_shell"
    ```
  - Lưu thay đổi bằng lệnh:  
    ```bash
    source ~/.profile
    ```

+ **Cách hoạt động của PATH**  
  - Khi gõ lệnh, Shell sẽ tìm trong các thư mục trong PATH theo thứ tự từ trên xuống dưới. Gặp lệnh nào đầu tiên, nó sẽ chạy luôn.  
  - Nếu muốn ưu tiên thư mục của mình trước, hãy thêm đường dẫn vào **đầu** PATH:  
    ```bash
    export PATH=your_directory:$PATH
    ```
  - Nếu không cần ưu tiên, thêm vào **sau** PATH như bình thường.

### **Variables**  
+ **Các biến có sẵn trong shell:**  
  - `PATH`  
  - `HOME`  
  - `HOSTNAME`  
  - `PS1`: Là biến quy định giao diện của dòng nhắc lệnh (prompt).  

+ **Chỉnh sửa PS1 để thay đổi giao diện prompt:**  
  ```bash
  PS1="Ghi vào đây"
  ```
  Bạn có thể vào [ezprompt.net](https://ezprompt.net/) để tạo prompt tùy chỉnh.  

+ **Quay lại prompt mặc định:**  
  ```bash
  source ~/.bashrc
  ```
### **Command identification (Nhận dạng lệnh)**  
+ Shell chia các command thành **lệnh đơn giản** hoặc **lệnh ghép**.  
+ **Lệnh đơn giản**: ví dụ `echo`  
+ **Lệnh phức tạp**: như `if`, `while`...  
+ **Tất cả các lệnh đơn giản đều kết thúc bằng một toán tử điều khiển**  

#### **Các toán tử điều khiển**:  
- `newline`  
- `|`  
- `||`  
- `&`  
- `&&`  
- `;`  
- `;;`  
- `;&`  
- `;;&`  
- `|&`  
- `(`  
- `)`  

Ví dụ:  
```bash
echo 1 2 3; echo a b c
```  
Sẽ in ra:  
```
1 2 3  
a b c  
```

### **Shell Expansions - Mở rộng câu lệnh trong Shell**  
Shell hỗ trợ mở rộng câu lệnh thông qua **bốn giai đoạn** chính:  

1. **Brace expansion**: `{1..3}` sẽ mở rộng thành `1 2 3`.  
2. **Include**: Bao gồm các loại mở rộng như **biến số (parameter), số học (arithmetic), thay thế lệnh (command substitution)**.  
3. **Word splitting**: Tách chuỗi thành các từ riêng biệt dựa trên dấu cách.  
4. **Globbing**: Dùng ký tự đại diện (`*`, `?`, `[]`) để tìm kiếm tệp.  

Ví dụ:  
```bash
name=Thanh
echo $name có {1..3} quả táo và $((1+2)) quả lê
```
Kết quả:  
```
Thanh có 1 2 3 quả táo và 3 quả lê
```  

🔹 **Globbing**: Ví dụ tìm tệp có dạng `????.doc`  
```bash
ls -l chăn????.doc
```  
Tìm tất cả các tệp có tên dài 8 ký tự, bắt đầu bằng `chăn` và kết thúc bằng `.doc`.

### **Word Splitting - Tách từ trong Shell**  

#### **Khái niệm**  
- Trong Bash, **Word Splitting** là quá trình tách một chuỗi thành các từ riêng lẻ dựa trên các ký tự phân tách.  
- Các ký tự này được lưu trong biến **IFS (Internal Field Separator)**.  
- Mặc định, IFS chứa **dấu cách (space), tab (`\t`), và xuống dòng (`\n`)**.  

#### **Ví dụ**  
1. **Mặc định IFS**  
   ```bash
   numbers="1 2 3 4"
   touch $numbers
   ls
   ```
   🔹 Các tệp `1`, `2`, `3`, `4` được tạo vì mặc định IFS là dấu cách.  

2. **Dùng dấu phẩy làm dấu phân tách**  
   ```bash
   numbers="1,2,3,4"
   touch $numbers
   ls
   ```
   🔹 Chỉ tạo **một tệp duy nhất** có tên `1,2,3,4` vì dấu phẩy không nằm trong IFS.  

3. **Thay đổi IFS thành dấu phẩy (`IFS=","`)**  
   ```bash
   IFS=","
   numbers="1,2,3,4"
   touch $numbers
   ls
   ```
   🔹 Lần này, `IFS` đã thay đổi nên các tệp `1`, `2`, `3`, `4` được tạo riêng lẻ.  

#### **Kiểm tra giá trị của IFS**  
```bash
echo "${IFS@Q}"
```
🔹 Hiển thị nội dung của IFS (`$' \t\n'` tương ứng với dấu cách, tab, xuống dòng).

### **Globbing - Mở rộng tên tệp trong Shell**  

#### **Khái niệm**  
- **Globbing** là quá trình mở rộng mẫu ký tự đại diện (**wildcards**) để tìm kiếm hoặc thao tác với nhiều tệp cùng lúc.  
- Bash sẽ thay thế các ký tự đại diện thành danh sách các tệp phù hợp.  

#### **Các ký tự đại diện phổ biến**  
| Ký tự | Ý nghĩa | Ví dụ | Kết quả |
|-------|--------|------|---------|
| `*` | Đại diện cho **bất kỳ số lượng ký tự nào** | `ls *.txt` | Liệt kê tất cả tệp `.txt` |
| `?` | Đại diện cho **một ký tự bất kỳ** | `ls file?.txt` | Liệt kê `file1.txt`, `fileA.txt`, nhưng không có `file12.txt` |
| `[...]` | Đại diện cho **một ký tự trong danh sách** | `ls file[0-9].txt` | Liệt kê `file1.txt`, `file2.txt`, nhưng không có `fileA.txt` |
| `{a,b,c}` | Chọn **một trong các giá trị** | `ls {file1,file2}.txt` | Chỉ liệt kê `file1.txt` và `file2.txt` |
| `???` | Ba ký tự bất kỳ | `ls ???.txt` | Liệt kê các tệp có tên đúng 3 ký tự + `.txt` |

#### **Ví dụ thực tế**  
1. **Liệt kê tất cả các tệp `.txt` trong thư mục**  
   ```bash
   ls *.txt
   ```

2. **Tìm các tệp có tên bắt đầu bằng "file" và theo sau là một số từ 0-9**  
   ```bash
   ls file[0-9].txt
   ```

3. **Tìm tệp có tên dài 8 ký tự, bắt đầu bằng "f, o, o, t" và kết thúc bằng ".doc"**  
   ```bash
   ls chân????.doc
   ```
   - Ví dụ này tìm kiếm tệp có tên như `football.doc` (như trong ảnh).

  ### **Loại bỏ ký tự đặc biệt - Trích dẫn (Quoting) trong Shell**  

#### **Mục đích**  
Trích dẫn trong Shell giúp **loại bỏ ý nghĩa đặc biệt** của một số ký tự, tránh lỗi cú pháp hoặc thay đổi hành vi của lệnh.  

#### **Các cách trích dẫn**  

| Cách | Ý nghĩa | Ví dụ | Kết quả |
|------|--------|------|---------|
| **Dấu gạch chéo ngược (`\`)** | Bỏ ý nghĩa đặc biệt của một ký tự ngay sau nó | `echo \$HOME` | `$HOME` (không bị thay thế) |
| **Dấu nháy đơn (`' '`)** | Bỏ ý nghĩa đặc biệt của toàn bộ nội dung bên trong | `echo '$HOME'` | `$HOME` (hiển thị đúng chuỗi) |
| **Dấu nháy kép (`" "`)** | Giữ nguyên hầu hết ký tự nhưng vẫn cho phép thay thế biến | `echo "$HOME"` | `/home/user` |

#### **Ví dụ thực tế**  

1. **Dùng `\` để escape ký tự đặc biệt**  
   ```bash
   echo So1 \& So2
   ```
   - Hiển thị: `So1 & So2` (thay vì chạy nền tiến trình).  

2. **Dùng nháy đơn `' '` để giữ nguyên nội dung**  
   ```bash
   path='D:\Code\ThonNV'
   echo $path
   ```
   - Kết quả: `D:\Code\ThonNV` (không bị Shell xử lý thêm).  

3. **Dùng nháy kép `" "` để thay thế biến**  
   ```bash
   path="D:\Code\$USER"
   echo $path
   ```
   - Nếu `$USER = thon12`, kết quả: `D:\Code\thon12`.  

Trích dẫn giúp tránh lỗi cú pháp, bảo toàn dữ liệu đầu vào, và kiểm soát cách Shell xử lý ký tự đặc biệt.

### **Ví dụ về chuyển hướng đầu ra trong Shell**  

#### **Câu lệnh mẫu**  
```bash
name="Tho"
out="out.txt"
echo $name > $out
```
- **Giải thích:**  
  - Biến `name` chứa giá trị `"Tho"`.  
  - Biến `out` chứa tên file `"out.txt"`.  
  - `echo $name > $out`: Lệnh `echo` in giá trị biến `name` và chuyển hướng (`>`) vào file `out.txt`.

#### **Các bước xử lý**  

1. **Tìm từ (Word) và toán tử**  
   - `echo`: Lệnh shell.  
   - `$name`: Biến shell.  
   - `>`: Toán tử chuyển hướng.  
   - `$out`: Biến shell (tên file).  

2. **Nhận dạng command**  
   - Xác định đây là lệnh `echo`, có biến `$name` và sử dụng chuyển hướng `>` để ghi vào file.  

3. **Mở rộng (Expansion)**  
   - `$name` → `Tho`.  
   - `$out` → `out.txt`.  
   - Sau khi mở rộng, lệnh thực sự là:  
     ```bash
     echo Tho > out.txt
     ```  

4. **Remove Quote (Bỏ dấu nháy nếu có)**  
   - Không có dấu nháy nên không cần xử lý thêm.  

5. **Chuyển hướng (Redirection)**  
   - **stdout (tiêu chuẩn đầu ra)** bị chuyển vào file `out.txt`.  
   - Nội dung file `out.txt` sau khi thực thi lệnh:
     ```
     Tho
     ```
   - Có một ký tự **newline ở cuối dòng**, nhưng bị ẩn.  

#### **Minh họa quá trình**
- **Lệnh `echo Tho`** → Gửi kết quả vào **stdout** (màn hình).  
- **Dấu `>` chuyển hướng stdout** → Ghi nội dung vào file `out.txt`.
