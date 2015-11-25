// CS184 Simple OpenGL Example
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#include <sstream>
#include <string>

#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define PI 3.14159265

using namespace std;


float maxPt = 1.0f;
float step = 0.1f;
bool adaptive = false;



GLfloat material_diffuse[] = { 1, 0, 0, 1 };
GLfloat material_specular[] = { 1, 1, 1, 1 };
GLfloat material_shininess = 100;

//****************************************************
// Some Classes
//****************************************************
class Viewport {
  public:
    int w, h; // width and height
};

class TPoint { //more like TVector
public:
    float x,y,z;
    TPoint(float x1,float y1,float z1):x(x1),y(y1),z(z1){}
    TPoint sub(TPoint p){
        TPoint rtn = TPoint(0,0,0);
        float x1,y1,z1;
        x1 = x-p.x;
        y1 = y-p.y;
        z1 = z-p.z;
        rtn.x = x1;
        rtn.y = y1;
        rtn.z = z1;
        return rtn;
    }
    TPoint add(TPoint p){
        TPoint rtn = TPoint(0,0,0);
        float x1,y1,z1;
        x1 = x+p.x;
        y1 = y+p.y;
        z1 = z+p.z;
        rtn.x = x1;
        rtn.y = y1;
        rtn.z = z1;
        return rtn;
    }
    TPoint scale(float s){
        TPoint rtn = TPoint(0,0,0);
        float x1,y1,z1;
        x1 = x*s;
        y1 = y*s;
        z1 = z*s;
        rtn.x = x1;
        rtn.y = y1;
        rtn.z = z1;
        return rtn;
    }
    TPoint cross(TPoint p){
        TPoint rtn = TPoint(0,0,0);
        float x1,y1,z1;
        
        x1 = y*p.z - z*p.y;
        y1 = z*p.x - x*p.z;
        z1 = x*p.y - y*p.x;
        
        
        rtn.x = x1;
        rtn.y = y1;
        rtn.z = z1;
        return rtn;
    
    }
    TPoint normalize(){
        TPoint rtn = TPoint(0,0,0);
        float x1,y1,z1;
        float mag = 0.0000001; //just to prevent a divide by zero
        mag += sqrt(x*x + y*y + z*z);
        x1 = x/mag;
        y1 = y/mag;
        z1 = z/mag;
        rtn.x = x1;
        rtn.y = y1;
        rtn.z = z1;
        return rtn;
    }
    void disp(){ cout<<"(" <<  x  <<  ", "  <<  y  <<  ", " << z <<  ")"  <<endl;}
};

class TTriVert { //stores position and normal
public:
    TPoint vert;
    TPoint norm;
    TTriVert(TPoint v, TPoint n):vert(v), norm(n){}
    void disp(){
        cout<< "here is my point:"<<endl;
        vert.disp();
        cout<< "and here is my norm:"<<endl;
        norm.disp();
    }
};


class TPatch {
public:
    TPoint p1;
    TPoint p2;
    TPoint p3;
    TPoint p4;
    TPoint p5;
    TPoint p6;
    TPoint p7;
    TPoint p8;
    TPoint p9;
    TPoint p10;
    TPoint p11;
    TPoint p12;
    TPoint p13;
    TPoint p14;
    TPoint p15;
    TPoint p16;

    TPatch(TPoint pt1,
           TPoint pt2,
           TPoint pt3,
           TPoint pt4,
           TPoint pt5,
           TPoint pt6,
           TPoint pt7,
           TPoint pt8,
           TPoint pt9,
           TPoint pt10,
           TPoint pt11,
           TPoint pt12,
           TPoint pt13,
           TPoint pt14,
           TPoint pt15,
           TPoint pt16): p1(pt1),
                         p2(pt2),
                         p3(pt3),
                         p4(pt4),
                         p5(pt5),
                         p6(pt6),
                         p7(pt7),
                         p8(pt8),
                         p9(pt9),
                         p10(pt10),
                         p11(pt11),
                         p12(pt12),
                         p13(pt13),
                         p14(pt14),
                         p15(pt15),
                         p16(pt16){}
    
    
    void disp(){
        cout<<"here are my control points:"<< endl;
        p1.disp();
        p2.disp();
        p3.disp();
        p4.disp();
        p5.disp();
        p6.disp();
        p7.disp();
        p8.disp();
        p9.disp();
        p10.disp();
        p11.disp();
        p12.disp();
        p13.disp();
        p14.disp();
        p15.disp();
        p16.disp();
    }
    
};

