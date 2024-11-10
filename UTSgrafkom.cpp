#include <GL/freeglut.h>
#include <math.h> 
#include <stdbool.h>

float jumpVelocity = 0.0f;          // Kecepatan lompatan
bool isJumping = false;             // karakter lagi lompat atau tidak
float gravity = -0.5f;              // gaya gravitasi ketika lompat
float characterX = 0.0f;           // Posisi X karakter
float characterBaseY = -125.0f;     // Posisi y karakter (kaki)
float cameraX = 0.0f;               // Posisi X kamera
const float screenWidth = 800.0f;   // Lebar layar
const float backgroundWidth = 1600.0f;  // Lebar latar belakang
const float characterWidth = 10.0f; // Lebar kotak (karakter)
float cloudBaseY = 220.0f;          // Dasar awan
float cloudTopY = 240.0f;           // Puncak awan

bool facingSide = false;            // Apakah karakter sedang menghadap samping
bool facingRight = true;            // Apakah karakter menghadap kanan (jika menghadap samping)

//var untuk angle rotasi kaki kiri, kanan ,dan tangan 
//var untuk kondisi karakter bergerak ke kiri atau kanan
// dan juga kondisi karakter sedang berjalan atau tidak 
float leftLegAngle = 0.0f;          
float rightLegAngle = 0.0f;
float angle = 0.0f; 
bool isWalking = false; 
float leftArmAngle = 0.0f;
bool isMovingLeft = false;
bool isMovingRight = false;

void updateJump() {
    if (isJumping) {
        characterBaseY += jumpVelocity;  // Update posisi Y berdasarkan kecepatan lompatan
        jumpVelocity += gravity;         // Tambahkan gravitasi ke kecepatan lompatan


        if (characterBaseY <= -125.0f) {
            characterBaseY = -125.0f;   // Kembalikan ke posisi dasar
            isJumping = false;          // Lompatan selesai
            jumpVelocity = 0.0f;        // Reset kecepatan lompatan
        }
    }
}

void updateLegMovement(bool isWalking, bool facingRight) {
    float speedFactor = 10.0f; 
    float maxAngle = 15.0f;  

    if (isWalking) {
       
        float timeFactor = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f; 

        if (facingRight) {
            leftLegAngle = sin(timeFactor * speedFactor) * maxAngle; 
            rightLegAngle = -leftLegAngle; 

            leftArmAngle = sin(timeFactor * speedFactor) * maxAngle;
        }
        else {
            rightLegAngle = sin(timeFactor * speedFactor) * maxAngle;  
            leftLegAngle = -rightLegAngle; 

            leftArmAngle = -sin(timeFactor * speedFactor) * maxAngle;
        }
    }
    else {
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
        glColor3f(0.5f, 0.35f, 0.05f);  
        glBegin(GL_QUADS);
        glVertex2f(x - 10.0f, -150.0f);    
        glVertex2f(x + 10.0f, -150.0f);    
        glVertex2f(x + 10.0f, -100.0f);    
        glVertex2f(x - 10.0f, -100.0f);    
        glEnd();
        // Daun pohon (bentuk lingkaran sederhana)
        glColor3f(0.0f, 0.7f, 0.0f);  
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, -80.0f);    
        for (int i = 0; i <= 20; i++) {
            float angle = i * 2.0f * 3.14159f / 20;  
            float dx = 30.0f * cosf(angle);  
            float dy = 30.0f * sinf(angle);  
            glVertex2f(x + dx, -80.0f + dy);  
        }
        glEnd();
    }


}

