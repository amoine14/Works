/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoine <amoine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:04:47 by username          #+#    #+#             */
/*   Updated: 2026/10/23 22:58:37 by amoine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "test.h"
#include <stdio.h>
#include <ctype.h>

static int	g_malloc_fail_at = 0;
static int	g_malloc_calls = 0;

void	*__wrap_malloc(size_t size)
{
	if (g_malloc_fail_at > 0)
	{
		g_malloc_calls++;
		if (g_malloc_calls == g_malloc_fail_at)
			return (NULL);
	}
	return (__real_malloc(size));
}

/*
** Affichage et enregistrement des résultats.
*/

static void test_is(t_test_result * result, int(*ft)(int),
	int	(*original)(int), int normaliser)
{
	const int	tab_tests[15] =
	{
		0, ' ', '/', '0', '9', 'A', 'Z', 'a', 'z', 127,
		EOF, 31, 126, 128, 255
	};
	int	i;
	int	obtenu;
	int	attendu;

	printf(BOLD CYAN "\n%s\n" RESET, result->name);
	printf("+----------+-------------+--------------+--------+\n");
	printf("| %8s | %11s | %12s | Statut |\n",
		"Entree", "Obtenu", "Attendu");
	printf("+----------+-------------+--------------+--------+\n");
	i = 0;
	while (i < 15)
	{
		obtenu = ft(tab_tests[i]);
		attendu = original(tab_tests[i]);
		if (normaliser)
		{
			obtenu = !!obtenu;
			attendu = !!attendu;
		}
		result->total++;
		result->passed += (obtenu == attendu);
		printf("| %8d | %11d | %12d | ",
			tab_tests[i], obtenu, attendu);
		if (obtenu == attendu)
			printf(BOLD "[" GREEN "OK" RESET BOLD "]" RESET "   |\n");
		else
			printf(BOLD "[" RED "FAIL" RESET BOLD "]" RESET " |\n");
		i++;
	}
	printf("+----------+-------------+--------------+--------+\n");
}

static void	tests_ascii(t_test_result results[7])
{
	const char	*names[7] =
	{
		"ft_isalpha", "ft_isdigit", "ft_isalnum", "ft_isascii",
		"ft_isprint", "ft_toupper", "ft_tolower"
	};
	int	i;

	printf(BOLD CYAN
		"\n============================================================\n"
	"             SERIE 01 - ASCII ET CARACTERES\n"
	"============================================================\n" RESET);
	i = 0;
	while (i < 7)
	{
		results[i].name = names[i];
		results[i].passed = 0;
		results[i].total = 0;
		i++;
	}
	test_is(&results[0], ft_isalpha, isalpha, 1);
	test_is(&results[1], ft_isdigit, isdigit, 1);
	test_is(&results[2], ft_isalnum, isalnum, 1);
	test_is(&results[3], ft_isascii, isascii, 1);
	test_is(&results[4], ft_isprint, isprint, 1);
	test_is(&results[5], ft_toupper, toupper, 0);
	test_is(&results[6], ft_tolower, tolower, 0);
}

static void	memory_header(const char *name)
{
	printf(BOLD CYAN "\n%s\n" RESET, name);
	printf("------------------------------------------------------------\n");
	printf("%-28s | %-8s | %-8s | Statut\n",
		"Test", "Obtenu", "Attendu");
	printf("------------------------------------------------------------\n");
}

static void memory_result(t_test_result * result, const char * label,
	int	obtained, int expected)
{
	int	ok;

	ok = (obtained == expected);
	result->total++;
	result->passed += ok;
	printf("%-28s | %8d | %8d | ", label, obtained, expected);
	if (ok)
		printf(BOLD "[" GREEN "OK" RESET BOLD "]" RESET "\n");
	else
		printf(BOLD "[" RED "FAIL" RESET BOLD "]" RESET "\n");
}

static int	number_sign(int n)
{
	return ((n > 0) - (n < 0));
}

/*
** memset : compare tout le buffer, y compris la zone qui doit
** rester intacte, puis vérifie le pointeur retourné.
*/

static void test_memset(t_test_result * result,
	void	*(*ft)(void *, int, size_t),
void	*(*original)(void *, int, size_t))
{
	const int	values[6] =
	{
		'A', 0, -1, 256, 255, 'Z'
	};
	const size_t	sizes[6] =
	{
		5, 5, 3, 3, 1, 0
	};
	const char	*labels[6] =
	{
		"Remplissage normal", "Octets nuls", "Valeur negative",
		"Conversion de 256", "Un seul octet", "Taille nulle"
	};
	unsigned char	obtained[10];
	unsigned char	expected[10];
	void			*ret_ft;
	void			*ret_original;
	int				i;

	memory_header(result->name);
	i = 0;
	while (i < 6)
	{
		memset(obtained, 0xAA, sizeof(obtained));
		memset(expected, 0xAA, sizeof(expected));
		ret_ft = ft(obtained + 2, values[i], sizes[i]);
		ret_original = original(expected + 2, values[i], sizes[i]);
		memory_result(result, labels[i],
			memcmp(obtained, expected, sizeof(obtained)) == 0
		&& ret_ft == obtained + 2,
		ret_original == expected + 2);
		i++;
	}
}

/*
** bzero : vérifie également les octets autour de la zone.
*/

static void test_bzero(t_test_result * result,
	void	(*ft)(void *, size_t),
void	(*original)(void *, size_t))
{
	const size_t	sizes[4] =
	{
		5, 1, 0, 8
	};
	const char	*labels[4] =
	{
		"Zone partielle", "Un seul octet",
		"Taille nulle", "Zone complete"
	};
	unsigned char	obtained[10];
	unsigned char	expected[10];
	int				i;

	memory_header(result->name);
	i = 0;
	while (i < 4)
	{
		memset(obtained, 0xAA, sizeof(obtained));
		memset(expected, 0xAA, sizeof(expected));
		ft(obtained + 1, sizes[i]);
		original(expected + 1, sizes[i]);
		memory_result(result, labels[i],
			memcmp(obtained, expected, sizeof(obtained)) == 0, 1);
		i++;
	}
}

/*
** Copies normales communes à memcpy et memmove.
** Les données contiennent un zéro et des octets élevés.
*/

static void test_copy(t_test_result * result,
	void	*(*ft)(void *, const void *, size_t),
void	*(*original)(void *, const void *, size_t))
{
	const unsigned char	src[8] =
	{
		'A', 0, 'B', 128, 255, 'C', 'D', 'E'
	};
	const size_t	sizes[4] =
	{
		8, 1, 0, 4
	};
	const char	*labels[4] =
	{
		"Copie complete et binaire", "Un seul octet",
		"Taille nulle", "Copie partielle"
	};
	unsigned char	obtained[12];
	unsigned char	expected[12];
	void			*ret_ft;
	void			*ret_original;
	int				i;

	memory_header(result->name);
	i = 0;
	while (i < 4)
	{
		memset(obtained, 0xAA, sizeof(obtained));
		memset(expected, 0xAA, sizeof(expected));
		ret_ft = ft(obtained + 2, src, sizes[i]);
		ret_original = original(expected + 2, src, sizes[i]);
		memory_result(result, labels[i],
			memcmp(obtained, expected, sizeof(obtained)) == 0
		&& ret_ft == obtained + 2,
		ret_original == expected + 2);
		i++;
	}
}

/*
** Cas supplémentaires réservés à memmove.
*/

static void test_move_overlap(t_test_result * result,
	void	*(*ft)(void *, const void *, size_t),
void	*(*original)(void *, const void *, size_t))
{
	const size_t	dst[3] =
	{
		2, 0, 1
	};
	const size_t	src[3] =
	{
		0, 2, 1
	};
	const char	*labels[3] =
	{
		"Chevauchement vers droite",
		"Chevauchement vers gauche",
		"Source et destination egales"
	};
	unsigned char	obtained[10];
	unsigned char	expected[10];
	void			*ret_ft;
	void			*ret_original;
	int				i;

	i = 0;
	while (i < 3)
	{
		memcpy(obtained, "ABCDEFGHI", sizeof(obtained));
		memcpy(expected, "ABCDEFGHI", sizeof(expected));
		ret_ft = ft(obtained + dst[i], obtained + src[i], 6);
		ret_original = original(expected + dst[i], expected + src[i], 6);
		memory_result(result, labels[i],
			memcmp(obtained, expected, sizeof(obtained)) == 0
		&& ret_ft == obtained + dst[i],
		ret_original == expected + dst[i]);
		i++;
	}
}

/*
** memchr : les deux fonctions lisent le même tableau.
** On peut donc comparer directement les pointeurs retournés.
** Pour l'affichage : -1 signifie NULL, sinon indice dans src.
*/

static void test_memchr(t_test_result * result,
	void	*(*ft)(const void *, int, size_t),
void	*(*original)(const void *, int, size_t))
{
	const unsigned char	src[8] =
	{
		'A', 0, 'B', 128, 255, 'A', 'D', 'E'
	};
	const int	values[10] =
	{
		'A', 'E', 'Z', 0, 'A', 'E', 'B', 128, -1, 256
	};
	const size_t	sizes[10] =
	{
		8, 8, 8, 8, 0, 7, 2, 8, 8, 8
	};
	const char	*labels[10] =
	{
		"Premiere occurrence", "Dernier octet", "Octet absent",
		"Recherche de zero", "Taille nulle", "Juste hors limite",
		"Limite avant occurrence", "Octet superieur a 127",
		"Conversion de -1", "Conversion de 256"
	};
	void	*ret_ft;
	void	*ret_original;
	int		position_ft;
	int		position_original;
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		ret_ft = ft(src, values[i], sizes[i]);
		ret_original = original(src, values[i], sizes[i]);
		position_ft = -1;
		position_original = -1;
		if (ret_original)
			position_original = (const unsigned char *) ret_original - src;
		if (ret_ft == ret_original)
			position_ft = position_original;
		else
			position_ft = -2;
		memory_result(result, labels[i], position_ft, position_original);
		i++;
	}
}

