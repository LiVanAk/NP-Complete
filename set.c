#include"set.h"

// 判断两个集合是否有交集
bool isEmpty(int* S1, int sz1, int* S2, int sz2){
    for(int i = 0; i != sz1; i++){
        for(int j = 0; j != sz2; j++){
            if(S1[i] == S2[j])
                return false;
        }
    }
    return true;
}

