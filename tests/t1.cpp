
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"

using namespace std;
using namespace rapidjson;

typedef struct TestData
{
    bool run;
    int data1;
    int data2;
};

typedef struct ResultData
{
    int result;
};

#define INPUT_FILE      "_fusher_in.fs"
#define OUTPUT_FILE     "_fusher_out.fs"

bool getInput(const char* inFile, TestData* target);
bool setOutput(const char* outFile, ResultData data);
int doAction(TestData input);

int main(void)
{
    TestData inputObj;
    ResultData outputObj;

    int operationCounter = 0;

    while(true)
    {
        getInput(inData, &inputObj);
        outputObj.result = doAction(inputObj);
        operationCounter++;

        if(setOutput(outData, outputObj))
        {
            cout << "Output pushed! Total operations = " << operationCounter << endl;
        }
        else
        {
            cout << "Output push failed at operation " << operationCounter << "..." << endl;
        }
    }

    cout << "Loop ended... Returning." << endl;
    return 0;
}

int getInput(const char* inFile, TestData* target)
{
    FILE* inData = fopen(inFile, "r");
    
    char inputData[100];
    char actChar = '';
    int sizeCounter = 0;
    while(actChar != EOF)
    {
        actChar = fgetc(inFile);
        inputData[sizeCounter] = actChar;
    }

    return stoi(inputData);
}

bool setOutput(const char* outFile, ResultData data)
{
    FILE* outData = fopen(outFile, "w");
}

int doAction(TestData input)
{
    return input.data1 + inputData.data2;
}