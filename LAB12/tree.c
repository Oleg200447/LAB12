#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"tree.h"
#include"file.h"

#define KB 1024

#define MEMORY_MISTAKE 1
#define CANT_OPEN_FILE 1

#define SYMBOL "&\n\0"

char* giveMemoryForUserName()
{
	char* user_name = (char*)calloc(KB, sizeof(char));
	return user_name;
}

void checkUserAnswer(char* symbol)
{
	while ((scanf_s("%c", symbol, 1)) != 1 || getchar() != '\n' || (*symbol!='Y' && *symbol != 'N'))
	{
		printf("(Y/N):");
		rewind(stdin);
	}
}

void getAnswer(tree* head,FILE* data_base,char *user_name)
{
	if (head->right == NULL || head->left==NULL)
	{
		printf("Answer:%s", head->data);

		checkForRightAnswer(data_base, head->data,user_name);

		return;
	}

	printf("%s(Y/N):", head->data);

	char user_answer;

	rewind(stdin);

	checkUserAnswer(&user_answer);

	char user_answer_str[3]={'\0'};

	user_answer_str[0] = user_answer;
	user_answer_str[1] = '\n';
	user_answer_str[2] = '\0';

	addLooggs(user_answer_str,user_name);

	if (user_answer == 'N')
	{
		getAnswer(head->left,data_base, user_name);
	}
	else if(user_answer=='Y')
	{
		getAnswer(head->right,data_base, user_name);
	}
}

void checkForRightAnswer(FILE * data_base,char *answer,char *user_name)
{
	char user_answer='\0';

	printf("\nIs it answer correct?(Y/N):");
	checkUserAnswer(&user_answer);

	char user_answer_str[3]={'\0'};

	user_answer_str[0] = user_answer;
	user_answer_str[1] = '\n';
	user_answer_str[2] = '\0';

	addLooggs(user_answer_str, user_name);
	
	if (user_answer == 'Y')
		return;
	else if(user_answer=='N')
	{
		char* right_answer = (char*)calloc(KB, sizeof(char));
		if (right_answer != NULL)
		{
			printf("Input right answer:");
			fgets(right_answer, KB, stdin);

			addLooggs(right_answer,user_name);
		}

		char* difference = (char*)calloc(KB, sizeof(char));
		if (difference != NULL)
		{
			prepareAnswersForQuestion(&answer, &right_answer);
			printf("\nWhats the difference between %s and %s?\n", answer, right_answer);
			fgets(difference, KB, stdin);

			addLooggs(difference,user_name);
		}
		prepareDifferenceForNewBase(&difference);
		prepareAnswerForNewBase(&right_answer);
		prepareAnswerForNewBase(&answer);

		
		makeNewDataBase(data_base, difference, right_answer, answer);

		free(right_answer);
		free(difference);
	}
				
}

void prepareAnswersForQuestion(char** program_answer, char** right_answer)
{
	int i = 0;
	while (*(*program_answer + i) != '\n')
	{
		i++;
	}
	*(*program_answer + i) = '\0';

	i = 0;
	while (*(*right_answer + i) != '\n')
	{
		i++;
	}
	*(*right_answer + i) = '\0';
}

void prepareDifferenceForNewBase(char** difference)
{
	int i = 0;

	while (*(*difference + i) != '\n')
	{
		i++;
	}
	*(*difference + i) = '?';

	i++;
	*(*difference + i) = '\n';

	i++;
	*(*difference + i) = '\0';
}

void prepareAnswerForNewBase(char** answer)
{
	int i = 0;

	while (*(*answer + i) != '\0')
	{
		i++;
	}

	*(*answer + i) = '\n';

	i++;
	*(*answer + i) = '\0';
}

void makeNewDataBase(FILE* data_base,char *difference,char * right_answer,char* answer)
{
	FILE* new_data_base;
	errno_t err_file = fopen_s(&new_data_base, "Answers2.txt", "w+");

	if (err_file != 0)
	{
		printf("Cant open file");
		exit(CANT_OPEN_FILE);
	}

	char* temp = (char*)calloc(KB, sizeof(char));

	rewind(data_base);
	while (!feof(data_base) && strcmp(fgets(temp, KB, data_base), answer) != 0)
	{
		fputs(temp, new_data_base);
	}

	fputs(difference,new_data_base);
	fputs(right_answer, new_data_base);
	for (int i = 0; i < 2; i++)
	{
		fputs(SYMBOL, new_data_base);
	}

	while (!feof(data_base))
	{
		fputs(temp, new_data_base);
		fgets(temp, KB, data_base);
	}
	fputs(temp, new_data_base);

	free(temp);

	fclose(new_data_base);
	fclose(data_base);
	
	delateOldBase();
}

void freeTree(tree** head)
{
	if ((*head)->right == NULL || (*head)->left == NULL)
	{
		free((*head)->data);
		free(*head);
		return;
	}

	freeTree(&(*head)->left);
	freeTree(&(*head)->right);	

	free((*head)->data);
	free(*head);
}