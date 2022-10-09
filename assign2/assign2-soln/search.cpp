// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "search.h"
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include <fstream>
#include <iostream>
using namespace std;

#define CLEANTOKEN_V1
#ifdef CLEANTOKEN_V1
/**
 * @brief cleanToken - 标准化字符串
 * @param s
 * @return 
 */
string cleanToken(string s)
{
    // 去除字符串首的标点符号
    int start = 0;
    while (start < s.size() && ispunct(s[start]))
        start++;
    if (start > 0)
        s.erase(0, start);

    // 去除字符串尾的标点符号
    int end = s.size() - 1;
    while (end > 0 && ispunct(s[end]))
        end--;
    if (end < s.size() - 1)
        s.erase(end + 1, s.size());

    // 确认字符串至少包含一个字符，如发现数字返回空字符串
    bool letterFlag = false;
    for (int i = 0; i < s.size(); i++) {
        if (isalpha(s[i])) {
            letterFlag = true;
            break;
        }
    }
    if (!letterFlag) // 所有字符全部没有通过测试
        return "";

    // 将字符串转换为小写
    return toLowerCase(s);
}
#endif

STUDENT_TEST("cleanToken 测试") {
    EXPECT_EQUAL(cleanToken(""), "");
    EXPECT_EQUAL(cleanToken(";"), "");
    EXPECT_EQUAL(cleanToken(";22‘"), "");
    EXPECT_EQUAL(cleanToken("北京"), "");
}

/**
 * @brief gatherTokens - 获取网页文本中的关键字集合
 * @param text
 * @return 网页文本关键字集合
 */
Set<string> gatherTokens(string text)
{
    Set<string> tokens;

    Vector<string> v = stringSplit(text, " "); // 拆分
    for (const string &item : v) {             // 遍历
        string t = cleanToken(item);
        if (t.size()) // 不要忘记 token 的要求
            tokens.add(t); // 无需判断
    }

    return tokens;
}

/**
 * @brief buildIndex - 读取网页数据库，构建反向索引
 * @param dbfile
 * @param index
 * @return 网页数量
 */
int buildIndex(string dbfile, Map<string, Set<string>> &index) {
    // 重用 maze 中代码读取 dbfile
    ifstream in;
    if (!openFile(in, dbfile))
        error("Cannot open file named " + dbfile);
    Vector<string> lines;
    readEntireFile(in, lines);

    // 构建反向索引
    int pages = 0;
    for (int url = 0; url < lines.size(); url += 2) {
        // 取出网页中的 tokens
        Set<string> tokens = gatherTokens(lines[url + 1]); // 默认小写
        // 对每一个 token 绑定页面 url
        for (const string &token : tokens) {
            index[token].add(lines[url]); // 无需判断
        }
        pages++;
    }

    return pages;
}

#define FINDQUERYMATCHES_V1
#ifdef FINDQUERYMATCHES_V2 // 学生测试
Set<string> findQueryMatches(Map<string, Set<string>> &index, string query) {

}
#endif

#ifdef FINDQUERYMATCHES_V1 // my soln
/**
 * @brief findQueryMatches - 根据 query 不同组合整理匹配结果
 * @param index
 * @param query
 * @return 搜索结果 url 集合
 */
Set<string> findQueryMatches(Map<string, Set<string>> &index, string query) {
    Set<string> result;
    // 拆分关键词
    Vector<string> tokens = stringSplit(query, " ");
    // 遍历关键词并整合结果
    for (const string &token : tokens) {
        // 处理交集
        if (startsWith(token, "+")) {
            result.intersect(index[cleanToken(token)]);
        }
        // 处理差集
        else if (startsWith(token, "-")) {
            result.difference(index[cleanToken(token)]);
        }
        // 处理并集
        else {
            result.unionWith(index[cleanToken(token)]);
        }
    }

    return result;
}
#endif

STUDENT_TEST("findQueryMatches 测试大小写") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "rEd fiSh");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
}

/**
 * @brief searchEngine
 * @param dbfile
 */
void searchEngine(string dbfile)
{
    // 根据 dbfile 构建反向索引
    Map<string, Set<string>> index;
    int pages = buildIndex(dbfile, index);
    // 打印信息
    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << pages << " pages containing " << index.size() << " unique terms" << endl;
    // 循环提示用户输入查询关键词
    while (true) {
        string terms = getLine("Enter query sentence (RETURN/ENTER to quit): ");
        // 当用户输入空字符串时，提示查询完成，程序结束。
        if (terms.empty()) {
            break;
        }
        // 对于每一个查询关键词，找出所有匹配页面并打印出 URLs
        Set<string> matches = findQueryMatches(index, terms);
        cout << "Found " << matches.size() << " matching pages" << endl;
        cout << matches << endl;
        cout << endl;
    }
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}

PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here
