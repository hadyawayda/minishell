/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:30:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/23 12:05:49 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


extern char **environ;

/* Validate identifier: [A-Za-z_] then [A-Za-z0-9_]* */
static int is_valid_id(const char *s)
{
    int i = 0;
    if (!ft_isalpha(s[0]) && s[0] != '_')
        return (0);
    i = 1;
    while (s[i])
    {
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

/* Compare two entries by key (up to '=' or end) */
static int cmp_key(const char *a, const char *b)
{
    while (*a && *a != '=' && *b && *b != '=' && *a == *b)
    {
        a++; b++;
    }
    unsigned char ca = (*a == '=' || *a == '\0') ? '\0' : (unsigned char)*a;
    unsigned char cb = (*b == '=' || *b == '\0') ? '\0' : (unsigned char)*b;
    return (ca - cb);
}

int process_export(char **args, char **envp)
{
    int    status = 0;
    int    idx;
    long   count;
    char **copy;
    int    swapped;

    (void)envp;

    /* 1) Process KEY[=VAL] arguments */
    idx = 1;
    while (args[idx])
    {
        char *arg = args[idx++];
        char *eq  = ft_strchr(arg, '=');
        char *key;
        char *val;

        if (eq)
        {
            size_t klen = (size_t)(eq - arg);
            key = malloc(klen + 1);
            if (!key)
                return (1);
            ft_strncpy(key, arg, klen);
            key[klen] = '\0';
            val = eq + 1;
        }
        else
        {
            key = ft_strdup(arg);
            val = "";
        }

        if (!is_valid_id(key))
        {
            write(2, "bash: export: `", 15);
            write(2, arg,            ft_strlen(arg));
            write(2, "`: not a valid identifier\n", 26);
            free(key);
            return (1);
        }

        setenv(key, val, 1);
        free(key);
    }

    /* 2) Copy global environ into an array */
    count = 0;
    while (environ[count])
        count++;
    copy = malloc((count + 1) * sizeof(char *));
    if (!copy)
        return (1);
    idx = 0;
    while (idx < count)
    {
        copy[idx] = environ[idx];
        idx++;
    }
    copy[count] = NULL;

    /* 3) Bubble‐sort copy[] by key, using manual swap */
    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        idx = 0;
        while (idx < count - 1)
        {
            if (cmp_key(copy[idx], copy[idx + 1]) > 0)
            {
                char *tmp = copy[idx];
                copy[idx] = copy[idx + 1];
                copy[idx + 1] = tmp;
                swapped = 1;
            }
            idx++;
        }
    }

    /* 4) Print sorted entries */
    idx = 0;
    while (idx < count)
    {
        char *e  = copy[idx];
        char *eq = ft_strchr(e, '=');
        size_t klen = eq ? (size_t)(eq - e) : ft_strlen(e);

        write(1, "export ", 7);
        if (eq && eq[1] != '\0')
        {
            write(1, e,       klen);
            write(1, "=\"",    2);
            write(1, eq + 1,  ft_strlen(eq + 1));
            write(1, "\"\n",  2);
        }
        else
        {
            write(1, e,     klen);
            write(1, "\n",  1);
        }
        idx++;
    }
    free(copy);
    return (status);
}
