#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(char **line)
{
	int		i;
	int		rdd_bts;
	char	c;
	char	*buf;

	i = 0;
	if (!(buf = malloc(100000 + 1)))
		return (-1);
	while ((rdd_bts = read(0, &c, 1) > 0) && c != '\n' && c != '\0')
		buf[i++] = c;
	buf[i] = '\0';
	*line = buf;
	return (rdd_bts);
}

int	main()
{
	char	*line = NULL;

	while ((get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s\n", line);
	free(line);
	line = NULL;
}