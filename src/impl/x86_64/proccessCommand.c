#include "proccessCommand.h"

char process(char* command) {
    int sofarsogood = 0;
    for (int i = 0; 1; i++) {

        if (command[i] == '\0' & i == 3) {
            break;
        } else if (command[i] == '\0') {
            sofarsogood = 0;
            break;
        }

        if (i == 0 & command[i] == 'c') {
            sofarsogood = 1;
        } else if (i == 1 & command[i] == 'l') {
            sofarsogood = 1;
        } else if (i == 2 & command[i] == 'r') {
            sofarsogood = 1;
        } else {
            sofarsogood = 0;
            break;
        }
    }
    if (sofarsogood) {
        return 'c';
    } else {
        return '1';
    }
}