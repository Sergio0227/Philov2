/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:44:33 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/12 16:18:19 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_intro2(void)
{
	printf("   ░░░▒▓▓█████████████▓███▓█▓▒█▓██▓▒░▒▒▓▓█▒▓▓░░░░░░░░░░ \n");
	printf("   ▒▒▒▓▓▓▓█████████████▓▒▒▒░▒▒▒░▒░▓▓▒░░▒▓██▓▒▒▒░░░░░░░░ \n");
	printf("   ▒▒▒▒▒▒▓▓███████████████▓▓▒▓█▓█▓▓▓▓▓█▒▒▒▓░▒▒░▒▒░░░░░░ \n");
	printf("   ▒▒▒▒▒▒▒▒▓▓███████████████▓▒▒░▓█████▓░▒▒▒▒░▒░░░░░░░░░ \n");
	printf("   ▒▒▒▒▒▒▒▒▒▒▒▓▓██████████████▓▓▒▒█▓▒▓▓▓▒▓▒▒▒░▒░░░░░░░░ \n");
	printf("   ▒░░░░░░░░░▒░▒▒▒▒▓█████████████▓█▓▒▒▓▓▓▒▒░▒░░▒░░░░░░░ \n");
	printf("   ▒░░░░░░░░░░░░░░░░▒▒▓██████████████▓▒░░░░░▒▒░▒░░░░░░░ \n");
	printf("   ▒░░░░░░░░░░░░░░░░░░░░░░▒▒▒▓▓▒▒░░░░░░░░░░░░▒░░▒░░░░░░ \n");
	printf(GREEN_BOLD "");
	printf(" ____  _     _ _                       _                   \n");
	printf("|  _ \\| |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ ___ \n");
	printf("| |_) | '_ \\| | |/ _ \\/ __|/ _ \\| '_ \\| '_ \\ / _ \\ '__/ __|");
	printf("\n");
	printf("|  __/| | | | | | (_) \\__ \\ (_) | |_) | | | |  __/ |  \\__ \\ ");
	printf("\n");
	printf("|_|   |_| |_|_|_|\\___/|___/\\___/| .__/|_| |_|\\___|_|  |___/ \n");
	printf("                                |_|                         ");
	printf("\n" DEF_COL);
}

void	print_intro(void)
{
	printf(LIGHT_CYAN "");
	printf("   ░░░░░░░░░░░░░░░░░▒▒▒▒░▒▒░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░░░▓▒▒▓▒░▒░▒▒░▒▓▓▒░░░░░░░░░░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░░▒▓▒▒▒▒▓░░▓█▓░▓▒▒▒░░░▒▒░▒░▒▒▒▒░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░▒▓▓▒▒▒▓▒▒▓░▒▓▓▒▓▓▓▓▓▓▒░▒░░░░░▒▒▒▒░░░░░░░░░ \n");
	printf("   ░░░░░░░░░▒▓▓▓░▓▓▒▒▒░▒▒▒▒▒░░░░░▒▒░▒▒░▒▒░░░░░░▒░░░░░░░ \n");
	printf("   ░░░░░░░░░█▓█▒▒▓▒░░▓░▒▒▒▒▒░░░░░░░░░░░░░░░░░░▒░░░░░░░░ \n");
	printf("   ░░░░░░░░█▓▓█▒▒▓▓▓▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░▒▒▒▒░░░░░░ \n");
	printf("   ░░░░░░░░▓███▓██▒░░▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░▒▓▓░░░░░░ \n");
	printf("   ░░░░░░░▓█████▓▓▓▓▒▓██▓▒▒░░░░░░░░░░░░░░░░░░▒▒▒░░░░░░░ \n");
	printf("   ░░░░░░░▓██████▓▒▓████▓▓▒▓▓▓▓▓▓▒░░░░▒▒▒▒▒▒▒▓▒░░░░░░░░ \n");
	printf("   ░░░░░░░█████████▓█▓██████▓▒▓███▓░░▒███▓▓▓▒▓▓▒░░░░░░░ \n");
	printf("   ░░░░░░░████████▓░▓▓▓▓████▓▒▒███▓░░▒█▓▓▓▓▓░▓░░░░░░░░░ \n");
	printf("   ░░░░░░░░███████▓▒▓▓▓▒░░▒▒▒▒░░▒▓▓░░░░▒▒▒░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░███████▓▒▓██▓▒▒░░░░░░▒▓▓▒░░░░░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░▒████▒▓▒▒▓██▓▓▒▒░░░▒▓▓▓▒░░░░░░░▒░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░▓███▓▓▒▒▒▓▒▒▓▓▒▒▒▒▓▓██▓▒▒▒░░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░██▓▓▒▒▒▓▒▒▒▒▒▒▒▒▒▒▓████▓▒░░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░▒████▒▒▓█▒░▒▒▒▒▒▒▒▒▓██▓▒▒░░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░░█▓█▒▒▒▒█▓▒▒▒▒▓▓████████▓▒░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░░▓███▓▓▒▒▒▓▓▒▒▓▓▒▒░░░░░▒▒░░░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░░███▓▓█▓▓▓▒▓▓▒░▒▒░░░░░░░░░▒░░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░░▒███▓▓███▓▒▒▓▒▒▒░▒░░▒▒░░▒▒▒░░░░░░░░░░░░░ \n");
	printf("   ░░░░░░░░░░░▒▒▓████▓▓▓███▓▓▓▓▓▓▒▒▓▓█▓▒▒░▒▒▒░░░░░░░░░░ \n");
	print_intro2();
}
