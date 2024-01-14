//
// Created by serra on 1/4/2024.
//

#include "files.h"



int writeUserInfo(char* path, const userInfo* users, int* numUserPairs, const char *encryptionKey) {


    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", path);
        return 0;  // Return 0 to indicate failure
    }

    //Generar mempria pàra una cadena a cifrar con todos los datos
    char* cadenaCifrado = (char*) malloc(sizeof(int)+sizeof(char)+ *numUserPairs * sizeof (userInfo)*(4*sizeof(char)));
    setbuf(stdout, 0);
    printf("\nCadenaCifrado readUserInfo%d", strlen(cadenaCifrado));
    printf("\nCadenaCifrado readUserInfo%d", strlen(cadenaCifrado));

    char* outputCifrado = (char*) malloc(sizeof(int)+sizeof(char)+ *numUserPairs * sizeof (userInfo)*(4*sizeof(char)));
    printf("\nOutputCifrado readUserInfo%d", strlen(outputCifrado));

    //generar cadena a cifrar
    const char * numUsers = (char *) numUserPairs;
    char cadena[100];
    char breakPoint = '|';
    char cadenanumUserPairs[10];
    sprintf(cadenanumUserPairs,"%d",*numUserPairs);
    sprintf(cadena,"%c",breakPoint);
    strcat(cadenanumUserPairs, cadena);


    sprintf(cadena,"%d",*numUserPairs);
    strcpy(cadenaCifrado, cadena);
    //add | character
    sprintf(cadena,"%c",breakPoint);
    strcat(cadenaCifrado, cadena);



    for (int i = 0; i < *numUserPairs; ++i) {
        sprintf(cadena,"%d",users[i].username_length);
        // Write username and password lengths
        //fwrite(&(users[i].username_length), sizeof(int), 1, file);
       // char userNameLen = (char ) users[i].username_length;
        strcat(cadenaCifrado,cadena );
        //add | character

        sprintf(cadena,"%c",breakPoint);
        strcat(cadenaCifrado, cadena);
        //fwrite(&(users[i].password_length), sizeof(int), 1, file);
        sprintf(cadena,"%d",users[i].password_length);
        strcat(cadenaCifrado,cadena);
        //add | character
        sprintf(cadena,"%c",breakPoint);
        strcat(cadenaCifrado, cadena);
        // Write username and password
        //fwrite(users[i].username, sizeof(char), users[i].username_length, file);
        strcat(cadenaCifrado,users[i].username);
        //add | character
        sprintf(cadena,"%c",breakPoint);
        strcat(cadenaCifrado, cadena);
        //fwrite(users[i].password, sizeof(char), users[i].password_length, file);
        strcat(cadenaCifrado,users[i].password);
        //add | character
        sprintf(cadena,"%c",breakPoint);
        strcat(cadenaCifrado, cadena);
    }
    setbuf(stdout,0);




    printf("%s",cadenaCifrado);
    printf("%llu",strlen(cadenaCifrado));

    // Perform your encryption logic here before writing to the file
    XORCifrado(cadenaCifrado,  encryptionKey,  (int)strlen(cadenaCifrado),  (int)strlen(encryptionKey),outputCifrado);
    setbuf(stdout,0);
    printf("%s",outputCifrado);
    printf("%llu",strlen(outputCifrado));
    //write content
    size_t bytesWritten;

    bytesWritten = fwrite(cadenanumUserPairs, sizeof(char), strlen(cadenanumUserPairs), file);
    bytesWritten = bytesWritten + fwrite(outputCifrado, sizeof(char), strlen(outputCifrado), file);
    setbuf(stdout,0);
    printf("%zu",bytesWritten);




           fclose(file);
    return 1;  // Return 1 to indicate success
}

