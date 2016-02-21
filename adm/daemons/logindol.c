// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
string Rname;
int STRv, CPSv, INTv, CORv, CONv, SPIv, PERv, KARv;
string *banned_name = ({
        "Äã", "Äã", "ÎÒ", "Ëû", "Ëı", "Ëü", "Ëü",
        "·çÔÆ","°¢Ìú", 
});
// in the format of 129.4.84.110, or tuna.sp.trw.com
string *banned_site = ({

"*.*.*.*",

});
string *start_loc = ({
        "/d/snow/inn",
        "/u/guanwai/inn",
        "/u/cloud/tearoom",
	"/d/choyin/hotel1",
	"/d/fy/fysquare",
        "/d/fy/fysquare",
        "/d/fy/fysquare",

});
private void get_id(string arg, object ob);
private void read_msg(string arg, object ob);
private void get_resp(string arg, object ob);
private void confirm_id(string yn, object ob);
object make_body(object ob);
private init_new_player(object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
string random_name();
void create() 
{
        seteuid(getuid());
        set("channel_id", "Á¬Ïß¾«Áé");
}

void logon(object ob)
{
        object *usr;
        int i, wiz_cnt, ppl_cnt, login_cnt;
	string siteip;
	siteip = query_ip_name(ob);
        if( member_array(siteip, banned_site)!=-1 ) {
                write("¶Ô²»Æğ£¬Çë£Å£Í£Á£É£Ì
		£ê£é£å£À£î£é£ã£ã£ï£®£ó£ó£ã£î£å£ô£®£õ£ã£ì£á£®£å£ä£õ
			³ÂËß¡£\n");
		destruct(ob);
                return ;
        }

         cat( WELCOME) ;
        UPTIME_CMD->main();

        usr = users();
        wiz_cnt = 0;
        ppl_cnt = 0;
        login_cnt = 0;
        for(i=0; i<sizeof(usr); i++) {
                if( !environment(usr[i]) ) login_cnt++;
                else if( wizardp(usr[i]) ) wiz_cnt++;
                else ppl_cnt++;
        }
        printf(RED"Ä¿Ç°¹²ÓĞ%sÎ»ÉñÏÉ¡¢%sÎ»Íæ¼ÒÔÚÏßÉÏ£¬ÒÔ¼°%s 
Î»Ê¹ÓÃÕß³¢ÊÔÁ¬ÏßÖĞ¡£\n\n" NOR,
                chinese_number(wiz_cnt), chinese_number(ppl_cnt), 
		chinese_number(login_cnt) );

        write("ÄúµÄÓ¢ÎÄÃû×Ö£º");
        input_to( (: get_id :), ob );
}

private void get_id(string arg, object ob)
{
        object ppl;


        arg = lower_case(arg);
        if( !check_legal_id(arg)) {
                write("ÄúµÄÓ¢ÎÄÃû×Ö£º");
                input_to("get_id", ob);
                return;
        }
#ifdef MAX_USERS
        if( (string)SECURITY_D->get_status(arg)=="(player)"
        && sizeof(users()) >= MAX_USERS ) {
                ppl = find_body(arg);
        // Only allow reconnect an interactive player when MAX_USERS exceeded.
                if( !ppl || !interactive(ppl) ) {
                        write("¶Ô²»Æğ£¬" + MUD_NAME + 
"µÄÊ¹ÓÃÕßÒÑ¾­Ì«¶àÁË£¬Çë´ı»áÔÙÀ´¡£\n");
                        destruct(ob);
                        return;
                }
        }
#endif

        if( wiz_level(arg) < wiz_lock_level ) {
                write("¶Ô²»Æğ£¬" + MUD_NAME + "Ä¿Ç°ÕıÔÚÕûÀíÍæ¼Ò×ÊÁÏ£¬Çë¹ı¼¸·ÖÖÓÔÙÁ¬Ïß¡£\n");
                destruct(ob);
                return;
        }
        
        if( (string)ob->set("id", arg) != arg ) {
                write("Failed setting user name.\n");
                destruct(ob);
                return;
        }

        if( arg=="guest" ) {
                // If guest, let them create the character.
                confirm_id("Yes", ob);
                return;
        } else if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 
) {
                if( ob->restore() ) {
                        write("ÇëÊäÈëÃÜÂë£º");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("ÄúµÄÈËÎï´¢´æµ²³öÁËÒ»Ğ©ÎÊÌâ£¬ÇëÀûÓÃ guest 
ÈËÎïÍ¨ÖªÎ×Ê¦´¦Àí¡£\n");
                destruct(ob);
                return;
        }

        write("Ê¹ÓÃ " + (string)ob->query("id") + " 
Õâ¸öÃû×Ö½«»á´´ÔìÒ»¸öĞÂµÄÈËÎï£¬ÄúÈ·¶¨Âğ(y/n)£¿");
        input_to("confirm_id", ob);
}

private void get_passwd(string pass, object ob)
{
        string my_pass;
        object user;

        write("\n");
        my_pass = ob->query("password");
        if( crypt(pass, my_pass) != my_pass ) {
                write("ÃÜÂë´íÎó£¡\n");
                destruct(ob);
                return;
        }

        // Check if we are already playing.
        user = find_body(ob->query("id"));
        if (user) {
                if( user->query_temp("netdead") ) {
                        reconnect(ob, user);
                        return;
                }
                
write("ÄúÒª½«ÁíÒ»¸öÁ¬ÏßÖĞµÄÏàÍ¬ÈËÎï¸Ï³öÈ¥£¬È¡¶ø´úÖ®Âğ£¿(y/n)");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if( objectp(user = make_body(ob)) ) {
                if( user->restore() ) {
                        log_file( "USAGE", sprintf("%s loggined from %s 
(%s)\n", user->query("name"),
                                query_ip_name(ob), ctime(time()) ) );
                        enter_world(ob, user);
                        return;
                } else {
                        destruct(user);
                }
        }
        write("ÇëÄúÖØĞÂ´´ÔìÕâ¸öÈËÎï¡£\n");
        confirm_id("y", ob);
}

private void confirm_relogin(string yn, object ob, object user)
{
        object old_link;

        if( yn=="" ) {
                
write("ÄúÒª½«ÁíÒ»¸öÁ¬ÏßÖĞµÄÏàÍ¬ÈËÎï¸Ï³öÈ¥£¬È¡¶ø´úÖ®Âğ£¿(y/n)");
                input_to("confirm_relogin", ob, user);
                return;
        }       

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("ºÃ°É£¬»¶Ó­ÏÂ´ÎÔÙÀ´¡£\n");
                destruct(ob);
                return;
        } else {
                tell_object(user, "ÓĞÈË´Ó±ğ´¦( " + query_ip_name(ob)
                        + " )Á¬ÏßÈ¡´úÄãËù¿ØÖÆµÄÈËÎï¡£\n");
                log_file( "USAGE", sprintf("%s replaced by %s (%s)\n", 
user->query("name"),
                        query_ip_name(ob), ctime(time()) ) );
        }

        // Kick out tho old player.
        old_link = user->query_temp("link_ob");
        if( old_link ) {
                exec(old_link, user);
                destruct(old_link);
        }

        reconnect(ob, user);    
}

private void confirm_id(string yn, object ob)
{
        if( yn=="" ) {
                write("Ê¹ÓÃÕâ¸öÃû×Ö½«»á´´ÔìÒ»¸öĞÂµÄÈËÎï£¬ÄúÈ·¶¨Âğ(y/n)£¿");
                input_to("confirm_id", ob);
                return;
        }       

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("ºÃ°É£¬ÄÇ÷áÇëÖØĞÂÊäÈëÄúµÄÓ¢ÎÄÃû×Ö£º");
                input_to("get_id", ob);
                return;
        }

        write( @TEXT
[35m
ÇëÄúÏëÒ»¸öÓĞÆøÖÊ£¬ÓĞ¸öĞÔ£¬ÓÖ²»»áÌ«Ææ¹ÖµÄÖĞÎÄÃû×Ö£¬ÌØ±ğÒªÌáĞÑÄú
µÄÊÇ£¬·çÔÆÊÇÒ»¸öÒÔ¹ÅÖĞ¹úÓë¶«·½Îª±³¾°µÄÊÀ½ç£¬Çë²»ÒªÈ¡Ò»Ğ©²»
ÑÅ»òÊÇÈİÒ×Ôì³ÉËûÈËÀ§ÈÅµÄÃû×Ö£¬Õâ¸öÃû×Ö½«´ú±íÄãµÄÈËÎï£¬¶øÇÒÍùáá
½«²»ÄÜÔÙ¸ü¸Ä£¬ÇëÎñ±ØÉ÷ÖØ¡£
[37m
[31m
Èç¹ûÄãÓĞÀ§ÄÑÊäÈëÖĞÎÄÃû×Ö£¬ÇëÖ±½ÓÇÃ»Ø³µ¼ü£Û£Ò£Å£Ô£Õ£Ò£Î£İ¡£
[37m
TEXT
        );
        write("ÄúµÄÖĞÎÄÃû×Ö£º");
        input_to("get_name", ob);
}
private void read_msg(string arg, object ob)
{
        return;
}
private void get_resp(string arg, object ob)
{
        if( arg=="" ) {
                write("ÄúÂúÒâ(y)²»ÂúÒâ(n)Õâ¸öÖĞÎÄÃû×Ö£¿");
                input_to("get_resp", ob);
                return;
        }

        if( arg[0]=='y' || arg[0]=='Y' )
	{
        printf("%O\n", ob);
        ob->set("name", Rname);
        write("ÇëÉè¶¨ÄúµÄÃÜÂë£º");
        input_to("new_password", 1, ob);
	return;
	}
        else 
	if( arg[0]=='n' || arg[0]=='N')
	{
	Rname = random_name();
        write("ÄúÂúÒâ(y)²»ÂúÒâ(n)Õâ¸öÖĞÎÄÃû×Ö£¿");
        printf( HIY" -- %s £º"NOR, Rname);
        input_to("get_resp", ob);
	return;
	}
        else {
                write("¶Ô²»Æğ£¬ÄúÖ»ÄÜÑ¡ÔñÂúÒâ(y)²»ÂúÒâ(n)£º ");
                input_to("get_resp", ob);
                return;
        }


}

private void get_name(string arg, object ob)
{
	string name;
        if( arg =="")
        {
	Rname = random_name();
        write("¿´À´ÄúÒª¸öËæ»ú²úÉúµÄÖĞÎÄÃû×Ö£®£®\n");
        write("ÄúÂúÒâ(y)²»ÂúÒâ(n)Õâ¸öÖĞÎÄÃû×Ö£¿");
        printf( HIY" -- %s £º"NOR, Rname);
        input_to("get_resp", ob);
	}
	else {
        if( !check_legal_name(arg) ) {
                write("ÄúµÄÖĞÎÄÃû×Ö£º");
                input_to("get_name", ob);
                return;
        }

        printf("%O\n", ob);
        ob->set("name", arg);
        write("ÇëÉè¶¨ÄúµÄÃÜÂë£º");
        input_to("new_password", 1, ob);
		}
}

private void new_password(string pass, object ob)
{
        write("\n");
        if( strlen(pass)<5 ) {
                write("ÃÜÂëµÄ³¤¶ÈÖÁÉÙÒªÎå¸ö×ÖÔª£¬ÇëÖØÉèÄúµÄÃÜÂë£º");
                input_to("new_password", 1, ob);
                return;
        }
        ob->set("password", crypt(pass,0) );
        write("ÇëÔÙÊäÈëÒ»´ÎÄúµÄÃÜÂë£¬ÒÔÈ·ÈÏÄúÃ»¼Ç´í£º");
        input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
        string old_pass;
        write("\n");
        old_pass = ob->query("password");
        if( crypt(pass, old_pass)!=old_pass ) {
                write("ÄúÁ½´ÎÊäÈëµÄÃÜÂë²¢²»Ò»Ñù£¬ÇëÖØĞÂÉè¶¨Ò»´ÎÃÜÂë£º");
                input_to("new_password", 1, ob);
                return;
        }

        write("ÄúµÄµç×ÓÓÊ¼şµØÖ·£º");
        input_to("get_email",  ob);
}

private void get_email(string email, object ob)
{
        object user;

        ob->set("email", email);

  // If you want do race stuff, ask player to choose one here, then you can
  // set the user's body after the question is answered. The following are
        // options for player's body, so we clone a body here.
        ob->set("body", USER_OB);
        if( !objectp(user = make_body(ob)) )
                return;

        write("ÄúÒª°çÑİÄĞĞÔ(m)µÄ½ÇÉ«»òÅ®ĞÔ(f)µÄ½ÇÉ«£¿");
        input_to("get_gender", ob, user);
}

private void get_gender(string gender, object ob, object user)
{
        if( gender=="" ) {
                write("ÄúÒª°çÑİÄĞĞÔ(m)µÄ½ÇÉ«»òÅ®ĞÔ(f)µÄ½ÇÉ«£¿");
                input_to("get_gender", ob, user);
                return;
        }

        if( gender[0]=='m' || gender[0]=='M' )
                user->set("gender", "ÄĞĞÔ");
        else if( gender[0]=='f' || gender[0]=='F' )
                user->set("gender", "Å®ĞÔ" );
        else {
                write("¶Ô²»Æğ£¬ÄúÖ»ÄÜÑ¡ÔñÄĞĞÔ(m)»òÅ®ĞÔ(f)µÄ½ÇÉ«£º");
                input_to("get_gender", ob, user);
                return;
        }
	STRv = 10 + random(21);
        CPSv = 10 + random(21);
        INTv = 10 + random(21);
        CORv = 10 + random(21);
        CONv = 10 + random(21);
        SPIv = 10 + random(21);
        PERv = 10 + random(21);
        KARv = 10 + random(21);
        write(sprintf(RED "\n
      ëöÁ¦£º[%d]  µ¨Ê¶£º[%d]  ÎòĞÔ£º[%d]  ÁéĞÔ£º[%d]\n
      ¶¨Á¦£º[%d]  ÈİÃ²£º[%d]  ¸ù¹Ç£º[%d]  ¸£Ôµ£º[%d]\n\n"NOR,
        STRv,CORv,INTv,SPIv,CPSv,PERv,CONv,KARv));
       write("ÄúÂúÒâ(y)²»ÂúÒâ(n)ÕâÌ×Ìì¸³£¿");
	input_to("get_nresp",ob, user);
}
private void get_nresp(string arg, object ob, object user)
{
        if( arg=="" ) {
                write("ÄúÂúÒâ(y)²»ÂúÒâ(n)ÕâÌ×Ìì¸³£¿");
                input_to("get_nresp", ob, user);
                return;
        }
        if( arg[0]=='y' || arg[0]=='Y' )
        {
        log_file( "USAGE", sprintf("%s was created from %s (%s)\n", 
user->query("id"),
                query_ip_name(ob), ctime(time()) ) );
        init_new_player(user);
        enter_world(ob, user);
	return;
	}
	else
        if( arg[0]=='n' || arg[0]=='N')
        {
        STRv = 10 + random(21);
        CPSv = 10 + random(21);
        INTv = 10 + random(21);
        CORv = 10 + random(21);
        CONv = 10 + random(21);
        SPIv = 10 + random(21);
        PERv = 10 + random(21);
        KARv = 10 + random(21);
        write(sprintf(RED "\n
      ëöÁ¦£º[%d]  µ¨Ê¶£º[%d]  ÎòĞÔ£º[%d]  ÁéĞÔ£º[%d]\n
      ¶¨Á¦£º[%d]  ÈİÃ²£º[%d]  ¸ù¹Ç£º[%d]  ¸£Ôµ£º[%d]\n\n"NOR,
        STRv,CORv,INTv,SPIv,CPSv,PERv,CONv,KARv));
        write("ÄúÂúÒâ(y)²»ÂúÒâ(n)ÕâÌ×Ìì¸³£¿");
        input_to("get_nresp", ob,user);
        return;
        }
        else {
                write("¶Ô²»Æğ£¬ÄúÖ»ÄÜÑ¡ÔñÂúÒâ(y)²»ÂúÒâ(n)£º ");
                input_to("get_nresp", ob,user);
                return;
        }

}

object make_body(object ob)
{
        string err;
        object user;
        int n;

        user = new(ob->query("body"));
        if(!user) {
                
write("ÏÖÔÚ¿ÉÄÜÓĞÈËÕıÔÚĞŞ¸ÄÊ¹ÓÃÕßÎï¼şµÄ³ÌÊ½£¬ÎŞ·¨½øĞĞ¸´ÖÆ¡£\n");
                write(err+"\n");
                return 0;
        }
        seteuid(ob->query("id"));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        user->set("id", ob->query("id"));
        user->set_name( ob->query("name"), ({ ob->query("id")}) );
        return user;
}

private init_new_player(object user)
{
	object money;
        user->set("title", "ÆÕÍ¨°ÙĞÕ");
        user->set("birthday", time() );
        user->set("potential", 99);

        user->set("str", STRv);
        user->set("cps", CPSv);
        user->set("int", INTv);
        user->set("cor", CORv);
        user->set("con", CONv);
        user->set("spi", SPIv);
        user->set("per", PERv);
        user->set("kar", KARv);

	user->setup();
        user->set("food", user->max_food_capacity());
        user->set("water", user->max_water_capacity());
	user->set("env/wimpy", 50);
        money = new("/obj/money/silver");
        money->move(user);

        user->set("channels", ({ "chat" }) );
}

varargs void enter_world(object ob, object user, int silent)
{
        object cloth, room;
        string startroom;

        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        exec(user, ob);

        write("Ä¿Ç°È¨ÏŞ£º" + wizhood(user) + "\n");
        user->setup();

        // In case of new player, we save them here right aftre setup 
        // compeleted.
        user->save();
        ob->save();

        cloth = new("/obj/cloth");
        cloth->move(user);
        cloth->wear();
        if( !silent ) {
                cat(MOTD);
	        write("ÇëÇÃ»Ø³µ¼ü£Û£Ò£Å£Ô£Õ£Ò£Î£İ£®£®£®£®£®");
	        input_to( "read_msg", user );
                if( ob->query("new_mail") ) {
                        write( GRN + 
"\n¶Å¿í¸æËßÄã£ºÓĞÄúµÄĞÅ£¡Çëµ½æäÕ¾À´Ò»ÌË...\n\n" + NOR);
                        ob->set("new_mail", 0);
                }
                if( user->is_ghost() )
                        startroom = DEATH_ROOM;
                else if( !stringp(startroom = user->query("startroom")) )
                        startroom = start_loc[random(sizeof(start_loc))];

                if( !catch(load_object(startroom)) )
		{
                        user->move(startroom);
			user->set("startroom", startroom);
		}
                else {
                        user->move(START_ROOM);
                        startroom = START_ROOM;
                        user->set("startroom", START_ROOM);
                }
                tell_room(startroom, user->query("name") + 
"Á¬Ïß½øÈëÕâ¸öÊÀ½ç¡£\n",
                        ({user}));
        }
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s ( %s ) ÓÉ%sÁ¬Ïß½øÈë¡£", user->name(), 
user->query("id"),query_ip_name(user)) );
        UPDATE_D->check_user(user);
}

varargs void reconnect(object ob, object user, int silent)
{
        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        exec(user, ob);

        user->reconnect();
        if( !silent ) {
                tell_room(environment(user), user->query("name") + 
"ÖØĞÂÁ¬Ïß»Øµ½Õâ¸öÊÀ½ç¡£\n",
                ({user}));
        }
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%sÓÉ%sÖØĞÂÁ¬Ïß½øÈë¡£", user->query("name"), 
query_ip_name(user)) );
        UPDATE_D->check_user(user);
}

int check_legal_id(string id)
{
        int i;

        i = strlen(id);
        
        if( (strlen(id) < 3) || (strlen(id) > 12 ) ) {
                write("¶Ô²»Æğ£¬ÄãµÄÓ¢ÎÄÃû×Ö±ØĞëÊÇ 3 µ½ 12 ¸öÓ¢ÎÄ×ÖÄ¸¡£\n");
                return 0;
        }
        while(i--)
                if( id[i]<'a' || id[i]>'z' ) {
                        write("¶Ô²»Æğ£¬ÄãµÄÓ¢ÎÄÃû×ÖÖ»ÄÜÓÃÓ¢ÎÄ×ÖÄ¸¡£\n");
                        return 0;
                }

        return 1;
}
string random_name()
{
	string *lname = ({
"ÕÔ","Ç®","Ëï","Àî","ÖÜ","Îâ","Ö£","Íõ","·ë","³Â","ñÒ","ÎÀ","½¯","Éò","º«","Ñî","Öì","ÇØ","ÓÈ","Ğí","ºÎ","ÂÀ","Ê©","ÕÅ",
"¿×","²Ü","ÑÏ","»ª","½ğ","Îº","ÌÕ","½ª","Æİ","Ğ»","×Ş","Ó÷","°Ø","Ë®","ñ¼","ÕÂ","ÔÆ","ËÕ","ÅË","¸ğ","ŞÉ","·¶","Åí","ÀÉ",
"Â³","Î¤","²ı","Âí","Ãç","·ï","»¨","·½","Óá","ÈÎ","Ô¬","Áø","µË","±«","Ê·","ÌÆ","·Ñ","Á®","á¯","Ñ¦","À×","ºØ","Äß","ÌÀ",
"ÌÙ","Òó","ÂŞ","»ª","ºÂ","Úù","°²","³£","ÀÖ","ÓÚ","Ê±","¸¶","Æ¤","±å","Æë","¿µ","Îé","Óà","Ôª","²·","¹Ë","Ó¯","Æ½","»Æ",
"ºÍ","ÄÂ","Ğ¤","Òü","Ò¦","ÉÛ","Õ¿","Íô","Æî","Ã«","Óí","µÒ","Ã×","±´","Ã÷","²Ø","¼Æ","·ü","³É","´÷","Ì¸","ËÎ","Ã©","ÅÓ",
"ĞÜ","¼Í","Êæ","Çü","Ïî","×£","¶­","Áº","·®","ºú","Áè","»ô","Óİ","Íò","Ö§","¿Â","êÃ","¹Ü","Â¬","Ó¢","Íò","ºò","Ë¾Âí",
"ÉÏ¹Ù","Å·Ñô","ÏÄºò","Öî¸ğ","ÎÅÈË","¶«·½","ºÕÁ¬","»Ê¸¦","Î¾³Ù","¹«Ñò","å£Ì¨","¹«ÖÎ",
"×ÚÕş","å§Ñô","´¾ÓÚ","µ¥ÓÚ","Ì«Êå","ÉêÍÀ","¹«Ëï","ÖÙËï","Ô¯Ğù","Áîºü","ÖÓÀë","ÓîÎÄ",
"³¤Ëï","Ä»Èİ","Ë¾Í½","Ê¦¿Õ","ò§¿×","¶ËÄ¾","Î×Âí","¹«Î÷","Æáµñ","ÀÖÕı","ÈÀæá","¹«Á¼",
"ÍØÖº","¼Ğ¹È","Ô×¸¸","¹ÈÁº","³ş½ú","ÑÖ·¨","ÈêÛ³","Í¿ÇÕ","¶ÎÇ§","°ÙÀï","¶«¹ù","ÄÏ¹ù",
"ºôÑÓ","¹éº£","ÑòÉà","Î¢Éú","ÔÀ","Ë§","çÃ","¿º","¿ö","ºó","ÓĞ","ÇÙ","ÁºÇğ","×óÇğ","¶«ÃÅ","Î÷ÃÅ",
			});
			 return (lname[random(200)] + chinese_number(random(20)));
}
int check_legal_name(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
                write("¶Ô²»Æğ£¬ÄãµÄÖĞÎÄÃû×Ö±ØĞëÊÇÒ»µ½Áù¸öÖĞÎÄ×Ö¡£\n");
                return 0;
        }
        while(i--) {
                if( name[i]<=' ' ) {
                        write("¶Ô²»Æğ£¬ÄãµÄÖĞÎÄÃû×Ö²»ÄÜÓÃ¿ØÖÆ×ÖÔª¡£\n");
                        return 0;
                }
                if( i%2==0 && !is_chinese(name[i..<0]) ) {
                        write("¶Ô²»Æğ£¬ÇëÄúÓÃ¡¸ÖĞÎÄ¡¹È¡Ãû×Ö¡£\n");
                        return 0;
                }
        }
        if( member_array(name, banned_name)!=-1 ) {
                write("¶Ô²»Æğ£¬ÕâÖÖÃû×Ö»áÔì³ÉÆäËûÈËµÄÀ§ÈÅ¡£\n");
                return 0;
        }

        return 1;
}

object find_body(string name)
{
        object ob, *body;

        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for(int i=0; i<sizeof(body); i++)
                if( clonep(body[i])
                &&      getuid(body[i]) == name ) return body[i];

        return 0;
}

int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) <= level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
}
 
