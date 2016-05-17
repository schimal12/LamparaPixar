//Animación de lampara de Pixar
//Graficas computacionales
//Sebastian Chimal Montes de Oca

#ifdef _WIN32
#include "glut.h"
#elif __APPLE__
#include <GLUT/GLUT.h>
#endif
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <sstream>



using namespace std;


struct objeto{
    float x;
    float y;
    float z;
    
    float angulo;
    float radio;
    float velocidad;
};

#define PI 3.14159265

GLint contador = 0;
GLfloat ang = 0;
GLfloat tiempo = 0;
float ground=-1.0;

GLboolean EaseIn = false;
GLboolean EaseOut = false;
GLboolean EaseInOut = false;
GLboolean Linear = false;

GLint variablesLinea = 0;

float primeraParte = 0.0,shoulder2 = 0.0, elbow = 30.0,elbow2=-40.0, foco=0.0;
float focoX = 0.0,focoY = 0.0,focoZ = 0.0;

float baseX =  2.0f, baseY = ground+0.0f, baseZ = -1.0f;
float rod1X = -1.0f, rod1Y = ground+0.2f, rod1Z = -1.0f;
float rod2X = -1.0f, rod2Y = ground+1.2f, rod2Z = -1.0f;
float lampX = -1.0f, lampY = ground+2.2f, lampZ = -1.0f;


objeto base={baseX,baseY,baseZ,0.0f,0.6f,0.0f};
objeto rod1={rod1X,rod1Y,rod1Z,0.0f,0.07f,0.0f};
objeto rod2={rod2X,rod2Y,rod2Z,0.0f,0.07f,0.0f};
objeto lamp={lampX,lampY,lampZ,0.0f,0.35f,0.0f};

void Init();
void Display();
void Reshape();


void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void initRendering() {
    glClearColor (0.3, 0.3, 0.1, 0.6);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    
}


void Keyboard(unsigned char key,
              int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            EaseIn = true;
            EaseOut = false;
            EaseInOut = false;
            Linear = false;
            break;
        case 's':
        case'S':
            EaseOut = true;
            EaseIn = false;
            EaseInOut = false;
            Linear = false;
            break;
        case 'a':
        case 'A':
            EaseInOut = true;
            EaseOut = false;
            EaseIn = false;
            Linear = false;
            break;
        case 'd':
        case 'D':
            Linear = true;
            EaseInOut = false;
            EaseOut = false;
            EaseIn = false;
            break;
        default:
            Linear = false;
            EaseInOut = false;
            EaseOut = false;
            EaseIn = false;
            break;
    }
}



