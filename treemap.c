#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap *new = (TreeMap*) malloc(sizeof(TreeMap));
    new->lower_than = lower_than;
    new->root = NULL;
    new->current = NULL;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    TreeNode *aux = tree->root;
    TreeNode *newNode;
    int resultado;

    while (aux != NULL)
    {
        if (is_equal(tree, aux->pair->key, key) == 1) return;
        else
        {
            resultado = tree->lower_than(aux->pair->key, key);
            if (resultado == 1) aux = aux->right;
            else aux = aux->left;

            if (aux->left == NULL)
            {
                newNode = createTreeNode(key, value);
                aux->left = newNode;
                newNode->parent = aux;
                return;
            }
            if (aux->right == NULL)
            {
                newNode = createTreeNode(key, value);
                aux->right = newNode;
                newNode->parent = aux;
                return;
            }
        }
    }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    TreeNode *aux = tree->root;
    int resultado;

    while (aux != NULL)
    {
        if (is_equal(tree, aux->pair->key, key) == 1)
        {
            tree->current = aux;
            return aux->pair;
        }
        else
        {
            resultado = tree->lower_than(aux->pair->key, key);
            if (resultado == 1) aux = aux->right;
            else aux = aux->left;
        }
    }

    tree->current = aux;
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
