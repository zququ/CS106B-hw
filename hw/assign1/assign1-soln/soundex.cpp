/*
 * 姓氏编码检索程序
 */
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include <cctype>
#include <fstream>
#include <string>
using namespace std;

// 1. 去除字符串中所有非字母字符：横线、空格、标点等
// ""           ->   ""
// "12_34"      ->   ""
// "O'Con ner"  ->   "OConner"
string removeNonLetters(string s) {
    // string result = charToString(s[0]); // 空字符串
    string result;
    for (int i = 0; i < s.length(); i++) { // 1 -> 0
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

STUDENT_TEST("测试空字符串、无字母字符串") {
    EXPECT_EQUAL(removeNonLetters(""), "");
    EXPECT_EQUAL(removeNonLetters("1234"), "");
}

// 2. 根据编码规则，将字符串中每个字符转换为对应编码
// "AbCd"   ->  "0123"
// ""       ->  ""
// "123"    ->  ""
string encodeLetters(string s) {
    string result;

    string zero = "AEIOUHWY";
    string one = "BFPV";
    string two = "CGJKQSXZ";
    string three = "DT";
    string four = "L";
    string five = "MN";
    string six = "R";

    for (int i = 0; i < s.size(); i++) {
        char ch = toUpperCase(s[i]);
        if (zero.find(ch) != string::npos)
            result += "0";
        if (one.find(ch) != string::npos)
            result += "1";
        if (two.find(ch) != string::npos)
            result += "2";
        if (three.find(ch) != string::npos)
            result += "3";
        if (four.find(ch) != string::npos)
            result += "4";
        if (five.find(ch) != string::npos)
            result += "5";
        if (six.find(ch) != string::npos)
            result += "6";
    }

    return result;
}

STUDENT_TEST("测试编码函数") {
    EXPECT_EQUAL(encodeLetters("AbCd"), "0123");
    EXPECT_EQUAL(encodeLetters(""), "");
    EXPECT_EQUAL(encodeLetters("1234"), "");
}

// 3. 合并字符串中重复的数字(任意重复字符合并)
// "223344"       ->    "234"
// ""             ->    ""
// "aa11bb22"     ->    "a1b2"
// "aa__bb  c''d" ->    "a_b c'd"
string coalesceLetters(string s) {
    string result;
    for (int i = 0; i < s.size(); i++) {
        if (result.back() == s[i])
            continue;
        result += s[i];
    }
    return result;
}

STUDENT_TEST("测试合并函数") {
    EXPECT_EQUAL(coalesceLetters("223344"), "234");
    EXPECT_EQUAL(coalesceLetters(""), "");
    EXPECT_EQUAL(coalesceLetters("aa11bb22"), "a1b2");
    EXPECT_EQUAL(coalesceLetters("aa__bb  c''d"), "a_b c'd");
}

// 4. 使用姓氏名的第一个字符替换第一个数字，并转为大写
// "", ""       -> ""
// "01", "mike" -> "M1"
string replaceHeader(string s, string name) {
    if (s.size() && name.size())
        s[0] = toUpperCase(name[0]);
    return s;
}

STUDENT_TEST("测试替换函数") {
    EXPECT_EQUAL(replaceHeader("", ""), "");
    EXPECT_EQUAL(replaceHeader("01", "mike"), "M1");
}

// 5. 删除字符串中的数字 0
// ""       ->    ""
// " _"     ->    " _"
// "a0b2"   ->    "ab2"
// "100200" ->    "12"
string removeZeroLetter(string s) {
    string result;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            continue;
        result += s[i];
    }
    return result;
}

STUDENT_TEST("测试去零函数") {
    EXPECT_EQUAL(removeZeroLetter(""), "");
    EXPECT_EQUAL(removeZeroLetter(" _"), " _");
    EXPECT_EQUAL(removeZeroLetter("0a0b2"), "ab2");
    EXPECT_EQUAL(removeZeroLetter("0100200"), "12");
}

// 6. 填充0或截取多余字符
// ""        ->    "0000"
// "12"      ->    "1200"
// "xuehao"  ->    "xueh"
string adjustStrlen(string s) {
    if (s.size() > 4)
        return s.substr(0, 4);

    for (int i = 4 - s.size(); i > 0; i--) {
        s += '0';
    }
    return s;
}

STUDENT_TEST("测试调整函数") {
    EXPECT_EQUAL(adjustStrlen(""), "0000");
    EXPECT_EQUAL(adjustStrlen("12"), "1200");
    EXPECT_EQUAL(adjustStrlen("xuehao"), "xueh");
}

// 7. 姓氏编码程序
// "Curie"       ->   "C600"
// "O'Conner"    ->   "O256"
// ""            ->   "0000"
string soundex(string s) {
    string result;
    result = removeNonLetters(s);
    result = encodeLetters(result);
    result = coalesceLetters(result);
    result = replaceHeader(result, s);
    result = removeZeroLetter(result);
    result = adjustStrlen(result);
    return result;
}

STUDENT_TEST("测试编码程序") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
    EXPECT_EQUAL(soundex(""), "0000");
    EXPECT_EQUAL(soundex(" ——"), "0000");
    EXPECT_EQUAL(soundex("上海"), "0000");
}


/* 8. 姓氏编码检索程序 */
void soundexSearch(string filepath) {
    ifstream in;
    Vector<string> databaseNames;
    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    /* 姓氏编码检索交互部分 */
    while (true) {
        string name = getLine("Enter a surname (RETURN to quit): ");
        if (name.empty()) {
            cout << "All done!" << endl;
            break;
        }

        string code = soundex(name);

        cout << "Soundex code is " << code << endl;

        Vector<string> matchNames;
        for (const string& name : databaseNames) {
            if (soundex(name) == code)
                matchNames.add(name);
        }
        matchNames.sort();
        cout << "Matches from database: " << matchNames << endl;
    }
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here

