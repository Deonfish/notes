#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;
struct Commodity{
    Commodity(){}
    Commodity(int t, int n, int s): type(t), num(n), score(s){}
    ~Commodity(){}
    int type, num, score;
    bool operator < (const Commodity &other) const {
        if(score != other.score) return score > other.score;
        else if(type != other.type) return type < other.type;
        else return num < other.num;
    }
};
int m, n, T;
set<Commodity> st;
void adCom(int type, int num, int score){
    st.insert(Commodity(type, num, score));
}
void delCom(int type, int num){
    auto it = st.begin();
    for(; it != st.end(); it++)
        if(it->type == type && it->num == num) break;
    st.erase(it);
}
void printCom(vector<int> &vec){ //vec[1]: 0类商品上限
    vector<vector<int> > ans(m); //商品编号
    for(auto com : st){
        if(vec[0] <= 0) break;
        if(vec[com.type+1] > 0){
            ans[com.type].push_back(com.num);
            vec[0]--; vec[com.type+1]--;
        }
    }
    for(int i = 0; i < ans.size(); i++) sort(ans[i].begin(), ans[i].end());
    for(int i = 0; i < ans.size(); i++)
        if(ans[i].size() == 0) cout << "-1" << endl;
        else{
            for(int j = 0; j < ans[i].size(); j++)
                if(j != ans[i].size()-1) cout << ans[i][j] << " ";
                else cout << ans[i][j] << endl;
        }
}
int main(){
    freopen("in.txt", "r", stdin);
    cin >> m >> n;
    while(n--){
        int num, score;
        cin >> num >> score;
        for(int i = 0; i < m; i++)
            st.insert(Commodity(i, num, score));
    }
    cin >> T;
    while(T--){
        int flag;
        cin >> flag;
        if(flag == 1){
            int type, num, score;
            cin >> type >> num >> score;
            adCom(type, num, score);
        }
        else if(flag == 2){
            int type, num;
            cin >> type >> num;
            delCom(type, num);
        }
        else if(flag == 3){
            vector<int> vec(m+1);
            for(int &x : vec) cin >> x;
            printCom(vec);
        }
    }

    return 0;
}
