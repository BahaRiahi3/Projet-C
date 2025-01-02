#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define FILE_NAME "scores.txt"

void clearScreen() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/MacOS
#endif
}

// Fonction pour choisir la taille du plateau en fonction du niveau
int chooseDifficulty() {
    int choice;
    printf("choose the difficulty :\n");
    printf("1. easy (2x2)\n2. medium (4x4)\n3. HARD!! (6x6)\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: return 2;  
        case 2: return 4;  
        case 3: return 6;  
        default: return 4;  
    }
    // depending on the choice made by the user, the size of the board will be 
    // either 2by2, 4by4 or 6by6 and the default case is going to be 4by4
}


void initializeBoard(char **board, char **values, int size) {
    int pairs = (size * size) / 2;
    int used[pairs];
    memset(used, 0, sizeof(used));

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int random;
            do {
                random = rand() % pairs + 'A';
            } while (used[random - 'A'] >= 2);

            values[i][j] = random;
            used[random - 'A']++;
            board[i][j] = '*';
        }
    }
}


void displayBoard(char **board, int size) {
    printf("\n   ");
    for (int i = 0; i < size; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d  ", i);
        for (int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}


void saveScore(const char *name, int attempts, int timeSpent) {
    FILE *file = fopen(FILE_NAME, "a");  // Open file in append mode
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier des scores.\n");
        return;
    }
    // Write player name, attempts, and time to the file
    fprintf(file, "%s %d %d\n", name, attempts, timeSpent);
    fclose(file);
    printf("Votre score est enregistre.\n");
}


void displayScores() {
    FILE *file = fopen(FILE_NAME, "r");  // Open file in read mode
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier des scores.\n");
        return;
    }

    char name[MAX_NAME_LEN];
    int attempts, timeSpent;

    printf("\nScores pr�c�dents :\n");
    while (fscanf(file, "%s %d %d", name, &attempts, &timeSpent) != EOF) {
        printf("%s - %d tentatives, %d secondes\n", name, attempts, timeSpent);
    }

    fclose(file);
}

int main() {
    int size = chooseDifficulty();
    char **board = (char **)malloc(size * sizeof(char *));
    char **values = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        board[i] = (char *)malloc(size * sizeof(char));
        values[i] = (char *)malloc(size * sizeof(char));
    }

    initializeBoard(board, values, size);
    displayBoard(board, size);

    int pairsFound = 0;
    int attempts = 0;
    clock_t start = clock(); 

    while (pairsFound < (size * size) / 2) {
        int x1, y1, x2, y2;

        printf("\nChoisissez la premiere carte (ligne colonne) : ");
        scanf("%d %d", &x1, &y1);
        printf("Choisissez la deuxieme carte (ligne colonne) : ");
        scanf("%d %d", &x2, &y2);

        if (board[x1][y1] != '*' || board[x2][y2] != '*' || (x1 == x2 && y1 == y2)) {
            printf("Choix invalide, essayez encore.\n");
            continue;
        }
        clearScreen(); // Clear the screen before each input

        // Retourner les cartes
        board[x1][y1] = values[x1][y1];
        board[x2][y2] = values[x2][y2];
        clearScreen(); // Clear the screen before each input

        displayBoard(board, size);

        if (values[x1][y1] == values[x2][y2]) {
            printf("Paire trouvee !\n");
            pairsFound++;
        } else {
            printf("Pas une paire. Try again!\n");
            board[x1][y1] = '*';
            board[x2][y2] = '*';
        }
        attempts++;
    }

    clock_t end = clock(); 
    int timeSpent = (int)((end - start) / CLOCKS_PER_SEC);

    printf("\nFelicitations ! Vous avez trouv� toutes les paires en %d tentatives.\n", attempts);
    printf("Temps coulé : %d secondes.\n", timeSpent);


    char playerName[MAX_NAME_LEN];
    printf("Entrez votre nom : ");
    scanf("%s", playerName);
    saveScore(playerName, attempts, timeSpent);


    displayScores();


    for (int i = 0; i < size; i++) {
        free(board[i]);
        free(values[i]);
    }
    free(board);
    free(values);

    return 0;
}