class TTriangle {
public:
    TTriVert v1;
    TTriVert v2;
    TTriVert v3;
    TTriangle(TTriVert vt1, TTriVert vt2, TTriVert vt3):v1(vt1), v2(vt2), v3(vt3){}
    void render(){
        /*
        
          glPushMatrix();
          
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
          */
          
        
        
        glBegin(GL_TRIANGLES);
        glNormal3f(v1.norm.x,v1.norm.y,v1.norm.z);
        glVertex3f(v1.vert.x,v1.vert.y,v1.vert.z);
        glNormal3f(v2.norm.x,v2.norm.y,v2.norm.z);
        glVertex3f(v2.vert.x,v2.vert.y,v2.vert.z);
        glNormal3f(v3.norm.x,v3.norm.y,v3.norm.z);
        glVertex3f(v3.vert.x,v3.vert.y,v3.vert.z);
        
        glEnd();
        
        //glPopMatrix();
    }
   
};


//****************************************************
// Global Variables
//****************************************************
Viewport    viewport;

vector<TPatch> patches;

vector<TTriangle> tris;


//returns a point--interpolates a,b by u. a(1-u) + b(u) so when u=0, rtn a, and when u=1, rtn b
TPoint lerp(TPoint a, TPoint b, float u){
    TPoint rtn = TPoint(0,0,0);
    
    float rx,ry,rz;
    rx = a.x*(1-u) + b.x*u;
    ry = a.y*(1-u) + b.y*u;
    rz = a.z*(1-u) + b.z*u;
    
    rtn.x = rx;
    rtn.y = ry;
    rtn.z = rz;
    
    return rtn;
}


//returns (point, deriv)
TTriVert bezcurveinterp(TPoint p1, TPoint p2, TPoint p3, TPoint p4, float u){
    TPoint dummy = TPoint(0,0,0);
    TTriVert rtn = TTriVert(dummy,dummy);
    
    //split the three segments (p1,p2) (p2,p3) (p3,p4) to AB and BC
    TPoint a = lerp(p1,p2,u);
    TPoint b = lerp(p2,p3,u);
    TPoint c = lerp(p3,p4,u);
    
    //split AB and BC to form DE
    TPoint d = lerp(a,b,u);
    TPoint e = lerp(b,c,u);
    
    
    TPoint point = lerp(d,e,u);
    
    rtn.vert = point;
    
    TPoint deriv = e.sub(d);
    deriv = deriv.scale(3);
    
    rtn.norm = deriv;
    
    return rtn;
}


