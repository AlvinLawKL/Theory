//
//  kwoklunlaw.c
//  
//
//  Created by Alvin Law K.L. on 21/12/2014.
//
//

#include "yourfile.h"

int parse(char *g)
{
    if (g[0] == 'p' || g[0] == 'q' || g[0] == 'r')
    {
        if (g[1] == '\0')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (g[0] == '-')
    {
        char *formula = malloc(50);
        int i = 1;
        while (g[i] != '\0')
        {
            formula[i-1] = g[i];
            i++;
        }
        
        if (parse(formula) != 0)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else if (g[0] == '(')
    {
        char *partOne = partone(g);
        char *partTwo = parttwo(g);
        if (parse(partOne) != 0 && parse(partTwo) != 0)
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int type(char *g) {
    if (parse(g) == 1)
    {
        return 1;
    }
    else if (parse(g) == 2)
    {
        int i = 0;
        int negation = 0;
        while (g[i] == '-')
        {
            negation++;
            i++;
        }
        
        if (negation % 2 == 0)
        {
            return 4;
        }
        else if (g[i+1] == '\0')
        {
            return 1;
        }
        else if (bin(g) == '^')
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }
    else if (parse(g) == 3)
    {
        if (bin(g) == '^')
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
    else {
        return 0;
    }
}

char bin(char *g) {
    int i = 0;
    while (g[i] != '(')
    {
        i++;
    }
    i++;
    int openBracket = 1;
    int bin = 0;
    while (openBracket != bin)
    {
        if (g[i] == '(')
        {
            openBracket++;
        }
        else if (g[i] == 'v' || g[i] == '^' || g[i] == '>')
        {
            bin++;
        }
        
        i++;
    }
    return g[i-1];
}

char *partone(char *g) {
    int i = 0;
    while (g[i] != '(')
    {
        i++;
    }
    i++;
    int openBracket = 1;
    int bin = 0;
    int j = 0;
    char *partOne = malloc(50);
    while (openBracket != bin)
    {
        if (g[i] == '\0')
        {
            break;
        }
        else if (g[i] == '(')
        {
            openBracket++;
        }
        else if (g[i] == 'v' || g[i] == '^' || g[i] == '>')
        {
            bin++;
        }
        
        if (openBracket != bin)
        {
            partOne[j] = g[i];
            j++;
        }
        i++;
    }
    return partOne;
}

char *parttwo(char *g) {
    int i = 0;
    while (g[i] != '(')
    {
        i++;
    }
    i++;
    int openBracket = 1;
    int bin = 0;
    while (openBracket != bin)
    {
        if (g[i] == '\0')
        {
            break;
        }
        else if (g[i] == '(')
        {
            openBracket++;
        }
        else if (g[i] == 'v' || g[i] == '^' || g[i] == '>')
        {
            bin++;
        }
        i++;
    }
    int j = 0;
    char *partTwo = malloc(50);
    if (g[i] == '\0')
    {
        return partTwo;
    }
    while (g[i] != ')' && g[i+1] != '\0')
    {
        partTwo[j] = g[i];
        i++;
        j++;
    }
    return partTwo;
}

char *firstexp(char *g)
{
    if (type(g) == 2)
    {
        if (bin(g) == 'v')
        {
            int i = 0;
            char *firstExpansion = malloc(50);
            firstExpansion[0] = '-';
            char *partOne = partone(g);
            while (partOne[i] != '\0')
            {
                firstExpansion[i+1] = partOne[i];
                i++;
            }
            return firstExpansion;
        }
        else
        {
            return partone(g);
        }
    }
    else if (type(g) == 3)
    {
        if (bin(g) == 'v')
        {
            return partone(g);
        }
        else
        {
            int i = 0;
            char *firstExpansion = malloc(50);
            firstExpansion[0] = '-';
            char *partOne = partone(g);
            while (partOne[i] != '\0')
            {
                firstExpansion[i+1] = partOne[i];
                i++;
            }
            return firstExpansion;
        }
    }
    else if (type(g) == 4)
    {
        int i = 0;
        while (g[i] == '-')
        {
            i++;
        }
        char *formula = malloc(50);
        int j = 0;
        while (g[i] != '\0')
        {
            formula[j] = g[i];
            i++;
            j++;
        }
        return firstexp(formula);
    }
    else
    {
        return g;
    }
}

char *secondexp(char *g)
{
    if (type(g) == 2)
    {
        if (bin(g) == '^')
        {
            return parttwo(g);
        }
        else
        {
            int i = 0;
            char *secondExpansion = malloc(50);
            secondExpansion[0] = '-';
            char *partTwo = parttwo(g);
            while (partTwo[i] != '\0')
            {
                secondExpansion[i+1] = partTwo[i];
                i++;
            }
            return secondExpansion;
        }
    }
    else if (type(g) == 3)
    {
        if (bin(g) == '^')
        {
            int i = 0;
            char *secondExpansion = malloc(50);
            secondExpansion[0] = '-';
            char *partTwo = parttwo(g);
            while (partTwo[i] != '\0')
            {
                secondExpansion[i+1] = partTwo[i];
                i++;
            }
            return secondExpansion;
        }
        else
        {
            return parttwo(g);
        }
    }
    else if (type(g) == 4)
    {
        int i = 0;
        while (g[i] == '-')
        {
            i++;
        }
        char *formula = malloc(50);
        int j = 0;
        while (g[i] != '\0')
        {
            formula[j] = g[i];
            i++;
            j++;
        }
        return secondexp(formula);
    }
    else
    {
        return g;
    }
}

int closed(tableau *t){
    if (t->left == 0)
    {
        tableau *n = t;
        char *check = t->root;
        while (n->parent != 0)
        {
            n = n->parent;
            char *check2 = n->root;
            if ((type(check2) == 1) && (parse(check) != parse(check2)))
            {
                char first;
                char second;
                int k = 0;
                while (check[k] == '-')
                {
                    k++;
                }
                first = check[k];
                k = 0;
                while(check2[k] == '-')
                {
                    k++;
                }
                second = check2[k];
                if (first == second)
                {
                    t->closedbranch = 1;
                }
            }
        }
    }
    else if ((t->right != 0))
    {
        int i = closed(t->right);
        int j = closed(t->left);
        if ((i == 1) && (j == 1))
        {
            t->closedbranch = 1;
        }
    }
    else
    {
        closed(t->left);
        t->closedbranch = t->left->closedbranch;
    }
    return t->closedbranch;
}

void complete(tableau *t)
{
    if ((type(t->root) == 2) || (type(t->root) == 3))
    {
        tableau* g = malloc(sizeof(tableau));
        g->root = firstexp(t->root);
        
        tableau* h = malloc(sizeof(tableau));
        h->root = secondexp(t->root);
        
        if ((type(t->root) == 2))
        {
            if (t->right != 0)
            {
                tableau *n = t;
                while (n->right != 0)
                {
                    n = n->right;
                }
                while (n->left != 0)
                {
                    n = n->left;
                }
                n->left = g;
                g->parent = n;
                g->left = h;
                h->parent = g;
                complete(g);
                complete(h);
            }
            
            tableau *n = t;
            while (n->left != 0)
            {
                n = n->left;
            }
            
            n->left = g;
            g->parent = n;
            g->left = h;
            h->parent = g;
            complete(g);
            complete(h);
        }
        else
        {
            if (t->right !=0)
            {
                tableau *n = t;
                while (n->right != 0)
                {
                    n = n->right;
                }
                while (n->left != 0)
                {
                    n = n->left;
                }
                n->left = g;
                g->parent = n;
                n->right = h;
                h->parent = n;
                complete(g);
                complete(h);
            }
            
            tableau *n = t;
            while (n->left != 0)
            {
                n = n->left;
            }
            n->left = g;
            g->parent = n;
            n->right = h;
            h->parent = n;
            complete(g);
            complete(h);
        }
    }
    else if ((type(t->root) == 4))
    {
        int i = 0;
        char *c = t->root;
        while (c[i] == '-')
        {
            i++;
        }
        int j = 0;
        char *formula = malloc(50);
        while(c[i] != '\0')
        {
            formula[j] = c[i];
            i++;
            j++;
        }
        
        tableau* g = malloc(sizeof(tableau));
        g->root = formula;
        
        if (t->right != 0)
        {
            tableau *n = t;
            while (n->right != 0)
            {
                n = n->right;
            }
            while (n->left != 0)
            {
                n = n->left;
            }
            n->left = g;
            g->parent = n;
            complete(g);
        }
        
        tableau *n = t;
        while (n->left != 0)
        {
            n = n->left;
        }
        n->left = g;
        g->parent = n;
        complete(g);
    }
    else if (type(t->root) == 0)
    {
        exit(1);
    }
}