/*
** memcmp : comparaison des signes, pas des valeurs exactes.
*/

static void test_memcmp(t_test_result * result,
	int	(*ft)(const void *, const void *, size_t),
int	(*original)(const void *, const void *, size_t))
{
	const unsigned char	left[8][5] =
	{
		{
			'A', 'B', 'C', 'D', 'E'
		},
		{
			'A', 'B', 'C', 'D', 'E'
		},
		{
			'Z', 'B', 'C', 'D', 'E'
		},
		{
			'A', 'B', 'C', 'D', 'E'
		},
		{
			'A', 'B', 'C', 'D', 'E'
		},
		{
			'A', 0, 'B', 'D', 'E'
		},
		{
			0, 0, 0, 0, 0
		},
		{
			255, 0, 0, 0, 0
		}
	};
	const unsigned char	right[8][5] =
	{
		{
			'A', 'B', 'C', 'D', 'E'
		},
		{
			'Z', 'B', 'C', 'D', 'E'
		},
		{
			'A', 'B', 'C', 'D', 'E'
		},
		{
			'A', 'B', 'C', 'D', 'F'
		},
		{
			'A', 'B', 'C', 'D', 'F'
		},
		{
			'A', 0, 'C', 'D', 'E'
		},
		{
			255, 0, 0, 0, 0
		},
		{
			0, 0, 0, 0, 0
		}
	};
	const size_t	sizes[8] =
	{
		5, 0, 5, 5, 4, 5, 1, 1
	};
	const char	*labels[8] =
	{
		"Tableaux identiques", "Taille nulle",
		"Difference au debut", "Difference au dernier octet",
		"Difference hors limite", "Difference apres un zero",
		"Zero contre 255", "255 contre zero"
	};
	int	i;
	int	obtained;
	int	expected;

	memory_header(result->name);
	i = 0;
	while (i < 8)
	{
		obtained = number_sign(ft(left[i], right[i], sizes[i]));
		expected = number_sign(original(left[i], right[i], sizes[i]));
		memory_result(result, labels[i], obtained, expected);
		i++;
	}
}

/*
** Lancement de la catégorie.
** Le tableau de résultats appartient au main pour être conservé.
*/

static void	tests_memory(t_test_result results[6])
{
	const char	*names[6] =
	{
		"ft_memset", "ft_bzero", "ft_memcpy",
		"ft_memmove", "ft_memchr", "ft_memcmp"
	};
	int	i;

	printf(BOLD CYAN
		"\n============================================================\n"
	"             SERIE 02 - OPERATIONS MEMOIRE\n"
	"============================================================\n" RESET);
	i = 0;
	while (i < 6)
	{
		results[i].name = names[i];
		results[i].passed = 0;
		results[i].total = 0;
		i++;
	}
	test_memset(&results[0], ft_memset, memset);
	test_bzero(&results[1], ft_bzero, bzero);
	test_copy(&results[2], ft_memcpy, memcpy);
	test_copy(&results[3], ft_memmove, memmove);
	test_move_overlap(&results[3], ft_memmove, memmove);
	test_memchr(&results[4], ft_memchr, memchr);
	test_memcmp(&results[5], ft_memcmp, memcmp);
}

/*
** Résumé réutilisable pour les autres catégories.
*/

static void	test_strlen(t_test_result *result)
{
	const char	*strings[10] =
	{
		"", "A", "ABC", "Hello world", " ",
		"     ", "\t\n", "ABC\0DEF", "0123456789",
		"abcdefghijklmnopqrstuvwxyz"
	};
	const char	*labels[10] =
	{
		"Chaine vide", "Un caractere", "Trois caracteres",
		"Phrase avec espace", "Un espace", "Cinq espaces",
		"Tabulation et saut de ligne", "Zero au milieu",
		"Dix chiffres", "Alphabet"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		memory_result(result, labels[i],
			ft_strlen(strings[i]), strlen(strings[i]));
		i++;
	}
}

static void test_char_search(t_test_result * result,
	char	*(*ft)(const char *, int),
char	*(*original)(const char *, int))
{
	const char	*strings[10] =
	{
		"ABACA", "ABACA", "ABCDE", "ABCDE", "",
		"", "ABCDE", "ABCDE", "ABACA", "ABCDE"
	};
	const int	chars[10] =
	{
		'A', 'C', 'E', 'Z', 'A',
		0, 0, 'A', 'B', 256
	};
	const char	*labels[10] =
	{
		"Occurrences multiples", "Au milieu", "Dernier caractere",
		"Absent", "Chaine vide", "Zero dans chaine vide",
		"Terminateur final", "Premier caractere",
		"Occurrence unique", "Conversion en char"
	};
	char	*obtained;
	char	*expected;
	int		position;
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		obtained = ft(strings[i], chars[i]);
		expected = original(strings[i], chars[i]);
		position = -1;
		if (expected)
			position = expected - strings[i];
		if (obtained != expected)
			memory_result(result, labels[i], -2, position);
		else
			memory_result(result, labels[i], position, position);
		i++;
	}
}

static void	test_strncmp(t_test_result *result)
{
	const char	*left[10] =
	{
		"ABC", "", "", "ABC", "ABC",
		"ABC", "ABC", "ABC", "\200", "AB\0X"
	};
	const char	*right[10] =
	{
		"ABC", "", "A", "", "ABD",
		"ABD", "XYZ", "ABCD", "\177", "AB\0Y"
	};
	const size_t	sizes[10] =
	{
		3, 5, 1, 1, 3, 2, 0, 4, 1, 4
	};
	const char	*labels[10] =
	{
		"Chaines identiques", "Deux chaines vides",
		"Premiere vide", "Deuxieme vide",
		"Difference dans limite", "Difference hors limite",
		"Taille nulle", "Chaine prefixe",
		"Caracteres non signes", "Arret au terminateur"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		memory_result(result, labels[i],
			number_sign(ft_strncmp(left[i], right[i], sizes[i])),
		number_sign(strncmp(left[i], right[i], sizes[i])));
		i++;
	}
}

/*
** strlcpy : attentes explicites pour ne pas dépendre
** de la disponibilité de strlcpy sur la machine.
*/

static void	test_strlcpy(t_test_result *result)
{
	const char	*src[10] =
	{
		"ABC", "ABC", "ABC", "ABC", "ABC",
		"", "", "A", "ABCDE", "AB\0CD"
	};
	const size_t	sizes[10] =
	{
		8, 0, 1, 3, 4, 5, 0, 2, 3, 8
	};
	const char	*copies[10] =
	{
		"ABC", "", "", "AB", "ABC",
		"", "", "A", "AB", "AB"
	};
	const char	*labels[10] =
	{
		"Copie normale", "Taille nulle", "Place pour zero seul",
		"Troncature", "Taille exacte", "Source vide",
		"Source vide taille nulle", "Un caractere",
		"Troncature importante", "Zero dans source"
	};
	unsigned char	obtained[12];
	unsigned char	expected[12];
	size_t			ret;
	int				i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		memset(obtained, 0xAA, sizeof(obtained));
		memset(expected, 0xAA, sizeof(expected));
		if (sizes[i] > 0)
			memcpy(expected + 1, copies[i], strlen(copies[i]) + 1);
		ret = ft_strlcpy((char *) obtained + 1, src[i], sizes[i]);
		memory_result(result, labels[i],
			ret == strlen(src[i])
		&& memcmp(obtained, expected, sizeof(obtained)) == 0, 1);
		i++;
	}
}

/*
** strlcat : les tailles sont celles annoncées à la fonction.
** Les octets non concernés doivent rester inchangés.
*/

static void	test_strlcat(t_test_result *result)
{
	const char	*initial[10] =
	{
		"AB", "", "AB", "AB", "AB",
		"AB", "AB", "AB", "", "AB"
	};
	const char	*src[10] =
	{
		"CD", "CD", "", "CD", "CD",
		"CD", "CD", "CD", "", "CDEF"
	};
	const size_t	sizes[10] =
	{
		8, 8, 8, 0, 1, 2, 3, 4, 1, 5
	};
	const char	*final[10] =
	{
		"ABCD", "CD", "AB", "AB", "AB",
		"AB", "AB", "ABC", "", "ABCD"
	};
	const size_t	returns[10] =
	{
		4, 2, 2, 2, 3, 4, 4, 4, 0, 6
	};
	const char	*labels[10] =
	{
		"Concatenation normale", "Destination vide", "Source vide",
		"Taille nulle", "Taille inferieure a dst",
		"Taille egale longueur dst", "Place pour zero seul",
		"Troncature", "Deux chaines vides", "Remplissage exact"
	};
	unsigned char	obtained[16];
	unsigned char	expected[16];
	size_t			ret;
	int				i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		memset(obtained, 0xAA, sizeof(obtained));
		memcpy(obtained + 1, initial[i], strlen(initial[i]) + 1);
		memcpy(expected, obtained, sizeof(expected));
		memcpy(expected + 1, final[i], strlen(final[i]) + 1);
		ret = ft_strlcat((char *) obtained + 1, src[i], sizes[i]);
		memory_result(result, labels[i],
			ret == returns[i]
		&& memcmp(obtained, expected, sizeof(obtained)) == 0, 1);
		i++;
	}
}

