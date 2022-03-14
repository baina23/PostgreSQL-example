#include <iostream>
#include <pqxx/pqxx>
#include <unistd.h>

#include "exerciser.h"

using namespace std;
using namespace pqxx;
#define PATH_SIZE 255

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;
  char p[PATH_SIZE];
  if(!getcwd(p,PATH_SIZE)){
    cout << "Get path fail!" << endl;
    return 0;
  }
  string path(p);

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      //cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
 
      string sql00, sql01, sql02, sql03;
      string sql10, sql11, sql12, sql13;
      string sql20, sql21, sql22, sql23;
      string sql30, sql31, sql32, sql33;
      
      sql00 = "DROP TABLE IF EXISTS PLAYER CASCADE;";
      sql01 = "CREATE TABLE PLAYER("  \
      "PLAYER_ID SERIAL PRIMARY KEY     NOT NULL," \
      "TEAM_ID        INT      NOT NULL," \
      "UNIFORM_NUM        INT      NOT NULL," \
      "FIRST_NAME           TEXT    NOT NULL," \
      "LAST_NAME           TEXT    NOT NULL," \
      "MPG            INT     NOT NULL," \
      "PPG            INT     NOT NULL," \
      "RPG            INT     NOT NULL," \
      "APG            INT     NOT NULL," \
      "SPG            FLOAT     NOT NULL," \
      "BPG            FLOAT     NOT NULL);";
      sql02 = "COPY PLAYER FROM '" + path + "/player.txt" + "' CSV DELIMITER E' ';"; 
      sql03 = "SELECT setval('PLAYER_PLAYER_ID_SEQ', (SELECT MAX(PLAYER_ID) FROM PLAYER));";

      sql10 = "DROP TABLE IF EXISTS TEAM CASCADE;";
      sql11 = "CREATE TABLE TEAM("  \
      "TEAM_ID    SERIAL  PRIMARY KEY    NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "STATE_ID            INT     NOT NULL," \
      "COLOR_ID            INT     NOT NULL," \
      "WINS            INT     NOT NULL," \
      "LOSSES            INT     NOT NULL);";
      sql12 = "COPY TEAM FROM '" + path + "/team.txt" + "' CSV DELIMITER E' ';"; 
      sql13 = "SELECT setval('TEAM_TEAM_ID_SEQ', (SELECT MAX(TEAM_ID) FROM TEAM));";

      sql20 = "DROP TABLE IF EXISTS STATE CASCADE;";
      sql21 = "CREATE TABLE STATE("  \
      "STATE_ID SERIAL PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL);"; 
      sql22 = "COPY STATE FROM '" + path + "/state.txt" + "' CSV DELIMITER E' ';"; 
      sql23 = "SELECT setval('STATE_STATE_ID_SEQ', (SELECT MAX(STATE_ID) FROM STATE));";

      sql30 = "DROP TABLE IF EXISTS COLOR CASCADE;";
      sql31 = "CREATE TABLE COLOR("  \
      "COLOR_ID SERIAL PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL);";
      sql32 = "COPY COLOR FROM '" + path + "/color.txt" + "' CSV DELIMITER E' ';"; 
      sql33 = "SELECT setval('COLOR_COLOR_ID_SEQ', (SELECT MAX(COLOR_ID) FROM COLOR));";

      /* Create a transactional object. */
      work W(*C);
      
      //W.exec( sql );
      /* Execute SQL query */
      W.exec( sql00 );
      W.exec( sql01 );
      W.exec( sql02 );
      W.exec( sql03 );
      //cout << "Table PLAYER created successfully" << endl;
      W.exec( sql10 );
      W.exec( sql11 );
      W.exec( sql12 );
      W.exec( sql13 );
      //cout << "Table TEAM created successfully" << endl;
      W.exec( sql20 );
      W.exec( sql21 );
      W.exec( sql22 );
      W.exec( sql23 );
      //cout << "Table STATE created successfully" << endl;
      W.exec( sql30 );
      W.exec( sql31 );
      W.exec( sql32 );
      W.exec( sql33 );
      //cout << "Table COLOR created successfully" << endl;
      W.commit();

  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}


