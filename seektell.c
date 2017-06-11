#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct index{
	char *word;
	int *inFile;
	int toFill;
};
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
int isPresant(struct index *arr,char *word,int a){
	int i;
	int pos=-1;
	for(i=0;i<=a;i++){
		if(compare(arr[i].word,word)==0){
			pos=i;
			break;
		}
	}
	return pos;
}
int isStopWord(char *word){
	FILE *f_stop;
	f_stop=fopen("smart-stopwords","r");
	if(f_stop==NULL){
		printf("Unable to open 'smart-stopwords',Try again!!\n");
		return 0;
	}
	else{
		char *check;
		check=malloc(20*sizeof(char));
		int flag=0;
		while(1==fscanf(f_stop,"%s",check)){
			if(compare(check,word)==0){
				flag=1;
				break;
			}
		}
		return flag;
	}
}
int main(){
	FILE *f_list,*f_names,*f_vec;
	struct index *arr;
	arr=malloc(20*sizeof(struct index));
	int i,j;
	for(i=0;i<20;i++){
		arr[i].word=(char *)(malloc(30*sizeof(char)));
		arr[i].inFile=malloc(20*sizeof(int));
		arr[i].toFill=0;
	}
	for (i=0;i<20;i++){
		for (int i = 0;i<20;i++){
			(arr[i].inFile)[j]=0;
		}
	}
	f_names=fopen("names","r");
	if(f_names==NULL){
		printf("Unable to open file!!\n");
		return 0;
	}
	char *fileName;
	int a=0;
	fileName=malloc(5);
	while(1==fscanf(f_names,"%s",fileName)){
		f_list=fopen(fileName,"r");
		if(f_list==NULL){
			printf("Unable to open file!!\n");
			return 0;
		}
		else{
			char *temp;
			int file;
			temp=malloc(30*sizeof(int));
			i=0;
			int j=0;
			char c;
			while(EOF!=(c=fgetc(f_list))){
				char x=(char)c;
				if((x>='a' && x<='z') || (x>='A' && x<='Z')){
       				temp[i++]=x;       	
    			}
    			else{
    				if(!isStopWord(temp)){
    					if(isalpha(temp[0])){
    						int p=isPresant(arr,temp,a);
    						if(-1==p){    							
    							arr[a].word=temp;
    							(arr[a].inFile)[arr[a].toFill]=atoi(fileName);
    							arr[a].toFill=arr[a].toFill+1;
    							a++;    						    						
    						}
    						else if(p>=0){
    							arr[p].inFile[arr[p].toFill]=atoi(fileName);
    							arr[p].toFill=arr[p].toFill+1;
    						}
							i=0;
							temp=NULL;
							free(temp);
							temp=malloc(30*sizeof(char));
						}
					}
					else if(isStopWord(temp)){
						i=0;
						temp=NULL;
						free(temp);
						temp=malloc(30*sizeof(char));
					}
    			}
			}
		}
	}
	return 0;
}