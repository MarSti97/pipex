/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:30:55 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 16:48:44 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int m_str(char const *s, char **split, char c)
{
	int words;
	int leng;
	words = 0;

	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
			words++;
		leng = 0;
		while (s[leng] != c && s[leng] != '\0')
			leng++;
		if (split && leng)
			split[words - 1] = ft_substr(s, 0, leng);
		s += leng;
	}
	if (split)
		split[words] = NULL;
	return (words);
}
char **ft_split(char const *s, char c)
{
	char **split;

	split = (char **) malloc(sizeof(char *) * (m_str(s, NULL, c) + 1));
	if (!split)
		return (0);
	m_str(s, split, c);
	return (split);
}

// static void	free_data(char **data);

// static int	counter(char const *str, char c)
// {
// 	int	i;
// 	int	count;
// 	int	skip;

// 	i = 0;
// 	count = 0;
// 	skip = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != c && skip == 0)
// 		{
// 			count += 1;
// 			skip = 1;
// 		}
// 		i++;
// 		while (str[i] == c && str[i])
// 		{
// 			skip = 0;
// 			i++;
// 		}
// 	}
// 	return (count);
// }

// static int	mem_all(char const *str, char c, char **res)
// {
// 	int		i;
// 	int		count;
// 	int		size;

// 	count = 0;
// 	i = 0;
// 	size = 0;
// 	while (str[size])
// 	{
// 		while (str[size] != c && str[size])
// 			size++;
// 		res[count] = ft_calloc(sizeof(char), ((size - i) + 1));
// 		if (!res[count])
// 		{
// 			free_data(res);
// 			return (1);
// 		}
// 		ft_memcpy(res[count], &str[i], (size - i));
// 		count++;
// 		while (str[size] == c && str[size])
// 				size++;
// 		i = size;
// 	}
// 	return (0);
// }

// char	**ft_split(char const *str, char c)
// {
// 	char	**res;
// 	int		words;
// 	char	*ptr;

// 	words = counter(str, c);
// 	ptr = ft_strtrim(str, (char *)&c);
// 	if (!ptr)
// 		return (NULL);
// 	res = (char **)malloc(sizeof(char *) * (words + 1));
// 	if (!res)
// 		return (NULL);
// 	if (mem_all(ptr, c, res) == 1)
// 		return (NULL);
// 	res[words] = NULL;
// 	free (ptr);
// 	return (res);
// }

// static void	free_data(char **data)
// {
// 	int	i;

// 	i = 0;
// 	while (data[i])
// 	{
// 		free (data[i]);
// 		i++;
// 	}
// 	free (data);
// }

// int main()
// {
//     char const str[] = "0 1 2 3 4 ";
//     char c = ' ';
// 	char **res = ft_split(str, c);
// 	printf("%i\n", counter(str, c));
// 	printf("Result word 1: %s$\n", res[0]);
// 	printf("Result word 2: %s$\n", res[1]);
// 	printf("Result word 3: %s$\n", res[2]);
// 	printf("Result word 4: %s$\n", res[3]);
// 	printf("Result word 5: %s$\n", res[4]);
// 	printf("Result word NULL: %s$\n", res[5]);
// 	free_data(res);
// }
