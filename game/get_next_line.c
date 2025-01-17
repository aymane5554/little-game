/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:25:00 by ayel-arr          #+#    #+#             */
/*   Updated: 2024/11/16 17:25:02 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*nb;

	i = 0;
	nb = (char *)b;
	while (i < len)
	{
		nb[i] = c;
		i++;
	}
	return ((void *)nb);
}

char	*line_in_last(char **last, char *buff)
{
	char	*new;

	new = *last;
	*last = ft_strdup(*last + isin(*last, ft_strlen(*last), '\n') + 1);
	new[isin(new, ft_strlen(new), '\n') + 1] = '\0';
	free(buff);
	return (new);
}

void	free_empty_string(char **new)
{
	if (*new != NULL && **new == '\0')
	{
		free(*new);
		*new = NULL;
	}
}

char	*line_in_lastbuffer(char **last, char *buffer, int byte)
{
	char	*new;

	if (byte == 0)
	{
		new = *last;
		*last = NULL;
		free_empty_string(&new);
		free(buffer);
		return (new);
	}
	new = *last;
	*last = ft_strjoin(*last, buffer);
	free(new);
	new = *last;
	if (isin(new, ft_strlen(new), '\n') > -1)
	{
		*last = ft_strdup(*last + isin(*last, ft_strlen(*last), '\n') + 1);
		new[isin(new, ft_strlen(new), '\n') + 1] = '\0';
	}
	else if (isin(new, ft_strlen(new), '\n') == -1 && new[0] != '\0')
		*last = NULL;
	free(buffer);
	return (new);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*last;
	char			*tmp;
	int				byte;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = malloc((long long)BUFFER_SIZE + 1);
	if (buffer == NULL || read(fd, buffer, 0) == -1)
		return (free(buffer), NULL);
	while (1)
	{
		if (last != NULL && isin(last, ft_strlen(last), '\n') > -1)
			return (line_in_last(&last, buffer));
		ft_memset(buffer, '\0', (long long)BUFFER_SIZE + 1);
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte < BUFFER_SIZE)
			return (line_in_lastbuffer(&last, buffer, byte));
		tmp = last;
		last = ft_strjoin(last, buffer);
		free(tmp);
	}
	return (last);
}
