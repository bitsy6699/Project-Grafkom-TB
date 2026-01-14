#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

//konfigurasi layar
int w = 1024;
int h = 768;

//variabel interaksi
float busMove = 12.0f;      //translate bus
float busRotation = 0.0f;   //rotate bus
float treeScale = 1.0f;     //skala besar/kecil pohon

//variabel kamera
float camAngle = 0.4f;     //horizontal
float camPitch = 0.0f;      //vertical (look up/down)
float cameraY = 5.0f;       //tinggi kamera (fixed or controlled separately)
float camDist = 45.0f;      //jarak zoom (unused in FPS)
float viewX = 0.0f;         //posisi kamera X
float viewZ = 20.0f;        //posisi kamera Z

//anim alam
float waterAnim = 0.0f;     
float fireAnim = 0.0f;      

//kontrol mouse
int lastMouseX = -1;
int lastMouseY = -1;
int isMouseDragging = 0;

//Input State untuk Smooth Movement
bool keyState[256]; // Array untuk menyimpan status tombol (ditekan/tidak)

//sistem cuaca
int isSun = 1;             
int weatherMode = 1;      

//konfigurasi partikel (Hujan/Salju)
#define MAX_PARTICLES 300
float particlePos[MAX_PARTICLES][3];
float particleSpeed[MAX_PARTICLES];

//konfigurasi Bintang
#define NUM_STARS 300
float starPos[NUM_STARS][3];

//warna Bus
float busColors[4][3] = {
    {0.7f, 0.5f, 0.2f},   
    {0.15f, 0.06f, 0.1f}, 
    {1.0f, 1.0f, 1.0f},   
    {0.7f, 0.3f, 0.7f}    
};

//inisialisasi data
void initRandomObjects() {
    srand(time(NULL));
    
    //partikel cuaca
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particlePos[i][0] = (rand() % 140) - 70;
        particlePos[i][1] = (rand() % 50);
        particlePos[i][2] = (rand() % 140) - 70;
        particleSpeed[i] = 0.05 + ((rand() % 10) / 100.0);
    }

    //bintang (Posisi Rendah/Horizon)
    for (int i = 0; i < NUM_STARS; i++) {
        starPos[i][0] = (rand() % 300) - 150; 
        starPos[i][1] = 20 + (rand() % 50); //tinggi
        starPos[i][2] = (rand() % 300) - 150;
    }
}

void drawStars() {
    if (isSun) return; //bintang cuma ada pas malam
    
    glDisable(GL_LIGHTING); 
    glDisable(GL_FOG); //matikan kabut
    
    glColor3f(1.0f, 1.0f, 0.9f);
    glPointSize(7.0f);
    
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_STARS; i++) { 
        glVertex3f(starPos[i][0], starPos[i][1], starPos[i][2]); 
    }
    glEnd();
    
    glPointSize(1.0f);
    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
}

void drawWeatherParticles() {
    glDisable(GL_LIGHTING);
    
    if (weatherMode == 1) { 
        //mode salju
        glColor3f(1.0, 1.0, 1.0);
        for (int i = 0; i < MAX_PARTICLES; i++) {
            glPushMatrix(); 
                glTranslatef(particlePos[i][0], particlePos[i][1], particlePos[i][2]); 
                glutSolidSphere(0.25, 8, 8); 
            glPopMatrix();
        }
    } else { 
        //Mode Hujan
        glColor3f(0.6f, 0.7f, 0.9f); 
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        for (int i = 0; i < MAX_PARTICLES; i++) {
            glVertex3f(particlePos[i][0], particlePos[i][1], particlePos[i][2]);
            glVertex3f(particlePos[i][0], particlePos[i][1] - 2.5f, particlePos[i][2]);
        }
        glEnd(); 
        glLineWidth(1.0f);
    }
    glEnable(GL_LIGHTING);
}

