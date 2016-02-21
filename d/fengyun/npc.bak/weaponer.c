
inherit NPC;
inherit F_VENDOR;
#include <ansi.h>
void create()
{
	set_name("Öî¸ðÀ×", ({ "zhuge" }) );
	set("gender", "ÄÐÐÔ" );
	set("age", 31);
	set("title", HIG "¼±·ç½£" NOR);
	set("long",
		"½ðÊ¨ïÚ¾ÖµÄ´óïÚÍ·£¬ÊÖµ×ÏÂ»¹¿ÉÒÔ£®\n");
	set("combat_exp", 500000);
	set("attitude", "friendly");
	set("per",30);
	set("vendor_goods", ([
                "±Þ×Ó": "/obj/weapon/whip",
                "³¤½£": "/obj/weapon/longsword",
                "·ÉïÚ": "/obj/weapon/dart",
                "Å£Æ¤¶Ü": "/obj/weapon/shield",
                "°Ë½Ç´¸": "/obj/weapon/eighthammer",
                "Ï¸½£": "/obj/weapon/thin_sword",
                "Ø°Ê×": "/obj/weapon/dagger.c",
               "µ¥µ¶": "/obj/weapon/blade.c",
		"ìøÕÈ" : __DIR__"obj/1staff.c",
                "·Éµ¶" : __DIR__"obj/knife.c",
               "Ë«»·" : __DIR__"obj/dual_ring.c",
	]) );
	set_skill("sword",50);
	set_skill("six-chaos-sword",50);
	set_skill("pyrobat-steps",50);
	set_skill("dodge",50);
	set_skill("parry",50);
	map_skill("dodge","pyrobat-steps");
	map_skill("parry", "six-chaos-sword");
	map_skill("sword","six-chaos-sword");
	setup();
	carry_object(__DIR__"obj/jinzhuang")->wear();
	carry_object("/obj/longsword")->wield();
}
void init()
{
        add_action("do_vendor_list", "list");
}

