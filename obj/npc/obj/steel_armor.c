// steel_armor.c

#include <armor.h>

inherit ARMOR;

void create()
{
	set_name("�ظ�ս��", ({ "steel armor", "armor" }) );
	set_weight(70000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "steel");
		set("value", 9000);
                set("no_get",1);
                set("no_drop",1);

		set("armor_prop/armor", 70);
		set("armor_prop/dodge", -30);
	}
	setup();
}
