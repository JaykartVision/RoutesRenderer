#ifndef _BST_H_
#define _BST_H_

typedef int (*CmpFunc)(void* inputData1, void* inputData2);

typedef struct TreeItem {
    void* key;
    void* data;
    struct TreeItem* less;
    struct TreeItem* more;
} TreeItem;

typedef struct Tree {
    TreeItem* root;
    CmpFunc cmpFunc;
    size_t sizeofItem;
} Tree;

// Create empty tree
Tree* BstCreate(CmpFunc cmpFunc, size_t sizeofItem);

// Clear tree but do not destroy tree struct
void BstClear(Tree* inputTree, void (*destroyData)(void* inputData));

// Completely destroy tree
void BstDestroy(Tree* inputTree, void (*destroyData)(void* inputData));

int BstSize(Tree* inputTree);

// Find element with equal data and return its data if any else NULL
void* BstFind(Tree* inputTree, void* key);

void* BstFindItem(Tree* inputTree, void* key);

// Return data which was replaced by this insertion if any else NULL
void* BstInsert(Tree* inputTree, void* inputData, void* key);

// Delete node with equal data and return its data if any else NULL
void* BstDelete(Tree* inputTree, void* key);

// Call foreach_func for every node's data in tree passing given extra_data
void BstForeach(Tree* inputTree, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3);

void BstForeachKey(Tree* inputTree, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3);

#endif
