/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 19:10:47 by ael-hana          #+#    #+#             */
/*   Updated: 2017/04/09 15:05:51 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_HPP
# define INIT_HPP
# include "Class.Aplayer.hpp"
# include "Class.Gamer.hpp"
# include "Ncurse.hpp"
typedef struct node	t_node;

struct node	{
		Aplayer		*ptr;
		t_node		*next;
};
t_node	*insList(t_node *, int);
void	list_add_Entities(Aplayer *ins);
void	eventLoop(Ncurse *, Gamer *);
void	list_free_Entities(Aplayer *ins);
#endif
