/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:50:59 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/16 18:45:38 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_open_file_fds(char **argv, int files_fd[2])
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	files_fd[0] = open(argv[1], O_RDONLY);
	if (files_fd[0] == -1)
		perror("infile");
	files_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (files_fd[1] == -1)
		perror("outfile");
}


bool	ft_open_file_append_trunc(char *file_name)
{
	int	fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd == -1)
	{
		perror("outfile");
		return (false);
	}
	return (true);
}

void	ft_skip_single_quotes(char *cmd_line, int *i)
{
	char	quote;

	while (cmd_line[*i] && cmd_line[*i] == '\'')
	{
		quote = '\'';
		while (cmd_line[++(*i)] && cmd_line[*i] != quote)
			;
		if (cmd_line[*i] && cmd_line[*i] == quote)
			*i += 1;
	}
}

void ft_skip_whitespace(char *string, int *i)
{
	while (string[*i] && (string[*i] == ' '
		|| string[*i] == '\t' || string[*i] == '\n'))
		*i += 1;
}

char	*ft_trim_variable_value(char *string)
{
	int		i;
	int		j;
	int		start;
	int		count;
	char	*result;

	i = 0;
	count = 0;
	while (string[i])
	{
		start = i;
		ft_skip_whitespace(string, &i);
		if (string[i] && start > 0 && start != i)
			count++;
		if (string[i])
		{
			count++;
			i++;
		}
	}
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (result);
	i = 0;
	j = 0;
	while (string[i])
	{
		start = i;
		ft_skip_whitespace(string, &i);
		if (string[i] && start > 0 && start != i)
			result[j++] = ' ';
		if (string[i])
		{
			result[j++] = string[i];	
			i++;
		}
	}
	result[j] = '\0';
	// free(string);
	return (result);
}


//searches for the next delimiter
//and stops if it finds quotes or the end of the string.
void	ft_skip_to_next_non_delimiter_and_skip_quotes(char *string, int *i, bool skip_quote)
{
	if (string[*i] == '$')
		*i += 1;
	while (string[*i] && string[*i] != ' ' && string[*i] != '\t' && string[*i] != '\n' && string[*i] != '$'
		&& ((skip_quote == false && string[*i] != '\"') || skip_quote == true))
	{
		if (skip_quote && (string[*i] == '\"' || string[*i] == '\''))
			ft_skip_quote_block(string, i);
		*i += 1;
	}
}

char	*ft_get_variable_name(char *string, int *start, bool skip_quote)
{
	char	*variable_name;
	int		end;

	end = *start;
	if (string[end] == '$' && string[end + 1] == '?')
		end += 2;
	else if (string[end] == '$' && string[end + 1] == '\"')
		end += 1;
	else
		ft_skip_to_next_non_delimiter_and_skip_quotes(string, &end, skip_quote);
	variable_name = ft_substr(string, *start, end - *start);
	return (variable_name);
}

char	*ft_get_variable_value(char *variable_name)
{
	int	name_len;

	name_len = ft_strlen(variable_name);
	if (name_len == 1 && variable_name[0] == '$')
		return ("");
	else if (name_len == 2 && variable_name[0] == '$' && variable_name[1] == '?')
		return ("-EXIT_CODE-");
	return ("-ORIG_VALUE-");
}

char	*ft_handle_variable_replacement(char *string, int *i, bool trim, bool skip_quote)
{
	char	*variable_name;
	char	*variable_value;
	char	*before_variable;
	char	*after_variable;
	char	*result;
	char	*tmp;

	printf("i at start: %d\n", *i);
	printf("gettin variable name\n");
	variable_name = ft_get_variable_name(string, i, skip_quote);
	if (!variable_name)
		return (NULL);
	printf("variable name: %s\n", variable_name);
	printf("gettin variable value\n");
	variable_value = ft_get_variable_value(variable_name);
	if (!variable_value)
	{
		//cleanup
		return (NULL);
	}
	printf("variable value: %s\n", variable_value);
	if (trim)
		variable_value = ft_trim_variable_value("-TRIM_VALUE-");
	if (trim && !variable_value)
	{
		//cleanup
		return (NULL);
	}
	printf("trimed variable value: %s\n", variable_value);
	printf("i: %d\n", *i);
	if (*i > 0)
		before_variable = ft_substr(string, 0, *i);
	else
		before_variable = "";
	if (!before_variable)
	{
		//cleanup
		return (NULL);
	}
	printf("before variable: %s\n", before_variable);
	after_variable = string + *i + ft_strlen(variable_name);
	printf("after variable: %s\n", after_variable);
	tmp = ft_strjoin(before_variable, variable_value);
	if (!tmp)
	{
		//cleanup
		return (NULL);
	}
	printf("joined before variable and variable value: %s\n", tmp);
	result = ft_strjoin(tmp, after_variable);
	if (!result)
	{
		//cleanup
		return (NULL);
	}
	printf("joined before variable, variable value and after variable: %s\n", result);
	//set i to a value where it can continue
	//for now back to the start i = 0;
	*i += ft_strlen(variable_value);
	printf("reaplacing: %s -> %s\n", variable_name, variable_value);
	printf("replaced string: %s\n\n", result);
	return (result);
}


