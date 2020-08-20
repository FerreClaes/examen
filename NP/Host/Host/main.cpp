#include <QList>
#include <stdio.h>
#include <stdlib.h>
#include <zmq.h>
#include <string>
#include <string.h>
#include "player.h"
#include <time.h>
#include <pthread.h>

using namespace std;
int control[5];
bool restart = false;
void delay(int seconds)
{
    // Converting time into milli_seconds
        int milli_seconds = 1000 * seconds;

        // Storing start time
        clock_t start_time = clock();

        // looping till required time is not achieved
        while (clock() < start_time + milli_seconds)
        {}
}

void * context;

void *online(void *vargp)
{
    char send[30];
    void * pusher = zmq_socket( context, ZMQ_PUSH );
    //zmq_connect( pusher, "tcp://benternet.pxl-ea-ict.be:24041" );
    zmq_connect( pusher, "tcp://192.168.0.198:24041" );

    string push = "weerwolven! >offline >";
    while (1)
    {
        delay(180);
        for(int i = 0; i < 5; i++)
        {
            if (control[i] > 0) {}
            else
            {
                push.append(to_string(i + 1));
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                restart = true;
            }
            control[i] = 0;
        }

        for(int i = 0; i < 5; i++)
        {
            control[i] = 0;
        }
    }
}



int getRole();
int mostFrequent(int arr[], int n);

QList<uint> numList;
uint num;
bool duplicate;
bool burger;

