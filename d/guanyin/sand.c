// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit ROOM;
void create()
{
        set("short", "�����Ļ�ɳ��");
        set("long", @LONG
������Ӱ���ƺ�������ɨ��ɨ�أ����ǵĶ�������ô������ȴ����
��ô���й��ɣ�����������һȺû�������Ŀ��ܣ����Ǻ������������
ʱɨ�ŵأ�һֱҪɨ�������ĩ�ա�
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"flower",
  "south" : __DIR__"narrow",
]));
        set("objects", ([
                __DIR__"npc/ghost" : 3,
       ]) );

        setup();
        replace_program(ROOM);
}