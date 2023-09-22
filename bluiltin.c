#include "wem_karl.h"

/**
 * exitCommand - exits the shell
 * @info: information about the shell's state
 * Return: 0 if success
 */
int exitCommand(info_t *info)
{
	int checker_exit;

	if (info->argv[1])
	{
		checker_exit = ErrorStringToInteger(info->argv[1]);
		if (checker_exit == -1)
		{
			info->status = 2;
			printErrorMessage(info, "Illegal number: ");
			printInputString(info->argv[1]);
			printChar('\n');
			return (1);
		}
		info->err_num = ErrorStringToInteger(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * changeDirectory - change the current working directory
 * @info: information about the shell's state
 *
 * Return: 0 always success
 */
int changeDirectory(info_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (cwd == NULL)
		putStr("TODO: >>getcwd failure emsg here<<\n");

	if (info->argv[1] == NULL)
	{
		dir = getEnvironVariable(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = getEnvironVariable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compareStr(info->argv[1], "-") == 0)
	{
		if (getEnvironVariable(info, "OLDPWD=") == NULL)
		{
			putStr(cwd);
			putChar('\n');
			return (1);
		}
		putStr(getEnvironVariable(info, "OLDPWD=")), putChar('\n');
		chdir_ret = chdir((dir = getEnvironVariable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printErrorMessage(info, "can't cd to ");
		printInputString(info->argv[1]), printChar('\n');
	}
	else
	{
		setEnvVariable(info, "OLDPWD", getEnvironVariable(info, "PWD="));
		setEnvVariable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help - help on the command type
 * @info: information about the shell's state
 * Return: 0 means that everything is ok
 */
int help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	putStr("help call works. Function not yet implemented \n");

	if (true)
		putStr(*arg_array);

	return (0);
}

