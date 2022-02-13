#include "pip.h"

void    handler_int(int signal)
{
    (void)signal;
    
    rl_on_new_line();
    ft_putendl_fd("", STDOUT_FILENO);
    //rl_forced_update_display ();
    rl_replace_line ("", 0);
    rl_redisplay();
}

void    handler_quit(int signal)
{
    handler_int(signal);
}