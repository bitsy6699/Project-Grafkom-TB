#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdlib>
#include <iostream>

// ================= KONSTANTA =================
const float PI = 3.14159265f;
const float MOVE_SPEED = 0.5f; // Saya percepat sedikit agar enak keliling
const float MOUSE_SENS = 0.2f;

// ================= KAMERA ====================
float camX = 20.0f, camY = 10.0f, camZ = 30.0f;
float camYaw = 0.0f, camPitch = -15.0f;
bool keys[256] = { false };
int winW = 1280, winH = 720;

// ================= LOADING ===================
bool isLoading = true;
float loadingProgress = 0.0f;

// ================= LIGHTING GLOBALS ==========
bool lightingEnabled = true;
int lightMode = 1;

bool isDirectional = false;
bool isSpotlight = false;
float spotCutoff = 45.0f;
float spotExponent = 2.0f;
float linearAttenuation = 0.0f;
bool isShiny = true;

// ================= INIT ======================
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Darker background for lighting effect
}

// ================= LIGHTING FUNCTIONS ========
void updateLightingLogic() {
    if (!lightingEnabled) {
        glDisable(GL_LIGHTING);
        return;
    }
    glEnable(GL_LIGHTING);

    GLfloat val_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat val_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat val_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat val_black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    if (lightMode == 1) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, val_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, val_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, val_specular);
    } else if (lightMode == 2) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, val_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, val_black);
        glLightfv(GL_LIGHT0, GL_SPECULAR, val_black);
    } else if (lightMode == 3) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, val_black);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, val_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, val_black);
    } else if (lightMode == 4) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, val_black);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, val_black);
        glLightfv(GL_LIGHT0, GL_SPECULAR, val_specular);
    }

    GLfloat w_component = isDirectional ? 0.0f : 1.0f;
    GLfloat light_pos[] = {0.0f, 5.0f, 0.0f, w_component};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    if (isSpotlight) {
        GLfloat spotDir[] = {0.0f, -1.0f, 0.0f};
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
    } else {
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
    }

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

    if (isShiny) {
        GLfloat mat_spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    } else {
        GLfloat mat_spec[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    }
}

