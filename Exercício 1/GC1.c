#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


GLfloat xf, yf, win;
typedef struct Coordenadas_poligono{
	int quantidade_de_lados;
	GLfloat *coordenadas_x, *coordenadas_y;
}CoordenadasTriangulo;
GLint view_w, view_h;

CoordenadasTriangulo Triangulo;
float escala = 1;

void Desenha(void);
void Inicializa(void);
void GerenciaTeclado(unsigned char key, int x, int y);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void rotaciona_poligono();

void main(int argc, char** argv){
    
    int x, y, quantidade_de_lados;
    //Inicializacao de um poligono de 3 lados
    quantidade_de_lados = 3;
    Triangulo.coordenadas_x = (GLfloat *)malloc(sizeof(GLfloat)*quantidade_de_lados);
    Triangulo.coordenadas_y = (GLfloat *)malloc(sizeof(GLfloat)*quantidade_de_lados);
    Triangulo.coordenadas_x[0] = 0.125;
    Triangulo.coordenadas_x[1] = 0.375;
    Triangulo.coordenadas_x[2] = 0.245;
    Triangulo.coordenadas_y[0] = 0.125;
    Triangulo.coordenadas_y[1] = 0.125;
    Triangulo.coordenadas_y[2] = 0.375;
    //-----------------------------------------------
    
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
    glVertex2f(Triangulo.coordenadas_x[0]*escala, Triangulo.coordenadas_y[0]*escala); //baixo esq
    glVertex2f(Triangulo.coordenadas_x[1]*escala, Triangulo.coordenadas_y[1]*escala); //baixo dir
    glVertex2f(Triangulo.coordenadas_x[2]*escala, Triangulo.coordenadas_y[2]*escala); //cima
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
			escala += 0.4;
		break;
		case 'm':
		case 'M':// muda a escala menor
			escala -= 0.4;
		break;
		case 'n':
		case 'N':
			//coloque aqui os teclas para rotação/translação
		break;
	}
	glutPostRedisplay();
}