TTriVert bezpatchinterp(TPatch patch, float u, float v){
    TPoint dummy = TPoint(0,0,0);
    TTriVert rtn = TTriVert(dummy,dummy);
    
    //control points for v curve
    TPoint v1 = bezcurveinterp(patch.p1,patch.p2,patch.p3,patch.p4,u).vert;
    TPoint v2 = bezcurveinterp(patch.p5,patch.p6,patch.p7,patch.p8,u).vert;
    TPoint v3 = bezcurveinterp(patch.p9,patch.p10,patch.p11,patch.p12,u).vert;
    TPoint v4 = bezcurveinterp(patch.p13,patch.p14,patch.p15,patch.p16,u).vert;
    
    //control points for u curve
    TPoint u1 = bezcurveinterp(patch.p1,patch.p5,patch.p9,patch.p13,v).vert;
    TPoint u2 = bezcurveinterp(patch.p2,patch.p6,patch.p10,patch.p14,v).vert;
    TPoint u3 = bezcurveinterp(patch.p3,patch.p7,patch.p11,patch.p15,v).vert;
    TPoint u4 = bezcurveinterp(patch.p4,patch.p8,patch.p12,patch.p16,v).vert;
    
    
    /*
    //try swapping below?
    
     //control points for v curve
     TPoint u1 = bezcurveinterp(patch.p1,patch.p2,patch.p3,patch.p4,v).vert;
     TPoint u2 = bezcurveinterp(patch.p5,patch.p6,patch.p7,patch.p8,v).vert;
     TPoint u3 = bezcurveinterp(patch.p9,patch.p10,patch.p11,patch.p12,v).vert;
     TPoint u4 = bezcurveinterp(patch.p13,patch.p14,patch.p15,patch.p16,v).vert;
     
     //control points for u curve
     TPoint v1 = bezcurveinterp(patch.p1,patch.p5,patch.p9,patch.p13,u).vert;
     TPoint v2 = bezcurveinterp(patch.p2,patch.p6,patch.p10,patch.p14,u).vert;
     TPoint v3 = bezcurveinterp(patch.p3,patch.p7,patch.p11,patch.p15,u).vert;
     TPoint v4 = bezcurveinterp(patch.p4,patch.p8,patch.p12,patch.p16,u).vert;
    */
    
    
    TTriVert pdv = bezcurveinterp(v1,v2,v3,v4,v);
    TTriVert pdu = bezcurveinterp(u1,u2,u3,u4,u);
    
    
    //pdv.disp();
    //pdu.disp();
    // */ // eh almost the same point. why not avg them
    TPoint point = pdu.vert.scale(-1);
    point = pdv.vert.sub(point);
    point = point.scale(.5);
    //point.disp();
    
    rtn.vert = point;
    
    TPoint norm = pdu.norm.cross(pdv.norm);
    norm = norm.normalize();
    
    //norm = norm.scale(-1);
    
    rtn.norm = norm;

    return rtn;
}

void tessalate(TPatch patch){
    if (!adaptive) {
        //cout<<step<<endl;
        int numdiv = (int)((1.0001)/step);
        
        for (float iu = 0; iu < (float)numdiv; iu ++) {
            
            float u = iu*step;
            
            if (u>1) {
                u=1;
            }
            
            for (float iv = 0; iv < (float)numdiv; iv ++) {
                
                float v = iv*step;
                
                if (v>1){
                    cout << "t" << endl;
                    v=1;
                }
                
                TTriVert u1 = bezpatchinterp(patch,u,v);
                TTriVert u2 = bezpatchinterp(patch,u + step,v);
                TTriVert u3 = bezpatchinterp(patch,u + step,v + step);
                TTriVert u4 = bezpatchinterp(patch,u,v + step);
                
                //split this square grid entry (in uv space) to 2 triangles along diagonal
                TTriangle t1 = TTriangle(u1,u4,u3);
                TTriangle t2 = TTriangle(u1,u3,u2);
                
                tris.push_back(t1);
                tris.push_back(t2);
            }
        }
        
        
    }
}



//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport(0,0,viewport.w,viewport.h);// sets the rectangle that will be the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // loading the identity matrix for the screen
    
    //glRotatef(0, 0.0f, 1.0f, 0.0f);
    //glRotatef(0, 1.0f, 0.0f, 0.0f);
    //glRotatef(-100, 1.0f, 0.0f, 0.0f);

  //----------- setting the projection -------------------------
  // glOrtho sets left, right, bottom, top, zNear, zFar of the chord system


  // glOrtho(-1, 1 + (w-400)/200.0 , -1 -(h-400)/200.0, 1, 1, -1); // resize type = add
  // glOrtho(-w/400.0, w/400.0, -h/400.0, h/400.0, 1, -1); // resize type = center

  glOrtho(-1*maxPt, 1*maxPt, -1*maxPt, 1*maxPt, 4, -4);    // resize type = stretch

  //------------------------------------------------------------
}


