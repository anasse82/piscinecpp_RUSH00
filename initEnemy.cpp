#include "initEnemy.hpp"
#include "Class.Enemy.hpp"
#include "Class.Shoot.hpp"
#include <unistd.h>
#include <stdio.h>

t_node	*insList(t_node *, int = 0);

t_node	*insListEnemy(t_node *ins, int opt = 0)
{
	static t_node *ptr = NULL;

	if (opt == 1)
		ptr = ins;
	else if (ptr == NULL)
	{
		if (ins)
			ptr = ins;
		return NULL;
	}
	return ptr;
}

void	list_add_EntitiesEnemy(Aplayer *ins)
{
	t_node *list = new node;
	t_node	*ptr = NULL;

	list->ptr = ins;
	list->next = NULL;
	ptr = insListEnemy(list);
	if (ptr == NULL)
		return;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = list;
}

void	generate_aste(void){
	int		posy = (rand() % WINDOW_Y) - 3;
	if (posy < 0)
		posy = 0;
	list_add_EntitiesEnemy(new Enemy("1", 0, 0, WINDOW_X - 3, posy));
	list_add_EntitiesEnemy(new Enemy("2", 0, 0, WINDOW_X - 3, posy + 1));
	list_add_EntitiesEnemy(new Enemy("3", 0, 0, WINDOW_X - 3, posy + 2));
	list_add_EntitiesEnemy(new Enemy("4", 0, 0, WINDOW_X - 2, posy));
	list_add_EntitiesEnemy(new Enemy("5", 0, 0, WINDOW_X - 2, posy + 1));
	list_add_EntitiesEnemy(new Enemy("6", 0, 0, WINDOW_X - 2, posy + 2));
	list_add_EntitiesEnemy(new Enemy("7", 0, 0, WINDOW_X - 1, posy));
	list_add_EntitiesEnemy(new Enemy("8", 0, 0, WINDOW_X - 1, posy + 1));
	list_add_EntitiesEnemy(new Enemy("9", 0, 0, WINDOW_X - 1, posy + 2));
}

void	eventLoopEnemy(Ncurse *game, Gamer *g){
	t_node	*ptr;
	t_node	*tmp;
	char const *newargv[] = {"say", "-v", "Thomas", "TIJE", NULL};
	char *env[] = {NULL};
	pid_t pid;
	static int	loop = 0;
	static int	loopshoot = 0;
	static int	loopins = 100;
	std::string		tab[] = {"A", "B", "C", "D", "E", "F", "G", "H", "TOTO", "ZIZI",
		"SEGFAULT", "COTON", "ZAZ", "THOR", "PAMPATA", "GARGAMEL"};
	std::string str(tab[rand() % 15]);
	const int			touch = TOUCH_ENEMY;

	++loop;
	if (loop <= 0)
		loop = 1;
	if ((g->getScore() / 100) == 1)
		loopins = 80;
	if ((g->getScore() / 100) == 3)
		loopins = 40;
	if ((g->getScore() / 100) >= 5 && loopins > 5)
		loopins -= 1;
	if (loop % loopins == 0)
	{
		list_add_EntitiesEnemy(new Enemy(str, 0, 0, WINDOW_X, rand() % WINDOW_Y));
		if ((++loopshoot % 5) == 0)
			list_add_EntitiesEnemy(new Shoot("+", 0, 0, WINDOW_X, rand() % WINDOW_Y));
		if ((loopshoot % 10) == 0)
			generate_aste();
	}
	ptr = insListEnemy(NULL);
	while (ptr) {
		*(ptr->ptr) << *(ptr->ptr);
		if (ptr->ptr->getPosX() == g->getPosX() &&
			ptr->ptr->getPosY() == g->getPosY())
		{
			ptr->ptr->setPosX(0);
			std::cout << " TIG !";
			pid = fork();
			if (pid == 0)
				execve("/usr/bin/say", (char *const *)newargv, env);
			g->setLife((g->getLife() - touch));
		}
		if (g->getLife() == 0)
			return;
		else if (ptr && ptr->ptr->getPosX() <= 0)
		{
			tmp = ptr->next;
			list_free_EntitiesEnemy(ptr->ptr);
			g->setScore(g->getScore() + touch);
			ptr = tmp;
		}
		else if (ptr)
		{
			game->print(ptr->ptr->getName(), ptr->ptr->getPosY(), ptr->ptr->getPosX());
			ptr = ptr->next;
		}
	}
}

void	list_free_EntitiesEnemy(Aplayer *ins)
{
	t_node	*ptr;
	t_node	*tmp;
	ptr = insListEnemy(NULL);
	if (ptr == NULL)
		return;
	if (ins == ptr->ptr)
	{
		tmp = ptr->next;
		delete ptr->ptr;
		delete ptr;
		insListEnemy(tmp, 1);
		return;
	}
	while (ptr->next)
	{
		if (ins == ptr->next->ptr)
		{
			tmp = ptr->next->next;
			delete ptr->next->ptr;
			delete ptr->next;
			ptr->next = tmp;
			return;
		}
		ptr = ptr->next;
	}
}