void drawTree(float x, float z) {
    glPushMatrix(); 
    glTranslatef(x, 0.0, z); 
    
    float finalScale = 4.0f * treeScale; 
    glScalef(finalScale, finalScale, finalScale);
    
    //batang Pohon
    glColor3f(0.4, 0.2, 0.1); 
    glPushMatrix(); 
        glRotatef(-90, 1, 0, 0); 
        GLUquadric* q = gluNewQuadric(); 
        gluCylinder(q, 0.05, 0.05, 0.3, 12, 1); 
    glPopMatrix();
    
    //daun
    glColor3f(0.0, 0.3, 0.1); 
    for(int i=0; i<3; i++) { 
        glPushMatrix(); 
            glTranslatef(0, 0.2 + (i*0.2), 0); 
            glRotatef(-90, 1, 0, 0); 
            glutSolidCone(0.3, 0.6, 12, 1); 
        glPopMatrix(); 
    }
    glPopMatrix();
}

void drawEnvironment() {
    float size = 200.0f; 
    float radiusHole = 7.0f; 
    int segments = 64;

    //gambar Tanah
    if (isSun) glColor3f(0.6f, 0.85f, 1.0f); 
    else glColor3f(0.3f, 0.3f, 0.35f);

    glBegin(GL_QUAD_STRIP); 
    for (int i = 0; i <= segments; i++) { 
        float angle = 2.0f * 3.14159f * (float)i / segments; 
        float x = cos(angle); 
        float z = sin(angle); 
        glNormal3f(0, 1, 0); 
        glVertex3f(x * size, 0, z * size); 
        glVertex3f(x * radiusHole, 0, z * radiusHole); 
    } 
    glEnd();
    
    //gambar Air
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (isSun) glColor4f(0.0f, 0.2f, 0.5f, 0.8f); 
    else glColor4f(0.0f, 0.1f, 0.2f, 0.9f);
    
    glPushMatrix(); 
        glTranslatef(0, -0.1f + sin(waterAnim) * 0.08f, 0); 
        glBegin(GL_TRIANGLE_FAN); 
            glVertex3f(0, 0, 0); 
            for (int i = 0; i <= segments; i++) { 
                float angle = 2.0f * 3.14159f * (float)i / segments; 
                glVertex3f(cos(angle) * radiusHole, 0, sin(angle) * radiusHole); 
            } 
        glEnd(); 
    glPopMatrix(); 
    glDisable(GL_BLEND);
    
    //pohon melingkar
    for (int i = 0; i < 40; i++) { 
        float angle = i * (2.0f * 3.14159f / 40); 
        drawTree(cos(angle) * 30.0f, sin(angle) * 30.0f); 
        drawTree(cos(angle + 0.5f) * 25.0f, sin(angle + 0.5f) * 25.0f); 
        drawTree(cos(angle + 0.6f) * 20.0f, sin(angle + 0.6f) * 20.0f); 
    }
}

void drawBonfire(float x, float z) {
    glPushMatrix(); 
    glTranslatef(x, 0.0f, z);
    
    //kayu bakar
    glColor3f(0.35f, 0.2f, 0.1f); 
    for(int i=0; i<3; i++) { 
        glPushMatrix(); 
            glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f); 
            glTranslatef(0.6f, 0.6f, 0.0f); 
            glRotatef(-70.0f, 0.0f, 0.0f, 1.0f); 
            glScalef(2.5f, 0.25f, 0.25f); 
            glutSolidCube(1.0f); 
        glPopMatrix(); 
    }
    
    //api di malam
    if (!isSun) {
        float flicker = (sin(fireAnim) + 1.2f) * 0.1f; 
        glDisable(GL_LIGHTING); 
        
        //api layer 1
        glColor3f(0.9f, 0.1f, 0.0f); 
        glPushMatrix(); 
        glTranslatef(0, 0.6, 0); 
        glScalef(1.2+flicker, 1.8, 1.2+flicker); 
        glutSolidSphere(0.5, 12, 12); 
        glPopMatrix();
        
        //api layer 2
        glColor3f(1.0f, 0.55f, 0.1f); 
        glPushMatrix(); 
        glTranslatef(0, 1.5, 0); 
        glScalef(0.9+flicker, 1.6, 0.9+flicker); 
        glutSolidSphere(0.45, 12, 12); 
        glPopMatrix();
        
        //api layer 3 
        glColor3f(1.0f, 0.9f, 0.3f); 
        glPushMatrix(); 
        glTranslatef(0, 2.4, 0); 
        glScalef(0.5+flicker, 1.2, 0.5+flicker); 
        glutSolidSphere(0.3, 12, 12); 
        glPopMatrix();
        
        glEnable(GL_LIGHTING); 
    }
    glPopMatrix();
}

