/*static int	create_dash_tok(void *data)
{
	t_lexdat	*cdat;
	char		tokc[2];
	t_str		vdumb;

	if (!data)
		return ((int)kLexStateUndefined);
	cdat = (t_lexdat*)data;
	tokc[0] = **cdat->linep;
	tokc[1] = '\0';
	vdumb.s = tokc;
	if (!add_token(cdat->ret, &vdumb, DASH, 0))
		return ((int)kLexStateUndefined);
	return ((int)kLexStateGeneral);
}*/