void drawLightSource() {
    if (!lightingEnabled) return;
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 0.0f);
    
    if (isDirectional) {
        glColor3f(1.0f, 1.0f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    if (isSpotlight) {
        glutWireSphere(0.2, 10, 10);
    } else {
        glutSolidSphere(0.15, 20, 20);
    }
    
    glPopMatrix();
    if (lightingEnabled) glEnable(GL_LIGHTING);
}

// ================= LOADING SCREEN ============
void drawLoadingScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winW, 0, winH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos2i(winW/2 - 60, winH/2 + 40);
    const char* text = "LOADING...";
    for (int i = 0; text[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

    float barW = 400, barH = 25;
    float x = winW/2 - barW/2;
    float y = winH/2;

    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + barW, y);
        glVertex2f(x + barW, y + barH);
        glVertex2f(x, y + barH);
    glEnd();

    glColor3f(0.2f, 0.6f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + barW * (loadingProgress / 100.0f), y);
        glVertex2f(x + barW * (loadingProgress / 100.0f), y + barH);
        glVertex2f(x, y + barH);
    glEnd();

    glutSwapBuffers();
}

// ================= KAMERA ====================
void updateCamera() {
    float yawRad = camYaw * PI / 180.0f;
    float pitchRad = camPitch * PI / 180.0f;

    float fx = sin(yawRad) * cos(pitchRad);
    float fy = -sin(pitchRad);
    float fz = -cos(yawRad) * cos(pitchRad);

    float rx = sin(yawRad + PI / 2);
    float rz = -cos(yawRad + PI / 2);

    if (keys['w']) { camX += fx * MOVE_SPEED; camY += fy * MOVE_SPEED; camZ += fz * MOVE_SPEED; }
    if (keys['s']) { camX -= fx * MOVE_SPEED; camY -= fy * MOVE_SPEED; camZ -= fz * MOVE_SPEED; }
    if (keys['a']) { camX -= rx * MOVE_SPEED; camZ -= rz * MOVE_SPEED; }
    if (keys['d']) { camX += rx * MOVE_SPEED; camZ += rz * MOVE_SPEED; }
}

void drawLEDWave(float x1, float z1, float x2, float z2) {
    glDisable(GL_LIGHTING);

    int lampCount = 40;
    float topY = 30.0f;
    float waveAmp = 3.0f;

    for (int i = 0; i <= lampCount; i++) {
        float t = (float)i / lampCount;

        float x = x1 + (x2 - x1) * t;
        float z = z1 + (z2 - z1) * t;
        float y = topY - sin(t * PI) * waveAmp;

        switch (i % 4) {
            case 0: glColor3ub(255, 80, 80);  break;
            case 1: glColor3ub(80, 255, 120); break;
            case 2: glColor3ub(80, 120, 255); break;
            case 3: glColor3ub(255, 255, 120);break;
        }

        glPushMatrix();
            glTranslatef(x, y, z);
            glutSolidSphere(0.6f, 16, 16);
        glPopMatrix();
    }
}

// ================= DISPLAY ===================
void display() {
	glLineWidth(4.0);

    if (isLoading) {
        drawLoadingScreen();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)winW / winH, 0.1, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float yawRad = camYaw * PI / 180.0f;
    float pitchRad = camPitch * PI / 180.0f;

    float fx = sin(yawRad) * cos(pitchRad);
    float fy = -sin(pitchRad);
    float fz = -cos(yawRad) * cos(pitchRad);

    gluLookAt(camX, camY, camZ,
              camX + fx, camY + fy, camZ + fz,
              0, 1, 0);

    updateLightingLogic();
    drawLightSource();

    glDisable(GL_LIGHTING);

    // ===== LANTAI =====
    glColor3f(0.5f, 0.75f, 0.8f);
    glBegin(GL_QUADS);
        glVertex3f(-100, -15, -100);
        glVertex3f(100, -15, -100);
        glVertex3f(100, -15, 100);
        glVertex3f(-100, -15, 100);
    glEnd();

    // ===== RUANGAN =====
    glColor3f(1.0f, 0.85f, 0.9f);
    glBegin(GL_QUADS);
        // Dinding belakang dll... (Disederhanakan mappingnya)
        glVertex3f(-50,-15,50); glVertex3f(50,-15,50);
        glVertex3f(50,35,50);   glVertex3f(-50,35,50);
        
        glVertex3f(-50,-15,-50); glVertex3f(50,-15,-50);
        glVertex3f(50,35,-50);   glVertex3f(-50,35,-50);
        
        glVertex3f(-50,-15,-50); glVertex3f(-50,-15,50);
        glVertex3f(-50,35,50);   glVertex3f(-50,35,-50);
        
        glVertex3f(50,-15,-50); glVertex3f(50,-15,50);
        glVertex3f(50,35,50);   glVertex3f(50,35,-50);
        
        glVertex3f(-50,35,-50); glVertex3f(50,35,-50);
        glVertex3f(50,35,50);   glVertex3f(-50,35,50);
    glEnd();

    // ================= MEJA ===================
    glEnable(GL_LIGHTING);

    GLfloat woodSpec[] = {0.25f, 0.15f, 0.05f, 1};
    GLfloat woodShine[] = {20};
    glMaterialfv(GL_FRONT, GL_SPECULAR, woodSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, woodShine);

    glPushMatrix();
        glTranslatef(0, -5, 0);
        glColor3ub(139, 69, 19);

        glPushMatrix();
            glScalef(30, 1.5, 20);
            glutSolidCube(1);
        glPopMatrix();

        float px[2] = { 14,-14 };
        float pz[2] = { 9,-9 };

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++) {
                glPushMatrix();
                    glTranslatef(px[i], -5, pz[j]);
                    glScalef(1.5, 10, 1.5);
                    glutSolidCube(1);
                glPopMatrix();
            }
    glPopMatrix();

    // ================= KADO =================
    glEnable(GL_LIGHTING);
    
    GLfloat giftSpec2[] = {0.9f, 0.9f, 0.9f, 1};
    GLfloat giftShine2[] = {80};
    glMaterialfv(GL_FRONT, GL_SPECULAR, giftSpec2);
    glMaterialfv(GL_FRONT, GL_SHININESS, giftShine2);
    
    float giftX[3] = { -12.0f, -14.5f, -10.0f };
    float giftZ[3] = {   7.0f,    5.5f,   9.0f };
    float giftS[3] = { 1.6f, 1.2f, 0.9f };
    
    unsigned char giftColor[3][3] = {
        {255,120,180},
        {255,170,210},
        {240, 90,160}
    };
    
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(giftX[i], -3.4f, giftZ[i]);
        glScalef(giftS[i], giftS[i], giftS[i]);

        // Badan kado
        glColor3ub(giftColor[i][0], giftColor[i][1], giftColor[i][2]);
        glutSolidCube(1.5);

        // Pita vertikal
        glColor3ub(255,255,255);
        glPushMatrix();
            glScalef(0.25f, 1.55f, 1.55f);
            glutSolidCube(1.0);
        glPopMatrix();

        // Pita horizontal
        glPushMatrix();
            glScalef(1.55f, 0.25f, 1.55f);
            glutSolidCube(1.0);
        glPopMatrix();

        // Tutup
        glColor3ub(255,200,230);
        glPushMatrix();
            glTranslatef(0, 0.9f, 0);
            glScalef(1.6f, 0.25f, 1.6f);
            glutSolidCube(1.0);
        glPopMatrix();

        // Pita atas
        glColor3ub(255,80,150);
        glPushMatrix();
            glTranslatef(0.25f, 1.1f, 0);
            glutSolidSphere(0.2, 14, 14);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.25f, 1.1f, 0);
            glutSolidSphere(0.2, 14, 14);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, 1.0f, 0);
            glRotatef(-90,1,0,0);
            glutSolidCone(0.1, 0.3, 12, 5);
        glPopMatrix();

        glPopMatrix();
    }

    // ================= KUE ULANG TAHUN =================
    GLfloat cakeSpec[] = {0.08f, 0.08f, 0.08f, 1};
    GLfloat cakeShine[] = {6};
    glMaterialfv(GL_FRONT, GL_SPECULAR, cakeSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, cakeShine);

    GLUquadric* quad = gluNewQuadric();

    glPushMatrix();
        glTranslatef(0, -2.8f, 0);

        // TINGKAT 1
        glColor3ub(160, 82, 45);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            gluCylinder(quad, 6.5, 6.5, 3, 40, 40);
        glPopMatrix();

        glColor3ub(255, 248, 240);
        glPushMatrix();
            glTranslatef(0, 3, 0);
            glScalef(7, 0.7, 7);
            glutSolidSphere(1, 30, 30);
        glPopMatrix();

        // TINGKAT 2
        glTranslatef(0, 3.6f, 0);
        glColor3ub(255, 182, 193);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            gluCylinder(quad, 4.5, 4.5, 2.5, 40, 40);
        glPopMatrix();

        glColor3ub(255, 250, 250);
        glPushMatrix();
            glTranslatef(0, 2.5, 0);
            glScalef(5, 0.6, 5);
            glutSolidSphere(1, 30, 30);
        glPopMatrix();

        // TINGKAT 3
        glTranslatef(0, 3.0f, 0);
        glColor3ub(173, 216, 230);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            gluCylinder(quad, 3, 3, 2, 40, 40);
        glPopMatrix();

        glColor3ub(255, 255, 255);
        glPushMatrix();
            glTranslatef(0, 2, 0);
            glScalef(3.6, 0.5, 3.6);
            glutSolidSphere(1, 30, 30);
        glPopMatrix();

        // LILIN
        for (int i = 0; i < 5; i++) {
            GLfloat candleSpec[] = {0.6f, 0.6f, 0.3f, 1};
            GLfloat candleShine[] = {50};
            glMaterialfv(GL_FRONT, GL_SPECULAR, candleSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, candleShine);

            float a = i * (360.0f / 5) * PI / 180.0f;
            float x = cos(a) * 1.5f;
            float z = sin(a) * 1.5f;

            glColor3ub(255, 255, 0);
            glPushMatrix();
                glTranslatef(x, 2.5f, z);
                glScalef(0.3f, 1.8f, 0.3f);
                glutSolidCube(1);
            glPopMatrix();

            glColor3ub(255, 100, 0);
            glPushMatrix();
                glTranslatef(x, 3.5f, z);
                glutSolidSphere(0.25f, 20, 20);
            glPopMatrix();
        }

    glPopMatrix();
    gluDeleteQuadric(quad);
    glDisable(GL_LIGHTING);


    glEnable(GL_LIGHTING); 
    
    drawLEDWave(-45, 49.9f, 45, 49.9f);
    drawLEDWave(-45, -49.9f, 45, -49.9f);
    drawLEDWave(-49.9f, -45, -49.9f, 45);
    drawLEDWave(49.9f, -45, 49.9f, 45);

    // ================= BALON (SUDAH DITAMBAHKAN PITA) =================
    glEnable(GL_LIGHTING);

    GLfloat balloonSpec[] = {0.8f, 0.8f, 0.8f, 1};
    GLfloat balloonShine[] = {80};
    glMaterialfv(GL_FRONT, GL_SPECULAR, balloonSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, balloonShine);

    float bx[4] = { -25, 25, -20, 20 };
    float bz[4] = { -20, -20, 25, 25 };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(bx[i], 8, bz[i]);

        // 1. Badan Balon
        glColor3ub(255, 80, 120);
        glPushMatrix();
            glTranslatef(0, 3.5f, 0);
            glScalef(1, 1.3f, 1);
            glutSolidSphere(2, 30, 30);
        glPopMatrix();

        // 2. Leher Balon
        GLUquadric* q = gluNewQuadric();
        glColor3ub(220, 60, 100);
        glPushMatrix();
            glTranslatef(0, 1.8f, 0);
            glRotatef(-90, 1, 0, 0);
            gluCylinder(q, 0.4, 0.4, 1.2, 20, 10);
        glPopMatrix();

        // 3. Cincin Mulut Balon
        glColor3ub(200, 40, 80);
        glPushMatrix();
            glTranslatef(0, 1.6f, 0);
            glutSolidTorus(0.15, 0.45, 16, 24);
        glPopMatrix();

        // 4. PITA PENGHIAS (OBJEK BARU)
        glColor3ub(255, 215, 215); // Warna Emas
        glPushMatrix();
            glTranslatef(0, 0.5f, 0.2f); // Posisi
            glScalef(2, 1.2f, 2);
            
            // Simpul Tengah
            glPushMatrix();
            glTranslated(0, 0.2, 0);
            glutSolidSphere(0.2, 10, 10);
            glPopMatrix();
            
            // Sayap Kiri
            glPushMatrix();
                glTranslatef(-0.35f, 0.1f, 0); glRotatef(35, 0, 0, 1);
                glScalef(0.6f, 0.3f, 0.1f); glutSolidSphere(1.0, 10, 10);
            glPopMatrix();
            
            // Sayap Kanan
            glPushMatrix();
                glTranslatef(0.35f, 0.1f, 0); glRotatef(-35, 0, 0, 1);
                glScalef(0.6f, 0.3f, 0.1f); glutSolidSphere(1.0, 10, 10);
            glPopMatrix();
            
                        // Sayap Kiri atas
            glPushMatrix();
                glTranslatef(-0.35f, 0.4f, 0); glRotatef(-35, 0, 0, 1);
                glScalef(0.6f, 0.3f, 0.1f); glutSolidSphere(1.0, 10, 10);
            glPopMatrix();
            
            // Sayap Kanan atas
            glPushMatrix();
                glTranslatef(0.35f, 0.4f, 0); glRotatef(35, 0, 0, 1);
                glScalef(0.6f, 0.3f, 0.1f); glutSolidSphere(1.0, 10, 10);
            glPopMatrix();
            
            // Untaian Kiri
            glPushMatrix();
                glTranslatef(0.2f, -0.2f, 0); glRotatef(15, 0, 0, 1);
                glScalef(0.15f, 0.8f, 0.05f); glutSolidCube(1.0);
            glPopMatrix();
            
            // Untaian Kanan
            glPushMatrix();
                glTranslatef(-0.2f, -0.2f, 0); glRotatef(-15, 0, 0, 1);
                glScalef(0.15f, 0.8f, 0.05f); glutSolidCube(1.0);
            glPopMatrix();
        glPopMatrix();
        // ======================================

        // 5. Tali Balon
        glDisable(GL_LIGHTING);
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_LINES);
            glVertex3f(0, 1.4f, 0);
            glVertex3f(0, -4, 0);
        glEnd();
        glEnable(GL_LIGHTING);

        gluDeleteQuadric(q);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// ================= LOADING TIMER =============
