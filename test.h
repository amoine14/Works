/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:09:30 by username          #+#    #+#             */
/*   Updated: 2026/10/23 22:55:18 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <errno.h>
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>
# include <ctype.h>
# include <string.h>
# include <strings.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define BOLD "\033[1m"

typedef struct s_test_result
{
	const char	*name;
	int			passed;
	int			total;
}	t_test_result;

/* Fonctions communes */

static void	memory_header(const char *name);
static void memory_result(t_test_result * result, const char * label,
	int	obtained, int expected);
static int	number_sign(int n);

/* ASCII et caracteres */

static void test_is(t_test_result * result, int(*ft)(int),
	int	(*original)(int), int normaliser);
static void	tests_ascii(t_test_result results[7]);

/* Memoire */

static void test_memset(t_test_result * result,
	void	*(*ft)(void *, int, size_t),
void	*(*original)(void *, int, size_t));
static void test_bzero(t_test_result * result,
	void	(*ft)(void *, size_t),
void	(*original)(void *, size_t));
static void test_copy(t_test_result * result,
	void	*(*ft)(void *, const void *, size_t),
void	*(*original)(void *, const void *, size_t));
static void test_move_overlap(t_test_result * result,
	void	*(*ft)(void *, const void *, size_t),
void	*(*original)(void *, const void *, size_t));
static void test_memchr(t_test_result * result,
	void	*(*ft)(const void *, int, size_t),
void	*(*original)(const void *, int, size_t));
static void test_memcmp(t_test_result * result,
	int	(*ft)(const void *, const void *, size_t),
int	(*original)(const void *, const void *, size_t));
static void	tests_memory(t_test_result results[6]);

/* Chaines de caracteres */

static void	test_strlen(t_test_result *result);
static void test_char_search(t_test_result * result,
	char	*(*ft)(const char *, int),
char	*(*original)(const char *, int));
static void	test_strncmp(t_test_result *result);
static void	test_strlcpy(t_test_result *result);
static void	test_strlcat(t_test_result *result);
static void	test_strnstr(t_test_result *result);
static void	tests_strings(t_test_result results[7]);

/* Allocations et conversions */

static void check_allocated_string(t_test_result * result,
	const char	*label, char *obtained,
const char	*expected);
static void	test_atoi(t_test_result *result);
static void	test_calloc(t_test_result *result);
static void	test_strdup(t_test_result *result);
static void	test_substr(t_test_result *result);
static void	test_strjoin(t_test_result *result);
static void	test_strtrim(t_test_result *result);
static void	test_itoa(t_test_result *result);
static void	tests_allocations(t_test_result results[7]);

/* Resume */

static size_t summary_section(const char * title,
	const t_test_result	*results, size_t count);
static void	print_summary(const t_test_result results[43]);
void		*__real_malloc(size_t size);
void		*__wrap_malloc(size_t size);

#endif
