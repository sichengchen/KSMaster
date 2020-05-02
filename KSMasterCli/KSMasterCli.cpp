/**
Copyright 2020 scchan

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissionsand
limitations under the License.
**/

//--------------------------------------//
// Project KSMaster                     //
// KSMasterCli.cpp                      //
//--------------------------------------//
//     Created by ChenSC ("scchan")     //
//              2020/5/1                //
//     mail:sicheng.chen@scchan.com     //
//--------------------------------------//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "csv.h"
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

int main( int argc, char* argv[] )
{
    int argvlabel = 0;
    if (argc == 1) {
        printf("Error: invalid path\nUsage:\n\"ksmastercli <source_file_path> (-o) (<output_file_path>)\"\nFor more help please visit our website.\n");
        return 0;
    }
    for (int j = 1; j <= argc; j++) {
        if (argv[j] == "-o") {
            argvlabel = j + 1;
        }
    }
    srand(int(time(0)));
    std::string stuName[50],sname[50];
    int stuNum[50], stuRank[50],snumber[50];
    io::CSVReader<3> in(argv[1]);
    in.read_header(io::ignore_extra_column, "stunum", "stuname", "sturank");
    std::string stuname; int stunum; int sturank;
    int i = 1;
    while (in.read_row(stunum, stuname, sturank)) {
        stuName[i] = stuname;
        stuNum[i] = stunum;
        stuRank[i] = sturank;
        i++;
    }
    int MAXN = 48;
    for (int j = 1; j <= MAXN; j++) {
        snumber[stuRank[j]] = stuNum[j];
        sname[snumber[stuRank[j]]] = stuName[j];
    }
    int kai[10][10];
    int j = 1;
    while( j <= MAXN ){
        for (int k = 1; k <= 6; k++) {
            for (int l = 1; l <= 8; l++) {
                kai[k][l] = snumber[j];
                j++;
            }
        }
    }
    int group[10][10];
    int gumiin[10];
    for (int k = 1; k <= 8; k++)gumiin[k] = 1;
    for (int kurasu = 1; kurasu <= 6; kurasu++) {
        bool flag[10];
        for (int k = 1; k <= 8; k++)flag[k] = 0;
        for (int kurasuin = 1; kurasuin <= 8; kurasuin++) {
            randl:int tmpa = rand() % 8 + 1;
            if (!flag[tmpa]) {
                group[tmpa][gumiin[tmpa]] = kai[kurasu][kurasuin];
                flag[tmpa] = 1;
                gumiin[tmpa]++;
            }
            else {
                goto randl;
            }
        }
    }
    int result[10][10];
    for (int j = 0; j < 10; j++) {
        for (int k = 0; k < 10; k++) {
            result[j][k] = 0;
        }
    }
    for (int j = 1; j <= 8; j++) {
        bool flag[10];
        for (int k = 1; k <= 7; k++)flag[k] = 0;
        for (int k = 1; k <= 6; k++) {
            randm:int tmpb = rand() % 6 + 1;
            if (!flag[tmpb]) {
                result[j][tmpb] = group[j][k];
                flag[tmpb] = 1;
            }
            else {
                goto randm;
            }
        }
    }
    std::ofstream outFile;
    outFile.open(argvlabel==0?"map.csv":argv[argvlabel]);
    const char c1 = 0xEF;
    const char c2 = 0xBB;
    const char c3 = 0xBF;
    outFile << c1 << c2 << c3;
    outFile << ",,,,座位表" << std::endl;
    outFile << "行列";
    for (int j = 1; j <= 8; j++) {
        outFile << "," << j;
    }
    outFile << std::endl;
    for (int j = 1; j <= 3; j++) {
        outFile << 7-j;
        for (int k = 1; k <= 4; k++) {
            for (int l = j*2-1; l <= j*2; l++) {
                outFile << "," << sname[result[k][l]];
            }
        }
        outFile << std::endl;
    }
    for (int j = 4; j <= 6; j++) {
        outFile << 7-j;
        for (int k = 5; k <= 8; k++) {
            for (int l = (j-3) * 2 - 1; l <= (j-3) * 2; l++) {
                outFile << "," << sname[result[k][l]];
            }
        }
        outFile << std::endl;
    }
    outFile << ",,,,讲台" << std::endl;
    outFile << "Powered by KSMasterCli (Ver0.3). ChenSC" << std::endl;
    std::cout << "Done." << std::endl;
    return 0;
}