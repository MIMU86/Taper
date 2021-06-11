#include "pch.h"
#include "wechat.h"

/// <summary>
/// ����ģʽ
/// </summary>
/// <returns></returns>
WeChat& WeChat::Instance()
{
    static WeChat vx;
    return vx;
}

DWORD WeChat::Offset(DWORD offset)
{
    return (DWORD)WeChatWin_ + offset;
}


bool WeChat::Init(std::string& ret)
{
    //����Wechatģ��
    WeChatWin_ = LoadLibraryA("WeChatWin");
    if (WeChatWin_ == nullptr)
    {
        ret = std::to_string(GetLastError());
        return false;
    }
    return true;
}
