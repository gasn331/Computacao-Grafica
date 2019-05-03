#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

typedef struct paleta_de_cores{ //estrutura criada com a finalidade de manter a paleta de cores a ser utilizada na função MidPointCircle
	GLfloat cores[3];
}cor;

/* limites para as coordenadas do mundo */
GLsizei  winWidth = 600,  winHeight = 600;
GLfloat xwcMin = -255.0, xwcMax = 255.0;
GLfloat  ywcMin = -255.0, ywcMax = 255.0;
/*--------------------------------------*/
cor paleta;

void write_pixel(GLfloat x, GLfloat y, cor paleta){ //funçao que pinta um pixel na tela
	glBegin(GL_POINTS);
	glColor3f(paleta.cores[0],paleta.cores[1],paleta.cores[2]);
	glVertex2i(x,y);
	glEnd();
}

void write_line(GLfloat x, GLfloat y, GLfloat x2, GLfloat y2, cor paleta){ //Funçao analoga ao write_pixel, foi uma tentativa de pintar o circulo
	glBegin(GL_LINES);
	glColor3f(paleta.cores[0],paleta.cores[1],paleta.cores[2]);
	glVertex2i(x,y);
	glVertex2i(x2,y2);
	glEnd();
}

void CirclePoints(int x, int y, cor paleta){ //A função MidPointCircle apenas desenha um quadrante da circunferência, portanto essa função é necessária para achar os outros pontos que completam a cincunferência
	write_pixel( x, y, paleta);
	write_pixel( x, -y, paleta);
	write_pixel(-x, y, paleta);
	write_pixel(-x, -y, paleta);
	write_pixel( y, x, paleta);
	write_pixel( y, -x, paleta);
	write_pixel(-y, x, paleta);
	write_pixel(-y, -x, paleta);
}/*end CirclePoints*/

void CircleLines(int x, int y, cor paleta){ //Função analoga ao CirclePoints, seria uma função para ser utilizada junto com o write_line com a finalidade de pintar o circulo, porém não está sendo usada
	write_line( x, y, x, -y,paleta);
	write_line( x, -y, -x, y, paleta);
	write_line(-x, y, -x, -y, paleta);
	write_line(-x, -y, y, x, paleta);
	write_line( y, x, y, -x, paleta);
	write_line( y, -x, -y, x, paleta);
	write_line(-y, x, -y, -x, paleta);
	write_line(-y, -x, x, y, paleta);
}/*end CirclePoints*/

void MidpointCircle(int radius,cor paleta){ //função que desenha a circunferência dado um raio e cor utilizando a teoria do ponto médio
	int x = 0;
	int y = radius;
	int d = 1 - radius;
	CirclePoints(x, y, paleta);
	//CircleLines(x, y, paleta);
	while(y > x) {
		if(d < 0) d += 2 * x + 3;
		else{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		CirclePoints(x, y, paleta);
		//CircleLines(x, y, paleta);
	}
}

/* Janela inicial */
void init (void)
{
	/* determina cor da janela de branca*/
	glClearColor (1.0,1.0,1.0,1.0);
}

void displayFcn (void)
{
	srand(time(NULL));
	paleta.cores[0]=(rand() % 100)/100;
	paleta.cores[1]=(rand() % 100)/100;
	paleta.cores[2]=(rand() % 100)/100;
	MidpointCircle(200,paleta); // 200 é o raio da circunferência
	glFlush();
}
void winReshapeFcn (GLint newWidth, GLint newHeight)
{ 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (xwcMin, xwcMax,ywcMin, ywcMax);
	glClear (GL_COLOR_BUFFER_BIT);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Circunferencia");
	init();
	glutDisplayFunc(displayFcn);    
	glutReshapeFunc(winReshapeFcn);    
	glutMainLoop();
}
