#include "query_funcs.h"

#include <fstream>

void execute_sql(connection * C, string sql) {
  work W(*C);
  W.exec(sql);
  W.commit();
}

void drop_exist_table(connection * C) {
  if (!C->is_open()) {
    throw pqxx::broken_connection();
  }

  string sql = "DROP TABLE IF EXISTS PLAYER CASCADE; \
            DROP TABLE IF EXISTS TEAM CASCADE; \
            DROP TABLE IF EXISTS STATE CASCADE; \
            DROP TABLE IF EXISTS COLOR CASCADE;";
  execute_sql(C, sql);
}

void create_color_table(connection * C) {
  if (!C->is_open()) {
    throw pqxx::broken_connection();
  }

  string sql = "\
        CREATE TABLE COLOR (\
            COLOR_ID SERIAL,\
            NAME VARCHAR(100),\
            PRIMARY KEY(COLOR_ID)\
    );";

  execute_sql(C, sql);
}

void create_state_table(connection * C) {
  if (!C->is_open()) {
    throw pqxx::broken_connection();
  }

  string sql = "\
        CREATE TABLE STATE (\
        STATE_ID SERIAL,\
        NAME VARCHAR(100),\
        PRIMARY KEY(STATE_ID));";
  execute_sql(C, sql);
}

void create_team_table(connection * C) {
  if (!C->is_open()) {
    throw pqxx::broken_connection();
  }

  string sql = "\
        CREATE TABLE TEAM (\
        TEAM_ID SERIAL,\
        NAME VARCHAR(100),\
        STATE_ID int,\
        COLOR_ID int,\
        WINS int,\
        LOSSES int,\
        PRIMARY KEY(TEAM_ID),\
        FOREIGN KEY(STATE_ID) REFERENCES STATE\
                            ON DELETE CASCADE\
                            ON UPDATE CASCADE,\
        FOREIGN KEY(COLOR_ID) REFERENCES COLOR\
                            ON DELETE CASCADE\
                            ON UPDATE CASCADE\
    );";

  execute_sql(C, sql);
}

void create_player_table(connection * C) {
  if (!C->is_open()) {
    throw pqxx::broken_connection();
  }

    string sql = "CREATE TABLE PLAYER (\
        PLAYER_ID SERIAL,\
        TEAM_ID int,\
        UNIFORM_NUM int,\
        FIRST_NAME VARCHAR(100),\
        LAST_NAME VARCHAR(100), \
        MPG float, \
        PPG float, \
        RPG float,  \
        APG float, \
        SPG float, \
        BPG float,\
        PRIMARY KEY(PLAYER_ID),\
        FOREIGN KEY(TEAM_ID) REFERENCES TEAM\
                            ON DELETE CASCADE\
                            ON UPDATE CASCADE\
    );";

    execute_sql(C, sql);
}

void load_data(connection * C) {
  load_color_data(C);
  load_state_data(C);
  load_team_data(C);
  load_player_data(C);
}

void load_color_data(connection * C) {
  fstream fs;
  fs.open("./color.txt", ios::in);

  string line;
  while (getline(fs, line)) {
    string color_name;
    int color_id;
    stringstream ss(line);
    ss >> color_id >> color_name;
    add_color(C, color_name);
  }
}

void load_state_data(connection * C) {
  fstream fs;
  fs.open("./state.txt", ios::in);

  string line;
  while (getline(fs, line))
  {
    int state_id;
    string state_name;
    stringstream ss(line);
    ss >> state_id >> state_name;
    add_state(C, state_name);
  }
}

void load_player_data(connection * C) {
  fstream fs;
  fs.open("./player.txt", ios::in);

  string line;
  while(getline(fs, line)) {
    int player_id, team_id, uniform_num, mpg, ppg, rpg, apg;
    string first_name, last_name;
    double spg, bpg;

    stringstream ss(line);
    ss >> player_id >> team_id >> uniform_num >> first_name >> last_name >> mpg \
    >> ppg >> rpg >> apg >> spg >> bpg;
    add_player(C, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
  }
}

void add_player(connection * C,
                int team_id,
                int jersey_num,
                string first_name,
                string last_name,
                int mpg,
                int ppg,
                int rpg,
                int apg,
                double spg,
                double bpg) {
  work w(*C);
  string sql = "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) VALUES (" +\
    to_string(team_id) + ", " + to_string(jersey_num) + ", " + w.quote(first_name) + ", " + w.quote(last_name) + ", " +\
    to_string(mpg) + ", " + to_string(ppg) + ", " + to_string(rpg) + ", " + to_string(apg) + ", "\
    + to_string(spg) + ", " + to_string(bpg) + ")";
  w.exec(sql);
  w.commit();
}

void add_team(connection * C,
              string name,
              int state_id,
              int color_id,
              int wins,
              int losses) {
  string sql = "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) VALUES ('" + name \
                + "', " + to_string(state_id) + 
                ", " + to_string(color_id) +
                ", " + to_string(wins) +
                ", " + to_string(losses) + ");";
  execute_sql(C, sql);

}

void add_state(connection * C, string name) {
  string sql = "INSERT INTO STATE (NAME) VALUES ('" + name + "');";
  execute_sql(C, sql);
}

void add_color(connection * C, string name) {
  string sql = "INSERT INTO COLOR (NAME) VALUES ('" + name + "');";
  execute_sql(C, sql);
}

void load_team_data(connection * C) {
    fstream fs;
    fs.open("./team.txt", ios::in);

    string line;
    while(getline(fs, line)) {
      stringstream ss(line);
      int team_id = 0, state_id = 0, color_id = 0, wins = 0, loss = 0;
      string name;

      ss >> team_id >> name >> state_id >> color_id >> wins >> loss;
      add_team(C, name, state_id, color_id, wins, loss);
    }
}

void query1(connection * C,
            int use_mpg,
            int min_mpg,
            int max_mpg,
            int use_ppg,
            int min_ppg,
            int max_ppg,
            int use_rpg,
            int min_rpg,
            int max_rpg,
            int use_apg,
            int min_apg,
            int max_apg,
            int use_spg,
            double min_spg,
            double max_spg,
            int use_bpg,
            double min_bpg,
            double max_bpg) {
}

void query2(connection * C, string team_color) {
}

void query3(connection * C, string team_name) {
}

void query4(connection * C, string team_state, string team_color) {
}

void query5(connection * C, int num_wins) {
}
