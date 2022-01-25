#include <stdio.h>
#include <stdlib.h>
#include "the3.h"


Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth){
    Apartment* new_apt = (Apartment*)malloc(sizeof(Apartment));
    Apartment* temp = head;
    Apartment* next;
    int i = 0;
    new_apt->name = apartment_name;
    new_apt->max_bandwidth = max_bandwidth;
    new_apt->flat_list = NULL;
    if((head == NULL) && (index == 0)){
        new_apt->next = new_apt;
        return new_apt;
    }
    else if((head != NULL) && (index == 0)){
        new_apt->next = head;
        while(temp->next != head){
            temp = temp->next;
        }
        temp->next = new_apt;
        return new_apt;
    }
    else{
        for (i=0;temp->next != head && i < index-1; i++){
            temp = temp->next;
        }
        next = temp->next;
        temp->next = new_apt;
        new_apt->next = next;
        return head;
        }
}

int helper_compare_strings(char* x, char* y)
{
    int flag = 0;
    while(*x != '\0' || *y != '\0'){
        if (*x == *y){
            x++;
            y++;
        }
        else if (*x != *y || (*x == '\0' && *y != '\0') || (*x != '\0' && *y == '\0')){
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        return 1;
    }
    return 0;
}

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth){
    int i;
    int total_flat = 0;
    int left_bandwidth, total_bandwidth = 0;
    Apartment* temp = head;
    Flat* counter, *iter;
    Flat* new_flat = (Flat*)malloc(sizeof(Flat));
    new_flat->id = flat_id;
    new_flat->is_empty = 0;
    while(!(helper_compare_strings(temp->name,apartment_name))){
        temp = temp->next;
    }
    counter = temp->flat_list;
    while(counter != NULL){
        total_flat++;
        total_bandwidth += counter->initial_bandwidth;
        counter = counter->next;
    }
    left_bandwidth = temp->max_bandwidth - total_bandwidth;
    if(temp->flat_list == NULL && index == 0){
        new_flat->next = NULL;
        new_flat->prev = NULL;
        temp->flat_list = new_flat;
    }
    else if((temp->flat_list != NULL) && (index == 0)){
        new_flat->next = temp->flat_list;
        new_flat->prev = NULL;
        temp->flat_list->prev = new_flat;
        temp->flat_list = new_flat;
    }
    else{
        iter = temp->flat_list;
        for (i=0; i < index-1; i++){
            iter = iter->next;
        }
        new_flat->next = iter->next;
        iter->next = new_flat;
        new_flat->prev = iter;
        if (new_flat->next != NULL){
            new_flat->next->prev = new_flat;
        }
    }
    if(initial_bandwidth <= left_bandwidth){
        new_flat->initial_bandwidth = initial_bandwidth;
    }
    else{
        new_flat->initial_bandwidth = left_bandwidth;
    }
}


Apartment* remove_apartment(Apartment* head, char* apartment_name){
    Apartment* temp = head;
    Apartment* iter = head;
    Apartment* next;
    Flat* iter_flat;
    if(head == NULL){
        return NULL;
    }
    if((helper_compare_strings(temp->name,apartment_name))){
        while(iter->next != head){
            iter = iter->next;
        }
        iter->next = temp->next;
        iter_flat = temp->flat_list;
        if(iter_flat){
            while(iter_flat->next != NULL){
                iter_flat = iter_flat->next;
                free(iter_flat->prev);
            }
            free(iter_flat);
        }
        if(temp == temp->next){
            free(temp);
            return NULL;
        }
        else{
            next = temp->next;
            free(temp);
            return next;
        }
    }
    while(!(helper_compare_strings(iter->next->name,apartment_name))){
        iter = iter->next;
    }
    if(iter->next->next != head){
        iter_flat = iter->next->flat_list;
        if(iter_flat){
            while(iter_flat->next != NULL){
                iter_flat = iter_flat->next;
                free(iter_flat->prev);
            }
            free(iter_flat);
        }
        next = iter->next->next;
        free(iter->next);
        iter->next = next;
        return head;
    }
    else{
        iter_flat = iter->next->flat_list;
        if(iter_flat){
            while(iter_flat->next != NULL){
                iter_flat = iter_flat->next;
                free(iter_flat->prev);
            }
            free(iter_flat);
        }
        free(iter->next);
        iter->next = head;
        return head;
    }
}


void make_flat_empty(Apartment* head, char* apartment_name, int flat_id){
    Apartment * temp = head;
    Flat* iter_flat;
    while(!(helper_compare_strings(temp->name,apartment_name))){
        temp = temp->next;
    }
    iter_flat = temp->flat_list;
    while(iter_flat->id != flat_id){
        iter_flat = iter_flat->next;
    }
    iter_flat->initial_bandwidth = 0;
    iter_flat->is_empty = 1;
}

