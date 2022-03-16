#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
     string sql;
     string team_id_str = to_string(team_id);
     string jersey_num_str = to_string(jersey_num);
     string mpg_str = to_string(mpg);
     string ppg_str = to_string(ppg);
     string rpg_str = to_string(rpg);
     string apg_str = to_string(apg);
     string spg_str = to_string(spg);
     string bpg_str = to_string(bpg);
     sql = "INSERT INTO PLAYER (PLAYER_ID,TEAM_ID,UNIFORM_NUM,FIRST_NAME,LAST_NAME, MPG,PPG,RPG,APG,SPG,BPG) "  \
      "VALUES ( DEFAULT, " + team_id_str + ',' + jersey_num_str + ", '" + first_name + "', '" + last_name + "', " + mpg_str +
        ',' + ppg_str + ',' + rpg_str + ',' + apg_str + ',' + spg_str + ',' + bpg_str + "); " ;
      work W(*C);
      W.exec( sql );
      W.commit();
    return;
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
    string sql;
    string state_id_str = to_string(state_id);
    string color_id_str = to_string(color_id);
    string wins_str = to_string(wins);
    string losses_str = to_string(losses);
    
    sql = "INSERT INTO TEAM (TEAM_ID, NAME, STATE_ID, COLOR_ID, WINS, LOSSES) "  \
    "VALUES ( DEFAULT, '"  + name + "'," + state_id_str + ',' + color_id_str + ',' + wins_str + ',' + losses_str + "); " ;
    work W(*C);
    W.exec( sql );
    W.commit(); 
    return;
}


void add_state(connection *C, string name)
{
    string sql;
    sql = "INSERT INTO STATE (STATE_ID, NAME) "  \
    "VALUES ( DEFAULT, '" + name + "'); " ;
    work W(*C);
    W.exec( sql );
    W.commit();
    return;
}


void add_color(connection *C, string name)
{
    string sql;
    sql = "INSERT INTO COLOR (COLOR_ID, NAME) "  \
    "VALUES ( DEFAULT, '" + name + "'); " ;
    work W(*C);
    W.exec( sql );
    W.commit();
    return;
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
    string mpg;
    bool pre = false;
    if (use_mpg){
        string min = to_string(min_mpg);
        string max = to_string(max_mpg);
        mpg = "MPG BETWEEN " + min + " AND " + max;
        pre = true;
    } 

     string ppg;
    if (use_ppg){
        if (pre) ppg = " AND ";
        else pre = true;
        string min = to_string(min_ppg);
        string max = to_string(max_ppg);
        ppg += "PPG BETWEEN " + min + " AND " + max;
    } 

     string rpg;
    if (use_rpg){
        if (pre) rpg = " AND ";
        else pre = true;
        string min = to_string(min_rpg);
        string max = to_string(max_rpg);
        rpg += "RPG BETWEEN " + min + " AND " + max;
    } 

     string apg;
    if (use_apg){
        if (pre) apg = " AND ";
        else pre = true;
        string min = to_string(min_ppg);
        string max = to_string(max_ppg);
        apg += "APG BETWEEN " + min + " AND " + max;
    } 

     string spg;
    if (use_spg){
        if (pre) spg = " AND ";
        else pre = true;
        string min = to_string(min_ppg);
        string max = to_string(max_ppg);
        spg += "SPG BETWEEN " + min + " AND " + max;
    } 

     string bpg;
    if (use_bpg){
        if (pre) bpg = " AND ";
        else pre = true;
        string min = to_string(min_ppg);
        string max = to_string(max_ppg);
        bpg += "BPG BETWEEN " + min + " AND " + max;
    } 
    

    string where = mpg + ppg + rpg + apg + spg + bpg;
    string sql;
    if(pre)
        sql = "SELECT * FROM PLAYER WHERE " + where + ';';
    else
        sql = "SELECT * FROM PLAYER";

     /* Create a non-transactional object. */
    nontransaction N(*C);
      
    /* Execute SQL query */
    result R( N.exec( sql ));
      
    /* List down all the records */
    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<int>() << ' ';
      cout << c[1].as<int>() << ' ';
      cout << c[2].as<int>() << ' ';
      cout << c[3].as<string>() << ' ';
      cout << c[4].as<string>() << ' ';
      cout << c[5].as<int>() << ' ';
      cout << c[6].as<int>() << ' ';
      cout << c[7].as<int>() << ' ';
      cout << c[8].as<int>() << ' ';
      cout << c[9].as<float>() << ' ';
      cout << c[10].as<float>() << endl;
    }
    return;
    
}


void query2(connection *C, string team_color)
{
    string sql;
    sql = "SELECT TEAM.NAME FROM TEAM, COLOR WHERE TEAM.COLOR_ID = COLOR.COLOR_ID" \
    " AND COLOR.NAME = '" + team_color + "';";
     /* Create a non-transactional object. */
    nontransaction N(*C);
      
    /* Execute SQL query */
    result R( N.exec( sql ));
    cout << "NAME" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<string>() << endl;
    }
    return;

}


void query3(connection *C, string team_name)
{
    string sql;
    sql = "SELECT FIRST_NAME, LAST_NAME FROM PLAYER, TEAM " \
    "WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.NAME = '"+ team_name + "'" +\
    "ORDER BY PLAYER.PPG DESC;";
     /* Create a non-transactional object. */
    nontransaction N(*C);
      
    /* Execute SQL query */
    result R( N.exec( sql ));
    cout << "FIRST_NAME LAST_NAME" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<string>() << ' ';
      cout << c[1].as<string>() << endl;
    }
    return;
}


void query4(connection *C, string team_state, string team_color)
{
    string sql;
    sql = "SELECT FIRST_NAME, LAST_NAME, UNIFORM_NUM FROM PLAYER, TEAM, STATE, COLOR "\
    "WHERE STATE.STATE_ID = TEAM.STATE_ID AND COLOR.COLOR_ID = TEAM.COLOR_ID AND PLAYER.TEAM_ID = TEAM.TEAM_ID "\
    "AND STATE.NAME = '"+ team_state + "'"+ " AND COLOR.NAME = '"+ team_color + "';";
     /* Create a non-transactional object. */
    nontransaction N(*C);
      
    /* Execute SQL query */
    result R( N.exec( sql ));
    cout << "UNIFORM_NUM FIRST_NAME LAST_NAME" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<string>() << ' ';
      cout << c[1].as<string>() << ' ';
      cout << c[2].as<string>() << endl;
    }
    return;
}


void query5(connection *C, int num_wins)
{
    string num_wins_str = to_string(num_wins);
    string sql = "SELECT FIRST_NAME, LAST_NAME, NAME, WINS FROM PLAYER, TEAM "\
    "WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.WINS > "+ num_wins_str + ';';

     /* Create a non-transactional object. */
    nontransaction N(*C);
      
    /* Execute SQL query */
    result R( N.exec( sql ));
    cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
      cout << c[0].as<string>() << ' ';
      cout << c[1].as<string>() << ' ';
      cout << c[2].as<string>() << ' ';
      cout << c[3].as<int>() << endl;
    }
    return;
}



