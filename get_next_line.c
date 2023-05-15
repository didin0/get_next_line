/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:13:39 by mabbadi           #+#    #+#             */
/*   Updated: 2023/05/15 17:57:18 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *backup)
{
	int		readed;
	char	*char_temp;

	readed = 1;
	while (readed != '\0')
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
			return (NULL);
		else if (readed == 0)
			break ;
		buf[readed] = '\0';
		if (!backup)
			backup = ft_strdup("");
		char_temp = backup;
		backup = ft_strjoin(char_temp, buf);
		free(char_temp);
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (backup);
}

char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = ft_read(fd, buf, backup);
	free(buf);
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = extract(line);
	return (line);
}

// int main()
// {
// 	int fd;

// 	fd = open("read_error.txt", O_RDONLY);
// 	if (fd < 0) {
// 		perror("r1");
// 		exit(1);
// 	}

// 	printf("Those bytes are as follows: %s", get_next_line(fd));

// 	return 0;
// }
