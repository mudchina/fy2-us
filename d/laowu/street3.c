
inherit ROOM;

void create()
{
        set("short", "���ر���");
        set("long", @LONG
�����µı��ӣ��������Ի�׳�ۡ�����ʮ�ɣ����������������Ӱ��ܽ���������
ɫȴ����ȱ𴦻�Ҫ�Щ��һ�ο���¶�ں����ϣ�����ǿ�ʼ�⽭��ʱ�������ġ�
��֦Ҳ��֪��˭��ƽ�ˣ�����ȴ����һС��¶�ں����⡣
LONG
        );
        set("exits", ([ 
  "west" : __DIR__"street2",
  "east" : __DIR__"street4",
  "north" : __DIR__"street5",
  "south" : __DIR__"street6",
  "southwest" : __DIR__"street7",
  "northwest" : __DIR__"street8",
]));
        set("outdoors", "laowu");

        setup();
        replace_program(ROOM);

}
