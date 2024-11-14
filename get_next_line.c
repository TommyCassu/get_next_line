/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:05:02 by toto              #+#    #+#             */
/*   Updated: 2024/11/14 15:21:15 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*file_read(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	ssize_t b_read;
	int		retour;

	retour = 1;
	while (retour != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE));
		//zprintf("alloc BUFFER\n");
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (b_read == -1)
			return NULL;
		buffer[b_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (ft_strlen(stash) > 0)
			free(stash);
		//printf("free previous strjoin\n");
		stash = temp;
		free(buffer);
		//printf("free BUFFER\n");
		if (ft_strchr(stash, '\n') != NULL || b_read == 0)
            retour = 0;
	}
	return (stash);
}
char	*get_line(char *str)
{
	char	*line;
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*get_stash(char *str, char *stash)
{
	char	*tempstash;
	int i;
	int j;
	
	i = 0;
	j = 0;
	
	while (stash[i] != '\n')
		i++;
	while(stash[i++] != '\0')
		j++;
	tempstash = (char *)malloc(sizeof(char) * (j));
	//printf("alloc tempstash\n");
	i = ft_strlen(str);
	j = 0;
	while (stash[i] != '\0')
	{
		tempstash[j++] = stash[i++];
	}
	tempstash[j] = '\0';
	free(stash);
	return(tempstash);
}
char	*get_next_line(int fd)
{
	static char	*stash = "";
	char	*line;
	char	*temp;
	// recuperer la ligne
	printf("%s", stash);
	temp = file_read(fd, stash);
	// on assigne la ligne
	line = get_line(temp);
	// on separe le surplus de ligne
	stash = get_stash(line, temp);
	
	if (ft_strchr(stash, '\0') == stash)
		printf("fin");
	return (line);
}

int main()
{
	int fd;
	char *result;
	
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (1);
	}
	result = get_next_line(fd);
	printf("Ligne 1 :%s", result);
	free(result);
	result = get_next_line(fd);
	printf("Ligne 1 :%s", result);
	free(result);

	close(fd);
	return (0);
}