int main()
{
    context = zmq_ctx_new();

    void * pusher = zmq_socket( context, ZMQ_PUSH );
    void * subscriber = zmq_socket(context, ZMQ_SUB);

    zmq_connect( pusher, "tcp://192.168.0.198:24041" );
    zmq_connect( subscriber, "tcp://192.168.0.198:24042" );

    zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE,"weerwolven? >", 13);

    char read[1000] = "";
    zmq_msg_t msg;
    int rc;
    int size;
    bool init = false;
    char sub[20];
    char name[25];
    char command[30];
    char data[700];
    char data2[700];
    string push = "weerwolven! >";
    char send[1000];
    int i = 0;
    bool play = false;
    bool begin = true;
    int murder = 0;
    int murder2 = 0;
    int alive = 5;
    int counter = 0;
    int votes[5];
    bool weerwolf = true;
    bool heks = true;
    int koppel[2];

    player player1;
    player player2;
    player player3;
    player player4;
    player player5;
    player spectator;



    while (1)
    {
        rc = zmq_msg_init (&msg);                                                           //read benthernet
        rc = zmq_recvmsg (subscriber, &msg, 0);
        size = zmq_msg_size (&msg);
        memcpy(read, zmq_msg_data(&msg), size);
        zmq_msg_close(&msg);
        read[size] = 0;
        printf("%s\n", read);
        zmq_msg_close (&msg);

        sscanf(read, "%s > %s >%s >%s", sub, command, data, data2);

        if (strcmp(command, "init") == 0)
        {
            if (init)
            {
                spectator.name = name;
                spectator.role = 4;
                spectator.alive = true;

                push.append("init >");
                push.append("6");
                push.append(" >");
                push.append(to_string(spectator.role));
                push.append(" >");
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                i++;
                push = "weerwolven! >";
                strcpy(name, "");
            }
            else
            {
                sscanf(data, "%s", name);
                switch (i)
                {
                case 0:

                    player1.name = name;
                    player1.role = getRole();
                    player1.alive = true;

                    push.append(name);
                    push.append(" >");
                    push.append("init >");
                    push.append("1");
                    push.append(" >");
                    push.append(to_string(player1.role));
                    push.append(" >");
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    i++;
                    printf(send);printf("\n");
                    push = "weerwolven! >";
                    strcpy(name, "");
                    break;
                case 1:

                    player2.name = name;
                    player2.role = getRole();
                    player2.alive = true;
                    push.append(name);
                    push.append(" >");
                    push.append("init >");
                    push.append("2");
                    push.append(" >");
                    push.append(to_string(player2.role));
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    i++;
                    printf(send);printf("\n");
                    strcpy(name, "");
                    push = "weerwolven! >";
                    break;
                case 2:

                    player3.name = name;
                    player3.role = getRole();
                    player3.alive = true;
                    push.append(name);
                    push.append(" >");
                    push.append("init >");
                    push.append("3");
                    push.append(" >");
                    push.append(to_string(player3.role));
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    i++;
                    printf(send);printf("\n");
                    push = "weerwolven! >";
                    strcpy(name, "");
                    break;
                case 3:

                    player4.name = name;
                    player4.role = getRole();
                    player4.alive = true;
                    push.append(name);
                    push.append(" >");
                    push.append("init >");
                    push.append("4");
                    push.append(" >");
                    push.append(to_string(player4.role));
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    i++;
                    printf(send);printf("\n");
                    push = "weerwolven! >";
                    strcpy(name, "");
                    break;
                case 4:

                    player5.name = name;
                    player5.role = getRole();
                    player5.alive = true;
                    push.append(name);
                    push.append(" >");
                    push.append("init >");
                    push.append("5");
                    push.append(" >");
                    push.append(to_string(player5.role));
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    push = "weerwolven! >";
                    printf(send);printf("\n");
                    strcpy(name, "");

                    play = true;
                    init = true;
                    break;
                }
            }
        }

        if (init)
        {
            if (init && begin)
            {
                push = "weerwolven! >cupido";
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >";
                begin = false;
                pthread_t tid;
                pthread_create(&tid, NULL, online, NULL);
            }

            if (strcmp(command, "koppel") == 0)
            {
                koppel[0] = stoi(data);
                koppel[1] = stoi(data2);
                push.append("koppel >");
                push.append(data);
                push.append(" >");
                push.append(data2);
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >weerwolf";
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >";
            }

            if (strcmp(command, "murderdByWeerwolf") == 0)
            {
                murder = stoi(data);
                printf("%d\n", murder);
                if (heks)
                {
                    push.append("heks >");
                    push.append(data);
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    push = "weerwolven! >";
                }
                else
                {
                    push = "weerwolven! >wakker >";
                    push.append(to_string(murder));
                    push.append(" >");
                    switch (murder)
                    {
                    case 1:
                        push.append(to_string(player1.role));
                        player1.alive = false;
                        switch (player1.role)
                        {
                        case 0:
                            break;
                        case 1:
                            weerwolf = false;
                            break;
                        case 2:
                            heks = false;
                            break;
                        case 3:
                            break;
                        }
                        break;
                    case 2:
                        push.append(to_string(player2.role));
                        player2.alive = false;
                        switch (player2.role)
                        {
                        case 0:
                            break;
                        case 1:
                            weerwolf = false;
                            break;
                        case 2:
                            heks = false;
                            break;
                        case 3:
                            break;
                        }
                        break;
                    case 3:
                        push.append(to_string(player3.role));
                        player3.alive = false;
                        switch (player3.role)
                        {
                        case 0:
                            break;
                        case 1:
                            weerwolf = false;
                            break;
                        case 2:
                            heks = false;
                            break;
                        case 3:
                            break;
                        }
                        break;
                    case 4:
                        push.append(to_string(player4.role));
                        player4.alive = false;
                        switch (player4.role)
                        {
                        case 0:
                            break;
                        case 1:
                            weerwolf = false;
                            break;
                        case 2:
                            heks = false;
                            break;
                        case 3:
                            break;
                        }
                        break;
                    case 5:
                        push.append(to_string(player5.role));
                        player5.alive = false;
                        switch (player5.role)
                        {
                        case 0:
                            break;
                        case 1:
                            weerwolf = false;
                            break;
                        case 2:
                            heks = false;
                            break;
                        case 3:
                            break;
                        }
                        break;
                    }
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    push = "weerwolven! >";
                }
            }

            if (strcmp(command, "murderdByHeks") == 0)
            {
                murder2 = stoi(data);
                push.append("wakker >");
                push.append(to_string(murder));
                push.append(" >");
                push.append(data);
                push.append(" >");
                switch (murder)
                {
                case 1:
                    push.append(to_string(player1.role));
                    player1.alive = false;
                    switch (player1.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 2:
                    push.append(to_string(player2.role));
                    player2.alive = false;
                    switch (player2.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 3:
                    push.append(to_string(player3.role));
                    player3.alive = false;
                    switch (player3.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 4:
                    push.append(to_string(player4.role));
                    player4.alive = false;
                    switch (player4.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 5:
                    push.append(to_string(player5.role));
                    player5.alive = false;
                    switch (player5.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                }
                push.append(" >");
                switch (murder2)
                {
                case 1:
                    push.append(to_string(player1.role));
                    player1.alive = false;
                    break;
                case 2:
                    push.append(to_string(player2.role));
                    player2.alive = false;
                    break;
                case 3:
                    push.append(to_string(player3.role));
                    player3.alive = false;
                    break;
                case 4:
                    push.append(to_string(player4.role));
                    player4.alive = false;
                    break;
                case 5:
                    push.append(to_string(player5.role));
                    player5.alive = false;
                    break;
                }
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >";
            }

            if (strcmp(command, "heal") == 0)
            {
                push.append("wakker >0");
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >";
                murder = 0;
                murder2 = 0;
            }

            if (strcmp(command, "niks") == 0)
            {
                push.append("wakker >");
                push.append(to_string(murder));
                push.append(" >0 >");
                switch (murder)
                {
                case 1:
                    push.append(to_string(player1.role));
                    player1.alive = false;
                    switch (player1.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 2:
                    push.append(to_string(player2.role));
                    player2.alive = false;
                    switch (player2.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 3:
                    push.append(to_string(player3.role));
                    player3.alive = false;
                    switch (player3.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 4:
                    push.append(to_string(player4.role));
                    player4.alive = false;
                    switch (player4.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                case 5:
                    push.append(to_string(player5.role));
                    player5.alive = false;
                    switch (player5.role)
                    {
                    case 0:
                        break;
                    case 1:
                        weerwolf = false;
                        break;
                    case 2:
                        heks = false;
                        break;
                    case 3:
                        break;
                    }
                    break;
                }
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >";
                murder2 = 0;
            }

            if (murder == koppel[0] || murder2 == koppel[0])
            {
                switch (koppel[0])
                {
                case 0:
                    break;
                case 1:
                    player1.alive = false;
                    //murder = 0;
                    alive--;
                    break;
                case 2:
                    player2.alive = false;
                    //murder = 0;
                    alive--;
                    break;
                case 3:
                    player3.alive = false;
                    //murder = 0;
                    alive--;
                    break;
                case 4:
                    player4.alive = false;
                    //murder = 0;
                    alive--;
                    break;
                case 5:
                    player5.alive = false;
                    //murder = 0;
                    alive--;
                    break;
                }
            }

            switch (murder)
            {
            case 0:
                break;
            case 1:
                player1.alive = false;
                //murder = 0;
                alive--;
                break;
            case 2:
                player2.alive = false;
                //murder = 0;
                alive--;
                break;
            case 3:
                player3.alive = false;
                //murder = 0;
                alive--;
                break;
            case 4:
                player4.alive = false;
                //murder = 0;
                alive--;
                break;
            case 5:
                player5.alive = false;
                //murder = 0;
                alive--;
                break;
            }

            switch (murder2)
            {
            case 0:
                break;
            case 1:
                player1.alive = false;
                //murder2 = 0;
                alive--;
                break;
            case 2:
                player2.alive = false;
                //murder2 = 0;
                alive--;
                break;
            case 3:
                player3.alive = false;
                //murder2 = 0;
                alive--;
                break;
            case 4:
                player4.alive = false;
                //murder2 = 0;
                alive--;
                break;
            case 5:
                player5.alive = false;
                //murder2 = 0;
                alive--;
                break;
            }

            if (strcmp(command, "vote") == 0)
            {
                if (counter < alive)
                {
                    votes[counter] = stoi(data);
                    counter++;
                }
                else
                {
                    push.append("result >");
                    push.append(to_string(mostFrequent(votes, 5)));
                    push.append(" >");
                    switch (mostFrequent(votes, 5))
                    {
                    case 1:
                        push.append(to_string(player1.role));
                        player1.alive = false;
                        break;
                    case 2:
                        push.append(to_string(player2.role));
                        player2.alive = false;
                        break;
                    case 3:
                        push.append(to_string(player3.role));
                        player3.alive = false;
                        break;
                    case 4:
                        push.append(to_string(player4.role));
                        player4.alive = false;
                        break;
                    case 5:
                        push.append(to_string(player5.role));
                        player5.alive = false;
                        break;
                    }
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    push = "weerwolven! >";
                    push.append("weerwolf");
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    push = "weerwolven! >";
                }
            }

            if (strcmp(command, "restart") == 0)
            {
                push.append("restart");
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >";
                i = 0;
            }

            if (strcmp(command, "restartVote") == 0)
            {
                if (i < 4)
                {
                    votes[i] = stoi(data);
                    i++;
                }
                else
                {
                    votes[i] = stoi(data);
                    if (mostFrequent(votes, 5) == 0)
                    {
                        push.append("restart! >0");
                    }
                    else if (mostFrequent(votes, 5) == 1)
                    {
                        push.append("restart! >1");
                        restart = true;
                    }
                    strcpy(send, push.c_str());
                    zmq_send( pusher, send, strlen(send), 0 );
                    push = "weerwolven! >";
                    i = 0;
                    printf("send restart\n");
                }
            }

            if (strcmp(command, "control") == 0)
            {
                control[stoi(data)-1]++;
            }

            if (restart)
            {
                printf("restart\n");
                i = 0;
                play = false;
                begin = true;
                init = false;
                alive = 5;
                counter = 0;
                numList.clear();
                restart = false;
            }

            if (weerwolf == false)
            {
                push = "weerwolven! >endGame";
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven! >";

                i = 0;
                play = false;
                begin = true;
                init = false;
                alive = 5;
                counter = 0;
                numList.clear();
            }
        }
    }
    return 0;
}

int getRole()
{
    do {
        srand(time(NULL));
        num =  rand()% 4;
        if (numList.contains(num) && num != 0)
        {
            duplicate = true; // skip duplicates
        }
        else
        {
            if (num == 0 && burger == false)
            {
                duplicate = false;
                burger = true;
                //printf("lol\n");
            }
            else
            {
                numList.append(num);
                duplicate = false;
            }
        }
    } while (duplicate);
    return num;
}

int mostFrequent(int arr[], int n)
{
    // Sort the array
    sort(arr, arr + n);

    // find the max frequency using linear traversal
    int max_count = 1, res = arr[0], curr_count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == 0)
        {}
        else if (arr[i] == arr[i - 1])
        {
            curr_count++;
        }
        else {
            if (curr_count > max_count) {
                max_count = curr_count;
                res = arr[i - 1];
            }
            curr_count = 1;
        }
    }

    // If last element is most frequent
    if (curr_count > max_count)
    {
        max_count = curr_count;
        res = arr[n - 1];
    }

    return res;
}
