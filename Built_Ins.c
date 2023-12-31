#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Built In command that Print all of the Aliases or specific
 * alias, or sets a new set of  alias.
 * @args: argumments array.
 * @front: Double pointer beginning of 'args'.
 *
 * Description:a function that prints alias.
 * Return: If error occurs then return - -1.
 *         or - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int x, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (x = 0; args[x]; x++)
	{
		temp = aliases;
		value = _strchr(args[x], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[x], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + x, 1);
		}
		else
			set_alias(args[x], value);
	}
	return (ret);
}

/**
 * set_alias - Will set an already exist alias 'name' with new value,
 * Or create  new alias with a new 'name' and 'value'.
 * @var_name: alias name.
 * @value: alias value. First Character is '='.
 *
 * Description:a fucntion that will set a name with value.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int le, v, k;
	char *new_value;

	*value = '\0';
	value++;
	le = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (le + 1));
	if (!new_value)
		return;
	for (v = 0, k = 0; value[v]; v++)
	{
		if (value[v] != '\'' && value[v] != '"')
			new_value[k++] = value[v];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Print  alias in format name = value.
 * @alias: Pointer to one of the  alias.
 *
 * Description:a function that prints a alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int le = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (le + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, le);
	free(alias_string);
}
/**
 * replace_aliases - Go through every argument then replace matching alias
 * with the assigned values.
 * @args:two-dimensional pointer to arguments.
 *
 * Description: a replace fucntion
 * Return: two-dimensional pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int v;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (v = 0; args[v]; v++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[v], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[v]);
				args[v] = new_value;
				v--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
