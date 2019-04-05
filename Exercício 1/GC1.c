#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*'Coordenadas_poligono' serve como base para a criacao de poligonos
 * Nesse caso estamos gerando um Triangulo */
typedef struct Coordenadas_poligono{
	int quantidade_de_lados;
	GLfloat *coordenadas_x, *coordenadas_y, *coordenadas_z;
}CoordenadasTriangulo;

CoordenadasTriangulo Triangulo;
GLint view_w, view_h;
GLfloat xf, yf, win;
float escala = 1;
double Valor_fixo_rotacao = 30.0;

void Desenha(void);
void Inicializa(void);
void GerenciaTeclado(unsigned char key, int x, int y);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void rotacionar(double angulo);

void main(int argc, char** argv){
    
    int x, y;
    //Inicializacao de um poligono de 3 lados
    Triangulo.quantidade_de_lados = 3;
    Triangulo.coordenadas_x = (GLfloat *)malloc(sizeof(GLfloat)*Triangulo.quantidade_de_lados);
    Triangulo.coordenadas_y = (GLfloat *)malloc(sizeof(GLfloat)*Triangulo.quantidade_de_lados);
    Triangulo.coordenadas_z = (GLfloat *)malloc(sizeof(GLfloat)*Triangulo.quantidade_de_lados);
    Triangulo.coordenadas_x[0] = 0.125;
    Triangulo.coordenadas_x[1] = 0.375;
    Triangulo.coordenadas_x[2] = 0.245;
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
void Desenha(void){
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(Triangulo.coordenadas_x[0]*escala, Triangulo.coordenadas_y[0]*escala, Triangulo.coordenadas_z[0]*escala); //baixo esq
    glVertex3f(Triangulo.coordenadas_x[1]*escala, Triangulo.coordenadas_y[1]*escala, Triangulo.coordenadas_z[1]*escala); //baixo dir
    glVertex3f(Triangulo.coordenadas_x[2]*escala, Triangulo.coordenadas_y[2]*escala, Triangulo.coordenadas_z[2]*escala); //cima
    glEnd();
    glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa (void){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	view_w = w;
	view_h = h;
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-win, win, -win, win);
}
/*Funcao para rotacao ao redor do eixo Z
 * parametros: double angulo -> espera um valor real com o angulo de rotacao
 */
void rotacionar(double angulo){
	GLfloat nova_coordenada_x, nova_coordenada_y;
	int contador;
	double seno_angulo, cosseno_angulo;
	seno_angulo = sin(angulo);
	cosseno_angulo = cos(angulo);
	for(contador = 0; contador < Triangulo.quantidade_de_lados; contador++){
		//Calcula as coordenadas x e y de acordo com os calculos da matriz de rotação
		nova_coordenada_x = Triangulo.coordenadas_x[contador]*cosseno_angulo - Triangulo.coordenadas_y[contador]*seno_angulo;
		nova_coordenada_y = Triangulo.coordenadas_x[contador]*seno_angulo + Triangulo.coordenadas_y[contador]*cosseno_angulo;
		Triangulo.coordenadas_x[contador] = nova_coordenada_x;
		Triangulo.coordenadas_y[contador] = nova_coordenada_y;
	}
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
		case 'r':
		case 'R':
			rotacionar(Valor_fixo_rotacao);
			//rotacionar, o valor fixado esta em 30 graus
			break;
	}
	glutPostRedisplay();
}

