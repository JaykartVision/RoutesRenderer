#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BST.h"
#include <string.h>

typedef struct FlashCard {
	char marker;
	char* frontSide;
	char* backSide;
}FlashCard;

typedef struct Container {
	int frequency;
	int number;
	Tree* flashCards;
}Container;

typedef struct ClassContainers {
	int countCont;
	int countCard;
	int step;
	Container** containers;
}ClassContainers;

TreeItem* CreateItem(void* inputData, void* key, size_t sizeofItem);

void RecFree(TreeItem* inputItem, void (*destroyData)(void* inputData));

void RecSize(TreeItem* inputItem, int* size);

void RecForeach(TreeItem* inputItem, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3);

void RecForeachKey(Tree* inputTree, void* inputKey, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3);

TreeItem* MaxSearch(Tree* inputTree, TreeItem* inputItem, TreeItem* compareItem);

TreeItem* MinSearch(Tree* inputTree, TreeItem* inputItem, TreeItem* compareItem);

void* ParentSearch(Tree* inputTree, TreeItem* inputItem, int* parentCompare);

Tree* BstCreate(CmpFunc cmpFunc, size_t sizeofItem)
{
	if (cmpFunc == 0) return NULL;
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if (tree == NULL) return NULL;
	tree->root = NULL;
	tree->cmpFunc = cmpFunc;
	tree->sizeofItem = sizeofItem;
	return tree;
}

void BstClear(Tree* inputTree, void (*destroyData)(void* inputData))
{
	Tree* tree = (Tree*)inputTree;
	RecFree(tree->root, destroyData);
	tree->root = NULL;
	tree->cmpFunc = NULL;
}

void BstDestroy(Tree* inputTree, void (*destroyData)(void* inputData))
{
	Tree* tree = (Tree*)inputTree;
	BstClear(tree, destroyData);
	free(tree);
	tree = NULL;
}

int BstSize(Tree* inputTree)
{
	if (inputTree == NULL) return -1;
	Tree* tree = (Tree*)inputTree;
	if (tree == NULL) return -1;
	int size = 0;
	int* sizePtr = &size;
	if (tree->root == NULL) return 0;
	TreeItem* bufer = tree->root;
	if (bufer == NULL) return -1;
	RecSize(bufer, sizePtr);
	return size;
}

void* BstFind(Tree* inputTree, void* key)
{
	if (inputTree == NULL) return NULL;
	Tree* tree = (Tree*)inputTree;
	if (tree == NULL) return NULL;
	if (tree->root == NULL) return NULL;
	TreeItem* bufer = tree->root;
	while (bufer != NULL)
	{
		int compare = tree->cmpFunc(key, bufer->key);
		if (compare == 2)
		{
			return bufer->data;
		}
		else
		{
			if (compare == 1)
			{
				bufer = bufer->less;
			}
			if (compare == 3)
			{
				bufer = bufer->more;
			}
		}
	}
	return NULL;
}

void* BstFindItem(Tree* inputTree, void* key)
{
	if (inputTree == NULL) return NULL;
	Tree* tree = (Tree*)inputTree;
	if (tree == NULL) return NULL;
	if (tree->root == NULL) return NULL;
	TreeItem* bufer = tree->root;
	while (bufer != NULL)
	{
		int compare = tree->cmpFunc(key, bufer->key);
		if (compare == 2)
		{
			return bufer;
		}
		else
		{
			if (compare == 1)
			{
				bufer = bufer->less;
			}
			if (compare == 3)
			{
				bufer = bufer->more;
			}
		}
	}
	return NULL;
}

void* BstInsert(Tree* inputTree, void* inputData, void* key)
{
	if (inputTree == NULL) return NULL;
	if (inputData == NULL) return NULL;
	if (key == NULL) return NULL;
	Tree* tree = (Tree*)inputTree;
	if (tree == NULL) return NULL;
	if (tree->root == NULL)
	{
		tree->root = CreateItem(inputData, key, tree->sizeofItem);
		return NULL;
	}
	else
	{
		TreeItem* bufer = tree->root;
		void* returnData = NULL;
		if (bufer != NULL)
		{
			while (1)
			{
				int compare = tree->cmpFunc(key, bufer->key);
				if (compare == 2)
				{
					returnData = bufer->data;
					memcpy(bufer->data, inputData, tree->sizeofItem);
					return returnData;
				}
				else
				{
					if (compare == 1)
					{
						if (bufer->less == NULL)
						{
							bufer->less = CreateItem(inputData, key, tree->sizeofItem);
							return NULL;
						}
						bufer = bufer->less;
					}
					if (compare == 3)
					{
						if (bufer->more == NULL)
						{
							bufer->more = CreateItem(inputData, key, tree->sizeofItem);
							return NULL;
						}
						bufer = bufer->more;
					}
				}
			}
		}
	}
	return NULL;
}

