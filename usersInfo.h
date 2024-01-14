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
#ifndef ENCRYPTED_ACCOUNT_MANAGER_USERSINFO_H
#define ENCRYPTED_ACCOUNT_MANAGER_USERSINFO_H
#include <stdio.h>
#include "stdlib.h"
#include <string.h>

//Define Struct
typedef struct {
    char *username;
    char *password;
    int username_length;
    int password_length;
} userInfo;

userInfo* createUserInfo(int numInitialAllocation);
void fillUserInfo(userInfo *user);
void freeUserInfo(userInfo *user); //Not used
void freeAllUserInfo(userInfo* user, int numUserPairs); //Not used
void deleteUserInfo(userInfo* users, int* numUserPairs, int indexToDelete,char* path,const char *encryptionKey);


#endif //ENCRYPTED_ACCOUNT_MANAGER_USERSINFO_H