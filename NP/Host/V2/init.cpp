#include "init.h"
#include "stdio.h"
#include <zmq.h>
#include <string.h>
#include <string>

using namespace std;

void * context;

init::init()
{
    context = zmq_ctx_new();

    void * pusher = zmq_socket( context, ZMQ_PUSH );
    void * subscriber = zmq_socket(context, ZMQ_SUB);

    zmq_connect( pusher, "tcp://192.168.0.198:24041" );
    zmq_connect( subscriber, "tcp://192.168.0.198:24042" );

    zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE,"weerwolven? >", 13);
    read(&subscriber);
}

string init::read(void * subscriber)
{
    char read[1000];
    zmq_msg_t msg;
    int rc = zmq_msg_init (&msg);                                                           //read benthernet
    rc = zmq_recvmsg (subscriber, &msg, 0);
    int size = zmq_msg_size (&msg);
    memcpy(read, zmq_msg_data(&msg), size);
    zmq_msg_close(&msg);
    read[size] = 0;
    printf("%s\n", read);
    zmq_msg_close (&msg);
    return(read);
}
