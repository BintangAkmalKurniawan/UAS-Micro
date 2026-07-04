Link Video Penjelasan:
https://youtu.be/exp0aNJhhoU?si=KeMQ5Nq8ueTS2viv

Sistem Deteksi Banjir IoT (ESP32 + Supabase)

Sistem Deteksi Banjir IoT adalah platform pemantauan ketinggian air cerdas yang dirancang untuk memberikan peringatan dini secara lokal dan pemantauan data secara real-time via dashboard web. Sistem ini mengintegrasikan pengolahan data lokal, logika cloud, dan visualisasi data yang responsif.

🛠️ Komponen Perangkat Keras

Sistem ini dibangun dengan komponen yang terjangkau namun andal:

- ESP32 (Microcontroller): Otak sistem yang dilengkapi WiFi terintegrasi untuk pengiriman data IoT.

- Sensor Air (Water Sensor/Ultrasonic HC-SR04): Mendeteksi ketinggian air secara akurat.

- Buzzer: Komponen output audio untuk memberikan peringatan fisik instan saat air mencapai titik bahaya.

- Breadboard & Jumper Wires: Media prototipe untuk menghubungkan komponen tanpa perlu penyolderan.

- Resistor (Voltage Divider): Digunakan khusus jika menggunakan sensor 5V (HC-SR04) guna memastikan sinyal yang masuk ke pin ESP32 tetap berada di level aman (3.3V).

🚀 Cara Kerja Sistem

- Akuisisi Data: ESP32 membaca data dari sensor air setiap beberapa detik.

-  Peringatan Lokal: ESP32 secara mandiri memeriksa data. Jika nilai sensor melampaui batas (misal: 1500), ESP32 segera menyalakan buzzer sebagai respons instan.

- Pengiriman Data: Data ketinggian air dikirimkan ke cloud melalui protokol HTTP/Webhook.

- Pemrosesan Cloud (n8n): Data diterima oleh workflow n8n. n8n menjalankan logika kondisional (If-Else) untuk menentukan apakah status saat ini "AMAN" atau "BAHAYA".

- Penyimpanan: Data hasil olahan (ketinggian + status) disimpan ke database Supabase.

- Visualisasi: Dashboard web (HTML/JS) secara otomatis mengambil data terbaru dari Supabase untuk ditampilkan kepada pengguna.

💻 Teknologi yang Digunakan

- Firmware: C++ (Arduino IDE) untuk ESP32.

- Backend Automation: n8n untuk manajemen alur kerja (workflow) data dari perangkat ke database.

- Database: Supabase (PostgreSQL) sebagai basis data cloud yang cepat dan skalabel.

Frontend:

- Native JavaScript: Untuk fetch data dari API Supabase secara real-time.

- Tailwind CSS CDN: Untuk antarmuka yang modern, cepat, dan responsif (Mobile Friendly).

📋 Struktur Database (Supabase)

Tabel sensor_data memerlukan skema berikut:

- id (int8, Primary Key, Auto Increment)

- created_at (timestamptz, default: now())

- water_level (int4)

- status (text/varchar)

