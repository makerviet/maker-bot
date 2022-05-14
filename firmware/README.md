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

- **Thư viện Adafruit PCA9685**: Thư viện PWM cho PCA9685, [link](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)
- **Thư viện tay PS2** : Sử dụng tay cầm PS2 với Makerbot [link](https://github.com/makerhanoi/Arduino-PS2X-ESP32-Makerbot)
- **Thư viện ESPUI** : sử dụng tạo giao diện webserver [link](https://github.com/s00500/ESPUI)
- **Thư viện AsyncTCP cho ESP32** : Thư viện đi kèm ESPUI [link](https://github.com/me-no-dev/AsyncTCP)
- **Thư viện Async Webserver cho ESP32** : Thư viện đi kèm ESPUI [link](https://github.com/me-no-dev/ESPAsyncWebServer)
- **Thư viện LITTLEFS cho ESP32** : Thư viện đi kèm ESPUI [link](https://github.com/lorol/LITTLEFS)
- **Thư viện ArduinoJson** : Thư viện đi kèm ESPUI [link](https://github.com/bblanchon/ArduinoJson)

## Sử dụng ví dụ Maker_bot_motor_test
Sau khi nạp ví dụ này chương trình mạch Makerbot sẽ phát ra một WIFI Access point tên là **"Makerbot BANHMI 01"**

Hai chữ số cuối của tên Access point có thể được thay đổi để tránh nhầm lẫn mạch giữa các đội tham gia

![](../images/wifi_scan.jpg) 
<!-- <img src="../images/wifi_scan.jpg" alt="drawing" width="200"/> -->

Kết nối với WiFi AP này không yêu cầu mật khẩu. 

Sau khi kết nối với Wifi ta sử dụng trình duyệt web, ta truy cập vào địa chỉ **192.168.1.1** hoặc **makerbot.io** để vào giao diện điều khiển động cơ.

**_Lưu ý:_** _đối với mạch Makerbot BANHMI bản 12V (Mạch VRC 2022) động cơ cần phải được cắm với nguồn điện 12V từ Pin Lipo hoặc adapter để có thể điều khiển được động cơ với ví dụ này_



Trên giao diện chính thấy có 2 tab