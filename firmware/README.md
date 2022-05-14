# Hướng dẫn sử dụng các ví dụ phần mềm
## Giới thiệu 
Trên đây là những ví dụ đề kiểm tra, thử nhiệm các tính năng hoạt động của mạch Makerbot, bao gồm:
- Maker_bot_motor_test: ví dụ điều khiển động cơ DC và Servo
- MakerbotwPS2: ví dụ điều khiển động cơ DC bằng tay cầm PS2 (xe điều khiển 3 bánh)

## Cài đặt trình biên dịch
### Sử dụng Arduino IDE
Các bạn có thể download và cài đặt Arduino IDE [tại đây](https://www.arduino.cc/en/software)

Cài đặt ESP32 trên Arduino, hướng dẫn [tại đây](../docs/Tutorial_Docs/Cài-đặt-thư-viện-ESP32-trên-Arduino-IDE.pdf) 

### Sử dụng Platform IO
Để sử dụng Platform IO các bạn cần 1 code editor, BTC recommend sử dụng VScode, có thể tải [tại đây](https://code.visualstudio.com/download) 

## Thư viện cần thiết

Để tiện lợi cho các mentor và các bạn thí sinh dưới đây là tổng hợp toàn bộ các thư viện cần thiết, [tại đây](https://rogosmart-my.sharepoint.com/:u:/g/personal/tu_danganh_rogo_com_vn/ESJKm2XPhw9Hl89-lLPU8d4B54ctBPSGGFCmoeG4xCfOxw?e=gbFQdg)  


Giải nén file nén trên tới Thư mục: **Document > Arduino > libraries** 

![](../images/library_window.PNG) 

Ngoài ra các bạn có thể cài theo cách thủ công từng thư viện, dưới đây là chi tiết các thư viện cần thiết để chạy các chương trình ví dụ trên.

- Thư viện Adafruit PCA9685: thư viện PWM cho PCA9685, [link](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)
