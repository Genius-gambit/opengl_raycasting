#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double	max(double dx, double dy)
{
	return (abs(dx) > abs(dy) ? dx : dy);
}

int main(void)
{
	double	dx;
	double	dy;
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	step;
	double	x_inct;
	double	y_inct;
	double	x;
	double	y;

	dx = cos(M_PI / 3);
	dy = sin(M_PI / 3); 
	x1 = 1;
	y1 = 1;
	x2 = x1 + dx;
	y2 = y1 + dy;
	step = max(dx, dy);
	printf("x1: %f, y1: %f, x2: %f, y2: %f, step: %f\n", x1, y1, x2, y2, step);
	x_inct = dx / step;
	y_inct = dy / step;
	x = x1 + x_inct;
	y = y1 + y_inct;
	return (0);
}