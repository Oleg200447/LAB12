#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"file.h"
#include"tree.h"

#define KB 1024

#define MEMORY_MISTAKE 1

#define SYMBOL "&\n\0"
#define SPACE " "


tree* loadInfoFromFile(FILE* file,tree* head)
{
	if (feof(file) == 1)
	{
		return NULL;
	}

	char* str = (char*)calloc(KB, sizeof(char));

	if (str == NULL)
		return NULL;
		
	fgets(str, KB, file);

	if (strcmp(str, SYMBOL) == 0)
	{
		return NULL;
	}

	head = (tree*)calloc(1, sizeof(tree));
	if (head == NULL)
	{
		return NULL;
		exit(MEMORY_MISTAKE);
	}

	head->data = str;
	head->left = NULL;
	head->right = NULL;

	head->left = loadInfoFromFile(file, head->left);
	head->right = loadInfoFromFile(file, head->right);

	return head;
}

void delateOldBase()
{
	errno_t err_file;
	const char new_name[] = "C:\\Users\\Oleg\\source\\repos\\LAB12\\LAB12\\Answers.txt";
	const char old_name[] = "C:\\Users\\Oleg\\source\\repos\\LAB12\\LAB12\\Answers2.txt";

	err_file = remove(new_name);
	if (err_file != 0)
	{
		printf("Error!");
		exit(err_file);
	}

	err_file = rename(old_name, new_name);

	if (err_file != 0)
	{
		printf("Error!");
		exit(err_file);
	}
}

void addLooggs(char* user_answer,char *user_name)
{
	FILE* loggs;
	errno_t err_file = fopen_s(&loggs, "Loggs.txt", "a+");

	if (err_file != 0)
	{
		printf("Cant open file");
		exit(err_file);
	}

	char* str_log = (char*)calloc(KB, sizeof(char));
	if (str_log != NULL)
	{
		time_t mytime = time(NULL);
		struct tm* now = localtime(&mytime);
		char str[15];
		strftime(str, sizeof(str), "%x", now);

		char data[] = "Data:";
		strcat_s(str_log,KB, data);
		strcat_s(str_log, KB, str);
		strcat_s(str_log, KB, SPACE);

		strftime(str, sizeof(str), "%X", now);

		char time[] = "Time:";
		strcat_s(str_log, KB, time);
		strcat_s(str_log, KB, str);
		strcat_s(str_log, KB, SPACE);

		strcat_s(str_log, KB, user_name);
		char answer[] = " says:";
		strcat_s(str_log, KB, answer);
		strcat_s(str_log,KB, user_answer);

		fputs(str_log, loggs);

		free(str_log);

		fclose(loggs);
	}
}