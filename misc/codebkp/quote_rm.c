/*
**inline static void	quote_removal(char *s, t_tab *qidx)
**{
**	char			*tmp;
**	unsigned long	idx;
**
**	idx = qidx->count;
**	while (TRUE)
**	{
**		if (*(tmp = s + ((int*)(qidx->data))[--idx]))
**			(void)ft_strcpy(tmp, tmp + 1);
**		if (idx == 0)
**			break ;
**	}
**}
*/
