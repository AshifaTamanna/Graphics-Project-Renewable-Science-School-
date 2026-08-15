#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>

// ---------- Global Variables ----------
float cloudX = 0.0f;
const int CLOUD_COUNT = 8;
const float CLOUD_GAP = 20.0f;
float sunAngle = 0.0f;
float busX = 110.0f;
float busOppositeX = -60.0f;
bool isNight = false;
const int STAR_COUNT = 80;
float currentSpeed = 0.25f;
float starX[STAR_COUNT];
float starY[STAR_COUNT];



void drawRectangle(float x, float y, float w, float h,
                   float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}


void drawCircle(float cx, float cy, float r,
                float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1416f / 180.0f;
        glVertex2f(cx + r * cos(angle),
                   cy + r * sin(angle));
    }
    glEnd();
}
void mouseControl(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            currentSpeed = 1.0f;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            currentSpeed = 0.0f;
        }
    }
}
void drawSun() {
    glPushMatrix();
    glTranslatef(75, 90, 0);

    if (isNight) {
        drawCircle(0, 0, 4.5f, 0.9f, 0.9f, 0.9f); // moon
    } else {
        glRotatef(sunAngle, 0, 0, 1);
        glColor3f(1.0f, 0.9f, 0.2f);
        glBegin(GL_LINES);
        for (int i = 0; i < 360; i += 20) {
            float a = i * 3.1416f / 180.0f;
            glVertex2f(0, 0);
            glVertex2f(6 * cos(a), 6 * sin(a));
        }
        glEnd();
        drawCircle(0, 0, 4.5f, 1.0f, 0.85f, 0.0f);
    }
    glPopMatrix();
}

// ---------- Draw Cloud Shape ----------
void drawCloudShape() {
    drawCircle(0, 0, 3,   1.0f, 1.0f, 1.0f);
    drawCircle(4, 1, 3.5, 1.0f, 1.0f, 1.0f);
    drawCircle(8, 0, 3,   1.0f, 1.0f, 1.0f);
    drawCircle(4, -1, 4,  1.0f, 1.0f, 1.0f);
}
// ---------- Playground (FULL X-AXIS WIDTH) ----------
void drawPlayground() {
    glColor3f(0.2f, 0.7f, 0.2f);

    glBegin(GL_QUADS);
        glVertex2f(0, 18);     // LEFT edge
        glVertex2f(100, 18);   // RIGHT edge
        glVertex2f(100, 45);   // TOP
        glVertex2f(0, 45);     // LEFT edge
    glEnd();

    // Top border (thicker line)
    drawRectangle(0, 44.0f, 100, 2.0f,
                  0.8f, 0.8f, 0.8f);
}

void drawPlaygroundMarkings() {
    glColor3f(1, 1, 1); // white lines

    // Outer border
    glBegin(GL_LINE_LOOP);
        glVertex2f(25, 18);
        glVertex2f(100, 18);
        glVertex2f(100, 45);
        glVertex2f(25, 45);
    glEnd();

    // Center line
    glBegin(GL_LINES);
        glVertex2f(62.5f, 18);
        glVertex2f(62.5f, 45);
    glEnd();

    // Center circle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float a = i * 3.1416f / 180.0f;
        glVertex2f(62.5f + 5 * cos(a),
                   31.5f + 5 * sin(a));
    }
    glEnd();
}

void drawBench(float x, float y) {
    // seat
    drawRectangle(x, y, 6, 1, 0.6f, 0.3f, 0.1f);
    // legs
    drawRectangle(x + 0.5f, y - 1, 0.5f, 1, 0.4f, 0.2f, 0.1f);
    drawRectangle(x + 5.0f, y - 1, 0.5f, 1, 0.4f, 0.2f, 0.1f);
}
void drawBush(float x, float y) {

    // Bottom left
    drawCircle(x - 1.2f, y, 1.2f, 0.0f, 0.6f, 0.0f);

    // Bottom right
    drawCircle(x + 1.2f, y, 1.2f, 0.0f, 0.6f, 0.0f);

    // Top center
    drawCircle(x, y + 1.4f, 1.0f, 0.0f, 0.55f, 0.0f);
}


