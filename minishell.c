/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:26:37 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/18 20:56:11 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **av, char  **envp)
{
    t_minishell *new_env;
    void(av);
    
    if (argc != 1)
    {
        perror("INVALID NUMBER ARGUMENT :--");
        exit(1);
    }
}