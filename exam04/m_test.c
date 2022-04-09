#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_cmd {
	char	**args;
	int		type[2];
	int		pipe[2];
	int		prev_pipe;
}	t_cmd;

int	strl(char *str) {
	int	i = 0;
	while (str && str[i++]);
	return (--i);
}

void	fatal() {
	printf("fatal\n");
	exit (1);
}

void	exec_cmd(t_cmd *lst, char **env) {
	pid_t	pid;
	int		ex;

	if ((lst->type[1] == 1 || lst->type[0] == 1) && pipe(lst->pipe))
		fatal();
	if ((pid = fork()) < 0)
		fatal();
	if (!pid) {
		if (lst->type[1] == 1 && (dup2(lst->pipe[1], 1) < 0))
			fatal();
		if (lst->type[0] == 1 && (dup2(lst->prev_pipe, 0) < 0))
			fatal();
		if ((ex = execve(lst->args[0], lst->args, env)) < 0)
			printf("err");
		exit (ex);
	} else {
		waitpid(pid, 0, 0);
		if (lst->type[1] == 1 || lst->type[0] == 1) {
			close(lst->pipe[1]);
			if (lst->type[1] != 1)
				close(lst->pipe[0]);
		}
		if (lst->type[0] == 1)
			close(lst->prev_pipe);
	}
}

int	lst_len(t_cmd *lst, int start, char **argv) {
	int	end;
	int	len;

	end = start;
	while (argv[end] && strcmp(argv[end], "|") && strcmp(argv[end], "|"))
		end++;
	len = end - start;
	if (len > 0) {
		lst->args = &argv[start];
		lst->type[0] = lst->type[1];
		if (!argv[end])
			lst->type[1] = 0;
		else if (!strcmp(argv[end], "|"))
			lst->type[1] = 1;
		else
			lst->type[1] = 2;
		argv[end] = NULL;
		lst->prev_pipe = lst->pipe[0];
	}
	return (end);
}

int	main(int argc, char **argv, char **env) {
	t_cmd	lst;
	int		i;
	int		start;

	i = 0;
	while (i < argc && argv[++i]) {
		start = i;
		i = lst_len(&lst, i, argv);
		if (!strcmp(argv[start], "cd")) {
			if (i - start != 2)
				printf("err");
			if (chdir(lst.args[1]) == -1)
				printf("err");
		}
		else if (i > start)
			exec_cmd(&lst, env);
	}
	return (0);
}
