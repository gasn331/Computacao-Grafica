// Controls:    Seta para Esquerda - Rotacionar para Esquerda
//              Seta para Direita - Rotaciona para direita
//              Seta para Cima    - Rotaciona para cima
//              Seta para Baixo - Rotaciona para Baixo     

// ----------------------------------------------------------
// Inclusões
// ----------------------------------------------------------
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <bits/stdc++.h>
using namespace std;
// ----------------------------------------------------------
// Variáveis Globais
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;
double rotate_z = 0;
GLsizei winWidth = 600, winHeight = 600;
char title[] = "Cube 3D - Back-face culling";
vector<vector<vector<float>>> faces(6);
int cullface_FRONT = 1;
/* Initialize OpenGL Graphics */
void initGL() {

}
/* ----------------------------------------------------------
 ** função Produto_vetorial() 
 * Calcula o produto vetorial de dois vetores em R3
 ** ---------------------------------------------------------*/
void Produto_Vetorial(vector<float> vec1, vector<float> vec2,
		vector<float> &normal) {
	normal.push_back(vec1[1] * vec2[2] - vec1[2] * vec2[1]);
	normal.push_back(vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	normal.push_back(vec1[0] * vec2[1] - vec1[1] * vec2[0]);
}
/* ----------------------------------------------------------
** função Normalizar()
** A normalização de uma face determina a direção para a qual está apontada.
** Assim, queremos comparar a direção da face com a direção da câmera, como explicado em display()
** ---------------------------------------------------------*/
vector<float> Normalizar(vector<float> vec1, vector<float> vec2,
		vector<float> vec3) {
	vector<float> vec_a, vec_b, normal;
	float sum = 0;
	int i;
	for (i = 0; i < 3; i++) {
		//vec3 - vec2
		vec_a.push_back(vec3[i] - vec2[i]);
		//vec1 - vec2
		vec_b.push_back(vec1[i] - vec2[i]);
	}
	Produto_Vetorial(vec_a, vec_b, normal);
	/* determina a magnitude do vetor normal */
	for (i = 0; i < 3; i++)
		sum += normal[i] * normal[i];
	sum = sqrt(sum);
	/********************************* */
	for (i = 0; i < 3; i++)
		normal[i] /= sum;
	return normal;
}
/* ----------------------------------------------------------
 ** função Produto_Escalar()
 * Calcula o produto escalar entre dois vetores em R3 
 ** ---------------------------------------------------------*/
float Produto_Escalar(vector<float> vec1, vector<float> vec2) {
	float produto = 0;
	for (int i = 0; i < 3; i++) {
		produto += vec1[i] * vec2[i];
	}
	return produto;
}
// ----------------------------------------------------------
// função display() 
// ----------------------------------------------------------
void display() {
	//  Limpa a tela e o Z-Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	/*A função glMatrixMode() especifica agora que a pilha de matrizes de modelview,
	 usadas para definir translação, rotação e escalamento, será o alvo das
	 transformações subseqüentes.*/

	// Reinicia transformações
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);
	//Rotaciona o cubo
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_z, 1.0, 0.0, 0.0);

	float modelview[16], angle;
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	vector<float> normal, camera;
	/*
	 * Recupera a direção pra qual a camera está apontando a partir
	 * da matrix Modelview
	 */
	camera.push_back(modelview[2]);
	camera.push_back(modelview[6]);
	camera.push_back(modelview[10]);
	/********************************* */
	glBegin (GL_QUADS);
	// Top face (y = 1.0f)
	
	/* calcula o vetor normal da respectiva face do cubo,
	 * nesse caso a normal é calculada em ordem anti-horária,
	 * seguindo os vértives 0 -> 2 -> 1
	 * O vetor normal determina a direção para qual a face está apontada
	 */
	//normal = Normalizar(faces[0][0],faces[0][1],faces[0][2]);
	normal = Normalizar(faces[0][0], faces[0][2], faces[0][1]);
	/********************************* */
	/*A partir do vetor normal da face e do vetor da direção da câmera calculamos
	 * o produto escalar entre eles. O produto escalar retorna o ângulo formado
	 * de um vetor em relação ao outro, assim sabemos se apontam na mesma direção
	 * ou em direções opostas.
	 */
	angle = Produto_Escalar(normal, camera);
	/********************************* */
	/*Portanto, se o angle(ângulo) calculado pelo produto escalar for maior que zero,
	 * sabemos que a câmera e a face estão apontando para a mesma direção, determinando
	 * que essa face é uma front face, então, a mesma é desenhada.
	 * A interpretação do sinal do produto escalar é determinada de acordo com a forma que
	 * o vetor normal da face foi calculado, se o cálculo fosse feito no sentido horário,
	 * então a interpretação seria invertida.
	 * 
	 * PS: Esta implementação permite a front-face culling, basta retirar '//' de CULLFACE_FRONT() na função main.
	 * Aqui o front-face culling apenas inverte o sinal do ângulo.
	 */
	if (cullface_FRONT * angle > 0) {
		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
	}
	// Bottom face (y = -1.0f)
	//normal = Normalizar(faces[1][0],faces[1][1],faces[1][2]);
	normal = Normalizar(faces[1][0], faces[1][2], faces[1][1]);
	angle = Produto_Escalar(normal, camera);
	if (cullface_FRONT * angle > 0) {
		glColor3f(1.0f, 0.5f, 0.0f);     // Orange
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	}
	// Front face  (z = 1.0f)
	//normal = Normalizar(faces[2][0],faces[2][1],faces[2][2]);
	normal = Normalizar(faces[2][0], faces[2][2], faces[2][1]);
	angle = Produto_Escalar(normal, camera);
	if (cullface_FRONT * angle < 0) {
		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
	}
	// Back face (z = -1.0f)
	//normal = Normalizar(faces[3][0],faces[3][1],faces[3][2]);
	normal = Normalizar(faces[3][0], faces[3][2], faces[3][1]);
	angle = Produto_Escalar(normal, camera);
	if (cullface_FRONT * angle < 0) {
		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
	}
	// Left face (x = -1.0f)
	//normal = Normalizar(faces[4][0],faces[4][1],faces[4][2]);
	normal = Normalizar(faces[4][0], faces[4][2], faces[4][1]);
	angle = Produto_Escalar(normal, camera);
	if (cullface_FRONT * angle < 0) {
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	}
	// Right face (x = 1.0f)
	//normal = Normalizar(faces[5][0],faces[5][1],faces[5][2]);
	normal = Normalizar(faces[5][0], faces[5][2], faces[5][1]);
	angle = Produto_Escalar(normal, camera);
	if (cullface_FRONT * angle < 0) {
		glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	}
	glEnd();

	//Executa uma troca de buffer na camada em uso para a janela atual 
	glutSwapBuffers();
}
/* Handler for window re-size event. Called back when the window first appears and
 whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) { // GLsizei for non-negative integer
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	/* ------------------------------
	 ** Especifica qual pilha de matriz
	 ** será o destino das operações
	 ** de matriz subsequentes
	 ** -----------------------------*/
	glMatrixMode (GL_PROJECTION);

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

	GLdouble matrixPerspective[16] = { (2 * near / (right - left)), 0, 0, 0, 0,
			(2 * near / (top - bottom)), 0, 0,
			((right + left) / (right - left)),
			((top + bottom) / (top - bottom)), ((far + near) / (far - near)),
			-1, 0, 0, ((2 * far * near) / (far - near)), 0 };

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
	glMatrixMode (GL_MODELVIEW);

}

