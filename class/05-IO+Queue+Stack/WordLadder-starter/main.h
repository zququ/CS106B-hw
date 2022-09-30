#ifndef MAIN_H
#define MAIN_H

#include "console.h"
#include "filelib.h"
#include "queue.h"
#include "set.h"
#include "simpio.h"
#include "stack.h"
#include "strlib.h"
#include <iostream>

Set<std::string> dictionary; // not good style, don't follow it
Set<std::string> visitedWords(Stack<std::string> currentLadder);
Set<std::string> nextWords(std::string currentWord);

#endif // MAIN_H
