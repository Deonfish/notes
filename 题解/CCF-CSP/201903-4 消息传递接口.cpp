201903-4 消息传递接口
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <algorithm>
using namespace std;
vector<vector<short>> send;
vector<bool> callable;  //是否该执行下一条指令
vector<int> nextIns;    //下一条指令index
vector<vector<string> > Ins;
int n;
void init(){
    fill(nextIns.begin(), nextIns.end(), 0);
    fill(callable.begin(), callable.end(), true);
    for(int i = 0; i < n; i++){
        Ins[i].clear();
        fill(send[i].begin(), send[i].end(), 0);
    }
}
bool continueable(){ //指令遍历完毕或无可执行指令返回false，否则true
    for(int i = 0; i < n; i++) if(callable[i]) return true;
    return false;
}
bool runIns(){
    while(continueable()){ //遍历每一个可执行指令
        //cout << "continue: " << endl;
        for(int i = 0; i < n; i++){ //每个进程
            //printf("in %d: \n", i);
            if(callable[i] == 0 || nextIns[i] >= Ins[i].size()) continue;
            string sIns = Ins[i][nextIns[i]];
            int r = -1, c = -1;
            if(sIns[0] == 'S'){
                r = i; c = stoi(sIns.substr(1));
                send[r][c] ++;
            }
            else {
                r = stoi(sIns.substr(1)); c = i;
                send[r][c]--;
            }
            //printf("r = %d, c = %d\n", r, c);
            if(send[r][c] == 0){
                nextIns[r]++; nextIns[c]++;
                callable[r] = true; callable[c] = true;
                if(nextIns[r] >= Ins[r].size()) callable[r] = false;
                if(nextIns[c] >= Ins[c].size()) callable[c] = false;
            }
            else callable[i] = false;
        }
        /*
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < send[i].size(); j++) cout << send[i][j] << " ";
            cout << endl;
        }
        cout << "callable: "; for(auto x : callable) cout << x << " "; cout << endl;
        cout << "nextIns: "; for(auto x : nextIns) cout << x << " "; cout << endl;
        */
    }
    for(int i = 0; i < n; i++)
        if(nextIns[i] != Ins[i].size()) return false;
    return true;
}

int main(){
    freopen("in.txt", "r", stdin);
    int T;
    cin >> T >> n;
    Ins.resize(n);
    send.resize(n);
    for(int i = 0; i < n; i++) send[i].resize(n);
    callable.resize(n);
    fill(callable.begin(), callable.end(), true);
    nextIns.resize(n);
    getchar();
    while(T--){
        init();
        string line, s;
        for(int i = 0; i < n; i++){
            getline(cin, line);
            stringstream ss(line);
            while(ss >> s) Ins[i].push_back(s);
        }
        cout << (runIns()? "0" : "1");
        cout << endl;
    }
    return 0;
}
