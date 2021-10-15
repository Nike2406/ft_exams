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
	char sym_backgound;
} drawing;

typedef struct s_rectangle {
	char type;
	float x;
	float y;
	float w;
	float h;
	char c;
	char sym_fig;
} rectangle;

FILE *f;
drawing d;
rectangle r;

int get_info(void)
{
	if (fscanf(f, "%d %d %c\n",
			&d.w, &d.h, &d.c) != 3)
		return (0);
	if ((d.w < 1) || (d.w > 300) || (d.h < 1) || (d.h > 300))
		return (0);



	if (!(d.m = malloc(d.w * d.h)))
		return (0);
	memset(d.m, d.c, d.w * d.h);
	return (1);
}

int is_retcanlge(float x, float y, char type) {

	float y_bot = r.y + r.h;
	float x_bot = r.x + r.w;

	if (x < r.x || y < r.y
		|| y > y_bot || x > x_bot)
		return 0;
	if (type == 'R')
		return 1;
	if (x - r.x < 1. || y - r.y < 1.
			|| y_bot - y < 1. || x_bot - x < 1.)
		return 1;
	return 0;
}

int execute(void)
{
	int x;
	int y;
	int scan;

	if (!get_info())
		return (0);
	while ((scan = fscanf(f, "%c %f %f %f %f %c\n",
			&r.type, &r.x, &r.y, &r.w, &r.h, &r.c)) == 6)
	{
		if ((r.w <= 0. || r.h <= 0.) || (r.type != 'R' && r.type != 'r'))
			return (0);

		x = -1;
		 while (++x < d.w)
		 {
			y = -1;
			while (++y < d.h)
			{
				if (is_retcanlge(x, y , r.type ))
					d.m[x + y * d.w] = r.c;
			}
		 }
	}
	if (scan != -1)
		return (0);
	x = -1;
	while (++x < d.h)
	{
		write(1, d.m + (x * d.w), d.w);
		write(1, "\n", 1);
	}
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