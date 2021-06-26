#include "word_count.h" 
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


#define MAX_FILE_SIZE 5000
#define MAX_WORDS 750
#define MAX_WORD_LEN 35


typedef struct {
    int length;
    int frequency;
    int unique;
    char list[MAX_WORDS][MAX_WORD_LEN];
}word;

word count[MAX_WORD_LEN];
   
char buf [MAX_FILE_SIZE+1];


void low_case(char* str);
void tokenize_string(char* line);
void print_a ();
void print_b ();
void print_c ();
void read_file(FILE* data, char buf[]);
int by_freq(const void* a, const void* b);
int by_length(const void* a, const void* b);
int by_alphanum(const void* a, const void* b);


void low_case (char* str) {  
    for (int i=0; str[i];i++){
        str[i] = tolower(str[i]);
    }
    return;
}

void read_file(FILE* data, char buf[]){
    while (fgets(buf,MAX_FILE_SIZE+1,data) != NULL){
        tokenize_string (buf);
    }
    fclose(data);
    return;
}

void tokenize_string(char *line){
    int i;
    char* t;
    t = strtok(line, " .,()\n\r\t");
    int seen=0;
         
    while (t!=NULL){
        seen=0;
        for (i=0;i<count[strlen(t)-1].frequency;i++){
            if (strcmp(t,count[strlen(t)-1].list[i])==0){
                count[strlen(t)-1].frequency++;
                seen=1;
                break;
            }
        }
        if (seen==0){
            strncpy(count[strlen(t)-1].list[count[strlen(t)-1].frequency],t,MAX_WORD_LEN);
            count[strlen(t)-1].unique++;
            count[strlen(t)-1].frequency++;
        }                       
        t = strtok(NULL," .,;()\n\r\t");
    }
    return;
} 

void print_a(){
 
    for( int i=0; i< MAX_WORD_LEN;i++){
        if (count[i].frequency!=0){
            printf("Count[%02d]=%02d;\n", count[i].length, count[i].frequency);
        }
    }
}

int by_freq(const void* a, const void* b){
    word* aa = (word *) a;
    word* bb = (word *) b;
    if ( bb->frequency != aa->frequency){
        return bb->frequency - aa->frequency;
    } else{
        return aa->length - bb->length;
    }
}

int by_length(const void* a, const void* b){
    word* aa = (word*) a;
    word* bb = (word*) b;
    return aa-> length - bb->length;
}

int by_alphanum(const void* a, const void* b){ 
    const char * aa = (const char*) a;
    const char * bb = (const char*) b;
    return strcmp(aa,bb);    
} 

void print_c(){  
    qsort(count,sizeof(count)/sizeof(word),sizeof(word),by_freq); //http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
    for (int i=0; i<MAX_WORD_LEN;i++){
        if (count[i].frequency!=0){
            printf("Count[%02d]=%02d; (", count[i].length, count[i].frequency);
            qsort(count[i].list, MAX_WORDS, sizeof(char)*MAX_WORD_LEN, by_alphanum);//http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
            if (count[i].unique==1){
                for (int u=0; u < MAX_WORDS; u++){
                    if(strcmp(count[i].list[u],"")!=0){
                       printf("words: \"%s\")\n", count[i].list[u]);
                       break;
                    }
                }
            } else{
                int num = 0;              
                for (int m=0; m< MAX_WORDS; m++){
                    if (strcmp(count[i].list[m],"")!=0){
                        if (num==0) {
                            printf("words: \"%s\"", count[i].list[m]);
                            num++;
                        }else if ( num!=0 && num < count[i].unique-1){
                            printf(", \"%s\"",count[i].list[m]);
                            num++;
                          
                        }else{
                            printf(" and \"%s\")\n", count[i].list[m]);
                            break;
                       }
                    }
                }
            }
        }
    }
    return;
}

void print_b(){

    int n = sizeof(count)/sizeof(word);
    int bucket = 0;
    int sum = 0;
    double length1 = 0;
    double length2 = 0;
    double median = 0;
    
    qsort(count, n, sizeof(word),by_freq);//http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
    for(int i = 0; i < MAX_WORD_LEN; i++){
        if(count[i].frequency!=0){
            bucket++;
            printf("Count[%02d]=%02d;\n", count[i].length, count[i].frequency);
        }
    }
    qsort(count,n,sizeof(word),by_length);
    if (bucket%2==0){
        for (int i=0; i< MAX_WORD_LEN;i++){
            if(count[i].frequency!=0){
                sum++;
                if (sum == bucket/2){
                    length1 = count[i].length;
                    
                }
                if (sum == bucket/2+1){
                    length2 = count[i].length;
                    break;
                }    
            }
        }
        median = (length1+length2)/2; 
    } else{
        for (int i=0;i<MAX_WORD_LEN;i++){
            if(count[i].frequency!=0){
                sum++;
                if (sum==bucket/2+1){
                    median = count[i].length;
                    break;
                }
             }
        }
    }
    printf("Median word length: %.1f\n", median);
    return;
}
        
   
int
real_main(int argc, char *argv[]) {
    int sortflag=0;
    int wordflag=0;
    FILE *input;
    for(int i=0; i< MAX_WORD_LEN;i++){
        count[i].length=i+1;
        count[i].frequency=0;
        count[i].unique =0;
        for (int j=0; j< MAX_WORDS;j++){
            memset(count[i].list[j], '\0', sizeof(char)* MAX_WORD_LEN);//https://www.quora.com/How-do-you-use-memset-to-fill-a-char-array-variable-with-blank-spaces
        }
    }
    if (argc<3){
        printf("program: missing \'--infile <filename> [--sort] [--print-words]\'\n");
        return 0;
    }
    for (int i=0; i<argc; i++){
        if (strcmp(argv[i], "--sort") == 0){
            sortflag=1;
        }
        if (strcmp(argv[i], "--print-words") == 0){
            wordflag=1;
        }
        if (strcmp(argv[i], "--infile") == 0){
            input = fopen(argv[i+1],"r");
            if (input == NULL){
                printf("unable to open 'badfile.txt' for reading\n");
                return 0; 
            }               
            
        }
    }
  
    read_file(input,buf);
    if (wordflag == 1){
        print_c();
    } else if (sortflag == 1){
        print_b();
    }else{
        print_a();
    }
    return 0;
}


#ifndef TEST
int
main(int argc, char *argv[]) {
    return real_main(argc, argv);
}

#endif
