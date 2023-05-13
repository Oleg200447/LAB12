#pragma once
#include<stdio.h>

typedef struct TREE {
	char* data;
	struct TREE* right;
	struct TREE* left;
}tree;

void checkUserAnswer(char* symbol);

void checkForRightAnswer(FILE* data_base, char* answer,const char *user_name);

void prepareAnswersForQuestion(char** program_answer, char** right_answer);

void prepareDifferenceForNewBase(char** difference);

void prepareAnswerForNewBase(char** answer);

void makeNewDataBase(FILE* data_base, char* difference, char* right_answer, char* answer);

void getAnswer(tree* head,FILE* data_base,char* user_name);

void freeTree(tree** head);

char* giveMemoryForUserName();
