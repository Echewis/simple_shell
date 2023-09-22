#include "wem_karl.h"

/**
 * runShell - main shell loop
 * @info: information about the shell's state
 * @av: argument vector
 *
 * Return: 0 on success
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
 * findBuiltInCommand - finds a builtin command
 * @info: information about the shell's state
 *
 * Return: 0 for success
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
 * findExecutable - finds a command in PATH
 * @info: information about the shell's state
 *
 * Return: Nothing
 */
void findExecutable(info_t *info)
{
	char *envar, *path = NULL;
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

	envar = getEnvironVariable(info, "PATH=");
	path = findExecutablePath(info, envar, info->argv[0]);
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
 * executeCommand - run a command
 * @info: information about the shell's state
 *
 * Return: Nothings
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
