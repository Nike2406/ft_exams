#include <unistd.h>

/*
	Используется метод приравнивания к таблице ascii
*/

void	ft_inter(char *argv1, char *argv2)
{
	char	arr[255];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (argv1[i])
	{
		j = 0;
		while(argv2[j])
		{
			if (argv1[i] == argv2[j] && argv1[i] != arr[(int)argv1[i]])
			{
				write(1, &argv1[i], 1);
				arr[(int)argv1[i]] = argv1[i];
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}