// ---------- Playground Fence ----------
void drawFence() {
    glColor3f(0.8f, 0.8f, 0.8f); // light gray


    // Top
    drawRectangle(25, 44.0, 75, 2.0, 0.8, 0.8, 0.8);


}
// ---------- Playground Entrance Gate ----------
void drawEntranceGate() {

    float gateX = 50.0f;   // center position
    float gateY = 18.0f;
    float gateW = 20.0f;
    float gateH = 10.0f;

    // Left pillar
    drawRectangle(gateX - gateW/2 - 1.2f, gateY,
                  1.2f, gateH,
                  0.6f, 0.6f, 0.6f);

    // Right pillar
    drawRectangle(gateX + gateW/2, gateY,
                  1.2f, gateH,
                  0.6f, 0.6f, 0.6f);

    // Top bar
    drawRectangle(gateX - gateW/2 - 1.2f,
                  gateY + gateH,
                  gateW + 2.4f, 1.2f,
                  0.5f, 0.5f, 0.5f);


}
// ---------- Gate Banner ----------
void drawGateBanner() {
    float bannerX = 50.0f;
    float bannerY = 30.5f;
    float bannerW = 22.0f;
    float bannerH = 3.5f;

    // 1. Banner background
    drawRectangle(bannerX - bannerW/2,
              bannerY,
              bannerW,
              bannerH,
              0.1f, 0.4f, 0.7f);

    // 2. Border
    glColor3f(1, 1, 1);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(bannerX - bannerW/2, bannerY);
        glVertex2f(bannerX + bannerW/2, bannerY);
        glVertex2f(bannerX + bannerW/2, bannerY + bannerH);
        glVertex2f(bannerX - bannerW/2, bannerY + bannerH);
    glEnd();

    // 3. Banner stand (small supports)
    drawRectangle(bannerX - bannerW/2 + 1.5f,
                  bannerY - 2.0f,
                  0.8f, 2.0f,
                  0.6f, 0.6f, 0.6f);
    drawRectangle(bannerX + bannerW/2 - 2.3f,
                  bannerY - 2.0f,
                  0.8f, 2.0f,
                  0.6f, 0.6f, 0.6f);

    // 4. TEXT ADDITION
    const char* schoolName = "    Renewable Science School    ";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(bannerX - 9.5f, bannerY + 1.2f);

    for (const char* c = schoolName; *c != '\0'; c++) {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
void drawStreetLight(float x, float y) {
    drawRectangle(x, y, 0.5f, 10, 0.3f,0.3f,0.3f);
    drawRectangle(x-1.5f, y+10.6f, 3, 0.8f, 0.1f,0.2f,0.4f);
    drawRectangle(x, y+9.5f, 2.5f, 0.4f, 0.4f,0.4f,0.4f);

    if (isNight) {

    drawCircle(x + 2.2f, y + 9.5f, 1.5f, 1.0f, 0.9f, 0.4f);

    drawCircle(x + 2.2f, y + 9.5f, 0.6f, 1.0f, 1.0f, 1.0f);
} else {

    drawCircle(x + 2.2f, y + 9.5f, 0.6f, 0.4f, 0.4f, 0.4f);
}
}

void drawBoy(float x, float y, float sR, float sG, float sB, float pR, float pG, float pB) {
    drawCircle(x, y + 4.5f, 1.0f, 1.0f, 0.8f, 0.6f);
    drawRectangle(x - 1.0f, y + 2.0f, 2.0f, 2.5f, sR, sG, sB);
    drawRectangle(x - 0.7f, y, 0.5f, 2.0f, pR, pG, pB);
    drawRectangle(x + 0.2f, y, 0.5f, 2.0f, pR, pG, pB);
}

void drawGirl(float x, float y, float sR, float sG, float sB, float skR, float skG, float skB) {
    drawCircle(x, y + 4.5f, 1.0f, 1.0f, 0.8f, 0.6f);

    glColor3f(skR, skG, skB);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 3.0f);
        glVertex2f(x - 1.8f, y + 0.5f);
        glVertex2f(x + 1.8f, y + 0.5f);
    glEnd();
    drawRectangle(x - 0.7f, y - 1.0f, 0.4f, 1.5f, 1.0f, 0.8f, 0.6f);
    drawRectangle(x + 0.3f, y - 1.0f, 0.4f, 1.5f, 1.0f, 0.8f, 0.6f);
}
// ---------- Playground Boundary Wall ----------
void drawPlaygroundWall() {
    float wallY = 18.0f;
    float wallH = 10.0f;


    drawRectangle(0, wallY, 40, wallH, 0.6f, 0.2f, 0.1f);
    drawRectangle(60, wallY, 40, wallH, 0.6f, 0.2f, 0.1f);

    glColor3f(0.4f, 0.1f, 0.05f);
    glBegin(GL_LINES);
    for(float i = wallY; i <= wallY + wallH; i += 2.0f) {
        glVertex2f(0, i); glVertex2f(40, i);
        glVertex2f(60, i); glVertex2f(100, i);
    }
    glEnd();
}
void staticBus() {
    glPushMatrix();
    glTranslatef(3.0f, 47.0f, 0.0f);

    glScalef(0.04f, 0.04f, 1.0f);
    glTranslatef(-350.0f, -610.0f, 0.0f);

    // --- Bus Body ---
    glBegin(GL_POLYGON);
    glColor3f(0.945f, 0.796f, 0.157f);
    glVertex2f(350, 610); glVertex2f(700, 610);
    glVertex2f(700, 750); glVertex2f(390, 750);
    glVertex2f(350, 700);
    glEnd();

    // Windows
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.8f, 0.95f);
    glVertex2f(360, 700); glVertex2f(395, 740);
    glVertex2f(440, 740); glVertex2f(440, 700);
    glEnd();

    for (float x = 465; x <= 650; x += 85) {
        drawRectangle(x, 700, 55, 40, 0.6f, 0.8f, 0.95f);
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, 700); glVertex2f(x, 740);
        glVertex2f(x + 55, 740); glVertex2f(x + 55, 700);
        glEnd();
    }

    // Wheels
    drawCircle(430, 610, 28, 0.0f, 0.0f, 0.0f);
    drawCircle(430, 610, 20, 0.7f, 0.7f, 0.7f);
    drawCircle(630, 610, 28, 0.0f, 0.0f, 0.0f);
    drawCircle(630, 610, 20, 0.7f, 0.7f, 0.7f);

    // Text
    const char* label = "STUDENT BUS";
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(450, 655);
    for (const char* c = label; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    }

    glPopMatrix();
}
void bus() {
    glPushMatrix();

    glTranslatef(busX, 0.0f, 0.0f);

    glTranslatef(15.0f, 2.0f, 0.0f);
    glScalef(0.04f, 0.04f, 1.0f);
    glTranslatef(-350.0f, -610.0f, 0.0f);

    // Bus Body
    glBegin(GL_POLYGON);
    glColor3f(0.945f, 0.796f, 0.157f);
    glVertex2f(350, 610); glVertex2f(700, 610);
    glVertex2f(700, 750); glVertex2f(390, 750);
    glVertex2f(350, 700);
    glEnd();

    // Windows
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.8f, 0.95f);
    glVertex2f(360, 700); glVertex2f(395, 740);
    glVertex2f(440, 740); glVertex2f(440, 700);
    glEnd();

    for (float x = 465; x <= 650; x += 85) {
        drawRectangle(x, 700, 55, 40, 0.6f, 0.8f, 0.95f);
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, 700); glVertex2f(x, 740);
        glVertex2f(x + 55, 740); glVertex2f(x + 55, 700);
        glEnd();
    }

    // Bottom Lines
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(350, 680); glVertex2f(700, 680);
    glVertex2f(350, 640); glVertex2f(700, 640);
    glEnd();

    // Wheels
    drawCircle(430, 610, 28, 0.0f, 0.0f, 0.0f);
    drawCircle(430, 610, 20, 0.7f, 0.7f, 0.7f);
    drawCircle(630, 610, 28, 0.0f, 0.0f, 0.0f);
    drawCircle(630, 610, 20, 0.7f, 0.7f, 0.7f);

    const char* label = "STUDENT BUS";
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(450, 655);
    for (const char* c = label; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    glPopMatrix();
}
void busOpposite() {
    glPushMatrix();

    glTranslatef(busOppositeX, 0.0f, 0.0f);
    glTranslatef(15.0f, 11.5f, 0.0f);
    glScalef(0.04f, 0.04f, 1.0f);
    glScalef(-1.0f, 1.0f, 1.0f);


    glTranslatef(-950.0f, -610.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.1f, 0.1f); // Red Car
    glVertex2f(400, 610);
    glVertex2f(700, 610);
    glVertex2f(700, 660);
    glVertex2f(400, 660);
    glEnd();

    // --- Car Top (Upper Part/Cabin) ---
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.1f, 0.1f);
    glVertex2f(460, 660);
    glVertex2f(640, 660);
    glVertex2f(610, 710);
    glVertex2f(490, 710);
    glEnd();

    // --- Windows (Glass) ---
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.9f, 1.0f);
    glVertex2f(500, 665);
    glVertex2f(600, 665);
    glVertex2f(585, 700);
    glVertex2f(515, 700);
    glEnd();

    drawCircle(460, 610, 22, 0.0f, 0.0f, 0.0f);
    drawCircle(460, 610, 15, 0.6f, 0.6f, 0.6f);
    drawCircle(640, 610, 22, 0.0f, 0.0f, 0.0f);
    drawCircle(640, 610, 15, 0.6f, 0.6f, 0.6f);

    // --- Headlight ---
    drawCircle(410, 635, 8, 1.0f, 1.0f, 0.6f);

    glPopMatrix();
}

