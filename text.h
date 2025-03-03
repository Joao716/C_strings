#ifndef _TEXT_H
#define _TEXT_H
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef unsigned char* text;
unsigned char text_contains(text*str,text instance);
void text_set(text*str,text value){
    *str=(text)malloc(strlen(value)+1);
    strcpy(*str,value);
}
void text_add(text*str,text value){
    size_t aux_len=strlen(*str)+strlen(value);
    *str=(text)realloc(*str,aux_len+1);
    strcat(*str,value);
}
void text_addChar(text*str,char c){
    size_t aux_len=strlen(*str)+1;
    *str=(text)realloc(*str,aux_len);
    text added=(text)malloc(2);added[0]=c;added[1]='\0';
    strcat(*str,added);
}
void text_prependChar(text*str,char c){
    text aux=malloc(strlen(*str)+1);
    aux[0]=c;aux[1]='\0';
    strcat(aux,*str);
    strcpy(*str,aux);
}
void text_prepend(text*str,text value){
    size_t aux_len=strlen(*str)+strlen(value);
    text aux=(text)malloc(aux_len+1);
    aux=(text)realloc(aux,aux_len+1);
    strcpy(aux,value);
    strcat(aux,*str);
    strcpy(*str,aux);
}
unsigned char text_equals(text*str,text value){
    return strcmp(*str,value)==0;
}
long int text_indexOf(text*str,text instance){
    text result=strstr(*str,instance);
    return result-*str;
}
void text_substring(text*str,text*receive,size_t index1,size_t index2){
    text_set(receive,"");
    size_t i;
    for(i=index1;i<index2;i++){
        text_addChar(receive,((unsigned char*)*str)[i]);
    }
}
void text_replace(text*str,text pattern,text substitute){
    size_t index1=text_indexOf(str,pattern);
    size_t index2=index1+strlen(pattern);
    text first,second;text_substring(str,&first,0,index1);
    text_substring(str,&second,index2,strlen(*str));
    text_set(str,"");text_add(str,first);text_add(str,substitute);text_add(str,second);
}
void text_replaceAll(text*str,text pattern,text substitute){
    // size_t ptr_length=1,i;
    // size_t*index=malloc(sizeof(size_t)*ptr_length);
    // index[0]=0;
    // index=realloc(index,sizeof(size_t)*(ptr_length+1));
    // ptr_length++;
    // text substr,aux;
    // text_set(&substr,*str);text_set(&aux,"");
    // while(text_contains(&substr,pattern)){
    //     index[ptr_length-1]=text_indexOf(&substr,pattern)+(strlen(*str)-strlen(substr));
    //     for(i=index[ptr_length-2];i<index[ptr_length-1];i++){
    //         text_addChar(&aux,(*str)[i]);
    //     }
    //     text_add(&aux,substitute);
    //     text_substring(str,&substr,index[ptr_length-1],strlen(*str));
    //     text_replace(&substr,pattern,"");
    //     index=realloc(index,sizeof(size_t)*(ptr_length+1));
    //     ptr_length++;
    //     index[ptr_length-2]+=strlen(pattern);
    // }
    // text_set(str,aux);
    size_t pattern_len = strlen(pattern);
    size_t substitute_len = strlen(substitute);
    size_t str_len = strlen(*str);

    text result = (text)malloc(1);
    result[0] = '\0';
    size_t result_len = 0;

    text current = *str;
    text match;

    while ((match = strstr(current, pattern)) != NULL) {
        size_t prefix_len = match - current;

        result = (text)realloc(result, result_len + prefix_len + 1);
        strncat(result, current, prefix_len);
        result_len += prefix_len;

        result = (text)realloc(result, result_len + substitute_len + 1);
        strcat(result, substitute);
        result_len += substitute_len;
        current = match + pattern_len;
    }
    size_t remaining_len = strlen(current);
    result = (text)realloc(result, result_len + remaining_len + 1);
    strcat(result, current);
    text_set(str,result);
}
void text_trim(text*str){
    size_t i;text aux,aux2;text_set(&aux,"");text_set(&aux2,"");
    for(i=0;i<strlen(*str) && ((unsigned char*)*str)[i]==' ';i++){
    }
    for(;i<strlen(*str);i++){
        text_addChar(&aux,((unsigned char*)*str)[i]);
    }
    for(i=strlen(aux)-1;i>0 && aux[i]==' ';i--){
    }
    for(;i>0;i--){
        text_prependChar(&aux2,aux[i]);
    }
    text_prependChar(&aux2,aux[0]);
    text_set(str,aux2);
}
void text_toUpperCase(text*str){
    unsigned char*s=*str;
    while (*s) {
        *s = toupper((unsigned char)*s);
        s++;
    }
}
void text_toLowerCase(text*str){
    unsigned char*s=*str;
    while (*s) {
        *s = tolower((unsigned char)*s);
        s++;
    }
}
unsigned char text_contains(text*str,text instance){
    return strstr(*str,instance)!=NULL;
}
size_t text_numberOf(text*str,text pattern){
    text aux;text_set(&aux,*str);
    size_t count;
    for(count=0;text_contains(&aux,pattern);count++){
        text_replace(&aux,pattern,"");
    }
    return count;
}
#endif