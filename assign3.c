#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 5

// Structure definition of an event aggregate data type
struct event{
int hour;//between 0 and 23 inclusive
int minute;//between 0 and 59 inclusive
char description[41];//a valid string describing the event
};
typedef struct event Event;//create alias foe event

/*
PURPOSE:to read the range from the user
INPUT:integer for minimum number, integer for maximum number
OUTPUT:returns the integer value for range
*/
int InputRange(int min, int max);
/*
PURPOSE:to input event data from user
INPUT:pointer variable to an event
OUTPUT:returns the event pointer
*/
Event* InputEvent(Event *newEvent);
/*
PURPOSE:to add an event at a specified index, overwriting any previous event at that index
INPUT:an array of events,a specified event to add, and the index where the event should be added
OUTPUT:return the index of the event added
*/
int AddEventAtIndex(Event list[], Event e, int i);
/*
PURPOSE:to insert an event at a specified index and update the size, keeping the list sorted
INPUT:array of events,pointer to integer of the size of the array, and a specific event
OUTPUT:returns the index of where the event is added
*/
int InsertionSortEvent(Event list[], int *p_size, Event e);
/*
PURPOSE:to display one event
INPUT:an event
OUTPUT:no output, just displays event to the screen
*/
void DisplayEvent(Event e);
/*
PURPOSE:too display the entire event list
INPUT:array of events,and the size of the array
OUTPUT:no output, just displays the event list to the screen
*/
void DisplayEventList(Event list[], int size);
/*
PURPOSE:to delete an event at a specified index and update the list accordingly
INPUT:array of events, index of event to be deleted, pointer to the size of the array
OUTPUT:returns index of event deleted, or -1 if index is not in range
*/
int DeleteEvent(Event list[], int i, int *p_size);
/*
PURPOSE:to save and write the event list to a file specified by the user
INPUT:string specifying the file name,array of events,and size of the array
OUTPUT:returns number of events added,or -1 if something went wrong
*/
int SaveEventList(char *filename,Event list[],int size);
/*
PURPOSE:to read a file and replace the event list
INPUT:string specifying file name, array of events,pointer to size of the array
OUTPUT:returns number of events added
*/
int LoadEventList(char *filename,Event list[],int *p_size);
/*
PURPOSE:to replace space characters with underscore characters
INPUT:string to be encoded
OUTPUT:returns pointer to the string
*/
char* encode(char*s);
/*
PURPOSE:to replace underscore characters with space
INPUT:string to be decoded
OUTPUT:returns pointer to the string
*/
char* decode(char*s);

int eventListSize=0;//size of the whole array

int main(){
  Event EventList[MAX]; //array of events
  char filenameW[41];//file name to write to
  char filenameR[41];//file name to read from
  int s;//switch case variable
  int d;//delete event variable
  //menu
  do{
    printf("1. Schedule an event.\n2. Delete an event.\n3. Display schedule.\n");
    printf("4. Save schedule.\n5. Load schedule.\n6. Exit\n");
    printf("==> Please enter an integer between 1 and 6: ");
    scanf("%d",&s);
    switch(s){
      case 1:
              if(eventListSize>=MAX){
                printf("The maximum number of events you can add to the schedule has been reached!\n");
                printf("We apologize for any inconvenience this may cause.\n");
                break;
              }
              InsertionSortEvent(EventList,&eventListSize,*InputEvent(&EventList[eventListSize]));
              break;
      case 2:
                if(eventListSize==0){
                printf("You need to have an event to delete first...\n");
                break;
                }
              printf("Which event you like to delete or -1 to cancel?\n");
              printf("Please enter an integer between -1 and %d: ",eventListSize-1);
              scanf("%d",&d);
              if(d==-1){
                break;
              }
              else{
                DeleteEvent(EventList, d, &eventListSize);
              }
              break;
      case 3:
                if(eventListSize==0){
                  printf("You need to have an event to display first...\n");
                  break;
                }
              DisplayEventList(EventList,eventListSize);
              break;
      case 4:
              printf("File name: ");
              scanf("%s",filenameW);
              printf("%d events saved into schedule file named %s\n",SaveEventList(filenameW,EventList,eventListSize),filenameW);
              break;
      case 5:
              printf("This action will replace the current schedule.\n");
              printf("File name (or \"abort\" to cancel operation): ");
              scanf("%s",filenameR);
              if(strcmp(filenameR,"abort")==0){
                break;
              }
              printf("%d events loaded into schedule file named %s\n",LoadEventList(filenameR,EventList,&eventListSize),filenameR);
              break;
      case 6:printf("Goodbye...\n");
             break;
      default:printf("Invalid input\n");
              break;
    }
  }while(s!=6);

}

int InputRange(int min, int max){
  int range;//range entered by user
  do{
  printf("Please enter an integer between %d and %d: ",min,max);
  scanf("%d",&range);
  if(range<min || range>max){
    printf("Invalid input\n");
  }
}while(range<min || range>max);
return range;
}

