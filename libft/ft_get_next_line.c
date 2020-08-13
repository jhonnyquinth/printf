/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrynn <sbrynn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:53:59 by sbrynn            #+#    #+#             */
/*   Updated: 2020/02/22 17:33:27 by sbrynn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*memccpy_2(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char*)dest;
	s = (const unsigned char*)src;
	if (d == s)
		return ((void*)src);
	if (!d && !s)
		return (NULL);
	while (n != 0)
	{
		if (*s == (unsigned char)c)
			return ((void*)(d + 1));
		*d = *s;
		s++;
		d++;
		n--;
	}
	return (NULL);
}

static int		gnl(int fd, char **mem, char **line)
{
	char	*s;
	char	*tmp;

	s = ft_strchr(mem[fd], '\n');
	if (s)
	{
		*line = ft_memalloc(s - mem[fd] + 1);
		memccpy_2(*line, mem[fd], '\n', ft_strlen(mem[fd]) - 1);
		tmp = ft_strdup(s + 1);
		free(mem[fd]);
		mem[fd] = tmp;
		if (*tmp == '\0')
			ft_strdel(&fd[mem]);
	}
	else
	{
		*line = ft_strdup(mem[fd]);
		ft_strdel(&mem[fd]);
	}
	return (1);
}

int				ft_get_next_line(const int fd, char **line)
{
	static char		*mem[2147483647];
	char			buff[BUFF_SIZE + 1];
	int				r;
	char			*s;

	if (fd > 2147483647)
		return (-1);
	while ((r = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		if (mem[fd] == NULL)
			mem[fd] = ft_strnew(1);
		s = ft_strjoin(mem[fd], buff);
		free(mem[fd]);
		mem[fd] = s;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (r < 0 || fd < 0 || !line)
		return (-1);
	else if (r == 0 && (mem[fd] == NULL || mem[fd][0] == '\0'))
		return (0);
	return (gnl(fd, mem, line));
}
