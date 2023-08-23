#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_CANDIDATES 10

typedef struct {
    char username[50];
    char password[50];
    int isCandidate;
    int hasVoted;
} User;

typedef struct {
    char username[50];
    char password[50];
    char position[50];
    int votesReceived;
} Candidate;

User users[MAX_USERS];
int userCount = 0;

Candidate candidates[MAX_CANDIDATES];
int candidateCount = 0;

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Registration failed.\n");
        return;
    }

    User newUser;

    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    newUser.isCandidate = 0;
    newUser.hasVoted = 0;

    users[userCount] = newUser;
    userCount++;

    printf("Registration successful!\n");
}

User *login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return &users[i];
        }
    }

    printf("Login failed.\n");
    return NULL;
}

void registerCandidate(User *user) {
    if (candidateCount >= MAX_CANDIDATES) {
        printf("Candidate limit reached. Nomination failed.\n");
        return;
    }

    Candidate newCandidate;

    strcpy(newCandidate.username, user->username);
    strcpy(newCandidate.password, user->password);

    printf("Enter candidate's position: ");
    scanf("%s", newCandidate.position);

    newCandidate.votesReceived = 0;

    candidates[candidateCount] = newCandidate;
    candidateCount++;

    user->isCandidate = 1;

    printf("Candidate nomination successful!\n");
}

void vote(User *voter) {
    if (voter->hasVoted) {
        printf("You have already voted.\n");
        return;
    }

    if (candidateCount == 0) {
        printf("No candidates available for voting.\n");
        return;
    }

    printf("Available candidates:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s (%s)\n", i + 1, candidates[i].username, candidates[i].position);
    }

    int choice;
    printf("Enter the number of your chosen candidate: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= candidateCount) {
        candidates[choice - 1].votesReceived++;
        voter->hasVoted = 1;
        printf("Vote cast successfully!\n");
    } else {
        printf("Invalid candidate choice.\n");
    }
}

void displayResults() {
    printf("Election Results:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%s (%s): %d votes\n", candidates[i].username, candidates[i].position, candidates[i].votesReceived);
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Nominate as Candidate\n");
        printf("4. Vote\n");
        printf("5. Display Results\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2: {
                User *loggedInUser = login();
                if (loggedInUser) {
                    if (loggedInUser->isCandidate) {
                        printf("Logged in as a candidate.\n");
                    } else {
                        printf("Logged in as a voter.\n");
                    }
                }
                break;
            }
            case 3: {
                User *loggedInUser = login();
                if (loggedInUser) {
                    if (loggedInUser->isCandidate) {
                        printf("You are already a candidate.\n");
                    } else {
                        registerCandidate(loggedInUser);
                    }
                }
                break;
            }
            case 4: {
                User *loggedInUser = login();
                if (loggedInUser) {
                    if (!loggedInUser->isCandidate) {
                        vote(loggedInUser);
                    } else {
                        printf("Candidates are not allowed to vote.\n");
                    }
                }
                break;
            }
            case 5:
                displayResults();
                break;
            case 0:
                printf("Exiting the application.\n");
                break;
            default:
                printf("Invalid choice. Please select again.\n");
        }
    } while (choice != 0);

    return 0;
}
