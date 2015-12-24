#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void freewords(char** words,int wcount) {
  int i;
  if(wcount>0) {
    for(i=0;i<wcount;i++) {
      free(words[i]);
    }
    free(words);
  }
}

void viewresult(char** result,int result_size) {
  int i;
  for(i=0;i<result_size;i++) {
    printf("%s ",result[i]);
  }
}

char **append(char** words,int *wcount,char* word)
{
    if(word!=NULL)
    {
        
        if(strlen(word)>1)
        {
            char temp[3] = {word[strlen(word)-2],word[strlen(word)-1],'\0'};
            if(strcmp("я",temp)==0||strcmp("Я",temp)==0)
            {
                word = (char*)realloc(word,sizeof(char)*(strlen(word)+3));
                word[strlen(word)-2] = '\0';
                strcat(word,"йа");
            }    
        }
        if(words!=NULL)
            words = (char**)realloc(words,sizeof(char*)*(*wcount+1));
        else
            words = (char**)malloc(sizeof(char*));
        
        words[(*wcount)++] = word;
    }
    return words;
}

void reset(char** words,int wcount,char* word)
{
    words = append(words,&wcount,word);
    viewresult(words,wcount);
    freewords(words,wcount);
}

int main(int count,char **args)
{
    char alphabet_en[][3] = {"q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","z","x","c","v","b","n","m","Q","W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","Z","X","C","V","B","N","M"};
    char alphabet_ru[][3] = {"а","б","в","г","д","е","ё","ж","з","и","й","к","л","м","н","о","п","р","с","т","у","ф","х","ц","ч","ш","щ","ь","ы","ъ","э","ю","я","А","Б","В","Г","Д","Е","Ё","Ж","З","И","Й","К","Л","М","Н","О","П","Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Щ","Ь","Ы","Ъ","Э","Ю","Я"};
    char alphabet_numbers[][2] = {"0","1","2","3","4","5","6","7","8","9","0"};
    char** words = NULL;
    int wcount = 0;
    char* word = NULL;
    char thechar[3];
    FILE *file = NULL;
    char lang[3];
    strcpy(lang,"??");
    while((thechar[0] = getchar())!=EOF)
    {
        char is_alpha = 0;
        int i = 0;
        if(thechar[0] < 0)
        {
            thechar[1] = getchar();
            thechar[2] = '\0';
        }
        else
            thechar[1] = '\0';
        for(i = 0;i < sizeof(alphabet_ru)/sizeof(alphabet_ru[0]);i++)
        {
            if(strcmp(thechar,alphabet_ru[i])==0)
            {
                if(strcmp(lang,"ru")!=0)
                {
                    reset(words,wcount,word);
                    word = NULL;
                    words = NULL;
                    wcount = 0;
                }
                strcpy(lang,"ru");
                is_alpha = 1;
                break;
            }
        }
        
        for(i = 0;i < sizeof(alphabet_numbers)/sizeof(alphabet_numbers[0]);i++)
        {
            if(strcmp(thechar,alphabet_numbers[i])==0)
            {
                if(strcmp(lang,"n")!=0)
                {
                    reset(words,wcount,word);
                    word = NULL;
                    words = NULL;
                    wcount = 0;
                }
                strcpy(lang,"n");
                is_alpha = 1;
                break;
            }
        }
        
        for(i = 0;i < sizeof(alphabet_en)/sizeof(alphabet_en[0]);i++)
        {
            if(strcmp(thechar,alphabet_en[i])==0)
            {
                if(strcmp(lang,"en")!=0)
                {
                    reset(words,wcount,word);
                    word = NULL;
                    words = NULL;
                    wcount = 0;
                }
                strcpy(lang,"en");
                is_alpha = 1;
                break;
            }
        }
        if(strcmp(thechar,".")==0 || strcmp(thechar,",")==0)
        {
            is_alpha = 2;
        }
        if(is_alpha)
        {
            if(word!=NULL)
            {
                word = (char*)realloc(word,sizeof(char)*(strlen(word)+(thechar[1]=='\0'?2:3)));
                strcat(word,thechar);
            }
            else if(is_alpha!=2)
            {
                word = (char*)malloc(sizeof(char)*(thechar[1]=='\0'?2:3));
                strcpy(word,thechar);
                
            }
            if(is_alpha==2)
            {
                words = append(words,&wcount,word);
                word = 0;
            }
        }
        else if(word!=NULL)
        {
            words = append(words,&wcount,word);
            word = 0;
        }
    }
    reset(words,wcount,word);
    return 0;
}
