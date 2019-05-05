// Controls:    Seta para Esquerda - Rotacionar para Esquerda
//              Seta para Direita - Rotaciona para direita
//              Seta para Cima    - Rotaciona para cima
//              Seta para Baixo - Rotaciona para Baixo     
 
// ----------------------------------------------------------
// Inclusões
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
 
// ----------------------------------------------------------
// Declarações de Funções
// ----------------------------------------------------------
void display();
void specialKeys();
 
// ----------------------------------------------------------
// Variáveis Globais
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
GLsizei winWidth = 600, winHeight = 600;
 
// ----------------------------------------------------------
// função display() 
// ----------------------------------------------------------
void display(){
	//  Limpa a tela e o Z-Buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Reinicia transformações
	glLoadIdentity();

	// Rotaciona quando o usuário muda rotate_x e rotate_y
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );

	//Lado multicolorido - FRENTE
	glBegin(GL_POLYGON);
		glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 é vermelho
		glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 é verde
		glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 é azul
		glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 é roxo
	glEnd();

	// Lado branco - TRASEIRA
	glBegin(GL_POLYGON);
		glColor3f(   1.0,  1.0, 1.0 );
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	// Lado roxo - DIREITA
	glBegin(GL_POLYGON);
		glColor3f(  1.0,  0.0,  1.0 );
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	// Lado verde - ESQUERDA
	glBegin(GL_POLYGON);
		glColor3f(   0.0,  1.0,  0.0 );
		glVertex3f( -0.5, -0.5, 0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	// Lado azul - TOPO
	glBegin(GL_POLYGON);
		glColor3f(   0.0,  0.0,  1.0 );
		glVertex3f(  0.5,  0.5,  0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	// Lado vermelho - BASE
	glBegin(GL_POLYGON);
		glColor3f(   1.0,  0.0,  0.0 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	glFlush();
	glutSwapBuffers();
}
 
// ----------------------------------------------------------
// Função specialKeys()
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) {
	//  Seta direita - aumenta rotação em 5 graus
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;
	//  Seta para esquerda - diminui a rotação por 5 graus
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Requisitar atualização do display
	glutPostRedisplay();
 
}

void animation(void){
	rotate_y += 2;
	rotate_x += 2;
	display();
}
 
// ----------------------------------------------------------
// Função main()
// ----------------------------------------------------------
int main(int argc, char* argv[]){
	//  Inicializa o GLUT e processa os parâmetros do usuário GLUT
	glutInit(&argc,argv);

	//  Requisita uma janela com buffer duplo e true color com um Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(50,50);

	// Cria a janela do programa
	glutCreateWindow("Exercicio 4 - Cube Ortogonal");

	//  Habilita o teste de profundidade do Z-buffer
	glEnable(GL_DEPTH_TEST);

	// Funções
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	//Set the function for the animation.
	glutIdleFunc(animation);
	//  Passa o controle dos eventos para o GLUT
	glutMainLoop();

	//  Retorna para o SO
	return 0;
}