/*
** strnstr : indices attendus explicites.
*/

static void	test_strnstr(t_test_result *result)
{
	const char	*haystack[10] =
	{
		"ABCDEF", "ABCDEF", "ABCDEF", "ABCDEF", "",
		"", "ABC", "ABCDEF", "ABCDEF", "AAAB"
	};
	const char	*needle[10] =
	{
		"ABC", "CD", "DEF", "XYZ", "",
		"A", "", "CD", "CD", "AAB"
	};
	const size_t	sizes[10] =
	{
		6, 6, 6, 6, 0, 5, 0, 4, 3, 4
	};
	const int	positions[10] =
	{
		0, 2, 3, -1, 0, -1, 0, 2, -1, 1
	};
	const char	*labels[10] =
	{
		"Au debut", "Au milieu", "A la fin", "Absent",
		"Deux chaines vides", "Chaine principale vide",
		"Aiguille vide taille nulle", "Fin exacte sur limite",
		"Correspondance hors limite", "Prefixes repetes"
	};
	char		*obtained;
	const char	*expected;
	int			position;
	int			i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		expected = NULL;
		if (positions[i] >= 0)
			expected = haystack[i] + positions[i];
		obtained = ft_strnstr(haystack[i], needle[i], sizes[i]);
		position = positions[i];
		if (obtained != expected)
			position = -2;
		memory_result(result, labels[i], position, positions[i]);
		i++;
	}
}

static void	tests_strings(t_test_result results[7])
{
	const char	*names[7] =
	{
		"ft_strlen", "ft_strchr", "ft_strrchr", "ft_strncmp",
		"ft_strlcpy", "ft_strlcat", "ft_strnstr"
	};
	int	i;

	printf(BOLD CYAN
		"\n============================================================\n"
	"             SERIE 03 - CHAINES DE CARACTERES\n"
	"============================================================\n" RESET);
	i = 0;
	while (i < 7)
	{
		results[i].name = names[i];
		results[i].passed = 0;
		results[i].total = 0;
		i++;
	}
	test_strlen(&results[0]);
	test_char_search(&results[1], ft_strchr, strchr);
	test_char_search(&results[2], ft_strrchr, strrchr);
	test_strncmp(&results[3]);
	test_strlcpy(&results[4]);
	test_strlcat(&results[5]);
	test_strnstr(&results[6]);
}

static void check_allocated_string(t_test_result * result,
	const char	*label, char *obtained, const char *expected)
{
	int	ok;

	ok = (obtained != NULL);
	if (ok)
		ok = (strcmp(obtained, expected) == 0);
	memory_result(result, label, ok, 1);
	if (!ok)
	{
		printf("  Obtenu  : \"%s\"\n", obtained ? obtained : "(NULL)");
		printf("  Attendu : \"%s\"\n", expected);
	}
	free(obtained);
}

static void	test_atoi(t_test_result *result)
{
	const char	*inputs[10] =
	{
		"0", "42", "-42", "+42", "",
		" \t\n\v\f\r-123", "00042", "42abc", "--42", "- 42"
	};
	const char	*labels[10] =
	{
		"Zero", "Positif", "Negatif", "Signe plus", "Chaine vide",
		"Tous les espaces initiaux", "Zeros initiaux",
		"Suffixe non numerique", "Double signe", "Espace apres signe"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		memory_result(result, labels[i],
			ft_atoi(inputs[i]), atoi(inputs[i]));
		i++;
	}
	memory_result(result, "INT_MAX",
		ft_atoi("2147483647"), INT_MAX);
	memory_result(result, "INT_MIN",
		ft_atoi("-2147483648"), INT_MIN);
}

static void	test_calloc(t_test_result *result)
{
	const size_t	counts[8] =
	{
		1, 8, 4, 0, 5, 0, 257, 3
	};
	const size_t	sizes[8] =
	{
		1, 1, sizeof(int), 5, 0, 0, 3, sizeof(double)
	};
	const char	*labels[8] =
	{
		"Un octet", "Plusieurs octets", "Tableau de int",
		"Nombre nul", "Taille nulle", "Deux tailles nulles",
		"Bloc plus grand", "Tableau de double"
	};
	unsigned char	*buffer;
	size_t			total;
	size_t			j;
	int				ok;
	int				i;

	memory_header(result->name);
	i = 0;
	while (i < 8)
	{
		total = counts[i] * sizes[i];
		buffer = ft_calloc(counts[i], sizes[i]);
		ok = (total == 0 || buffer != NULL);
		j = 0;
		while (buffer && j < total)
		{
			if (buffer[j] != 0)
				ok = 0;
			j++;
		}
		memory_result(result, labels[i], ok, 1);
		free(buffer);
		i++;
	}
	buffer = ft_calloc(SIZE_MAX / 2 + 1, 2);
	memory_result(result, "Overflow produit vers zero", buffer == NULL, 1);
	free(buffer);
	buffer = ft_calloc(SIZE_MAX / 2 + 2, 2);
	memory_result(result, "Overflow produit vers deux", buffer == NULL, 1);
	free(buffer);
}

static void	test_strdup(t_test_result *result)
{
	const char	*inputs[10] =
	{
		"", "A", "ABC", "Hello world", " ",
		"     ", "\t\n", "AB\0CD", "\200\377",
		"abcdefghijklmnopqrstuvwxyz"
	};
	const char	*labels[10] =
	{
		"Chaine vide", "Un caractere", "Chaine normale",
		"Phrase avec espace", "Un espace", "Plusieurs espaces",
		"Caracteres de controle", "Zero au milieu",
		"Octets eleves", "Alphabet"
	};
	char	source[64];
	char	*copy;
	int		ok;
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		strcpy(source, inputs[i]);
		copy = ft_strdup(source);
		ok = (copy != NULL);
		if (ok)
			ok = (copy != source && strcmp(copy, inputs[i]) == 0);
		if (ok && copy[0])
		{
			copy[0] = '!';
			ok = (strcmp(source, inputs[i]) == 0);
		}
		memory_result(result, labels[i], ok, 1);
		free(copy);
		i++;
	}
}

static void	test_substr(t_test_result *result)
{
	const char	*inputs[10] =
	{
		"ABCDE", "ABCDE", "ABCDE", "ABCDE", "ABCDE",
		"ABCDE", "ABCDE", "", "ABCDE", "ABCDE"
	};
	const unsigned int	starts[10] =
	{
		0, 1, 4, 2, 5, 6, UINT_MAX, 0, 0, 3
	};
	const size_t	lengths[10] =
	{
		3, 3, 1, 99, 3, 3, 3, 5, 0, SIZE_MAX
	};
	const char	*expected[10] =
	{
		"ABC", "BCD", "E", "CDE", "", "", "", "", "", "DE"
	};
	const char	*labels[10] =
	{
		"Au debut", "Au milieu", "Dernier caractere",
		"Longueur excessive", "Depart sur terminateur",
		"Depart apres la fin", "Depart UINT_MAX",
		"Source vide", "Longueur nulle", "Longueur SIZE_MAX"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		check_allocated_string(result, labels[i],
			ft_substr(inputs[i], starts[i], lengths[i]), expected[i]);
		i++;
	}
}

static void	test_strjoin(t_test_result *result)
{
	const char	*left[10] =
	{
		"AB", "", "AB", "", "A",
		"Hello", " ", "\t", "AB\0X", "\200"
	};
	const char	*right[10] =
	{
		"CD", "CD", "", "", "B",
		" world", " ", "\n", "CD", "\377"
	};
	const char	*expected[10] =
	{
		"ABCD", "CD", "AB", "", "AB",
		"Hello world", "  ", "\t\n", "ABCD", "\200\377"
	};
	const char	*labels[10] =
	{
		"Deux chaines normales", "Premiere vide", "Deuxieme vide",
		"Deux chaines vides", "Un caractere chacune", "Phrase",
		"Espaces", "Caracteres de controle",
		"Arret au premier zero", "Octets eleves"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		check_allocated_string(result, labels[i],
			ft_strjoin(left[i], right[i]), expected[i]);
		i++;
	}
}

static void	test_strtrim(t_test_result *result)
{
	const char	*inputs[10] =
	{
		"  ABC  ", "  ABC", "ABC  ", "ABC", "",
		"ABC", "abba", "xyABCyx", " A B ", "\t\nABC\r "
	};
	const char	*sets[10] =
	{
		" ", " ", " ", " ", " ", "", "ab", "xyx", " ", " \t\n\r"
	};
	const char	*expected[10] =
	{
		"ABC", "ABC", "ABC", "ABC", "",
		"ABC", "", "ABC", "A B", "ABC"
	};
	const char	*labels[10] =
	{
		"Deux extremites", "Debut seulement", "Fin seulement",
		"Aucun retrait", "Source vide", "Ensemble vide",
		"Tout retirer", "Ensemble avec doublon",
		"Conserver espaces internes", "Plusieurs types d'espaces"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		check_allocated_string(result, labels[i],
			ft_strtrim(inputs[i], sets[i]), expected[i]);
		i++;
	}
}

