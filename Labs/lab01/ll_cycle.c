#include "ll_cycle.h"
#include <stddef.h>

int ll_has_cycle(node *head) {
    node *a = head;
    node *b = head;
    if (!a) {
        return 0;
    }
    while (1) {
        if (a->next) {
            a = a->next;
        } else {
            break;
        }
        if (a->next) {
            a = a->next;
        } else {
            break;
        }
        b = b->next;
        if (a == b) {
            return 1;
        }
    }
    return 0;
}