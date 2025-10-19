#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FAQ {
    char question[100];
    char answer[200];
    struct FAQ *next;
};

struct FAQ *faqHead = NULL;

void addFAQ(const char *question, const char *answer) {
    struct FAQ *newFAQ = (struct FAQ *)malloc(sizeof(struct FAQ));
    if (!newFAQ) {
        printf("Memory allocation failed for FAQ.\n");
        return;
    }
    strcpy(newFAQ->question, question);
    strcpy(newFAQ->answer, answer);
    newFAQ->next = NULL;

    if (faqHead == NULL) {
        faqHead = newFAQ;
    } else {
        struct FAQ *temp = faqHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newFAQ;
    }
}

char* searchFAQ(const char *query) {
    struct FAQ *temp = faqHead;
    while (temp != NULL) {
        if (strstr(query, temp->question) != NULL) {
            return temp->answer;
        }
        temp = temp->next;
    }
    return NULL;
}

struct Stack {
    char query[100];
    struct Stack *next;
};

struct Stack *top = NULL;

void pushQuery(const char *query) {
    struct Stack *newNode = (struct Stack *)malloc(sizeof(struct Stack));
    if (!newNode) {
        printf("Memory allocation failed for Stack.\n");
        return;
    }
    strcpy(newNode->query, query);
    newNode->next = top;
    top = newNode;
}

void displayRecentQueries() {
    printf("\n--- Recent Queries ---\n");
    if (top == NULL) {
        printf("No recent queries yet.\n");
        return;
    }
    struct Stack *temp = top;
    while (temp != NULL) {
        printf("%s\n", temp->query);
        temp = temp->next;
    }
}

struct Chat {
    char message[200];
    struct Chat *next;
};

struct Chat *front = NULL, *rear = NULL;

void enqueueChat(const char *msg) {
    struct Chat *newNode = (struct Chat *)malloc(sizeof(struct Chat));
    if (!newNode) {
        printf("Memory allocation failed for Chat.\n");
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

void showMenu() {
    printf("=====================================\n");
    printf("     HEALTHCARE CHATBOT SYSTEM       \n");
    printf("=====================================\n");
    printf("Ask about: fever, cold, cough, headache\n");
    printf("Commands:\n");
    printf("  history - View full chat history (Queue)\n");
    printf("  recent  - View recent queries (Stack)\n");
    printf("  exit    - Quit chatbot\n");
    printf("=====================================\n");
}

void getUserInput(char *query, int size) {
    printf("\nYou: ");
    if (fgets(query, size, stdin)) {
        size_t len = strlen(query);
        if (len > 0 && query[len - 1] == '\n') {
            query[len - 1] = '\0';
        }
    }
}

int main() {
    char query[100];
    char *answer;

    addFAQ("fever", "Take rest, drink fluids, and consult a doctor if high fever persists.");
    addFAQ("cold", "Stay warm, drink ginger tea, and take steam inhalation.");
    addFAQ("headache", "Drink water, take rest, and avoid stress. Consult a doctor if severe.");
    addFAQ("cough", "Drink warm water, avoid cold drinks, and take honey with ginger.");

    showMenu();

    while (1) {
        getUserInput(query, sizeof(query));

        if (strcmp(query, "exit") == 0) {
            printf("\nChatbot: Take care! Always consult a doctor for serious issues.\n");
            break;
        } else if (strcmp(query, "history") == 0) {
            displayChatHistory();
            continue;
        } else if (strcmp(query, "recent") == 0) {
            displayRecentQueries();
            continue;
        }

        answer = searchFAQ(query);

        if (answer != NULL) {
            printf("Chatbot: %s\n", answer);
            enqueueChat(answer);
        } else {
            printf("Chatbot: Sorry, I don’t have info on that. Please consult a doctor.\n");
            enqueueChat("Unknown query – doctor consultation advised.");
        }

        pushQuery(query);
    }

    return 0;
}
