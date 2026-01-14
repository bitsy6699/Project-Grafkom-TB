#include <GLUT/glut.h>
#include <stdlib.h>

float rotationangle = 0.0;
bool hidden = false;

void hiddencarte();

void drawCartesius(){
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-50.0, 0.0, 0.0);
	glVertex3f(50.0, 0.0, 0.0);
	
	glVertex3f(0.0, -50.0, 0.0);
	glVertex3f(0.0, 50.0, 0.0);
	
	glVertex3f(0.0, 0.0, -50.0);
	glVertex3f(0.0, 0.0, 50.0);
	glEnd();
}

// Fungsi helper untuk menggambar balok warnawarni
void drawBox(float width, float height, float depth, float r, float g, float b) {
    glColor3f(r, g, b);
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Kursi Kayu
void drawChair() {
    glColor3f(0.6f, 0.4f, 0.2f); // Kayu Coklat
    
    // Alas Duduk (Lebih rendah lagi)
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f); // Was 0.35
    glScalef(1.2f, 0.1f, 1.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Kaki Kursi (Lebih Lebar / Panjang ke samping)
    float legX[] = {0.7f, -0.7f}; // Was 0.5 (Lebih lebar dari alas)
    float legZ[] = {0.7f, -0.7f}; // Was 0.5
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            glPushMatrix();
            glTranslatef(legX[i], 0.1f, legZ[j]); // Center Y at 0.1
            glScalef(0.15f, 0.2f, 0.15f); // Height 0.2
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
    
    // Sandaran
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, -0.55f); // Posisi menyesuaikan alas (0.25 + offset)
    glScalef(1.2f, 1.2f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawCharacter() {
    // Geser seluruh karakter ke posisi duduk (di atas kursi)
    // Kursi sangat rendah (0.25). Hip adjust ke -0.05.
    
    glPushMatrix();
    glTranslatef(0.0f, -0.05f, 0.0f); // Was 0.05

    // 1. KEPALA (Skin Color)
    glPushMatrix();
    glTranslatef(0.0f, 1.6f, 0.0f); 
    drawBox(0.8f, 0.8f, 0.8f, 0.96f, 0.80f, 0.69f); 
    
    // Mata
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(-0.2f, 0.1f, 0.41f); glScalef(0.1f, 0.1f, 0.05f); glutSolidCube(1.0); glPopMatrix();
    glPushMatrix(); glTranslatef(0.2f, 0.1f, 0.41f); glScalef(0.1f, 0.1f, 0.05f); glutSolidCube(1.0); glPopMatrix();
    
    // 1.5 TOPI RIMBA
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f); 
    drawBox(1.2f, 0.1f, 1.2f, 0.45f, 0.30f, 0.15f); // Brim
    glTranslatef(0.0f, 0.2f, 0.0f);
    drawBox(0.8f, 0.3f, 0.8f, 0.45f, 0.30f, 0.15f); // Crown
    glColor3f(0.3f, 0.2f, 0.1f); glScalef(0.82f, 0.1f, 0.82f); glutSolidCube(1.0); // Pita
    glPopMatrix();
    glPopMatrix(); // End Kepala

    // 2. BADAN (Kemeja Merah)
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, -0.1f); 
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f); // Senderan santai (Lean back)
    drawBox(1.0f, 1.2f, 0.5f, 0.8f, 0.1f, 0.1f); 
    // Kancing
    glColor3f(1.0f, 1.0f, 1.0f);
    for(float i=0.2f; i>-0.4f; i-=0.3f) {
        glPushMatrix(); glTranslatef(0.0f, i, 0.26f); glScalef(0.05f, 0.05f, 0.05f); glutSolidCube(1.0); glPopMatrix();
    }
    glPopMatrix();

    // 3. LENGAN (Ditaruh di paha)
    // Lengan Kanan
    glPushMatrix();
    glTranslatef(0.75f, 0.6f, -0.1f);
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f); // Ikut lean body
    drawBox(0.4f, 1.0f, 0.5f, 0.8f, 0.1f, 0.1f); // Lengan atas
    
    glTranslatef(0.0f, -0.5f, 0.0f); // Siku
    glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Tekuk ke depan (ke arah paha)
    glRotatef(-10.0f, 0.0f, 0.0f, 1.0f); // Masuk dikit
    glTranslatef(0.0f, -0.4f, 0.0f); // Lengan bawah
    drawBox(0.35f, 0.8f, 0.4f, 0.8f, 0.1f, 0.1f); 
    
    glTranslatef(0.0f, -0.5f, 0.0f); // Tangan
    drawBox(0.35f, 0.3f, 0.4f, 0.96f, 0.80f, 0.69f); 
    glPopMatrix();

    // Lengan Kiri
    glPushMatrix();
    glTranslatef(-0.75f, 0.6f, -0.1f);
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f); // Ikut lean body
    drawBox(0.4f, 1.0f, 0.5f, 0.8f, 0.1f, 0.1f); // Lengan atas
    
    glTranslatef(0.0f, -0.5f, 0.0f); // Siku
    glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Tekuk ke depan
    glRotatef(10.0f, 0.0f, 0.0f, 1.0f); // Masuk dikit
    glTranslatef(0.0f, -0.4f, 0.0f); // Lengan bawah
    drawBox(0.35f, 0.8f, 0.4f, 0.8f, 0.1f, 0.1f);
    
    glTranslatef(0.0f, -0.5f, 0.0f); // Tangan
    drawBox(0.35f, 0.3f, 0.4f, 0.96f, 0.80f, 0.69f);
    glPopMatrix();

    // 4. KAKI (POSE DUDUK BIASA)
    // Kaki Kiri
    glPushMatrix();
    glTranslatef(-0.25f, 0.0f, 0.0f); // Pangkal paha Kiri (Normal)
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f); // Lurus ke depan
    
    // Paha Kiri
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.6f); 
    drawBox(0.40f, 0.40f, 1.2f, 0.55f, 0.40f, 0.25f); 
    glPopMatrix();

    // Betis Kiri
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 1.1f); // Lutut
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f); // Lurus ke bawah
    glTranslatef(0.0f, -0.5f, 0.0f); 
    drawBox(0.35f, 1.2f, 0.4f, 0.55f, 0.40f, 0.25f); 
    
    // Sepatu Kiri
    glTranslatef(0.0f, -0.7f, 0.1f);
    drawBox(0.4f, 0.3f, 0.6f, 0.1f, 0.1f, 0.1f);
    glPopMatrix();
    glPopMatrix(); // End Kaki Kiri

    // Kaki Kanan
    glPushMatrix();
    glTranslatef(0.25f, 0.0f, 0.0f); // Pangkal paha Kanan (Normal)
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f); // Lurus ke depan
    
    // Paha Kanan
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.6f); 
    drawBox(0.40f, 0.40f, 1.2f, 0.55f, 0.40f, 0.25f); 
    glPopMatrix();

    // Betis Kanan
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 1.1f); // Lutut
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f); 
    glTranslatef(0.0f, -0.5f, 0.0f); 
    drawBox(0.35f, 1.2f, 0.4f, 0.55f, 0.40f, 0.25f); 
    
    // Sepatu Kanan
    glTranslatef(0.0f, -0.7f, 0.1f);
    drawBox(0.4f, 0.3f, 0.6f, 0.1f, 0.1f, 0.1f);
    glPopMatrix();
    glPopMatrix(); // End Kaki Kanan

    glPopMatrix(); // End Character Translation
}