userInfo* readUserInfo(char* path, int* numUserPairs, const char *encryptionKey) {

    //abrimos el fichero para leeer los usuarios
    FILE *file = fopen(path, "rb");
    setbuf(stdout,0);
    printf("%s", path);

    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", path);

        *numUserPairs = 0;  // Set numUserPairs to 0 to indicate zero accounts
        return NULL;
    }

    char buffer[1024];
    // Reading until the end of the file using fread
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {

        // Process the data in the buffer (example: print to stdout)
        fwrite(buffer, 1, bytesRead, stdout);
    }
    //hemos leido el fichero asqi ue cerramos el handle
    fclose(file);

    // Initialize variables to store values read from outputCifrado
    int readNumUserPairs, readUsernameLength, readPasswordLength;
    char  readUsername[1000], readPassword[1000];

    /*// Parse the decrypted data and extract values
sscanf(outputCifrado, "%d|%d|%d|%[^|]|%[^|]|", &readNumUserPairs, &readUsernameLength, &readPasswordLength, readUsername, readPassword);
*/
    sscanf(buffer, "%d|", &readNumUserPairs);
    // Set numUserPairs to the parsed value
    *numUserPairs = readNumUserPairs;

    setbuf(stdout,0);
    fprintf(stdout,"\n ReadUserInfo:\n sizeof userInfo: %llu \n numUserPairs:%d"
                ,sizeof (userInfo),*numUserPairs);



