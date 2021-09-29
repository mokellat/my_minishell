#ifndef SIGNALS_H
# define SIGNALS_H
# define CTRL_C SIGINT
# define CTRL_D 1
# define CTRL_S SIGQUIT

void	init_signals(void);
void	handle_signal(int event_code);
#endif