static void	test_itoa(t_test_result *result)
{
	const int	numbers[10] =
	{
		0, 1, -1, 9, 10, -10, 100, -100, INT_MAX, INT_MIN
	};
	char	expected[32];
	char	label[48];
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		snprintf(expected, sizeof(expected), "%d", numbers[i]);
		snprintf(label, sizeof(label), "Conversion de %d", numbers[i]);
		check_allocated_string(result, label,
			ft_itoa(numbers[i]), expected);
		i++;
	}
}

static void	tests_allocations(t_test_result results[7])
{
	const char	*names[7] =
	{
		"ft_atoi", "ft_calloc", "ft_strdup", "ft_substr",
		"ft_strjoin", "ft_strtrim", "ft_itoa"
	};
	int	i;

	printf(BOLD CYAN
		"\n============================================================\n"
	"          SERIE 04 - ALLOCATIONS ET CONVERSIONS\n"
	"============================================================\n" RESET);
	i = 0;
	while (i < 7)
	{
		results[i].name = names[i];
		results[i].passed = 0;
		results[i].total = 0;
		i++;
	}
	test_atoi(&results[0]);
	test_calloc(&results[1]);
	test_strdup(&results[2]);
	test_substr(&results[3]);
	test_strjoin(&results[4]);
	test_strtrim(&results[5]);
	test_itoa(&results[6]);
}

/*
** Comparaison indépendante :
** on parcourt la source et chaque mot retourné simultanément.
** Aucun appel à ft_split, ft_substr ou ft_strlen pour les attentes.
*/

static int	verify_split(const char *source, char separator, char **words)
{
	size_t	pos;
	size_t	word;
	size_t	j;

	if (!words)
		return (0);
	pos = 0;
	word = 0;
	while (source[pos])
	{
		if (source[pos] == separator)
			pos++;
		else
		{
			if (!words[word])
				return (0);
			j = 0;
			while (source[pos] && source[pos] != separator)
			{
				if (words[word][j] != source[pos])
					return (0);
				pos++;
				j++;
			}
			if (words[word][j] != '\0')
				return (0);
			word++;
		}
	}
	return (words[word] == NULL);
}

