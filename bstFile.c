#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct node{
  int frq;
  char *val;
  struct node *left;
  struct node *right;
};
struct node* allocatenode(char *item){
	struct node* temp;
	temp=(struct node*)malloc(sizeof(struct node));
  int i;
  temp->val=item;
  temp->frq=1;
	temp->right=NULL;
  temp->left=NULL;
	return temp;
}
int compare(char *s1,char *s2){
  int i;
  if(strcasecmp(s1,s2)>0){
    return 1;
  }
  else if(strcasecmp(s1,s2)<0){
    return 2;
  }
  else{
    return 0;
  }
}
void insert(struct node **root,char *item){
  if((*root)==NULL){
printf("%s\t",item);
    *root=allocatenode(item);
    return;
  }
  if(compare((*(root))->val,item)==1){
      insert(&((*root)->left),item);
    }
    else if((compare((*(root))->val,item)==2)){
      insert(&((*root)->right),item);
    }
    else if(compare((*(root))->val,item)==0){
      (*root)->frq+=1;
    }
}
void display(struct node *root,int level){
  int i=0;
	if(root==NULL)
		return;
	display(root->right,level+1);
	for(i=0;i<=level;i++)
		printf("\t");
  printf("%s\n",(root->val));
	display(root->left,level+1);
}
void find(struct node *root,int *f){
    if(root==NULL){
      return;
    }
    else{
      if(((root->val)[0]>='a' && (root->val)[0]<='z') || ((root->val)[0]>='A' && (root->val)[0]<='Z')){
        if((root->frq)>*f){
          *f=root->frq;
        }
      }
      find(root->left,f);
      find(root->right,f);
    }
}
void findMax(struct node *root,int max){
  if(root==NULL){
    return;
  }
  else{
    findMax(root->left,max);
    if(((root->val)[0]>='a' && (root->val)[0]<='z') || ((root->val)[0]>='A' && (root->val)[0]<='Z')){
      if((root->frq)>=max){
        printf("%s(%d)\t",root->val,root->frq);
      }
    }
    findMax(root->right,max);
    }
}
void inorder(struct node *root){
  if(root==NULL){
    return;
  }
  else{
    inorder(root->left);
    if(((root->val)[0]>='a' && (root->val)[0]<='z') || ((root->val)[0]>='A' && (root->val)[0]<='Z')){
      printf("(%s)(%d)\t",root->val,root->frq);
    }
    inorder(root->right);
  }
}
void sort(struct node *root,int fre){
	if(root!=NULL){
		if(root->frq==fre){
			printf("%s\t%d\n",root->val,root->frq);
		}
		sort(root->left,fre);
		sort(root->right,fre);
	}
}
int main(){
  struct node *root=NULL;
  FILE *fs,*fd;
  fs=fopen("list","r");//opening source file in read mode
  //if file does not exist
  if(fs==NULL){
    printf("Error opening file,CHECK AGAIN!!!!\n");
    exit(1);
  }
  /*
  the program uses a temporary file which is devoid of the special characters in the original input file,it is done merely for coding 'simplicity',the temporary file is however deleted automatically
  when the program terminates.
  the file "dest.txt" is our target temporary destination file
  */
  fd=fopen("dest.txt","w");//opening destination file in write mode
  int ch;
  while((ch=fgetc(fs))!=EOF){
    if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
       	fputc(ch,fd);
    }
    else{
   		ch='\n';
      	fputc(ch,fd);     
    }
  }
  //closing the files
  fclose(fd);
  fclose(fs);
  int n=0;
  int c;
  int i;
  char *temp;
  fd=fopen("dest.txt","r");//opening destination file in read mode
  //reading from the destination file
  temp=malloc(1000000);
  while((c=fgetc(fd))!=EOF){
      if(((char)c)!='\n'){
        if((c>='a' && c<='z') || (c>='A' && c<='Z')){
          temp[n++]=(char)c;
        }
    }
    else{
      n=0;
      insert(&root,temp);
      temp=NULL;
      free(temp);
      temp=malloc(1000000);
    }
  }
  printf("\n==============================\n");
  inorder(root);
  printf("\n==============================\n");
  int b=0;
  find(root,&b);
  printf("The (word)/(words) with the maximum frequency (is)/(are):\n");
  findMax(root,b);
  printf("\n");
  printf("\nSorted with respect to frequency in descending order\n");
  printf("WORDS\tFREQUENCY\n");
  printf("\n==============================\n");
  for(i=b;i>=1;i--){
    sort(root,i);
   }
  printf("\n");
  remove("dest.txt");//deleting temporary input file*/
  return 0;
}
