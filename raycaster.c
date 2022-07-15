#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.141592653589793238
#define WIDTH 800
#define HEIGHT 800

typedef struct s_player
{
	float	x;
	float	y;
	float	ang;
	float	dx;
	float	dy;
}				t_player;
typedef struct s_vars
{
	t_player	p;
	char		**maps;
}				t_vars;

t_vars	vars;

void	drawMap2D(void)
{
	int	i = 0;
	int	j = 0;
	int	xo;
	int	yo;

	xo = 0;
	yo = 0;
	while (vars.maps[i] != NULL)
	{
		j = 0;
		while (vars.maps[i][j])
		{
			xo = j * (WIDTH / 8);
			yo = i * (HEIGHT / 8);
			if (vars.maps[i][j] == '1')
				glColor3f(1, 0, 0);
			else
				glColor3f(0, 0, 0);
			glBegin(GL_QUADS);
			glVertex2i(xo + 2, yo + 2);
			glVertex2i(xo + 2, yo + (HEIGHT / 8) - 2);
			glVertex2i((xo + (WIDTH / 8)) - 2, (yo + (HEIGHT / 8)) - 2);
			glVertex2i(xo + (WIDTH / 8) - 2, yo + 2);
			glEnd();
			j++;
		}
		i++;
	}
}

void	drawPlayer()
{
	vars.p.dx = cos(vars.p.ang) * 5;
	vars.p.dy = sin(vars.p.ang) * 5;
	glColor3f(0, 1, 1);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2i(vars.p.x, vars.p.y);
	glEnd();
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(vars.p.x, vars.p.y);
	glVertex2i(vars.p.x + (vars.p.dx * 5), vars.p.y + (vars.p.dy * 5));
	glEnd();
}

void	buttons(unsigned char key, int x, int y)
{
	int	row;
	int	col;
	if (key == 'w')
	{
		vars.p.dx = cos(vars.p.ang) * 5;
		vars.p.dy = sin(vars.p.ang) * 5;
		printf("Change in X: %f, Change in Y: %f\n", vars.p.dx, vars.p.dy);
		if ((vars.p.x + vars.p.dx > 0) && (vars.p.x + vars.p.dx < WIDTH)
		&& (vars.p.y + vars.p.dy > 0) && (vars.p.y + vars.p.dy < HEIGHT))
		{
			vars.p.x += vars.p.dx;
			vars.p.y += vars.p.dy;
			printf("X: %f, Y: %f\n", vars.p.x, vars.p.y);
			row = (int)(vars.p.x * 8 / WIDTH);
			col = (int)(vars.p.y * 8 / HEIGHT);
			printf("Row: %d, Col: %d\n", row, col);
		}
	}
	else if (key == 's')
	{
		vars.p.dx = cos(vars.p.ang) * 5;
		vars.p.dy = sin(vars.p.ang) * 5;
		vars.p.x -= vars.p.dx;
		vars.p.y -= vars.p.dy;
	}
	else if (key == 'd')
	{
		vars.p.x -= -cos((PI / 2) + (vars.p.ang)) * 5;
		vars.p.y -= -sin((PI / 2) + (vars.p.ang)) * 5;
	}
	else if (key == 'a')
	{
		vars.p.x -= cos((PI / 2) + (vars.p.ang)) * 5;
		vars.p.y -= sin((PI / 2) + (vars.p.ang)) * 5;
	}
	else if (key == 'k')
	{
		vars.p.ang += 0.1;
		if (vars.p.ang > 2 * PI)
			vars.p.ang -= 2 * PI;
	}
	else if (key == 'j')
	{
		vars.p.ang -= 0.1;
		if (vars.p.ang < 0)
			vars.p.ang += 2 * PI;
	}
	else if (key == 27) { exit(0); }
	glutPostRedisplay();
}

void	display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawPlayer();
	glutSwapBuffers();
}

void	init()
{
	int	i = 0;
	int	j = 0;
	glClearColor(0.2, 0.2, 0.2, 0);
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	
	vars.p.x = 0;
	vars.p.y = 0;
	vars.p.dx = cos(vars.p.ang) * 5;
	vars.p.dy = sin(vars.p.ang) * 5;
	vars.p.ang = 0;
	while (vars.maps[i] != NULL)
	{
		j = 0;
		while (vars.maps[i][j])
		{
			if (vars.maps[i][j] == 'N')
				break;
			j++;
		}
		if (vars.maps[i][j] == 'N')
				break;
		i++;
	}
	vars.p.x = j * (WIDTH/8);
	vars.p.y = i * (HEIGHT/8);
}

int main(int argc, char **argv)
{
	char	**maps;
	
	vars.maps = malloc(sizeof(char *) * (64 + 1));
	vars.maps[0] = strdup("11111111");
	vars.maps[1] = strdup("1000N001");
	vars.maps[2] = strdup("10000001");
	vars.maps[3] = strdup("10010001");
	vars.maps[4] = strdup("10000001");
	vars.maps[5] = strdup("10001001");
	vars.maps[6] = strdup("10000001");
	vars.maps[7] = strdup("11111111");
	vars.maps[8] = NULL;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Cub3D");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(buttons);
	glutMainLoop();
	return (0);
}
