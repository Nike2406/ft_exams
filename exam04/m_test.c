#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

typedef struct s_cmd
{
	char	**args;
	int		pipe[2];
	int		prev_pipe;
	int		type[2];
}	t_cmd;


