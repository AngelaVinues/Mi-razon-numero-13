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
#ifndef ENCRYPTED_ACCOUNT_MANAGER_FILES_H
#define ENCRYPTED_ACCOUNT_MANAGER_FILES_H
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "usersInfo.h"


int writeUserInfo(char* path, const userInfo* userInfo, const int* numUserPairs, const char *encryptionKey);

userInfo* readUserInfo(char* path, int* numUserPairs, const char *encryptionKey, int* authentication);

void XORCifrado(char* data, const char* key, int dataLen, int keyLen,char* outputCifrado);


unsigned char checksum ( char *ptr, size_t sz);

#endif //ENCRYPTED_ACCOUNT_MANAGER_FILES_H