//Generar mempria pàra una cadena a cifrar con todos los datos
    char* cadenaCifrado = (char*) malloc(sizeof(int)+sizeof(char)+ *numUserPairs * sizeof (userInfo)*(4*sizeof(char)));
    setbuf(stdout, 0);
    printf("\nCadenaCifrado readUserInfo%d", strlen(cadenaCifrado));
    char *result = buffer+2;
    strcpy(cadenaCifrado, result);
    //sscanf(buffer, "%s", cadenaCifrado);
    printf("\nCadenaCifrado longitud readUserInfo%d", strlen(cadenaCifrado));
    printf("\nCadenaCifrado contenido en readUserInfo%s", cadenaCifrado);



    char* outputCifrado = (char*) malloc(sizeof(int)+sizeof(char)+ *numUserPairs * sizeof (userInfo)*(4*sizeof(char)));
    printf("\nOutputCifrado readUserInfo%d", strlen(outputCifrado));

    // Perform your decryption logic here before reading from the file
    XORCifrado(cadenaCifrado,  encryptionKey,  strlen(cadenaCifrado),  strlen(encryptionKey),outputCifrado);


    //Lectura del archivo //Hay que cambiarlo para que lea hasta la / y poder separar los tres primeros numeros

    setbuf(stdout,0);
    printf("%s\n", outputCifrado);

    /*// Read the number of user pairs from the file and initialize variable of number of accounts
    int ch = 0;
    int j =0;

    // Find the number of user pairs by parsing the decrypted data until the '|' character
    char *ptr = outputCifrado;
    *numUserPairs = atoi(ptr);  // Get the number before the first '|'
    while (*ptr != '|' && *ptr != '\0') {
        ++ptr;
    }

    *username_length = atoi(ptr);  // Get the number before the first '|'
    while (*ptr != '|' && *ptr != '\0') {
        ++ptr;
    }*/



    // Allocate memory for user information structures
    //I have an error here allocating the memory for users
    userInfo* users = malloc((*numUserPairs) * sizeof(userInfo));
    if (users == NULL) {
        setbuf(stdout, 0);
        fprintf(stderr, "Memory allocation failed.\n");
       return 0;
        // Handle the error, possibly by terminating the program or returning an error code.
    }


    int c=0;
    // Set username_length and password_length for each user
    for (int i = 0; i < *numUserPairs; i++) { //this should be i =0

        fflush(stdin);
        fflush(stdout);
        char barra[100];
        int a = 5;
        int b= i+1;

        // Initialize the string
        barra[0] = '\0';

            // Concatenate '|' to the string numUserPairs times
        if (b > 1) {
            if (b==2){
                for (int z = 0; z < ((b - 1) * a); ++z) {
                    strcat(barra, "|");
                }
            }
//cambiar esto a un switch para cada valor de b que es ams rapido y facil
            else{
                for (int z = 0; z < ((b - 1) * a)-c; ++z) {
                    strcat(barra, "|");
                }

            }


            c=c+1;
            // Define the variable for the number of characters to skip
            int numCharsToSkip = strlen(barra);

            // Find the starting position after skipping the required number of '|' characters
            int currentPosition = 0;
            while (numCharsToSkip > 0 && outputCifrado[currentPosition] != '\0') {
                if (outputCifrado[currentPosition] == '|') {
                    --numCharsToSkip;
                }
                ++currentPosition;
            }



            // Read the values after skipping the required number of '|' characters
            sscanf(outputCifrado + currentPosition, "%d|%d|%[^|]|%[^|]|", &readUsernameLength, &readPasswordLength, readUsername, readPassword);

        } else{
            sscanf(outputCifrado, "%d|%d|%d|%[^|]|%[^|]|", &readNumUserPairs, &readUsernameLength, &readPasswordLength, readUsername, readPassword);
        }




        // Allocate memory for username and password
        users[i].username = malloc((readUsernameLength - 1) * sizeof(char));
        users[i].password = malloc((readPasswordLength - 1) * sizeof(char));

        // Copy username and password
        strcpy(users[i].username, readUsername);
        strcpy(users[i].password, readPassword);

        users[i].username_length = readUsernameLength;
        users[i].password_length = readPasswordLength;
    }





   /* fread(numUserPairs, sizeof(int), 1, file);*/
    setbuf(stdout,0);
    printf("%d\n",*numUserPairs);
    if(*numUserPairs == 0)
    {
        fprintf(stderr,"No hay usuarios en tu archivo.");
        return NULL;
    }


    // Allocate memory for user information structures
    /*userInfo* users = malloc((*numUserPairs) * sizeof(userInfo));*/
    setbuf(stdout,0);
    printf("sizeof(userInfo:%d\n",sizeof(userInfo));

   /* // Read each user info structure from the file
    for (int i = 0; i < *numUserPairs; i++) {
        // Read username and password lengths
        fread(&(users[i].username_length), sizeof(int), 1, file);
        fread(&(users[i].password_length), sizeof(int), 1, file);

        // Allocate memory for username and password
        users[i].username = malloc((users[i].username_length + 1) * sizeof(char));
        users[i].password = malloc((users[i].password_length + 1) * sizeof(char));

        // Read username and password
        fread(users[i].username, sizeof(char), users[i].username_length, file);
        fread(users[i].password, sizeof(char), users[i].password_length, file);

        // Null-terminate the strings
        users[i].username[users[i].username_length] = '\0';
        users[i].password[users[i].password_length] = '\0';
    }*/
    // Read each user info structure from the file
    /*for (int i = 0; i < *numUserPairs; i++) {
        /// Read username and password lengths
        fread(&(users[i].username_length), sizeof(int), 1, file);
        fread(&(users[i].password_length), sizeof(int), 1, file);

        // Allocate memory for username and password
        users[i].username = malloc((users[i].username_length + 1) * sizeof(char));
        users[i].password = malloc((users[i].password_length + 1) * sizeof(char));

        // Read username and password
        fread(users[i].username, sizeof(char), users[i].username_length, file);
        fread(users[i].password, sizeof(char), users[i].password_length, file);*//*
        // Set username and password lengths
        users[i].username_length = readUsernameLength;
        users[i].password_length = readPasswordLength;

        // Allocate memory for username and password
        users[i].username = malloc((users[i].username_length + 1) * sizeof(char));
        users[i].password = malloc((users[i].password_length + 1) * sizeof(char));

        // Copy username and password from readUsername and readPassword arrays
        strcpy(users[i].username, readUsername);
        strcpy(users[i].password, readPassword);

        // Null-terminate the strings
        users[i].username[users[i].username_length] = '\0';
        users[i].password[users[i].password_length] = '\0';

    }*/

    fclose(file);
    return users;
}


void XORCifrado(char* data, char* key, int dataLen, int keyLen,char* outputCifrado) {
    setbuf(stdout, 0);
    int i;

    key[strlen(key)-1] = '\0';

    for (i = 0; i < dataLen; i++) {
        printf("\n%c", data[i]);
        char temp = data[i] ^ key[i % keyLen];
        if(temp=='\0'){
            printf("HAHHAAAHAHAHAHAHAHHAHAHAHAH");
            outputCifrado[i] = data[i];

        }
        else
        {
        outputCifrado[i] = temp;
        }

        printf("\n%d\n%llu", i, strlen(outputCifrado));

    }

    outputCifrado[i]='\0';
    printf("\n%llu", strlen(outputCifrado));

}

//descifrado? // Descifrado
//    char cadenaDescifrada[100]; // Ajusta el tamaño según tus necesidades
//    XORCifrado(cadenaCifrada, clave, longitudCadena, longitudClave, cadenaDescifrada)

unsigned char checksum (unsigned char *ptr, size_t sz) {
    unsigned char chk = 0;
    while (sz-- != 0)
        chk -= *ptr++;
    return chk;
}