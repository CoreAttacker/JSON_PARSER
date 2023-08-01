#include<sstream>
#include<fstream>
#include<algorithm>
#include"json_parser.hpp"

void Val::del(){
            if(type == Dynamic_type::STR) STR_VAL.clear();
            if(type == Dynamic_type::LIST) List.clear();
            if(type == Dynamic_type::DICT) Dict.clear();
        }
Val::Val(){}
Val::~Val(){
    del();
}
Val::Val(const int &x){
            del();
            INT_VAL = x;
            type = Dynamic_type::INT;
}
Val::Val(const double &x){
            del();
            DOU_VAL = x;
            type = Dynamic_type::DOU;
}
Val::Val(const string &x){
            del();
            STR_VAL = x;
            type = Dynamic_type::STR;
}
Val::Val(const char* x){
            del();
            type = Dynamic_type::STR;
            STR_VAL = string(x);
}
Val::Val(const bool &x){
            del();
            BOOL_VAL = x;
            type = Dynamic_type::BOOL;
}
Val::Val(initializer_list<Val> l){
            del();
            type = Dynamic_type::LIST;
            for(Val x : l) List.push_back(x);
}
void Val::add(Val x){
            if(type == Dynamic_type::LIST) List.push_back(x);
}
void Val::put(Val key, Val val){
            if(type == Dynamic_type::DICT) Dict[key] = val;
}
Val& Val::operator[](Val x){
            if(type == Dynamic_type::LIST) return List[x.INT_VAL];
            else return Dict[x];
}

ostream& operator << (ostream& out, const Val & v){
    if(v.type == Dynamic_type::INT) out << v.INT_VAL;
    if(v.type == Dynamic_type::DOU) out << v.DOU_VAL;
    if(v.type == Dynamic_type::STR) out << "\"" << v.STR_VAL << "\"";
    if(v.type == Dynamic_type::BOOL){
        if(v.BOOL_VAL) out << true;
        else out << false;
    }
    if(v.type == Dynamic_type::LIST){
        out << "[";
        for(int i = 0;i < v.List.size();i++){
            if(i) out << ',';
            out << v.List[i];
        }
        out << "]";
    }
    if(v.type == Dynamic_type::DICT){
          out << "{";
        for(auto i = v.Dict.begin();i != v.Dict.end();i++){
            if(i != v.Dict.begin()) out << ',';
            out << i->first << ':' << i->second;
        }
        out << "}";
    }
    return out;
}

bool operator < (const Val & a, const Val & b){
    if(a.type != b.type) return a.type < b.type;
    else{
        if(a.type == Dynamic_type::INT) return a.INT_VAL < b.INT_VAL;
        if(a.type == Dynamic_type::DOU) return a.DOU_VAL < b.DOU_VAL;
        if(a.type == Dynamic_type::STR) return a.STR_VAL < b.STR_VAL;
        if(a.type == Dynamic_type::LIST) return a.List < b.List;
        if(a.type == Dynamic_type::DICT) return a.Dict < b.Dict;
        return true;
    }
}

stringstream ss;
Val parser_int();
Val parser_dou();
Val parser_str();
Val parser_bool();
Val parser_list();
Val parser_dict();
 //peek()读取并返回下一个字符，但并不将下一个字符放到输入流中
 //get()将下一个字符放到输入流中
Val parser_int(){
    while(ss.peek() != -1){
        if(ss.peek() == ' ' || ss.peek() == '\n' || ss.peek() == '\t') ss.get();
        else if(ss.peek() == '"'){
            return parser_str();
        }
        else if(ss.peek() == 'f' || ss.peek() == 't'){
            return parser_bool();
        }
        else if(ss.peek() == '['){
            return parser_list();
        }
        else if(ss.peek() == '{'){
            return parser_dict();
        }
        else return parser_dou();
    }
    return 0;
}

Val parser_dou(){
    string s;//返回时将其转换成浮点数
    while (isdigit(ss.peek()) || ss.peek() == '.' || ss.peek() == 'e' || ss.peek() == '-' || ss.peek() == '+') s.push_back(ss.get());
    //isdigit()若参数是0~9整数，返回非0值，否则返回0
    if(count(s.begin(), s.end(), '.') || count(s.begin(), s.end(), 'e')){//如果是浮点数
        return stof(s); //将字符串转化为浮点数
    }
    else {//如果是整数
        return stoi(s); //将字符串转化为n进制整数（默认十进制）
    }
}

Val parser_str(){
    ss.get();//输出开头的"
    string s;
    while (ss.peek() != '"') s.push_back(ss.get());
    ss.get();//输出结尾的"
    return Val(s);
}

Val parser_bool(){
    if(ss.peek() == 'f'){
        ss.get();//f
        ss.get();//a
        ss.get();//l
        ss.get();//s
        ss.get();//e
        return Val(false);
    }
    else {
        ss.get();//t
        ss.get();//r
        ss.get();//u
        ss.get();//e
        return Val(true);
    }
}

Val parser_list(){
    ss.get(); //输出开头的[
    Val vec;
    vec.type = Dynamic_type::LIST;
    while(ss.peek() != ']'){
        vec.add(parser_int());
        while(ss.peek() != ']' && (ss.peek() == ' ' || ss.peek() == '\t' || ss.peek() == '\n' || ss.peek() == ',')) ss.get();
    }
    ss.get();
    return vec;
}

Val parser_dict(){
    ss.get(); //开头的{放进输出流
    Val dict;
    dict.type = Dynamic_type::DICT;
    while(ss.peek() != '}'){
        Val key = parser_int(); //把key放进输出流
        while(ss.peek() == ' ' || ss.peek() == ':') ss.get(); //键值对中间的空格和冒号放进输出流
        Val val = parser_int(); //把val放进输出流
        dict.put(key, val); //把每个键值对都放入dict实例的Val::Dict中
        while(ss.peek() != '}' && (ss.peek() == ' ' || ss.peek() == '\t' || ss.peek() == '\n' || ss.peek() == ',')) ss.get(); //检测该json对象{}中是否有有多个键值对
    }
    ss.get(); //结尾的}放进输出流
    return dict;
}

Val parser(string s){
    ss.clear();
    ss << s;
    return parser_int();
}

int main(){
    ifstream fin("test.json");
    stringstream ss; //存json
    ss << fin.rdbuf();
    Val x = parser(ss.str()); //解析，ss.str()将rebuf转换为string
    cout << x << endl; //重载后可输出多类型的值，而输出的顺序正确是因为
    return 0;
}
