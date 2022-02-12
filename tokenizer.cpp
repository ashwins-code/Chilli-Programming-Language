#include "tokenizer.h"
#include <regex>

using namespace std;

Token::Token(string v, string t, int n) {
    value = v;
    type = t;
    lineno = n;
}


Tokenizer::Tokenizer(string s) {
    src = s;
    idx = 0;
    lineno = 1;
}

Token Tokenizer::NextToken() {
    Token token = Peek();
    idx += token.value.size();

    return token;
}

Token Tokenizer::Peek() {
    for (vector<string> s : scheme) {
        smatch sm;
        regex r(s[0]);
        string sub_src = src.substr(idx);

        if (regex_search(sub_src, sm, r)) {
            string v = sm[0];
            string t = s[1];

            if (t == "") { 
                idx += v.size();
                return Peek();
            }

            Token token(v, t, lineno);
            
            return token;
        }
    }

    return Token("", "NONE", -1);
}