void* BstDelete(Tree* inputTree, void* key)
{
	if (inputTree == NULL) return NULL;
	Tree* tree = (Tree*)inputTree;
	if (tree == NULL) return NULL;
	if (key == NULL) return NULL;
	if (tree->root == NULL) return NULL;
	TreeItem* bstFind = tree->root;
	void* value = NULL;
	int count = 0;
	while (bstFind != NULL)
	{
		int compare = tree->cmpFunc(key, bstFind->key);
		if (compare == 2)
		{
			value = malloc(tree->sizeofItem);
			memcpy(value, bstFind->data, tree->sizeofItem);
			break;
		}
		else
		{
			if (compare == 1)
			{
				bstFind = bstFind->less;
				count = 1;
			}
			if (compare == 3)
			{
				bstFind = bstFind->more;
				count = 1;
			}
		}
	}
	if (bstFind == NULL) return NULL;
	int parentCompare = 0;
	int* ptrParentCompare = &parentCompare;
	if ((bstFind->less == NULL) && (bstFind->more == NULL))
	{
		if (count == 0)
		{
			tree->root = NULL;
		}
		else
		{
			TreeItem* revFind = (TreeItem*)ParentSearch(inputTree, bstFind, ptrParentCompare);
			if (parentCompare == 1)
			{
				revFind->less = NULL;
			}
			if (parentCompare == 3)
			{
				revFind->more = NULL;
			}
		}
		free(bstFind->key);
		free(bstFind->data);
		free(bstFind);
		return value;
	}
	if ((bstFind->less == NULL) && (bstFind->more != NULL))
	{
		if (count == 0)
		{
			tree->root = bstFind->more;
		}
		else
		{
			TreeItem* revFind = (TreeItem*)ParentSearch(inputTree, bstFind, ptrParentCompare);
			if (parentCompare == 1)
			{
				revFind->less = bstFind->more;
			}
			if (parentCompare == 3)
			{
				revFind->more = bstFind->more;
			}
		}
		free(bstFind->key);
		free(bstFind->data);
		free(bstFind);
		return value;
	}
	if ((bstFind->less != NULL) && (bstFind->more == NULL))
	{
		if (count == 0)
		{
			tree->root = bstFind->less;
		}
		else
		{
			TreeItem* revFind = (TreeItem*)ParentSearch(inputTree, bstFind, ptrParentCompare);
			if (parentCompare == 1)
			{
				revFind->less = bstFind->less;
			}
			if (parentCompare == 3)
			{
				revFind->more = bstFind->less;
			}
		}
		free(bstFind->key);
		free(bstFind->data);
		free(bstFind);
		return value;
	}
	if ((bstFind->less != NULL) && (bstFind->more != NULL))
	{
		TreeItem* maxChild = bstFind->less;
		MaxSearch(inputTree, bstFind->less, maxChild);
		TreeItem* ParentChild = ParentSearch(inputTree, maxChild, &parentCompare);
		memcpy(bstFind->key, maxChild->key, sizeof(maxChild->key));
		memcpy(bstFind->data, maxChild->data, sizeof(maxChild->data));
		if (parentCompare == 1)
		{
			ParentChild->less = maxChild->less;
		}
		if (parentCompare == 3)
		{
			ParentChild->more = maxChild->less;
		}
		free(maxChild->data);
		free(maxChild->key);
		free(maxChild);
		return value;
	}
	return NULL;
}

void BstForeach(Tree* inputTree, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3)
{
	Tree* tree = (Tree*)inputTree;
	if ((tree->root != NULL) && (foreachFunc != NULL))
	{
		RecForeach(tree->root, foreachFunc, extraData1, extraData2, extraData3);
	}
}

void BstForeachKey(Tree* inputTree, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3)
{
	Tree* tree = (Tree*)inputTree;
	if ((tree->root != NULL) && (foreachFunc != NULL))
	{
		RecForeachKey(tree, tree->root->key, foreachFunc, extraData1, extraData2, extraData3);
	}
}

void RecFree(TreeItem* inputItem, void (*destroyData)(void* inputData))
{
	if (inputItem != NULL)
	{
		TreeItem* bufer = inputItem;
		if (bufer != NULL)
		{
			if (bufer->less != NULL)
				RecFree(bufer->less, destroyData);
			if (bufer->more != NULL)
				RecFree(bufer->more, destroyData);
			if (destroyData != NULL) destroyData(bufer->data);
			free(bufer);
		}
	}
}

