#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct s_drawing
{
	char *m;
	int w;
	int h;
	char c;
} drawing;

typedef struct s_circle {
	char type;
	float x;
	float y;
	float r;
	char c;
} circle;

FILE *f;
drawing d;
circle r;

int get_info(void)
{
	if (fscanf(f, "%d %d %c\n", &d.w, &d.h, &d.c) != 3)
		return (0);
	if ((d.w < 1) || (d.w > 300) || (d.h < 1) || (d.h > 300))
		return (0);
	if (!(d.m = malloc(d.w * d.h)))
		return (0);
	memset(d.m, d.c, d.w * d.h);
	return (1);
}

int in_circle(float x, float y)
{
	float	distance;

	distance = sqrtf(powf(x - r.x, 2) + powf(y - r.y, 2)) - r.r;
	if (distance > 0.)
		return (0);
	if (distance <= -1.)
		return (1);
	return (2);
}

int apply(void)
{
	int x;
	int y;
	int is;

	if ((r.r <= 0.) || (r.type != 'C' && r.type != 'c'))
		return (0);
	x = -1;
	while (++x < d.w && (y = -1))
		while (++y < d.h)
			if ((is = in_circle((float)x, (float)y)) == 2 || (is == 1 && r.type == 'C'))
				d.m[x + y * d.w] = r.c;
	return (1);
}

int execute(void)
{
	int x;
	int scan; 

	x = -1;
	if (!get_info())
		return (0);
	while ((scan = fscanf(f, "%c %f %f %f %c\n", &r.type, &r.x, &r.y, &r.r, &r.c)) == 5)
		if (!apply())
			return (0);
	if (scan != -1)
		return (0);
	while (++x < d.h)
		write(1, d.m + (x * d.w), d.w) && write(1, "\n", 1);
	return (1);
}

int main (int argc, char **argv) {
	if (argc == 2) {
		f = fopen(argv[1], "r");
		if (f && execute())
			return (0);
		write (1, "Error: Operation file corrupted\n", 32);
	}
	else
		write(1, "Error: argument\n", 16);
	return (1);
}