void dibujarTetera(GLfloat primeraParteRotacion, GLfloat shoulderRotacion, GLfloat elbowRotacion, GLfloat elbow2Rotacion, GLfloat focoRotacion,GLfloat MoverX, GLfloat MoverY, GLfloat MoverZ, float focoX, float focoY, float focoZ){
    
    
    //Posicionar la base
    glPushMatrix();
    glRotatef (10.0, 1.0, 0.0, 0.0);
    glTranslatef (MoverX,MoverY, MoverZ);
    glRotatef ((GLfloat) primeraParteRotacion, 0.0, 0.0, 1.0);
    glTranslatef (0.0, 0.0, 0.0);
    
    //Dibujar Baseº
    glPushMatrix();
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    glColor3f(0.7,0.7,0.7);
    GLUquadricObj *disco;
    disco = gluNewQuadric();
    gluCylinder(disco , 0.6f , 0.5f , 0.2f , 32 ,32 ) ;
    glPopMatrix();
    glTranslatef (0.0, 0.20, 0.0);
    
    //Piso de la base de la lámpara
    glPushMatrix();
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    glColor3f(1.0,0.0,0);
    disco = gluNewQuadric();
    gluDisk(disco, 0, 0.5f, 32, 32);
    glPopMatrix();
    
    //Esfera de la base
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glutSolidSphere(0.1f,64,64) ;
    glPopMatrix();
    
    //Rotar cuerpo de la lampara
    glRotatef ((GLfloat) elbowRotacion, 0.0, 0.0, 1.0);
    
    
    //Dibujar parte 1 de la lampara [Primer brazo]
    glPushMatrix();
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    GLUquadricObj *cuadratica;
    cuadratica = gluNewQuadric();
    glColor3f(1.0,1.0,1.0);
    gluCylinder(cuadratica,0.07f,0.07,1.0f,32,32);
    glPopMatrix();
    
    //Posicionar esfera para servir como union con el siguiente brazo
    glTranslatef (0.0, 1.0, 0.0);
    glRotatef ((GLfloat) elbow2Rotacion, 0.0, 0.0, 1.0);
    
    //Dibujar esfera
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef (0.0, 0.07, 0);
    glutSolidSphere(0.1f,64,64) ;
    glPopMatrix();
    
    //Dibujar segunda parte de la lampara[Segundo brazo]
    glPushMatrix();
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    GLUquadricObj *cuadratica2;
    cuadratica2 = gluNewQuadric();
    glColor3f(1,1,1);
    gluCylinder(cuadratica2,0.07f,0.07,1.0f,100,100);
    glPopMatrix();
    
    //Union del cuerpo de la lampara con el foquito
    glTranslatef (0.0, 1.0, 0.0);
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glutSolidSphere(0.1f,64,64) ;
    glPopMatrix();
    
    //Rotar a posicion cero el foco
    glRotatef ((GLfloat) focoRotacion, focoX, focoY, focoZ);
    glRotatef ((GLfloat) shoulderRotacion, 0.0, 1.0, 0.0);
    
    //Crear la cobertura de la lampara
    glPushMatrix();
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    GLUquadricObj *cuadratica3;
    cuadratica3 = gluNewQuadric();
    glColor3f(0.7,0.7,0.7);
    gluCylinder(cuadratica3,0.09f,0.4,0.40f,100,100);
    glTranslatef (0.0, 0.0,0.05);
    
    //Hacer el foco
    glutSolidSphere(0.1f,32,32) ;
    glPopMatrix();
    glPopMatrix();
    

}

void controladorLampara4(float primeraParte, float shoulder, float elbow, float elbow2, float foco, objeto *baseX,float primeraParteF, float shoulderF, float elbowF, float elbow2F, float focoF, objeto *baseXF, float tiempo,float focoX, float focoY, float focoZ){
    
    
    //Variables iniciales
    
    GLfloat primeraP = primeraParte;
    GLfloat shoulderP = shoulder;
    GLfloat elbowP = elbow;
    GLfloat elbow2P = elbow2;
    GLfloat focoP = foco;
    
    objeto baseXFi = *baseX;
    
    
    //Variables finales
    
    GLfloat primeraPF = primeraParteF;
    GLfloat shoulderPF = shoulderF;
    GLfloat elbowPF = elbowF;
    GLfloat elbow2PF = elbow2F;
    GLfloat focoPF = focoF;
    
    objeto baseXFF = *baseXF;
    
    //Datos de interpolacion
    
    /*
     return c*t/d + b;
     */
    
    
    //Rotaciones
    //Primera Parte
    GLfloat primeraParteRotacion = ((primeraPF-primeraP)*tiempo)+primeraP;
    //Shoulder
    GLfloat shoulderRotacion = ((shoulderPF-shoulderP)*tiempo)+shoulderP;
    
    //Elbow1
    GLfloat elbowRotacion = ((elbowPF-elbowP)*tiempo)+elbowP;
    //Elbow 2
    GLfloat elbow2Rotacion = ((elbow2PF-elbow2P)*tiempo)+elbow2P;
    //Foco
    GLfloat focoRotacion = ((focoPF-focoP)*tiempo)+focoP;
    
    //Traslacion
    GLfloat  MoverX = ((baseXFF.x-baseXFi.x)*tiempo)+baseXFi.x;
    
    GLfloat  MoverY = ((baseXFF.y-baseXFi.y)*tiempo)+baseXFi.y;
    
    GLfloat  MoverZ = ((baseXFF.z-baseXFi.z)*tiempo)+baseXFi.z;
    
    //Dibujar Tetera
    dibujarTetera(primeraParteRotacion,shoulderRotacion,elbowRotacion,elbow2Rotacion,focoRotacion,MoverX,MoverY,MoverZ, focoX, focoY, focoZ);
    
}


