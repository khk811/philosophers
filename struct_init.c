#include "philo.h"

t_args	*t_args_init(void)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
		return (NULL);
	new->philo_num = 0;
	new->time_to_die = 0;
	new->time_to_eat = 0;
	new->time_to_sleep = 0;
	new->num_of_must_eat = 0;
	return (new);
}

t_info	*t_info_init(void)
{
	t_info	*new;

	new = malloc(sizeof(t_info));
	if (!new)
		return (NULL);
	new->start = malloc(sizeof(struct timeval));
	if (!(new->start))
	{
		free(new);
		new = NULL;
		return (NULL);
	}
	gettimeofday(new->start, NULL);
	return (new);
}
