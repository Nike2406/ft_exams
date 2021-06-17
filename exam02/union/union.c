#include <unistd.h>

/*
	Используется метод приравнивания к таблице ascii
*/
void	ft_union(char *argv, char *arr)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != arr[(int)argv[i]])
		{
			write(1, &argv[i], 1);
			arr[(int)argv[i]] = argv[i];
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	arr[255];

	if (argc == 3)
	{
		ft_union(argv[1], arr);
		ft_union(argv[2], arr);
	}
	write(1, "\n", 1);
	return (0);
}