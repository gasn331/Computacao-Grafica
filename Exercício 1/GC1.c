#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


GLfloat xf, yf, win;
GLint view_w, view_h;
float escala = 1;

void Desenha(void);
void Inicializa(void);
void GerenciaTeclado(unsigned char key, int x, int y);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);

void main(int argc, char** argv){
     int x, y;
    
 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(50,50);
    glutCreateWindow ("Exercicio 01 --- Grupo 07");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glOrtho (0, 1, 0, 1, -1 ,1);
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(GerenciaTeclado);
    
    Inicializa();
    glutMainLoop();
   
}


// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glVertex2f(0.125*escala,0.125*escala); //baixo esq
    glVertex2f(0.375*escala,0.125*escala); //baixo dir
    glVertex2f(0.245*escala,0.375*escala); //cima
    glEnd();
    glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa (void){
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
// Função callback chamada para gerenciar eventos de teclado
void GerenciaTeclado(unsigned char key, int x, int y){
	switch (key) {
		case 'g':
		case 'G':// muda a escala pra grande
		    escala = 2.0;
		break;
		case 'm':
		case 'M':// muda a escala pra muito grande
		    escala = 4.0;
		break;
		case 'n':
		case 'N'://muda a escala para Normal
		    escala = 1;
		break;
	}
	glutPostRedisplay();
}
