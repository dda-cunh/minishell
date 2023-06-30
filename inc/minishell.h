/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:51:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/06/30 20:52:12 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
	includes go here
*/

typedef struct s_data
{
	char			**env;
	struct s_cmd	*cmd;
	int				infile;
	int				outfile;
}				t_data;

typedef struct s_cmd
{
	/*
		tokens, etc
	*/
	struct s_cmd	*next;
}				t_cmd;

#endif
