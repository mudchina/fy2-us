//tan2.c

inherit ROOM;

void create()
{
	set("short", "�����Ϻ� ");
	set("long",
		"�����Ǽ����Ϻ�ˮ�� �����ܵ���������Щ�谵�ˣ���������ͷ����̶ˮ��Ͷ����\n"
		"������ʱҲ����ô�����ˣ��������������ߵ���ϼ���������һƬҲ��֪��\n"
		"Щʲô�����ܵ�ˮ��Ҳû����ôƽ���ˣ��ƺ�����һ�����������š��㲻������\n"
		"һ���������а����ɣ���\n"

	);
	set("exits", ([
		"up" : __DIR__"tan1",
		"down" : __DIR__"tan3",
	]));
	setup();
	replace_program(ROOM);
}