static void	destroy_split(char **words)
{
	size_t	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

/*
** Source exacte + copie témoin.
** La copie témoin sert aussi à calculer le résultat attendu,
** même si ft_split modifie accidentellement sa source.
*/

static int	run_split_case(const char *input, char separator)
{
	char	*source;
	char	*witness;
	char	**words;
	size_t	size;
	int		ok;

	size = strlen(input) + 1;
	source = malloc(size);
	witness = malloc(size);
	if (!source || !witness)
	{
		free(source);
		free(witness);
		return (0);
	}
	memcpy(source, input, size);
	memcpy(witness, input, size);
	words = ft_split(source, separator);
	ok = verify_split(witness, separator, words);
	if (memcmp(source, witness, size) != 0)
		ok = 0;
	destroy_split(words);
	free(source);
	free(witness);
	return (ok);
}

static void	split_fixed_cases(t_test_result *result)
{
	const char	*inputs[] =
	{
		"", "", ",", ",,,,,", "A", "A", "ABCDE",
		",ABCDE", "ABCDE,", ",,,ABCDE,,,",
		"A,B,C", "A,,,B,,,,C", ",,A,,B,,C,,",
		"A B\tC\nD", " A B ", "ABC", "   ",
		"A\t\tB\tC", "\nA\n\nB\n",
		"A\200B\200\200C", "A\377B\377\377C",
		"\200,\377", "AB\0,CD", "ABABA",
		"00010002000", "a a  a", "a,b;c", "\377\377"
	};
	const char	separators[] =
	{
		',', '\0', ',', ',', ',', 'A', ',',
		',', ',', ',', ',', ',', ',',
		',', ' ', '\0', '\0', '\t', '\n',
		(char) 128, (char) 255, ',', ',', 'A',
		'0', ' ', ';', (char) 255
	};
	const char	*labels[] =
	{
		"Vide / separateur virgule",
		"Vide / separateur nul",
		"Un separateur seul",
		"Uniquement separateurs",
		"Un caractere conserve",
		"Un caractere retire",
		"Aucun separateur",
		"Separateur au debut",
		"Separateur a la fin",
		"Separateurs autour",
		"Trois mots",
		"Separateurs repetes",
		"Repetitions partout",
		"Espaces et controles gardes",
		"Decoupage sur espace",
		"Separateur nul",
		"Espaces / separateur nul",
		"Decoupage tabulations",
		"Decoupage sauts de ligne",
		"Separateur octet 128",
		"Separateur octet 255",
		"Mots avec octets eleves",
		"Arret au premier zero",
		"Alternance mot separateur",
		"Chiffre comme separateur",
		"Mots identiques",
		"Separateur exact uniquement",
		"Uniquement octets 255"
	};
	size_t	i;

	i = 0;
	while (i < sizeof(inputs) / sizeof(inputs[0]))
	{
		memory_result(result, labels[i],
			run_split_case(inputs[i], separators[i]), 1);
		i++;
	}
}

/*
** Quatre tests de volume :
** - un mot de 100 000 caracteres ;
** - 100 000 separateurs ;
** - 20 000 mots ;
** - longues series de separateurs autour de deux mots.
*/

static size_t	split_expected_words(const char *source, char separator)
{
	size_t	i;
	size_t	count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (source[i])
	{
		if (source[i] == separator)
			in_word = 0;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

static void	split_print_hex(const unsigned char *input, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (i % 16 == 0)
			printf("  %04zu : ", i);
		printf("%02X ", (unsigned int) input[i]);
		i++;
		if (i % 16 == 0 || i == length)
			printf("\n");
	}
	if (length == 0)
		printf("  (chaine vide)\n");
}

static void	split_large_cases(t_test_result *result)
{
	const char	*labels[4] =
	{
		"Mot de 100000 caracteres",
		"100000 separateurs",
		"20000 petits mots",
		"Longues plages separateurs"
	};
	char	*input;
	size_t	i;
	size_t	length;
	size_t	words;
	int		test;
	int		ok;

	printf(BOLD CYAN "\n--- STRESS : GRANDES ENTREES ---\n" RESET);
	input = malloc(100001);
	if (!input)
	{
		memory_result(result, "Preparation grosses entrees", 0, 1);
		return ;
	}
	test = 0;
	while (test < 4)
	{
		length = 100000;
		if (test == 0)
			memset(input, 'A', length);
		else
			memset(input, ',', length);
		if (test == 2)
		{
			length = 40000;
			i = 0;
			while (i < length)
			{
				input[i] = 'A';
				input[i + 1] = ',';
				i += 2;
			}
		}
		if (test == 3)
		{
			input[25000] = 'A';
			input[75000] = 'B';
		}
		input[length] = '\0';
		words = split_expected_words(input, ',');
		printf("\n" BOLD "Stress %d/4 : %s\n" RESET,
			test + 1, labels[test]);
		printf("  Source            : %zu octets + terminateur\n", length);
		printf("  Separateur        : ',' (0x2C)\n");
		printf("  Mots attendus     : %zu\n", words);
		if (test == 0)
			printf("  Structure         : un mot de 100000 caracteres\n");
		else if (test == 1)
			printf("  Structure         : tableau contenant seulement NULL\n");
		else if (test == 2)
			printf("  Structure         : 20000 mots \"A\", puis NULL\n");
		else
			printf("  Structure         : deux mots \"A\" et \"B\", puis NULL\n");
		ok = run_split_case(input, ',');
		memory_result(result, labels[test], ok, 1);
		test++;
	}
	free(input);
}
/*
** Generateur deterministe : mêmes tests à chaque exécution.
** Les calculs unsigned sont volontairement modulaires.
*/

static unsigned int	split_random(unsigned int *state)
{
	*state = *state * 1664525u + 1013904223u;
	return (*state);
}

/*
** Teste des separateurs variés et des octets non ASCII.
** Les 5000 cas sont regroupés sur une ligne du bilan.
** Le premier cas en échec est identifié et affiché en hexadécimal.
*/

static void	split_generated_cases(t_test_result *result)
{
	const unsigned char	alphabet[] =
	{
		'A', 'B', '0', ' ', ',', '\t', '\n', 128, 255
	};
	const unsigned char	separators[] =
	{
		',', ' ', 'A', '\t', '\n', 128, 255, 0
	};
	unsigned int	state;
	unsigned char	input[257];
	unsigned char	separator;
	size_t			length;
	size_t			words;
	size_t			total_words;
	size_t			total_bytes;
	size_t			i;
	int				test;
	int				passed;

	printf(BOLD CYAN "\n--- STRESS : 5000 CAS GENERES ---\n" RESET);
	printf("  Graine            : 42 (reproductible)\n");
	printf("  Longueurs         : de 0 a 256 octets\n");
	printf("  Separateurs hex   : 2C 20 41 09 0A 80 FF 00\n");
	printf("  Controles         : mots, terminateurs, NULL final, source\n\n");
	state = 42;
	test = 0;
	passed = 0;
	total_words = 0;
	total_bytes = 0;
	while (test < 5000)
	{
		length = split_random(&state) % 257;
		separator = separators[split_random(&state)
			% sizeof(separators)];
		i = 0;
		while (i < length)
		{
			input[i] = alphabet[split_random(&state) % sizeof(alphabet)];
			i++;
		}
		input[length] = '\0';
		words = split_expected_words((char *) input, (char) separator);
		if (!run_split_case((char *) input, (char) separator))
		{
			printf(BOLD RED "\nEchec du cas genere #%d\n" RESET,
				test + 1);
			printf("  Longueur          : %zu octets\n", length);
			printf("  Separateur        : 0x%02X\n",
				(unsigned int) separator);
			printf("  Mots attendus     : %zu\n", words);
			printf("  Source en hexadecimal (sans terminateur) :\n");
			split_print_hex(input, length);
			break ;
		}
		passed++;
		total_words += words;
		total_bytes += length;
		test++;
		if (passed % 500 == 0)
		{
			printf("  Cas %4d a %4d : " BOLD "[" GREEN "OK"
				RESET	BOLD "]" RESET "\n", passed - 499, passed);
		}
	}
	printf("\n  Cas reussis       : %d/5000\n", passed);
	printf("  Octets traites    : %zu\n", total_bytes);
	printf("  Mots verifies     : %zu\n", total_words);
	memory_result(result, "Tests generes", passed, 5000);
}

static void split_allocation_case(t_test_result * result,
	const char	*input, char separator, int allocations)
{
	char	**words;
	char	label[64];
	int		fail_at;
	int		calls;

	fail_at = 1;
	while (fail_at <= allocations)
	{
		printf("\n  Allocation %d/%d forcee en echec : ",
			fail_at, allocations);
		if (fail_at == 1)
			printf("tableau de pointeurs\n");
		else
			printf("mot numero %d\n", fail_at - 1);
		fflush(stdout);
		g_malloc_calls = 0;
		g_malloc_fail_at = fail_at;
		words = ft_split(input, separator);
		calls = g_malloc_calls;
		g_malloc_fail_at = 0;
		snprintf(label, sizeof(label), "Echec allocation %d", fail_at);
		memory_result(result, label, words == NULL, 1);
		memory_result(result, "Allocation cible atteinte", calls, fail_at);
		printf("  Appels malloc observes : %d\n", calls);
		if (words)
			destroy_split(words);
		fail_at++;
	}
}

/*
** Après tous les échecs, vérifie aussi que split fonctionne
** lorsque le dernier point d'échec est placé après ses allocations.
*/

static void	split_allocation_failures(t_test_result *result)
{
	char	**words;
	int		ok;
	int		calls;

	printf(BOLD CYAN
		"\n--- STRESS : ECHECS SUCCESSIFS DE MALLOC ---\n" RESET);
	printf("  Source : \"alpha,beta,gamma,delta,epsilon\"\n");
	printf("  Attendu : 1 tableau + 5 mots = 6 allocations\n");
	split_allocation_case(result,
		"alpha,beta,gamma,delta,epsilon", ',', 6);
	printf(BOLD CYAN "\n  Cas sans mot : chaine vide\n" RESET);
	split_allocation_case(result, "", ',', 1);
	printf(BOLD CYAN "\n  Cas sans mot : separateurs seuls\n" RESET);
	split_allocation_case(result, ",,,,,", ',', 1);
	printf(BOLD CYAN "\n  Separateur nul : un seul mot\n" RESET);
	split_allocation_case(result, "ABCDE", '\0', 2);
	printf(BOLD CYAN "\n  Retour au fonctionnement normal\n" RESET);
	g_malloc_calls = 0;
	g_malloc_fail_at = 7;
	words = ft_split("alpha,beta,gamma,delta,epsilon", ',');
	calls = g_malloc_calls;
	g_malloc_fail_at = 0;
	ok = verify_split("alpha,beta,gamma,delta,epsilon", ',', words);
	memory_result(result, "Succes apres les six malloc", ok, 1);
	printf("  Appels malloc observes : %d (attendu : 6)\n", calls);
	memory_result(result, "Nombre allocations normal", calls, 6);
	destroy_split(words);
}

static void	tests_split(t_test_result *result)
{
	result->name = "ft_split";
	result->passed = 0;
	result->total = 0;
	printf(BOLD CYAN
		"\n============================================================\n"
	"              SERIE 05 - SPLIT : STRESS TESTS\n"
	"============================================================\n" RESET);
	memory_header(result->name);
	split_fixed_cases(result);
	split_large_cases(result);
	split_generated_cases(result);
	split_allocation_failures(result);
}

/*
** État de contrôle des callbacks.
*/

static const char	*g_callback_source;
static size_t		g_callback_calls;
static int			g_callback_valid;

/*
** Transforme les minuscules et modifie un caractère sur deux.
** Le résultat dépend donc du caractère ET de son indice.
*/

static char	callback_expected(unsigned int index, char c)
{
	if (c >= 'a' && c <= 'z')
		c = c - ('a' - 'A');
	if (index % 2 != 0)
		c = '*';
	return (c);
}

static char	test_mapi_callback(unsigned int index, char c)
{
	if (index != g_callback_calls)
		g_callback_valid = 0;
	if (g_callback_calls >= strlen(g_callback_source))
		g_callback_valid = 0;
	else if (c != g_callback_source[g_callback_calls])
		g_callback_valid = 0;
	g_callback_calls++;
	return (callback_expected(index, c));
}

static void	test_iteri_callback(unsigned int index, char *c)
{
	if (index != g_callback_calls)
		g_callback_valid = 0;
	if (g_callback_calls >= strlen(g_callback_source))
		g_callback_valid = 0;
	else if (*c != g_callback_source[g_callback_calls])
		g_callback_valid = 0;
	g_callback_calls++;
	*c = callback_expected(index, *c);
}

static void	test_strmapi(t_test_result *result)
{
	const char	*inputs[8] =
	{
		"", "a", "ab", "abcde", "ABCDEF",
		"a b\tc", "\200a\377b", "ab\0cd"
	};
	const char	*labels[8] =
	{
		"Chaine vide", "Un caractere", "Deux caracteres",
		"Longueur impaire", "Longueur paire",
		"Espaces et controles", "Octets eleves",
		"Arret au premier zero"
	};
	char	source[32];
	char	expected[32];
	char	*obtained;
	size_t	length;
	size_t	j;
	int		ok;
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 8)
	{
		length = strlen(inputs[i]);
		memcpy(source, inputs[i], length + 1);
		j = 0;
		while (j < length)
		{
			expected[j] = callback_expected(j, inputs[i][j]);
			j++;
		}
		expected[length] = '\0';
		g_callback_source = inputs[i];
		g_callback_calls = 0;
		g_callback_valid = 1;
		obtained = ft_strmapi(source, test_mapi_callback);
		ok = (obtained != NULL);
		if (ok)
			ok = (obtained != source
			&& strcmp(obtained, expected) == 0);
		ok = (ok && g_callback_valid && g_callback_calls == length
			&& memcmp(source, inputs[i], length + 1) == 0);
		memory_result(result, labels[i], ok, 1);
		free(obtained);
		i++;
	}
}

/*
** Vérifie aussi que strmapi peut produire des octets nuls
** sans arrêter les appels suivants.
*/

static char	test_zero_callback(unsigned int index, char c)
{
	(void) c;
	if (index != g_callback_calls)
		g_callback_valid = 0;
	g_callback_calls++;
	return ('\0');
}

static void	test_strmapi_extra(t_test_result *result)
{
	char	*obtained;
	int		ok;
	size_t	i;

	g_callback_source = "ABCDE";
	g_callback_calls = 0;
	g_callback_valid = 1;
	g_malloc_fail_at = 0;
	obtained = ft_strmapi("ABCDE", test_zero_callback);
	ok = (obtained != NULL);
	if (obtained)
	{
		i = 0;
		while (i < 6)
		{
			if (obtained[i] != '\0')
				ok = 0;
			i++;
		}
	}
	memory_result(result, "Callback produisant des zeros",
		ok && g_callback_valid && g_callback_calls == 5, 1);
	free(obtained);
	g_callback_source = "ABCDE";
	g_callback_calls = 0;
	g_callback_valid = 1;
	g_malloc_calls = 0;
	g_malloc_fail_at = 1;
	obtained = ft_strmapi("ABCDE", test_mapi_callback);
	g_malloc_fail_at = 0;
	memory_result(result, "Echec allocation", obtained == NULL && g_malloc_calls == 1, 1);
	free(obtained);
}

static void	test_striteri(t_test_result *result)
{
	const char	*inputs[8] =
	{
		"", "a", "ab", "abcde", "ABCDEF",
		"a b\tc", "\200a\377b", "ab\0cd"
	};
	const char	*labels[8] =
	{
		"Chaine vide", "Un caractere", "Deux caracteres",
		"Longueur impaire", "Longueur paire",
		"Espaces et controles", "Octets eleves",
		"Arret au premier zero"
	};
	char	buffer[34];
	char	expected[34];
	size_t	length;
	size_t	j;
	int		ok;
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 8)
	{
		length = strlen(inputs[i]);
		memset(buffer, 0x55, sizeof(buffer));
		memcpy(buffer + 1, inputs[i], length + 1);
		memcpy(expected, buffer, sizeof(expected));
		j = 0;
		while (j < length)
		{
			expected[j + 1] = callback_expected(j, inputs[i][j]);
			j++;
		}
		g_callback_source = inputs[i];
		g_callback_calls = 0;
		g_callback_valid = 1;
		ft_striteri(buffer + 1, test_iteri_callback);
		ok = (memcmp(buffer, expected, sizeof(buffer)) == 0
			&& g_callback_valid && g_callback_calls == length);
		memory_result(result, labels[i], ok, 1);
		i++;
	}
}

