#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <locale.h>
#include <time.h>


int main(int argc, char** argv){
  char puffer[255], command[59], dateiname[128],
    *create, *insert;
  time_t jetzt;
  struct tm* lokaljetzt;
  sqlite3* db;
  sqlite3_stmt* stmt;
  const char* tail;
  
  setlocale(LC_ALL, "");
  time(&jetzt);
  lokaljetzt = localtime(&jetzt);

  sqlite3_open("dateien.db", &db);

  create = "CREATE TABLE IF NOT EXISTS angebot(id INTEGER PRIMARY KEY, "
    "dateiname TEXT, zeit NOT NULL DEFAULT CURRENT_TIMESTAMP, lokalzeit DATE DEFAULT(DATETIME('NOW', 'LOCALTIME')));";

  sqlite3_exec(db, create, NULL, NULL, NULL);

  strncpy(dateiname, argv[1], 64);
  strncat(dateiname, "_", 65);
  
  strftime(puffer, 255, "%d-%m-%Y_%H:%M:%S", lokaljetzt);

  strncat(dateiname, puffer, 64);
  strncat(dateiname, ".txt", 64);

  insert = "INSERT INTO angebot (dateiname) VALUES(?);";

  sqlite3_prepare(db, insert, strlen(insert), &stmt, &tail);

  sqlite3_bind_text(stmt, 1, dateiname, strlen(dateiname), 0);

  sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  sqlite3_exec(db, insert, NULL, NULL, NULL);

  sqlite3_close(db);
  
  printf("Länge des Dateinamens: %d.\n", (int)strlen(dateiname));
  
  snprintf(command, 255, "xclip -o > %s", dateiname);

  system(command);
  
  printf("\nDatei %s ist soeben geschrieben und in dateien.db registriert worden.\n", dateiname);
}