Event* InputEvent(Event *newEvent){

  if (newEvent != NULL) // quality assurance:
 // make sure the pointer is valid
 {
 printf("Enter the event time:\n");
 newEvent->hour = InputRange(0, 23);
 newEvent->minute = InputRange(0, 59);
 printf("Enter the event description: ");
 scanf(" %[^\n]",newEvent->description);

}
eventListSize++;//we added an event so increase size
return newEvent;

}

int AddEventAtIndex(Event list[], Event e, int i){
  list[i].hour=e.hour;
  list[i].minute=e.minute;
  strcpy(list[i].description,e.description);

return i;//return index
}

int InsertionSortEvent(Event list[], int *p_size, Event e){
  //check if we have space to add an event
  int thour;//temporary hour variable to swap
  int tmin;//temporary variable to swap minute
  char temp[41];//to swap strings
  int index;//index of the event e
  AddEventAtIndex(list,e,*p_size);
  //SORT
  for(int i = 0;i<(*p_size);i++){
    for(int j=i+1;j<(*p_size);j++){
      //swap if previous term time is greater
      if(list[i].hour>list[j].hour){
        //swap hour
        thour=list[i].hour;
        list[i].hour=list[j].hour;
        list[j].hour=thour;
        //swap minute
        thour=list[i].minute;
        list[i].minute=list[j].minute;
        list[j].minute=thour;
        //swap string
        strcpy(temp,list[i].description);
        strcpy(list[i].description,list[j].description);
        strcpy(list[j].description,temp);
      }
      //if hour is equal,check minute
      else if(list[i].hour==list[j].hour){
        if(list[i].minute<=list[j].minute){
          continue;
        }
        else{
          //swap hour
          thour=list[i].hour;
          list[i].hour=list[j].hour;
          list[j].hour=thour;
          //swap minute
          thour=list[i].minute;
          list[i].minute=list[j].minute;
          list[j].minute=thour;
          //swap string
          strcpy(temp,list[i].description);
          strcpy(list[i].description,list[j].description);
          strcpy(list[j].description,temp);
        }
      }
      //if previous hour is smaller, continue,(its in the right spot)
      else{
        continue;
      }
    }

}
for(index=0;index<eventListSize;index++){
  if(list[index].hour==e.hour && list[index].minute==e.minute && (strcmp(list[index].description,e.description)==0)){
    break;//index has been found
  }
}
return index;//return the index
}

void DisplayEvent(Event e){
  printf("%02d:%02d %s\n",e.hour, e.minute, e.description);
}

void DisplayEventList(Event list[], int size){

  for(int i=0;i<size;i++){
    printf("[%d] ",i);
    DisplayEvent(list[i]);
  }
}

int DeleteEvent(Event list[], int i, int *p_size){
  //checks if index is out of range
  int index = i;//i is changed so we set the index to i to return at the end
  if (i<0 || i>eventListSize){
    printf("The event you want to delete does not exist\n");
    return -1;
  }
  while(i<(*p_size)-1){
    AddEventAtIndex(list,list[i+1],i);
    i++;
  }
  (*p_size)--;
  return index;//return index
}

char* encode(char*s){
  for(int i=0;i<strlen(s);i++){
    if (isspace(*(s+i))){
      *(s+i)='_';
    }
  }
  return s;
}

char* decode(char*s){
  for(int i=0;i<strlen(s);i++){
    if (*(s+i)=='_'){
      *(s+i)=' ';
    }
  }
  return s;
}

int SaveEventList(char *filename,Event list[],int size){
  FILE *fptr;//pointer to file
  fptr = fopen(filename,"w");
  int i;//counts numbers of events added
  if(fptr!=NULL){
  for(i=0;i<size;i++){
    encode(list[i].description);
    fprintf(fptr,"%d %d %s\n",list[i].hour,list[i].minute,list[i].description);//printf event record to file
  }
}
else  // safe code with informative error message
    {
        fprintf(stderr, "Error opening the file for writing.\n");   // need stdlib.h for errno
        return -1;
    }
    fclose(fptr);//close the file

return i;//return number of events
}

int LoadEventList(char *filename,Event list[],int *p_size){
FILE *fptr;//pointer to file
fptr = fopen(filename,"r");
*p_size=0;//iterator, will count number of events
if(fptr!=NULL){//check for NULL

  while(!feof(fptr) && *p_size<=MAX){//makesure there is something to read
    fscanf(fptr,"%d%d%s",&list[*p_size].hour,&list[*p_size].minute,list[*p_size].description);
      decode(list[*p_size].description);
      (*p_size)++;
  }
fclose(fptr);//close the file

}

else{  // safe code with informative error message

        fprintf(stderr, "Error opening the file for writing.\n");
        return -1;
    }
(*p_size)--;//account for the extra count
return *p_size;
}
