//mac's houzai.c
// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.

#include <room.h>
inherit ROOM;
void create()
{
  set("short","������");
  set("long",@LONG
��������ĺ��ţ������Ǹ����ɵ���שΧǽ�������򱱱���̩ɽ
�ˣ�������ۻ��ǱشӴ��ţ���˳�Ϊ�����ţ�Ϊ���ض������˼��
LONG
  );
  set("exits",([
 //        "north":"/d/taishan/daizong.c",
         "south":__DIR__"tongting.c",
         "west" :__DIR__"jiaolou3.c",
         "east" :__DIR__"jiaolou4.c",
               ]));
        set("objects", ([
                __DIR__"npc/tie" : 1,
       ]) );
  setup();
  replace_program(ROOM);
}