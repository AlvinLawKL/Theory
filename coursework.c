#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */
#include "yourfile.h"

int Fsize = 50;

int  main()

{ /*input a string and check if its a propositional formula */
  char *name = malloc(Fsize);
  printf("Enter a formula:");
  scanf("%s", name);
  int p=parse(name);
  switch(p)
    {case(0): printf("not a formula");break;
    case(1): printf("a proposition");break;
    case(2): printf("a negated formula");break;
    case(3): printf("a binary formula");break;
    default: printf("what the f***!");
    }
  printf("\n");
  if (p==3) 
    {
      printf("the first part is %s and the second part is %s. ", partone(name), parttwo(name));
      printf("the binary connective is %c \n", bin(name));
    } 


  int t =type(name);
  switch(t)
    {case(0):printf("I told you, not a formula");break;
    case(1): printf("A literal");break;
    case(2): printf("An alpha formula");break;
    case(3): printf("A beta formula");break;
    case(4): printf("Double negation");break;
    default: printf("SOmewthing's wrong");
    }
  printf("\n");
  if(t==2)  printf("first expansion fmla is %s, second expansion fmla is %s.\n", firstexp(name), secondexp(name));
  if (t==3) printf("first expansion fmla is %s, second expansion fmla is %s.\n", firstexp(name), secondexp(name));




  tableau tab;	     
  tab.root = name;
  tab.left=0;
  tab.parent=0;
  tab.right=0;
  tab.closedbranch=0;


  complete(&tab);/*expand the root node then recursively expand any child nodes */
  if (closed(&tab)) printf("%s is not satisfiable\n", name);
  else printf("%s is satisfiable\n", name);

  return(0);
}
