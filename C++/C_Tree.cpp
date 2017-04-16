#include <stdio.h>
#include <malloc.h>


typedef int Data;

struct Node {
    Data val;            
    struct Node * left;  
    struct Node * right; 
    int povt;
};

struct Node * tree_add (struct Node * tree, Data x, int * i) //добавляет узел
{
	if (tree == NULL)
	{
		tree = (struct Node *) malloc(sizeof (struct Node));
		tree->val=x;
		tree->right = NULL;
		tree->left = NULL;
		tree->povt = 1;
		return tree;
	}
	
	if (x < tree->val)	tree->left = tree_add(tree->left, x, i);
	else if (x > tree->val) tree->right = tree_add(tree->right, x, i);
		 else tree->povt++;
	return tree;
}

void tree_print (struct Node * tree) // обходит дерево в глубину, выводит значения в узлах
{
	if (tree == NULL) return;
	if (tree->left != NULL) tree_print(tree->left);
	printf("%d ", tree->val);
	if (tree->right != NULL) tree_print(tree->right);
	
	return;
}

void tree_destroy (struct Node * tree) // освобождает память из - под дерева
{
	if (tree != NULL)
	{
		if (tree->left != NULL) tree_destroy(tree->left);
		if (tree->right != NULL) tree_destroy(tree->right);
		free(tree);
	}	
} 	

int tree_high (struct Node * tree) // высота дерева
{
	int i=0, j=0;
	if (tree != NULL)
	{
		if (tree->left != NULL) 
		{
			i = i + tree_high(tree->left) + 1;
		}
		if (tree->right != NULL) 
		{
			j=j + tree_high(tree->right) + 1;
		}
		if (tree->left == NULL) i++;
		if (tree->right == NULL) j++;
	}
	if (i > j)	return i;
	return j;	
} 	

int tree_balance (struct Node * tree) // для любой вершины высота левого и правого поддерева различаются не более, чем на 1
{
	if (tree != NULL)
	{
		if ((tree_high(tree->right) - tree_high(tree->left) > 1) || (tree_high(tree->right) - tree_high(tree->left) < -1)) return 0;
		int k = 1;
		k = tree_balance(tree->left);
		if (k == 1) k = tree_balance(tree->right);
		return k;
	}	
	return 1;
} 	

void tree_print_if (struct Node * tree) //список всех вершин не имеющих потомков
{
	if (tree == NULL) return;
	if (tree->left != NULL) tree_print_if(tree->left);
	if ((tree->right == NULL) && (tree->left == NULL)) printf("%d ", tree->val);
	if (tree->right != NULL) tree_print_if(tree->right);
	
	return;
}
void tree_print_povt (struct Node * tree) // количество повторов каждого значения
{
	if (tree == NULL) return;
	if (tree->left != NULL) tree_print_povt(tree->left);
	printf("%d %d\n", tree->val, tree->povt);
	if (tree->right != NULL) tree_print_povt(tree->right);
	
	return;
}

void add (struct Node * tree, int * i, struct Node * a[]) //
{
	a[(*i)] = tree;
	(*i)++;
}

void  del(int * i, struct Node * a[])
{
	int j;
	for (j = 0; j < ((*i)-1); j++)
	{
		a[j]=a[j+1];
	}
	(*i)--;
	return;
}

void tree_print_floor(struct Node * tree, int * i, struct Node * a[])
{
	if (tree == NULL) return;
	add(tree, i, a);
	while ((*i) != 0)
	{
		printf("%d ", a[0]->val);
		
		if (a[0]->left != NULL) 
		{
			add(a[0]->left, i, a);
		}
		
		if (a[0]->right != NULL) 
		{
			add(a[0]->right, i, a);
		}
		
		del(i, a);
	}
}

int main ()
{
	struct Node ** a;
	a= (struct Node **) malloc(1000 * sizeof(struct Node *));
	Data x;
	int i = 0;
	struct Node * tree=NULL;
	do
	{
		scanf("%d", &x);
		if (x != 0) tree=tree_add(tree, x, &i);
	} while ((x != 0));
	
	tree_print_floor(tree, &i, a);
	free (a);
	tree_destroy(tree);
	return 0;
}
