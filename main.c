//
// Created by serra on 1/4/2024.
//
/*

██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗██╗██╗
██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝██║██║
██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ██║██║
██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ╚═╝╚═╝
╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗██╗██╗
 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝╚═╝╚═╝
*/
/*
    ██╗     ██╗██████╗ ██████╗  █████╗ ██████╗ ██╗███████╗███████╗
    ██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗██║██╔════╝██╔════╝
    ██║     ██║██████╔╝██████╔╝███████║██████╔╝██║█████╗  ███████╗
    ██║     ██║██╔══██╗██╔══██╗██╔══██║██╔══██╗██║██╔══╝  ╚════██║
    ███████╗██║██████╔╝██║  ██║██║  ██║██║  ██║██║███████╗███████║
    ╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝
*/
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"
#include "files.h"
#include "usersInfo.h"
//Start of if def

#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep((x) / 1000)
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

//End of endif

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
#define MAX_CHAR_SIZES 100
#define MAX_USER_ACCOUNTS 5
#define MAX_USERNAME_SIZE MAX_CHAR_SIZES
#define MAX_PASSWORD_SIZE MAX_CHAR_SIZES

#define program_name "Encrypted Account Manager Coquette"
/*
    ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
    ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
    █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
    ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/
/*
    ██╗      ██████╗  ██████╗     ██╗███╗   ██╗  ║║   ███████╗██╗ ██████╗ ███╗   ██╗    ██╗   ██╗██████╗
    ██║     ██╔═══██╗██╔════╝     ██║████╗  ██║  ║║   ██╔════╝██║██╔════╝ ████╗  ██║    ██║   ██║██╔══██╗
    ██║     ██║   ██║██║  ███╗    ██║██╔██╗ ██║  ║║   ███████╗██║██║  ███╗██╔██╗ ██║    ██║   ██║██████╔╝
    ██║     ██║   ██║██║   ██║    ██║██║╚██╗██║  ║║   ╚════██║██║██║   ██║██║╚██╗██║    ██║   ██║██╔═══╝
    ███████╗╚██████╔╝╚██████╔╝    ██║██║ ╚████║  ║║   ███████║██║╚██████╔╝██║ ╚████║    ╚██████╔╝██║
    ╚══════╝ ╚═════╝  ╚═════╝     ╚═╝╚═╝  ╚═══╝  ║║   ╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝     ╚═════╝ ╚═╝
*/
void menuLogin(char* masterUserName, char* masterPassword);
/*
    ███████╗███████╗████████╗████████╗██╗███╗   ██╗ ██████╗     ██╗   ██╗██████╗
    ██╔════╝██╔════╝╚══██╔══╝╚══██╔══╝██║████╗  ██║██╔════╝     ██║   ██║██╔══██╗
    ███████╗█████╗     ██║      ██║   ██║██╔██╗ ██║██║  ███╗    ██║   ██║██████╔╝
    ╚════██║██╔══╝     ██║      ██║   ██║██║╚██╗██║██║   ██║    ██║   ██║██╔═══╝
    ███████║███████╗   ██║      ██║   ██║██║ ╚████║╚██████╔╝    ╚██████╔╝██║
    ╚══════╝╚══════╝   ╚═╝      ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝      ╚═════╝ ╚═╝
*/
void setupFilePath(char* filePath,char* masterUserName);
/*
    ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗ ██████╗
    ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██║████╗  ██║██╔════╝
    ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║██║██╔██╗ ██║██║  ███╗
    ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██║██║╚██╗██║██║   ██║
    ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║██║██║ ╚████║╚██████╔╝
     ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
*/
void welcomeNewUser();

/*
    ██████╗ ██████╗ ██╗██████╗  ██████╗ ███████╗
    ██╔══██╗██╔══██╗██║██╔══██╗██╔════╝ ██╔════╝
    ██████╔╝██████╔╝██║██║  ██║██║  ███╗█████╗
    ██╔══██╗██╔══██╗██║██║  ██║██║   ██║██╔══╝
    ██████╔╝██║  ██║██║██████╔╝╚██████╔╝███████╗
    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═════╝  ╚═════╝ ╚══════╝
 */
