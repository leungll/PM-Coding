/*
 * @Author: Lili Liang
 * @Date: 2021-02-04 22:56:42
 * @LastEditTime: 2021-02-21 01:02:26
 * @LastEditors: Please set LastEditors
 * @Description: Solver algorithm in #3 Paper
 * @FilePath: \Paper_3\PM-Coding.cpp
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> PAIR;
const int MAXN = 1e6 + 10;

// #define LOCAL

//initial hard clause, soft clause
vector<ll> hard_clause[MAXN], soft_clause[MAXN];
//numbered hard clause, soft clause
vector<ll> hard_clause_numbered_vector[MAXN], soft_clause_numbered_vector[MAXN];

//numbered vertex matrix, sort numbered vertex matrix
ll numberedVertex[MAXN][23], sortNumberedVertexMatrix[MAXN][23], updateNumberedVertex[MAXN][23];
vector<ll> sortVertex, deleteVertex;
set<ll> deleteVertexRow;

set<ll> updateVertexSet;

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

bool CompareMapValue(const PAIR &left, const PAIR &right){
    return left.second > right.second;
}

vector<ll> SortVertexFunc1(int ver, int hard_clause_num){
    int sortVertexNum[MAXN];
    map<ll, ll> sortVertexMap;
    memset(sortVertexNum, 0, sizeof(sortVertexNum));

    //sort vertexNum
    for(int i = 0; i < hard_clause_num;i++){
        for(int j = 0; j < hard_clause[i].size(); j++){
            int temp = abs(hard_clause[i][j]);
            sortVertexNum[temp]++;
        }
    }
    #ifdef LOCAL
    cout << "SortVertexNum: " << endl;
    #endif
    for(int i = 1; i <= ver; i++){
        #ifdef LOCAL
        cout << "ver :" << i << " num : " << sortVertexNum[i] << endl;
        #endif

        pair<ll, ll> p(i, sortVertexNum[i]);
        sortVertexMap.insert(p);
    }

    //sort vertexMap
    #ifdef LOCAL
    cout << "SortVertexMap:" << endl;
    #endif
    vector<PAIR> vec(sortVertexMap.begin(), sortVertexMap.end());
    sort(vec.begin(), vec.end(), CompareMapValue);
    vector<PAIR>:: iterator itor = vec.begin();
    for(; itor != vec.end(); itor++){
        #ifdef LOCAL
        cout << itor -> first << " " << itor -> second << endl;
        #endif

        sortVertex.push_back(itor -> first);
    }
    return sortVertex;
}

int main(int argc, char **argv) {
    int k = atoi(argv[2]), sort = atoi(argv[3]);
// int main(){ 
//     int k = 3, sort = 1;

    int ver, clauseNum, hard_clause_weight;
    string hard_clause_weight_string;
    
    int clauseNumTemp = 0, hard_clause_num_temp_flag = 0;
    //number of hard clause, soft_clause
    int hard_clause_num, soft_clause_num;

    //number of numbered hard clause, soft_clause
    int hard_clause_numbered = 0, soft_clause_numbered = 0;

    ll updateClauseNum = 0;

    // #ifdef LOCAL
    // cout << "Please enter the value of K, sort:";
    // cin >> k >> sort;
    // #endif

    /*
    * Read file
    */ 
    string fileString;
    // fstream in("V4.wcnf", ios::in);
    fstream in(argv[1]);
    if(!in) {
        cout << "Read file error!" << endl;
    }
    while(getline(in, fileString)) {
        if(fileString[0] == 'c'){
            continue;
        }else if(fileString[0] == 'p'){
            std::vector<string> res = Split(fileString, " ");
            int len = res.size();

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

    /*
    * hard_clause
    */
    #ifdef LOCAL
    puts("-------------------------");
    #endif
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
        #ifdef LOCAL
        cout << "hard_clause_numbered_temp: " << endl;
        for(int j = 0; j < hard_clause_numbered_temp.size(); j++){
            cout << hard_clause_numbered_temp[j] << " ";
        }
        puts("");
        #endif

        int cnt = 0;
        #ifdef LOCAL
        cout << "hard_clause : " << endl;
        #endif
        for(int j = 0; j < k; j++){
            for(int x = 0; x < hard_clause_numbered_temp.size(); x++) {
                if( (x - cnt) % k == 0){
                    #ifdef LOCAL
                    cout << hard_clause_numbered_temp[x] << " ";
                    #endif

                    cnt = x;
                    int temp = hard_clause_numbered_temp[x];
                    hard_clause_numbered_vector[hard_clause_numbered].push_back(temp);
                }
            }
            cnt++;
            hard_clause_numbered++;
            #ifdef LOCAL
            puts("");
            #endif
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
        #ifdef LOCAL
        cout << "soft_clause_numbered_temp: " << endl;
        #endif
        for(int j = 0; j < soft_clause_numbered_temp.size(); j++){
            #ifdef LOCAL
            cout << soft_clause_numbered_temp[j] << " ";
            #endif

            int temp = soft_clause_numbered_temp[j];
            soft_clause_numbered_vector[soft_clause_numbered].push_back(temp);
        }
        soft_clause_numbered++;
        #ifdef LOCAL
        puts("");
        #endif
    }

    /*
    * SortVertex
    */
    #ifdef LOCAL
    puts("-------------------------");
    #endif
    if(sort == 1){
        sortVertex = SortVertexFunc1(ver, hard_clause_num);
    }
    #ifdef LOCAL
    cout << "SortVertex:" << endl;
    for(int i = 0; i < sortVertex.size();i++){
        cout << sortVertex[i] << " ";
    }
    #endif
    for(int i = 0; i < sortVertex.size(); i++) {
        int temp1 = sortVertex[i];
        int temp2;
        for(int j = 1; j <= k; j++) {
            temp2 = numberedVertex[temp1][j];
            sortNumberedVertexMatrix[i + 1][j] = temp2;
        }
    }
    #ifdef LOCAL
    cout << "\nSortNumberedVertexMatrix:" << endl;;
    for(int i = 1; i <= ver; i++) {
        for(int j = 1; j <= k; j++) {
            cout << sortNumberedVertexMatrix[i][j] << " ";
        }
        puts("");
    }
    #endif
    
    for(int i = 1;i <= k;i++){
        for(int j = 1;j <= k;j++){
            if(i < j){
                deleteVertex.push_back(sortNumberedVertexMatrix[i][j]);
                sortNumberedVertexMatrix[i][j] = 0;
            }
        }
    }
    #ifdef LOCAL
    cout << "Changed sortNumberedVertexMatrix:" << endl;
    for(int i = 1; i <= ver; i++) {
        for(int j = 1; j <= k; j++) {
            if(sortNumberedVertexMatrix[i][j]){
                cout << sortNumberedVertexMatrix[i][j] << " ";
            }
        }
        puts("");
    }
    #endif
    
    int num2 = 1, num3 = 1;
    for(int i = 1; i <= ver; i++) {
        for(int j = 1; j <= k; j++) {
            if(count(deleteVertex.begin(), deleteVertex.end(), num2) == 0){
                updateNumberedVertex[i][j] = num3;
                num3++;
            }
            num2++;
        }
    }
    #ifdef LOCAL
    puts("-------------------------");
    cout << "updateNumberedVertex:" << endl;
    for(int i = 1; i <= ver; i++) {
        for(int j = 1; j <= k; j++) {
            cout << updateNumberedVertex[i][j] << " ";
        }
        puts("");
    }
    #endif

    /*
    * DeleteVertex
    */
    #ifdef LOCAL
    puts("-------------------------");
    cout << "DeleteVertex:" << endl;
    for(int i = 0;i < deleteVertex.size();i++){
        cout << deleteVertex[i] << " ";
    }
    puts("");
    cout << "Now clause:" << endl;
    #endif
    for(int i = 0; i < hard_clause_numbered; i++){
        for(int j = 0; j < hard_clause_numbered_vector[i].size(); j++){
            #ifdef LOCAL
            cout << hard_clause_numbered_vector[i][j] << " ";
            #endif

            int temp = hard_clause_numbered_vector[i][j];
            for(int x = 0;x < deleteVertex.size();x++){
                if(abs(temp) == deleteVertex[x]){
                    if(temp > 0){
                        hard_clause_numbered_vector[i][j] = 0;
                    }else if(temp < 0){
                        deleteVertexRow.insert(i);
                    }
                }
            }
        }
        #ifdef LOCAL
        puts("");
        #endif
    }
    #ifdef LOCAL
    puts("");
    #endif
    for(int i = 0; i < soft_clause_numbered; i++){
        for(int j = 0; j < soft_clause_numbered_vector[i].size(); j++){
            #ifdef LOCAL
            cout << soft_clause_numbered_vector[i][j] << " ";
            #endif

            int temp = soft_clause_numbered_vector[i][j];
            for(int x = 0;x < deleteVertex.size();x++){
                if(abs(temp) == deleteVertex[x]){
                    soft_clause_numbered_vector[i][j] = 0;
                }
            }
        }
        #ifdef LOCAL
        puts("");
        #endif
    }
    
    /*
    * Calculate updateClauseNum, the size of the updateVertexSet
    */
    for(int i = 0; i < soft_clause_numbered; i++){
        int putFlag = 0;
        for(int j = 0; j < soft_clause_numbered_vector[i].size(); j++){
            if(soft_clause_numbered_vector[i][j] != 0){
                int ans;

                //renumber the vertex
                int temp = abs(soft_clause_numbered_vector[i][j]);
                int line = temp / k + 1, row = temp % k;
                if(row != 0){
                    ans = updateNumberedVertex[line][row];
                }else{
                    ans = updateNumberedVertex[line - 1][k];
                }

                updateVertexSet.insert(abs(ans));
                putFlag = 1;
            }
        }
        if(putFlag == 1){
            updateClauseNum++;
        }
    }
    for(int i = 0; i < hard_clause_numbered; i++){
        if(deleteVertexRow.count(i) == 0){
            int putFlag = 0;
            for(int j = 0; j < hard_clause_numbered_vector[i].size(); j++){
                if(hard_clause_numbered_vector[i][j] != 0){
                    int ans;

                    //renumber the vertex
                    int temp = abs(hard_clause_numbered_vector[i][j]);
                    int line = temp / k + 1, row = temp % k;
                    if(row != 0){
                        ans = updateNumberedVertex[line][row];
                    }else{
                        ans = updateNumberedVertex[line - 1][k];
                    }
                
                    updateVertexSet.insert(abs(ans));
                    putFlag = 1;
                }
            }
            if(putFlag == 1){
                updateClauseNum++;
            }
        }
    }
    
    /*
    * Output
    */
    #ifdef LOCAL
    puts("-------------------------");
    cout << "Update clause: " << endl;
    #endif
    cout << "p wcnf " << updateVertexSet.size() << " " << updateClauseNum << " " << hard_clause_weight << endl;
    //soft clause
    for(int i = 0; i < soft_clause_numbered; i++){
        int putEndFlag = 0, putFirstFlag = 0;
        for(int j = 0; j < soft_clause_numbered_vector[i].size(); j++){
            if(soft_clause_numbered_vector[i][j] != 0){
                if(putFirstFlag == 0){
                    cout << "1 ";
                    putFirstFlag = 1;
                }

                //renumber the vertex
                int temp = abs(soft_clause_numbered_vector[i][j]);
                int line = temp / k + 1, row = temp % k;
                if(row != 0){
                    if(soft_clause_numbered_vector[i][j] > 0){
                        cout << updateNumberedVertex[line][row] << " ";
                    }else{
                        cout << -updateNumberedVertex[line][row] << " ";
                    }
                }else{
                    if(soft_clause_numbered_vector[i][j] > 0){
                        cout << updateNumberedVertex[line - 1][k] << " ";
                    }else{
                        cout << -updateNumberedVertex[line - 1][k] << " ";
                    }
                }
   
                putEndFlag = 1;
            }
        }
        if(putEndFlag == 1){
            cout << "0";
            puts("");
        }
    }
    //hard clause
    for(int i = 0; i < hard_clause_numbered; i++){
        if(deleteVertexRow.count(i) == 0){
            int putEndFlag = 0, putFirstFlag = 0;
            for(int j = 0; j < hard_clause_numbered_vector[i].size(); j++){
                if(hard_clause_numbered_vector[i][j] != 0){
                    if(putFirstFlag == 0){
                        cout << hard_clause_weight << " ";
                        putFirstFlag = 1;
                    }

                    //renumber the vertex
                    int temp = abs(hard_clause_numbered_vector[i][j]);
                    int line = temp / k + 1, row = temp % k;
                    if(row != 0){
                        if(hard_clause_numbered_vector[i][j] > 0){
                            cout << updateNumberedVertex[line][row] << " ";
                        }else{
                            cout << -updateNumberedVertex[line][row] << " ";
                        }
                    }else{
                        if(hard_clause_numbered_vector[i][j] > 0){
                            cout << updateNumberedVertex[line - 1][k] << " ";
                        }else{
                            cout << -updateNumberedVertex[line - 1][k] << " ";
                        }
                    }

                    putEndFlag = 1;
                }
            }
            if(putEndFlag == 1){
                cout << "0";
                puts("");
            }
        }
    }

    // cout << "over!" << endl;
    // system("pause");
    return 0;
}