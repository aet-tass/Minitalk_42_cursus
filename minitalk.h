/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 04:47:41 by aet-tass          #+#    #+#             */
/*   Updated: 2023/04/23 21:18:45 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "utils/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

void	send_message(int pid, char *message);
char	conv_to_char(int *bits, int size);
void	update_buffer(int signal, int *bit_buffer, int *buffer_index);
void	handle_signal(int signal, siginfo_t *info, void *context);
int		ft_atoi(const char *str);

#endif