void drawSunMoon() {
    glPushMatrix(); 
    glTranslatef(0.0, 20.0, 0.0); 
    glDisable(GL_LIGHTING); 
    
    if (isSun) { 
        glColor3f(1.0, 1.0, 0.6); //matahari
        glutSolidSphere(2.5, 40, 40); 
    } else { 
        glColor3f(0.8, 0.8, 1.0); //bulan
        glutSolidSphere(2.5, 40, 40); 
    }
    
    glEnable(GL_LIGHTING); 
    glPopMatrix();
}

void drawTent(float x, float z, float rot, int colorType) {
    glPushMatrix(); 
    glTranslatef(x, 0.0f, z); 
    glRotatef(rot, 0.0f, 1.0f, 0.0f); 
    glScalef(3.5f, 3.5f, 4.5f); 
    
    float r, g, b, r2, g2, b2; 
    
    //warna tenda
    if (colorType == 0) { r=0.1f; g=0.1f; b=0.1f; r2=0.0f; g2=0.0f; b2=0.0f; } 
    else if (colorType == 1) { r=1.0f; g=0.5f; b=0.8f; r2=0.8f; g2=0.3f; b2=0.6f; } 
    else { r=1.0f; g=0.5f; b=0.0f; r2=0.9f; g2=0.4f; b2=0.0f; }
    
    //body tenda
    glColor3f(r, g, b); 
    glBegin(GL_QUADS); 
        glNormal3f(-1,1,0); 
        glVertex3f(-0.5,0,-0.5); 
        glVertex3f(-0.5,0,0.5); 
        glVertex3f(0,0.7,0.5); 
        glVertex3f(0,0.7,-0.5); 
    glEnd();
    
    glColor3f(r2, g2, b2); 
    glBegin(GL_QUADS); 
        glNormal3f(1,1,0); 
        glVertex3f(0.5,0,0.5); 
        glVertex3f(0.5,0,-0.5); 
        glVertex3f(0,0.7,-0.5); 
        glVertex3f(0,0.7,0.5); 
    glEnd();
    // Segitiga Depan/Belakang
    glColor3f(0.3f, 0.1f, 0.0f); 
    glBegin(GL_TRIANGLES); 
        glNormal3f(0,0,1); 
        glVertex3f(-0.5,0,0.5); 
        glVertex3f(0.5,0,0.5); 
        glVertex3f(0,0.7,0.5); 
    glEnd();
    
    glColor3f(r, g, b); 
    glBegin(GL_TRIANGLES); 
        glNormal3f(0,0,-1); 
        glVertex3f(0.5,0,-0.5); 
        glVertex3f(-0.5,0,-0.5); 
        glVertex3f(0,0.7,-0.5); 
    glEnd();
    
    glPopMatrix();
}

// bus
void drawWheel(float x, float y, float z, bool isSpare = false) {
    glPushMatrix(); 

    glTranslatef(x, y, z);
    if (isSpare) glScalef(0.8f, 0.8f, 0.8f); 
    //ban
    glColor3f(0.05f, 0.05f, 0.05f); 
    glRotatef(180, 0.0f, 1.0f, 0.0f); 
    glutSolidTorus(0.15, 0.45, 12, 24);
    //pelg
    glColor3f(0.5f, 0.5f, 0.5f); 
    glutSolidSphere(0.2, 10, 10);
    glPopMatrix();
}

