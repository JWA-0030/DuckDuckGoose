//Jesse Alsing
//3/26/2017
//COP 3502

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct used to form a linked list of integers.
struct ll {
  char name[20];
  struct ll *next;
};

void print(struct ll *front);
void freelist(struct ll *front);
struct ll* insert_front(struct ll *front, char name[]);
struct ll* insert_inorder(struct ll *front, char name[]);
struct ll* insert_back(struct ll *front, char name[]);
void delete_node(struct ll *front);

int main() {


    int num_games, i, num_names, j, rounds, ducks, m, n, empty;

    char name[20];

   // printf("enter numcases:");
    scanf("%d", &num_games);

    for(i=1; i <= num_games; i++)
    {

        struct ll *randlist=NULL;
        struct ll *inorderlist=NULL;

       // printf("Enter numstudents:");
        scanf("%d", &num_names);

        for(j=0; j< num_names; j++)
        {
            scanf("%s", name);
            randlist = insert_back(randlist, name);
        }

        //printf("Enter the number of rounds:");
        scanf("%d", &rounds);

       // printf("Enter the number of Ducks:");
        scanf("%d", &ducks);

        for(m=0; m<rounds; m++)
        {
            for(n = 0; n < ducks; n++)
            {
                randlist = randlist->next;
            }
            if(strcmp(randlist, randlist->next) == 0)
            {
                empty = 1;
            }
            delete_node(randlist);
        }

        printf("Game %d:\n", i);
        //print(randlist);
        struct ll* iter = randlist;

        do {
            //printf("\nInserting...%s-> %s\n", inorderlist, iter);
            inorderlist = insert_inorder(inorderlist, iter);
           //print(inorderlist);
            iter = iter->next;
            // Here we check if the next element is back to the front, if so, we stop!
        }while(iter != randlist);

        if(empty == 1)
        {
            printf("Jimmy has friends no more.\n\n");
            empty = 0;
        }

        else
            print(inorderlist);

        freelist(randlist);
        freelist(inorderlist);
        freelist(iter);
    }
  return 0;
}

// Pre-condition: front points to the head of a circular linked list.
// Post-condition: each value in the list will be printed.
void print(struct ll *front) {

  struct ll* iter = front;

  // If the list is empty just print a blank line.
  if (front == NULL) {
    printf("Jimmy has friends no more.\n");
    return;
  }

  // Now, iterate through each element, printing.
  do {
    printf("%s\n", iter->name);
    iter = iter -> next;

  // Here we check if the next element is back to the front, if so, we stop!
  } while (iter != front);

  // Go to the next line.
  printf("\n");
}


// Pre-condition: front points to the head of a circular linked list and also takes in a name to be inserted
// Post-condition: a new node storing name will be inserted to the front of
//                 this list and a pointer to this node will be returned.
struct ll* insert_front(struct ll *front, char name[]) {

  struct ll *temp, *iter;

  // Create temp node and store the value.
  temp = (struct ll*)malloc(sizeof(struct ll));
  strcpy(temp->name, name);

  // We are adding to an empty list.
  if (front == NULL) {
     // In a circular list, this means link to yourself...
     temp->next = temp;
  }

  // Here we add to an existing list.
  else {

     // Link our new node to the first element in the old list.
     temp->next = front;

     // Iterate to the last element in the old list.
     iter = front;
     while (iter->next != front)
       iter = iter->next;

     // Now, this needs to relink to our new first element, temp.
     iter->next = temp;
   // printf("\n****%s***\n", temp);
  }

  // Return the new front of the list.
  //printf("\n****%s***\n", temp);
  return temp;
}

// Pre-condition: front points to the head of a linked list structure and name to be inserted.
// Post-condition: a new node containing name will be created and added
//                 to the end of the linked listed pointed to by front.
struct ll* insert_back(struct ll *front, char name[]) {

  struct ll *temp, *iter;

  // Create temp node and store the value.
  temp = (struct ll*)malloc(sizeof(struct ll));
  strcpy(temp->name, name);

  // We are adding to an empty list.
  if (front == NULL) {

     // In a circular list, this means link to yourself...
     temp->next = temp;

     // Return the new front of the list.
     return temp;
  }

  // Here we add to an existing list.
  else {

     // Link our new node to the first element in the old list.
     temp->next = front;

     // Iterate to the last element in the old list.
     iter = front;
     while (iter->next != front)
       iter = iter->next;

     // Now, this needs to relink to our new first element, temp.
     iter->next = temp;

     // This STAYS as the front of our list!
     return front;
  }

}


// Pre-condition: front points to the head of a linked list and a name to be inserted.
// Post-condition: a new node containing name will be created and added
//                 into the appropriate position in the linked list
//                 front and a pointer to the front of this new linked
//                 list will be returned.
struct ll* insert_inorder(struct ll *front, char name[]) {

  struct ll *temp;
  struct ll *iter;
  struct ll *savelink;
//THIS WORKS
  // Take care of the case where we insert into the front of the list.
  if (front == NULL || strcmp(name, front) < 0)
    return insert_front(front, name);

         // Create the new node.
  temp = (struct ll*)malloc(sizeof(struct ll));

  strcpy(temp->name, name);
 // printf("\nNAME PASSED IF IN ORDER %s***\n", name); PROVEN TRUE
  temp->next = NULL;

  // Start iter at the front of the linked list.
  iter = front;
    // printf("\nNAME PASSED IF IN ORDER %s***\n", iter); PROVEN TRUE

  // Use iter to iterate to the right spot to insert temp.
  // We stop if the node after iter is pointing back to the front of the list.
  while (strcmp(iter->next,front) != 0 && strcmp(name, iter->next) > 0)
    iter = iter->next;

  // Save the node to patch to.
  savelink = iter->next;
  //printf("\nSPIT OUT OF STRCMP %s.\n", savelink);
  //printf("\n***%s***\n", savelink);

  // Insert temp.
  iter->next = temp;
  temp->next = savelink;

  // Return a pointer to the front of the list.
  return front;

}
// Pre-condition: front points to a linked list.
// Post-condition: All the memory for the linked list pointed to by front is
//                 freed for use.

void freelist(struct ll *front){
    //Length = 0, 1 cases.
    if (front == NULL) return;

    if (front == front->next){
        free(front);
        return;
    }

    //Mark the front.
    struct ll* tmp = front;

    //Use tmp to delete nodes, one by one.
    tmp = tmp->next;
    while (tmp != front) {
        struct ll* del = tmp;
        tmp = tmp->next;
        free(del);
    }
    //Free at last!
    free(tmp);
}

//Pre-condition: front points to the head of a linked list.
//Post-condition: deletes a node at position front and returns the new head of the linked list.
void delete_node(struct ll *front) {

   struct ll *temp = front->next;

   strcpy(front->name, temp->name);
   front->next = temp->next;
   free(temp);

}
