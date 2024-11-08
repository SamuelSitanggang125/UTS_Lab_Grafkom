#include <GL/freeglut.h>

float characterX = 0.0f;   // Posisi X karakter
float cameraX = 0.0f;      // Posisi X kamera
const float screenWidth = 800.0f;       // Lebar layar
const float backgroundWidth = 1600.0f;  // Lebar latar belakang
const float characterWidth = 10.0f;     // Lebar kotak (karakter)

void drawBackground() {
    // Gambar latar belakang dengan pola sederhana
    for (float x = 0.0f; x < backgroundWidth; x += 100.0f) {
        if (static_cast<int>(x / 100) % 2 == 0) {
            glColor3f(0.5f, 0.8f, 1.0f);  // Warna biru langit
        }
        else {
            glColor3f(0.6f, 0.9f, 1.0f);  // Warna biru langit muda
        }
        glBegin(GL_QUADS);
        glVertex2f(x, -200.0f);
        glVertex2f(x + 100.0f, -200.0f);
        glVertex2f(x + 100.0f, 200.0f);
        glVertex2f(x, 200.0f);
        glEnd();
    }
}

void drawCharacter() {
    // Gambar badan (Merah)
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah
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
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Atur kamera dengan translasi pada sumbu X
    glPushMatrix();
    glTranslatef(-cameraX, 0.0f, 0.0f);

    // Panggil fungsi untuk menggambar latar belakang
    drawBackground();

    // Gambar karakter
    glPushMatrix();
    glTranslatef(characterX, 0.0f, 0.0f);  // Pindahkan karakter
    drawCharacter();  // Gambar karakter yang telah dibuat
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
    gluOrtho2D(0.0f, screenWidth, -100.0f, 300.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