void drawRoofCargo() {
    //rak besi
    glColor3f(0.2f, 0.2f, 0.2f); 
    glPushMatrix(); 
        glTranslatef(0.0f, 1.15f, 0.0f); 
        glScalef(2.5f, 0.1f, 1.6f); 
        glutWireCube(1.0f); 
    glPopMatrix();
    //koper
    glColor3f(0.4f, 0.3f, 0.1f); 
    glPushMatrix(); 
        glTranslatef(-0.6f, 1.3f, 0.3f); 
        glScalef(0.8f, 0.5f, 0.7f); 
        glutSolidCube(1.0f); 
    glPopMatrix();
    //kantong
    glColor3f(0.8f, 0.1f, 0.1f); 
    glPushMatrix(); 
        glTranslatef(0.5f, 1.3f, -0.4f); 
        glScalef(0.4f, 0.6f, 0.3f); 
        glutSolidCube(1.0f); 
    glPopMatrix();
    //ban serep
    drawWheel(0.5f, 1.3f, 0.4f, true);
}

void drawCampingBus(int idx) {
    glPushMatrix();
    glRotatef(busRotation, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 1.2f, 0.0f);
    //body utama
    glColor3f(busColors[idx][0], busColors[idx][1], busColors[idx][2]);
    glPushMatrix(); 
        glScalef(4.0f, 1.5f, 2.0f); 
        glutSolidCube(1.0f); 
    glPopMatrix();
    //fender handap
    glColor3f(1.0f, 0.7f, 0.0f);
    glPushMatrix(); 
        glScalef(4.02f, 0.15f, 2.02f); 
        glutSolidCube(1.0f); 
    glPopMatrix();
    //luhur mobil
    glColor3f(0.9f, 0.9f, 0.9f);
    glPushMatrix(); 
        glTranslatef(0.0f, 0.9f, 0.0f); 
        glScalef(3.2f, 0.4f, 1.8f); 
        glutSolidCube(1.0f); 
    glPopMatrix();
    //aksesoris
    drawRoofCargo();
    //lampu kaka
    glDisable(GL_LIGHTING); 
    glColor3f(1.0f, 0.9f, 0.6f); 
    glPushMatrix(); 
    glTranslatef(2.0f, -0.2f, 0.6f); 
    glutSolidSphere(0.25f, 12, 12); 
    
    glPopMatrix();
    
    glPushMatrix(); 
    glTranslatef(2.0f, -0.2f, -0.6f); 
    glutSolidSphere(0.25f, 12, 12); 
    glPopMatrix();
    glEnable(GL_LIGHTING); 

    //bagasi
    //engsel
    glColor3f(0.1f, 0.1f, 0.1f); 
    glPushMatrix(); 
        glTranslatef(-2.01f, 0.2f, 0.0f); 
        glScalef(0.1f, 0.8f, 1.5f); 
        glutSolidCube(1.0f); 
    glPopMatrix();
    //gagang panto
    glPushMatrix(); 
        glTranslatef(-2.0f, 0.75f, 0.0f); 
        glRotatef(-110.0f, 0.0f, 0.0f, 1.0f); 
        glTranslatef(-0.05f, -0.4f, 0.0f);    
        //luarna
        glColor3f(busColors[idx][0], busColors[idx][1], busColors[idx][2]); 
        glPushMatrix(); 
        glScalef(0.1f, 0.9f, 1.6f); 
        glutSolidCube(1.0f); 
        glPopMatrix();
        //jerona
        glColor3f(0.15f, 0.15f, 0.15f); 
        glPushMatrix(); 
        glTranslatef(0.06f, 0.0f, 0.0f); 
        glScalef(0.02f, 0.8f, 1.4f); 
        glutSolidCube(1.0f);
    glPopMatrix();

    //rodana
    drawWheel( 1.4f, -0.5f,  1.0f); 
    drawWheel( 1.4f, -0.5f, -1.0f);
    drawWheel(-1.4f, -0.5f,  1.0f); 
    drawWheel(-1.4f, -0.5f, -1.0f);
    
    glPopMatrix();
}

