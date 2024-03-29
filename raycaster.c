#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.141592653589793238
#define WIDTH 1712
#define HEIGHT 960
#define RATIO_Y 107
#define RATIO_X 0 
#define BLOCK_SIZE 8
# define CONST 180

typedef struct	s_rays
{
	double	x;
	double	y;
	double	ang;
	double	dist;
	double	height;
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
	int		y_trig;
	int		x_trig;
	t_rays	rays[849];
}				t_player;
typedef struct s_vars
{
	t_player	p;
	char		**maps;
}				t_vars;

t_vars	vars;

void	Draw_line_float(double x_start, double y_start,
	double x_end, double y_end)
{
	/*glBegin(GL_LINES);
	glVertex2f(x_start, y_start);
	glVertex2f(x_end, y_end);
	glEnd();*/
}

double	sq(double x)
{
	return (x * x);
}

double	get_dist(double x1, double x2, double y1, double y2)
{
	double	hyp;
	double	adj;
	static int	count;
	
	hyp = sqrt(sq(x2 - x1) + sq(y2 - y1));
	adj = cos(vars.p.rays[count].ang - vars.p.ang) * hyp;
	if (count == 849)
		count = 0;
	count++;
	return (adj);
}

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
			xo = j * ((WIDTH / 2) / 8);
			yo = i * (HEIGHT / 8);
			if (vars.maps[i][j] == '1')
				glColor3f(1, 0, 0);
			else
				glColor3f(0, 0, 0);
			glBegin(GL_QUADS);
			glVertex2i(xo + 2, yo + 2);
			glVertex2i(xo + 2, yo + (HEIGHT / 8) - 2);
			glVertex2i((xo + ((WIDTH / 2) / 8)) - 2, (yo + (HEIGHT / 8)) - 2);
			glVertex2i(xo + ((WIDTH / 2) / 8) - 2, yo + 2);
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
	glVertex2i(vars.p.x * 107, vars.p.y * 120);
	glEnd();
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(vars.p.x * 107, vars.p.y * 120);
	glVertex2i((vars.p.x * 107) + (vars.p.dx * 5), (vars.p.y * 120) + (vars.p.dy * 5));
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
	
	
	angle = vars.p.ang - (30 * (PI / 180));
	if (angle < 0)
		angle += 2 * PI;
	x = 0;
	row = 0;
	col = 0;
	y = 0;
	glColor3f(1, 0, 1);
	glPointSize(2);
	vars.p.stop_frwrd = 0;
	while (count > 0)
	{
		x = vars.p.x + (cos(angle) * 0.125);
		y = vars.p.y + (sin(angle) * 0.125);
		row = (int)x;
		col = (int)y;
		if (vars.maps[col][row] == '1')
			vars.p.stop_frwrd = 1;
		glBegin(GL_POINTS);
		glVertex2f(x * 107, y * 120);
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
	while (count > 0)
	{
		x = vars.p.x + (cos(angle) * 0.125);
		y = vars.p.y + (sin(angle) * 0.125);
		row = (int)x;
		col = (int)y;
		if (vars.maps[col][row] == '1')
			vars.p.stop_bckwrd = 1;
		glBegin(GL_POINTS);
		glVertex2f(x * 107, y * 120);
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
	while (count > 0)
	{
		x = vars.p.x + (cos(angle) * 0.125);
		y = vars.p.y + (sin(angle) * 0.125);
		row = (int)x;
		col = (int)y;
		if (vars.maps[col][row] == '1')
			vars.p.stop_left = 1;
		glBegin(GL_POINTS);
		glVertex2f(x * 107, y * 120);
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
	angle += (PI / 2);
	if (angle > 2 * PI)
		angle -= 2 * PI;
	x = 0;
	row = 0;
	col = 0;
	y = 0;
	glColor3f(1, 0, 1);
	glPointSize(2);
	vars.p.stop_right = 0;
	while (count > 0)
	{
		x = vars.p.x + (cos(angle) * 0.125);
		y = vars.p.y + (sin(angle) * 0.125);
		row = (int)x;
		col = (int)y;
		if (vars.maps[col][row] == '1')
			vars.p.stop_right = 1;
		glBegin(GL_POINTS);
		glVertex2f(x * 107, y * 120);
		glEnd();
		angle += (10 * PI / 180);
		if (angle > 2 * PI)
			angle -= 2 * PI;
		count--;
	}
}

double	abs_max(double dx, double dy)
{
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	return (dx > dy ? dx : dy);
}

int	changed_grid(double x, double y, double com_x, double com_y)
{
	if ((int)com_x != (int)x && (int)com_y != (int)y)
		return (2);
	else if ((int)com_x != (int)x || (int)com_y != (int)y)
	{
		if ((int)com_x != (int)x)
			return ('x');
		else if ((int)com_y != (int)y)
			return ('y');
	}
	else
		return (0);
}

double	dda_x(double new_x, double old_x, double old_y)
{
	double	y;
	double	diff;
	double	tan_value;

	diff = new_x - old_x;
	tan_value = tan(vars.p.ang);
	//printf("X2: %f, X1: %f, Y: %f, tan value: %f, diff: %f, ang: %f\n", new_x, old_x, old_y, tan(vars.p.ang), diff, vars.p.ang * 180 / PI);
	y = ((new_x - old_x) * tan(vars.p.ang)) + old_y;
	return (y);
}

double	dda_y(double new_y, double old_y, double old_x)
{
	double	x;
	//static int	iter;
	
	/*if (!iter)
		printf("X: %f, Y: %f, tan value: %f\n", old_y, new_y, ((new_y - old_y) / tan(vars.p.ang)));
	iter++;*/
	x = ((new_y - old_y) / tan(vars.p.ang)) + old_x;
	return (x);
}

/**
** side, which side of the wall hit, if x hit then side = 0, else side = 1
**
**/
static void check_grid(double angle)
{
	double	cx;
	double	cy;
	double	dx;
	double	dy;
	int		m_x;
	int		m_y;
	double	x_step;
	double	y_step;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	perp_wall_dist;
	double	x;
	double	y;
	int		wall;
	static int iter;
	int		check;
	
	dx = cos(vars.p.ang) * 0.001;
	dy = sin(vars.p.ang) * 0.001;
	x = vars.p.x;
	y = vars.p.y;
	wall = 0;
	while ((int)x == (int)vars.p.x && (int)y == (int)vars.p.y)
	{
		x += dx;
		y += dy;
	}
	if (vars.maps[(int)y][(int)x] == '1')
		wall = 1;
	if (wall == 1)
	{
		glColor3f(0, 0, 1);
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f(x * 107, y * 120);
		glEnd();
		return ;
	}
	check = 0;
	if (!iter)
		printf("X: %f, Y: %f\n", x, y);
	glColor3f(0, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(x * 107, y * 120);
	glEnd();
	cx = cos(vars.p.ang);
	cy = sin(vars.p.ang);
	dx = sqrt(1 + (sq(cy) / sq(cx)));
	dy = sqrt(1 + (sq(cx) / sq(cy)));
	m_x = (int)vars.p.x;
	m_y = (int)vars.p.y;
	if (cos(vars.p.ang) < 0)
	{
		x_step = -1;
		side_dist_x = (vars.p.x - (int)vars.p.x) * dx;
	}
	else
	{
		x_step = 1;
		side_dist_x = ((int)vars.p.x + 1.0 - vars.p.x) * dx;
	}
	if (sin(vars.p.ang) < 0)
	{
		y_step = -1;
		side_dist_y = (vars.p.y - (int)vars.p.y) * dy;
	}
	else
	{
		y_step = 1;
		side_dist_y = ((int)vars.p.y + 1.0 - vars.p.y) * dy;
	}
	while (!wall)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += dx;
			m_x += x_step;
			side = 0;
		}
		else
		{
			side_dist_y += dy;
			m_y += y_step;
			side = 1;
		}
		if (vars.maps[m_y][m_x] == '1')
			wall = 1;
	}
	glColor3f(0, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(x * 107, y * 120);
	glEnd();
	if (side == 0)
	{
		if (cos(vars.p.ang) < 0)
		{
			x = m_x + 1;
			y = dda_x(x, vars.p.x, vars.p.y);
		}
		else
		{
			x = m_x;
			y = dda_x(x, vars.p.x, vars.p.y);
		}
	}
	else
	{
		if (!iter)
			printf("Sin value: %f\n", sin(vars.p.ang));
		if (sin(vars.p.ang) < 0)
		{
			y = m_y + 1;
			if (!iter)
				printf("Y: %f\n", y);
			x = dda_y(y, vars.p.y, vars.p.x);
		}
		else
		{
			y = m_y;
			x = dda_y(y, vars.p.y, vars.p.x);
		}
	}
	if (!iter)
		printf("X: %f, Y: %f\n", x, y);
	glColor3f(0, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(x * 107, y * 120);
	glEnd();
	glColor3f(0, 1, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(m_x * 107, m_y * 120);
	glEnd();
	if (!iter)
		printf("MX: %d, MY: %d\nSide_distX: %f, Side_distY: %f\n\n", (int)m_x, (int)m_y, side_dist_x, side_dist_y);
	iter++;
	if (iter == 849)
		iter = 0;
}

void	drawRays()
{
	int	count = 849;
	double	ang;
	double	x;
	double	y;
	int		wall = 0;
	
	ang = vars.p.ang - (30 * (PI / 180));
	count = 849;
	while (count > 0)
	{
		wall = 0;
		x = vars.p.x;
		y = vars.p.y;
		check_grid(ang);
		while (!wall)
		{
			x += cos(ang) * 0.012;
			y += sin(ang) * 0.012;
			if (vars.maps[(int)y][(int)x] == '1')
				wall = 1;
		}
		glColor3f(1, 1, 0);
		Draw_line_float(vars.p.x * 107, vars.p.y * 120, x * 107, y * 120);
		vars.p.rays[849 - count].x = x;
		vars.p.rays[849 - count].y = y;
		vars.p.rays[849 - count].ang = ang;
		count--;
		ang += 0.0012334482346249678988860005431;
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
		vars.p.dx = cos(vars.p.ang) * 0.0525;
		vars.p.dy = sin(vars.p.ang) * 0.0525;
		if ((vars.p.x + vars.p.dx > 0) && (vars.p.x + vars.p.dx < WIDTH)
		&& (vars.p.y + vars.p.dy > 0) && (vars.p.y + vars.p.dy < HEIGHT))
		{
			row = (int)(vars.p.x + vars.p.dx);
			col = (int)(vars.p.y + vars.p.dy);
			if (vars.maps[col][row] == '1' || vars.p.stop_frwrd)
				return ;
			vars.p.x += vars.p.dx;
			vars.p.y += vars.p.dy;
			vars.maps[col][row] = '0';
		}
	}
	else if (key == 's')
	{
		vars.p.dx = cos(vars.p.ang) * 0.0525;
		vars.p.dy = sin(vars.p.ang) * 0.0525;
		if ((vars.p.x - vars.p.dx > 0) && (vars.p.x - vars.p.dx < WIDTH)
		&& (vars.p.y - vars.p.dy > 0) && (vars.p.y - vars.p.dy < HEIGHT))
		{
			row = (int)((vars.p.x - vars.p.dx));
			col = (int)(vars.p.y - vars.p.dy);
			if (vars.maps[col][row] == '1' || vars.p.stop_bckwrd)
				return ;
			vars.p.x -= vars.p.dx;
			vars.p.y -= vars.p.dy;
			vars.maps[col][row] = '0';
		}
	}
	else if (key == 'd')
	{
		vars.p.dx = cos((PI / 2) + (vars.p.ang)) * 0.0525;
		vars.p.dy = sin((PI / 2) + (vars.p.ang)) * 0.0525;
		if ((vars.p.x + vars.p.dx > 0) && (vars.p.x + vars.p.dx < WIDTH)
		&& (vars.p.y + vars.p.dy > 0) && (vars.p.y + vars.p.dy < HEIGHT))
		{
			row = (int)(vars.p.x + vars.p.dx);
			col = (int)(vars.p.y + vars.p.dy);
			if (vars.maps[col][row] == '1' || vars.p.stop_right)
				return ;
			vars.p.x += vars.p.dx;
			vars.p.y += vars.p.dy;
			vars.maps[col][row] = '0';
		}
	}
	else if (key == 'a')
	{
		vars.p.dx = cos((PI / 2) + (vars.p.ang)) * 0.0525;
		vars.p.dy = sin((PI / 2) + (vars.p.ang)) * 0.0525;
		if ((vars.p.x - vars.p.dx > 0) && (vars.p.x - vars.p.dx < WIDTH)
		&& (vars.p.y - vars.p.dy > 0) && (vars.p.y - vars.p.dy < HEIGHT))
		{
			row = (int)(vars.p.x - vars.p.dx);
			col = (int)(vars.p.y - vars.p.dy);
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

double	get_height(int index)
{
	double	height;
	
	height = (BLOCK_SIZE * CONST) / vars.p.rays[index].dist;
	if (height < 0)
		height  = 0;
	else if (height > HEIGHT)
		height = HEIGHT;
	return (height);
}

void	draw3DMap(void)
{
	int	count;
	int	x;
	int	y;
	
	count = 0;
	while (count < 849)
	{
		vars.p.rays[count].dist = get_dist(vars.p.x, vars.p.rays[count].x, vars.p.y, vars.p.rays[count].y);
		vars.p.rays[count].height = get_height(count);
		count++;
	}
	x = 0;
	while(x < 849)
	{
		glBegin(GL_LINES);
		glVertex2i(863 + x, ((HEIGHT / 2) - (vars.p.rays[x].height / 2)));
		glVertex2i(863 + x, ((HEIGHT / 2) + (vars.p.rays[x].height / 2)));
		glEnd();
		x++;
	}
}

void	display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawRays();
	drawPlayer();
	draw3DMap();
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
	vars.p.ang = PI;
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
	vars.p.x = j + 0.5 ;
	vars.p.y = i + 0.5;
}

int main(int argc, char **argv)
{
	char	**maps;
	
	vars.maps = malloc(sizeof(char *) * (64 + 1));
	vars.maps[0] = strdup("11111111");
	vars.maps[1] = strdup("10N00101");
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
