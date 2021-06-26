#define _POSIX_C_SOURCE 200809L 
#include "word_count.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct word {
    char * w;
    struct word *wordnext;
    struct word *wordprev;
}word;

typedef struct list {
    int length;
    int frequency;
    struct list *listnext;
    struct word *wordnext;
}list;
    
list *head;

void get_word(FILE *input);
void add_word(char* t); 
void print(int sort);
void *emalloc(size_t n);
void free_list(list *pointer);
void free_word(word *pointer);

void free_list(list * pointer){
    list* tmp=NULL;
    for(; pointer!=NULL; pointer=tmp){
        tmp = pointer->listnext;
        free_word(pointer->wordnext);
        free(pointer);    
    }
}

void free_word (word * pointer){
    word* node=NULL;
    for(; pointer!=NULL; pointer=node){
        node = pointer->wordnext;
        free(pointer->w);
        free(pointer);
    }    
    return;
}

void *emalloc(size_t n){
    void *p;
    p = malloc(n);
    if(p==NULL){
        fprintf(stderr, "malloc of %zu bytes failed", n);
        exit(3);
    }
    return p;
}

void get_word (FILE *input){
    char *line=NULL;
    char *t;
    size_t len=0;
    size_t nread;
    while ((nread=getline(&line,&len,input)) != -1){
        t = strtok(line," .,;()\n\t\r");
        while(t!=NULL){
            add_word(t);
            t = strtok(NULL," .,;()\n\t");
        }
    }
    if(line){
        free(line);
    }

}

void add_word(char *t){
    list * prev;
    list * temp;
    word * temp1;
    word * prev1;
    list *listnode=(list*) emalloc(sizeof(list));
    word *wordnode=(word*) emalloc(sizeof(word));
    
    listnode -> length = strlen(t);
    listnode -> frequency = 1;
    listnode -> listnext=NULL;
    listnode -> wordnext=NULL;

    wordnode -> w = strdup(t);  
    wordnode ->wordnext = NULL;
    wordnode -> wordprev = NULL;
    if (head -> length == strlen(t)){
        free(listnode);
        head -> frequency++;
        if (head->wordnext==NULL){
            head->wordnext=wordnode;
            return;
        }
        temp1= head->wordnext;
        if (strcmp(temp1->w,t)>0){ 
             wordnode-> wordnext = temp1;
             temp1->wordprev = wordnode;
             head->wordnext = wordnode; 
             wordnode-> wordprev = NULL; 
             return;    
        } else{
            while (strcmp(temp1->w,t)<0 && temp1->wordnext!=NULL){   
                prev1= temp1;
                temp1= temp1-> wordnext;
            }   
            if (temp1->wordnext==NULL && strcmp(temp1->w,t)<0){
                temp1->wordnext=wordnode;
                wordnode->wordprev=temp1;
                return;
            }else if (strcmp(temp1->w,t)>0){  
                wordnode->wordnext = temp1;
                prev1->wordnext = wordnode;
                temp1->wordprev = wordnode;
                wordnode->wordprev= prev1;
                return;
            }else if (strcmp(temp1->w,t)==0){
                free(wordnode->w);
                free(wordnode);
                return;
            }           
        }      
    }
    temp=head;
    while (temp-> listnext != NULL && temp->length < strlen(t)) {
        prev = temp;
        temp = temp -> listnext; 
    }       
    if (temp -> listnext == NULL && temp->length < strlen(t)){ 
        temp -> listnext = listnode;
        listnode->wordnext= wordnode;
        wordnode->wordprev= NULL;
        return;
    }else if (temp->length-strlen(t)>0){
        listnode->listnext = temp;
        prev->listnext = listnode;
        listnode->wordnext = wordnode;
        wordnode->wordprev = NULL;
        return;
    }else{ 
        free(listnode);
        temp -> frequency++;
        temp1 = temp-> wordnext;
        if (strcmp(temp1->w,t)>0){        
            wordnode-> wordnext = temp1;
            temp1-> wordprev = wordnode;
            temp->wordnext=wordnode; 
            wordnode->wordprev = NULL;
            return;
        }
        while(strcmp(temp1->w,t)<0 && temp1-> wordnext!= NULL){   
            prev1 = temp1;
            temp1 = temp1->wordnext;
        }
        if (strcmp(temp1->w,t)==0){
            free(wordnode->w);
            free(wordnode);
            return;
        }else if (temp1->wordnext==NULL && strcmp(temp1->w,t)<0){   
            temp1->wordnext=wordnode;
            wordnode-> wordprev = temp1;
            return;
        }else if (strcmp(temp1->w,t)>0){    
            wordnode -> wordnext = temp1;
            temp1->wordprev =wordnode;
            prev1 -> wordnext = wordnode;
            wordnode->wordprev=prev1;
        }                      
    }
}
        
void print(int sort){
    list * lpointer;
    word * wpointer;
    lpointer = head;
    while (lpointer!=NULL){
        if(lpointer->frequency!=0){
            printf ("Count[%02d]=%02d; ",lpointer->length,lpointer->frequency);
            if(sort==0){
                wpointer = lpointer-> wordnext;
                if (wpointer -> wordnext==NULL){
                    printf ("(words: \"%s\")\n",wpointer->w);
                } else if ((wpointer->wordnext)->wordnext==NULL){
                    printf ("(words: \"%s\" and \"%s\")\n",wpointer->w, wpointer->wordnext->w);
                }else{
                    printf ("(words: ");
                    while ((wpointer->wordnext)->wordnext!=NULL){
                        printf ("\"%s\", ", wpointer->w);
                        wpointer= wpointer->wordnext;
                    }   
                    printf ("\"%s\" and \"%s\")\n",wpointer->w, wpointer->wordnext->w);
                }
               
            } else {
                wpointer = lpointer->wordnext;
                while(wpointer->wordnext !=NULL){
                    wpointer= wpointer->wordnext;
                }
                if (wpointer->wordprev==NULL){
                    printf("(words: \"%s\")\n",wpointer->w);
                } else if ((wpointer->wordprev)->wordprev==NULL){
                    printf("(words: \"%s\" and \"%s\")\n",wpointer->w, wpointer->wordprev->w);
                }else{
                    printf("(words: ");
                    while((wpointer->wordprev)->wordprev!=NULL){
                        printf("\"%s\", ", wpointer->w);
                        wpointer= wpointer->wordprev;
                    }
                    printf("\"%s\" and \"%s\")\n",wpointer->w,wpointer->wordprev->w);
                }
            }
        }
        lpointer = lpointer-> listnext;
    }
}        


int 
main(int argc, char *argv[]) {
    FILE * input;
    int sort=0;
    int file=0;
    
    head = (list*) emalloc (sizeof(list));
    head-> length = 1;
    head-> frequency = 0;
    head-> listnext = NULL;
    head-> wordnext = NULL;

    if (argc<3){
        fprintf(stderr,"Not enough arguments\n");
        exit(1);
    }
    for (int i=1; i< argc;i++){
        if (strcmp(argv[i],"--sort")==0){
             sort=1;
        }
        if (strcmp(argv[i],"--infile")==0){
            file=1;
            if ((i+1)>=argc){
                fprintf(stderr,"No file name provide\n");
                exit(1);
            }   
            input =fopen(argv[i+1],"r");
            if (input==NULL){
                fprintf(stderr,"Cannot open the file \n");
                exit (2);
            }
        }
    }
    if (file==0){
        fprintf(stderr,"Missing infile\n");
        exit(1);
    }
    get_word(input);
    fclose(input);
    print(sort);
    free_list(head);
    exit (0);
}

