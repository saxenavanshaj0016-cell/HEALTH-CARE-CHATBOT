#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//queue – chat history 
struct Chat {
    char message[200];
    struct Chat *next;
};

struct Chat *front = NULL, *rear = NULL;

//add new message to chat history
void enqueueChat(char *msg) {
    struct Chat *newNode = (struct Chat *)malloc(sizeof(struct Chat));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newNode->message, msg);
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}
// full chat history
void displayChatHistory() {
    printf("\n--- Chat History ---\n");

    if (front == NULL) {
        printf("No chat history yet.\n");
        return;
    }
    struct Chat *temp = front;
    while (temp != NULL) {
        printf("%s\n", temp->message);
        temp = temp->next;
    }
}

// stack–recent queries
struct Stack {
    char query[100];
    struct Stack *next;
};

struct Stack *top = NULL;

//push new query to stack
void pushQuery(char *query) {
    struct Stack *newNode = (struct Stack *)malloc(sizeof(struct Stack)); 
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newNode->query, query);
    newNode->next = top;
    top = newNode;
}
// display recent queries
void displayRecentQueries() {
    printf("\n--- Recent Queries ---\n");

    if (top == NULL) {
        printf("No recent queries.\n");
        return;
    }

    struct Stack *temp = top;
    while (temp != NULL) {
        printf("%s\n", temp->query);
        temp = temp->next;
    }
}

//main function 

//demo

int main() {
    //add chats to history (Queue)
    enqueueChat("User: I have a headache.");
    enqueueChat("Bot: Try resting and staying hydrated.");
    enqueueChat("User: I also have a slight fever.");
    enqueueChat("Bot: Monitor temperature and rest. See a doctor if it persists.");

    //add queries (stack)
    pushQuery("headache");
    pushQuery("fever");
    pushQuery("cold and cough");

    // Display results
    displayChatHistory();
    displayRecentQueries();

    return 0;
}
