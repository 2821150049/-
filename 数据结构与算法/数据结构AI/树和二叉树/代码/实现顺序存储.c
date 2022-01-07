#include <stdio.h> 
#include <stdlib.h>
/*
	树的顺序存储结构----一般只用于完全二叉树，防止内存浪费 
*/

#define MAX_SIZE 1024
char Tree_[MAX_SIZE]; 
void InitTree(char tree);
int main(){
	
	return 0;
}
void InitTree(char tree){
	for(int i=0;i<MAX_SIZE;i++){
		tree[i] = '\0';
	}
}