void controladorLampara2(float primeraParte, float shoulder, float elbow, float elbow2, float foco, objeto *baseX,float primeraParteF, float shoulderF, float elbowF, float elbow2F, float focoF, objeto *baseXF, float tiempo,float focoX, float focoY, float focoZ){
    
    
    //Variables iniciales
    
    GLfloat primeraP = primeraParte;
    GLfloat shoulderP = shoulder;
    GLfloat elbowP = elbow;
    GLfloat elbow2P = elbow2;
    GLfloat focoP = foco;
    
    objeto baseXFi = *baseX;
    
    
    //Variables finales
    
    GLfloat primeraPF = primeraParteF;
    GLfloat shoulderPF = shoulderF;
    GLfloat elbowPF = elbowF;
    GLfloat elbow2PF = elbow2F;
    GLfloat focoPF = focoF;
    
    objeto baseXFF = *baseXF;
    
    //Datos de interpolacion
    
    /*
     -c * Math.cos(t/d * (Math.PI/2)) + c + b;
     */
    
    
    //Rotaciones
    //Primera Parte
    GLfloat primeraParteRotacion = -(primeraPF-primeraP)*cos(tiempo*(M_PI/2))+(primeraPF-primeraP)+primeraP;
    //Shoulder
    GLfloat shoulderRotacion = -(shoulderPF-shoulderP)*cos(tiempo*(M_PI/2))+(shoulderPF-shoulderP)+shoulderP;
    
    //Elbow1
    GLfloat elbowRotacion = -(elbowPF-elbowP)*cos(tiempo*(M_PI/2))+(elbowPF-elbowP)+elbowP;
    //Elbow 2
    GLfloat elbow2Rotacion = -(elbow2PF-elbow2P)*cos(tiempo*(M_PI/2))+(elbow2PF-elbow2P)+elbow2P;
    //Foco
    GLfloat focoRotacion =-(focoPF-focoP)*cos(tiempo*(M_PI/2))+(focoPF-focoP)+focoP;
    
    //Traslacion
    GLfloat  MoverX = -(baseXFF.x-baseXFi.x)*cos(tiempo*(M_PI/2))+(baseXFF.x-baseXFi.x)+baseXFi.x;
    
    GLfloat  MoverY = -(baseXFF.y-baseXFi.y)*cos(tiempo*(M_PI/2))+(baseXFF.y-baseXFi.y)+baseXFi.y;
    
    GLfloat  MoverZ = -(baseXFF.z-baseXFi.z)*cos(tiempo*(M_PI/2))+(baseXFF.z-baseXFi.z)+baseXFi.z;
    
    //Dibujar Tetera
    dibujarTetera(primeraParteRotacion,shoulderRotacion,elbowRotacion,elbow2Rotacion,focoRotacion,MoverX,MoverY,MoverZ, focoX, focoY, focoZ);
    
}



void controladorLampara3(float primeraParte, float shoulder, float elbow, float elbow2, float foco, objeto *baseX,float primeraParteF, float shoulderF, float elbowF, float elbow2F, float focoF, objeto *baseXF, float tiempo,float focoX, float focoY, float focoZ){
    
    
    //Variables iniciales
    
    GLfloat primeraP = primeraParte;
    GLfloat shoulderP = shoulder;
    GLfloat elbowP = elbow;
    GLfloat elbow2P = elbow2;
    GLfloat focoP = foco;
    
    objeto baseXFi = *baseX;
    
    
    //Variables finales
    
    GLfloat primeraPF = primeraParteF;
    GLfloat shoulderPF = shoulderF;
    GLfloat elbowPF = elbowF;
    GLfloat elbow2PF = elbow2F;
    GLfloat focoPF = focoF;
    
    objeto baseXFF = *baseXF;
    
    //Datos de interpolacion
    
    /*
     return c * Math.sin(t/d * (Math.PI/2)) + b;
     
     */
    
    //Rotaciones
    //Primera Parte
    GLfloat primeraParteRotacion = primeraP + (sin(tiempo*M_PI/2))*(primeraPF - primeraP);
    //Shoulder
    GLfloat shoulderRotacion = shoulderP + (sin(tiempo*M_PI/2))*(shoulderPF - shoulderP);
    //Elbow1
    GLfloat elbowRotacion = elbowP + (sin(tiempo*M_PI/2))*(elbowPF - elbowP);
    //Elbow 2
    GLfloat elbow2Rotacion = elbow2P + (sin(tiempo*M_PI/2))*(elbow2PF - elbow2P);
    //Foco
    GLfloat focoRotacion = focoP + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(focoPF - focoP);
    
    //Traslacion
    GLfloat  MoverX = baseXFi.x + (sin(tiempo*M_PI/2))*(baseXFF.x - baseXFi.x);
    GLfloat  MoverY = baseXFi.y + (sin(tiempo*M_PI/2))*(baseXFF.y - baseXFi.y);
    GLfloat  MoverZ = baseXFi.z + (sin(tiempo*M_PI/2))*(baseXFF.z - baseXFi.z);
    
    //Dibujar Tetera
    dibujarTetera(primeraParteRotacion,shoulderRotacion,elbowRotacion,elbow2Rotacion,focoRotacion,MoverX,MoverY,MoverZ, focoX, focoY, focoZ);


    
}



