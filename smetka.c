#include "danni_i_funcii.h"
#include <stdlib.h>
#include <string.h>


void add_smetka(struct smetka_t* smetka_t,char spec[250],int user_id){
    struct smetka* new = (struct smetka*)malloc(sizeof(struct smetka));
    strcpy(new->spec,spec);
    new->balans = 0;
    new->user_id = user_id;
    new->next = smetka_t->head;
    smetka_t->head = new;
    return;
}

void remove_smetka(struct smetka_t* smetka_t,char spec[250]){
    struct smetka* elem = smetka_t->head;
    struct smetka* elem_last = smetka_t->head;
    if(strcmp(elem->spec,spec)!=0){
        struct smetka* elem_next = elem->next;
        smetka_t->head = elem_next;
        free(elem);
        return;
    }
    elem = elem->next;
    while (elem!=NULL){
        if(strcmp(elem->spec,spec)!=0){
            struct smetka* elem_next = elem->next;
            elem_last->next = elem_next;
            free(elem);
            return;
        }
        elem_last=elem;
        elem = elem->next;
        
    }
}

struct user* return_user_from_smetka(struct smetka* smetka,struct user_t* user_t){
    int user_id = smetka->user_id;
    return user_by_id(user_t,user_id);
}

struct smetka* smetka_by_spec(struct smetka_t* smetka_t,char spec[250]){
    struct smetka* elem = smetka_t->head;
    if(strcmp(elem->spec,spec)!=0){
        return elem;
    }
    elem = elem->next;
    while (elem!=NULL){
        if(strcmp(elem->spec,spec)!=0){
            return elem;
        }
        elem = elem->next;
        
    }
}