/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:50:19 by hmellahi          #+#    #+#             */
/*   Updated: 2021/09/25 19:23:23 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell_ref(t_shell *shell)
{
	static t_shell	*ref;

	if (shell)
		ref = shell;
	return (ref);
}

int	main(int ac, char **argv, char **env_vars)
{
	t_shell	shell;

	(void)ac;
	shell.n_flag = 0;
	shell_ref(&shell);
	if (str_cmp(argv[1], "-c") == TRUE)
	{
		shell.n_flag = 1;
		shell.cmd = argv[2];
	}
	init_shell(&shell, env_vars);
	shell_loop(&shell);
	if (!shell.is_exit_printed)
		put_str("exit");
	// sf_malloc(0, FREE);
	// system("leaks minishell");
	return (shell.exit_code);
}

// int	main(int ac, char **argv, char **env_vars)
// {
// 	t_shell	shell;
// 	shell_ref(&shell);
// 	init_shell(&shell, env_vars);
// 	char			*mystr;
// 	t_split_pipe	pipe_split;
// 	t_cmd			*final_str;

// 	// mystr = " 'echo'ali    >       'bro'         a hey | $HOME<<'dude' | 'l''s' | cat<  1";
// 	// mystr = " 'echo'ali    >       bro         a hey ";
// 	// mystr = "echo \"|\" |" ; // we should take it as syntax error
// 	// mystr = "|" ; // syntax error
// 	// mystr = "\"l\"\"s\"                 >>           'med ali'" ; // syntax error
// 	// mystr = "echo \"$HOME\"" ; // todo not working
// 	// mystr = "echo << a";
// 	// mystr = "echo \"$s\"Make\'$s\'";
// 	// mystr = "unset \"'\" test";
// 	// mystr = " ls >";
// 	// mystr = " 'echo' ali >> \"name name name\"okay ca marche";
// 	// mystr = " 'echo'ali >> 'name name name'\"$HOME\"";
// 	// mystr = "echo \"$TEST='$TEST'\"";
// 	mystr = "export a='
ls -la'";
// 	mystr = "echo \"''\"";
// 	// mystr = "echo '\"\"'";
// 	// mystr = "echo '""""""""""""""""""'";

// 	//| \'$ça\' << '\"name' | 'ali is the best' | cat <\"1\" >'1'"; //fix this bro
// 	if(!open_quotes(mystr))
// 	{
// 		write(2, "syntax error\n", 14);
// 		return (0);
// 	}
// 	pipe_split.pipe_str = split_delimiter_func(mystr,
// 							'|', pipe_split.pipe_str, &pipe_split.num_tab);
// 	final_str = space_delimiter_func(pipe_split.pipe_str, " <>", pipe_split.num_tab);
// 	//final_str = space_delimiter_func(pipe_split.pipe_str, "<>", pipe_split.num_tab);
// 	for(int i = 0; i < pipe_split.num_tab; i++)
// 	{
// 		if(!multiple_red(pipe_split.pipe_str[i]))
// 		{
// 			write(2, "syntax error\n", 14);
// 			return (0);
// 		}
// 	}
// 		printf("%d\n", pipe_split.num_tab);
// 	puts("--------");
// 	for(int i = 0; i < pipe_split.num_tab; i++)
// 	{	
// 		printf("n : %d\n", final_str[i].n);
// 		for (int j = 0; j < final_str[i].n; j++)
// 		{
// 			printf("|%s|\n", final_str[i].args[j]);
// 		}
// 		for (int k =0; k < final_str[i].files_count;k++)
// 			printf("the name : %s, type : %d, q : %d\n", final_str[i].files[k].name, final_str[i].files[k].type, final_str[i].files[k].is_quoted);
// 		puts("-------");
// 	}
// }