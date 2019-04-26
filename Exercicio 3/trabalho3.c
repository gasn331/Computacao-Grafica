#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

typedef struct a {
	int x,y	
} Ponto;

void desenhaLinha(Ponto p1, Ponto p2){
	int i;
	GLint x,y;
	
	//Calcula o coeficiente angular da reta
	double m = (double) (p2.y - p1.y) / (p2.x - p1.x);
	
	for (i=p1.x; i<p2.x; i++){
		x = i;
		
		//Para cada x, calcula o y a ser pintado de acordo com o coeficiente da reta
		y = round(p1.y + m * (i - p1.x));
		
		//Desenha o ponto (x,y)
		glBegin(GL_POINTS);
			glVertex2i(x, y);
		glEnd();
	}
}

void displayFcn(void){
	//Cria e configura o ponto inicial da linha (p1) e o ponto final da linha (p2)
	Ponto p1, p2;
	p1.x = 50;
	p1.y = 50;
	p2.x = 500;
	p2.y = 500;
	
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0,0.0,1.0);
	
	//Chama a função pra desenhar a linha
	desenhaLinha (p1,p2);
	
	//Atualiza a tela
	glFlush();

}

main(int argc, char** argv){
	//Inicializa
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 100);
	glutInitWindowSize (400, 300);
	glutCreateWindow ("Desenha Linha"); 
	glClearColor (1.0,1.0,1.0,0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
	
	glutDisplayFunc(displayFcn);//Define a função de display
	glutMainLoop();
}