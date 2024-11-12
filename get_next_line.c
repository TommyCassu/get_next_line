/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:05:02 by toto              #+#    #+#             */
/*   Updated: 2024/11/12 16:51:20 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

# define BUFFER_SIZE 6

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		size;
	char	*result;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static	char	*stash = "";// memoire reserve
	char	buffer[BUFFER_SIZE]; // memoire buffer pour read
	char	*line;  // memoire pour la ligne en cours
	char	*t;
	ssize_t b_read;
	int retour;
	int i;

	i = 0;
	retour = 0;
	line = "";
	while (retour == 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (b_read == -1)
			return (NULL);
		t = ft_strjoin(stash, buffer);
		stash = t;
		//printf("%s\n", stash);
		if (ft_strchr(stash, '\n') != NULL)
			retour = 1;
	}
	line = stash;
	printf("%s\n", line[0]);
	printf("Stash : %s\n", line);
	
	stash = ft_strchr(stash, '\n');
	stash = ft_strcpy(stash , stash + 1);
	
	printf("Stash : %s\n", stash);
	//return (line);
}

int main()
{
	int fd;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (1);
	}
	get_next_line(fd);
	//printf("Line : %s\n", get_next_line(fd));
	//get_next_line(fd);
}
/* if (ft_strchr(stash, '\n') == NULL)
			retour = 1;
			
			
			char	buffer[BUFFER_SIZE]; // memoire buffer pour read
	//char	*line;  // memoire pour la ligne en cours
	char *temp;
	ssize_t b_read;
	int retour;

	retour = 0;
	while (retour == 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (b_read == -1)
		{
			// Erreur de lecture
			free(stash);
			return NULL;
		}
		ft_strjoin(buffer, stash);
		printf("%s", buffer);
	}
	//printf("%s", stash);*/