static void	tests_callbacks(t_test_result results[2])
{
	results[0].name = "ft_strmapi";
	results[0].passed = 0;
	results[0].total = 0;
	results[1].name = "ft_striteri";
	results[1].passed = 0;
	results[1].total = 0;
	printf(BOLD CYAN
		"\n============================================================\n"
	"             SERIE 06 - CALLBACKS SUR CHAINES\n"
	"============================================================\n" RESET);
	test_strmapi(&results[0]);
	test_strmapi_extra(&results[0]);
	test_striteri(&results[1]);
}

/*
** Sélection de la fonction à tester.
*/

enum e_fd_test
{
	FD_CHAR,
	FD_STRING,
	FD_LINE,
	FD_NUMBER
};

/*
** Capture et comparaison de la sortie.
** Les cas ci-dessous produisent tous moins de 256 octets.
*/

static int check_fd_output(int kind, const char * text, int value,
	const void	*expected, size_t expected_size)
{
	FILE			*file;
	unsigned char	buffer[256];
	size_t			total;
	ssize_t			bytes;
	int				fd;
	int				ok;

	file = tmpfile();
	if (!file)
	{
		perror("tmpfile");
		return (0);
	}
	fd = fileno(file);
	if (kind == FD_CHAR)
		ft_putchar_fd((char) value, fd);
	else if (kind == FD_STRING)
		ft_putstr_fd((char *) text, fd);
	else if (kind == FD_LINE)
		ft_putendl_fd((char *) text, fd);
	else
		ft_putnbr_fd(value, fd);
	if (lseek(fd, 0, SEEK_SET) == -1)
	{
		perror("lseek");
		fclose(file);
		return (0);
	}
	total = 0;
	ok = 1;
	while (total < sizeof(buffer))
	{
		bytes = read(fd, buffer + total, sizeof(buffer) - total);
		if (bytes < 0 && errno == EINTR)
			continue ;
		if (bytes < 0)
			ok = 0;
		if (bytes <= 0)
			break ;
		total += (size_t) bytes;
	}
	ok = (ok && total == expected_size);
	if (ok)
		ok = (memcmp(buffer, expected, expected_size) == 0);
	if (!ok)
	{
		printf("  Octets attendus : %zu ; obtenus : %zu\n",
			expected_size, total);
		printf("  Obtenu en hex : ");
		for (size_t j = 0; j < total; j++)
			printf("%02X ", (unsigned int) buffer[j]);
		printf("\n  Attendu en hex : ");
		for (size_t j = 0; j < expected_size; j++)
			printf("%02X ", (unsigned int)((const unsigned char *) expected)[j]);
		printf("\n");
	}
	if (fclose(file) != 0)
		ok = 0;
	return (ok);
}

static void	test_putchar_fd(t_test_result *result)
{
	const unsigned char	values[10] =
	{
		'A', 'z', '0', ' ', '\n', '\t', 0, 127, 128, 255
	};
	const char	*labels[10] =
	{
		"Majuscule", "Minuscule", "Chiffre", "Espace",
		"Saut de ligne", "Tabulation", "Octet nul",
		"Octet 127", "Octet 128", "Octet 255"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		memory_result(result, labels[i],
			check_fd_output(FD_CHAR, NULL, values[i], &values[i], 1), 1);
		i++;
	}
}

static void	test_putstr_fd(t_test_result *result)
{
	const char	*inputs[10] =
	{
		"", "A", "Hello world", " ", "     ",
		"\n", "\tABC\n", "AB\0CD", "\200\377",
		"abcdefghijklmnopqrstuvwxyz0123456789"
	};
	const char	*labels[10] =
	{
		"Chaine vide", "Un caractere", "Phrase", "Un espace",
		"Plusieurs espaces", "Saut de ligne", "Controles",
		"Arret au premier zero", "Octets eleves", "Chaine longue"
	};
	int	i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		memory_result(result, labels[i],
			check_fd_output(FD_STRING, inputs[i], 0,
			inputs[i], strlen(inputs[i])), 1);
		i++;
	}
}

static void	test_putendl_fd(t_test_result *result)
{
	const char	*inputs[10] =
	{
		"", "A", "Hello world", " ", "     ",
		"\n", "ABC\n", "AB\0CD", "\200\377", "ABCDEF"
	};
	const char	*labels[10] =
	{
		"Vide devient saut de ligne", "Un caractere", "Phrase",
		"Un espace", "Plusieurs espaces", "Deux sauts de ligne",
		"Saut deja present", "Arret au premier zero",
		"Octets eleves", "Chaine normale"
	};
	char	expected[64];
	size_t	length;
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		length = strlen(inputs[i]);
		memcpy(expected, inputs[i], length);
		expected[length] = '\n';
		memory_result(result, labels[i],
			check_fd_output(FD_LINE, inputs[i], 0,
			expected, length + 1), 1);
		i++;
	}
}

static void	test_putnbr_fd(t_test_result *result)
{
	const int	values[10] =
	{
		0, 1, -1, 9, 10, -10, 100, -100, INT_MAX, INT_MIN
	};
	char	expected[32];
	char	label[48];
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 10)
	{
		snprintf(expected, sizeof(expected), "%d", values[i]);
		snprintf(label, sizeof(label), "Ecriture de %d", values[i]);
		memory_result(result, label,
			check_fd_output(FD_NUMBER, NULL, values[i],
			expected, strlen(expected)), 1);
		i++;
	}
}

static void	tests_fd(t_test_result results[4])
{
	const char	*names[4] =
	{
		"ft_putchar_fd", "ft_putstr_fd", "ft_putendl_fd", "ft_putnbr_fd"
	};
	int	i;

	printf(BOLD CYAN
		"\n============================================================\n"
	"             SERIE 07 - SORTIES SUR DESCRIPTEUR\n"
	"============================================================\n" RESET);
	i = 0;
	while (i < 4)
	{
		results[i].name = names[i];
		results[i].passed = 0;
		results[i].total = 0;
		i++;
	}
	test_putchar_fd(&results[0]);
	test_putstr_fd(&results[1]);
	test_putendl_fd(&results[2]);
	test_putnbr_fd(&results[3]);
}

/*
** Outils indépendants des fonctions de listes à tester.
*/

static int	g_list_deleted;
static int	g_list_visited;

static void	list_delete_content(void *content)
{
	g_list_deleted++;
	free(content);
}

static void	list_increment(void *content)
{
	g_list_visited++;
	if (content)
		(*(int *) content)++;
}

static void	*list_double(void *content)
{
	int	*copy;

	copy = malloc(sizeof(int));
	if (!copy)
		return (NULL);
	*copy = *(int *) content * 2;
	return (copy);
}

/*
** Construction indépendante de ft_lstnew et ft_lstadd_back.
*/

