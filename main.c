#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

struct Item {
    char *itemName;
    int itemNum;
    struct Item *previous;
    struct Item *next;
};

struct Person {
    char *name;
    char *location;
    struct Person *previous;
    struct Person *next;
};

char forbiddenWords[3][7] = { "NOBODY", "NOTHING", "NOWHERE"};  // These words cannot be used inside a sentence
char keywords[16][5] = {"sell", "buy", "go", "to", "from", "and", "at", "has", "if",
                        "less", "more", "than", "exit", "where", "total", "who"};  // Used for parsing

// Check if a given entity name is valid
int isValidEntityName(char *word);

// Check if a word is a keyword
int isKeyword(char *word);

// Check if a word is forbidden
int isForbiddenWord(char *word);

// Add a new person
void addToPersonList(struct Person *tail, struct Person *newPerson);

// Add a new item
void addToItemList(struct Item *tail, struct Item *newItem);

int main() {
    struct Person *head = NULL;
    struct Person *tail = NULL;
    (*head).next = tail;

    char line[1025];

    while (1) {
        printf(">> ");
        fflush(stdout);
        int isInvalid = false;  // To pass to the next while iteration

        if (fgets(line, 1025, stdin) == NULL) {
            break;
        }
        if (strcmp(line, "exit\n") == 0) {
            break;
        }

        // Store words of the current line in array
        char *t;
        int wordCount = 0;
        int maxWordCount = 512;
        char *words[maxWordCount];
        for(t = strtok(line, " \n"); t != NULL; t = strtok(NULL, " \n")) {
            words[wordCount] = t;
            wordCount++;
        }

        struct Person *dummy = NULL;
        (*dummy).name = "DUMMY";
        (*dummy).location = "BOUN";

        addToPersonList(tail, dummy);

        // Check whether first word is "who"
        if(strcmp(words[0], "who") == 0) {
            if(strcmp(words[1], "at") != 0) {
                printf("INVALID\n");
                continue;
            }

            char *locationName = words[2];
            if(isKeyword(locationName) == 0 || isForbiddenWord(locationName) == 0) {
                printf("INVALID\n");
                continue;
            }

            // Location is valid
            int locationFound = false;

            struct Person *tmp = (*head).next;
            while((*tmp).next != tail) {
                if(strcmp((*tmp).location, locationName) == 0) {
                    locationFound = true;
                    printf("%s\n", (*tmp).name);
                    break;
                }
            }

            if(locationFound == false) {
                printf("NOBODY\n");
            }

            continue;
        }


    }

    return 0;
}

int isValidEntityName(char *word) {
    for(int j = 0; j < sizeof(*word) - 1; j++) {
        // Subject names can only include lowercase, uppercase or underscore
        if((64 < word[j] && word[j] < 91) || (96 < word[j] && word[j] < 123) || word[j] == 95) {
            continue;
        }
        else {
            return false;
        }
    }

    return true;
}

int isKeyword(char *word) {
    for(int i = 0; i < sizeof(keywords) / sizeof(char *); i++) {
        if(strcmp(word, keywords[i]) == 0) {
            return true;
        }
    }

    return false;
}

int isForbiddenWord(char *word) {
    for(int i = 0; i < 3; i++) {
        if(strcmp(word, forbiddenWords[i]) == 0) {
            return true;
        }
    }

    return false;
}

void addToPersonList(struct Person *tail, struct Person *newPerson) {
    (*newPerson).next = tail;
    (*(*tail).previous).next = newPerson;
    (*newPerson).previous = (*tail).previous;
    (*tail).previous = newPerson;
}

void addToItemList(struct Item *tail, struct Item *newItem) {
    (*newItem).next = tail;
    (*(*tail).previous).next = newItem;
    (*newItem).previous = (*tail).previous;
    (*tail).previous = newItem;
}
