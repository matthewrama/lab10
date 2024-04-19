/*
Matthew Ramaswami
Lab 10
0027
18 April 2024*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

/*
Creating trie structure 
having a pointer to children
integer for endof the word
and counter integer
*/
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
};

/*
Allocate memeory for a trie
if allocating is successful set the end of word and count variables to 0,
then set the children to null
return the trie node*/
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->isEndOfWord = 0;
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }
    return node;
}

// Inserts a word into the Trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->isEndOfWord = 1;
    current->count++;
}

/*
setting the current node to the root node
iterate through the word until NULL is encountered
set the index to be the front
if the word sis not found, reutrn 0
set the current to the current child's index
return the dang thang*/
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!current->children[index])
            return 0;
        current = current->children[index];
    }
    return (current != NULL && current->isEndOfWord) ? current->count : 0;
}

/*
Taking the root as a parameter,
if the root is not found, return because the task has been delt with
if the root is found, iterate through the alphabet,
deallocating the root's children upon the current iteration, freeing the root*/
void deallocateTrie(struct TrieNode *root) {
    if (!root)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        deallocateTrie(root->children[i]);
    free(root);
}

//taking the filename and pointer to inputted words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r"); //file is used for reading
    if (!file) {
        printf("Error opening file.\n");
        exit(1);
    }

    int numWords = 0; //declaring and initializing number of words to 0
    char word[100]; // Assuming maximum word length is 100
    while (fscanf(file, "%s", word) != EOF) { //ipput of words
        pInWords[numWords] = strdup(word); //duplicating words and setting it to the pointer to words
        numWords++; //increasing the number of wrods by 1 per iteration
    }

    fclose(file);//close it up!
    return numWords; //returning that thang
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *root = createNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }

    // Test with sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    deallocateTrie(root);
    return 0;
}
