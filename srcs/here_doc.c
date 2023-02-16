#include "../inc/here_doc.h"

int ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	if (!str1 || !str2)
	{
		return (0);
	}
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}


char	*reallocate(char *old, int size)
{
	char	*tmp;
	char	*alloc;
	int		i;

	alloc = calloc(size, sizeof(char));
	tmp = old;
	while (tmp[i])
	{
		alloc[i] = tmp[i];
		i++;
	}
	free(old);
	return (tmp);
}

char	*get_next_line(int fd)
{
	int		i;
	char	*ret;
	int		size;

	i = 0;
	size = 1;
	if (read(fd, NULL, 0) < 0)
		return (NULL);
	ret = calloc(sizeof(char), 200);
	while(read(fd, &ret[i], 1) > 0 && ret[i] != '\n')
	{
		i++;
		if (i > size * 200 - 1)
		{
			size++;
			ret = reallocate(ret, size * 200);
		}
	}
	ret[i + 1] = '\0'; 
	return (ret);
}

char	*uuid_generator(void)
{
	char			*ret;
	int				random;
	unsigned char	buffer[16];
	char			*moving;
	ssize_t			read_ret;
	int				i;
	unsigned char	pick;


	random = open("/dev/urandom", O_RDONLY);
	if (random < 0)
		return (NULL);
	read_ret = read(random, buffer, sizeof(buffer));
	if (read_ret != sizeof(buffer))
	{
		close(random);
		return (NULL);
	}
	ret = malloc(sizeof(char) * 37);
	if(!ret)
		return (NULL);
	close(random);
	moving = ret;
	i = 0;
	while (i < 16)
	{
		pick = buffer[i];
		*moving++ = "0123456789abcdef"[pick >> 4];
		*moving++ = "0123456789abcdef"[pick & 0x0f];
		if (i == 3 || i == 5 || i == 7 || i == 9)
		{
            *moving++ = '-';
        }
		i++;
	}
	*moving = '\0';
	return (ret);
}

char    *get_here_doc(char *str)
{
    char    *tmp;
    char    *ret;
    char    *delim;

    delim = ft_strjoin(str, "\n");
    ret = ft_calloc(sizeof(char), 1);
	ret[0] = '\0';
    while (1)
    {
        tmp = get_next_line(0);
        if (ft_strcmp(tmp, delim) == 0)
            break;
        if (ret == NULL)
            ret = tmp;
        else
            ret = ft_strappend(ret , tmp);
    }
    free(delim);
    return (ret);
}

/// @brief Need optimise
/// @param str 
/// @return 
char	*hd_name(char *str)
{
	char	*ret;
	char	*uuid;

	uuid = uuid_generator();
	ret = ft_strdup(".");
	ret = ft_strappend(ret, uuid);
	ret = ft_strappend(ret, "-");
	ret = ft_strappend(ret, str);
	free(uuid);
	return (ret);
}