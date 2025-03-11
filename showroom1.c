#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIKES 500
#define MAX_SHOWROOMS 100
#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 50

typedef struct {
    char model[50];
    char manufacturer[50];
    float price;
    char showroomCity[50];
    char showroomLocation[100];
} Bike;

typedef struct {
    char city[50];
    char location[100];
} Showroom;

// Function Prototypes
void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
int authenticateAdmin();
void addAdmin();
void deleteAdmin();
void addBike();
void showBikes();
void addShowroom();
void showShowrooms();
void searchBike();
void searchShowroom();
void saveBikesToFile();
void loadBikesFromFile();
void saveShowroomsToFile();
void loadShowroomsFromFile();

int main() {
    loadBikesFromFile();
    loadShowroomsFromFile();
    int choice;
    while (1) {
        displayMainMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
            case 1:
                if (authenticateAdmin())
                    {
                        while (1)
                        {
                        displayAdminMenu();
                        printf("Enter choice: ");
                        scanf("%d", &choice);
                        getchar();
                        if (choice == 1) { addBike(); saveBikesToFile(); }
                        else if (choice == 2) showBikes();
                        else if (choice == 3) { addShowroom(); saveShowroomsToFile(); }
                        else if (choice == 4) showShowrooms();
                        else if (choice == 5) addAdmin();
                        else if (choice == 6) deleteAdmin();
                        else if (choice == 7) break;
                        else printf("Invalid choice.\n");
                        }
                    }
                    else{
                        printf("Username or password is incorrect.\n");
                    }
                    
                
                
                break;
            case 2:
                while (1) {
                    displayUserMenu();
                    printf("Enter choice: ");
                    scanf("%d", &choice);
                    getchar();
                    if (choice == 1) showShowrooms();
                    else if (choice == 2) showBikes();
                    else if (choice == 3) searchBike();
                    else if (choice == 4) searchShowroom();
                    else if (choice == 5) break;
                    else printf("Invalid choice.\n");
                }
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

void displayMainMenu() {
    printf("\n1. Admin\n2. User\n");
}
void displayAdminMenu() {
    printf("\n1. Add Bike\n2. Show Bikes\n3. Add Showroom\n4. Show Showrooms\n5. Add Admin\n6. Delete Admin\n7. Exit\n");
}
void displayUserMenu() {
    printf("\n1. Show Showrooms\n2. Show Bikes\n3. Search Bike\n4. Search Showroom\n5. Exit\n");
}

void addBike() {
    FILE *file = fopen("bikes.txt", "a");
    if (!file) { printf("Error opening file.\n"); return; }
    Bike b;
    printf("Enter model: "); 
    fgets(b.model, 50, stdin); 
    strtok(b.model, "\n");
    printf("Enter manufacturer: "); 
    fgets(b.manufacturer, 50, stdin); 
    strtok(b.manufacturer, "\n");
    printf("Enter price: "); 
    scanf("%f", &b.price); 
    getchar();
    printf("Enter showroom city: "); 
    fgets(b.showroomCity, 50, stdin); 
    strtok(b.showroomCity, "\n");
    printf("Enter showroom location: "); 
    fgets(b.showroomLocation, 100, stdin); 
    strtok(b.showroomLocation, "\n");
    fprintf(file, "%s\n%s\n%.2f\n%s\n%s\n", b.model, b.manufacturer, b.price, b.showroomCity, b.showroomLocation);
    fclose(file);
    printf("Bike added!\n");
}


    void showBikes() {
        FILE *file = fopen("bikes.txt", "r");
        if (!file) { 
            printf("No bikes found.\n"); 
            return; 
        }
    
        Bike b;
        printf("\nAvailable Bikes:\n");
        
        while (fgets(b.model, sizeof(b.model), file) &&
               fgets(b.manufacturer, sizeof(b.manufacturer), file) &&
               fscanf(file, "%f\n", &b.price) &&
               fgets(b.showroomCity, sizeof(b.showroomCity), file) &&
               fgets(b.showroomLocation, sizeof(b.showroomLocation), file)) {
    
            // Remove newline characters at the end of strings
            strtok(b.model, "\n");
            strtok(b.manufacturer, "\n");
            strtok(b.showroomCity, "\n");
            strtok(b.showroomLocation, "\n");

            printf("\n---------------------------\n");
            printf("Model       : %s\n", b.model);
            printf("Manufacturer: %s\n", b.manufacturer);
            printf("Price       : %.2f\n", b.price);
            printf("City        : %s\n", b.showroomCity);
            printf("Location    : %s\n", b.showroomLocation);
            printf("---------------------------\n");
        }
        
        fclose(file);
    }
    
        
        
    
    
    
    

void addShowroom() {
    FILE *file = fopen("showrooms.txt", "a");
    if (!file) { printf("Error opening file.\n"); return; }
    Showroom s;
    printf("Enter city: "); fgets(s.city, 50, stdin); strtok(s.city, "\n");
    printf("Enter location: "); fgets(s.location, 100, stdin); strtok(s.location, "\n");
    fprintf(file, "%s,%s\n", s.city, s.location);
    fclose(file);
    printf("Showroom added!\n");
}

void showShowrooms() {
    FILE *file = fopen("showrooms.txt", "r");
    if (!file) { 
        printf("No showrooms found.\n"); 
        return; 
    }

    Showroom s;
    printf("\nAvailable Showrooms:\n");
    
    while (fgets(s.city, sizeof(s.city), file) &&
           fgets(s.location, sizeof(s.location), file)) {

        strtok(s.city, "\n");
        strtok(s.location, "\n");

        printf("\n---------------------------\n");
        printf("City    : %s\n", s.city);
        printf("Location: %s\n", s.location);
        printf("---------------------------\n");
    }
    
    fclose(file);
}

    


void searchBike() {
    char query[50];
    printf("Enter bike model to search: ");
    fgets(query, 50, stdin); strtok(query, "\n");
    FILE *file = fopen("bikes.txt", "r");
    if (!file) { printf("No bikes found.\n"); return; }
    Bike b; int found = 0;
    while (fscanf(file, "%[^,],%[^,],%f,%[^,],%[^\n]\n", b.model, b.manufacturer, &b.price, b.showroomCity, b.showroomLocation) != EOF) {
        if (strcmp(b.model, query) == 0) {
            printf("Model: %s, Manufacturer: %s, Price: %.2f, City: %s, Location: %s\n", b.model, b.manufacturer, b.price, b.showroomCity, b.showroomLocation);
            found = 1;
        }
    }
    if (!found) printf("Bike not found.\n");
    fclose(file);
}

void searchShowroom() {
    char query[50];
    printf("Enter showroom city to search: ");
    fgets(query, 50, stdin); strtok(query, "\n");
    FILE *file = fopen("showrooms.txt", "r");
    if (!file) { printf("No showrooms found.\n"); return; }
    Showroom s; int found = 0;
    while (fscanf(file, "%[^,],%[^\n]\n", s.city, s.location) != EOF) {
        if (strcmp(s.city, query) == 0) {
            printf("City: %s, Location: %s\n", s.city, s.location);
            found = 1;
        }
    }
    if (!found) printf("Showroom not found.\n");
    fclose(file);
}

// Function to add a new admin
void addAdmin() {
    FILE *file = fopen("admins.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];

    printf("Enter new admin username: ");
    scanf("%s", username);
    printf("Enter new admin password: ");
    scanf("%s", password);

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("Admin added successfully!\n");
}

// Function to delete an admin
void deleteAdmin() {
    char username[MAX_NAME_LEN];
    printf("Enter admin username to delete: ");
    scanf("%s", username);

    FILE *file = fopen("admins.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        perror("Error opening file");
        return;
    }

    char fileUsername[MAX_NAME_LEN];
    char filePassword[MAX_PASS_LEN];
    int found = 0;

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(fileUsername, username) != 0) {
            fprintf(temp, "%s %s\n", fileUsername, filePassword);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("admins.txt");
    rename("temp.txt", "admins.txt");

    if (found) {
        printf("Admin deleted successfully!\n");
    } else {
        printf("Admin not found!\n");
    }
}

// Admin authentication
int authenticateAdmin() {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];

    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin password: ");
    scanf("%s", password);

    FILE *file = fopen("admins.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char fileUsername[MAX_NAME_LEN];
    char filePassword[MAX_PASS_LEN];

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(fileUsername, username) == 0 && strcmp(filePassword, password) == 0) {
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0; // Authentication failed
}

void saveBikesToFile() {
    // saving bikes to file
}

void loadBikesFromFile() {
    // loading bikes from file
}

void saveShowroomsToFile() {
    // saving showrooms to file
}

void loadShowroomsFromFile() {
    // loading showrooms from file
}
