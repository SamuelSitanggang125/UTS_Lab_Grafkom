#include <GL/freeglut.h>

float characterX = 0.0f;   // Posisi X karakter
float cameraX = 0.0f;      // Posisi X kamera
const float screenWidth = 800.0f;       // Lebar layar
const float backgroundWidth = 1600.0f;  // Lebar latar belakang
const float characterWidth = 20.0f;     // Lebar kotak (karakter)

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

    // Gambar pohon
    glColor3f(0.4f, 0.2f, 0.1f);  // Warna batang pohon
    glBegin(GL_QUADS);
    glVertex2f(300.0f, -100.0f);
    glVertex2f(320.0f, -100.0f);
    glVertex2f(320.0f, 0.0f);
    glVertex2f(300.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.8f, 0.0f);  // Warna daun pohon
    glBegin(GL_TRIANGLES);
    glVertex2f(280.0f, 0.0f);
    glVertex2f(340.0f, 0.0f);
    glVertex2f(310.0f, 60.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(290.0f, 30.0f);
    glVertex2f(330.0f, 30.0f);
    glVertex2f(310.0f, 80.0f);
    glEnd();

    // Gambar awan
    glColor3f(1.0f, 1.0f, 1.0f);  // Warna putih untuk awan
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(600.0f, 150.0f);
    glVertex2f(580.0f, 150.0f);
    glVertex2f(590.0f, 170.0f);
    glVertex2f(610.0f, 170.0f);
    glVertex2f(620.0f, 150.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(650.0f, 160.0f);
    glVertex2f(630.0f, 160.0f);
    glVertex2f(640.0f, 180.0f);
    glVertex2f(660.0f, 180.0f);
    glVertex2f(670.0f, 160.0f);
    glEnd();
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
