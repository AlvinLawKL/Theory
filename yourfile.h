#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int parse(char *g); /* returns 0 if g is not a formula, 1 for proposition, 2 for negated formula, 3 for a binary formula */
int type(char *g); /* returns 0 if g is not a formula, 1 for alpha, 2 for beta */
char bin(char *g); /* if g is a binary "(A b B)" then this returns the character b */
char *partone(char *g); /* if g is binary "(A b B)" then this returns A */
char *parttwo(char *g); /* if g is binary "(A b B)" then this returns B */
char *firstexp(char *g); /* given an alpha or beta this returns the first of the two expansion formulas */
char *secondexp(char *g); /* given an alpha (but not a double negation) or beta, this returns the second expansion formula */



typedef struct tableau tableau;

struct tableau {
  char *root;
  tableau *left;
  tableau *right;
  tableau *parent;
  int closedbranch;
};

int closed(tableau *t); /* returns 1 if every branch of tableau is closed, else 0*/
void complete(tableau *t); /*expands the root node according to its type, then recursively completes any child nodes*/

