#include "pch.h"
#include "wechat.h"

namespace {

WeChat::MsgHandler khandler;
DWORD old_call_addr;
DWORD ret_addr;
DWORD msg_addr;

void __declspec(naked) RecvMsgCall()
{
    _asm
    {
        call old_call_addr; // �����ǵ�ԭָ��
        mov msg_addr, esi;
    }
    [] {
        if (::IsBadReadPtr(&msg_addr, 0x258) != 0)
        {
            return;
        }
        // �ж��Ƿ�����Ϣ
        if (*(LPCWSTR*)(msg_addr + 0x68) == nullptr)
        {
            return;
        }

        DWORD type = *(DWORD*)(msg_addr + 0x30);
        DWORD from = *(DWORD*)(msg_addr + 0x34);

        //��Ϣ���� 0x01���� 0x03ͼƬ 0x22���� 0x25����ȷ�� 0x28���� 0x2A��Ƭ 0x2B��Ƶ 0x2F���� 0x30λ�� 0x2710ϵͳ��Ϣ
        //        0x31����ʵʱλ�� �ļ� ת�� ���� �տ�
        DWORD type2 = *(DWORD*)(msg_addr + 0xEC);
        if (type == 0x31 && type2 != 0x0)
        {
            type = type2;
        }
        const wchar_t* from_wxid = *(const wchar_t**)(msg_addr + 0x40);
        const wchar_t* msg = *(const wchar_t**)(msg_addr + 0x68);
        const wchar_t* final_from_wxid = *(const wchar_t**)(msg_addr + 0x164);
        const wchar_t* msgid = *(const wchar_t**)(msg_addr + 0x178);
        khandler(type, from, msg, from_wxid, final_from_wxid, msgid);
    }();
    __asm jmp ret_addr;
}

} //namespace


void WeChat::BindMsgHandler(MsgHandler handler)
{
    khandler = handler;

    old_call_addr = Offset(0x87800); //ԭָ���call

    //msg_ptr = WeChatWin_ + 0x1AA872C; //��Ϣ�ṹ��ָ��Ĵ�ŵ�ַ

    DWORD jmp_addr = Offset(0x2F24E7); //��Ҫ��ת�ĵ�ַ
    ret_addr = jmp_addr + 5; //��ת���صĵ�ַ


    BYTE jmp_code[5] = { 0xE9 }; //��ָ�� call
    *(DWORD*)&jmp_code[1] = (DWORD)RecvMsgCall - jmp_addr - 5; //����ת���ĺ���

    /*
    70D124DC    8D4D B8         lea ecx,dword ptr ss:[ebp-0x48]
    70D124DF    84C0            test al,al
    70D124E1    75 03           jnz short WeChatWi.70D124E6
    70D124E3    8D4D D0         lea ecx,dword ptr ss:[ebp-0x30]
    70D124E6    56              push esi                                 ; ��Ϣ�ṹ��
    70D124E7    E8 1453D9FF     call WeChatWi.70AA7800                   ; ��©��Ϣ�Ľ�����Ϣhook
    70D124EC    81C6 58020000   add esi,0x258
    70D124F2    81C7 58020000   add edi,0x258
    70D124F8    3B73 04         cmp esi,dword ptr ds:[ebx+0x4]
    */
    WriteProcessMemory(
        GetCurrentProcess(),
        (void*)jmp_addr,
        &jmp_code,
        sizeof(jmp_code),
        NULL
    );
}