void RecSize(TreeItem* inputItem, int* size)
{
	if (inputItem != NULL)
	{
		*size = *size + 1;
		TreeItem* bufer = inputItem;
		if (bufer != NULL)
		{
			if (bufer->less != NULL)
			{
				RecSize(bufer->less, size);
			}
			if (bufer->more != NULL)
			{
				RecSize(bufer->more, size);
			}
		}
	}
}

void RecForeach(TreeItem* inputItem, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3)
{
	if (inputItem != NULL)
	{
		TreeItem* less = NULL;
		TreeItem* more = NULL;
		if (inputItem->less != NULL) less = inputItem->less;
		if (inputItem->more != NULL) more = inputItem->more;
		foreachFunc(extraData1, extraData2, extraData3, inputItem->data, inputItem->key);
		if (less != NULL) RecForeach(less, foreachFunc, extraData1, extraData2, extraData3);
		if (more != NULL) RecForeach(more, foreachFunc, extraData1, extraData2, extraData3);
	}
}

void RecForeachKey(Tree* inputTree, void* inputKey, void (*foreachFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey), void* extraData1, void* extraData2, void* extraData3)
{
	TreeItem* item = BstFindItem(inputTree, inputKey);
	if (item != NULL)
	{
		void* lessKey = NULL;
		void* moreKey = NULL;
		if (item->less != NULL) lessKey = item->less->key;
		if (item->more != NULL) moreKey = item->more->key;
		foreachFunc(extraData1, extraData2, extraData3, item->data, item->key);
		if (lessKey != NULL) RecForeachKey(inputTree, lessKey, foreachFunc, extraData1, extraData2, extraData3);
		if (moreKey != NULL) RecForeachKey(inputTree, moreKey, foreachFunc, extraData1, extraData2, extraData3);
	}
}

TreeItem* MaxSearch(Tree* inputTree, TreeItem* inputItem, TreeItem* compareItem)
{
	if ((inputItem != NULL) && (compareItem != NULL))
	{
		if (inputTree->cmpFunc(inputItem->key, compareItem->key) == 3)
		{
			compareItem = inputItem;
		}
		if (inputItem->less != NULL)
		{
			compareItem = MaxSearch(inputTree, inputItem->less, compareItem);
		}
		if (inputItem->more != NULL)
		{
			compareItem = MaxSearch(inputTree, inputItem->more, compareItem);
		}
	}
	return compareItem;
}

TreeItem* MinSearch(Tree* inputTree, TreeItem* inputItem, TreeItem* compareItem)
{
	if ((inputItem != NULL) && (compareItem != NULL))
	{
		if (inputTree->cmpFunc(inputItem->key, compareItem->key) == 1)
		{
			compareItem = inputItem;
		}
		if (inputItem->less != NULL)
		{
			compareItem = MinSearch(inputTree, inputItem->less, compareItem);
		}
		if (inputItem->more != NULL)
		{
			compareItem = MinSearch(inputTree, inputItem->more, compareItem);
		}
	}
	return compareItem;
}

void* ParentSearch(Tree* inputTree, TreeItem* inputItem, int* parentCompare)
{
	if (inputTree == NULL) return NULL;
	if (inputItem == NULL) return NULL;
	Tree* tree = (Tree*)inputTree;
	if (tree == NULL) return NULL;
	TreeItem* bufer = tree->root;
	while (bufer != NULL)
	{
		//printf("STEP1\n");
		if ((bufer->less != NULL) && (tree->cmpFunc(bufer->less->key, inputItem->key) == 2))
		{
			*parentCompare = 1;
			return bufer;
		}
		if ((bufer->more != NULL) && (tree->cmpFunc(bufer->more->key, inputItem->key) == 2))
		{
			*parentCompare = 3;
			return bufer;
		}
		int compare = tree->cmpFunc(inputItem->key, bufer->key);
		if (compare == 1)
		{
			bufer = bufer->less;
		}
		if (compare == 3)
		{
			bufer = bufer->more;
		}
		//printf("STEP2\n");
	}
	return NULL;
}

TreeItem* CreateItem(void* inputData, void* key, size_t sizeofItem)
{
	if (inputData == NULL) return NULL;
	if (key == NULL) return NULL;
	TreeItem* treeItem = (TreeItem*)malloc(sizeof(TreeItem));
	if (treeItem == NULL) return NULL;
	treeItem->key = malloc(sizeof(key));
	if (treeItem->key == NULL) return NULL;
	treeItem->data = malloc(sizeofItem);
	if (treeItem->data == NULL) return NULL;
	memcpy(treeItem->key, key, sizeof(key));
	memcpy(treeItem->data, inputData, sizeofItem);
	treeItem->less = NULL;
	treeItem->more = NULL;
	return treeItem;
}