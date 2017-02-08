#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


typedef struct bin_t{
    struct bin_t *left;     //pointer to left node
    struct bin_t *right;    //pointer to right node
    int count;              //number of times word added to tree
    char *word;             //word contained in the node
} node;                     //Binary tree node

void insert(char newWord[], node **root);   //Adds a node to the tree
void read(FILE *fp, node **root);           //Reads the file and adds all words to the binary tree
char *getWord(FILE *fp);                    //reads the next word from the file
void printInOrder(node **root, FILE *fp);   //In order (Alphabetical) print of binary tree with word and count
char* mystrdup(const char* s);              //duplicate string function

int main(int argc, char **argv) {
    node *root = 0; //initilize tree

    //printf("Enter the name of the file to read: "); //print to screen
    char *file;                                  //initilize string for input file name
    file = argv[1];                            //File designation
    //scanf("%s", file);

    FILE *f1 = fopen(file, "r"); //input file
    FILE *f2 = fopen("myOutput.txt", "w"); //output file
    read(f1, &root); //read input to tree
    printInOrder(&root, f2); //print tree

    return 0;
}

void insert(char newWord[], node **leaf) { //Adds newword to the tree or increase the count of that word
    if (*leaf == 0) {                     //found an empty leaf - add a node with the word and count = 1
        *leaf = (node *) malloc(sizeof(node));
        (*leaf)->word = newWord;
        (*leaf)->left = 0;
        (*leaf)->right = 0;
        (*leaf)->count = 1;
    } else {                            //leaf exists
        int dif = strcmp(newWord, (*leaf)->word); //compare the word with the newword
        if (dif < 0) { //new word is smaller
            insert(newWord, &(*leaf)->left);//continue insert to left pointer
        } else if (dif > 0) {//newword is larger
            insert(newWord, &(*leaf)->right);//continue insert to right pointer
        } else if (dif == 0) { //word exists
            (*leaf)->count += 1; //increase nodes count by one
        }
    }
}


char *getWord(FILE *fp){//gets the next word from the file
    char word[100]; //holder for next word
    int ch, i=0; //ch is the next character of the word; i is the length of the word

    while(EOF!=(ch=fgetc(fp)) && !isalpha(ch)); //go to end of white space

    if(ch == EOF) //if next character is end of file - return
        return NULL;
    do{ //add the character to the word, then increase i by one
        word[i++] = tolower(ch);
    }while(EOF!=(ch=fgetc(fp)) && isalpha(ch));//while not at end of file or white space

    word[i]='\0'; //null terminate
    return mystrdup(word); //return the word
}
void read(FILE *fp, node **root){//read the file to the tree

    char *word;  //holder for word to add
    while((word=getWord(fp))!=NULL){ //whilie there are more words - get the next word
        insert(word, root); //add word to the tree
    }
    fclose(fp);//close the file
}

void printInOrder(node **root, FILE *fp){//print the tree in order (Alphabetically)
    if((*root)->left!=0){
        printInOrder(&(*root)->left, fp);
    }
    fprintf(fp, "%s: %i \n", (*root)->word, (*root)->count);
    if((*root)->right!=0){
        printInOrder(&(*root)->right, fp);
    }
}
char* mystrdup(const char* s)
{
    char* p = malloc(strlen(s)+1);
    if (p) strcpy(p, s);
    return p;
}
