#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "daemon.h"
#include "player_op.h"
#include "add_stats.h"
#include "io.h"
#include "file_op.h" 

bool daemon_comm(hashtable **ht, vector **vec, team **t) {
    printf("DAEMON_READY\n");
    fflush(stdout);

    char *buffer = get_line();
    if (!buffer) return false;

    do {
        char *cmd = strtok(buffer, "|");
        if (cmd == NULL) {
            // Empty command
        }
        else if (strcmp(cmd, "ADD_PLAYER") == 0) {
            char *name = strtok(NULL, "|"); 
            if (name) {
                add_player(ht, vec, name); 
                save_to_sql(*vec); 
                printf("OK\n");
            } else {
                printf("ERROR: Missing name\n");
            }
        } 
        else if (strcmp(cmd, "REMOVE") == 0) {
            char *name = strtok(NULL, "|");
            if (name) {
                bool ok = remove_player_pipe(ht, vec, *t, name);
                if(!ok) break;
                save_to_sql(*vec);
                printf("OK\n");
            } else {
                printf("ERROR: Missing name\n");
            }
        }
        else if (strcmp(cmd, "STATS") == 0) {
            char *name = strtok(NULL, "|");
            char *stat_code = strtok(NULL, "|");
            char *val_str = strtok(NULL, "|");
            
            if (name && stat_code && val_str) {
                bool ok = add_pipe(*ht, *vec, *t, atoi(stat_code), name, atoi(val_str));
                if(!ok) break;
                save_to_sql(*vec);
                printf("OK\n");
            } else {
                printf("ERROR: Missing stats arguments\n");
            }
        }
        else if (strcmp(cmd, "LOAD") == 0) {
            char *type_str = strtok(NULL, "|"); //  "1", "2" ή "3"
            char *filename = strtok(NULL, "|"); //  "../tests/nba.json"
            
            if (type_str && filename) {
                int type = atoi(type_str);
                bool success = false;
                char message[256] = "";

                if (type == 1) success = pipe_txt(ht, vec, t, message, filename);
                else if (type == 2) success = pipe_json(ht, vec, t, message, filename);
                else if (type == 3) success = pipe_csv(ht, vec, t, message, filename);
                
                if (success) {
                    printf("OK\n");
                } else {
                    printf("ERROR: %s\n", message);
                }
            } else {
                printf("ERROR: Missing LOAD arguments\n");
            }
        }
        else if (strcmp(cmd, "EXIT") == 0) {
            free(buffer);
            printf("BYE\n");
            fflush(stdout);
            return true;
        }

        fflush(stdout);
        free(buffer);
        buffer = NULL;
        buffer = get_line();
        
    } while (buffer != NULL);

    return true;
}