void menuMain();
/*
     ██████╗██╗  ██╗███████╗ ██████╗██╗  ██╗██╗███╗   ██╗ ██████╗     ██████╗  █████╗ ███████╗███████╗██╗    ██╗ ██████╗ ██████╗ ██████╗
    ██╔════╝██║  ██║██╔════╝██╔════╝██║ ██╔╝██║████╗  ██║██╔════╝     ██╔══██╗██╔══██╗██╔════╝██╔════╝██║    ██║██╔═══██╗██╔══██╗██╔══██╗
    ██║     ███████║█████╗  ██║     █████╔╝ ██║██╔██╗ ██║██║  ███╗    ██████╔╝███████║███████╗███████╗██║ █╗ ██║██║   ██║██████╔╝██║  ██║
    ██║     ██╔══██║██╔══╝  ██║     ██╔═██╗ ██║██║╚██╗██║██║   ██║    ██╔═══╝ ██╔══██║╚════██║╚════██║██║███╗██║██║   ██║██╔══██╗██║  ██║
    ╚██████╗██║  ██║███████╗╚██████╗██║  ██╗██║██║ ╚████║╚██████╔╝    ██║     ██║  ██║███████║███████║╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝
     ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝ ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝
*/
void askPassword(char* masterPassword);
/*
    ██╗      ██████╗  █████╗ ██████╗ ██╗███╗   ██╗ ██████╗     ██████╗  █████╗ ██████╗
    ██║     ██╔═══██╗██╔══██╗██╔══██╗██║████╗  ██║██╔════╝     ██╔══██╗██╔══██╗██╔══██╗
    ██║     ██║   ██║███████║██║  ██║██║██╔██╗ ██║██║  ███╗    ██████╔╝███████║██████╔╝
    ██║     ██║   ██║██╔══██║██║  ██║██║██║╚██╗██║██║   ██║    ██╔══██╗██╔══██║██╔══██╗
    ███████╗╚██████╔╝██║  ██║██████╔╝██║██║ ╚████║╚██████╔╝    ██████╔╝██║  ██║██║  ██║
    ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝
*/

