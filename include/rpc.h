// Google BSD license http://code.google.com/google_bsd_license.html
// Copyright 2012 Google Inc. wrightt@google.com

//
// iOS WebInspector
//

#ifndef RPC_H
#define	RPC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>


typedef uint8_t rpc_status;
#define RPC_ERROR 1
#define RPC_SUCCESS 0

// Create a UUID, e.g. "4B2550E4-13D6-4902-A48E-B45D5B23215B".
rpc_status rpc_new_uuid(char **to_uuid);

struct rpc_app_struct {
  char *app_id;
  char *app_name;
  bool is_proxy;
};
typedef struct rpc_app_struct *rpc_app_t;

struct rpc_page_struct {
  uint32_t page_id;
  char *connection_id;
  char *title;
  char *url;
};
typedef struct rpc_page_struct *rpc_page_t;

struct rpc_struct;
typedef struct rpc_struct *rpc_t;
rpc_t rpc_new(bool is_sim);
void rpc_free(rpc_t self);

// iOS WebInspector.
struct rpc_struct {

    //
    // Use these APIs:
    //

    rpc_status (*on_recv)(rpc_t self, const char *buf, ssize_t length);

    rpc_status (*send_reportIdentifier)(rpc_t self,
            const char *connection_id);

    rpc_status (*send_getConnectedApplications)(rpc_t self,
            const char *connection_id);

    rpc_status (*send_forwardGetListing)(rpc_t self,
            const char *connection_id, const char *app_id);

    rpc_status (*send_forwardIndicateWebView)(rpc_t self,
            const char *connection_id, const char *app_id,
            uint32_t page_id, bool is_enabled);

    rpc_status (*send_forwardSocketSetup)(rpc_t self,
            const char *connection_id, const char *app_id,
            uint32_t page_id, const char *sender_id);

    rpc_status (*send_forwardSocketData)(rpc_t self,
            const char *connection_id, const char *app_id,
            uint32_t page_id, const char *sender_id,
            const char *data, size_t length);

    rpc_status (*send_forwardDidClose)(rpc_t self,
            const char *connection_id, const char *app_id,
            uint32_t page_id, const char *sender_id);

    void *state;

    //
    // Set these callbacks:
    //

    rpc_status (*send_packet)(rpc_t self, const char *packet, size_t length);

    rpc_status (*on_reportSetup)(rpc_t self);

    rpc_status (*on_reportConnectedApplicationList)(rpc_t self,
            const rpc_app_t *apps);

    rpc_status (*on_applicationConnected)(rpc_t self,
            const rpc_app_t app);

    rpc_status (*on_applicationDisconnected)(rpc_t self,
            const rpc_app_t app);

    rpc_status (*on_applicationSentListing)(rpc_t self,
            const char *app_id, const rpc_page_t *pages);

    rpc_status (*on_applicationSentData)(rpc_t self,
            const char *app_id, const char *dest_id,
            const char *data, size_t length);

    // For internal use only:
    rpc_status (*on_error)(rpc_t self, const char *format, ...);
};


#ifdef	__cplusplus
}
#endif

#endif	/* RPC_H */