void controladorLampara(float primeraParte, float shoulder, float elbow, float elbow2, float foco, objeto *baseX,float primeraParteF, float shoulderF, float elbowF, float elbow2F, float focoF, objeto *baseXF, float tiempo,float focoX, float focoY, float focoZ){
    
    
    //Variables iniciales
    
    GLfloat primeraP = primeraParte;
    GLfloat shoulderP = shoulder;
    GLfloat elbowP = elbow;
    GLfloat elbow2P = elbow2;
    GLfloat focoP = foco;
    
    objeto baseXFi = *baseX;
    
    
    //Variables finales
    
    GLfloat primeraPF = primeraParteF;
    GLfloat shoulderPF = shoulderF;
    GLfloat elbowPF = elbowF;
    GLfloat elbow2PF = elbow2F;
    GLfloat focoPF = focoF;
    
    objeto baseXFF = *baseXF;
    
    //Datos de interpolacion
    
    //Rotaciones
    //Primera Parte
    GLfloat primeraParteRotacion = primeraP + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(primeraPF - primeraP);
    //Shoulder
    GLfloat shoulderRotacion = shoulderP + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(shoulderPF - shoulderP);
    //Elbow1
    GLfloat elbowRotacion = elbowP + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(elbowPF - elbowP);
    //Elbow 2
    GLfloat elbow2Rotacion = elbow2P + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(elbow2PF - elbow2P);
    //Foco
    GLfloat focoRotacion = focoP + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(focoPF - focoP);
    
    //Traslacion
    GLfloat  MoverX = baseXFi.x + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(baseXFF.x - baseXFi.x);
    GLfloat  MoverY = baseXFi.y + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(baseXFF.y - baseXFi.y);
    GLfloat  MoverZ = baseXFi.z + ((sin(tiempo*M_PI-M_PI/2)+1)/2)*(baseXFF.z - baseXFi.z);
    
    //Dibujar Tetera
    dibujarTetera(primeraParteRotacion,shoulderRotacion,elbowRotacion,elbow2Rotacion,focoRotacion,MoverX,MoverY,MoverZ, focoX, focoY, focoZ);
    
}

