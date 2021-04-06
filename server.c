#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <libwebsockets.h>

static int callback_ws_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            printf("connection established.\n");
            break;
        case LWS_CALLBACK_CLOSED:
            printf("connection closed.\n");
            break;
        case LWS_CALLBACK_RECEIVE: {

            unsigned char *buf = (unsigned char*) malloc(LWS_PRE + len);
            
            int i;
            
            for (i=0; i < len; i++) {
                buf[LWS_SEND_BUFFER_PRE_PADDING + (len - 1) - i ] = ((char *) in)[i];
            }
            
            printf("received data: %.*s, replying: %.*s\n", (int)len, (char *)in, (int)len, buf + LWS_PRE);
            
            lws_write(wsi, &buf[LWS_PRE], len, LWS_WRITE_TEXT);
            
            free(buf);
            break;
        }
        default:
            break;
    }
    
    return 0;
}


struct lws_protocols protocols[] = {
    {"http", lws_callback_http_dummy, 0, 0},
    {"ws_echo", callback_ws_echo, 0, 0},
    {NULL, NULL, 0, 0}
};

int main(int argc, char **argv)
{
    const char* socket_path = "/tmp/meow.sock";

    int logs = LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE;
    lws_set_log_level(logs, NULL);

    struct lws_context_creation_info info;
    struct lws_context *context;

    memset(&info, 0, sizeof(info));
    info.options = LWS_SERVER_OPTION_UNIX_SOCK;
    info.iface = socket_path;
    info.protocols = protocols;
    
    context = lws_create_context(&info);

    while (1) 
        lws_service(context, 0);
    return 0;
}