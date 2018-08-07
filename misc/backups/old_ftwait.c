/*int				ft_wait(t_list **jobnode)
{
	t_jobctrl	*jdat;
	t_uint8		ret;

	if (!jobnode)
		return (-1);
	while (*jobnode)
	{
		jdat = (t_jobctrl*)(*jobnode)->content;
		if (jdat->j_state != kJobStateRunning)
			break ;
	}
	if (!*jobnode)
		return (-1);
	ret = jdat->j_exval;
	if (jdat->j_state == kJobStateExited)
	{
		sh_jobop_lock();
		ft_lstdelone(jobnode, &ft_joblstdel);
		sh_jobop_unlock();
	return ((int)ret);
}*/