/* ----------------------------------------------------------
 ** Função specialKeys()
 ** Função callback chamada para gerenciar eventos de teclas especiais 
 ** --------------------------------------------------------*/
void specialKeys(int key, int x, int y) {
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
void normalKeys(unsigned char key, int x, int y) {
	// Tecla Esc
	if (key == 27)
		exit(0);
}

/* ----------------------------------------------------------
 ** Função animation()
 ** --------------------------------------------------------*/
void animation(void) {

	rotate_y += 2;
	rotate_x += 2;
	rotate_z += 2;
	display();

}
/* ----------------------------------------------------------
 ** função CULLFACE_FRONT 
 ** Habilita o culling das faces do cubo que estão na frente
 ** ---------------------------------------------------------*/
void CULLFACE_FRONT() {
	cullface_FRONT = -1;
}
/* ----------------------------------------------------------
 ** Função main()
 ** --------------------------------------------------------*/
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); // Enable double buffered mode
	glutInitWindowSize(winWidth, winHeight); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title

	//CULLFACE_FRONT(); //Ativa o Front-face Culling
	faces[0] = { {1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}};
	faces[1] = { {1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}};
	faces[2] = { {1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}};
	faces[3] = { {1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, -1.0f}};
	faces[4] = { {-1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}};
	faces[5] = { {1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, -1.0f}};
	glutDisplayFunc(display);
	glEnable (GL_DEPTH_TEST);   // Ativa depth testing for z-culling
	glutReshapeFunc(reshape); // callback handler para a janela, quando é redimensionada

	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(normalKeys);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

	glutIdleFunc(animation); //Set the function for the animation. 

	glutMainLoop();
	return 0;
}
