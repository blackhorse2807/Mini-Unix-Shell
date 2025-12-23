#include "signals.h"
#include <signal.h>

void setup_signal_handlers() {
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}
