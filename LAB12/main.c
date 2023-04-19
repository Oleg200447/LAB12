#include<stdio.h>
#include<stdlib.h>

#include"tree.h"
#include"file.h"

#define KB 1024

int main()
{
	char flg = 'Y';

	char* user_name = giveMemoryForUserName();
	printf("Input your name:");
	scanf_s("%s", user_name,KB);
	
	do {

	tree* head = NULL;

	FILE* file;
	errno_t err_file = fopen_s(&file, "Answers.txt", "a+");
	if (err_file != 0)
	{
		printf("Cant open file");
		exit(err_file);
	}
		
	rewind(file);
	head = loadInfoFromFile(file, head);

	if (head == NULL)
	{
		return 0;
	}

	getAnswer(head, file,user_name);

	system("cls");

	printf("Do you want to try again?\n(Y/N):");
	checkUserAnswer(&flg);

	system("cls");

	freeTree(&head);

	fclose(file);

	} while (flg=='Y');

	free(user_name);

	return 0;
}