void drawRoad() {
    // Main road (lower)
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(100, 0);
        glVertex2f(100, 18);
        glVertex2f(0, 18);
    glEnd();

    // Top white strip
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glVertex2f(0, 16.5f);
        glVertex2f(100, 16.5f);
        glVertex2f(100, 18);
        glVertex2f(0, 18);
    glEnd();

    // Bottom white strip (right side only)
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(100, 0);
        glVertex2f(100, 1.5f);
        glVertex2f(0, 1.5f);
    glEnd();

    // Middle dashed line
    for(int i = 0; i < 100; i += 12){
        glBegin(GL_QUADS);
            glVertex2f(i + 3, 8);
            glVertex2f(i + 8, 8);
            glVertex2f(i + 8, 10);
            glVertex2f(i + 3, 10);
        glEnd();
    }
}

void drawRoofSolar(float x, float y, float w, float h) {

    drawRectangle(x, y, w, h, 0.0f, 0.0f, 0.4f);


    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for(float i = 0.5f; i < w; i += 1.0f) {
        glVertex2f(x + i, y);
        glVertex2f(x + i, y + h);
    }
    for(float j = 0.5f; j < h; j += 1.0f) {
        glVertex2f(x, y + j);
        glVertex2f(x + w, y + j);
    }
    glEnd();
}
void drawBuilding1() {

    int floors = 2;
    float floorHeight = 6.0f;

    float winWidth = 3.0f;
    float winHeight = 2.5f;
    float frame = 0.3f;

    float rightEdge = 60.0f;
    float buildingWidth = 42.0f;

    float baseX = rightEdge - buildingWidth;
    float baseY = 45.0f;

    float buildingHeight = floors * floorHeight + 4;

    // ===== Building Body =====
    drawRectangle(baseX, baseY,
                  buildingWidth, buildingHeight,
                  0.85f, 0.6f, 0.4f);

    // ===== Windows =====
    int winCount = 6;
    float gap = 6.5f;

    float startX = baseX + 3.0f;

    for (int f = 0; f < floors; f++) {
        float y = baseY + 3 + f * floorHeight;

        for (int j = 0; j < winCount; j++) {
            float x = startX + j * gap;

            // Frame
            drawRectangle(x - frame, y - frame,
                          winWidth + 2 * frame,
                          winHeight + 2 * frame,
                          1.0f, 1.0f, 1.0f);

            // Glass
            drawRectangle(x, y,
                          winWidth, winHeight,
                          0.0f, 0.6f, 0.9f);
        }

    }

    // ===== Floor Divider =====
    drawRectangle(baseX,
                  baseY + floorHeight + 2,
                  buildingWidth, 0.3f,
                  0.7f, 0.7f, 0.7f);

    // ===== Door (center aligned) =====
    float windowRowWidth = (winCount - 1) * gap + winWidth;
    float windowRowCenter = startX + windowRowWidth / 2.0f;

    drawRectangle(windowRowCenter - 2.0f,
                  baseY,
                  4.0f, 6.0f,
                  0.4f, 0.2f, 0.1f);

    float b1Width = 42.0f;
    float b1BaseX = 60.0f - b1Width;
    float b1RoofY = 45.0f + (2 * 6.0f + 4); // floorHeight

    float panelWidth = 8.0f;
    float panelHeight = 3.0f;
    float startX1 = b1BaseX + 4.0f;
    float spacing = 13.0f;

    for (int i = 0; i < 3; i++) {
        // panel stands
        drawRectangle(startX1 + (i * spacing) + 3.5f, b1RoofY, 1.0f, 1.0f, 0.4f, 0.4f, 0.4f);

        //panel
        drawRoofSolar(startX1 + (i * spacing), b1RoofY + 1.0f, panelWidth, panelHeight);
    }
   for (int f = 0; f < floors; f++) {
    float y = baseY + 3 + f * floorHeight;

    for (int j = 0; j < winCount; j++) {
        float x = startX + j * gap;

        // Window frame
        drawRectangle(x - frame, y - frame,
                      winWidth + 2 * frame,
                      winHeight + 2 * frame,
                      1, 1, 1);

        // Window glass (DAY / NIGHT)
        if (isNight)
            drawRectangle(x, y, winWidth, winHeight, 1.0f, 1.0f, 0.6f); // light ON
        else
            drawRectangle(x, y, winWidth, winHeight, 0.0f, 0.6f, 0.9f); // normal
    }


}
}


   void keyboard(unsigned char key, int, int) {
    if (key=='n' || key=='N') {
        isNight = !isNight;
        glutPostRedisplay();
    }
   }