//how to handle the varibale expansion for rediretion:
//where to save if there is an "ambiguous redirect" error
//Maybe add a flag in the struct: ambiguous_redirect
//check if there is a space in an unquoted variable_value
//when does it occur?
//when there is a variable in the redirection
//and the variable is unquoted and contains a space
char	*ft_replace_variale_with_value(char *string)
{
	int		i;
	bool	double_quote;

	i = 0;
	double_quote = false;
	printf(BOLD_YELLOW "input string: %s\n\n" STYLE_DEF, string);
	while (string[i])
	{
		if (string[i] == '\"' && double_quote == false)
		{
			double_quote = true;
			i++;
		}
		else if (string[i] == '\"' && double_quote == true)
		{
			double_quote = false;
			i++;
		}
		if (string[i] == '\'' && double_quote == false)
			ft_skip_single_quotes(string, &i);
		if (string[i] == '$' && string[i + 1] == '?')
		{
			printf("found $? - replace with last exit code\n"); // fucnction -> replace_in_place, no trim
			string = ft_handle_variable_replacement(string, &i, false, true);
		}
		else if (string[i] == '$' && string[i + 1] == '\"' && double_quote == false)
		{
			printf("found $\" -- just remove the '$'\n"); // fucnction -> remove dollar sign
			string = ft_handle_variable_replacement(string, &i, false, true);
		}
		else if (string[i] == '$' && string[i + 1] && !(string[i + 1] == ' '
		|| string[i + 1] == '\t' || string[i + 1] == '\n') && double_quote == false)
		{
			//find the name of the variable
			printf("found $ - replace with variable value - trim spaces\n"); //ftunction -> replace_in_place, trim
			string = ft_handle_variable_replacement(string, &i, true, true);
		}
		else if (string[i] == '$' && string[i + 1] != '\"' && string[i + 1] != ' ' && string[i + 1] != '\t' && string[i + 1] != '\n'
				&& double_quote == true)
		{
			//find the name of the variable
			printf("found $ - replace with variable value, preserve spaces\n"); // fucnction -> replace_in_place, no trim
			string = ft_handle_variable_replacement(string, &i, false, false);
		}
		else
			i++;
	}
	return (string);
}

// bool	ft_expand_variable(t_tokens *token)
// {
// 	//search for single quotes - skip block
// 	//seachr for double quotes - expand variable preserve spaces
// 	//search for $? - expand variable in place - ignore the rest of the text after ?
// 	//search for $ - expand variable in place - trim spaces
// 	char	*string;
// 	int		i;
// 	bool	in_double_quote;
// 	bool	valid;

// 	in_double_quote = false;
// 	valid = true;
// 	string = token->token;
// 	i = 0;
// 	// while (string[i])
// 	// {
// 	// 	if (string[i] == '\'')
// 	// 		ft_skip_single_quotes(string, &i);
// 	// 	if (string[i] == '\"' && in_double_quote == false)
// 	// 		in_double_quote = true;
// 	// 	else
// 	// 		in_double_quote = false;
// 	// 	if (string[i] == '$' && in_double_quote == false)
// 	// 		valid = ft_expand_variable_in_place(string, &i);
// 	// 	else if (string[i] == '$' && in_double_quote == true)
// 	// 		valid = ft_expand_variable_preserve_spaces(string, &i);
// 	// 	else
// 	// 		i++;
// 	// }
// 	while (string[i])
// 	{
// 		if (string[i] == '$' && (string[i + 1] == '\'' || string[i + 1] == '\"'))
// 			ft_remoove_dollar_sign(string, &i);
// 			valid = ft_expand_variable_in_place(string, &i);
// 		else if (string[i] == '$')
// 			valid = ft_expand_variable_preserve_spaces(string, &i);
// 		else
// 			i++;
// 		i++;
// 	}
// 	return (valid);
// }

bool	ft_variable_expansion(t_data *data)
{

	t_tokens	*token;

	token = data->tokens;
	while (token)
	{
		if (token->token_type == enum_word)
		{
			// free(token->token);
			token->token = ft_replace_variale_with_value(token->token);
			if(!token->token)
				return (false);
			//removing quotes from tokens
			if (ft_remove_quotes_from_elements(token) == false)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	ft_handle_operators(t_data *data)
{
	if (ft_variable_expansion(data) == false)
		return (false);
	
	//1. expand variables - assume like this -> variable in and value out
	//2. here_doc
	//3. redirection

	return (true);
}


// int main(void)
// {
// 	char *test_string = "echo $HOME $USER $?";
// 	//result: echo -TRIM_VALUE- -TRIM_VALUE- -EXIT_CODE-
// 	char *test_string2 = "echo $HOME \"$PATH\"$? $\"hello\" $ ";
// 	//echo -TRIM_VALUE- "-ORIG_VALUE-"-EXIT_CODE- "hello" $
// 	char *test_string3 = "echo $HOME $USER $? $ $ ";
// 	//echo -TRIM_VALUE- -TRIM_VALUE- -EXIT_CODE- $ $
// 	char *test_string4 = "echo no_space:\"$\" with_space:\"$ \"";
// 	//echo no_space:"$" with_space:"$ "
// 	char *result;

// 	result = ft_replace_variale_with_value(test_string);
// 	printf(BOLD_YELLOW "before value: %s\n" STYLE_DEF, test_string);
// 	printf(BOLD_PINK "final result: %s\n" STYLE_DEF, result);
// 	printf("\n");
// 	result = ft_replace_variale_with_value(test_string2);
// 	printf(BOLD_YELLOW "before value: %s\n" STYLE_DEF, test_string2);
// 	printf(BOLD_PINK "final result: %s\n" STYLE_DEF, result);
// 	printf("\n");
// 	result = ft_replace_variale_with_value(test_string3);
// 	printf(BOLD_YELLOW "before value: %s\n" STYLE_DEF, test_string3);
// 	printf(BOLD_PINK "final result: %s\n" STYLE_DEF, result);
// 	printf("\n");
// 	result = ft_replace_variale_with_value(test_string4);
// 	printf(BOLD_YELLOW "before value: %s\n" STYLE_DEF, test_string4);
// 	printf(BOLD_PINK "final result: %s\n" STYLE_DEF, result);
// }