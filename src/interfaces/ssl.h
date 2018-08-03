/* Public interfaces for SSL sockets and contexts */

#ifndef LIBUS_NO_SSL

/* An options structure where set options are non-null. Used to initialize an SSL socket context */
struct us_ssl_socket_context_options {
    const char *key_file_name;
    const char *cert_file_name;
    const char *passphrase;
};

/* See us_create_socket_context. SSL variant taking SSL options structure */
struct us_ssl_socket_context *us_create_ssl_socket_context(struct us_loop *loop, int context_ext_size, struct us_ssl_socket_context_options options);

/* See us_socket_context */
void us_ssl_socket_context_on_open(struct us_ssl_socket_context *context, void (*on_open)(struct us_ssl_socket *s));
void us_ssl_socket_context_on_close(struct us_ssl_socket_context *context, void (*on_close)(struct us_ssl_socket *s));
void us_ssl_socket_context_on_data(struct us_ssl_socket_context *context, void (*on_data)(struct us_ssl_socket *s, char *data, int length));
void us_ssl_socket_context_on_writable(struct us_ssl_socket_context *context, void (*on_writable)(struct us_ssl_socket *s));
void us_ssl_socket_context_on_timeout(struct us_ssl_socket_context *context, void (*on_timeout)(struct us_ssl_socket *s));

/* Technically SSL sockets cannot be half-closed, so this callback is never called */
void us_ssl_socket_context_on_end(struct us_ssl_socket_context *context, void (*on_end)(struct us_ssl_socket *s));

/* See us_socket_context */
struct us_listen_socket *us_ssl_socket_context_listen(struct us_ssl_socket_context *context, const char *host, int port, int options, int socket_ext_size);

/* See us_socket */
int us_ssl_socket_write(struct us_ssl_socket *s, const char *data, int length, int msg_more);

/* See us_socket */
void us_ssl_socket_timeout(struct us_ssl_socket *s, unsigned int seconds);

/* */
void *us_ssl_socket_context_ext(struct us_ssl_socket_context *s);

/* */
struct us_ssl_socket_context *us_ssl_socket_get_context(struct us_ssl_socket *s);

/* Return the user data extension of this socket */
void *us_ssl_socket_ext(struct us_ssl_socket *s);

/* */
int us_ssl_socket_is_shut_down(struct us_ssl_socket *s);

/* */
void us_ssl_socket_shutdown(struct us_ssl_socket *s);

/* */
void us_ssl_socket_close(struct us_ssl_socket *s);

#endif