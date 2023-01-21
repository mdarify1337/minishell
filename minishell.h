/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:27:02 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/18 21:03:32 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define INPUT_FD 0
#define OUTPUT_FD 1
#define ERROR_FD 2
#define FIRST_FILE_ARG 1
#define FULL_ACCESS 0777

typedef struct s_minishell 
{
    char    **spilt_cmd;
    char    *f_path;    
} t_minishell;

#endif