int find_sum_of_max_bandwidths(Apartment* head){
    int sum = 0;
    Apartment *iter = head;
    if(head){
        sum += iter->max_bandwidth;
        while(iter->next != head){
            iter = iter->next;
            sum += iter->max_bandwidth;
        }
        return sum;
    }
    else{
        return sum;
    }
}


Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2){
    Apartment* iter1 = head, *iter2 = head, *iter3 = head, *temp = head, *next;
    Flat* flat1, *flat2;
    while(!(helper_compare_strings(iter1->name,apartment_name_1))){
        iter1 = iter1->next;
    }
    flat1 = iter1->flat_list;
    while(!(helper_compare_strings(iter2->name,apartment_name_2))){
        iter2 = iter2->next;
    }
    flat2 = iter2->flat_list;
    if(flat1){
        while(flat1->next != NULL){
            flat1 = flat1->next;
        }
    }
    if(flat1 && flat2 != NULL){
        do {
            flat1->next = flat2;
            flat2->prev = flat1;
            flat2 = flat2->next;
            flat1->next->next = NULL;
            flat1 = flat1->next;
        }while(flat2 != NULL);
    }
    else if(flat1 == NULL && flat2 != NULL){
        iter1->flat_list = iter2->flat_list;
    }
    iter1->max_bandwidth += iter2->max_bandwidth;
    if((helper_compare_strings(temp->name,apartment_name_2))){
        while(iter3->next != head){
            iter3 = iter3->next;
        }
        iter3->next = temp->next;
        free(temp);
        return temp->next;
    }
    while(!(helper_compare_strings(iter3->next->name,apartment_name_2))){
        iter3 = iter3->next;
    }
    if(iter3->next->next != head){
        next = iter3->next->next;
        free(iter3->next);
        iter3->next = next;
        return head;
    }
    else{
        free(iter3->next);
        iter3->next = head;
        return head;
    }
}


void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list){
    int i = 0;
    int counter =0 ;
    Apartment *apt = head, *iter;
    Flat * flats, *next_flat, *flat1;
    while(!(helper_compare_strings(apt->name,new_apartment_name))){
        apt = apt->next;
    }
    flats = apt->flat_list;
    if(flats->id != flat_id_to_shift){
        while(flats->next->id != flat_id_to_shift){
            flats = flats->next;
        }
        next_flat = flats->next;
        while(flat_id_list[i] != '\0'){
            iter = head;
            do{
                if(!(helper_compare_strings(iter->name,new_apartment_name))){
                    flat1 = iter->flat_list;
                    while(flat1 != NULL){
                        if(flat1->id == flat_id_list[i]){
                            
                            if(flat1->prev == NULL){
                                iter->flat_list = iter->flat_list->next;
                                flats->next = flat1;
                                flat1->prev = flats;
                                flat1->next = next_flat;
                                next_flat->prev = flat1;
                                if(iter->flat_list){
                                    iter->flat_list->prev = NULL;
                                }
                                flats = flats->next;
                            }
                            
                            else if(flat1->next == NULL){
                                if(flat1->prev){
                                    flat1->prev->next = NULL;
                                }
                                else{
                                    iter->flat_list = NULL;
                                }
                                flats->next = flat1;
                                flat1->prev = flats;
                                flat1->next = next_flat;
                                next_flat->prev = flat1;
                                flats = flats->next;
                            }
                            
                            else if(flat1->next != NULL){
                                flat1->prev->next = flat1->next;
                                flat1->next->prev = flat1->prev;
                                flats->next = flat1;
                                flat1->prev = flats;
                                flat1->next = next_flat;
                                next_flat->prev = flat1;
                                flats = flats->next;
                            }
                            apt->max_bandwidth += flat1->initial_bandwidth;
                            iter->max_bandwidth -= flat1->initial_bandwidth;
                            
                        }
                        flat1 = flat1->next;
                    }
                }
                iter = iter->next;
            }while(iter != head);
            i++;
        }
    }
    else{
        next_flat = flats;
        while(flat_id_list[i] != '\0'){
            iter = head;
            do{
                if(!(helper_compare_strings(iter->name,new_apartment_name))){
                    flat1 = iter->flat_list;
                    while(flat1 != NULL){
                        if(flat1->id == flat_id_list[i]){
                            
                            if(flat1->prev == NULL){
                                iter->flat_list = iter->flat_list->next;
                                if(counter == 0){
                                    apt->flat_list = flat1;
                                    flat1->next = next_flat;
                                    next_flat->prev = flat1;
                                    flat1->prev = NULL;
                                    flats = flat1;
                                }
                                else{
                                    flats->next = flat1;
                                    flat1->prev = flats;
                                    flat1->next = next_flat;
                                    next_flat->prev = flat1;
                                    flats = flats->next;
                                }
                                if(iter->flat_list){
                                    iter->flat_list->prev = NULL;
                                }
                            }
                            
                            else if(flat1->next == NULL){
                                if(flat1->prev){
                                    flat1->prev->next = NULL;
                                }
                                else{
                                    iter->flat_list = NULL;
                                }
                                if(counter == 0){
                                    apt->flat_list = flat1;
                                    flat1->next = next_flat;
                                    next_flat->prev = flat1;
                                    flat1->prev = NULL;
                                    flats = flat1;
                                }
                                else{
                                    flats->next = flat1;
                                    flat1->prev = flats;
                                    flat1->next = next_flat;
                                    next_flat->prev = flat1;
                                    flats = flats->next;
                                }
                            }
                            
                            else if(flat1->next != NULL){
                                if(counter == 0){
                                    flat1->prev->next = flat1->next;
                                    flat1->next->prev = flat1->prev;
                                    apt->flat_list = flat1;
                                    flat1->next = next_flat;
                                    next_flat->prev = flat1;
                                    flat1->prev = NULL;
                                    flats = flat1;
                                }
                                else{
                                    flat1->prev->next = flat1->next;
                                    flat1->next->prev = flat1->prev;
                                    flats->next = flat1;
                                    flat1->prev = flats;
                                    flat1->next = next_flat;
                                    next_flat->prev = flat1;
                                    flats = flats->next;
                                }
                                
                            }
                            apt->max_bandwidth += flat1->initial_bandwidth;
                            iter->max_bandwidth -= flat1->initial_bandwidth;
                            counter++;
                        }
                        flat1 = flat1->next;
                    }
                }
                iter = iter->next;
            }while(iter != head);
            i++;
        }
    }
}
