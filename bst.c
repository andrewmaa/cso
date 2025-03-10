#include <stdio.h>
#include <stdlib.h>

typedef struct tnode { /* the tree node: */
   int num; /* value of number */
   int count; /* number of occurrences */
   struct tnode *left; /* left child */
   struct tnode *right; /* right child */
} tnode;

tnode *addtree(tnode *p, int x);
void treeprint(tnode*);

/* talloc: make a tnode */
tnode *talloc(void)
{
   return (tnode *) malloc(sizeof(tnode));
}

/* addtree: add a node with w, at or below p */
tnode *addtree(tnode *p, int val)
{
   //start at root, descend 1 level deeper with
   //each recursive call
   //set higher level left and right child with
   //each call
   if (p == NULL) { /* a new num has arrived */
       p = talloc(); /* make a new node */
       p->num = val;
       p->count = 1;
       p->left = p->right = NULL;
   } else if (val == p->num)
       p->count++; /* number already in tree */
   //if still need to search tree
   //recursively call addtree() with next node *
   //exit when finds leaf or requested value
   else if (val < p->num) /* less than into left subtree */
       p->left = addtree(p->left, val);
   else if (val > p->num) /* greater than into right subtree */
       //could just use else here
       p->right = addtree(p->right, val);
   return p;
}

/* treeprint: in-order print of tree p */
void treeprint(tnode *p)
{
   if (p != NULL) {
       treeprint(p->left);
       printf("Value %d appears %d time(s)\n",  p->num, p->count);
       treeprint(p->right);
   }
}

void invertTree(tnode *p) {
    if (p == NULL) {
        return;
    }

    invertTree(p->left);
    invertTree(p->right);

    tnode *temp = p->left;
    p->left = p->right;
    p->right = temp;
    
}

void main() {
   tnode *root = NULL;
   root = NULL;

   int myints[] = {3, 5, 2, 4, 6, 3};
   for (int i = 0; i < sizeof(myints) / sizeof(myints[0]); i++) {
       root = addtree(root, myints[i]);
   }

   printf("Original tree:\n");
   treeprint(root);

   printf("Inverted tree:\n");
   invertTree(root);

   treeprint(root);
}
