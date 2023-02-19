
#ifndef HERE_DOC_H
#define HERE_DOC_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>

# define BUFFER_SIZE 1

char    *get_next_line(int fd);
char    *get_here_doc(char *str);
char	*uuid_generator(void);
char	*hd_name(char *str);
int ft_strcmp(char *str1, char *str2);

#endif