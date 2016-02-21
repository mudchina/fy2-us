// Room: /u/cat/workroom.c

inherit ROOM;

void create()
{
        set("short", "Ã¨µÄ¹¤×÷ÊÒ");
        set("long", @LONG
ÕâÊÇÃ¨µÄ¹¤×÷ÊÒ,¿Õµ´µ´µÄ,Ö»ÓÐÒ»Ì¨µçÄÔ,Ò»±­Ë®¶øÒÑ. Ç½ÉÏ¹ÒÕß
Ò»ÕÅ¿ñ²Ý×Ö·ù:

                  [37;44m©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©·[0m
                  [37;44m©§[33m Ë¹ÊÇÂªÊÒ,ÆäÀÖÈÚÈÚ©§[0m
                  [37;44m©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿[0m

    [35mÆ½Æ½µ­µ­²ÅÊÇÕæ°¡~~~~~~~~~~~~~~~.[0m

LONG
        );
        set("exits", ([ /* sizeof() == 1 */
	"down" : "/d/fy/fysquare",
	"west" : "/u/t/tjb/workroom",
	// "out" : "/d/wizard/workroom",
]));
	set("valid_startroom",1);
        set("objects",([
                __DIR__"guo" : 5,
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