void loadingTimer(int) {
    if (loadingProgress < 100) {
        loadingProgress += 2.0f;
        glutPostRedisplay();
        glutTimerFunc(40, loadingTimer, 0);
    } else {
        isLoading = false;
    }
}

// ================= INPUT =====================
void keyboard(unsigned char key, int, int) {
    keys[key] = true;
    if (key == 27) exit(0);

    // Lighting Controls
    if (key == 'l' || key == 'L') lightingEnabled = !lightingEnabled;
    if (key == '1') lightMode = 1;
    if (key == '2') lightMode = 2;
    if (key == '3') lightMode = 3;
    if (key == '4') lightMode = 4;

    if (key == 'y' || key == 'Y') isDirectional = !isDirectional;
    if (key == 'h' || key == 'H') isSpotlight = !isSpotlight;

    if (key == 'j' || key == 'J') {
        spotCutoff -= 2.0f;
        if (spotCutoff < 0) spotCutoff = 0;
    }
    if (key == 'k' || key == 'K') {
        spotCutoff += 2.0f;
        if (spotCutoff > 90) spotCutoff = 90;
    }

    if (key == 'n' || key == 'N') linearAttenuation += 0.05f;
    if (key == 'm' || key == 'M') {
        linearAttenuation -= 0.05f;
        if (linearAttenuation < 0) linearAttenuation = 0;
    }

    if (key == 'i' || key == 'I') isShiny = !isShiny;
}
void keyboardUp(unsigned char key, int, int) { keys[key] = false; }

void mouseMotion(int x, int y) {
    int cx = winW / 2, cy = winH / 2;
    // Cek agar mouse tidak melompat terlalu jauh di frame pertama
    static bool firstMouse = true;
    if(firstMouse) { glutWarpPointer(cx, cy); firstMouse = false; return; }

    camYaw += (x - cx) * MOUSE_SENS;
    camPitch += (y - cy) * MOUSE_SENS;
    if (camPitch > 89) camPitch = 89;
    if (camPitch < -89) camPitch = -89;
    
    if(x != cx || y != cy) glutWarpPointer(cx, cy);
}

void idle() {
    if (!isLoading) updateCamera();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
}

// ================= MAIN ======================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Opening Loading + Party Scene");
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE); // Menyembunyikan kursor agar tidak mengganggu kamera

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(mouseMotion); // Tambahkan ini agar tetap jalan saat klik tahan
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    glutTimerFunc(40, loadingTimer, 0);
    glutWarpPointer(winW / 2, winH / 2);

    glutMainLoop();
    return 0;
}