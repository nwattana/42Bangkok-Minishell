/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uuid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:25:58 by lkaewsae          #+#    #+#             */
/*   Updated: 2023/02/21 01:36:05 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/here_doc.h"

char	*uuid_extend(unsigned char *buffer)
{
	char			*ret;
	int				random;
	ssize_t			read_ret;

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
	if (!ret)
		return (NULL);
	close(random);
	return (ret);
}

char	*uuid_generator(void)
{
	char			*moving;
	int				i;
	unsigned char	pick;
	unsigned char	buffer[16];

	moving = uuid_extend(buffer);
	i = 0;
	while (i < 16)
	{
		pick = buffer[i];
		*moving++ = "0123456789abcdef"[pick >> 4];
		*moving++ = "0123456789abcdef"[pick & 0x0f];
		if (i == 3 || i == 5 || i == 7 || i == 9)
			*moving++ = '-';
		i++;
	}
	*moving = '\0';
	return (uuid_extend(buffer));
}
