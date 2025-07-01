# Dino Egg Shooter - Game bắn trứng STM32

---

## Yêu cầu môi trường và công cụ

- **Bo mạch:** STM32F429I-DISCO  
- **STM32CubeIDE:** v1.14.0  
- **TouchGFX Designer:** v4.23.0  
- **ST-Link USB Driver:** phiên bản mới nhất  

---

## Hướng dẫn cài đặt chi tiết

1. **Cài đặt công cụ cần thiết:**
   - Tải và cài đặt **STM32CubeIDE v1.14.0** từ trang chính thức của ST:  
     https://www.st.com/en/development-tools/stm32cubeide.html
   - Tải và cài đặt **TouchGFX Designer v4.23.0** từ:  
     https://touchgfx.zendesk.com/
   - Cài đặt **ST-Link Driver** để máy tính nhận board STM32

2. **Clone mã nguồn dự án:**
   Mở Terminal (hoặc CMD), chạy:
   ```bash
   git clone https://github.com/Phamquangduc194518/dino-egg-shooter.git
   ```

3. **Mở dự án trong STM32CubeIDE:**
   - Mở TouchGFXProjects > chọn dự án vừa clone về
   - Chọn `MyApplication > STM32CubeIDE`
   - double click vào .project
   - Sau đó ứng dụng sẽ được mở ra

4. **Generate code với TouchGFX Designer:**
   - Vào thư mục `TouchGFX` trong project
   - Mở file `.touchgfx` bằng TouchGFX Designer
   - Nhấn **Generate Code** ở góc trên bên phải

5. **Build project và nạp vào board:**
   - Quay lại STM32CubeIDE
   - Click nút "Build" (búa) để biên dịch mã
   - Kết nối STM32F429I-DISCO bằng cáp USB
   - Click nút "Run" (mũi tên xanh) để flash chương trình vào board

6. **Chạy game:**
   - Sau khi nạp xong, board sẽ khởi động lại và vào game
   - Dùng màn hình cảm ứng để chơi
   - Điểm cao được lưu trong Flash (sector 11), không cần reset

---

## Link GitHub
[Dino Egg Shooter](https://github.com/Phamquangduc194518/dino-egg-shooter)
