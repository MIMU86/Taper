#include "pch.h"
#include "wechat.h"

/// <summary>
/// ����wxidȡ�û���Ϣ
/// Ϊ����ȡ������Ϣ
/// </summary>
/// <param name="wxid"></param>
/// <returns></returns>
WeChat::Info WeChat::GetInfo(const wchar_t* wxid)
{
    DWORD call1_addr = Offset(0x0);
    DWORD call2_addr = Offset(0x0);
    DWORD call3_addr = Offset(0x0);

    _asm
    {

    }
    return {};
}

/// <summary>
/// ȡ΢�Ÿ���id
/// </summary>
/// <returns></returns>
const char* WeChat::wxid()
{
    return *(const char**)Offset(0x1AA6038);
}

const char* WeChat::avatar()
{
    return *(const char**)Offset(0x1AA5EFC);
}

const char* WeChat::nickname()
{
    return (const char*)Offset(0x1AA6020);
}

const char* WeChat::platform()
{
    return (const char*)Offset(0x1AA6070);
}

const char* WeChat::phone()
{
    return (const char*)Offset(0x1AA5C50);
}

bool WeChat::IsLogin()
{
    return *(bool*)Offset(0x1AA6010);
}