void monitor(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glRotatef(rotationangle, 0, 1, 0); 
	hiddencarte();
	
    drawChair();     // Gambar Kursi dulu
    drawCharacter(); // Gambar Karakter (sudah diposisikan duduk)

	glPopMatrix();
	
	glutSwapBuffers();
	
	rotationangle += 1.0; 
    if (rotationangle > 360) rotationangle -= 360;
}

void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init3DProjection(void){
	glutCreateWindow("Traveler Character");
	glutDisplayFunc(monitor);
	glClearColor(1.0, 1.0, 1.0, 1.0); // Background Putih
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
    // Ganti ke Perspective supaya lebih bagus 3D-nya, atau sesuaikan Ortho
    // Karena karakter lumayan tinggi (sekitar 4 unit total), kita perbesar ortho
	glOrtho(-3.0, 3.0, -3.0, 3.0, -50.0, 50.0);
    
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Setup pencahayaan sederhana supaya baloknya ada shading
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat light_pos[] = { 10.0, 10.0, 10.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
	glRotatef(15.0, 1, 0, 0); // Sedikit nunduk kameranya
}

void mykeyboard(unsigned char key, int x, int y){
	switch (key){
		case 'c':
			hidden = !hidden;
			break;
        case 27: // ESC
            exit(0);
            break;
	}
}

void hiddencarte(){
	if(hidden){
		drawCartesius();
	}
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(200, 0);
	init3DProjection();
	glutKeyboardFunc(mykeyboard);
    glutTimerFunc(0, timer, 0); // Pakai timer untuk animasi smooth
	glutMainLoop();
	return 0;
}
