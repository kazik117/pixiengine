#ifndef _error_h_9cd3e51ee3fe4da5a2c52d3da60f48f2_
#define _error_h_9cd3e51ee3fe4da5a2c52d3da60f48f2_

typedef enum {
    E_OK = 0,
    E_BADPTR, /* Invalid pointer */
    E_INIT, /* Init failure */
    E_WINCREAT, /* Window creation failure */
} sr_error_t;

#endif