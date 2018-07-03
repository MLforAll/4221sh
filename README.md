# 21sh
42 school's 21sh project

Continuation of the previous shell project -- minishell

# Main goals:

- Proper pipeline (lexer, parser, AST)
- Rewritten ft_readline
- ft_readline as a separate lib (deps on libft)

# Features:

- Lexer, Parser, AST
- Pipes
- fd redirections and closing
- Local variables
- Set variables with text (only)
- Customisable prompt with `SH_PROMPT` variable

# Line-editing Features:

- Move your cursor arround with left and right keys
- Jump home/end of the line
- Multiline editing
- Copy/Cut/Paste
- Automatic color removal for prompt
- Dumb mode with one-line editing

# Example usages:

`$> 21sh /path/to/script` or `$> cat /path/to/script | 21sh` runs the script with 21sh. It exists after the script ran.

`$> 21sh` runs an interactive shell.

# Changelog:

_Tuesday 3rd July 2018:_
21sh is almost finished!
Features from minishell are kept.
