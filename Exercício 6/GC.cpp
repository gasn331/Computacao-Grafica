// Controls:    Seta para Esquerda - Rotacionar para Esquerda
//              Seta para Direita - Rotaciona para direita
//              Seta para Cima    - Rotaciona para cima
//              Seta para Baixo - Rotaciona para Baixo     
 
// ----------------------------------------------------------
// Inclusões
// ----------------------------------------------------------
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
 
// ----------------------------------------------------------
// Variáveis Globais
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;
double rotate_z=0;
GLsizei winWidth = 600, winHeight = 600;
char title[] = "Cube 3D - Ortogonal";
 
/* Initialize OpenGL Graphics */
void initGL() {
   
}
 
// ----------------------------------------------------------
// função display() 
// ----------------------------------------------------------
void display() {
	//  Limpa a tela e o Z-Buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   glMatrixMode(GL_MODELVIEW);
   /*A função glMatrixMode() especifica agora que a pilha de matrizes de modelview,
   usadas para definir translação, rotação e escalamento, será o alvo das
   transformações subseqüentes.*/
 
   // Reinicia transformações
   glLoadIdentity();                 
   glTranslatef(0.0f, 0.0f, -7.0f);
   //Rotaciona o cubo
   glRotatef(rotate_y, 0.0, 1.0, 0.0 );
   glRotatef(rotate_x, 1.0, 0.0, 0.0 );
   glRotatef(rotate_z, 1.0, 0.0, 0.0 );
 
   glBegin(GL_QUADS);                
      // Top face (y = 1.0f)
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();
   
   //Executa uma troca de buffer na camada em uso para a janela atual 
   glutSwapBuffers(); 
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset

   glFrustum(-0.09, 0.09, -0.09, 0.09, 0.1f, 100.0f);
}

/* ----------------------------------------------------------
** Função specialKeys()
** Função callback chamada para gerenciar eventos de teclas especiais 
** --------------------------------------------------------*/
void specialKeys( int key, int x, int y ) {
	//  Seta direita - aumenta rotação em 5 graus
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;
	//  Seta para esquerda - diminui a rotação por 5 graus
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x -= 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x += 5;

	//Requisitar atualização do display
	glutPostRedisplay();
}

/* ----------------------------------------------------------
** Função normalKeys()
** Função callback chamada para gerenciar eventos de teclas
** --------------------------------------------------------*/
void normalKeys (unsigned char key, int x, int y){
	// Tecla Esc
   if (key == 27) 
		exit(0);
}

/* ----------------------------------------------------------
** Função animation()
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
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); // Enable double buffered mode
   glutInitWindowSize(winWidth, winHeight);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);       // callback handler para a janela, quando é redimensionada

   glutSpecialFunc(specialKeys);
   glutKeyboardFunc(normalKeys);
   
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
   glEnable(GL_DEPTH_TEST);   // Ativa depth testing for z-culling

   /*--------------Z-Czulling--------------
   * Encarregada de gerir as coordenadas de profundidade das imagens
   * nos gráficos em três dimensões (3-D), por forma a eliminar sobreposições
   */

   
   glutIdleFunc(animation); //Set the function for the animation.

   glutMainLoop();
   return 0;
}