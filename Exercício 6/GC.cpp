// Controles:   Seta para Esquerda - Rotacionar para Esquerda
//              Seta para Direita - Rotaciona para direita
//              Seta para Cima    - Rotaciona para cima
//              Seta para Baixo - Rotaciona para Baixo     
 
/* ----------------------------------------------------------
**  Inclusões
** --------------------------------------------------------*/
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <bits/stdc++.h>

using namespace std;
 
// ----------------------------------------------------------
// Variáveis Globais
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
double rotate_z=0;
GLsizei winWidth = 600, winHeight = 600;
char title[] = "Cube 3D - Perspective";
 
/* Initialize OpenGL Graphics */
void initGL() {
   
}
 
// ----------------------------------------------------------
// função display() 
// ----------------------------------------------------------
void display() {
	/* ------------------------------
   ** Limpa buffers para valores
   ** predefinidos
   ** -----------------------------*/
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   

   /* ------------------------------
   ** Especifica qual pilha de matriz
   ** será o destino das operações
   ** de matriz subsequentes
   ** -----------------------------*/
   glMatrixMode(GL_MODELVIEW);

   /* ------------------------------
   ** Reinicia as transformações
   ** Carrega uma matriz identidade
   ** -----------------------------*/
   glLoadIdentity();

   /* ------------------------------
   ** Transformação de Translação
   ** -----------------------------*/ 
   glTranslatef(0.0f, 0.0f, -7.0f);
   
   /* ------------------------------
   ** Rotacioar o cubo
   ** -----------------------------*/
   glRotatef(rotate_y, 0.0, 1.0, 0.0 );
   glRotatef(rotate_x, 1.0, 0.0, 0.0 );
   glRotatef(rotate_z, 1.0, 0.0, 0.0 );
   /*------------------------------*/

   /* ------------------------------
   ** Color Cube: Vermelho
   ** -----------------------------*/
   glColor3f(0.9, 0.0, 0.0);

   /* ------------------------------
   ** Transformação de escala
   ** -----------------------------*/
   glScalef(3.0,3.0,3.0);

   /* ------------------------------
   ** Cubo feito apartir do OpenGL
   ** Visualização de Wireframe
   ** -----------------------------*/
   glutWireCube(1.0);

   /* ------------------------------
   ** Flush Buffer da tela
   ** -----------------------------*/
   glFlush();  

   /* ------------------------------
   ** Executa uma troca de buffer na
   ** camada em uso para a janela atual
   ** -----------------------------*/
   glutSwapBuffers();
}

/* ----------------------------------------------------------
** Handler void reshape(GLsizei width, GLsizei height);
** Handler chamado quando a janela aparece pela primeira vez e
** sempre que a janela é redimensionada com sua nova largura e altura
** --------------------------------------------------------*/
void reshape(GLsizei width, GLsizei height) {
   if (height == 0) height = 1;
 
   glViewport(0, 0, width, height);
   
   /* ------------------------------
   ** Especifica qual pilha de matriz
   ** será o destino das operações
   ** de matriz subsequentes
   ** -----------------------------*/
   glMatrixMode(GL_PROJECTION);

   /* ------------------------------
   ** Reinicia as transformações
   ** Carrega uma matriz identidade
   ** -----------------------------*/
   glLoadIdentity();

   /* ------------------------------
   ** Matriz de projeção - Perspectiva
   ** -----------------------------*/
   
   GLdouble left = (-0.09);
   GLdouble right = (0.09);
   GLdouble bottom = (-0.09); 
   GLdouble top = (0.09);
   GLdouble near = 0.1f;
   GLdouble far = 100.0f;

   GLdouble matrixPerspective[16] = {(2*near/(right-left)), 0, 0, 0, 0, (2*near/(top-bottom)), 0, 0, ((right+left)/(right-left)), ((top+bottom)/(top-bottom)), ((far+near)/(far-near)), -1, 0, 0, ((2*far*near)/(far-near)), 0};
   
   /* -----------------------------------------------------------------------------------------------------
   [2*near/(right-left)] [0]                    [(right+left)/(right-left)]   [0]
   [0]                   [2*near/(top-bottom)]  [(top+bottom)/(top-bottom)]   [0]
   [0]                   [0]                    [(far+near)/(far-near)]       [(2*far*near)/(far-near)]
   [0]                   [0]                    [-1]                          [0]
   ----------------------------------------------------------------------------------------------------- */
   
   /* ------------------------------
   ** Função responsavel pela
   ** multiplicação de Matrizes
   ** -----------------------------*/
   glMultMatrixd(matrixPerspective);

   /* ------------------------------
   ** Especifica qual pilha de matriz
   ** será o destino das operações
   ** de matriz subsequentes
   ** -----------------------------*/
   glMatrixMode(GL_MODELVIEW);

}

/* ----------------------------------------------------------
** Função specialKeys()
** Função callback chamada para gerenciar eventos de teclas especiais
** --------------------------------------------------------*/
void specialKeys( int key, int x, int y ) {
	//  Seta direita - aumenta rotação em 5 graus
	if (key == GLUT_KEY_RIGHT) // Seta para direita - aumenta a rotação no eixo y por 5 graus
		rotate_y += 5;
	
	else if (key == GLUT_KEY_LEFT) // Seta para esquerda - diminui a rotação no eixo y por 5 graus
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP) // Seta para cima - diminui a rotação no eixo x por 5 graus
		rotate_x -= 5;

	else if (key == GLUT_KEY_DOWN) // Seta para baixo - aumenta a rotação no eixo x por 5 graus
		rotate_x += 5;

	//Requisitar atualização do display
	glutPostRedisplay();
}

/* ----------------------------------------------------------
** Função normalKeys()
** Função callback chamada para gerenciar eventos de teclas
** --------------------------------------------------------*/
void normalKeys (unsigned char key, int x, int y){
	
   if (key == 27) // Tecla Esc
		exit(0);
}

/* ----------------------------------------------------------
** Função animation()
** Incrementa + 1 grau para cada frame
** --------------------------------------------------------*/
void animation(void){
   rotate_y += 1;
   rotate_x += 1;
   rotate_z += 1;
   display();
}

/* ----------------------------------------------------------
** Função main()
** --------------------------------------------------------*/
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Ativa o modo de Bufferização - "GLUT_DOUBLE"
   glutInitWindowSize(winWidth, winHeight);   // Inicia a janela com a altura "winHeight" e largura "winWinth"
   glutInitWindowPosition(50, 50); // Posição inicial da janela
   glutCreateWindow(title);          // Cria uma janela com o nome da varialvel "title"
   
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);       // callback handler para a janela, quando é redimensionada

   glutSpecialFunc(specialKeys);
   glutKeyboardFunc(normalKeys);
   
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Background color para preto

   glutMainLoop();
   return 0;
}