// ---------- Tree ----------

void drawTree(float x, float y) {

    // Trunk
    drawRectangle(x, y,
                  0.8f, 5.0f,
                  0.45f, 0.25f, 0.15f);

    // leaves
    drawCircle(x + 0.4f, y + 6.0f, 2.2f, 0.0f, 0.6f, 0.0f);
    drawCircle(x - 1.2f, y + 5.2f, 1.8f, 0.0f, 0.55f, 0.0f);
    drawCircle(x + 1.8f, y + 5.2f, 1.8f, 0.0f, 0.55f, 0.0f);
}
// ---------- Grass Patch (under tree) ----------
void drawGrass(float y) {

    glColor3f(0.1f, 0.6f, 0.1f);   // Dark green color

    glBegin(GL_QUADS);
        glVertex2f(0, y);
        glVertex2f(100, y);
        glVertex2f(100, y + 1.5f);
        glVertex2f(0, y + 1.5f);
    glEnd();
}
void drawSolarPanel() {
    // 1. Panel Body (Realistic Dark Blue-Gray)
    glColor3f(0.0f, 0.1f, 0.4f);
    glBegin(GL_QUADS);
        glVertex3f(-1.0f, 0.05f, -1.5f);
        glVertex3f( 1.0f, 0.05f, -1.5f);
        glVertex3f( 1.0f, 0.05f,  1.5f);
        glVertex3f(-1.0f, 0.05f,  1.5f);
    glEnd();

    // 2. Frame (Metallic Silver/Gray)
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1.0f, 0.06f, -1.5f);
        glVertex3f( 1.0f, 0.06f, -1.5f);
        glVertex3f( 1.0f, 0.06f,  1.5f);
        glVertex3f(-1.0f, 0.06f,  1.5f);
    glEnd();
}
void drawDetailedSolarPanel(float x, float y, float w, float h) {
    // panel body
    drawRectangle(x, y, w, h, 0.0f, 0.0f, 0.4f);

    // Border
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();

    // Grid
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);

        for(float i = 0.2f; i < w; i += 1.0f) {
            glVertex2f(x + i, y);
            glVertex2f(x + i, y + h);
        }

        for(float j = 0.2f; j < h; j += 1.0f) {
            glVertex2f(x, y + j);
            glVertex2f(x + w, y + j);
        }
    glEnd();
}
// ---------- Building 2 (RIGHT, TALLER) ----------
void drawBuilding2() {

    int floors = 4;
    float floorHeight = 6.0f;

    float winWidth = 3.0f;
    float winHeight = 2.5f;
    float frame = 0.3f;

    float baseX = 62.0f;
    float baseY = 45.0f;

    float buildingWidth = 28.0f;
    float buildingHeight = floors * floorHeight + 5;

    // ===== Building Body =====
    drawRectangle(baseX, baseY,
                  buildingWidth, buildingHeight,
                  0.75f, 0.75f, 0.85f);

    // ===== Windows (DAY / NIGHT) =====
    for (int f = 0; f < floors; f++) {
        float y = baseY + 4 + f * floorHeight;

        for (int j = 0; j < 4; j++) {
            float x = baseX + 3 + j * 6;

            // Frame
            drawRectangle(x - frame, y - frame,
                          winWidth + 2 * frame,
                          winHeight + 2 * frame,
                          1.0f, 1.0f, 1.0f);

            // Glass
            if (isNight)
                drawRectangle(x, y, winWidth, winHeight,
                              1.0f, 1.0f, 0.6f);   // 💡 light ON
            else
                drawRectangle(x, y, winWidth, winHeight,
                              0.0f, 0.6f, 0.9f);   // day glass
        }
    }

    // ===== Floor Divider =====
    for (int f = 1; f < floors; f++) {
        drawRectangle(baseX,
                      baseY + f * floorHeight + 2,
                      buildingWidth, 0.4f,
                      0.7f, 0.7f, 0.7f);
    }

    // ===== Door =====
    drawRectangle(baseX + 12, baseY,
                  4, 6,
                  0.4f, 0.2f, 0.1f);

    // ===== Solar Panels =====
    float roofY = baseY + buildingHeight;

    drawDetailedSolarPanel(baseX + 2,  roofY, 8, 3);
    drawDetailedSolarPanel(baseX + 18, roofY, 8, 3);

    // panel stands
    drawRectangle(baseX + 5,  roofY - 0.5f, 0.5f, 0.5f, 0.3f, 0.3f, 0.3f);
    drawRectangle(baseX + 21, roofY - 0.5f, 0.5f, 0.5f, 0.3f, 0.3f, 0.3f);
}


