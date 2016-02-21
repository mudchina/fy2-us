//mac's jiaolou1.c
// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
#include <room.h>
inherit ROOM;
void create()
{
  set("short","Ç¬½ÇÂ¥");
  set("long",@LONG
ÕâÊÇá·ÃíÎ§Ç½ËÄÓçµÄ½ÇÂ¥£¬·Ö±ğÒÔËÄØÔÎªÃû£¬ÒÔÇó±ÜĞ×Ç÷¼ª£¬Â¥ÖĞ
ÓĞÒ»Ãæ´ó±®£¬±®ÉÏÊéÒ»´ó×Ö£º
[33m
				Ç¬
[37m
LONG
  );
  set("exits",([
         "north":__DIR__"jiaolou4.c",
         "west" :__DIR__"zhengyan.c",
               ]));
          set("objects", ([
                __DIR__"npc/gang2" : 1,
       ]) );
  setup();
  replace_program(ROOM);
}
