# Tugas UTS LAB GRAFKOM 

## Anggota Kelompok

- **Richard Fajar Christian (221401122)**
- **Samuel Bryan Parasian Sitanggang (221401125)**
- **Edi Suranta Ginting (221401134)**

## Deskripsi
Proyek ini adalah simulasi animasi karakter menggunakan OpenGL yang mencakup gerakan lompatan dan berjalan. Karakter dapat melompat dengan gravitasi yang mempengaruhinya, serta bergerak ke kiri dan kanan dengan animasi kaki dan tangan yang sesuai.

## Fitur Utama
- **Animasi Lompatan**: Karakter dapat melompat dengan pengaruh gravitasi.
- **Animasi Berjalan**: Karakter dapat berjalan ke kiri atau kanan dengan animasi kaki dan tangan yang bergerak sesuai.
- **Latar Belakang**: Latar belakang yang mencakup langit, rumput, awan, dan pohon.
- **Kontrol Gerakan**: Menggunakan status `isWalking`, `isJumping`, dan pengaturan kecepatan.

## Struktur Kode
- **Variabel Utama**:
  - `jumpVelocity`: Kecepatan lompatan karakter.
  - `isJumping`: Status apakah karakter sedang melompat.
  - `gravity`: Gaya gravitasi yang diterapkan saat melompat.
  - `characterX`, `characterBaseY`: Posisi karakter di layar.
  - `cameraX`: Posisi kamera.
  - `cloudBaseY`, `cloudTopY`: Posisi dasar dan puncak awan.
  - `isWalking`, `facingRight`, `facingSide`: Status dan arah karakter.
  
- **Fungsi Utama**:
  - `updateJump()`: Memperbarui posisi karakter selama lompatan.
  - `updateLegMovement()`: Memperbarui posisi kaki dan lengan saat berjalan.
  - `drawBackground()`: Menggambar latar belakang (langit, rumput, awan, pohon).
  - `drawCharacterFront()`: Menggambar karakter dengan orientasi menghadap depan.
  - `drawCharacterSide()`: Menggambar karakter dengan orientasi menghadap samping.

## Persyaratan Sistem
- **OpenGL** versi 2.1 atau lebih tinggi
- **FreeGLUT**
- **Compiler C/C++** (GCC, MinGW, atau IDE lain yang mendukung OpenGL)

## Cara penginstallan

### 1. Clone Repository

Clone proyek ini menggunakan Git:
```bash
git clone https://github.com/ricathsb/UTS_Lab_Grafkom.git
```

### 2. Install Dependencies nya 

Untuk penginstalan Dependencies nya (freeglut)
link https://www.youtube.com/watch?v=c1MTakMkf88

### 3. Jalankan (run) code nya di Visual Studio 2022

Klik run di Visual Studio anda

## Instruksi Kontrol Karakter

### 1. Keyboard
- **tombol "w"** lompat
- **tombol "a"** bergerak ke kiri
- **tombol "s"** bergerak ke menampilkan front view karakter
- **tombol "d"** bergerak ke kanan
- **tombol "space"** lompat

### 2. Mouse 
- **"klik kiri"** bergerak ke kiri
- **"klik kanan"** bergerak ke kiri
- **"Klik tengah"** lompat 

## Credits
Proyek ini dikembangkan sebagai bagian dari tugas Ujian Tengah Semester (UTS) di mata kuliah Laboratorium Grafik Komputer. Terima kasih kepada rekan-rekan tim yang telah berkontribusi dalam pengembangan proyek ini.
  
  












