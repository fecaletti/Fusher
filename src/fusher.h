#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

enum OS_ENUMERATOR
{
    LINUX_X86,
    LINUX_X64,
    WINDOWS_X86,
    WINDOWS_X64,
};

/* Fusher interface */
class iFusher
{
    public:
        virtual bool CreateBridge(const char* name) { return false; };
        virtual bool DeleteBridge(const char* name) { return false; };
        virtual int  GetBridgeCount() { return 0; };
        
        virtual bool UpdateBridge(const char* name, const char* data) { return false; };
        virtual bool GetLatestBridgeInfo(const char* name, const char* output) { return false; };
};

/* Fusher files interface */
class iFusherFile
{
    public:
        virtual bool InsertData(const char* data) { return false; };
        //virtual bool updateField(const char* field, const char* data) { return false; };
        virtual bool ReadData(const char* outPtr) { return false; };
};

/* Fusher factory interface */
class iFusherFactory
{
    public:
        virtual iFusher* CreateFusher() { return nullptr; };
};

/* Fusher factory to create the correct object based on the OS */
class FusherFactory : public iFusherFactory
{
    public:
        iFusher* CreateFusher();
    private:
        OS_ENUMERATOR DetectOS();
};

/* Fusher-file class */
class FusherFile : public iFusherFile
{
    public:
        FusherFile(const char* name);
        bool InsertData(const char* data);
        bool ReadData(const char* outPtr);
    private:
        const char* fileName;
        int fileState;
        string fileBuffer;
};

/* Base-Fusher class */
class BaseFusher : public iFusher
{
    public:
        bool CreateBridge(const char* name);
        bool DeleteBridge(const char* name);
        int  GetBridgeCount();
    protected:
        int bridgeCounter = 0;
        std::map<string, iFusherFile*> bridges;
};

/* Fusher windows concrete class */
class FusherWindows : public BaseFusher
{
    public:
        FusherWindows();        
        bool UpdateBridge(const char* name, const char* data);
        bool GetLatestBridgeInfo(const char* name, const char* output);
};