//TAMPILAN
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();
    
    //kamera
    //kamera FPS
    float dirX = sin(camAngle) * cos(camPitch);
    float dirY = sin(camPitch);
    float dirZ = -cos(camAngle) * cos(camPitch);
    
    //Posisi kamera = viewX, cameraY, viewZ
    //Target = Posisi + Arah
    gluLookAt(viewX, cameraY, viewZ, 
              viewX + dirX, cameraY + dirY, viewZ + dirZ, 
              0.0, 1.0, 0.0);
    
    //pencahayaan utama
    GLfloat light_pos0[] = { 0.0, 20.0, 0.0, 0.0 }; 
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
    
    //siang atau malam
    if (isSun) {
        //mode siang
        glClearColor(0.8, 0.9, 1.0, 1.0); 
        GLfloat fogCol[] = {0.8f, 0.9f, 1.0f, 1.0f}; 
        glFogfv(GL_FOG_COLOR, fogCol); 
        glDisable(GL_LIGHT1); 
    } else {
        //mode malam
        glClearColor(0.02, 0.02, 0.05, 1.0); 
        GLfloat fogCol[] = {0.02f, 0.02f, 0.05f, 1.0f}; 
        glFogfv(GL_FOG_COLOR, fogCol);
        
        GLfloat fireLightPos[] = { 10.0f, 3.0f, 10.0f, 1.0f }; 
        GLfloat fireLightCol[] = { 1.0f, 0.6f, 0.2f, 1.0f }; 
        glLightfv(GL_LIGHT1, GL_POSITION, fireLightPos); 
        glLightfv(GL_LIGHT1, GL_DIFFUSE, fireLightCol); 
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02f); 
        glEnable(GL_LIGHT1); 
    }

    //render obj
    drawSunMoon(); 
    drawStars(); 
    drawEnvironment(); 
    drawBonfire(10.0f, 10.0f);    
    
    drawTent(-10.0f, 10.0f, -45.0f, 0); 
    drawTent(-10.0f, -10.0f, -135.0f, 1); 
    drawTent(10.0f, -10.0f, 135.0f, 2);  
    
    for (int i = 0; i < 4; i++) { 
        glPushMatrix(); 
            glRotatef(i * 90.0f, 0.0f, 1.0f, 0.0f); 
            glTranslatef(busMove, 0.0f, 0.0f); 
            drawCampingBus(i); 
        glPopMatrix(); 
    }
    
    drawWeatherParticles(); 
    
    glutSwapBuffers();
}

void updateMovement() {
    float moveSpeed = 0.5f; // Kecepatan gerak (per-frame)

    // Forward Vector (3D)
    float dx = sin(camAngle) * cos(camPitch);
    float dy = sin(camPitch);
    float dz = -cos(camAngle) * cos(camPitch);

    // Strafe Vector (Horizontal only for stability)
    float sx = cos(camAngle);
    float sz = sin(camAngle);

    if (keyState['w']) {
        viewX += dx * moveSpeed;
        cameraY += dy * moveSpeed;
        viewZ += dz * moveSpeed;
    }
    if (keyState['s']) {
        viewX -= dx * moveSpeed;
        cameraY -= dy * moveSpeed;
        viewZ -= dz * moveSpeed;
    }
    if (keyState['a']) {
        viewX -= sx * moveSpeed;
        viewZ -= sz * moveSpeed;
    }
    if (keyState['d']) {
        viewX += sx * moveSpeed;
        viewZ += sz * moveSpeed;
    }
}

void timer(int v) {
    updateMovement(); // Update posisi setiap frame timer

    //anim hujan/salju
    for (int i = 0; i < MAX_PARTICLES; i++) {
        float speed = (weatherMode == 2) ? particleSpeed[i] * 3.0f : particleSpeed[i];
        particlePos[i][1] -= speed; 
        if (particlePos[i][1] < 0) particlePos[i][1] = 40; 
    }
    
    waterAnim += 0.08f; 
    fireAnim += 0.2f; 
    
    glutPostRedisplay(); 
    glutTimerFunc(16, timer, 0); // 60 FPS approx (1000ms / 60 = 16.6ms)
}

