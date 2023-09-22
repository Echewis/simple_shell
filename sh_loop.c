#include "wem_karl.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int runShell(info_t *info, char **av)
{
	ssize_t bytes_read = 0;
	int built_command = 0;

	while (bytes_read != -1 && built_command != -2)
	{
		clearInfo(info);
		if (isInteractive(info))
			putStr("$ ");
		printChar(BUF_FLUSH);
		bytes_read = readInput(info);
		if (bytes_read != -1)
		{
			setInfo(info, av);
			built_command = findBuiltInCommand(info);
			if (built_command == -1)
				findExecutable(info);
		}
		else if (isInteractive(info))
			putChar('\n');
		freeInfo(info, 0);
	}
	writeHistoryToFile(info);
	freeInfo(info, 1);
	if (!isInteractive(info) && info->status)
		exit(info->status);
	if (built_command == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_command);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int findBuiltInCommand(info_t *info)
{
	int i, built_command = -1;
	builtin_table built_tab[] = {
		{"exit", exitCommand},
		{"env", EnvCommand},
		{"help", help},
		{"history", history},
		{"setenv", SetEnvCommand},
		{"unsetenv", UnsetEnvCommand},
		{"cd", changeDirectory},
		{"alias", alias},
		{NULL, NULL}
	};

	for (i = 0; built_tab[i].type; i++)
		if (compareStr(info->argv[0], built_tab[i].type) == 0)
		{
			info->line_count++;
			built_command = built_tab[i].func(info);
			break;
		}
	return (built_command);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findExecutable(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!isDelimiter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = findExecutablePath(info, getEnvironVariable(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		executeCommand(info);
	}
	else
	{
		if ((isInteractive(info) || getEnvironVariable(info, "PATH=")
					|| info->argv[0][0] == '/') && isCommandInPath(info, info->argv[0]))
			executeCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printErrorMessage(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void executeCommand(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnvList(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printErrorMessage(info, "Permission denied\n");
		}
	}
}