void Display()
{
    
    
   
    
    //Variables de animacion general
    
    GLfloat primeraParteLectura;
    GLfloat shoulderLectura;
    GLfloat elbowLectura;
    GLfloat elbow2Lectura;
    GLfloat focoLectura;
    GLfloat baseXLectura;
    GLfloat baseYLectura;
    GLfloat baseZLectura;
    GLfloat primeraParteFLectura;
    GLfloat shoulderFLectura;
    GLfloat elbowFlectura;
    GLfloat elbow2FLectura;
    GLfloat focoFLectura;
    GLfloat baseXFLectura;
    GLfloat baseYFLectura;
    GLfloat baseZFLectura;
    GLfloat focoXLectura;
    GLfloat focoYLectura;
    GLfloat focoZLectura;
    
    
    
    if(variablesLinea<10){
        if(EaseInOut){
            if(tiempo<1.0){
                
                tiempo+=0.02;
            }else{
                tiempo=0.0;
                variablesLinea++;
                printf(" tiempo: %f",tiempo);
            }
            std::ifstream infile("example.txt");
            std::string line;
            if(infile.is_open()){
                while (std::getline(infile, line))
                {
                    if(contador>9){
                        contador=0;
                    }
                    printf("Linea :%i\n",contador);
                    if(contador == variablesLinea){
                        std::istringstream iss(line);
                        iss >> primeraParteLectura >> shoulderLectura >> elbowLectura >> elbow2Lectura >> focoLectura >> baseXLectura >> baseYLectura >> baseZLectura >> primeraParteFLectura  >> shoulderFLectura >> elbowFlectura >> elbow2FLectura >> focoFLectura >> baseXFLectura >> baseYFLectura >> baseZFLectura >> focoXLectura >> focoYLectura >> focoZLectura;
                        contador++;
                    }else{
                        contador++;
                    }
                    
                }
                infile.close();
            }
            
            
            
            ang+=0.5;
            glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
            
            
            
            
            glColor3f(1.0,1.0,1.0);
            //Primera Base Inicial
            float baseXfloat = baseXLectura;
            float baseYfloat = ground+baseYLectura;
            float baseZfloat = baseZLectura;
            objeto baseX={baseXfloat,baseYfloat,baseZfloat,0.0f,0.6f,0.0f};
            //Segunda Base Final
            
            float baseXfloat2 = baseXFLectura;
            float baseYfloat2 = ground+baseYFLectura;
            float baseZfloat2 = baseZFLectura;
            objeto baseXFinal={baseXfloat2,baseYfloat2,baseZfloat2,0.0f,0.6f,0.0f};
            
            
            controladorLampara(primeraParteLectura, shoulderFLectura, elbowLectura, elbow2Lectura, focoLectura, &baseX,primeraParteFLectura, shoulderFLectura, elbowFlectura, elbow2FLectura, focoFLectura, &baseXFinal, tiempo, focoXLectura, focoYLectura, focoZLectura);
            
            
        }else{
            
            if(EaseIn){
                
                if(tiempo<1.0){
                    printf("Variable para animacion: %i\n",variablesLinea);
                    tiempo+=0.02;
                }else{
                    tiempo=0.0;
                    variablesLinea++;
                    printf("Variable para animacion: %i ",variablesLinea);
                    printf(" tiempo: %f",tiempo);
                }
                
                
                std::ifstream infile("example.txt");
                std::string line;
                if(infile.is_open()){
                    while (std::getline(infile, line))
                    {
                        if(contador>9){
                            contador=0;
                        }
                        printf("Linea :%i\n",contador);
                        if(contador == variablesLinea){
                            std::istringstream iss(line);
                            iss >> primeraParteLectura >> shoulderLectura >> elbowLectura >> elbow2Lectura >> focoLectura >> baseXLectura >> baseYLectura >> baseZLectura >> primeraParteFLectura  >> shoulderFLectura >> elbowFlectura >> elbow2FLectura >> focoFLectura >> baseXFLectura >> baseYFLectura >> baseZFLectura >> focoXLectura >> focoYLectura >> focoZLectura;
                            contador++;
                        }else{
                            contador++;
                        }
                        
                    }
                    infile.close();
                }
                
                
                
                ang+=0.5;
                glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
                
                
                
                
                glColor3f(1.0,1.0,1.0);
                //Primera Base Inicial
                float baseXfloat = baseXLectura;
                float baseYfloat = ground+baseYLectura;
                float baseZfloat = baseZLectura;
                objeto baseX={baseXfloat,baseYfloat,baseZfloat,0.0f,0.6f,0.0f};
                //Segunda Base Final
                
                float baseXfloat2 = baseXFLectura;
                float baseYfloat2 = ground+baseYFLectura;
                float baseZfloat2 = baseZFLectura;
                objeto baseXFinal={baseXfloat2,baseYfloat2,baseZfloat2,0.0f,0.6f,0.0f};
                
                
                controladorLampara2(primeraParteLectura, shoulderFLectura, elbowLectura, elbow2Lectura, focoLectura, &baseX,primeraParteFLectura, shoulderFLectura, elbowFlectura, elbow2FLectura, focoFLectura, &baseXFinal, tiempo, focoXLectura, focoYLectura, focoZLectura);
                
                
            }else{
                
            }if(EaseOut){
                
                if(tiempo<1.0){
                    printf("Variable para animacion: %i\n",variablesLinea);
                    tiempo+=0.02;
                }else{
                    tiempo=0.0;
                    variablesLinea++;
                    printf("Variable para animacion: %i ",variablesLinea);
                    printf(" tiempo: %f",tiempo);
                }
                
                
                std::ifstream infile("example.txt");
                std::string line;
                if(infile.is_open()){
                    while (std::getline(infile, line))
                    {
                        if(contador>9){
                            contador=0;
                        }
                        printf("Linea :%i\n",contador);
                        if(contador == variablesLinea){
                            std::istringstream iss(line);
                            iss >> primeraParteLectura >> shoulderLectura >> elbowLectura >> elbow2Lectura >> focoLectura >> baseXLectura >> baseYLectura >> baseZLectura >> primeraParteFLectura  >> shoulderFLectura >> elbowFlectura >> elbow2FLectura >> focoFLectura >> baseXFLectura >> baseYFLectura >> baseZFLectura >> focoXLectura >> focoYLectura >> focoZLectura;
                            contador++;
                        }else{
                            contador++;
                        }
                        
                    }
                    infile.close();
                }
                
                
                
                ang+=0.5;
                glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
                
                
                
                
                glColor3f(1.0,1.0,1.0);
                //Primera Base Inicial
                float baseXfloat = baseXLectura;
                float baseYfloat = ground+baseYLectura;
                float baseZfloat = baseZLectura;
                objeto baseX={baseXfloat,baseYfloat,baseZfloat,0.0f,0.6f,0.0f};
                //Segunda Base Final
                
                float baseXfloat2 = baseXFLectura;
                float baseYfloat2 = ground+baseYFLectura;
                float baseZfloat2 = baseZFLectura;
                objeto baseXFinal={baseXfloat2,baseYfloat2,baseZfloat2,0.0f,0.6f,0.0f};
                
                
                controladorLampara3(primeraParteLectura, shoulderFLectura, elbowLectura, elbow2Lectura, focoLectura, &baseX,primeraParteFLectura, shoulderFLectura, elbowFlectura, elbow2FLectura, focoFLectura, &baseXFinal, tiempo, focoXLectura, focoYLectura, focoZLectura);
                
                
            }if(Linear){
                
                if(tiempo<1.0){
                    printf("Variable para animacion: %i\n",variablesLinea);
                    tiempo+=0.02;
                }else{
                    tiempo=0.0;
                    variablesLinea++;
                    printf("Variable para animacion: %i ",variablesLinea);
                    printf(" tiempo: %f",tiempo);
                }
                
                std::ifstream infile("example.txt");
                std::string line;
                if(infile.is_open()){
                    while (std::getline(infile, line))
                    {
                        if(contador>9){
                            contador=0;
                        }
                        printf("Linea :%i\n",contador);
                        if(contador == variablesLinea){
                            std::istringstream iss(line);
                            iss >> primeraParteLectura >> shoulderLectura >> elbowLectura >> elbow2Lectura >> focoLectura >> baseXLectura >> baseYLectura >> baseZLectura >> primeraParteFLectura  >> shoulderFLectura >> elbowFlectura >> elbow2FLectura >> focoFLectura >> baseXFLectura >> baseYFLectura >> baseZFLectura >> focoXLectura >> focoYLectura >> focoZLectura;
                            contador++;
                        }else{
                            contador++;
                        }
                        
                    }
                    infile.close();
                }
                
                
                
                ang+=0.5;
                glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
                
                
                
                
                glColor3f(1.0,1.0,1.0);
                //Primera Base Inicial
                float baseXfloat = baseXLectura;
                float baseYfloat = ground+baseYLectura;
                float baseZfloat = baseZLectura;
                objeto baseX={baseXfloat,baseYfloat,baseZfloat,0.0f,0.6f,0.0f};
                //Segunda Base Final
                
                float baseXfloat2 = baseXFLectura;
                float baseYfloat2 = ground+baseYFLectura;
                float baseZfloat2 = baseZFLectura;
                objeto baseXFinal={baseXfloat2,baseYfloat2,baseZfloat2,0.0f,0.6f,0.0f};
                
                
                controladorLampara4(primeraParteLectura, shoulderFLectura, elbowLectura, elbow2Lectura, focoLectura, &baseX,primeraParteFLectura, shoulderFLectura, elbowFlectura, elbow2FLectura, focoFLectura, &baseXFinal, tiempo, focoXLectura, focoYLectura, focoZLectura);
                
                
            }
        }
        
        
        //Ejemplo de datos que lleva mi método de arriba
        
        glutSwapBuffers();
        sleep(0.5);
        glutPostRedisplay();

    }else{
        exit(0);
    }

    
}

void Reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    initRendering();
     glutKeyboardFunc(Keyboard);
    glutDisplayFunc(Display);
   
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}
