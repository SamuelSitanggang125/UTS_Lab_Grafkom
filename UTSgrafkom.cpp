#include <GL/freeglut.h>
#include <math.h> 
#include <stdbool.h>


float characterX = 0.0f;           // Posisi X karakter
float characterBaseY = -125.0f;     // Posisi dasar Y karakter (letak kaki karakter)
float cameraX = 0.0f;               // Posisi X kamera
const float screenWidth = 800.0f;   // Lebar layar
const float backgroundWidth = 1600.0f;  // Lebar latar belakang
const float characterWidth = 10.0f; // Lebar kotak (karakter)
float cloudBaseY = 220.0f;          // Dasar awan
float cloudTopY = 240.0f;           // Puncak awan

bool facingSide = false;            // Apakah karakter sedang menghadap samping
bool facingRight = true;            // Apakah karakter menghadap kanan (jika menghadap samping)

float leftLegAngle = 0.0f;
float rightLegAngle = 0.0f;
float angle = 0.0f; // Variabel ini akan digunakan untuk mengubah sudut rotasi kaki
bool isWalking = false; // Menentukan apakah karakter sedang berjalan'
float leftArmAngle = 0.0f;



void updateLegMovement(bool isWalking, bool facingRight) {
    float speedFactor = 10.0f;  // Adjust this value to control the speed of the leg and arm movement
    float maxAngle = 15.0f;  // Maximum angle for leg and arm movement (reduce if too large)

    if (isWalking) {
        // Update the angle of the legs and arms for walking animation
        float timeFactor = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Convert time to seconds

        if (facingRight) {
            leftLegAngle = sin(timeFactor * speedFactor) * maxAngle;  // Left leg moves
            rightLegAngle = -leftLegAngle; // Right leg moves in the opposite direction

            // Left arm moves in sync with left leg
            leftArmAngle = sin(timeFactor * speedFactor) * maxAngle;
        }
        else {
            rightLegAngle = sin(timeFactor * speedFactor) * maxAngle;  // Right leg moves
            leftLegAngle = -rightLegAngle; // Left leg moves in the opposite direction

            // Left arm moves in sync with left leg (mirror the arm movement if facing left)
            leftArmAngle = -sin(timeFactor * speedFactor) * maxAngle;
        }
    }
    else {
        // If not walking, set legs and arm to a resting position
        leftLegAngle = 0.0f;
        rightLegAngle = 0.0f;
        leftArmAngle = 0.0f;

    }
}

void drawBackground() {
    // Menggambar langit
    glColor3f(0.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-backgroundWidth, 300.0f);
    glVertex2f(backgroundWidth, 300.0f);
    glVertex2f(backgroundWidth, -150.0f);
    glVertex2f(-backgroundWidth, -150.0f);
    glEnd();

    // Menggambar rumput
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-backgroundWidth, -200.0f);
    glVertex2f(backgroundWidth, -200.0f);
    glVertex2f(backgroundWidth, -150.0f);
    glVertex2f(-backgroundWidth, -150.0f);
    glEnd();

    // Menggambar awan
    glColor3f(1.0f, 1.0f, 1.0f);
    for (float x = -backgroundWidth; x <= backgroundWidth; x += 250.0f) {
        for (float offset = 0.0f; offset <= 70.0f; offset += 30.0f) {
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x + offset, cloudBaseY);
            glVertex2f(x + offset - 20.0f, cloudBaseY);
            glVertex2f(x + offset - 10.0f, cloudTopY);
            glVertex2f(x + offset + 10.0f, cloudTopY);
            glVertex2f(x + offset + 20.0f, cloudBaseY);
            glEnd();
        }
    }

    for (float x = -backgroundWidth + 100.0f; x <= backgroundWidth; x += 300.0f) {
        // Batang pohon
        glColor3f(0.5f, 0.35f, 0.05f);  // Warna coklat untuk batang
        glBegin(GL_QUADS);
        glVertex2f(x - 10.0f, -150.0f);    // Bawah kiri
        glVertex2f(x + 10.0f, -150.0f);    // Bawah kanan
        glVertex2f(x + 10.0f, -100.0f);    // Atas kanan
        glVertex2f(x - 10.0f, -100.0f);    // Atas kiri
        glEnd();
        // Daun pohon (bentuk lingkaran sederhana)
        glColor3f(0.0f, 0.7f, 0.0f);  // Warna hijau untuk daun
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, -80.0f);    // Pusat lingkaran
        for (int i = 0; i <= 20; i++) {
            float angle = i * 2.0f * 3.14159f / 20;  // Menghitung sudut per titik
            float dx = 30.0f * cosf(angle);  // Posisi X titik lingkaran
            float dy = 30.0f * sinf(angle);  // Posisi Y titik lingkaran
            glVertex2f(x + dx, -80.0f + dy);  // Menambahkan posisi titik
        }
        glEnd();
    }


}