void loadingBar(int total, int current) {
    fflush(stdout);
    int progress = (int)((double)current / total * 100);
    int numHashes = progress / 2;

    printf("\r[");
    for (int i = 0; i < numHashes; i++) {
        printf("#");
    }
    for (int i = numHashes; i < 50; i++) {
        printf(" ");
    }
    printf("] %d%%", progress);
    printf("\n");


    // Add a newline character to ensure a clean line break
    if (current == total) {
        printf("\n");
    }
}
/*
    ███╗   ███╗ █████╗ ██╗███╗   ██╗
    ████╗ ████║██╔══██╗██║████╗  ██║
    ██╔████╔██║███████║██║██╔██╗ ██║
    ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
    ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
*/
int main(){
/*
    ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███████╗
    ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
    ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ███████╗
    ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ╚════██║
     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗███████║
      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚══════╝
*/
    char masterUserName[MAX_USERNAME_SIZE];
    char masterPassword[MAX_PASSWORD_SIZE];
    char filePath[MAX_USERNAME_SIZE + 10]; //+6 for users/ AND +4 FOR THE.BIN
    
    
    userInfo *readUsers = NULL; //Initialize the struct to NULL
    //number of accounts of the user initialize to 0
    int numUserPairs =0;
    //for checksum and authentication
    int authentication = -1;


    //Read the users
    do{
        /*
    ██╗      ██████╗  ██████╗     ██╗███╗   ██╗  ║║   ███████╗██╗ ██████╗ ███╗   ██╗    ██╗   ██╗██████╗
    ██║     ██╔═══██╗██╔════╝     ██║████╗  ██║  ║║   ██╔════╝██║██╔════╝ ████╗  ██║    ██║   ██║██╔══██╗
    ██║     ██║   ██║██║  ███╗    ██║██╔██╗ ██║  ║║   ███████╗██║██║  ███╗██╔██╗ ██║    ██║   ██║██████╔╝
    ██║     ██║   ██║██║   ██║    ██║██║╚██╗██║  ║║   ╚════██║██║██║   ██║██║╚██╗██║    ██║   ██║██╔═══╝
    ███████╗╚██████╔╝╚██████╔╝    ██║██║ ╚████║  ║║   ███████║██║╚██████╔╝██║ ╚████║    ╚██████╔╝██║
    ╚══════╝ ╚═════╝  ╚═════╝     ╚═╝╚═╝  ╚═══╝  ║║   ╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝     ╚═════╝ ╚═╝
*/
        menuLogin(masterUserName,masterPassword);
        //setup File Path for the users Info
        setupFilePath(filePath,masterUserName);
        readUsers = readUserInfo(filePath, &numUserPairs, masterPassword, &authentication); //read the path/file

        //readUsers = NULL if the file doesn't exist or the password is incorrect
        //authentication = -1 if the password had never check
        //authentication = 0 if password have been checked, and it's good, or it's a new user
        //authentication = i, where i is the number of trys
        if(readUsers == NULL && authentication == 0)
        {
            //New User ask again for the password
            askPassword(masterPassword);
        }
        else if(readUsers == NULL && authentication > 2)
        {
            fprintf(stdout, "\nYou don't have any more trys, GoodBye %s", masterUserName);
            return 0;
            //End the program if the user trys 3 times
        }
        if(authentication<3 && authentication>0)
        {
            fprintf(stdout, "\nUsername or Password not valid\n"); //If it's not valid the password
        }

    }while(authentication!=0); //Until authentication, it's not 0
/*
██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗██╗██╗
██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝██║██║
██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ██║██║
██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ╚═╝╚═╝
╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗██╗██╗
 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝╚═╝╚═╝
*/
    //Loading Bar

    int total = 100;
    for (int i = 0; i <= total; i++) {
        if (i==0){
            printf("\tNos representa");
        }
        loadingBar(total, i);


        usleep(50000);  // Sleep for 100,000 microseconds (0.1 seconds)

    }
    printf("\nLoading complete!\n");

    //End of loading Bar
    fprintf(stdout, "Welcome %s", masterUserName); //Say Hi
    int selectedOption = 0;
    int allocatedUserPairs = numUserPairs; //Accounts in the file
    do {
        menuMain();
        fscanf(stdin, "%d" ,&selectedOption);
/*
                 ██████╗ ██████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗
                ██╔═══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
                ██║   ██║██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║███████╗
                ██║   ██║██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║╚════██║
                ╚██████╔╝██║        ██║   ██║╚██████╔╝██║ ╚████║███████║
                 ╚═════╝ ╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
                 */
        if (selectedOption >=1 && selectedOption<=4) {

            /*
          ██╗
         ███║
         ╚██║
          ██║
          ██║
          ╚═╝
            */
            if (selectedOption==1){
                if(readUsers == NULL) {
                    readUsers = readUserInfo(filePath, &numUserPairs, masterPassword,&authentication); //read and allocated memory of the user accounts
                }
                if(numUserPairs >0 ){
                    //Print the read data
                    for (int i = 0; i < numUserPairs; ++i){

                        fprintf(stdout, "Account Number %d:", i + 1);

                            fprintf(stdout, "Username: %s\n", readUsers[i].username);
                        //printf("%s", readUsers[i].username);


                        fprintf(stdout, "Password: %s", readUsers[i].password);
                        fprintf(stdout, "\n");
                    }
                } else{
                    fprintf(stdout, "You don't have any accounts yet.\n"); //If it doesn't have accounts yet
                }
            }
                /*
                    ██████╗
                    ╚════██╗
                     █████╔╝
                    ██╔═══╝
                    ███████╗
                    ╚══════╝
                */
            else if (selectedOption == 2)
            {
                if(numUserPairs >= MAX_USER_ACCOUNTS) { //Max accounts in this case 5
                    fprintf(stdout, "\nMax numbers of accounts reach, pls pay 50 euros to the developer to add more accounts. ");
                }else if(allocatedUserPairs <= 0) {
                    //Initialize users arrays
                    readUsers = createUserInfo(MAX_USER_ACCOUNTS);
                    if(readUsers==NULL){ //Problem this should be happening, so it would exit with -2 error code
                        fprintf(stderr, "\nThere's been a problem with your data, pls contact a developer.");
                        return -2;
                    }

                }
                fillUserInfo(&readUsers[numUserPairs]); //fill the data of the new account
                numUserPairs++; //+1 to the number of accounts that he has
                allocatedUserPairs = numUserPairs; // equals both variable for supporting
            }
            /*
            ██████╗
            ╚════██╗
             █████╔╝
             ╚═══██╗
            ██████╔╝
            ╚═════╝
            */
            else if (selectedOption==3){
                int selectedIndex = -1; //Index of the account you want to remove
                do {
                    fprintf(stdout, "\nWhat account do you want to delete? (1 - %d):\n", numUserPairs);
                    fflush(stdin);
                    fflush(stdout);
                    fscanf(stdin, "%d", &selectedIndex); //ask the account
                    fflush(stdin);
                    fflush(stdout);
                } while (selectedIndex<1 || selectedIndex > numUserPairs); //check if it's a possible value

                deleteUserInfo(readUsers, &numUserPairs, selectedIndex-1,filePath,masterPassword); //ask for the function for delete the struct
                allocatedUserPairs--; //one less to allocated userPairs which is also numUserPairs
            }
                /*
                    ██╗  ██╗
                    ██║  ██║
                    ███████║
                    ╚════██║
                         ██║
                         ╚═╝
                         */
            else if (selectedOption == 4){
                //call teh write function
                writeUserInfo(filePath, readUsers, &numUserPairs, masterPassword); //write all the information in the file with encryption
            }
        }
        //ERROR NO OPTION AVAILABLE
        else        {
            fprintf(stdout, "\nUnknown Option");
        }
    } while (selectedOption !=4);


    //Llama a la funcion que esta dando problemas
    //freeAllUserInfo(readUsers,  numUserPairs);
   // freeUserInfo(readUsers,numUserPairs);

    return 0;

}


