/*
** to be continued and normed
**
** How to manage lexer read-again?
** 	- special type for unfinished token?
**	- lexer automatically changes last token if lst is not empty?
**
** 1. Add special type to last token if unfinished
** 2. When read again, lexer goes to last token and checks if unfinished,
**			then changes
**		- to change, rm last token from dest and add it as current token
**		- to change, when add_token, check at that time and modify latest
**			rather than add
**			- to save perf, only check once (store the result in t_lexdat)
*/
