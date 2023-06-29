#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//////////////////////////////////////////////////////////////////////////////

int main (int argc , char **argv){
    int s_id,new_id,update_student,resault;
    char s_name[MAXSTRING],x;
    node s_node;
    node n;
    node student_to_del;
    node head,temp;
    list l;
    l = create_list_first();
    load(argv[1],l);
    printMenu();
    do{
        scanf("%c",&x);
        switch(x){
           case '1': //Add
           do{
           printf("Give student id:");
           scanf("%d",&s_id);
           }while(s_id<0);
           printf("Give student name:");
           scanf("%s",s_name);
           s_node = findStudent(l->head,s_id);//to see if student id already exists if NULL no else yes
           if (s_node==NULL){
              n = addStudent(l,s_id,s_name);
              if (n==NULL) printf("memory full\n"); else printf("Add was successfull\n");
           }else printf("A student with this id already exists\n");

           break;
           case '2': //Delete
           printf("Give student id:");
           scanf("%d",&s_id);
           printf("\n");
           resault = deleteStudent(l,s_id);
           if (resault==1) printf("Delete was successful\n");// else printf("couldnt delete, student may not exists\n");

           break;
           
           case '3': //Search
           printf("Give student id:");
           scanf("%d",&s_id);
           printf("\n");
           s_node = findStudent(l->head,s_id);
           print(s_node);
           break;
           case '4': //Change
           printf("Give student id that you want to update:");
           scanf("%d",&s_id);
           printf("\n");
           printf("Give a new id:");
           scanf("%d",&new_id);
           printf("\n");
           printf("Give a new name:");
           scanf("%s",s_name);
           printf("\n");
           updateStudent(l->head,s_id,new_id,s_name);
           break;
           case '5': //All
           printstudents(l->head);

           break;
           case '6': //Exit

           save(argv[1],l);

           

           break;
           default : break; 
        }
        
    
   }while (x!='6');

 //free all nodes and list
   
   head = l->head;

   if(l->size>=1){
      while(head!=NULL){
         temp = head;
         head = head->next;
         free(temp);
      }
   }


   free(l);
   return 0;
}