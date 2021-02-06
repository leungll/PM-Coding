/*
 * @Author: Lili Liang
 * @Date: 2021-02-04 22:56:42
 * @LastEditTime: 2021-02-07 00:16:26
 * @LastEditors: Please set LastEditors
 * @Description: Solver algorithm in #3 Paper
 * @FilePath: \Paper_3\PM-Coding.cpp
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll>PAIR;
const int MAXN = 1e4 + 10;

#define LOCAL

vector<int> hard_clause[MAXN], soft_clause[MAXN];

vector<string> Split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	char * strs = new char[str.length() + 1];
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p;
		res.push_back(s);
		p = strtok(NULL, d);
	}
	return res;
}

// int main(int argc, char **argv) {
//     int k = atoi(argv[2]);
int main(){
    int k;

    int ver, clauseNum, hard_clause_weight;
    string hard_clause_weight_string;
    
    int clauseNumTemp = 0, hard_clause_num_temp_flag = 0;
    int hard_clause_num, soft_clause_num;

    /*
    * Read file
    */ 
    string fileString;
    fstream in("test.wcnf", ios::in);
    if(!in) {
        cout << "Read file error!" << endl;
    }
    while(getline(in, fileString)) {
        if(fileString[0] == 'c'){
            continue;
        }else if(fileString[0] == 'p'){
            std::vector<string> res = Split(fileString, " ");
            int len = res.size();

            #ifdef LOCAL
            cout << len << endl;
            #endif

            //hard_clause_weight
            string x1 = res[len - 1];
            hard_clause_weight_string = x1;
            stringstream ss1;
            ss1 << x1;
            ss1 >> hard_clause_weight;
            
            //clauseNum
            string x2 = res[len - 2];
            stringstream ss2;
            ss2 << x2;
            ss2 >> clauseNum;

            //ver
            string x3 = res[len - 3];
            stringstream ss3;
            ss3 << x3;
            ss3 >> ver;

            #ifdef LOCAL
            cout << "ver : " << ver << " clauseNum : " << clauseNum 
            << " hard_clause_weight : " << hard_clause_weight << endl;
            #endif
        }else if(fileString[0] == hard_clause_weight_string[0]){
            std::vector<string> res = Split(fileString, " ");
            int len = res.size();

            // cout << "clauseNumTemp: " << clauseNumTemp << endl; 
            for(int i = 1; i < len;i++){
                cout << res[i] << " ";
                if(res[i] != "0"){
                    int temp;
                    string x = res[i];
                    stringstream ss;
                    ss << x;
                    ss >> temp;
                    hard_clause[clauseNumTemp].push_back(temp);
                }
            }
            clauseNumTemp++;
            cout << endl;
        }else if(fileString[0] == '1'){
            if(!hard_clause_num_temp_flag){
                hard_clause_num_temp_flag = 1;

                hard_clause_num = clauseNumTemp;
                soft_clause_num = clauseNum - clauseNumTemp;
                
                #ifdef LOCAL
                cout << "hard_clause_num: " << hard_clause_num << endl;
                cout << "soft_clause_num: " << soft_clause_num << endl;
                #endif
            }
            
            std::vector<string> res = Split(fileString, " ");
            int len = res.size();
            cout << "len: " << len << endl;

            // cout << "clauseNumTemp: " << clauseNumTemp << endl; 
            for(int i = 1; i < len;i++){
                cout << res[i] << " ";
                if(res[i] != "0"){
                    int temp;
                    string x = res[i];
                    stringstream ss;
                    ss << x;
                    ss >> temp;
                    soft_clause[clauseNumTemp].push_back(temp);
                }
            }
            clauseNumTemp++;
            cout << endl;
        }
    }
    cout << "clauseNumTemp: " << clauseNumTemp << endl;
    for(int i = 0; i < hard_clause_num;i++){
        for(int j = 0; j < hard_clause[i].size(); j++){
            cout << hard_clause[i][j] << " ";
        }
        cout << endl;
    }
    for(int i = hard_clause_num; i < clauseNum;i++){
        for(int j = 0; j < soft_clause[i].size(); j++){
            cout << soft_clause[i][j] << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}