#ifndef MESSAGES_H
#define MESSAGES_H

#ifdef __cplusplus
extern "C" {
#endif

// #include <glib.h>
// #include <sys/types.h>

typedef enum { /*< skip >*/
    MESSAGES_MODE_CONCISE,
    MESSAGES_MODE_VERBOSE
} MessagesMode;

typedef struct _MessagesRecord        MessagesRecord;

struct _MessagesRecord {
	char   *message;
};

void        core_print                (MessagesRecord    *msg_rec, MessagesMode mode);

#ifdef __cplusplus
}
#endif

#endif /* MESSAGES_H */
