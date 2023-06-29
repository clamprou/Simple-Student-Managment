#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "student.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printMenu(){
    printf("\n\n");
    printf("1:To add a new student\n2:To delete a student\n3:To Search for a student\n4:To change a students data\n5:To see all students data\n6:To exit\n\n");
    printf("\n\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print(node s_node){
    if(s_node!=NULL){
        printf("The student with the id %d is %s\n",s_node->data.id,s_node->data.name);
    }else printf("Couldnt find student\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printstudents(node head){
    node holder = head;
    int i = 0;

    while(holder!=NULL){
        printf("id:%d name:%s\n",holder->data.id,holder->data.name);
        holder = holder->next;
        i++;
    }
    if(i==0) printf("NO STUDENT YET\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
node findStudent(node head,int s_id){
    node holder = head;
    
    while(holder!=NULL){
        
        if(holder->data.id==s_id){
            return holder;
        }
        
        holder = holder->next;
    }

    return NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
list create_list_first(){

    list l = (list) malloc(sizeof(struct _list));
    if (l==NULL){
        printf("couldnt create list\n");
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    
    return l;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
node addStudent(list l , int s_id , char* s_name){
    node n = (node) malloc(sizeof(struct _node));
    if (n==NULL){
        printf("couldnt find memory\n");
        return NULL;
    }
    n->data.id = s_id;           
    strcpy(n->data.name,s_name);
    n->next = NULL;//pada tha einai NULL to next gt tous pros8etw apo deksia
    
    if (l->size==0){//An den uparxei kanenas
        l->head = n;
        l->tail = n;
        l->size++;
        return n;
    }
    l->size++;
    l->tail = n;
    node counter = l->head;
    while(counter->next!=NULL){//vriskei ton proigoumeno gia na ftiaksei to next tou
        counter = counter->next;
    }
    counter->next = n;
    
    return n;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void updateStudent(node head,int s_id,int new_id,char* new_name){
    
    node s_node1 = findStudent(head,s_id);//vriskei an uparxei aftos pou 8elei na ftiaksei
    node s_node2 = findStudent(head,new_id);//vriskei an uparxei aftos pou 8elei na allaksei ston proigoumeno
    
    if ((s_node1!=NULL)&&(s_node2==NULL)){//An uparxei o protos kai oxi o defteros
        s_node1->data.id = new_id;
        strcpy(s_node1->data.name,new_name);
        printf("Changes succefull\n");
        return;
    }
    if((s_node1!=NULL)&&(s_node2!=NULL)&&(s_node2->data.id==s_node1->data.id)){//An uparxei o protos kai o defteros gt mporei na 8eloume na allaksoume mono to onoma kai to id na to afisoume ido
        strcpy(s_node1->data.name,new_name);
        printf("Changes succefull\n");
        return;
    }
    if (s_node1==NULL){
        printf("The student you want to change doesnt exists\n");
        return;
    }
    if (s_node2!=NULL){
        printf("The id is already been taken\n");
        return;
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int deleteStudent(list l,int s_id){
    node temp = l->head;
    node temp1;
    int size = l->size,i=-1,j;

    node x = findStudent(l->head,s_id);

    if (size==0){
        printf("NO STUDENTS YET\n");
        return 0;
    }


    if (x==NULL){
        printf("STUDENT DOESNT EXIST\n");
        return 0;
    }

    
    if (size==1){
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->size--;
        return 1;
    }

    if (size==2){
        if(l->head->data.id==s_id){//svinei ton prwto sthn lista
            free(l->head);
            l->size--;
            l->head = l->tail;
            l->tail->next = NULL;
            return 1;
        }
        if(l->tail->data.id==s_id){//svinei ton deftero sthn list
        free(l->tail);
        l->head->next = NULL;
        l->tail = l->head;
        l->size--;
        return 1;
        }
    }

    if(size>=3){
        if(l->head->data.id==s_id){//svinei ton terma aristera ths listas
            l->head = l->head->next;
            l->size--;
            free(temp);
            return 1;
        }
        if(l->tail->data.id==s_id){//psaxnei na vrei ton protelefteo ths listas wste na diagrapsei ton telefteo kai na allaksei to next tou proigoumenou
            for(j=0;j<size;j++){
                if(temp->next->data.id==s_id){
                    free(temp->next);
                    temp->next = NULL;
                    l->tail = temp;
                    l->size--;
                    return 1;
                }
                temp = temp->next;
            }
        }
    }

    if(size>=3){//diagrafei kapio endiameso node
        while(temp->next!=x){
            temp = temp->next;
        }
        temp1 = temp->next; //the node that i want to delete
        temp->next = temp1->next;
        free(temp1);
        l->size--;
        return 1;

    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void save(char *filename,list l){
    FILE *fp = fopen(filename,"w");
    node head = l->head;

    if (fp==NULL){
        printf("Couldnt save data, the problem may be that you didnt give any name for the file use:./a <file_name>\n");
        return;
    }

    if (l->size==0){
        fclose(fp);
        return;
    }

    fwrite(&l->size,sizeof(int),1,fp);//to proto pragma pou grafei einai enas ari8mos intiger wste na kserw otan 8a kanw load posa students exw na kanw load

    while(head!=NULL){//meta ton ari8mo afton amesos grafei to id kai dipla to onoma ka8e student
        fwrite(&head->data.id,sizeof(int),1,fp);
        fwrite(head->data.name,sizeof(char),MAXSTRING,fp);
        head = head->next;
    }
    fclose(fp);
    return;
}    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void load(char *filename,list l){
    FILE *fp = fopen(filename,"r");
    int size_students,i,id;
    long size;
    char name[MAXSTRING];
    node n;
    if (fp!=NULL){
        fseek(fp,0,SEEK_END);
        size = ftell(fp);    

        if (size!=0){//vlepei an o fakelos einai adios afou an einai adios to fseek 8a minei sthn arxh ara sthn 8esh 0 bytes
            rewind(fp);//paw ton dixth sthn arxh afou an den einai adios 8a exei metakini8ei
            fread(&size_students,sizeof(int),1,fp);
            for(i=0;i<size_students;i++){
                fread(&id,sizeof(int),1,fp);
                fread(name,sizeof(char),MAXSTRING,fp);
                n = addStudent(l,id,name);//kalw thn add student na ta valei monh ths
            }
            return;
        }
    }

    fclose(fp);
    return;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////