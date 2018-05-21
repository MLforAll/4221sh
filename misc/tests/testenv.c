#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_setenv(char *name, char *value)
{
	extern char	**environ;
	char		**tmp;
	static int	first = YES;

	tmp = environ;
	environ = ft_tabdup((const char**)environ);
	if (first)
		first = NO;
	else
		ft_tabfree(&tmp);
	for (unsigned i = 0; environ[i]; i++)
	{
		if (!ft_strstart(environ[i], name))
			continue ;
		free(environ[i]);
		environ[i] = ft_strnew(ft_strlen(name) + 1 + ft_strlen(value));
		ft_strcpy(environ[i], name);
		ft_strcat(environ[i], "=");
		ft_strcat(environ[i], value);
	}
}

int		main(int ac, char **av)
{
	if (ac < 2)
		return (ft_returnmsg("Err: too few args!", 2, 1));
	ft_setenv(av[1], "yolo");
	ft_putendl(getenv(av[1]));
	return 0;
}
