#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BST.h"

#define BUFFER_SIZE 4096

#define NUMBER_TOP_ELEMS 20
struct high_freq{
    char *data;
    int freq;
};

void initializeBST(BsTree *bst){
    bst->root = NULL;
}

BstNode* createBstNode(char* data){
    char *tmp_str = (char *)malloc(strlen(data)+1);
    if(!tmp_str){
        printf("Error: malloc() failure\n");
        return NULL;
    }
    strcpy(tmp_str, data);
    BstNode *tmp = (BstNode*)malloc(sizeof(BstNode));
    if(!tmp){
        printf("Error: malloc() failure\n");
        return NULL;
    }
    tmp->data = tmp_str;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->wordFreq = 1;
    return tmp;
}

void insert(BsTree *bst, char* data){
    if(!bst->root){
        bst->root = createBstNode(data);
        return;
    }
    BstNode *cur = bst->root;
    while(cur){
        if(strcmp(data,cur->data)<0){
            if(cur->left){
                cur = cur->left;
            } else{
                cur->left = createBstNode(data);
                break;
            }
        } else {
            if(cur->right){
                cur  = cur->right;
            } else {
                cur->right = createBstNode(data);
                break;
            }
        }
    } //end of while
}

void inorder(BstNode *node){
    if(!node){
        return;
    }
    inorder(node->left);
    printf("%s\t%d\n", node->data, node->wordFreq);
    inorder(node->right);
}
void display(BsTree *bst){
    if(!bst->root){
        printf("Info: BST is empty!!\n");
        return;
    }
    printf("The elements in the BST:\n");
    inorder(bst->root);
}
BstNode* findNode(BsTree *bst, char* data){
    if(!bst->root){
        printf("Info: BST is empty!!\n");
        return NULL;
    }
    BstNode *cur = bst->root;
    while(cur){
        if(strcmp(data, cur->data)<0)
            cur = cur->left;
        else if(strcmp(data, cur->data)>0)
            cur = cur->right;
        else{
            //printf("found node for data %d\n", data);
            return cur;
        }
    }
    return NULL;
    //printf("Not found node for data %d\n", data);
}

BstNode* inSuccessor(BstNode *node){
    BstNode* tmp = node;
    if(tmp->right){
        tmp = tmp->right;
        while(tmp->left){
            tmp = tmp->left;
        }
        return tmp;
    }    
}

int countChildren(BstNode *node){
    int count=0;
    if(node->left)
        count++;
    if(node->right)
        count++;
    return count;
}

BstNode* findParent(BsTree *bst, char* data){
    if(!bst->root){
        printf("Info: BST is empty!!\n");
        return NULL;
    }
    BstNode *cur = bst->root;
    BstNode *parent = NULL;
    while(cur){
        if(strcmp(data, cur->data)<0){
            parent = cur;
            cur = cur->left;
        }
        else if(strcmp(data, cur->data)>0){
            parent = cur;
            cur = cur->right;
        }
        else{
            //printf("found node for data %d\n", data);
            return parent;
        }
    }
    return NULL;
    //printf("Not found node for data %d\n", data);
}

void delete(BsTree* bst, char* data){
    if(!bst->root){
        printf("Info: BST is empty!!\n");
        return ;
    }
    BstNode *node = findNode(bst, data);
    BstNode* parent = findParent(bst, data);

    int children=0;
    if(node)
        children = countChildren(node);

    if(children==0){        
        BstNode* tmp = node;
        if(parent->left == node){
            parent->left = NULL;
        } else{
            parent->right = NULL;
        }
        free(tmp);
    } else if(children==1){
        BstNode *tmp = node;
        if(parent->left == node){
            if(node->left){
                parent->left = node->left;
            } else{
                parent->left = node->right;
            }
        } else {
            if(node->left){
                parent->right = node->left;                
            } else {
                parent->right = node->right;
            }
        }
        free(tmp);

    } else{ //node with 2 children
        BstNode *tmp = NULL;
        BstNode* successor = inSuccessor(node);
        BstNode* succParent = findParent(bst, successor->data);
        tmp = successor;
        if(successor->right){
            succParent->left = successor->right;
        } else{
            succParent->left = NULL;
        }
        node->data = (char *)malloc(strlen(successor->data)+1);
        strcpy(node->data, successor->data);
        free(tmp);
    }
}

void intialize_hf_words(struct high_freq arr[]){
    for(int i=0; i< NUMBER_TOP_ELEMS; i++){
        arr[i].data = NULL;
        arr[i].freq = 0;
    }
}

void insert_hf_words(BstNode *ptr, struct high_freq arr[]){
    static int max_elem=0;
    int i=0;
    if(max_elem<NUMBER_TOP_ELEMS){
        while(i<max_elem && ptr->wordFreq <arr[i].freq)
            i++;
        if(i!=max_elem){
            int j=max_elem;
            for(;j>i; j--){
                arr[j].data = arr[j-1].data;
                arr[j].freq = arr[j-1].freq;
            }            
        }
        arr[i].data = ptr->data;
        arr[i].freq = ptr->wordFreq;
        max_elem++;
    } else{
        while(i<max_elem && ptr->wordFreq < arr[i].freq)
            i++;
        if(i!=max_elem){
            int j=max_elem-1;
            for(;j>i; j--){
                arr[j].data = arr[j-1].data;
                arr[j].freq = arr[j-1].freq;
            }     
            arr[i].data = ptr->data;
            arr[i].freq = ptr->wordFreq;       
        }
        
        
    }

}
void extract_hf_words(BstNode *ptr, struct high_freq arr[]){
    if(ptr==NULL){
        return;
    }
    extract_hf_words(ptr->left, arr);
    insert_hf_words(ptr, arr);
    extract_hf_words(ptr->right, arr);
}

void print_hf_words(struct high_freq arr[]){
    for(int i=0; i< NUMBER_TOP_ELEMS; i++){
        printf("%s\t%d\n", arr[i].data, arr[i].freq);
    }
}
int main(int argc, char *argv[]){
    BsTree b1;
    initializeBST(&b1);
    char delimiters[100] = "\\/,.:;'\"-\t\n=+_{}[]? ~!@#$%^*()1234567890|";
    struct high_freq arr[NUMBER_TOP_ELEMS];
    FILE *fptr=NULL;
    if(!argv[1]){
        printf("Error: provide input filename!!");
        return -1;
    }

    fptr = fopen(argv[1],"r");
    if(!fptr){
        printf("Error: Unable to open the file!!");
        return -1;
    }
    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, fptr)!=NULL){
        for(int i=0; i<strlen(buffer); i++){
            buffer[i] = tolower(buffer[i]);
        }
        //printf("%s\n", buffer);
        char *token = strtok(buffer, delimiters);
        while(token!=NULL){
            if(strlen(token)>1){
                BstNode *bstNodePtr = findNode(&b1, token);
                if(!bstNodePtr){
                    insert(&b1, token);
                } else{
                    bstNodePtr->wordFreq++;
                }
            }
            token = strtok(NULL, delimiters);

        }
    }
    intialize_hf_words(arr);
    extract_hf_words(b1.root, arr);
    print_hf_words(arr);
    //display(&b1);
    fclose(fptr);

}
