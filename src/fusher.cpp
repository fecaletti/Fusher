#include "fusher.h"

/* Factory implementation */
OS_ENUMERATOR FusherFactory :: DetectOS()
{
    #ifdef __unix__
        return OS_ENUMERATOR :: LINUX_X86;
    #elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        return OS_ENUMERATOR :: WINDOWS_X64;
    #endif
}

iFusher* FusherFactory :: CreateFusher()
{   
    iFusher* newObject = nullptr;
    switch (this->DetectOS())
    {
        case OS_ENUMERATOR :: WINDOWS_X64:
            newObject = new FusherWindows();
            break;
        
        default:
            break;
    }

    return newObject;
}

/* Fusher file implementation */
FusherFile :: FusherFile(const char* name)
{
    this->fileName = name;
}

bool FusherFile :: InsertData(const char* data)
{
    std :: ofstream thisFile(this->fileName, std :: ifstream :: app);
    thisFile.write(data, strlen(data));

    thisFile.close();
    return true;
}

bool FusherFile :: ReadData(const char* outPtr)
{
    std :: ifstream thisFile(this->fileName, std :: ifstream :: in);
    std :: stringstream strBuff;

    strBuff << thisFile.rdbuf();

    this->fileBuffer = strBuff.str();
    outPtr = this->fileBuffer.c_str();

    thisFile.close();
    return true;
}

/* Base Fusher implementation */
bool BaseFusher :: CreateBridge(const char* name)
{
    this->bridges[name] = new FusherFile(name);
    return true;
}

bool BaseFusher :: DeleteBridge(const char* name)
{
    return true;
}

int BaseFusher :: GetBridgeCount()
{
    return this->bridgeCounter;
}

/* Fusher Windows implementation */
FusherWindows :: FusherWindows()
{

} 