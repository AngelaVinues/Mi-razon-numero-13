//
// Created by serra on 1/4/2024.
//
/*
    ██╗     ██╗██████╗ ██████╗  █████╗ ██████╗ ██╗███████╗███████╗
    ██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗██║██╔════╝██╔════╝
    ██║     ██║██████╔╝██████╔╝███████║██████╔╝██║█████╗  ███████╗
    ██║     ██║██╔══██╗██╔══██╗██╔══██║██╔══██╗██║██╔══╝  ╚════██║
    ███████╗██║██████╔╝██║  ██║██║  ██║██║  ██║██║███████╗███████║
    ╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝
*/
#include "usersInfo.h"
#include "files.h"
//reserve the memory for the struct user (userInfo)
userInfo* createUserInfo(int numInitialAllocation){
    return (userInfo *)malloc(numInitialAllocation * sizeof (userInfo ));
}


//delete a user and use the space for the rest elements of the string
//indexTodelete is the index of the users array
void deleteUserInfo(userInfo* users, int* numUserPairs, int indexToDelete,char* filePath,const char *masterPassword) {
    if(indexToDelete < 0 || indexToDelete > *numUserPairs){
        fprintf(stderr, "Índice de usuario a eliminar fuera de rango\n");
        exit(1);
    }
    //reorganize the fix for fill the empty space
    for (int i = indexToDelete; i < *numUserPairs - 1; i++) {
        memcpy(&users[i],&users[i+1],sizeof(userInfo ));
    }
    //reduce the users numbers by 1
    *numUserPairs = *numUserPairs -1;

    //save the new information
    writeUserInfo(filePath,users, numUserPairs, masterPassword);

}


//ask and fill the new user struct
void fillUserInfo(userInfo *user) {
    char username[100];
    char password[100];
    fflush(stdin);
    fflush(stdout);
    fprintf(stdout, "\nIntroduce the data of the new Account");


    //Read Username
    printf("\nUsername: ");
    scanf("%s", username);

    //Read Password
    printf("\nPassword: ");
    scanf("%s", password);

    //Allocate memory and copy values

    user->username_length = (int)strlen(username);
    user->password_length = (int) strlen(password);

    user->username = malloc(user->username_length - 1);
    user->password = malloc(user->password_length - 1);

    if (user->username == NULL || user->password == NULL) {
        fprintf(stderr, "ERROR: It cannot be written the data of the new user\n");
        exit(1);
    }

    strcpy(user->username, username);
    strcpy(user->password, password);

}

//Frees the memory that has been allocated throughout the program
void freeUserInfo(userInfo* user){
    /*
    free(user->username);
    free(user->password);
    free(user);
    */
    return;
}


void freeAllUserInfo(userInfo* user, int numUserPairs){
    //new allocated memory for reading
    /*
    for (int i = 0; i < numUserPairs; ++i) {
          freeUserInfo(&user[i]);
    }
    free(user);
     */
    return;
}

