#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "三清宫厢房");
	set("long", @LONG
不大的房间，却很干净明亮。左面墙上挂着几副山水画，
画下是几张床榻，几个道士正在打坐。右面的墙上挂着几把长
剑．可以看出它们都是好剑。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  		"east" : "/u/taoguan/da_yuan",
]));
        set("objects", ([ /* sizeof() == 2 */
                "/u/taoguan/npc/reg_taoist" : 5,
                "/u/taoguan/npc/up_taoist" : 1,
]));
	setup();
	replace_program(ROOM);
}
