#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

#include "files.h"
#include "usersInfo.h"

/*
     ██████╗ ██████╗ ███████╗███╗   ██╗████████╗ █████╗ ███╗   ██╗████████╗███████╗
    ██╔════╝██╔═══██╗██╔════╝████╗  ██║╚══██╔══╝██╔══██╗████╗  ██║╚══██╔══╝██╔════╝
    ██║     ██║   ██║███████╗██╔██╗ ██║   ██║   ███████║██╔██╗ ██║   ██║   ███████╗
    ██║     ██║   ██║╚════██║██║╚██╗██║   ██║   ██╔══██║██║╚██╗██║   ██║   ╚════██║
    ╚██████╗╚██████╔╝███████║██║ ╚████║   ██║   ██║  ██║██║ ╚████║   ██║   ███████║
     ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
*/


//COSAS HA HACER
//1. SEPARAR CADA NUMERO GUARDADO PARA PODER SEPARAR CADA CADENA EN SU STRUCT.NAME CORRESPONDIENTE
//2. \N NECESARIOS POR TODOS SITIOS
//3. COMPROBACION DE CONTRASEÑA CARACTERES MINIMOS
//4. COMPROBACION UNICA DE 3 OPORTUNIDADES SI NO TE ECHA
//5. ERROR AL FREEMEMORY

#define version 1.0
#define copyright "Copyright @ Alejandro Serrano Calvo 2023"
#define MAX 100
#define MAX_USERNAME_SIZE 100
#define MAX_PASSWORD_SIZE 100

#define program_name "Encrypted Account Manager"
void menuIntro(char* masterUserName, char* masterPassword);
void setupFilePath(char* filePath,char* masterUserName);
void welcomeNewUser();
void menuMain();






int main(){

    char masterUserName[MAX_USERNAME_SIZE];
    char masterPassword[MAX_PASSWORD_SIZE];
    char filePath[MAX_USERNAME_SIZE + 10]; //+2 FOR THE ./ AND +4 FOR THE.BIN
    userInfo *readUsers = NULL;
    //numero de cuentas de un usuario
    int numUserPairs =0;

    //presento el menu Login
    menuIntro(masterUserName,masterPassword);
    //contruyo la variable nombre archivo
    setupFilePath(filePath,masterUserName);

    //leo los usuarios
    readUsers = readUserInfo(filePath, &numUserPairs, masterPassword);

    if(readUsers == NULL)
    {
        //no puedo leer el archivo, solo cointemnplamos nuevo usuario
        char masterPasswordCheckAccount[MAX_PASSWORD_SIZE];
        welcomeNewUser();
        fprintf(stdout, "Escriba de nuevo su contraseña: ");
        fflush(stdin);
        fflush(stdout);
        fgets(masterPasswordCheckAccount, MAX_PASSWORD_SIZE, stdin);

        if (strcmp(masterPassword,masterPasswordCheckAccount) == 0) {
            fprintf(stdout, "Perfecto su contraseña maestra ha sido verificada.\n");
        }else{
            do {
                fprintf(stdout, "No coinciden las contraseñas.");
                fprintf(stdout, "Introduzca una nueva contraseña:");
                fflush(stdin);
                fflush(stdout);
                fgets(masterPassword, MAX_PASSWORD_SIZE, stdin);
                fprintf(stdout, "Escriba de nuevo la password");
                fflush(stdin);
                fflush(stdout);
                fgets(masterPasswordCheckAccount, MAX_PASSWORD_SIZE, stdin);
            } while (strcmp(masterPassword, masterPasswordCheckAccount) != 0);
        }

    }
    else
    {
        //tengo que comprobar el checksum que me dice sila cobntraseña es buena
    }



    fprintf(stdout, "Bienvenido %s", masterUserName);
    int selectedOption = 0;
    int allocatedUserPairs = numUserPairs;
    do {
        menuMain();
        fscanf(stdin, "%d", &selectedOption);

        if (selectedOption >=1 && selectedOption<=4) {
            if (selectedOption==1){
                if(readUsers == NULL) {
                    readUsers = readUserInfo(filePath, &numUserPairs, masterPassword);
                }
                if(numUserPairs >0 ){
                    //print the read data
                    for (int i = 0; i < numUserPairs; ++i){

                        fprintf(stdout, "Cuenta numero %d:", i + 1);

                            fprintf(stdout, "Usuario: %s\n", readUsers[i].username); //the error is here on readUsers[i]
                        //printf("%s", readUsers[i].username);


                        fprintf(stdout, "Password: %s", readUsers[i].password);
                        fprintf(stdout, "\n");
                    }
                } else{
                    fprintf(stdout, "Aun no tienes cuentas guardadas.\n");
                }
            }

            else if (selectedOption == 2) {
                if(allocatedUserPairs == numUserPairs){
                    if(numUserPairs>0){
                        readUsers= realloc(readUsers, 2* numUserPairs * sizeof(userInfo ));
                        if(readUsers == NULL){
                            fprintf(stderr, "No se pueden agregar mas cuentas, contacte con el desarrollador. ");
                            return 1;
                        }
                    } else{
                        allocatedUserPairs=5;
                        readUsers = createUserInfo(allocatedUserPairs);
                        numUserPairs = 0;
                        if(readUsers==NULL){
                            fprintf(stdout, "No se puede agregar mas cuentas, contacte con el desarrolaldor");
                            return 1;
                        }
                    }

                }

                fillUserInfo(&readUsers[numUserPairs]);
                numUserPairs++;
            }
            else if (selectedOption==3){
                int selectedIndex = -1;
                do {
                    fprintf(stdout, "Que cuenta desea borrar? (1 - %d):", numUserPairs);
                    fflush(stdin);
                    fflush(stdout);
                    fscanf(stdin, "%d", &selectedIndex);
                    fflush(stdin);
                    fflush(stdout);
                } while (selectedIndex<1 || selectedIndex > numUserPairs);

                deleteUser(readUsers, &numUserPairs, selectedIndex-1,filePath,masterPassword);
            }
            else if (selectedOption == 4){
                //call teh write function
                writeUserInfo(filePath, readUsers, &numUserPairs, masterPassword);
            }
        } else{
            fprintf(stdout, "opcion desconocida");
        }
    } while (selectedOption !=4);

    //Llama a la funcion que esta dando problemas
    freeAllUserInfo(readUsers,  numUserPairs);
   // freeUserInfo(readUsers,numUserPairs);

    return 0;

}


