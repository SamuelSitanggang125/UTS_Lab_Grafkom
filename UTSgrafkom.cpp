#include <GL/freeglut.h>
#include <math.h>  // Menambahkan header untuk fungsi cosf dan sinf

float characterX = 0.0f;   // Posisi X karakter
float cameraX = 0.0f;      // Posisi X kamera
const float screenWidth = 800.0f;       // Lebar layar
const float backgroundWidth = 1600.0f;  // Lebar latar belakang
const float characterWidth = 20.0f;     // Lebar kotak (karakter)

void drawBackground() {
    // Gambar langit
    glColor3f(0.5f, 0.8f, 1.0f);  // Warna biru muda untuk langit
    glBegin(GL_QUADS);
    glVertex2f(-backgroundWidth, 200.0f);   // Atas kiri
    glVertex2f(backgroundWidth, 200.0f);   // Atas kanan
    glVertex2f(backgroundWidth, -150.0f);  // Bawah kanan (di atas rumput)
    glVertex2f(-backgroundWidth, -150.0f);  // Bawah kiri
    glEnd();

    // Gambar rumput
    glColor3f(0.0f, 0.5f, 0.0f);  // Warna hijau untuk rumput
    glBegin(GL_QUADS);
    glVertex2f(-backgroundWidth, -200.0f);  // Bawah kiri
    glVertex2f(backgroundWidth, -200.0f);   // Bawah kanan
    glVertex2f(backgroundWidth, -150.0f);   // Atas kanan
    glVertex2f(-backgroundWidth, -150.0f);  // Atas kiri
    glEnd();

    // Gambar awan dengan jarak antar awan 300
    glColor3f(1.0f, 1.0f, 1.0f);  // Warna putih untuk awan
    for (float x = -backgroundWidth; x <= backgroundWidth; x += 250.0f) {
        for (float offset = 0.0f; offset <= 70.0f; offset += 30.0f) {
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x + offset, 150.0f);      // Titik pusat
            glVertex2f(x + offset - 20.0f, 150.0f);
            glVertex2f(x + offset - 10.0f, 170.0f);
            glVertex2f(x + offset + 10.0f, 170.0f);
            glVertex2f(x + offset + 20.0f, 150.0f);
            glEnd();
        }
    }

    // Gambar pohon
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Atur kamera dengan translasi pada sumbu X
    glPushMatrix();
    glTranslatef(-cameraX, 0.0f, 0.0f);

    // Panggil fungsi untuk menggambar latar belakang
    drawBackground();

    // Gambar karakter (kotak merah)
    glPushMatrix();
    glTranslatef(characterX, 0.0f, 0.0f);  // Pindahkan karakter
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-characterWidth / 2, -10.0f);
    glVertex2f(characterWidth / 2, -10.0f);
    glVertex2f(characterWidth / 2, 10.0f);
    glVertex2f(-characterWidth / 2, 10.0f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    // Update posisi kamera hanya jika karakter berada di tengah layar
    if (characterX > screenWidth / 2 && characterX < backgroundWidth - screenWidth / 2) {
        cameraX = characterX - screenWidth / 2;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    // Kontrol karakter dengan tombol 'a' (kiri) dan 'd' (kanan)
    if (key == 'a') {
        if (characterX > cameraX + characterWidth / 2) {  // Batas kiri layar
            characterX -= 10.0f;  // Gerakkan ke kiri
        }
    }
    else if (key == 'd') {
        if (characterX < cameraX + screenWidth - characterWidth / 2) {  // Batas kanan layar
            characterX += 10.0f;  // Gerakkan ke kanan
        }
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
    gluOrtho2D(0.0, screenWidth, -200.0, 200.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