void drawCharacterFront() {
    // Menggambar karakter tampak depan
    glColor3f(1.0f, 0.0f, 0.0f);  // Badan
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(24.0f, 0.0f);
    glVertex2f(24.0f, 20.0f);
    glVertex2f(4.0f, 20.0f);
    glEnd();

    // Gambar celana
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(24.0f, 0.0f);
    glVertex2f(24.0f, -7.0f);
    glVertex2f(4.0f, -7.0f);
    glEnd();

    // Gambar kaki (Biru)
    glColor3f(0.0f, 0.5f, 1.0f); // Warna biru
    glBegin(GL_QUADS);
    glVertex2f(6.0f, -20.0f);
    glVertex2f(10.0f, -20.0f);
    glVertex2f(10.0f, -7.0f);
    glVertex2f(6.0f, -7.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(18.0f, -20.0f);
    glVertex2f(22.0f, -20.0f);
    glVertex2f(22.0f, -7.0f);
    glVertex2f(18.0f, -7.0f);
    glEnd();

    // Gambar sepatu (Hitam)
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glBegin(GL_QUADS);
    glVertex2f(6.0f, -25.0f);
    glVertex2f(10.0f, -25.0f);
    glVertex2f(10.0f, -20.0f);
    glVertex2f(6.0f, -20.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(18.0f, -25.0f);
    glVertex2f(22.0f, -25.0f);
    glVertex2f(22.0f, -20.0f);
    glVertex2f(18.0f, -20.0f);
    glEnd();

    // Gambar kepala (Krem)
    glColor3f(1.0f, 0.9f, 0.6f); // Warna krem
    glBegin(GL_QUADS);
    glVertex2f(6.0f, 20.0f);
    glVertex2f(22.0f, 20.0f);
    glVertex2f(22.0f, 38.0f);
    glVertex2f(6.0f, 38.0f);
    glEnd();

    // Gambar hidung
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glBegin(GL_LINE_STRIP);
    glVertex2f(14.0f, 28.0f);
    glVertex2f(15.0f, 26.0f);
    glVertex2f(13.0f, 26.0f); // Titik tambahan
    glEnd();

    // Gambar Leher (Krem)
    glColor3f(1.0f, 0.9f, 0.6f); // Warna krem
    glBegin(GL_TRIANGLES);
    glVertex2f(8.0f, 20.0f);
    glVertex2f(20.0f, 20.0f);
    glVertex2f(14.5f, 18.0f);
    glEnd();

    // Gambar belakang mata 
    glColor3f(1.0f, 1.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(9.0f, 28.0f);
    glVertex2f(13.0f, 28.0f);
    glVertex2f(13.0f, 32.0f);
    glVertex2f(9.0f, 32.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(15.0f, 28.0f);
    glVertex2f(19.0f, 28.0f);
    glVertex2f(19.0f, 32.0f);
    glVertex2f(15.0f, 32.0f);
    glEnd();

    // Gambar mata (Hijau)
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hijau
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 29.0f);
    glVertex2f(12.0f, 29.0f);
    glVertex2f(12.0f, 31.0f);
    glVertex2f(10.0f, 31.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(16.0f, 29.0f);
    glVertex2f(18.0f, 29.0f);
    glVertex2f(18.0f, 31.0f);
    glVertex2f(16.0f, 31.0f);
    glEnd();

    // Gambar mulut (Abu-abu)
    glColor3f(0.5f, 0.5f, 0.5f); // Warna abu-abu
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 23.0f);
    glVertex2f(18.0f, 23.0f);
    glVertex2f(18.0f, 24.0f);
    glVertex2f(10.0f, 24.0f);
    glEnd();

    // Gambar bahu (Krem)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 20.0f);
    glVertex2f(4.0f, 20.0f);
    glVertex2f(4.0f, 14.0f);
    glVertex2f(0.0f, 14.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(24.0f, 20.0f);
    glVertex2f(28.0f, 20.0f);
    glVertex2f(28.0f, 14.0f);
    glVertex2f(24.0f, 14.0f);
    glEnd();

    // Gambar tangan (Krem)
    glColor3f(1.0f, 0.9f, 0.6f); // Warna krem untuk tangan
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 14.0f);
    glVertex2f(4.0f, 14.0f);
    glVertex2f(4.0f, -2.0f);
    glVertex2f(0.0f, -2.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(24.0f, 14.0f);
    glVertex2f(28.0f, 14.0f);
    glVertex2f(28.0f, -2.0f);
    glVertex2f(24.0f, -2.0f);
    glEnd();

    // Gambar rambut (Hitam)
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam untuk rambut
    glBegin(GL_QUADS);
    glVertex2f(6.0f, 38.0f);
    glVertex2f(6.0f, 30.0f);
    glVertex2f(22.0f, 38.0f);
    glVertex2f(22.0f, 30.0f);
    glEnd();

    // Gambar telinga
    glColor3f(1.0f, 0.9f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(6.0f, 30.0f);
    glVertex2f(5.0f, 30.0f);
    glVertex2f(5.0f, 25.0f);
    glVertex2f(6.0f, 25.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(22.0f, 30.0f);
    glVertex2f(23.0f, 30.0f);
    glVertex2f(23.0f, 25.0f);
    glVertex2f(22.0f, 25.0f);
    glEnd();
    glPopMatrix();

    // Detail lainnya seperti kaki, sepatu, kepala, mata, hidung, dll.
    // (Implementasi karakter seperti pada kode asli)
}

void drawCharacterSide(bool facingRight) {
    glPushMatrix();
    updateLegMovement(isWalking, facingRight);

    // Jika karakter menghadap kiri, kita membalikkan gambar di sumbu X
    if (!facingRight) {
        glScalef(-1.0f, 1.0f, 1.0f);
        glTranslatef(-20.0f, 0.0f, 0.0f);
    }

    // Menggambar badan karakter (tampak samping)
    glColor3f(1.0f, 0.0f, 0.0f);  // Badan
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(16.0f, 0.0f);
    glVertex2f(16.0f, 20.0f);
    glVertex2f(4.0f, 20.0f);
    glEnd();

    // Menggambar celana
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(16.0f, 0.0f);
    glVertex2f(16.0f, -7.0f);
    glVertex2f(4.0f, -7.0f);
    glEnd();

    // Kaki kiri
    glPushMatrix();
    glTranslatef(10.0f, -7.0f, 0.0f); // Pindah titik rotasi ke posisi pangkal kaki
    glRotatef(leftLegAngle, 0.0f, 0.0f, 1.0f); // Rotasi berdasarkan sudut kaki kiri
    glTranslatef(-10.0f, 7.0f, 0.0f); // Kembalikan posisi setelah rotasi
    glColor3f(0.0f, 0.5f, 1.0f); // Warna kaki kiri
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -7.0f);
    glVertex2f(8.0f, -7.0f);
    glEnd();

    // Sepatu kiri
    glTranslatef(0.0f, -5.0f, 0.0f); // Posisi sepatu kiri sedikit lebih rendah dari kaki
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam (sepatu kiri)
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -15.0f);
    glVertex2f(8.0f, -15.0f);
    glEnd();
    glPopMatrix();

    // Kaki kanan
    glPushMatrix();
    glTranslatef(10.0f, -7.0f, 0.0f); // Pindah titik rotasi ke posisi pangkal kaki
    glRotatef(rightLegAngle, 0.0f, 0.0f, 1.0f); // Rotasi berdasarkan sudut kaki kanan
    glTranslatef(-10.0f, 7.0f, 0.0f); // Kembalikan posisi setelah rotasi
    glColor3f(0.0f, 0.3f, 0.7f); // Warna kaki kanan
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -7.0f);
    glVertex2f(8.0f, -7.0f);
    glEnd();

    // Sepatu kanan
    glTranslatef(0.0f, -5.0f, 0.0f); // Posisi sepatu kanan sedikit lebih rendah dari kaki
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam (sepatu kanan)
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -15.0f);
    glVertex2f(8.0f, -15.0f);
    glEnd();
    glPopMatrix();

    // Menggambar kepala (Krem)
    glColor3f(1.0f, 0.9f, 0.6f); // Warna krem
    glBegin(GL_QUADS);
    glVertex2f(6.0f, 20.0f);
    glVertex2f(16.0f, 20.0f);
    glVertex2f(16.0f, 36.0f);
    glVertex2f(6.0f, 36.0f);
    glEnd();

    // Menggambar hidung (Hitam)
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glBegin(GL_TRIANGLES);
    glVertex2f(16.0f, 30.0f);
    glVertex2f(17.0f, 28.0f);
    glVertex2f(16.0f, 28.0f);
    glEnd();

    // Menggambar mata (Hijau)
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hijau
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 30.0f);
    glVertex2f(12.0f, 30.0f);
    glVertex2f(12.0f, 32.0f);
    glVertex2f(10.0f, 32.0f);
    glEnd();

    // Menggambar mulut (Abu-abu)
    glColor3f(0.5f, 0.5f, 0.5f); // Warna abu-abu
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 23.0f);
    glVertex2f(14.0f, 23.0f);
    glVertex2f(14.0f, 24.0f);
    glVertex2f(10.0f, 24.0f);
    glEnd();

    // Menggambar telinga (Krem)
    glColor3f(1.0f, 0.9f, 0.6f); // Warna krem
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 30.0f);
    glVertex2f(5.0f, 30.0f);
    glVertex2f(5.0f, 25.0f);
    glVertex2f(4.0f, 25.0f);
    glEnd();

    // Menggambar rambut (Hitam)
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam untuk rambut
    glBegin(GL_QUADS);
    glVertex2f(6.0f, 36.0f);
    glVertex2f(6.0f, 32.0f);
    glVertex2f(16.0f, 36.0f);
    glVertex2f(16.0f, 32.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // Warna krem untuk lengan atas
    glPushMatrix();
    glTranslatef(12.0f, 15.0f, 0.0f);  // Posisi pangkal lengan bawah (di bahu)
    glRotatef(leftArmAngle, 0.0f, 0.0f, 1.0f);  // Rotasi berdasarkan sudut tangan kiri
    glTranslatef(-12.0f, -15.0f, 0.0f);  // Kembalikan posisi setelah rotasi
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 20.0f);
    glVertex2f(14.0f, 20.0f);
    glVertex2f(14.0f, 10.0f);
    glVertex2f(10.0f, 10.0f);
    glEnd();
    glPopMatrix();

    // Lengan bawah (Rotasi berdasarkan sudut tangan kiri)
    glColor3f(1.0f, 0.9f, 0.6f); // Warna krem untuk lengan atas
    glPushMatrix();
    glTranslatef(12.0f, 15.0f, 0.0f);  // Posisi pangkal lengan bawah (di bahu)
    glRotatef(leftArmAngle, 0.0f, 0.0f, 1.0f);  // Rotasi berdasarkan sudut tangan kiri
    glTranslatef(-12.0f, -15.0f, 0.0f);  // Kembalikan posisi setelah rotasi
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 10.0f);
    glVertex2f(14.0f, 10.0f);
    glVertex2f(14.0f, -2.0f);
    glVertex2f(10.0f, -2.0f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}


