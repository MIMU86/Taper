#include "pch.h"
#include "wechat.h"

void WeChat::SendPic(const wchar_t* to_wxid, const wchar_t* path)
{
    DWORD call_addr1 = Offset(0x58CC00);
    DWORD call_addr2 = Offset(0x63720);
    DWORD call_addr3 = Offset(0x3B4F60);

    String to_wxid_stu{ to_wxid };

    String path_stu{ path };

    char call1_buf[0x30];
    char call2_buf[0x230];
    /*
    6334CB6F    83EC 14         sub esp,0x14                             ; ����ͼƬcall��ʼ
    6334CB72    8D47 E0         lea eax,dword ptr ds:[edi-0x20]          ; ���ջ�����
    6334CB75    8BCC            mov ecx,esp
    6334CB77    8965 BC         mov dword ptr ss:[ebp-0x44],esp
    6334CB7A    50              push eax                                 ; ����������
    6334CB7B    E8 80004800     call WeChatWi.637CCC00                   ; call1
    6334CB80    53              push ebx                                 ; ͼƬ·��
    6334CB81    8D85 78FFFFFF   lea eax,dword ptr ss:[ebp-0x88]          ; wxid
    6334CB87    C645 FC 09      mov byte ptr ss:[ebp-0x4],0x9
    6334CB8B    50              push eax                                 ; wxid����
    6334CB8C    8D85 B0FCFFFF   lea eax,dword ptr ss:[ebp-0x350]         ; ���ջ�����
    6334CB92    50              push eax                                 ; ����������
    6334CB93    E8 886BF5FF     call WeChatWi.632A3720                   ; call2
    6334CB98    8BC8            mov ecx,eax                              ; call2���ؽ��
    6334CB9A    C645 FC 01      mov byte ptr ss:[ebp-0x4],0x1
    6334CB9E    E8 BD832A00     call WeChatWi.635F4F60                   ; ����ͼƬcall����
    */
    __asm {
        sub esp, 0x14; //����
        lea eax, call1_buf; //������1
        mov ecx, esp;
        push eax;
        call call_addr1;

        lea ebx, path_stu; //
        push ebx; //ͼƬ·��
        lea eax, to_wxid_stu; //
        push eax; //����wxid
        lea eax, call2_buf;
        push eax;
        call call_addr2; //ȡ��eax

        mov ecx, eax;
        call call_addr3;
    }
}