void drawCharacterFront() {
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

    if (!facingRight) {
        glScalef(-1.0f, 1.0f, 1.0f);
        glTranslatef(-20.0f, 0.0f, 0.0f);
    }

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
    glTranslatef(10.0f, -7.0f, 0.0f); 
    glRotatef(leftLegAngle, 0.0f, 0.0f, 1.0f); 
    glTranslatef(-10.0f, 7.0f, 0.0f); 
    glColor3f(0.0f, 0.5f, 1.0f); 
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -7.0f);
    glVertex2f(8.0f, -7.0f);
    glEnd();

    // Sepatu kiri
    glTranslatef(0.0f, -5.0f, 0.0f); 
    glColor3f(0.0f, 0.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -15.0f);
    glVertex2f(8.0f, -15.0f);
    glEnd();
    glPopMatrix();

    // Kaki kanan
    glPushMatrix();
    glTranslatef(10.0f, -7.0f, 0.0f); 
    glRotatef(rightLegAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-10.0f, 7.0f, 0.0f); 
    glColor3f(0.0f, 0.3f, 0.7f); 
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -7.0f);
    glVertex2f(8.0f, -7.0f);
    glEnd();

    // Sepatu kanan
    glTranslatef(0.0f, -5.0f, 0.0f); 
    glColor3f(0.0f, 0.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(8.0f, -20.0f);
    glVertex2f(12.0f, -20.0f);
    glVertex2f(12.0f, -15.0f);
    glVertex2f(8.0f, -15.0f);
    glEnd();
    glPopMatrix();

    // Menggambar kepala (Krem)
    glColor3f(1.0f, 0.9f, 0.6f); 
    glBegin(GL_QUADS);
    glVertex2f(6.0f, 20.0f);
    glVertex2f(16.0f, 20.0f);
    glVertex2f(16.0f, 36.0f);
    glVertex2f(6.0f, 36.0f);
    glEnd();

    // Menggambar hidung (Hitam)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(16.0f, 30.0f);
    glVertex2f(17.0f, 28.0f);
    glVertex2f(16.0f, 28.0f);
    glEnd();

    // Menggambar mata (Hijau)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 30.0f);
    glVertex2f(12.0f, 30.0f);
    glVertex2f(12.0f, 32.0f);
    glVertex2f(10.0f, 32.0f);
    glEnd();

    // Menggambar mulut (Abu-abu)
    glColor3f(0.5f, 0.5f, 0.5f); 
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 23.0f);
    glVertex2f(14.0f, 23.0f);
    glVertex2f(14.0f, 24.0f);
    glVertex2f(10.0f, 24.0f);
    glEnd();

    // Menggambar telinga (Krem)
    glColor3f(1.0f, 0.9f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 30.0f);
    glVertex2f(5.0f, 30.0f);
    glVertex2f(5.0f, 25.0f);
    glVertex2f(4.0f, 25.0f);
    glEnd();

    // Menggambar rambut (Hitam)
    glColor3f(0.0f, 0.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(6.0f, 36.0f);
    glVertex2f(6.0f, 32.0f);
    glVertex2f(16.0f, 36.0f);
    glVertex2f(16.0f, 32.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(12.0f, 15.0f, 0.0f); 
    glRotatef(leftArmAngle, 0.0f, 0.0f, 1.0f); 
    glTranslatef(-12.0f, -15.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 20.0f);
    glVertex2f(14.0f, 20.0f);
    glVertex2f(14.0f, 10.0f);
    glVertex2f(10.0f, 10.0f);
    glEnd();
    glPopMatrix();

    glColor3f(1.0f, 0.9f, 0.6f); // Warna krem untuk lengan atas
    glPushMatrix();
    glTranslatef(12.0f, 15.0f, 0.0f);  
    glRotatef(leftArmAngle, 0.0f, 0.0f, 1.0f);  
    glTranslatef(-12.0f, -15.0f, 0.0f);  
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 10.0f);
    glVertex2f(14.0f, 10.0f);
    glVertex2f(14.0f, -2.0f);
    glVertex2f(10.0f, -2.0f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-cameraX, 0.0f, 0.0f); 

    drawBackground();
    glTranslatef(characterX, characterBaseY, 0.0f); 

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
    if (isWalking) {
        // Cegah karakter keluar dari batas kiri dan kanan latar belakang
        if (isMovingLeft && characterX > 0.0f) {
            characterX -= 2.0f;  
            facingRight = false;
        }
        else if (isMovingRight && characterX < backgroundWidth - characterWidth - 10.0f) {
            characterX += 2.0f;  
            facingRight = true;
        }
    }

    // Update posisi kamera berdasarkan posisi karakter
    if (characterX > screenWidth / 2 && characterX < backgroundWidth - screenWidth / 2) {
        cameraX = characterX - screenWidth / 2;
    }

    updateJump();

    // Perbarui sudut rotasi kaki menggunakan fungsi sinus dan cosinus
    leftLegAngle = sin(angle) * 15.0f;
    rightLegAngle = cos(angle) * 15.0f;

    // Tingkatkan angle untuk perubahan sudut di frame berikutnya
    angle += 0.1f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Timer untuk update posisi setiap 16 ms
}

void moveLeft() {
    characterX -= 5.0f;
    facingRight = false;
    facingSide = true;
    isWalking = true;
    updateLegMovement(isWalking, facingRight);
}

void moveRight() {
    characterX += 5.0f;
    facingRight = true;
    facingSide = true;
    isWalking = true;
    updateLegMovement(isWalking, facingRight);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': // Bergerak ke kiri
        isMovingLeft = true;
        isWalking = true;
        facingRight = false;
        facingSide = true;
        break;
    case 'd': // Bergerak ke kanan
        isMovingRight = true;
        isWalking = true;
        facingRight = true;
        facingSide = true;
        break;
    case 's': // Tampil di front view
        facingSide = false;
        facingRight = true;
        isWalking = false;
        break;
    case 'w': // Lompat dengan tombol 'w'
    case 32:  // Lompat dengan tombol 'Space'
        if (!isJumping) {
            jumpVelocity = 10.0f;
            isJumping = true;
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        isMovingLeft = false;
        isWalking = isMovingRight; // Tetap berjalan jika tombol kanan masih ditekan
        break;
    case 'd':
        isMovingRight = false;
        isWalking = isMovingLeft; // Tetap berjalan jika tombol kiri masih ditekan
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch (button) {
        case GLUT_LEFT_BUTTON:
            isMovingLeft = true;
            isWalking = true;
            facingRight = false;
            facingSide = true;
            break;
        case GLUT_RIGHT_BUTTON:
            isMovingRight = true;
            isWalking = true;
            facingRight = true;
            facingSide = true;
            break;
        case GLUT_MIDDLE_BUTTON:
            if (!isJumping) {
                jumpVelocity = 10.0f;
                isJumping = true;
            }
            break;
        default:
            break;
        }
    }
    else if (state == GLUT_UP) {
        if (button == GLUT_LEFT_BUTTON) {
            isMovingLeft = false;
            isWalking = isMovingRight;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            isMovingRight = false;
            isWalking = isMovingLeft;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, 400);
    glutCreateWindow("Tugas UTS LAB GRAFKOM");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, screenWidth, -200.0f, 300.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(16, update, 0);
    glutMouseFunc(mouse);


    glutMainLoop();
    return 0;
}