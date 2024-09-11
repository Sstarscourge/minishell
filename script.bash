
#!/bin/bash
# Simple script to greet the user
42 -c

42 -brew

42 -c

brew install readline


brew link readline --force

brew --prefix readline


export LDFLAGS="~/goinfre/homebrew/opt/readline/lib"
export CPPFLAGS="~/goinfre/homebrew/opt/readline/include"



source ~/.zshrc

#gcc -Wall -Wextra -Werror minishell.c -lreadline -L~/goinfre/homebrew/opt/readline/lib -I~/goinfre/homebrew/opt/readline/include