//
// Created by serra on 1/4/2024.
//

#include "usersInfo.h"
#include "files.h"

//reserva la memoria de la estructura user (userInfo)
userInfo* createUserInfo(int numInitialAllocation){
    return (userInfo *)malloc(numInitialAllocation * sizeof (userInfo ));
}

//elimina UN user y ocupa el espacio en caso de quedar libre con el resto de los elmentos del array.
//indexTodelete es el indice del array de users
void deleteUserInfo(userInfo* users, int* numUserPairs, int indexToDelete,char* filePath,const char *masterPassword) {
    if(indexToDelete < 0 || indexToDelete > *numUserPairs){
        fprintf(stderr, "Índice de usuario a eliminar fuera de rango\n");
        exit(1);
    }

    // Reorganizar el arreglo para llenar el espacio vacío
    for (int i = indexToDelete; i < *numUserPairs - 1; i++) {
        memcpy(&users[i],&users[i+1],sizeof(userInfo ));
    }
    //reducimos el numero de usuarios
    *numUserPairs = *numUserPairs -1;

    //grabamos la nueva infomracion
    writeUserInfo(filePath,users, numUserPairs, masterPassword);

}


//solcita y rellena la nueva estrutura user
void fillUserInfo(userInfo *user) {
    char username[100];
    char password[100];
    fflush(stdin);
    fflush(stdout);
    fprintf(stdout, "Introduzca los datos de la nueva cuenta");


    //Read Username
    printf("Nombre de usuario: ");
    scanf("%s", username);

    //Read Password
    printf("Password: ");
    scanf("%s", password);

    //Allocate memory and copy values

    user->username_length = (int)strlen(username);
    user->password_length = (int) strlen(password);

    user->username = malloc(user->username_length - 1);
    user->password = malloc(user->password_length - 1);

    if (user->username == NULL || user->password == NULL) {
        fprintf(stderr, "No se pudieron rellenar los datos del nuevo usuario\n");
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

