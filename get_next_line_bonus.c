/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:19:23 by jocorrea          #+#    #+#             */
/*   Updated: 2023/02/12 16:31:41 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_line_buffer(int fd, char *buffer)
{
	ssize_t	r;
	char	tmp[BUFFER_SIZE + 1];

	tmp[0] = '\0';
	r = 1;
	while (r > 0 && !ft_strchr(buffer, '\n'))
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r == -1)
			return (true_free(&buffer));
		if (r > 0)
		{
			tmp[r] = '\0';
			buffer = ft_strjoin(buffer, tmp, r);
			if (!buffer)
				return (NULL);
		}
	}
	return (buffer);
}

char	*split_first_line(char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		tmp = ft_calloc((i + 2), sizeof(char));
	else
		tmp = ft_calloc((i + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	j = -1;
	while (++j <= i)
		tmp[j] = buffer[j];
	return (tmp);
}

char	*update_line_save(char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i] || !buffer[i + 1])
		return (true_free(&buffer));
	tmp = ft_calloc((ft_strlen(buffer) - i), sizeof(char));
	if (!tmp)
		return (true_free(&buffer));
	j = 0;
	while (buffer[++i])
		tmp[j++] = buffer[i];
	true_free(&buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (!buffer[fd])
		buffer[fd] = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (true_free(&buffer[fd]));
	if (!buffer[fd] || (buffer[fd] && !ft_strchr(buffer[fd], '\n')))
		buffer[fd] = fill_line_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = split_first_line(buffer[fd]);
	if (!line)
		return (true_free(&buffer[fd]));
	buffer[fd] = update_line_save(buffer[fd]);
	return (line);
}
