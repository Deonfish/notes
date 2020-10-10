//90分
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;
vector<string> dt;
string parse(const string &s){
    string ans;
    for(int i = 0, j = 1; i < s.size(); i = j, j++){
        if(s[i] == '_'){
            int k = j;
            while(k < s.size() && s[k] != '_') k++;
            if(k == s.size()) {ans.push_back(s[i]); continue; }
            j = k;
            ans = ans+"<em>";
            ans = ans+s.substr(i+1, j-i-1);
            ans = ans+"</em>";
            j++;
        }
        else if(s[i] == '['){   //wrong2
            int k1 = -1, k2 = -1, k3 = j;
            while(k3 < s.size() && s[k3] != ')') { if(s[k3] == ']') k1 = k3; else if(s[k3] == '(') k2 = k3; k3++; }
            if(k2 == -1 || k1 == -1 || k3 == j || (k2 - k1 != 1)) { ans.push_back(s[i]); continue;}     //wrong：](中间不得有字符
            string str = "<a href=\"" + parse(s.substr(k2+1, k3-k2-1)) + "\">" + parse(s.substr(i+1, k1-i-1)) + "</a>";
            ans = ans + str;
            j = k3+1;
        }
        else ans.push_back(s[i]);
    }
    return ans;
}
int main(){
    freopen("in.txt", "r", stdin);
    string str;
    while(getline(cin, str)) dt.push_back(str);
    /*
     cout << dt.size() << endl;
     for(auto s : dt) cout << s << endl;
     */
    for(int i = 0, j = 1; i < dt.size(); i = j, j++){   //wrong: 每个while都要有保护性声明
        if(dt[i][0] == '#'){
            int lv = 0, k = 0;
            while(k < dt[i].size() && dt[i][k] == '#'){ lv++; k++; }
            while(k < dt[i].size() && dt[i][k] == ' ') k++;
            cout << "<h" << lv << ">" << parse(dt[i].substr(k)) << "</h" << lv << ">" << endl;
        }
        else if(dt[i][0] == '*'){
            while(j < dt.size() && dt[j][0] == '*') j++;
            cout << "<ul>" << endl;
            for(int k = i; k != j; k++){
                int beg = 1;
                while(beg < dt[k].size() && dt[k][beg] == ' ') beg++;
                cout << "<li>" << parse(dt[k].substr(beg)) << "</li>" << endl;
            }
            cout << "</ul>" << endl;
        }
        else{
            if(dt[i].size() == 0) continue;
            while(j < dt.size() && dt[j].size() != 0 && dt[j][0] != '*' && dt[j][0] != '#') j++;
            cout << "<p>";
            for(int k = i;k != j; k++) {
                cout << parse(dt[k]);
                if(k == j-1) cout << "</p>";
                cout << endl;
            }
        }
    }
    return 0;
}