static void	list_destroy_reference(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

static t_list	*list_build_reference(int count)
{
	t_list	*head;
	t_list	**tail;
	t_list	*node;
	int		i;

	head = NULL;
	tail = &head;
	i = 0;
	while (i < count)
	{
		node = malloc(sizeof(t_list));
		if (!node)
		{
			list_destroy_reference(head);
			return (NULL);
		}
		node->content = malloc(sizeof(int));
		if (!node->content)
		{
			free(node);
			list_destroy_reference(head);
			return (NULL);
		}
		*(int *) node->content = i + 1;
		node->next = NULL;
		*tail = node;
		tail = &node->next;
		i++;
	}
	return (head);
}

static void	test_lstnew(t_test_result *result)
{
	t_list	*node;
	int		value;

	memory_header(result->name);
	value = 42;
	node = ft_lstnew(&value);
	memory_result(result, "Contenu et next",
		node && node->content == &value && node->next == NULL, 1);
	free(node);
	node = ft_lstnew(NULL);
	memory_result(result, "Contenu NULL",
		node && node->content == NULL && node->next == NULL, 1);
	free(node);
	g_malloc_calls = 0;
	g_malloc_fail_at = 1;
	node = ft_lstnew(&value);
	g_malloc_fail_at = 0;
	memory_result(result, "Echec allocation", node == NULL, 1);
	free(node);
}

static void	test_lstadd_front(t_test_result *result)
{
	t_list	first;
	t_list	second;
	t_list	*head;

	memory_header(result->name);
	first.content = NULL;
	first.next = NULL;
	second.content = NULL;
	second.next = NULL;
	head = NULL;
	ft_lstadd_front(&head, &first);
	memory_result(result, "Ajout dans liste vide",
		head == &first && first.next == NULL, 1);
	ft_lstadd_front(&head, &second);
	memory_result(result, "Nouvelle tete et liens",
		head == &second && second.next == &first
	&& first.next == NULL, 1);
}

static void	test_lstsize(t_test_result *result)
{
	t_list	nodes[3];

	memory_header(result->name);
	nodes[0].content = NULL;
	nodes[1].content = NULL;
	nodes[2].content = NULL;
	nodes[0].next = NULL;
	nodes[1].next = &nodes[2];
	nodes[2].next = NULL;
	memory_result(result, "Liste vide", ft_lstsize(NULL), 0);
	memory_result(result, "Un maillon", ft_lstsize(&nodes[0]), 1);
	nodes[0].next = &nodes[1];
	memory_result(result, "Trois contenus NULL",
		ft_lstsize(&nodes[0]), 3);
}

static void	test_lstlast(t_test_result *result)
{
	t_list	nodes[3];

	memory_header(result->name);
	nodes[0].content = NULL;
	nodes[1].content = NULL;
	nodes[2].content = NULL;
	nodes[0].next = NULL;
	nodes[1].next = &nodes[2];
	nodes[2].next = NULL;
	memory_result(result, "Liste vide", ft_lstlast(NULL) == NULL, 1);
	memory_result(result, "Un maillon",
		ft_lstlast(&nodes[0]) == &nodes[0], 1);
	nodes[0].next = &nodes[1];
	memory_result(result, "Dernier de trois maillons",
		ft_lstlast(&nodes[0]) == &nodes[2], 1);
	memory_result(result, "Liens conserves",
		nodes[0].next == &nodes[1]
	&& nodes[1].next == &nodes[2] && nodes[2].next == NULL, 1);
}

static void	test_lstadd_back(t_test_result *result)
{
	t_list	nodes[3];
	t_list	*head;
	int		i;

	memory_header(result->name);
	i = 0;
	while (i < 3)
	{
		nodes[i].content = NULL;
		nodes[i].next = NULL;
		i++;
	}
	head = NULL;
	ft_lstadd_back(&head, &nodes[0]);
	memory_result(result, "Ajout dans liste vide",
		head == &nodes[0] && nodes[0].next == NULL, 1);
	ft_lstadd_back(&head, &nodes[1]);
	memory_result(result, "Ajout deuxieme maillon",
		head == &nodes[0] && nodes[0].next == &nodes[1]
	&& nodes[1].next == NULL, 1);
	ft_lstadd_back(&head, &nodes[2]);
	memory_result(result, "Ajout troisieme maillon",
		head == &nodes[0] && nodes[0].next == &nodes[1]
	&& nodes[1].next == &nodes[2] && nodes[2].next == NULL, 1);
}

static void	test_lstdelone(t_test_result *result)
{
	t_list	*head;
	t_list	*remaining;

	memory_header(result->name);
	head = list_build_reference(3);
	if (!head)
	{
		memory_result(result, "Preparation liste", 0, 1);
		return ;
	}
	remaining = head->next;
	g_list_deleted = 0;
	ft_lstdelone(head, list_delete_content);
	memory_result(result, "Un seul appel de del", g_list_deleted, 1);
	memory_result(result, "Maillons suivants conserves",
		*(int *) remaining->content == 2
	&& remaining->next != NULL
	&& *(int *) remaining->next->content == 3
	&& remaining->next->next == NULL, 1);
	list_destroy_reference(remaining);
}

/*
** Le contenu NULL est valide. Le callback sait le traiter.
*/

static void	test_lstclear(t_test_result *result)
{
	t_list	*head;

	memory_header(result->name);
	head = NULL;
	g_list_deleted = 0;
	ft_lstclear(&head, list_delete_content);
	memory_result(result, "Liste vide",
		head == NULL && g_list_deleted == 0, 1);
	head = list_build_reference(1);
	if (!head)
	{
		memory_result(result, "Preparation un maillon", 0, 1);
		return ;
	}
	g_list_deleted = 0;
	ft_lstclear(&head, list_delete_content);
	memory_result(result, "Un maillon libere",
		head == NULL && g_list_deleted == 1, 1);
	head = list_build_reference(3);
	if (!head)
	{
		memory_result(result, "Preparation trois maillons", 0, 1);
		return ;
	}
	free(head->next->content);
	head->next->content = NULL;
	g_list_deleted = 0;
	ft_lstclear(&head, list_delete_content);
	memory_result(result, "Trois maillons dont NULL",
		head == NULL && g_list_deleted == 3, 1);
	ft_lstclear(&head, list_delete_content);
	memory_result(result, "Deuxieme clear sans effet",
		head == NULL && g_list_deleted == 3, 1);
}

static void	test_lstiter(t_test_result *result)
{
	t_list	*head;
	t_list	*second;
	t_list	*third;

	memory_header(result->name);
	g_list_visited = 0;
	ft_lstiter(NULL, list_increment);
	memory_result(result, "Liste vide sans appel", g_list_visited, 0);
	head = list_build_reference(3);
	if (!head)
	{
		memory_result(result, "Preparation liste", 0, 1);
		return ;
	}
	second = head->next;
	third = second->next;
	g_list_visited = 0;
	ft_lstiter(head, list_increment);
	memory_result(result, "Un appel par maillon", g_list_visited, 3);
	memory_result(result, "Contenus transformes",
		*(int *) head->content == 2
	&& *(int *) second->content == 3
	&& *(int *) third->content == 4, 1);
	memory_result(result, "Liens conserves",
		head->next == second && second->next == third
	&& third->next == NULL, 1);
	list_destroy_reference(head);
}

/*
** Vérifie le résultat de map et l'indépendance des allocations.
*/

static int	list_check_map(t_list *source, t_list *mapped)
{
	t_list	*node;
	t_list	*other;
	int		expected;

	expected = 1;
	node = mapped;
	while (source && node)
	{
		if (!source->content || !node->content)
			return (0);
		if (*(int *) source->content != expected
				|| *(int *) node->content != expected * 2)
		return (0);
		other = mapped;
		while (other)
		{
			if (other == source || other->content == source->content)
				return (0);
			other = other->next;
		}
		source = source->next;
		node = node->next;
		expected++;
	}
	return (source == NULL && node == NULL && expected == 4);
}

/*
** Avec notre callback, chaque élément demande deux allocations :
** une pour le contenu transformé, une pour le nouveau maillon.
**
** On force l'échec des allocations de maillons : 2, 4 et 6.
** Le callback a alors réussi, et lstmap doit nettoyer son contenu.
*/

static void	test_lstmap(t_test_result *result)
{
	t_list	*source;
	t_list	*mapped;
	char	label[64];
	int		fail_at;
	int		calls;

	memory_header(result->name);
	mapped = ft_lstmap(NULL, list_double, list_delete_content);
	memory_result(result, "Liste vide", mapped == NULL, 1);
	list_destroy_reference(mapped);
	source = list_build_reference(3);
	if (!source)
	{
		memory_result(result, "Preparation liste", 0, 1);
		return ;
	}
	mapped = ft_lstmap(source, list_double, list_delete_content);
	memory_result(result, "Transformation et independance",
		list_check_map(source, mapped), 1);
	list_destroy_reference(mapped);
	fail_at = 2;
	while (fail_at <= 6)
	{
		g_list_deleted = 0;
		g_malloc_calls = 0;
		g_malloc_fail_at = fail_at;
		mapped = ft_lstmap(source, list_double, list_delete_content);
		calls = g_malloc_calls;
		g_malloc_fail_at = 0;
		snprintf(label, sizeof(label), "Echec maillon numero %d",
			fail_at / 2);
		memory_result(result, label, mapped == NULL, 1);
		snprintf(label, sizeof(label), "Nettoyage de %d contenus",
			fail_at / 2);
		memory_result(result, label, g_list_deleted, fail_at / 2);
		memory_result(result, "Arret apres echec", calls, fail_at);
		list_destroy_reference(mapped);
		fail_at += 2;
	}
	memory_result(result, "Source toujours intacte",
		*(int *) source->content == 1
	&& *(int *) source->next->content == 2
	&& *(int *) source->next->next->content == 3
	&& source->next->next->next == NULL, 1);
	list_destroy_reference(source);
}

static void	tests_lists(t_test_result results[9])
{
	const char	*names[9] =
	{
		"ft_lstnew", "ft_lstadd_front", "ft_lstsize",
		"ft_lstlast", "ft_lstadd_back", "ft_lstdelone",
		"ft_lstclear", "ft_lstiter", "ft_lstmap"
	};
	int	i;

	printf(BOLD CYAN
		"\n============================================================\n"
	"             SERIE 08 - LISTES CHAINEES BONUS\n"
	"============================================================\n" RESET);
	i = 0;
	while (i < 9)
	{
		results[i].name = names[i];
		results[i].passed = 0;
		results[i].total = 0;
		i++;
	}
	test_lstnew(&results[0]);
	test_lstadd_front(&results[1]);
	test_lstsize(&results[2]);
	test_lstlast(&results[3]);
	test_lstadd_back(&results[4]);
	test_lstdelone(&results[5]);
	test_lstclear(&results[6]);
	test_lstiter(&results[7]);
	test_lstmap(&results[8]);
}

/*
** Zones exactement dimensionnées.
** Valgrind détectera les lectures/écritures après leur fin.
*/

static void	test_exact_memory(t_test_result results[43])
{
	unsigned char	*source;
	unsigned char	*destination;
	unsigned char	*other;
	unsigned char	expected[4];
	void			*ret;

	printf(BOLD CYAN
		"\n--- CONTROLES MEMOIRE : BUFFERS EXACTS ---\n" RESET);
	source = malloc(4);
	destination = malloc(4);
	other = malloc(4);
	if (!source || !destination || !other)
	{
		memory_result(&results[9], "Preparation buffers exacts", 0, 1);
		free(source);
		free(destination);
		free(other);
		return ;
	}
	memcpy(source, "ABCD", 4);
	memset(destination, 0xAA, 4);
	ret = ft_memset(destination, 'X', 4);
	memory_result(&results[7], "Buffer exact : memset",
		ret == destination && memcmp(destination, "XXXX", 4) == 0, 1);
	ft_bzero(destination, 4);
	memset(expected, 0, 4);
	memory_result(&results[8], "Buffer exact : bzero",
		memcmp(destination, expected, 4) == 0, 1);
	ret = ft_memcpy(destination, source, 4);
	memory_result(&results[9], "Buffer exact : memcpy",
		ret == destination && memcmp(destination, source, 4) == 0, 1);
	memset(destination, 0xAA, 4);
	ret = ft_memmove(destination, source, 4);
	memory_result(&results[10], "Buffer exact : memmove",
		ret == destination && memcmp(destination, source, 4) == 0, 1);
	memcpy(destination, "ABCD", 4);
	ret = ft_memmove(destination + 1, destination, 3);
	memory_result(&results[10], "Chevauchement : fin exacte",
		ret == destination + 1
	&& memcmp(destination, "AABC", 4) == 0, 1);
	memory_result(&results[11], "Buffer exact : octet absent",
		ft_memchr(source, 'Z', 4) == NULL, 1);
	memory_result(&results[11], "Buffer exact : dernier octet",
		ft_memchr(source, 'D', 4) == source + 3, 1);
	memcpy(other, source, 4);
	memory_result(&results[12], "Buffer exact : egalite",
		ft_memcmp(source, other, 4), 0);
	other[3] = 'E';
	memory_result(&results[12], "Buffer exact : difference",
		number_sign(ft_memcmp(source, other, 4)), -1);
	free(source);
	free(destination);
	free(other);
}

/*
** Chaînes et destinations exactement dimensionnées.
*/

static void	test_exact_strings(t_test_result results[43])
{
	char	*source;
	char	*other;
	char	*destination;
	size_t	ret;

	printf(BOLD CYAN
		"\n--- CONTROLES CHAINES : BUFFERS EXACTS ---\n" RESET);
	source = malloc(4);
	other = malloc(4);
	destination = malloc(4);
	if (!source || !other || !destination)
	{
		memory_result(&results[13], "Preparation chaines exactes", 0, 1);
		free(source);
		free(other);
		free(destination);
		return ;
	}
	memcpy(source, "ABC", 4);
	memory_result(&results[13], "Terminaison en fin de bloc",
		ft_strlen(source) == 3, 1);
	memory_result(&results[14], "Recherche absente / fin bloc",
		ft_strchr(source, 'Z') == NULL, 1);
	memory_result(&results[15], "Recherche inverse / fin bloc",
		ft_strrchr(source, 0) == source + 3, 1);
	memory_result(&results[16], "Arret au zero / n tres grand",
		ft_strncmp(source, source, SIZE_MAX), 0);
	memcpy(other, "ABCD", 4);
	memory_result(&results[16], "Sans zero dans les n octets",
		ft_strncmp(other, other, 4), 0);
	memset(destination, 0x55, 4);
	ret = ft_strlcpy(destination, source, 4);
	memory_result(&results[17], "Copie dans allocation exacte",
		ret == 3 && memcmp(destination, "ABC", 4) == 0, 1);
	memcpy(destination, "ABCD", 4);
	ret = ft_strlcat(destination, source, 4);
	memory_result(&results[18], "Destination sans terminateur",
		ret == 7 && memcmp(destination, "ABCD", 4) == 0, 1);
	memcpy(destination, "A", 2);
	ret = ft_strlcat(destination, source, 4);
	memory_result(&results[18], "Concatenation / fin exacte",
		ret == 4 && memcmp(destination, "AAB", 4) == 0, 1);
	memory_result(&results[19], "Recherche au dernier caractere",
		ft_strnstr(source, "C", 3) == source + 2, 1);
	memory_result(&results[19], "Aiguille plus longue",
		ft_strnstr(source, "ABCD", SIZE_MAX) == NULL, 1);
	free(source);
	free(other);
	free(destination);
}

/*
** Chaque fonction testée ci-dessous réalise une seule allocation
** dans les versions habituelles de ta Libft.
*/

static void	test_extra_malloc_failures(t_test_result results[43])
{
	const char	*labels[6] =
	{
		"calloc : echec malloc", "strdup : echec malloc",
		"substr : echec malloc", "strjoin : echec malloc",
		"strtrim : echec malloc", "itoa : echec malloc"
	};
	void	*obtained;
	int		calls;
	int		i;

	printf(BOLD CYAN
		"\n--- ALLOCATIONS : ECHECS DE MALLOC ---\n" RESET);
	i = 0;
	while (i < 6)
	{
		g_malloc_calls = 0;
		g_malloc_fail_at = 1;
		if (i == 0)
			obtained = ft_calloc(4, sizeof(int));
		else if (i == 1)
			obtained = ft_strdup("ABC");
		else if (i == 2)
			obtained = ft_substr("ABCDE", 1, 3);
		else if (i == 3)
			obtained = ft_strjoin("AB", "CD");
		else if (i == 4)
			obtained = ft_strtrim("  ABC  ", " ");
		else
			obtained = ft_itoa(INT_MIN);
		calls = g_malloc_calls;
		g_malloc_fail_at = 0;
		memory_result(&results[21 + i], labels[i],
			obtained == NULL && calls == 1, 1);
		free(obtained);
		i++;
	}
}

/*
** Écrire des zéros ne doit pas empêcher les appels suivants.
** Vérifie aussi l'adresse exacte reçue par le callback.
*/

static char	*g_iteri_buffer;

static void	iteri_zero_callback(unsigned int index, char *character)
{
	if (index != g_callback_calls)
		g_callback_valid = 0;
	if (g_callback_calls >= 5)
		g_callback_valid = 0;
	else if (character != g_iteri_buffer + g_callback_calls)
		g_callback_valid = 0;
	g_callback_calls++;
	*character = '\0';
}

static void	test_striteri_zero(t_test_result *result)
{
	char	buffer[8];
	char	expected[8];

	printf(BOLD CYAN
		"\n--- STRITERI : CALLBACK ECRIVANT DES ZEROS ---\n" RESET);
	memcpy(buffer, "#ABCDE\0#", sizeof(buffer));
	memcpy(expected, buffer, sizeof(expected));
	memset(expected + 1, 0, 5);
	g_iteri_buffer = buffer + 1;
	g_callback_calls = 0;
	g_callback_valid = 1;
	ft_striteri(buffer + 1, iteri_zero_callback);
	memory_result(result, "Cinq appels malgre les zeros",
		g_callback_calls == 5 && g_callback_valid, 1);
	memory_result(result, "Zeros et octets temoins",
		memcmp(buffer, expected, sizeof(buffer)) == 0, 1);
}

static size_t summary_section(const char * title,
	const t_test_result	*results, size_t count)
{
	size_t	i;
	size_t	ok;

	printf(BOLD CYAN "\n  %s\n" RESET, title);
	printf("------------------------------------------------------------\n");
	i = 0;
	ok = 0;
	while (i < count)
	{
		printf("  %-18s %2d/%2d tests    ",
			results[i].name, results[i].passed, results[i].total);
		if (results[i].total > 0
				&& results[i].passed == results[i].total)
		{
			printf(BOLD "[" GREEN "OK" RESET BOLD "]" RESET "\n");
			ok++;
		}
		else
			printf(BOLD "[" RED "FAIL" RESET BOLD "]" RESET "\n");
		i++;
	}
	return (ok);
}

static void	print_summary(const t_test_result results[43])
{
	size_t	ok;

	printf(BOLD CYAN
		"\n============================================================\n"
	"                       RESUME GENERAL\n"
	"============================================================\n" RESET);
	ok = summary_section("01 - ASCII ET CARACTERES", results, 7);
	ok += summary_section("02 - OPERATIONS MEMOIRE", results + 7, 6);
	ok += summary_section("03 - CHAINES DE CARACTERES", results + 13, 7);
	ok += summary_section("04 - ALLOCATIONS ET CONVERSIONS",
		results + 20, 7);
	ok += summary_section("05 - SPLIT : STRESS TESTS", results + 27, 1);
	ok += summary_section("06 - CALLBACKS SUR CHAINES", results + 28, 2);
	ok += summary_section("07 - SORTIES SUR DESCRIPTEUR", results + 30, 4);
	ok += summary_section("08 - LISTES CHAINEES BONUS", results + 34, 9);
	printf("\n============================================================\n");
	printf(BOLD "  Fonctions OK : %zu/43\n" RESET, ok);
	printf(BOLD "  Fonctions en echec : %zu/43\n" RESET, 43 - ok);
	printf("============================================================\n");
}

int	main(void)
{
	t_test_result	results[43];
	int				i;
	int				failed;

	tests_ascii(results);
	tests_memory(results + 7);
	tests_strings(results + 13);
	tests_allocations(results + 20);
	tests_split(&results[27]);
	tests_callbacks(results + 28);
	tests_fd(results + 30);
	tests_lists(results + 34);
	test_exact_memory(results);
	test_exact_strings(results);
	test_extra_malloc_failures(results);
	test_striteri_zero(&results[29]);
	print_summary(results);
	print_summary(results);
	i = 0;
	failed = 0;
	while (i < 43)
	{
		if (results[i].total == 0
				|| results[i].passed != results[i].total)
		failed = 1;
		i++;
	}
	return (failed);
}
