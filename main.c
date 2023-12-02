#include <stdio.h>
#include <stdbool.h>
#include <stdint-gcc.h>

#define ROOT 0
#define TREE_SIZE 100



struct Leaf{

    uint64_t left;
    uint64_t right;

    int32_t value;

};


struct Leaf tree[TREE_SIZE];
uint32_t treeSize = 0;


bool addValue(int32_t value){

    uint64_t cmpLeaf = ROOT;

    if(treeSize >= TREE_SIZE)return false;

    while (true){

        if(tree[cmpLeaf].value < value){

            if(tree[cmpLeaf].left == ROOT){

                tree[cmpLeaf].left = treeSize;
                tree[treeSize++].value = value;

                return true;

            } else cmpLeaf = tree[cmpLeaf].left;

        }else if (tree[cmpLeaf].value > value){

            if(tree[cmpLeaf].right == ROOT){

                tree[cmpLeaf].right = treeSize;
                tree[treeSize++].value = value;

                return true;

            } else cmpLeaf = tree[cmpLeaf].right;

        }else{

            return false;

        }

    }

}



void printTree(int32_t levelDeep){

    #define LEVEL_BUFFER_SIZE 2

    uint32_t levelBuffer[LEVEL_BUFFER_SIZE][TREE_SIZE] = {{ROOT},{ROOT}};

    for (int32_t i = levelDeep; i > ROOT; --i) {

        for (int32_t j = 0; j < 1 << (i - 1); ++j)printf(" ");

        for (int32_t j = 0; j < 1 << (levelDeep - i); ++j){

            if(levelBuffer[i & 1][j] == 0 && levelDeep != i){

                levelBuffer[(~i) & 1][ j << 1 ]     = 0;
                levelBuffer[(~i) & 1][(j << 1) | 1] = 0;

                printf("n");

            }else{

                levelBuffer[(~i) & 1][ j << 1 ]     = tree[levelBuffer[i & 1][j]].left;
                levelBuffer[(~i) & 1][(j << 1) | 1] = tree[levelBuffer[i & 1][j]].right;

                printf("%d", tree[levelBuffer[i & 1][j]].value);

            }

            for (uint32_t k = 0; k < (1 << i) - 1; ++k)printf(" ");

        }

        printf("\n");

    }

}




int main() {

    addValue(6);
    addValue(1);
    addValue(0);
    addValue(7);
    addValue(2);
    addValue(8);
    addValue(9);
    addValue(3);

    printTree(6);

    return 0;
}
