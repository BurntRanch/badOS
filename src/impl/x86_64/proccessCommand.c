#include "proccessCommand.h"

char* process(char* command) {
    if (command == "clr") {
        return "CLEAR_SCREEN";
    }
    return "unknown";
}