//****************************************************
// sets the window up
//****************************************************
void initScene(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent
  
    /*
    glShadeModel(GL_FLAT);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //Material properties
    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[] = {0.5f, 0.7f, 0.9f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shine = 50.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);
    //Add ambient light
    //GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {-3.0f, -3.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); //Automatically normalize normals
     */
    
    //glClearColor (0.0, 0.0, 0.0, 0.0);
    
    glShadeModel(GL_FLAT);
    //glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    GLfloat light0_position[] = { 0, 0, 1, 0 };//light down the -z axis
    GLfloat light0_brightness[] = { 1, 1, 1, 1 };//purple light
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_brightness);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_brightness);
    
    GLfloat material_diffuse[] = { 1, 0, 0, 1 };
    GLfloat material_specular[] = { 1, 1, 1, 1 };
    GLfloat material_shininess = 50;
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    
    
  myReshape(viewport.w,viewport.h);
}


//***************************************************
// function that does the actual drawing
//***************************************************
void myDisplay() {


  //----------------------- ----------------------- -----------------------
  // This is a quick hack to add a little bit of animation.
  static float tip = 0.5f;
  const  float stp = 0.0001f;
  const  float beg = 0.1f;
  const  float end = 0.9f;

  tip += stp;
  if (tip>end) tip = beg;
  //----------------------- ----------------------- -----------------------


  glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer (sets everything to black)

  glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
  glLoadIdentity();                            // make sure transformation is "zero'd"

  //----------------------- code to draw objects --------------------------
    //glColor3f(1.0f,0.0f,1.0f); //purple color b/c why not
    /*
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glVertex3f(0,0,1);
    glNormal3f(0,0,1);
    glVertex3f(1,0,1);
    glNormal3f(0,0,1);
    glVertex3f(0,1,1);
    glEnd();
    
    */
    //add a light
    //glPushMatrix();//idk
    
    TPoint p1 = TPoint(0,0,0);
    TPoint p2 = TPoint(1,0,0);
    TPoint p3 = TPoint(0,1,0);
    
    
    TPoint n1 = TPoint(0,0,1);
    TPoint n2 = TPoint(0,0,1);
    TPoint n3 = TPoint(0,0,1);
    
    TTriVert v1 = TTriVert(p1,n1);
    TTriVert v2 = TTriVert(p2,n2);
    TTriVert v3 = TTriVert(p3,n3);
    
    TTriangle test = TTriangle(v1,v2,v3);
    //test.render();
    
    //cout << tris.size() << endl;
    
    for (int j=0; j<tris.size(); j++) {
        TTriangle t = tris[j];
        t.render();
    
    }
    
    //patches.clear();
    //tris.clear();
    
    //glPopMatrix();//idk
    
    /*
  // Rectangle Code
  //glColor3f(red component, green component, blue component);
  glColor3f(1.0f,0.0f,0.0f);                   // setting the color to pure red 90% for the rect

  glBegin(GL_POLYGON);                         // draw rectangle 
  //glVertex3f(x val, y val, z val (won't change the point because of the projection type));
  glVertex3f(-0.8f, 0.0f, 0.0f);               // bottom left corner of rectangle
  glVertex3f(-0.8f, 0.5f, 0.0f);               // top left corner of rectangle
  glVertex3f( 0.0f, 0.5f, 0.0f);               // top right corner of rectangle
  glVertex3f( 0.0f, 0.0f, 0.0f);               // bottom right corner of rectangle
  glEnd();
  // Triangle Code
  glColor3f(1.0f,0.5f,0.0f);                   // setting the color to orange for the triangle

  float basey = -sqrt(0.48f);                  // height of triangle = sqrt(.8^2-.4^2)
  glBegin(GL_POLYGON);
  glVertex3f(tip,  0.0f, 0.0f);                // top tip of triangle
  glVertex3f(0.1f, basey, 0.0f);               // lower left corner of triangle
  glVertex3f(0.9f, basey, 0.0f);               // lower right corner of triangle
  glEnd();
     */
  //-----------------------------------------------------------------------

  glFlush();
  glutSwapBuffers();                           // swap buffers (we earlier set double buffer)
}


