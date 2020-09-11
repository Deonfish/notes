#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
const long long E9 = (long long )1e9;
struct Commodity{
    Commodity(){}
    Commodity(long long _tNc, long long _s):tNc(_tNc), score(_s){}
    ~Commodity(){}
    bool operator < (const Commodity &o) const {
        return score != o.score ? score > o.score : tNc < o.tNc;
    }
    long long tNc, score;
};
set<Commodity> st;
unordered_map<long long, set<Commodity>::iterator> um; //tNc->iterator
int m, n;
int main(){
    freopen("in.txt", "r", stdin);
    int T;
    cin >> m >> n;
    while(n--){
        int id, score;
        cin >> id >> score;
        for(int i = 0; i < m; i++){
            long long key = i*E9+id;
            um[key] = st.insert(Commodity(key, score)).first;
        }
    }
    cin >> T;
    while(T--){
        int flag;
        cin >> flag;
        if(flag == 1){
            int type, com, sc; long long key;
            cin >> type >> com >> sc;
            key = type*E9 + com;
            um[key] = st.insert(Commodity(key, sc)).first;
        }
        else if(flag == 2){
            int type, com;
            cin >> type >> com;
            long long key = type*E9 + com;
            st.erase(um[key]);
        }
        else if(flag == 3){
            int k; vector<int> vec(m); vector<vector<int>> ans(m);
            cin >> k;
            for(auto &x : vec) cin >> x;
            for(auto com : st){
                if(k <= 0) break;
                if(vec[com.tNc/E9] > 0){
                    ans[com.tNc/E9].push_back(com.tNc%E9);
                    k--; vec[com.tNc/E9]--;
                }
            }
            for(int i = 0; i < ans.size(); i++) {
                //sort(ans[i].begin(), ans[i].end());
                if(ans[i].size() == 0) cout << "-1\n";
                else{
                    for(int j = 0; j < ans[i].size(); j++)
                        if(j != ans[i].size()-1) cout << ans[i][j] << " ";
                        else cout << ans[i][j] << endl;
                }
            }
        }
        /*
        for(auto com : st)
            printf("(%lld, %lld)\n", com.tNc, com.score);
        cout << "-------------\n";
        */
    }
    return 0;
}
