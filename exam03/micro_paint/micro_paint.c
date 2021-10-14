#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_drawing
{
	char *m;
	int w;
	int h;
	char c;
} drawing;

typedef struct s_rectangle {
	char type;
	float x;
	float y;
	float w;
	float h;
	char c;
} rectangle;

FILE *f;
drawing d;
rectangle r;

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

int in_rectangle(float x, float y)
{
	if (x < r.x || r.x + r.w < x || y < r.y || r.y + r.h < y)
		return (0);
	if (x - r.x < 1. || (r.x + r.w) - x < 1. || y - r.y < 1. || (r.y + r.h) - y < 1.)
		return (2);
	return (1);
}

int apply(void)
{
	int x;
	int y;
	int is;

	if ((r.w <= 0. || r.h <= 0.) || (r.type != 'R' && r.type != 'r'))
		return (0);
	x = -1;
	while (++x < d.w && (y = -1))
		while (++y < d.h)
			if ((is = in_rectangle(x, y)) == 2 || (is == 1 && r.type == 'R'))
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
	while ((scan = fscanf(f, "%c %f %f %f %f %c\n", &r.type, &r.x, &r.y, &r.w, &r.h, &r.c)) == 6)
		if (!apply())
			return (0);
	if (scan != -1)
		return (0);
	while (++x < d.h)
		write(1, d.m + (x * d.w), d.w) && write(1, "\n", 1);
	return (1);
}

int main (int argc, char **argv)
{
	if (argc == 2)
	{
		f = fopen(argv[1], "r");
		if (f && execute())
			return (0);
		write (1, "Error: Operation file corrupted\n", 32);
	}
	else
		write(1, "Error: argument\n", 16);
	return (1);
}