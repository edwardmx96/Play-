#include "Iop_LibSd.h"
#include "../Log.h"

#define LOG_NAME "iop_libsd"

using namespace Iop;
using namespace std;

CLibSd::CLibSd(CSIF& sif)
{
    sif.RegisterModule(MODULE_ID, this);
}

CLibSd::~CLibSd()
{

}

string CLibSd::GetId() const
{
    return "libsd";
}

void CLibSd::Invoke(CMIPS& context, unsigned int functionId)
{
    throw runtime_error("Not implemented.");
}

void CLibSd::Invoke(uint32 method, uint32* args, uint32 argsSize, uint32* ret, uint32 retSize, uint8* ram)
{
	switch(method)
	{
	case 0x8100:
        GetBufferSize(args, argsSize, ret, retSize);
        break;
	default:
        CLog::GetInstance().Print(LOG_NAME, "Unknown method invoked (0x%0.8X).\r\n", method);
		break;
	}
}

void CLibSd::GetBufferSize(uint32* args, uint32 argsSize, uint32* ret, uint32 retSize)
{
    static uint32 temp = 0;
    temp += 0x400;
    ret[0] = temp;
}