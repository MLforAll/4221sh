#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	tabadd(char ***ref, char *nn)
{
	char	**old;
	char	*toadd[2];

	toadd[0] = nn;
	toadd[1] = NULL;
	old = *ref;
	*ref = ft_tabjoin((const char**)*ref, (const char**)toadd);
	ft_tabfree(&old);
}

char	**get_tokens(char *s)
{
	char	**ret;

	ret = ft_tabnew();
	while (*s)
	{

		s++;
	}
	return (ret);
}

int		main(int ac, char **av)
{
	char	**tokens;

	if (ac < 2)
		return (ft_returnmsg("Need to have expr as first argument!", 2, 1));
	tokens = get_tokens(av[1]);
	ft_puttab(tokens, NULL);
	ft_tabfree(&tokens);
	return (EXIT_SUCCESS);
}
