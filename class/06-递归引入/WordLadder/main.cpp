/**
 * 词梯（Word Ladder）是刘易斯·卡罗尔发明的一种单词游戏。
 * 游戏会给出一个开始单词和结束单词。
 * 玩家需要更改开始单词中的某个字母，获得一个新词，计作一步。
 * 然后玩家需要再次更改所得新词中的某个字母，获得另一个新词。
 * 最终获得结束单词，游戏结束。
 */

#include "console.h"
#include "filelib.h"
#include "queue.h"
#include "set.h"
#include "simpio.h"
#include "stack.h"
#include <fstream>
#include <iostream>
using namespace std;
Set<std::string> dictionary; // ignore it
Set<Stack<string>> ladders;  // ignore it
Set<string> nextWords(string currentWord);
Set<string> visitedWords(const Stack<string> &curLadder);

/**
 * @brief findWordLadder - 实现一个单词阶梯查找算法
 *
 * 例如：开始单词 cold 和结束单词 warm 可以得到如下结果。
 *
 * COLD -> CORD -> CARD -> WARD -> WARM
 *
 * @param start
 * @param end
 * @return 将计算出的单词阶梯以栈的形式保存
 */
Stack<string> findWordLadder(string start, string end) {
    // 1. 初始化一个查询待办清单
    Stack<string> initLadder = {start};           // 用 Stack 追踪单词之间的依赖关系
    Queue<Stack<string>> ToDoList = {initLadder}; // 用 Queue 模拟待办清单

    // 2. 如果待办清单不为空，则依次处理每个待办事项
    while (!ToDoList.isEmpty()) {
        // 3. 按先后顺序从清单中取出一个任务
        Stack<string> curLadder = ToDoList.dequeue();
        // 4. 检查任务是否完成
        string word = curLadder.peek();
        if (word == end) { // 即是否匹配最终单词
                           //            return curLadder;
            ladders.add(curLadder);
            continue;
        }

        // 5. 记录已查询过的单词，防止重复
        Set<string> visited = visitedWords(curLadder);

        // 6. 如果任务尚未满足，则根据当前任务，整理出
        //    后续将要处理的任务，依次加入待办清单
        Set<string> next = nextWords(word);           // 计算接下来需要查询的单词，
        for (const string &word : next) {             // 检查每一个单词，
            if (!visited.contains(word)) {            // 如果之前没有处理过，
                Stack<string> copyLadder = curLadder; // 则复制一份当前任务，
                copyLadder.push(word);                // 将新单词与新任务绑定，
                ToDoList.enqueue(copyLadder);         // 将新任务加入待办清单，
            }
        }
    }

    return {};
}

// ******************* 无需修改以下代码 **********************

int main() {
    // 初始化单词表
//    ifstream fin("res/Longman.txt");
        ifstream fin("res/SelectedWords.txt");
    //    ifstream fin("res/EnglishWords.txt");
    Vector<string> lines;
    readEntireFile(fin, lines);
    for (const string &word : lines) {
        dictionary.add(word);
    }

    // 程序交互部分
    while (true) {
        string start = getLine("输入开始单词: ");
        if (!start.size())
            break;
        string end = getLine("输入结束单词: ");
        if (!end.size())
            break;

        Stack<string> wordLadder = findWordLadder(start, end);

        if (wordLadder.isEmpty()) {
            cout << "未找到单词阶梯！" << endl;
            continue;
        }

        cout << "以下是从 " << start << " 到 " << end << " 生成的阶梯：" << endl;
        while (!wordLadder.isEmpty()) {
            cout << wordLadder.pop() << endl;
        }
        cout << endl;
    }
    for (const auto &ladder : ladders)
        cout << ladder << endl;

    cout << "游戏结束！" << endl;
    return 0;
}

Set<string> visitedWords(const Stack<string> &curLadder) {
    Set<string> visited;
    auto temp = curLadder;
    while (!temp.isEmpty()) {
        visited.add(temp.pop());
    }
    return visited;
}

/**
 * @brief nextWords - 根据提供的 currentWord 找出与其仅一字之差的单词。
 *
 * 例如：cat 对应的单词有 bat、eat、cot、cab、car 等等。
 *
 * @param currentWord
 * @return 将所有找出的单词以集合的形式返回
 */
Set<string> nextWords(string currentWord) {
    Set<string> neighboringWords;
    for (int i = 0; i < currentWord.length(); i++) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            string newWord = currentWord;
            newWord[i] = ch;
            if (dictionary.contains(newWord)) {
                neighboringWords.add(newWord);
            }
        }
    }
    return neighboringWords;
}
