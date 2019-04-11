#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Coordenadas_poligono{
	int quantidade_de_lados;
	GLfloat *coordenadas_x, *coordenadas_y, *coordenadas_z;
}CoordenadasTriangulo;

CoordenadasTriangulo Triangulo;
GLint view_w, view_h;
GLfloat xf, yf, win;
float parametro_x = 0, parametro_y = 0;
float temp_x = 0, temp_y = 0, last_x=0, last_y=0;
int flag=0;

void Desenha(void);
void Inicializa(void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void rotacionar(double angulo);
void mouse(int x, int y);
void mouse_click (int button, int state, int x, int y);

int main(int argc, char** argv){
    
    
    //Inicializacao de um poligono de 3 lados
    Triangulo.quantidade_de_lados = 3;
    Triangulo.coordenadas_x = (GLfloat *)malloc(sizeof(GLfloat)*Triangulo.quantidade_de_lados);
    Triangulo.coordenadas_y = (GLfloat *)malloc(sizeof(GLfloat)*Triangulo.quantidade_de_lados);
    Triangulo.coordenadas_z = (GLfloat *)malloc(sizeof(GLfloat)*Triangulo.quantidade_de_lados);
    Triangulo.coordenadas_x[0] = 0.125;
    Triangulo.coordenadas_x[1] = 0.375;
    Triangulo.coordenadas_x[2] = 0.250;
    Triangulo.coordenadas_y[0] = 0.125;
    Triangulo.coordenadas_y[1] = 0.125;
    Triangulo.coordenadas_y[2] = 0.375;
    Triangulo.coordenadas_z[0] = 0.0;
    Triangulo.coordenadas_z[1] = 0.0;
    Triangulo.coordenadas_z[2] = 0.0;
    //-----------------------------------------------
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(0,0);
    glutCreateWindow ("Exercicio 01 --- Grupo 07");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glOrtho (0, 2, 0, 2, -2 ,2);
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);

    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse);
    
    Inicializa();
    glutMainLoop();
	return 0;
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{ 
    int i;
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    
    //if(parametro_x == 0){
        glVertex3f(temp_x + Triangulo.coordenadas_x[0],temp_y + Triangulo.coordenadas_y[0], Triangulo.coordenadas_z[0]); //baixo esq
        glVertex3f(temp_x + Triangulo.coordenadas_x[1],temp_y + Triangulo.coordenadas_y[1], Triangulo.coordenadas_z[1]); //baixo dir
        glVertex3f(temp_x + Triangulo.coordenadas_x[2],temp_y + Triangulo.coordenadas_y[2], Triangulo.coordenadas_z[2]); //cima
    
    for(i = 0; i < 3; i++){
        Triangulo.coordenadas_x[i] = temp_x + Triangulo.coordenadas_x[i];
        Triangulo.coordenadas_y[i] = temp_y + Triangulo.coordenadas_y[i];
    }

    glEnd();
    glFlush();
}
// Inicializa parâmetros de rendering
void Inicializa (void){
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	view_w = w;
	view_h = h;
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-win, win, -win, win);
}

/*Função de callback para detectar posição do mouse*/

/* Variaveis x e y representam a posição do mouse em coordenadas do dispositivo
   a função converte as coordenadas do dispositivo em coordenadas reais        */
void mouse(int x, int y){ 
    GLdouble ox=0.0,oy=0.0,oz=0.0;
    GLint viewport[4];
    GLdouble modelview[16],projection[16];
    GLfloat wx=x,wy,wz;
    // ------ Conversão de coordenadas ------ //
    glGetIntegerv(GL_VIEWPORT,viewport);
    y=viewport[3]-y;
    wy=y;
    glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
    glGetDoublev(GL_PROJECTION_MATRIX,projection);
    glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,& wz);
    gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);
    glutPostRedisplay();
    // -------------------------------------- //
    parametro_x = ox;
    parametro_y = oy;
    
    if( (ox >= Triangulo.coordenadas_x[0] && ox <= Triangulo.coordenadas_x[1]) && (oy >= Triangulo.coordenadas_y[0] && oy <= Triangulo.coordenadas_y[2]) ){
        printf("Dentro desgraça\n");
        if(flag == 1){ 
            temp_x =  parametro_x - last_x;
            temp_y =  parametro_y - last_y;
            last_x = parametro_x;
            last_y = parametro_y;
        }
        else{
            temp_x = 0;
            temp_y = 0;
            last_x = parametro_x;
            last_y = parametro_y;
            flag = 1;
        }
        printf("tempx -> %f  ||| tempy-> %f\n", temp_x, temp_y);
    }   
    //printf("World %f, %f, %f)\n", ox, oy,oz);
    printf("Mouse ANDANDO pressionado na janela. Posição: (%d, %d)\n", x,y);
}

void mouse_click (int button, int state, int x, int y) { 
    int a1, b1, a2, b2;
    GLdouble ox=0.0,oy=0.0,oz=0.0;
    GLint viewport[4];
    GLdouble modelview[16],projection[16];
    GLfloat wx=x,wy,wz;
    // ------ Conversão de coordenadas ------ //
    glGetIntegerv(GL_VIEWPORT,viewport);
    y=viewport[3]-y;
    wy=y;
    glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
    glGetDoublev(GL_PROJECTION_MATRIX,projection);
    glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,& wz);
    gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);
    glutPostRedisplay();
    // -------------------------------------- //
    
    if (state == GLUT_DOWN){
        printf("Ta dentro\n");
        
        temp_x = 0;
        temp_y = 0;
        flag = 0;
    /*
        a1 = (Triangulo.coordenadas_y[2] - Triangulo.coordenadas_y[0])/(Triangulo.coordenadas_x[2] - Triangulo.coordenadas_x[0]);
        a2 = (Triangulo.coordenadas_y[2] - Triangulo.coordenadas_y[1])/(Triangulo.coordenadas_x[2] - Triangulo.coordenadas_x[1]);
        b1 = Triangulo.coordenadas_y[2] - a1*Triangulo.coordenadas_x[2];
        b2 = Triangulo.coordenadas_y[2] - a2*Triangulo.coordenadas_x[2];
        
        
        if( (ox >= Triangulo.coordenadas_x[0] && ox <= Triangulo.coordenadas_x[1]) && 
            (oy >= Triangulo.coordenadas_y[0] && oy <= Triangulo.coordenadas_y[2]) ){
        
            printf("Dentro\n");
            flag = 1;
            /*
            if( ((a1*ox + b1) > oy) && ((a2*ox + b2) > oy) ){
                printf("Dentro do triangulo\n");
            }
            
        }
        else 
            flag = 2;
        */

    }

    if(state == GLUT_UP){
        flag = 0;
        printf("saiu\n");
    }
}