// kickout.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string wiz_status;
	string tmpstr;

	if( me!=this_player(1) ) return 0;

	if( !arg || sscanf(arg, "%s", arg)!=1 )
		return notify_fail("argument error!\n");


	wiz_status=SECURITY_D->get_status(me) ;

	if (wiz_status != "(admin)" && !me->query("marks/踢人") ) 
		return notify_fail("you r not admin!\n");

        ob = LOGIN_D->find_body(arg);
        if (!ob) return notify_fail("咦... 有这个人吗?\n");

                if (    !living(ob)
                ||      !ob->is_character()
                ||      ob==me )
			return notify_fail("ob error!\n");
	message_vision( HIW "\n$N把$n踢了出去\n\n" NOR, me,ob);
//	seteuid(getuid(ob));
//	command("quit");
//me->save();
	seteuid(ROOT_UID);
        ob->save();
        destruct(ob);
	seteuid(getuid());
	
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : kickout <某人>

HELP
    );
    return 1;
}

