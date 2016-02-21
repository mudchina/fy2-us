//mac's jiaolou3.c
// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
#include <room.h>
inherit ROOM;
void create()
{
  set("short","¿²½ÇÂ¥");
  set("long",@LONG
ÕâÊÇá·ÃíÎ§Ç½ËÄÓçµÄ½ÇÂ¥£¬·Ö±ğÒÔËÄØÔÎªÃû£¬ÒÔÇó±ÜĞ×Ç÷¼ª£¬Â¥ÖĞ
ÓĞÒ»Ãæ´ó±®£¬±®ÉÏÊéÒ»´ó×Ö£º
[31m
				¿²
[37m
LONG
  );
  set("exits",([
         "south":__DIR__"jiaolou1.c",
         "east" :__DIR__"houzai.c",
               ]));
        set("objects", ([
                __DIR__"npc/gang3" : 1,
       ]) );
  setup();
  replace_program(ROOM);
}