void keyboard(unsigned char key, int x, int y) {
    keyState[key] = true; // Set tombol sedang ditekan

    switch (key) {
        // Kontrol lain yang sifatnya toggle/sekali tekan
        case 'r': 
            treeScale += 0.1f; 
            if(treeScale > 3.0f) treeScale = 3.0f; 
            break; 
        case 't': 
            treeScale -= 0.1f; 
            if(treeScale < 0.2f) treeScale = 0.2f; 
            break; 
        case 'm': 
            isSun = !isSun; 
            break; 
        case 'n': 
            weatherMode = (weatherMode == 1) ? 2 : 1; 
            break; 
        
        case 27: 
            exit(0); 
            break; // esc
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keyState[key] = false; // Set tombol sudah dilepas
}

void special(int key, int x, int y) {
    switch (key) {
        //kontrol bus (Arrow Keys)
        case GLUT_KEY_UP:
            busMove -= 0.5f; 
            if(busMove < 9.0f) busMove = 9.0f; 
            break; 
        case GLUT_KEY_DOWN: 
            busMove += 0.5f; 
            break; 
        case GLUT_KEY_LEFT: 
            busRotation += 5.0f; 
            break; 
        case GLUT_KEY_RIGHT: 
            busRotation -= 5.0f; 
            break;
    }
    glutPostRedisplay();
}

//interaski mouse
void mouseClick(int button, int state, int x, int y) { 
    if (state == GLUT_UP) return; 
    //scroll zoom
    if (button == 3) { //scroll atas
        camDist -= 2.0f; 
        if (camDist < 5.0f) camDist = 5.0f; 
    } 
    else if (button == 4) { //scroll bawah
        camDist += 2.0f; 
        if (camDist > 100.0f) camDist = 100.0f; 
    }
    //drag cenah
    else if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) { 
        isMouseDragging = (state == GLUT_DOWN); 
        lastMouseX = x; 
        lastMouseY = y; 
    } 
    glutPostRedisplay();
}

void mouseMotion(int x, int y) { 
    if (isMouseDragging) { 
        camAngle += (x - lastMouseX) * 0.005f; 
        camPitch -= (y - lastMouseY) * 0.005f; // Invert mouse Y for intuitive pitch

        // Batas pitch supaya tidak salto (approx -89 to 89 degrees in radians)
        if (camPitch > 1.5f) camPitch = 1.5f;
        if (camPitch < -1.5f) camPitch = -1.5f;

        lastMouseX = x; 
        lastMouseY = y; 
        glutPostRedisplay(); 
    } 
}

//MAIN PROGRAM
void init() { 
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 
    glEnable(GL_COLOR_MATERIAL); 
    glEnable(GL_NORMALIZE); 
    glShadeModel(GL_SMOOTH); 
    //setup fog
    glEnable(GL_FOG); 
    glFogi(GL_FOG_MODE, GL_EXP2); 
    glFogf(GL_FOG_DENSITY, 0.01f); 
    
    initRandomObjects(); 
}

void reshape(int w1, int h1) { 
    glViewport(0, 0, w1, h1); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0, (float)w1/h1, 1.0, 500.0); 
    glMatrixMode(GL_MODELVIEW); 
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w, h); 
    glutCreateWindow("TB Grafika Komputer - Kel 9");
    
    init();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 
    glutKeyboardFunc(keyboard); 
    glutKeyboardUpFunc(keyboardUp); // Register fungsi saat tombol dilepas
    glutSpecialFunc(special); 
    glutMouseFunc(mouseClick); 
    glutMotionFunc(mouseMotion); 
    glutTimerFunc(20, timer, 0);
    
    glutMainLoop(); 
    return 0;
}