// dog.c

inherit NPC;

void create()
{
	set_name("ÂéÈ¸", ({ "bird" }) );
	set("race", "Ò°ÊŞ");
	set("age", 1);
	set("long", "ßÒßÒÔûÔûµÄÒ»Ö»Ğ¡ÂéÈ¸¡£\n");
	
	set("limbs", ({ "Í·²¿", "ÉíÌå", "³á°ò", "Î²°Í" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("chat_chance", 50);
	set("chat_msg", ({
		(: this_object(), "random_move" :),
		"ßÒßÒ¡£\n",
		"ÔûÔû¡£\n",
	}));
	set_temp("apply/dodge", 100);
	set_temp("apply/attack", 10);
	set_temp("apply/armor", 3);

	setup();
}
