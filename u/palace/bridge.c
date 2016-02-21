
inherit ROOM;

void create()
{
        set("short", "独木危桥");
        set("long", @LONG
这是一条宽约七寸的独木桥，天风凛冽，吹的人衣襟头发齐飞，只
要一不留神，稍一失足，立刻便要粉身碎骨。两崖相隔，约有五十余丈，
往下看，峭壁如刀削，云卷雾涌，深不见底，投块石子下去，也听不到
回声！
LONG
        );
        set("exits", ([ 
  "east" : __DIR__"intersection",
  "west" : __DIR__"entrance",
]));
        set("outdoors", "palace");

        setup();
}
int valid_leave(object me, string dir)
{
	object *inv;
	object ob;
	if( userp(me))
	{
	switch(random(9)){
		case 0:
	message_vision("$N脚下一滑，在独木桥上晃了晃．．\n",me);
	return notify_fail("还好，没掉下去！\n");
		break;
		case 1:
	inv = all_inventory(me);
	if(sizeof(inv)>=1)	
	{
		ob = inv[random(sizeof(inv))];
	message_vision(ob->name()+"从$N身上滑了出来，落入万丈深渊．\n",me);
		destruct(ob);
	}
	return notify_fail("你在独木桥上前仰后合地晃着．．．\n");
		break;
		default:
		return 1;
		break;
			}
	}
	else
	return 1;
}

