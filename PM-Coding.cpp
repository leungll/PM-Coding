/*
 * @Author: Lili Liang
 * @Date: 2021-02-04 22:56:42
 * @LastEditTime: 2021-02-15 01:06:58
 * @LastEditors: Please set LastEditors
 * @Description: Solver algorithm in #3 Paper
 * @FilePath: \Paper_3\PM-Coding.cpp
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> PAIR;
const int MAXN = 1e4 + 10;

#define LOCAL

int numberedVertex[MAXN][MAXN];
vector<ll> hard_clause[MAXN], soft_clause[MAXN];
vector<ll> hard_clause_numbered_vector[MAXN], soft_clause_numbered_vector[MAXN];

int sortVertex[MAXN];
map<ll, ll> sortVertexMap;

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

bool cmp(int x, int y){
	return x > y;
}

bool cmp_val(const PAIR &left, const PAIR &right){
    return left.second > right.second;
}

// int main(int argc, char **argv) {
//     int k = atoi(argv[2]);
int main(){ 
    int k;

    int ver, clauseNum, hard_clause_weight;
    string hard_clause_weight_string;
    
    int clauseNumTemp = 0, hard_clause_num_temp_flag = 0;
    //number of hard clause, soft_clause
    int hard_clause_num, soft_clause_num;

    //number of numbered hard clause, soft_clause
    int hard_clause_numbered = 0, soft_clause_numbered = 0;

    #ifdef LOCAL
    cout << "Please enter the value of K:";
    cin >> k;
    #endif

    /*
    * Read file
    */ 
    string fileString;
    fstream in("V2.wcnf", ios::in);
    if(!in) {
        cout << "Read file error!" << endl;
    }
    while(getline(in, fileString)) {
        if(fileString[0] == 'c'){
            continue;
        }else if(fileString[0] == 'p'){
            std::vector<string> res = Split(fileString, " ");
            int len = res.size();
            // cout << len << endl;

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
            // cout << "len: " << len << endl;
            
            // cout << "clauseNumTemp: " << clauseNumTemp << endl; 
            for(int i = 1; i < len;i++){
                // cout << res[i] << " ";
                if(res[i] != "0"){
                    int temp;
                    string x = res[i];
                    stringstream ss;
                    ss << x;
                    ss >> temp;
                    // cout << "temp: " << temp << endl;
                    hard_clause[clauseNumTemp].push_back(temp);
                }
            }
            clauseNumTemp++;
            // cout << endl;
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
            // cout << "len: " << len << endl;

            // cout << "clauseNumTemp: " << clauseNumTemp << endl; 
            for(int i = 1; i < len;i++){
                // cout << res[i] << " ";
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
            // cout << endl;
        }
    }

    /*
    * Vertex generated variables
    */
    int num = 1;
    for(int i = 1; i <= ver; i++) {
        for(int j = 1; j <= k; j++) {
            numberedVertex[i][j] = num;
            num++;
        }
    }
    #ifdef LOCAL
    puts("-------------------------");
    cout << "Vertex generated variables:" << endl;
    for(int i = 1; i <= ver; i++) {
        for(int j = 1; j <= k; j++) {
            cout << numberedVertex[i][j] << " ";
        }
        puts("");
    }
    #endif

    memset(sortVertex, 0, sizeof(sortVertex));
    for(int i = 0; i < hard_clause_num;i++){
        for(int j = 0; j < hard_clause[i].size(); j++){
            int temp = abs(hard_clause[i][j]);
            cout << temp << endl;
            sortVertex[temp]++;
        }
    }
    // sort(sortVertex, sortVertex + ver, cmp);
    cout << "sortVertex: " << endl;
    for(int i = 1; i <= ver; i++){
        cout << sortVertex[i] << " ";
        pair<ll, ll> p(i, sortVertex[i]);
        sortVertexMap.insert(p);
    }
    puts("");
    vector<PAIR> vec(sortVertexMap.begin(), sortVertexMap.end());
    sort(vec.begin(), vec.end(), cmp_val);
    vector<PAIR>:: iterator itor = vec.begin();
    for(; itor != vec.end(); itor++){
        cout << itor -> first << " " << itor -> second << endl;
    }

    /*
    * hard_clause
    */
    // cout << "clauseNumTemp: " << clauseNumTemp << endl;
    for(int i = 0; i < hard_clause_num;i++){
        // puts("");
        vector<ll> hard_clause_numbered_temp;
        for(int j = 0; j < hard_clause[i].size(); j++){

            // cout << hard_clause[i][j] << " " << endl;
            
            int temp1 = hard_clause[i][j];
            for(int x = 1; x <= k; x++){
                if(temp1 > 0){
                    int getNumberedVertex = numberedVertex[temp1][x];
                    hard_clause_numbered_temp.push_back(getNumberedVertex);
                }else if(temp1 < 0){
                    int temp2 = abs(temp1);
                    int getNumberedVertex = -numberedVertex[temp2][x];
                    hard_clause_numbered_temp.push_back(getNumberedVertex);
                }
            }
        }
        cout << "hard_clause_numbered_temp: " << endl;
        for(int j = 0; j < hard_clause_numbered_temp.size(); j++){
            cout << hard_clause_numbered_temp[j] << " ";
        }
        puts("");

        int cnt = 0;
        cout << "hard_clause : " << endl;
        for(int j = 0; j < k; j++){
            for(int x = 0; x < hard_clause_numbered_temp.size(); x++) {
                if( (x - cnt) % k == 0){
                    cout << hard_clause_numbered_temp[x] << " ";
                    cnt = x;
                    int temp = hard_clause_numbered_temp[x];
                    hard_clause_numbered_vector[hard_clause_numbered].push_back(temp);
                }
            }
            cnt++;
            hard_clause_numbered++;
            puts("");
        }
    }

    /*
    * soft_clause
    */
    for(int i = hard_clause_num; i < clauseNum;i++){
        // puts("");
        vector<ll> soft_clause_numbered_temp;
        for(int j = 0; j < soft_clause[i].size(); j++){

            // cout << soft_clause[i][j] << " " << endl;
            
            int temp1 = soft_clause[i][j];
            for(int x = 1; x <= k; x++){
                if(temp1 > 0){
                    int getNumberedVertex = numberedVertex[temp1][x];
                    soft_clause_numbered_temp.push_back(getNumberedVertex);
                }else if(temp1 < 0){
                    int temp2 = abs(temp1);
                    int getNumberedVertex = -numberedVertex[temp2][x];
                    soft_clause_numbered_temp.push_back(getNumberedVertex);
                }
            }
        }
        cout << "soft_clause_numbered_temp: " << endl;
        for(int j = 0; j < soft_clause_numbered_temp.size(); j++){
            cout << soft_clause_numbered_temp[j] << " ";
            int temp = soft_clause_numbered_temp[j];
            soft_clause_numbered_vector[soft_clause_numbered].push_back(temp);
        }
        soft_clause_numbered++;
        puts("");
    }

    puts("-------------------------");
    cout << "clause: " << endl;
    for(int i = 0; i < hard_clause_numbered; i++){
        for(int j = 0; j < hard_clause_numbered_vector[i].size(); j++){
            cout << hard_clause_numbered_vector[i][j] << " ";
        }
        puts("");
    }
    for(int i = 0; i < soft_clause_numbered; i++){
        for(int j = 0; j < soft_clause_numbered_vector[i].size(); j++){
            cout << soft_clause_numbered_vector[i][j] << " ";
        }
        puts("");
    }
    system("pause");
    return 0;
}