#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct node_s node_t;
struct node_s {
  char alphabet;
  char present;
  node_t *pnt;
};

typedef struct {
    node_t *first;
    int count;
} head_t;

#define NLETTERS 26
inline static int is_letter(char c) { return c <= 'z' && c >= 'a'; }

inline static node_t* new_trieblock() {
  const int size = NLETTERS * sizeof(node_t);
  node_t* block = malloc(size);
  memset(block, 0, size);
  for (int i = 0; i < NLETTERS; i++) {
    block[i].alphabet = 'a' + i;
  }
  return block;
}

inline static int trie_has(node_t *n, char *str) {
  node_t *trie = n;
  int len = strlen(str);
  for (int i = 0; i < len - 1; i++) {
    trie = trie[str[i] - 'a'].pnt;
    if (!trie) return 0;    
  }
  return trie[str[len-1] - 'a'].present;
}

int main(void) {
    FILE* dict = fopen("large", "r");

    head_t *header = malloc(sizeof(head_t));
    header->count = 0;
    header->first = new_trieblock();

    node_t *trie = header->first;
    char c = fgetc(dict);
    int nc;
    while(is_letter(c) || c == '\n') {
        nc = fgetc(dict);

        if (nc == '\n' || nc == EOF) {
            trie[c - 'a'].present = 1;
            header->count++;
        } else {
          if (!trie[c - 'a'].pnt) {
            trie = trie[c - 'a'].pnt = new_trieblock();
          } else {
            trie = trie[c - 'a'].pnt;
          }
        }

        c = nc;
        while (c == '\n') {
          trie = header->first;
          c = fgetc(dict);
        }
    }

    char tocheck[100];
    scanf("%s", tocheck);

    if (trie_has(header->first, tocheck)) {
        printf("correctly spelled\n");
    } else {
        printf("mis-spelled\n");
    }

    return 0;
}