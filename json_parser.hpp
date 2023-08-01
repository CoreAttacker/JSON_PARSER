#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include<iostream>
#include<vector>
#include<map>

using std::cout; using std::endl;
using std::vector; using std::map; 
using std::ostream; using std::ifstream;
using std::string; using std::stringstream;
using std::operator<<; using std::initializer_list;



enum class Dynamic_type{
    INT = 0,
    DOU,
    STR,
    BOOL,
    LIST,
    DICT
};

class Val{ //动态类型的变量
    public:
        int INT_VAL;
        double DOU_VAL;
        string STR_VAL;
        bool BOOL_VAL;
        vector<Val>List;
        map<Val, Val>Dict;
        Dynamic_type type;

        void del();

        Val();
        ~Val();

        Val(const int &x);
        Val(const double &x);
        Val(const string &x);
        Val(const char* x);
        Val(const bool &x);
        Val(initializer_list<Val> l);

        void add(Val x);
        void put(Val key, Val val);

        Val& operator[](Val x);

        string str();
};

ostream& operator << (ostream& out, const Val & v);
bool operator < (const Val & a, const Val & b);

Val parser_int();
Val parser_dou();
Val parser_str();
Val parser_bool();
Val parser_list();
Val parser_dict();
Val parser(string s);

#endif