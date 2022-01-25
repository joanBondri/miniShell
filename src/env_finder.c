#include "minishell.h"

int is_valid_var(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (i != 0)
            if (((!ft_isalpha(str[i])) || (!ft_isdigit(str[i])))&& (str[i] != '_'))
                return (1);
        if (i == 0)
            if (!ft_isalpha(str[i]) && (str[i] != '_'))
                return (1);
        i++;
    }
    return (0);
}

int is_correct_export(char **env_val, char *tab_cell, char *str)
{
    if (!env_val || !tab_cell)
        return (1);
    if (is_valid_var(env_val[0]))
        return (1);
    if (!ft_strncmp(str, "=", ft_strlen(str)))
        return(1);
    return (0);
}

char    *find_env(char *var, t_data *data)
{
    int index;
    char *tmp;

    index = find_index_env(data, var);
    if (index == -1)
        return (NULL);
    tmp = data->env[index];
    tmp = tmp + (ft_strlen(var) + 1);
    return (ft_strdup(tmp));
    
}

int find_index_env(t_data *data, char *str)
{
    int i;

    i = 0;
    if (!data->env)
        return(-2);
    while (data->env[i])
    {
        if (strncmp(data->env[i], str, ft_strlen(str)))
        {
            return (i);
        }
        i++;
    }
    return (-1);
}

int change_val_var(t_data *data, char *str, int i)
{
    free(data->env[i]);
    data->env[i] = str;
    return (1);
}

int add_var_tab(t_data *data, char *str)
{
    int i;
    int o;
    char **tmp;

    o = 0;
    i = 0;
    while (data->env[i] != NULL)
        i++;
    tmp = malloc(sizeof(char *) * (i + 2));
    while (data->env[o] != NULL)
    {
        tmp[o] = ft_strdup(data->env[o]);
        if (!tmp[o])
        {
            free_tab(tmp);
            return (-1);
        }
        o++;
    }    
    tmp[o] = str;
    if (!tmp[o])
    {
        free_tab(tmp);
        return (-1);     
    }
    tmp[++o] = NULL;
    free_tab(data->env);
    data->env = tmp;
    return (1);
}

int put_val_tab(t_data *data, char *var, char *new)
{
    char *tmp;

    tmp = ft_strjoin3(var, "=", new);
    if (!tmp)
        return (-1);
    if (find_index_env(data, var) == -1)
    {
        if (add_var_tab(data, tmp) == -1)
            return (-1);
    }
    else
    {
        if (change_val_var(data, tmp, find_index_env(data, var)) == -1)
            return (-1);
    }
    return (0);
}