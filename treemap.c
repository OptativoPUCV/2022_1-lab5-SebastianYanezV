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
            if (resultado == 1) 
            {
                if (aux->right == NULL)
                {
                    newNode = createTreeNode(key, value);
                    aux->right = newNode;
                    newNode->parent = aux;
                    tree->current = aux->right;
                    return;
                }
                aux = aux->right;
            }
            else
            {
                if (aux->left == NULL)
                {
                    newNode = createTreeNode(key, value);
                    aux->left = newNode;
                    newNode->parent = aux;
                    tree->current = aux->left;
                    return;
                }
                aux = aux->left;
            }
        }
    }
}

TreeNode * minimum(TreeNode * x)
{
    if (x->left == NULL) return x;

    TreeNode *aux;

    while (x != NULL)
    {
        aux = x;
        x = x->left;
    }

    return aux;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if (node == tree->root) return;

    if (node->left == NULL && node->right == NULL)
    {
        if (node == node->parent->left)
        {
            node->parent->left = NULL;
            free(node);
        }
        if (node == node->parent->right)
        {
            node->parent->right = NULL;
            free(node);
        }
        return;
    }

    if (node->left != NULL && node->right == NULL)
    {
        if (node == node->parent->left)
        {
            node->parent->left = node->left;
            node->left->parent = node->parent;
            free(node);
        }
        if (node == node->parent->right)
        {
            node->parent->right = node->left;
            node->left->parent = node->parent;
            free(node);
        }
        return;
    }
    else
    {
        if (node == node->parent->left)
        {
            node->parent->left = node->right;
            node->right->parent = node->parent;
            free(node);
        }
        if (node == node->parent->right)
        {
            node->parent->right = node->right;
            node->right->parent = node->parent;
            free(node);
        }
        return;
    }

    if (node->left != NULL && node->right != NULL)
    {
        TreeNode *aux = minimum(node->right);
        node->pair->key = aux->pair->key;
        node->pair->value = aux->pair->value;
        removeNode(tree, aux);
        return;
    }
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


Pair * upperBound(TreeMap * tree, void* key) 
{    
    Pair *pairBuscado = searchTreeMap(tree, key);

    if (pairBuscado != NULL) return pairBuscado;

    /*TreeNode *aux = tree->root;
    TreeNode *ubNode = aux;
    int resultado;

    while (aux != NULL)
    {
        resultado = tree->lower_than(key, aux->pair->key);
        if (resultado == 1)
        {
            resultado = tree->lower_than(aux->pair->key, ubNode->pair->key);

            if (resultado == 1)
            {
                ubNode = aux;
            }
        }
    }*/

    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode *aux = minimum(tree->root);
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    TreeNode *aux;
    TreeNode *currentAux;
    int resultado;

    if (tree->current->right != NULL)
    {
        aux = minimum(tree->current->right);
        tree->current = aux;
        return aux->pair;
    }
    else
    {
        currentAux = tree->current;
        aux = currentAux->parent;

        while (1)
        {
            resultado = tree->lower_than(aux->pair->key, currentAux->pair->key);

            if (resultado == 1) 
            {
                tree->current = aux;
                return aux->pair;
            }

            aux = aux->parent;
        }
    }
    return NULL;
}