void menuIntro(char* masterUserName, char* masterPassword)
{
    time_t t= time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(stdout, "============================================================\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "||             %s                 ||\n", program_name);
    fprintf(stdout, "||                    Welcome!!!                          ||\n");
    fprintf(stdout, "||     V%.1f | %s", version, copyright "    ||\n");
    fprintf(stdout, "||               Date: %d-%02d-%02d %02d:%02d:%02d                ||\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(stdout, "\n");
    fprintf(stdout, "============================================================\n");


    fprintf(stdout, "Por favor introduzca su nombre de usuario: ");
    fflush(stdin);
    fflush(stdout);
    fgets(masterUserName, MAX_USERNAME_SIZE, stdin);
    int len=masterUserName[strlen(masterUserName)-1] + '\0';
    fflush(stdin);
    fflush(stdout);


    fprintf(stdout, "Por favor introduzca su contraseña maestra: ");
    fflush(stdin);
    fflush(stdout);
    fgets(masterPassword, MAX_PASSWORD_SIZE, stdin);
    fflush(stdin);
    fflush(stdout);


}
void menuMain()
{
    fprintf(stdout, "Que desea hacer?\n");
    fprintf(stdout, "1) Ver cuentas guardadas\n");
    fprintf(stdout, "2) Agregar una nueva cuenta\n");
    fprintf(stdout, "3) Eliminar una cuenta\n");
    fprintf(stdout, "4) Guardar y salir\n");
    fprintf(stdout,"\n");
    fprintf(stdout, "Seleccione una opcion:");
    fflush(stdin);
    fflush(stdout);
}

void setupFilePath(char* filePath,char* masterUserName){

  //  char filePath[MAX_USERNAME_SIZE + 10]; //+2 FOR THE ./ AND +4 FOR THE.BIN
    int filePathIndex = 6;
    filePath[0] = 'u';
    filePath[1] = 's';
    filePath[2] = 'e';
    filePath[3] = 'r';
    filePath[4] = 's';
    filePath[5] = '/';
    while (filePathIndex< strlen(masterUserName)+6){
        filePath[filePathIndex] = masterUserName[filePathIndex -6];
        filePathIndex++;
    }

    filePath[filePathIndex -1] = '.';
    filePath[filePathIndex + 0] = 'b';
    filePath[filePathIndex + 1] = 'i';
    filePath[filePathIndex + 2] = 'n';
    filePath[filePathIndex + 3] = '\0';


    fprintf(stdout, "%s", filePath);
}

void welcomeNewUser()
{
    fprintf(stdout, "\n");
    fprintf(stdout, "************************************************************\n");
    fprintf(stdout, "* Welcome! As a new user, let us guide you through the usage *\n");
    fprintf(stdout, "* of the program:                                            *\n");
    fprintf(stdout, "*                                                            *\n");
    fprintf(stdout, "* This program stores user accounts encrypted with the       *\n");
    fprintf(stdout, "* password you have provided.                                *\n");
    fprintf(stdout, "*                                                            *\n");
    fprintf(stdout, "* Once you have completed the initial creation of your       *\n");
    fprintf(stdout, "* profile, you will be prompted to first enter the username  *\n");
    fprintf(stdout, "* or email of the account to be stored, and then the         *\n");
    fprintf(stdout, "* password. Once you have finished adding accounts, the      *\n");
    fprintf(stdout, "* manager will encrypt and save your information.            *\n");
    fprintf(stdout, "*                                                            *\n");
    fprintf(stdout, "* As you are creating a new profile, we will ensure that     *\n");
    fprintf(stdout, "* the entered master password is correct.                    *\n");
    fprintf(stdout, "************************************************************\n");
    fflush(stdin);
    fflush(stdout);
}