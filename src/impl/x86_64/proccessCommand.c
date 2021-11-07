#include "proccessCommand.h"

char equality_check(char* one, char* two) {
    int sofarsogood = 0;
    int lenone = 0;
    int lentwo = 0;

    for (int a = 0; one[a] != '\0'; a++) {
        lenone += 1;
    }

    for (int a = 0; two[a] != '\0'; a++) {
        lentwo += 1;
    }

    if (lenone != lentwo) {
        return 0;
    }

    for (int i = 0; 1; i++) {

        if (one[i] == '\0')
        {
            break;
        }
        
        if (one[i] == two[i]) {
            sofarsogood = 1;
        } else {
            sofarsogood = 0;
            break;
        }
    }
    
    return sofarsogood;
}