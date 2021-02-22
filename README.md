<!--
 * @Author: Lili Liang
 * @Date: 2021-02-07 00:29:19
 * @LastEditTime: 2021-02-22 23:27:44
 * @LastEditors: Please set LastEditors
 * @Description: Lili Liang
 * @FilePath: \Paper_3\PM-Coding\README.md
-->
# PM-Coding

### 1 服务器地址

```
/home/zhoujp/liangll/PM_Coding
```

### 2 执行方式
#### 2.1 编译
```
g++ -std=c++11 PM-Coding.cpp -o PM-Coding
```

#### 2.2 运行
```
./PM-Coding XXX.XXX k 1
```
- `XXX.XXX` : 输入文件
- `k` : 拓展变量个数
- `1` : 第一种 `顶点排序方法`，目前暂定为 `1`

### 3 变量编号举例
#### 3.1 输入文件
- V2.wcnf 
- k = 3
```
p wcnf 4 5 20
20 1 3 0
20 -2 -3 -4 0
1 -1 2 0
1 -2 0
1 -3 0
```

#### 3.2 执行
```
./PM-Coding V2.wcnf 3 1
```

#### 3.3 编号
- 变量拓展
  ```
    X11 X12 X13     1  2  3
    X21 X22 X23     4  5  6
    X31 X32 X33     7  8  9
    X41 X42 X43     10 11 12
  ```

- hard clause
    ```
    X11 ∨ X31                  1  7
    X12 ∨ X32                  2  8
    X13 ∨ X33                  3  9
    ㄱX21 ∨ ㄱX31 ∨ ㄱX41     -4 -7 -10
    ㄱX22 ∨ ㄱX32 ∨ ㄱX42     -5 -8 -11
    ㄱX23 ∨ ㄱX33 ∨ ㄱX43     -6 -9 -12
    ```

- soft clause
    ```
    ㄱX11 ∨ ㄱX12 ∨ ㄱX13 ∨ X21 ∨ X22 ∨ X23    -1 -2 -3 4 5 6 
    ㄱX21 ∨ ㄱX22 ∨ ㄱX23                         -4 -5 -6
    ㄱX31                                          -6     
    ```

#### 3.4 变量排序
- `{3, 1, 2, 4}`

- ```
    X31 X32 X33     
    X11 X12 X13     
    X21 X22 X23       
    X41 X42 X43     
  ```
-  `X32 = X33 = X13 = 0`
- 对拓展变量重新编号
    ```
    X11 X12         1  2  
    X21 X22 X23     3  4  5
    X31             6
    X41 X42 X43     7  8  9
    ```

#### 3.5 求解结果
- hard clause
    ```
    X11 ∨ X31                  1  6
    X12                         2
    ㄱX21 ∨ ㄱX31 ∨ ㄱX41     -3 -6 -7     
    ```

- soft clause
    ```
    ㄱX11 ∨ ㄱX12 ∨ X21 ∨ X22 ∨ X23   -1 -2 3 4 5 
    ㄱX21 ∨ ㄱX22 ∨ ㄱX23               -3 -4 -5
    ㄱX31 ∨ ㄱX32 ∨ ㄱX33               -6
    ```

#### 3.6 输出文件
```
p wcnf 7 6 20
1 -1 -2 3 4 5 0
1 -3 -4 -5 0
1 -6 0
20 1 6 0
20 2 0
20 -3 -6 -7 0
```