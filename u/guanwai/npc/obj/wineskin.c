// waterskin.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("��Ƥ�ƴ�", ({ "wineskin", "skin" }) );
	set_weight(700);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ����Ƥ��Ĵ�ƴ������װ�ðˡ������ľơ�\n");
		set("unit", "��");
		set("value", 20);
		set("max_liquid", 15);
	}

	// The liquid contained in the container is independent, we set a copy
	// in each cloned copy.
	set("liquid", ([
		"type": "alcohol",
		"name": "���̾�",
		"remaining": 15,
		"drunk_apply": 7,
	]) );
}
