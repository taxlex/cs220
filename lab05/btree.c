#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct tnode {
   struct tnode * left;
   struct tnode * right;
   int value;
};

struct tnode * makeNode(int value);
void freeTree(struct tnode * t);

void insertVal(struct tnode * t, int value);
void prLVR(struct tnode * t);
void prRVL(struct tnode * t);
void printTree(struct tnode * t, char * prefix);

int i;

int main(int argc, char **argv) {
   int i;

   if (argc<2) {
		printf("You must specify at least one argument to %s\n",argv[0]);
		return 1;
	}
	struct tnode * root=makeNode(atoi(argv[1]));
   for(i=2; i<argc; i++) {
      int val=atoi(argv[i]);
      insertVal(root,val);
   }
   printf("In LVR order: ");
   prLVR(root);
   printf("\nIn RVL order: ");
   prRVL(root);
   printf("\nGraphic Representation...\n");
   printTree(root,"");
   freeTree(root);
   return 0;
}

struct tnode * makeNode(int value) {
   struct tnode * t = malloc(sizeof(struct tnode));
   t->value=value;
   t->left=NULL;
   t->right=NULL;
   return t;
}

void freeTree(struct tnode * t) {
   assert(t);
   if (t->left) freeTree(t->left);
   if (t->right) freeTree(t->right);
   free(t);
}

void insertVal(struct tnode * t, int value) {
	assert(t);
	//decides if the value should go to the right or left ofthe node
	if(value <= t->value ){
		//if the node is null it makes a new node with the value
		if(t->left == NULL){
			t->left = makeNode(value);
		}
		//if the null is not null it class itself again but with the child node as argument
		else{
			insertVal(t->left,value);
		}
	}
	else if(value > t->value){
		if(t->right == NULL){
			t->right = makeNode(value);
		}
		else{
			insertVal(t->right,value);
		}
	}
}
//recursively goes to the left then prints out from left to right
void prLVR(struct tnode * t) {
	assert(t);
	if(t->left != NULL){
		prLVR(t->left);
	}
	printf("%d ",t->value);
	if(t->right != NULL){
		prLVR(t->right);
	}
}

//recursively goes to the right then prints out from right to left
void prRVL(struct tnode * t) {
	assert(t);
	if(t->right != NULL){
		prRVL(t->right);
	}
	printf("%d ",t->value);
	if(t->left != NULL){
		prRVL(t->left);
	}
}

void printTree(struct tnode * t, char * prefix) {
	assert(t);
	if(t->right != NULL){
		//appends "  |" to the prefix to be passed down to the next level
		int len = strlen(prefix);
		char str[len + 4];
		strcpy(str,prefix);
		str[len] = ' ';
		str[len+1] = ' ';
		str[len+2] = '|';
		str[len+3] = '\0';
		printTree(t->right,str);
	}
	//if the node has no children it is not printed with a '+'
	if(t->left != NULL || t->right != NULL){
		printf("%s%d%c\n",prefix,t->value,'+');
	}
	else{
		printf("%s%d \n",prefix,t->value);
	}
	if(t->left != NULL){
		//appends "  |" to the prefix to be passed down to the next level
		int len = strlen(prefix);
		char str[len + 4];
		strcpy(str,prefix);
		str[len] = ' ';
		str[len+1] = ' ';
		str[len+2] = '|';
		str[len+3] = '\0';
		printTree(t->left,str);
	}
}

