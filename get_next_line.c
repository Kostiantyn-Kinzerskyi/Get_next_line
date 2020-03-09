/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkinzers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:57:02 by kkinzers          #+#    #+#             */
/*   Updated: 2018/12/06 22:20:02 by kkinzers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*delstring(char *s)
{
	int			i;
	int			j;
	char		*str;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s) - i + 1))))
		return (NULL);
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

static char		*string(char *s)
{
	int			i;
	char		*str;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (!(str = ft_strnew(i)))
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	char		cache[BUFF_SIZE + 1];
	static char	*buf[0];
	char		*vb;
	int			r;

	if (fd < 0 || BUFF_SIZE < 1 || line == NULL || (read(fd, cache, 0) < 0))
		return (-1);
	*line = ft_strnew(1);
	while ((r = read(fd, cache, BUFF_SIZE)) > 0)
	{
		cache[r] = '\0';
		vb = buf[fd];
		buf[fd] = ft_strjoin(buf[fd], cache);
		free(vb);
		if (ft_strchr(cache, '\n'))
			break ;
	}
	vb = *line;
	*line = string(buf[fd]);
	free(vb);
	if ((r == 0 && ft_strcmp(buf[fd], "") == 0))
		return (0);
	buf[fd] = delstring(buf[fd]);
	return (1);
}