void drawCharacter() {
    glPushMatrix();
    glTranslatef(0.0f, characterBaseY, 0.0f);

    if (facingSide) {
        drawCharacterSide(facingRight);
    }
    else {
        drawCharacterFront();
    }

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-cameraX, 0.0f, 0.0f); // Apply camera movement

    drawBackground();
    glTranslatef(characterX, characterBaseY, 0.0f); // Move character position

    if (facingSide) {
        drawCharacterSide(facingRight);
    }
    else {
        drawCharacterFront();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    if (characterX > screenWidth / 2 && characterX < backgroundWidth - screenWidth / 2) {
        cameraX = characterX - screenWidth / 2;
    }

    // Perbarui sudut rotasi kaki menggunakan fungsi sinus dan cosinus
    leftLegAngle = sin(angle) * 15.0f;
    rightLegAngle = cos(angle) * 15.0f;

    // Tingkatkan angle untuk perubahan sudut di frame berikutnya
    angle += 0.1f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': // Bergerak ke kiri
        characterX -= 5.0f;
        facingRight = false;
        facingSide = true;
        isWalking = true; // Mulai animasi berjalan
        break;
    case 'd': // Bergerak ke kanan
        characterX += 5.0f;
        facingRight = true;
        facingSide = true;
        isWalking = true; // Mulai animasi berjalan
        break;
    case 's': // Tampil di front view
        facingSide = false; // Ganti ke front view
        facingRight = true; // Tampilkan karakter menghadap ke depan (sesuaikan jika perlu)
        isWalking = false; // Bisa menonaktifkan animasi berjalan jika tidak diperlukan
        break;
    default:
        break;
    }
    updateLegMovement(isWalking, facingRight); // Update leg movement based on walking state
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
    case 'd':
        isWalking = false; // Hentikan animasi berjalan
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, 400);
    glutCreateWindow("Side Scrolling with Background Elements");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, screenWidth, -200.0f, 300.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp); // Menambahkan fungsi ini
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