void drawStars() {
    glColor3f(1.0f, 1.0f, 1.0f); // white stars
    glPointSize(2.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < STAR_COUNT; i++) {
        glVertex2f(starX[i], starY[i]);
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // 🌙 DAY / NIGHT BACKGROUND
    if (isNight) {
        glClearColor(0.05f, 0.05f, 0.2f, 1.0f);   // Dark night sky
    } else {
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Day sky
    }

    // Sun
    drawSun();
     for(int i=0;i<CLOUD_COUNT;i++){
        float x = fmod(cloudX+i*CLOUD_GAP,300);
        glPushMatrix();
        glTranslatef(x,88,0);
        drawCloudShape();
        glPopMatrix();
    }
  if (isNight) {
        drawStars();
    }
    // Clouds (AUTO moving)
    glPushMatrix(); glTranslatef(cloudX, 85, 0); drawCloudShape(); glPopMatrix();
    glPushMatrix(); glTranslatef(cloudX - 40, 90, 0); drawCloudShape(); glPopMatrix();
    glPushMatrix(); glTranslatef(cloudX - 70, 80, 0); drawCloudShape(); glPopMatrix();
    glPushMatrix(); glTranslatef(cloudX - 100, 88, 0); drawCloudShape(); glPopMatrix();
    glPushMatrix(); glTranslatef(cloudX - 130, 92, 0); drawCloudShape(); glPopMatrix();
    for (int i = 0; i < CLOUD_COUNT; i++) {
        float x = fmod(cloudX + i * CLOUD_GAP, 300.0f);

        glPushMatrix();
        glTranslatef(x, 88, 0);
        drawCloudShape();
        glPopMatrix();
    }
    drawBuilding1();
    drawBuilding2();
    drawRoad();
    bus();
    busOpposite();
    staticBus();
    drawPlayground();
    drawPlaygroundMarkings();
    drawFence();
    drawGateBanner();

    drawTree(54.0f, 45.0f);
    drawTree(57.5f, 45.0f);
    drawTree(61.0f, 45.0f);

    drawTree(54.0f, 45.0f);
    drawTree(57.5f, 45.0f);
    drawTree(61.0f, 45.0f);

    drawStreetLight(10.0f, 45.0f);
    drawStreetLight(45.0f, 45.0f);
    drawStreetLight(80.0f, 45.0f);
    drawBench(39.0f, 43.0f);
    drawBench(75.0f, 43.0f);

    drawBench(56.0f, 43.0f);


   drawBush(10.0f, 42.5f);
   drawBush(14.0f, 43.5f);

   drawBush(34.0f, 43.0f);
   drawBush(38.0f, 43.0f);

   drawBush(68.0f, 43.0f);
   drawBush(72.0f, 43.0f);

   drawBush(88.0f, 43.5f);
   drawBush(85.0f, 43.5f);

   drawTree(92.0f, 45.0f);

   drawTree(95.5f, 45.0f);

   drawGrass(45.0f);
   drawTree(99.0f, 45.0f);


   drawTree(-2.0f, 45.0f);

   drawTree(2.5f, 45.0f);

   if (!isNight) {
    drawBoy(22.0f, 45.0f, 0.2f, 0.5f, 0.9f, 0.1f, 0.1f, 0.6f);
    drawGirl(30.0f, 45.5f, 1.0f, 0.4f, 0.6f, 0.8f, 0.2f, 0.4f);
    drawBoy(65.0f, 45.0f, 0.9f, 0.7f, 0.1f, 0.2f, 0.6f, 0.2f);
    drawGirl(75.0f, 45.5f, 0.4f, 0.7f, 0.1f, 1.0f, 0.5f, 0.0f);
}
   drawPlaygroundWall();
   drawEntranceGate();


 glFlush();
}

// ---------- Timer ----------
void update(int value) {
    cloudX += 0.05f;
    sunAngle += 0.1f;


    busX -= currentSpeed;

    if (busX < -60.0f) {
        busX = 110.0f;
    }

    busOppositeX += currentSpeed;
    if (busOppositeX > 110.0f) busOppositeX = -40.0f;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

void init() {
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // sky blue
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);

    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 100;
        starY[i] = 60 + rand() % 40; // sky area only
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1490, 760);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sky + Clouds + Detailed Road");
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseControl);
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}
