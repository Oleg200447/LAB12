#pragma once

#include<stdio.h>

#include"tree.h"

tree* loadInfoFromFile(FILE* file, tree* head);

void delateOldBase();

void addLooggs(const char* user_answer,const char* user_name);