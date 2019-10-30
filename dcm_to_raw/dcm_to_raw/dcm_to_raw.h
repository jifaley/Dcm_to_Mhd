#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <io.h>
#include <string.h>
#define MAX_PATH 10000


std::string getSerialID(std::string working_dir);

void getFilesFromDirectory(std::vector<std::string>& files, const char* directoryPath);

void convert(std::string working_dir,std::string serial_id, std::string option, std::string ouput_dir);