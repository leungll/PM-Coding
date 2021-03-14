# PM-Coding
Solver algorithm in #3 Paper: Diversified Top-k MaxSAT Solving with MaxSAT.

![GitHub last commit](https://img.shields.io/github/last-commit/leungll/PM-Coding?color=red&style=flat-square) ![C++11](https://img.shields.io/badge/C%2B%2B11-passing-yellow) ![GitHub license](https://img.shields.io/github/license/leungll/PM-Coding?color=orange&style=flat-square) ![GitHub repo size](https://img.shields.io/github/repo-size/leungll/PM-Coding?style=flat-square)

## Server Address
```
/home/zhoujp/liangll/PM_Coding
```

## Compile & Run
### Compile
```
g++ -std=c++11 PM-Coding.cpp -o PM-Coding
```

### Run
```
./PM-Coding XXX.XXX K 1
```
- `XXX.XXX` : 输入文件
- `K` : 拓展变量个数
- `1` : 第一种 `顶点排序方法`，目前暂定为 `1`

## Example of Variable Numbering
### Input File
- V2.wcnf 
- K = 3

```
p wcnf 4 5 20
20 1 3 0
20 -2 -3 -4 0
1 -1 2 0
1 -2 0
1 -3 0
```

### Run
```
./PM-Coding V2.wcnf 3 1
```

### Number
- 变量拓展
  ```
    X11 X12 X13                                   1  2  3
    X21 X22 X23                                   4  5  6
    X31 X32 X33                                   7  8  9
    X41 X42 X43                                   10 11 12
  ```

- Hard Clause
    ```
    X11 ∨ X31                                     1  7
    X12 ∨ X32                                     2  8
    X13 ∨ X33                                     3  9
    ㄱX21 ∨ ㄱX31 ∨ ㄱX41                        -4 -7 -10
    ㄱX22 ∨ ㄱX32 ∨ ㄱX42                        -5 -8 -11
    ㄱX23 ∨ ㄱX33 ∨ ㄱX43                        -6 -9 -12
    ```

- Soft Clause
    ```
    ㄱX11 ∨ ㄱX12 ∨ ㄱX13 ∨ X21 ∨ X22 ∨ X23    -1 -2 -3 4 5 6 
    ㄱX21 ∨ ㄱX22 ∨ ㄱX23                         -4 -5 -6
    ㄱX31 ∨ ㄱX32 ∨ ㄱX33                         -7 -8 -9    
    ```

### Variable Ordering
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

### Result
- Hard Clause
    ```
    X11 ∨ X31                                     1  6
    X12                                            2
    ㄱX21 ∨ ㄱX31 ∨ ㄱX41                        -3 -6 -7     
    ```

- Soft Clause
    ```
    ㄱX11 ∨ ㄱX12 ∨ X21 ∨ X22 ∨ X23            -1 -2 3 4 5 
    ㄱX21 ∨ ㄱX22 ∨ ㄱX23                        -3 -4 -5
    ㄱX31                                         -6
    ```

### Output File
```
p wcnf 7 6 20
1 -1 -2 3 4 5 0
1 -3 -4 -5 0
1 -6 0
20 1 6 0
20 2 0
20 -3 -6 -7 0
```