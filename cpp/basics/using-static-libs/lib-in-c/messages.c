#include <stdio.h>
#include "messages.h"

void
_print_no_record (void)
{
    printf("[*] <no record>\n");
}

void
_print_message (const char *msg, const char *arg)
{
    printf(msg, arg);
}

// Note this is the only function that is exposed in the include file messages.h
void
core_print (MessagesRecord *msg_rec, MessagesMode mode)
{
    if (msg_rec == NULL) {
        _print_no_record();
        return;
    }

    if (mode == MESSAGES_MODE_VERBOSE) {
        _print_message("[*] (VERBOSE MODE) Message: %s\n", msg_rec->message);
    }
    else {
        _print_message("[*] (CONCISE MODE) Message: %s\n", msg_rec->message);
    }
}

// Functions are accessible from outside even if 
// no public declaration is specified in the include file.
void _hidden_in_c(void) {
    printf("[*] Ey! I'm a not publicly declared in the include file of this C lib.\n");
}
