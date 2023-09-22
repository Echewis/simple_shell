#include "wem_karl.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int exitCommand(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = ErrorStringToInteger(info->argv[1]);
		if (exitcheck == -1)
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
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int changeDirectory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		putStr("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getEnvironVariable(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = getEnvironVariable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compareStr(info->argv[1], "-") == 0)
	{
		if (!getEnvironVariable(info, "OLDPWD="))
		{
			putStr(s);
			putChar('\n');
			return (1);
		}
		putStr(getEnvironVariable(info, "OLDPWD=")), putChar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = getEnvironVariable(info, "OLDPWD=")) ? dir : "/");
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
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	putStr("help call works. Function not yet implemented \n");
	if (0)
		putStr(*arg_array); /* temp att_unused workaround */
	return (0);
}