//****************************************************
// called by glut when there are no messages to handle
//****************************************************
void myFrameMove() {
  //nothing here for now
#ifdef _WIN32
  Sleep(10);                                   //give ~10ms back to OS (so as not to waste the CPU)
#endif
  glutPostRedisplay(); // forces glut to call the display function (myDisplay())
}



void processBez(string bezFileName){
    vector<TPoint> ctrlPts;
    ifstream iss(bezFileName.c_str());
    string test;
    while(getline(iss, test)){
        
        //cout << test << endl;
        istringstream issl(test);
        
        if (test.size() < 75) {//just gets rid of that annoying # of faces
            string sub;
            issl >> sub;
        }
        
        while(issl){
            float x,y,z;
            string sub;
            issl >> sub;
            if (sub.size() == 0) {
                continue;
            }
            x = atof(sub.c_str());
            issl >> sub;
            y = atof(sub.c_str());
            issl >> sub;
            z = atof(sub.c_str());
            TPoint pt = TPoint(x,y,z);
            ctrlPts.push_back(pt);
            //pt.disp();
            //cout << "t " << sub.size() << endl;
            
        }
        
    }
    //cout << ctrlPts.size() << endl;
    int i;
    for (i=0; i<ctrlPts.size(); i += 16) {
        TPatch patch = TPatch(ctrlPts[i],
                              ctrlPts[i+1],
                              ctrlPts[i+2],
                              ctrlPts[i+3],
                              ctrlPts[i+4],
                              ctrlPts[i+5],
                              ctrlPts[i+6],
                              ctrlPts[i+7],
                              ctrlPts[i+8],
                              ctrlPts[i+9],
                              ctrlPts[i+10],
                              ctrlPts[i+11],
                              ctrlPts[i+12],
                              ctrlPts[i+13],
                              ctrlPts[i+14],
                              ctrlPts[i+15]);
        patches.push_back(patch);
    }
    int j;
    /*
    for (j=0; j<patches.size(); j++) {
        patches[j].disp();
    }*/
    //cout<<"i have: " << patches.size() << " patches" << endl;
    
    //so this is to initially make whole object(s) visible
    for (j=0; j<ctrlPts.size(); j++) {
        maxPt = fmax(maxPt,ctrlPts[j].x);
        maxPt = fmax(maxPt,ctrlPts[j].y);
        maxPt = fmax(maxPt,ctrlPts[j].z);
    }
    maxPt++;
    //cout << maxPt << endl;
    
    
    for (int i=0; i<patches.size(); i++) {
        //cout<<"t"<<endl;
        TPatch p = patches[i];
        tessalate(p);
        
    }
    
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
    
    
    step = atof(argv[2]);
    
    string bezFile = "";
    bezFile = argv[1];
    
    //cout << bezFile << endl;
    processBez(bezFile);
    
    
    cout << tris.size() << endl;
    
   /* //test bezcurveinterp seems reasonable
    TPoint p1 = TPoint(0,0,0);
    TPoint p2 = TPoint(0,1,0);
    TPoint p3 = TPoint(1,1,0);
    TPoint p4 = TPoint(1,0,0);
    
    
    TTriVert test = bezcurveinterp(p1,p2,p3,p4,.75);
    test.vert.disp();
    test.norm.disp();//actually deriv*/
    /*//have no idea if this works but expected structure at least
    for (int j=0; j<patches.size(); j++) {
        cout << "t1" << endl;
        patches[j].disp();
        bezpatchinterp(patches[j],1,0).disp();
        cout << "t2" << endl;
    }*/
    
    for (int j=0; j<patches.size(); j++) {
        //cout << "t1" << endl;
        //patches[j].disp();
        //bezpatchinterp(patches[j],1,0).disp();
        //cout << "t2" << endl;
    }
    
    
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("CS184!");

  initScene();                                 // quick function to set up scene

  glutDisplayFunc(myDisplay);                  // function to run when its time to draw something
  glutReshapeFunc(myReshape);                  // function to run when the window gets resized
  glutIdleFunc(myFrameMove);                   // function to run when not handling any other task
  glutMainLoop();                              // infinite loop that will keep drawing and resizing and whatever else

  return 0;
}