/*
    ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
    ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
    █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
    ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/
void menuLogin(char* masterUserName, char* masterPassword)
{

    /*
 ████████╗██╗███╗   ███╗███████╗
 ╚══██╔══╝██║████╗ ████║██╔════╝
    ██║   ██║██╔████╔██║█████╗
    ██║   ██║██║╚██╔╝██║██╔══╝
    ██║   ██║██║ ╚═╝ ██║███████╗
    ╚═╝   ╚═╝╚═╝     ╚═╝╚══════╝
    */
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


    fprintf(stdout, "Hi, How should we adress to you?: ");
    fflush(stdin);
    fflush(stdout);
    fgets(masterUserName, MAX_USERNAME_SIZE, stdin);

    //int len=masterUserName[strlen(masterUserName)-1] + '\0';
    fflush(stdin);
    fflush(stdout);

    fprintf(stdout, "Hi, %s", masterUserName);
    fprintf(stdout, "Please, introduce your Master Password: ");
    fflush(stdin);
    fflush(stdout);
    fgets(masterPassword, MAX_PASSWORD_SIZE, stdin);
    fflush(stdin);
    fflush(stdout);


}
void menuMain()
{
    fprintf(stdout, "What do you want to do?\n");
    fprintf(stdout, "1) See saved Accounts\n");
    fprintf(stdout, "2) Add a new Account\n");
    fprintf(stdout, "3) Delete an Account\n");
    fprintf(stdout, "4) Save and Exit\n");
    fprintf(stdout,"\n");
    fprintf(stdout, "Select an Option:\n");
    fflush(stdin);
    fflush(stdout);
}

void setupFilePath(char* filePath,char* masterUserName){

  //  char filePath[MAX_USERNAME_SIZE + 10]; //+6 FOR THE ./ AND +4 FOR THE.BIN
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

    //for debugging
    /*fprintf(stdout, "%s", filePath);*/
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

void askPassword(char* masterPassword)
{
    //it cannot read the file, so it's a new user for sure
    char masterPasswordCheckAccount[MAX_PASSWORD_SIZE];
    welcomeNewUser();
    fprintf(stdout, "Write again your Master Password: ");
    fflush(stdin);
    fflush(stdout);
    fgets(masterPasswordCheckAccount, MAX_PASSWORD_SIZE, stdin);

    if (strcmp(masterPassword,masterPasswordCheckAccount) == 0) {
        fprintf(stdout, "Perfect, your Master Password have been confirmed.\n");
    }else{
        do {
            fprintf(stdout, "The password didn't match.");
            fprintf(stdout, "Please Introduce a New Master Password:");
            fflush(stdin);
            fflush(stdout);
            fgets(masterPassword, MAX_PASSWORD_SIZE, stdin);
            fprintf(stdout, "Write again the New Password:");
            fflush(stdin);
            fflush(stdout);
            fgets(masterPasswordCheckAccount, MAX_PASSWORD_SIZE, stdin);

        } while (strcmp(masterPassword, masterPasswordCheckAccount) != 0);
        //remove the carriage return from last position of the string
        masterPassword[strlen(masterPassword)-1] = '\0';
    }


}

/*

    ████████╗██╗  ██╗███████╗    ███████╗███╗   ██╗██████╗
    ╚══██╔══╝██║  ██║██╔════╝    ██╔════╝████╗  ██║██╔══██╗
       ██║   ███████║█████╗      █████╗  ██╔██╗ ██║██║  ██║
       ██║   ██╔══██║██╔══╝      ██╔══╝  ██║╚██╗██║██║  ██║
       ██║   ██║  ██║███████╗    ███████╗██║ ╚████║██████╔╝
       ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═══╝╚═════╝

*/