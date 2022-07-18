#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.141592653589793238
#define WIDTH 800
#define HEIGHT 800

typedef struct	s_rays
{
	float	x;
	float	y;
}				t_rays;

typedef struct s_player
{
	float	x;
	float	y;
	float	ang;
	float	dx;
	float	dy;
	t_rays	r;
	int		stop_frwrd;
	int		stop_bckwrd;
	int		stop_right;
	int		stop_left;
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
	glColor3f(1, 1, 0);
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

float	max(float a, float b)
{
	return (a > b ? a : b);
}

float	min(float a, float b)
{
	return (a < b ? a : b);
}

void Wall_C_forwrd(void)
{
	float	angle;
	float	x;
	float	y;
	int		count = 7;
	int		row;
	int		col;
	
	
	angle = vars.p.ang - (30 * PI / 180);
	if (angle < 0)
		angle += 2 * PI;
	x = 0;
	row = 0;
	col = 0;
	y = 0;
	glColor3f(1, 0, 1);
	glPointSize(2);
	vars.p.stop_frwrd = 0;
	printf("Angle: %f\n", angle * 180 / PI);
	while (count > 0)
	{
		printf("Angle: %f\n", angle * 180 / PI);
		x = vars.p.x + (cos(angle) * 12);
		y = vars.p.y + (sin(angle) * 12);
		row = (int)(x * 8 / WIDTH);
		col = (int)(y * 8 / HEIGHT);
		if (vars.maps[col][row] == '1')
			vars.p.stop_frwrd = 1;
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		angle += (10 * PI / 180);
		if (angle > 2 * PI)
			angle -= 2 * PI;
		count--;
	}
}

void Wall_C_bckwrd(void)
{
	float	angle;
	float	x;
	float	y;
	int		count = 7;
	int		row;
	int		col;
	
	
	angle = vars.p.ang - (30 * PI / 180) - PI;
	if (angle < 0)
		angle += 2 * PI;
	x = 0;
	row = 0;
	col = 0;
	y = 0;
	glColor3f(1, 0, 1);
	glPointSize(2);
	vars.p.stop_bckwrd = 0;
	printf("Angle: %f\n", angle * 180 / PI);
	while (count > 0)
	{
		printf("Angle: %f\n", angle * 180 / PI);
		x = vars.p.x + (cos(angle) * 12);
		y = vars.p.y + (sin(angle) * 12);
		row = (int)(x * 8 / WIDTH);
		col = (int)(y * 8 / HEIGHT);
		if (vars.maps[col][row] == '1')
			vars.p.stop_bckwrd = 1;
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		angle += (10 * PI / 180);
		if (angle > 2 * PI)
			angle -= 2 * PI;
		count--;
	}
}

void Wall_C_left(void)
{
	float	angle;
	float	x;
	float	y;
	int		count = 7;
	int		row;
	int		col;
	
	
	angle = vars.p.ang - (30 * PI / 180);
	if (angle < 0)
		angle += 2 * PI;
	angle += (3 * PI / 2);
	if (angle > 2 * PI)
		angle -= 2 * PI;
	x = 0;
	row = 0;
	col = 0;
	y = 0;
	glColor3f(1, 0, 1);
	glPointSize(2);
	vars.p.stop_left = 0;
	printf("Angle: %f\n", angle * 180 / PI);
	while (count > 0)
	{
		printf("Angle: %f\n", angle * 180 / PI);
		x = vars.p.x + (cos(angle) * 12);
		y = vars.p.y + (sin(angle) * 12);
		row = (int)(x * 8 / WIDTH);
		col = (int)(y * 8 / HEIGHT);
		if (vars.maps[col][row] == '1')
			vars.p.stop_left = 1;
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		angle += (10 * PI / 180);
		if (angle > 2 * PI)
			angle -= 2 * PI;
		count--;
	}
}

void Wall_C_right(void)
{
	float	angle;
	float	x;
	float	y;
	int		count = 7;
	int		row;
	int		col;
	
	
	angle = vars.p.ang - (30 * PI / 180);
	if (angle < 0)
		angle += 2 * PI;
	angle += (1 * PI / 2);
	if (angle > 2 * PI)
		angle -= 2 * PI;
	x = 0;
	row = 0;
	col = 0;
	y = 0;
	glColor3f(1, 0, 1);
	glPointSize(2);
	vars.p.stop_right = 0;
	printf("Angle: %f\n", angle * 180 / PI);
	while (count > 0)
	{
		printf("Angle: %f\n", angle * 180 / PI);
		x = vars.p.x + (cos(angle) * 12);
		y = vars.p.y + (sin(angle) * 12);
		row = (int)(x * 8 / WIDTH);
		col = (int)(y * 8 / HEIGHT);
		if (vars.maps[col][row] == '1')
			vars.p.stop_right = 1;
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		angle += (10 * PI / 180);
		if (angle > 2 * PI)
			angle -= 2 * PI;
		count--;
	}
}

void	drawRays()
{
	float	angle;
	int		walls;
	int		rows;
	int		cols;
	int		dof;
	
	angle = vars.p.ang;
	walls = 0;
	rows = 0;
	cols = 0;
	dof = 0;
	glColor3f(0, 1, 0);
	glLineWidth(1);
	while (dof < 3)
	{
		angle -= (10 * PI / 180);
		if (angle < 2 * PI)
			angle += 2 * PI;
		vars.p.dx = cos(angle) * 5;
		vars.p.dy = sin(angle) * 5;
		vars.p.r.x = vars.p.x + vars.p.dx;
		vars.p.r.y = vars.p.y + vars.p.dy;
		walls = 0;
		while (!walls)
		{
			rows = (int)(vars.p.r.x * 8 / WIDTH);
			cols = (int)(vars.p.r.y * 8 / HEIGHT);
			if (vars.maps[cols][rows] == '1')
				walls = 1;
			vars.p.r.x += vars.p.dx;
			vars.p.r.y += vars.p.dy;
		}
		glBegin(GL_LINES);
		glVertex2i(vars.p.x, vars.p.y);
		glVertex2i(vars.p.r.x, vars.p.r.y);
		glEnd();
		dof++;
	}
	angle = vars.p.ang;
	vars.p.dx = cos(angle) * 5;
	vars.p.dy = sin(angle) * 5;
	vars.p.r.x = vars.p.x + vars.p.dx;
	vars.p.r.y = vars.p.y + vars.p.dy;
	walls = 0;
	while (!walls)
	{
		rows = (int)(vars.p.r.x * 8 / WIDTH);
		cols = (int)(vars.p.r.y * 8 / HEIGHT);
		if (vars.maps[cols][rows] == '1')
			walls = 1;
		vars.p.r.x += vars.p.dx;
		vars.p.r.y += vars.p.dy;
	}
	glBegin(GL_LINES);
	glVertex2i(vars.p.x, vars.p.y);
	glVertex2i(vars.p.r.x, vars.p.r.y);
	glEnd();
	while (dof < 6)
	{
		angle += (10 * PI / 180);
		if (angle < 2 * PI)
			angle += 2 * PI;
		vars.p.dx = cos(angle) * 5;
		vars.p.dy = sin(angle) * 5;
		vars.p.r.x = vars.p.x + vars.p.dx;
		vars.p.r.y = vars.p.y + vars.p.dy;
		walls = 0;
		while (!walls)
		{
			rows = (int)(vars.p.r.x * 8 / WIDTH);
			cols = (int)(vars.p.r.y * 8 / HEIGHT);
			if (vars.maps[cols][rows] == '1')
				walls = 1;
			vars.p.r.x += vars.p.dx;
			vars.p.r.y += vars.p.dy;
		}
		glBegin(GL_LINES);
		glVertex2i(vars.p.x, vars.p.y);
		glVertex2i(vars.p.r.x, vars.p.r.y);
		glEnd();
		dof++;
	}
	Wall_C_forwrd();
	Wall_C_bckwrd();
	Wall_C_left();
	Wall_C_right();
}

void	buttons(unsigned char key, int x, int y)
{
	int	row;
	int	col;
	if (key == 'w')
	{
		vars.p.dx = cos(vars.p.ang) * 5;
		vars.p.dy = sin(vars.p.ang) * 5;
		if ((vars.p.x + vars.p.dx > 0) && (vars.p.x + vars.p.dx < WIDTH)
		&& (vars.p.y + vars.p.dy > 0) && (vars.p.y + vars.p.dy < HEIGHT))
		{
			row = (int)((vars.p.x + vars.p.dx) * 8 / WIDTH);
			col = (int)((vars.p.y + vars.p.dy) * 8 / HEIGHT);
			if (vars.maps[col][row] == '1' || vars.p.stop_frwrd)
				return ;
			vars.p.x += vars.p.dx;
			vars.p.y += vars.p.dy;
			vars.maps[col][row] = '0';
		}
	}
	else if (key == 's')
	{
		vars.p.dx = cos(vars.p.ang) * 5;
		vars.p.dy = sin(vars.p.ang) * 5;
		if ((vars.p.x + vars.p.dx > 0) && (vars.p.x + vars.p.dx < WIDTH)
		&& (vars.p.y + vars.p.dy > 0) && (vars.p.y + vars.p.dy < HEIGHT))
		{
			row = (int)((vars.p.x - vars.p.dx) * 8 / WIDTH);
			col = (int)((vars.p.y - vars.p.dy) * 8 / HEIGHT);
			if (vars.maps[col][row] == '1' || vars.p.stop_bckwrd)
				return ;
			vars.p.x -= vars.p.dx;
			vars.p.y -= vars.p.dy;
			vars.maps[col][row] = '0';
		}
	}
	else if (key == 'd')
	{
		vars.p.dx = cos((PI / 2) + (vars.p.ang)) * 5;
		vars.p.dy = sin((PI / 2) + (vars.p.ang)) * 5;
		if ((vars.p.x + vars.p.dx > 0) && (vars.p.x + vars.p.dx < WIDTH)
		&& (vars.p.y + vars.p.dy > 0) && (vars.p.y + vars.p.dy < HEIGHT))
		{
			row = (int)((vars.p.x + vars.p.dx) * 8 / WIDTH);
			col = (int)((vars.p.y + vars.p.dy) * 8 / HEIGHT);
			if (vars.maps[col][row] == '1' || vars.p.stop_right)
				return ;
			vars.p.x += vars.p.dx;
			vars.p.y += vars.p.dy;
			vars.maps[col][row] = '0';
		}
	}
	else if (key == 'a')
	{
		vars.p.dx = cos((PI / 2) + (vars.p.ang)) * 5;
		vars.p.dy = sin((PI / 2) + (vars.p.ang)) * 5;
		if ((vars.p.x - vars.p.dx > 0) && (vars.p.x - vars.p.dx < WIDTH)
		&& (vars.p.y - vars.p.dy > 0) && (vars.p.y - vars.p.dy < HEIGHT))
		{
			row = (int)((vars.p.x - vars.p.dx) * 8 / WIDTH);
			col = (int)((vars.p.y - vars.p.dy) * 8 / HEIGHT);
			if (vars.maps[col][row] == '1' || vars.p.stop_left)
				return ;
			vars.p.x -= vars.p.dx;
			vars.p.y -= vars.p.dy;
			vars.maps[col][row] = '0';
		}
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
	drawRays();
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
	vars.p.x = j * (WIDTH/8) + (WIDTH / 16);
	vars.p.y = i * (HEIGHT/8) + (HEIGHT / 16);
}

int main(int argc, char **argv)
{
	char	**maps;
	
	vars.maps = malloc(sizeof(char *) * (64 + 1));
	vars.maps[0] = strdup("11111111");
	vars.maps[1] = strdup("1000N101");
	vars.maps[2] = strdup("10001001");
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
