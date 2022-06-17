#pragma once
/*Includes*/
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <ctype.h>

/*Defines*/
#define KEY_UP 72
#define KEY_DOWN 80

/*Namespaces*/
using std::cout;
using std::cin;
using std::endl;
using std::string;

/*Prototypes*/
void BeginProgram();
void WriteInColor(unsigned short color, string outputString);
void PrintArray_MainMenu();
void ArrowSelectionMenu_MainMenu();