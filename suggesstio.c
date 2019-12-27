#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct hash{
	char word[20];
	struct hash *nxt;
}arr[26],*run,*temp;


int bits[10000];

void bloom(char []);
int bloomcheck(char []);
void spellcheck();
void suggess(char []);
void enterlist();
void displist();
void hash();

int main()
{
	int choice,i;
	
	i=0;
	while(i<=25)
	{
		arr[i].nxt=NULL;
		strcpy(arr[i].word,"0");
		i++;
	}
	
	i=0;
	while(i<=9999)
	{
		bits[i]=0;
		i++;
	}
	
	hash();
	
	
	
	
	do
	{
		printf("1 to Enter in list...\n2 to display list...\n3 to spell check and suggestion...\n0 to exit...\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:enterlist();
			       break;
			       
			case 2:displist();break;       
			case 3:spellcheck();break;
				default:printf("Enter valid choice...");
				
		}
	}while(choice!=0);
	
}

void enterlist(){
	char words[20];
	FILE *fptr;
	fptr = fopen("list.txt", "a+");
	printf("Enter the words...\nPress 0 to exit.\n\n");
	while(1){
		scanf("%s",words);
		if(strcmp(words,"0")){
		fprintf(fptr,"\n%s",words);
		}
		else
		break;
	}
	
	fclose(fptr);
	exit(0);
}

void displist(){
	char words[20];
	FILE *fptr;
	fptr = fopen("list.txt", "a+");
	printf("List of words...\n");
	

	while(fscanf(fptr,"%s",words)!=EOF){
		printf("%s\n",words);
	}
	
	fclose(fptr);
}

void hash()
{
  	char words[20];
	FILE *fptr;
	fptr = fopen("list.txt", "a+");
	printf("List of words...\n");
	while(fscanf(fptr,"%s",words)!=EOF){
		
	bloom(words);
		
	if(strcmp(arr[(words[0]-97)].word,"0")==0)
		strcpy(arr[(words[0]-97)].word,words);
	
	else if(arr[(words[0]-97)].nxt==NULL)
	{
			temp=(struct hash*)malloc(sizeof(struct hash));
		temp->nxt=NULL;
		strcpy(temp->word,words);
		arr[(words[0]-97)].nxt=temp;
	}
	else{
		
		temp=(struct hash*)malloc(sizeof(struct hash));
		temp->nxt=NULL;
		strcpy(temp->word,words);
		
		run=arr[(words[0]-97)].nxt;
		while(run->nxt!=NULL)
		run=run->nxt;
		
		run->nxt=temp;
	}	
		
		
	}
	
	fclose(fptr);
}

void bloom(char word[])
{
	int i,j=21;
	int x=0,y=0,len;
	len=strlen(word);
	for(i=0;i<len;i++)
	{
		x=(word[i]-97)*j;
		y+=x;
		j+=3;
	}
bits[y]=1;
}

int bloomcheck(char word[])
{
	int i,j=21,flag=0;
	int x=0,y=0,len;
	len=strlen(word);
	for(i=0;i<len;i++)
	{
		x=(word[i]-97)*j;
	y+=x;
		j+=3;
	}
if(bits[y]!=0)
  return 1;
  else
  return 0;
}

void spellcheck()
{
	char text[20];
	do{
	printf("Enter the word...\nPress 0 to exit...\n");
	scanf("%s",text);
	
	if(bloomcheck(text))
	{
		printf("\nThe word is in Dictionary...\n\n");
	}
	else{
		
		printf("\n\nThe word is not in Dictionary...\n\nSuggestions...\n\n");
		suggess(text);
		
	}
}while(strcmp(text,"0")!=0);
}

void suggess(char word[])
{
	int i,len,pos,count=0;
	len=strlen(word);
	pos=word[0]-97;

	for(i=0;i<len;i++)
	{
	if(word[i]==arr[pos].word[i])
		count++;
	}
	
	if(count>=strlen(arr[pos].word)/2)
	printf("%s\n",arr[pos].word);
	
	run=arr[pos].nxt;
	
	if(run!=NULL)
	{
		
		while(run
		!=NULL)
		{
			count=0;
			for(i=0;i<len;i++)
			{
					if(word[i]==run->word[i])
					count++;
				}
	
				if(count>=strlen(run->word)/2)
	             printf("%s\n",run->word);
			
			
			run=run->nxt;
		}
	}

}
