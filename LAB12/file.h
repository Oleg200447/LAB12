#pragma once

#include<stdio.h>

#include"tree.h"

tree* loadInfoFromFile(FILE* file, tree* head);

void delateOldBase();

void addLooggs(char* user_answer,char* user_name);