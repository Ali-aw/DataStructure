#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
char synonym[50];
struct node *next;
}node;

typedef struct list{
node *start;
node *end;
int size;
}list;

typedef struct node1{
char word[20];
list l;
struct node *left;
struct node *right;
}node1;

typedef node1* tree;

int isEmptyList(list l)
{
	return(l.size==0);
}

list creatList()
{
	list l;
    l.start=l.end=NULL;
    l.size=0;
    return l;
}

char insertStart (list *l,char synonym[])
{
	node *n=(node*)malloc(sizeof(node));
    strcpy(n->synonym,synonym);
    
      if(isEmptyList(*l))
         {
        	l->start=l->end=n;
            n->next=NULL;
         }  
      else
        {
	         n->next=l->start;
             l->start=n;
        }

    l->size=l->size+1;
}

tree Left(tree a)
{
	return a->left;
}
    
tree Right(tree a)
{
	return a->right;
}
    
char* Root(tree a)
{
	return a->word;
}
    
int isEmptyTree(tree a)
{
	return a==NULL;
}
    
void displaySynonyms(tree a)
{
	printf(" the word: %s \n the synonyms: ",(a));
    displayList(a->l);
    printf("\n\n");
        
          if(!isEmptyTree(Left(a)))
             displaySynonyms(Left(a));
        
          if(!isEmptyTree(Right(a)))
             displaySynonyms(Right(a));
}
       
tree Insert(tree a,char word[], list l)
{
  	if(isEmptyTree(a))
  	{
  		 node1 *n=(node1*) malloc(sizeof(node1));
         strcpy(n->word,word);
         n->l=l;
         n->left=NULL;
         n->right=NULL;
         return n;
	}
       
    else
    {
    	   if(strcmp(word,Root(a))>0)
            a->right=Insert(Right(a),word,l);
           else
            a->left=Insert(Right(a),word,l);
    return a;
	}
     
}

tree insertTree(char *name)
 {
FILE*fp;
fp=fopen(name,"r");
char line[255];
char word[30];
char synonym[255];
list l;
tree a=NULL;

while(1)
{
	  if(fscanf(fp,"%s",line)==1)//takes word by word it stops when encounter a space
	  {
	  	if(strcmp(line,"-")!=0)
            strcpy(word,line);
        if(strcmp(line,"-")==0)
        {
        	l=creatList();
            while(1)
            {
               char t=fgetc(fp);
               
                 if(t!=EOF&&t!='\n')
                 {
                	fscanf(fp,"%s",synonym);
                    insertStart(&l,synonym);
				 }
                    
                 else break;
			}
                
            a=Insert(a,word,l);
		}
            
	  }
        
      else break;
}
  
fclose(fp);
return a;
 }


tree Add(tree a,char word[],char synonym[]){
    if(isEmptyTree(a))
    {
    	node1 *n=(node1*)malloc(sizeof(node1));
        strcpy(n->word,word);
        n->left=NULL;
        n->right=NULL;
        list f=creatList();
        insertStart(&f,synonym);
        n->l=f;
        return n;
	}
        
    else if(strcmp(Root(a),word)==0)
    {
    	insertStart(&(a->l),synonym);
        return a;
	}
        
    else
    {
    	 if(strcmp(word,Root(a))<0)
    	 {
    	 	node1*n=(node1*)malloc(sizeof(node1));
             strcpy(n->word,Root(a));
             n->l=a->l;
             n->right=Right(a);
             n->left=Add(Left(a),word,synonym);
             return n;
		 }
             
         else
         {
         	node1*n=(node1*)malloc(sizeof(node1));
             strcpy(n->word,Root(a));
             n->l=a->l;
             n->left=Left(a);
             n->right=Add(Right(a),word,synonym);
             return n;
		 }
	}
}

int Seek(tree a,char word[])
  {
   	 if(isEmptyTree(a))
  	 {
  	   printf("not found");
       return 0;
	 }
    
     if(strcmp(Root(a),word)==0)
     {
     	 printf("synonymes:\t");
         printf("%s",returnList(a));
         return 1;
	 }
            
    else
     {
    	  if(strcmp(word,Root(a))>0)
    	  {
    	 	 return Seek(Right(a),word);
		  }
            
          else
          {
    	  return Seek(Left(a),word);
	      }
           
	 }
       
  }
    
void displayList(list l)
{
	while(l.start!=NULL)
	{
		printf("%s\t",l.start->synonym);
        l.start=l.start->next;
	}
    
}

void returnList(tree a)
{
	list l=a->l;
    displayList(l);
}
//part 7 in BST, the data is already sorted so we traverse the tree in postfix order  left>>root>>right 
//void displayPostFixOrder(tree*t,FILE*fp)
//{
//	if(t==NULL)
//	return;
//	
//	displayPostFixOrder(t->left,fp);
//	
//	displayPostFixOrder(t->right,fp);
//}

tree rotateRight(tree y)
{
	tree x=y->left;
	tree z=x->right;
	
	//make rotation
	x->right=y;
	y->left=z;
	//return root
	return x;
}

tree rotateLeft(tree x)
{
	tree y=x->left;
	tree z=y->right;
	
	//make rotation
	x->right=z;
	y->left=x;
	//return root
	return y;
}
//=======================================================================================================================================================================================//
int main(int argc, char *argv[]){
int choice;	
char*fn="WordsSynonyms.txt";
char word[30];
char synonym[200];

tree a=insertTree(fn);

/*part 7 assuming that t is given 
int main(){
FILE*fp;
fp=fopen(filename,"r");
node*t=NULL;
displayPostFixOrder(t,fp);
}*/
//while (1) 
//  {
//  	printf("\n1.>> View all words and their synonyms available in the file\n");
//    printf("2.>> Add a word and synonym\n");
//    printf("3.>> Search for a word \n");
//    printf("4.>> Exit\n Please enter a choice(1/2/3/4) :");
//    scanf("%d", &choice);
//    
//    	switch (choice)
//        {
//           case 1:
//           displaySynonyms(a);
//           break;
//           case 2:
//           printf("Enter the word you want to add:");
//           scanf("%s",word);
//           printf("Enter the synonym/s:");
//           scanf("%s",synonym);
//           a=Add(a,word,synonym);
//           break;
//           case 3:
//           printf("Enter the word you are searching for:");
//           scanf("%s",word);
//           Seek(a,word);
//           break;
//           case 4:exit(0);	
//        }	
//  }
//balancing the tree when the left subtree is higher than the right
  rotateRight(a);
  //balancing the tree when the Right subtree is higher than the left
  //rotateLeft(a);
return 0;
}









































