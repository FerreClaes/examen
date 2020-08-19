#include <stdio.h>
#include <stdlib.h>
#include <zmq.h>
#include <string>
#include <string.h>
#include <QList>
#include <pthread.h>
#include <time.h>

using namespace std;

void * context;
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

void *control(void *vargp)  //extra thread voor controleren online
{
    char send[30];
    void * pusher = zmq_socket( context, ZMQ_PUSH );
    zmq_connect( pusher, "tcp://192.168.0.198:24041" );
    string push = "weerwolven? >";
    int *id = (int *)vargp;
    push.append("control >");
    push.append(to_string(*id));
    strcpy(send, push.c_str());
    while (1)
    {
        delay(60);
        printf("send \n");
        zmq_send( pusher, send, strlen(send), 0 );
    }
}

int main()
{
    char name[25];
    char subscribe[100];
    string push = "weerwolven? >";
    string sub = "weerwolven! >";
    int id;
    char send[1000];
    bool game = true;
    zmq_msg_t msg;
    int rc;
    int size;
    char subscr[20];
    char command[100];
    char data[100];
    char data2[100];
    char data3[100];
    char data4[100];
    char read[1000] = "";
    bool init = false;
    int role = 0;
    char murderdByWeerwolf[10];
    int murderdByHeks;
    QList<int> deadlist;
    int hekscommand;
    int verdachte;
    int koppel1;
    int koppel2;
    bool endGame = false;
    bool weerwolf = true;
    bool heks = true;
    int aantalSpelers = 5;
    int akkoord;
    bool restart = false;

    context = zmq_ctx_new();

    void * pusher = zmq_socket( context, ZMQ_PUSH );
    void * subscriber = zmq_socket(context, ZMQ_SUB);

    zmq_connect( pusher, "tcp://192.168.0.198:24041" );
    zmq_connect( subscriber, "tcp://192.168.0.198:24042" );


    printf("Wat is uw naam? ");                                                     //speler id en role geven
    scanf("%s", name);
    sub.append(name);
    sub.append(" >");

    strcpy(subscribe, sub.c_str());
    zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE,subscribe, strlen(subscribe));
    //printf(subscribe);printf("\n");

    push.append("init >");
    push.append(name);
    strcpy(send, push.c_str());
    zmq_send( pusher, send, strlen(send), 0 );    //verzenden
    push = "weerwolven? >";



    while (game)
    {
        rc = zmq_msg_init (&msg);                                                           //read benthernet
        rc = zmq_recvmsg (subscriber, &msg, 0);
        size = zmq_msg_size (&msg);
        memcpy(read, zmq_msg_data(&msg), size);
        zmq_msg_close(&msg);
        read[size] = 0;
        printf("%s\n", read);
        zmq_msg_close (&msg);

        sscanf(read, "%s >%s >%s >%s >%s >%s", subscr, command, data, data2, data3, data4);

        if (strcmp(data, "init") == 0)
        {
            //printf("init/n");
            if (init == false)
            {
                //printf(data);
                if (strcmp(command, name) == 0)
                {
                    sscanf(data2, "%d", &id);
                    sscanf(data3, "%d", &role);
                    pthread_t tid;
                    pthread_create(&tid, NULL, control, (void *)&id);
                    printf("Jouw playerid is %d\n", id);
                    switch (role)
                    {
                    case 0:
                        printf("jij bent een burger.\n");
                        break;
                    case 1:
                        printf("Jij bent een weerwolf.\n");
                        break;
                    case 2:
                        printf("Jij bent de heks.\n");
                        break;
                    case 3:
                        printf("Jij bent cupido.\n");
                        break;
                    case 4:
                        printf("Er zijn al genoeg speler. U bent toeschouwer.");
                    }
                    init = true;
                    sub = "weerwolven! >";
                    strcpy(subscribe, sub.c_str());
                    zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE,subscribe, strlen(subscribe));
                    printf("Wachten op andere spelers...\n");
                }
            }
        }

        if (strcmp(command, "weerwolf") == 0)
        {
            printf("Iedereen gaat slapen.\nDe weerwolf wordt wakker!\n");
            if (role == 1)
            {
                printf("Wie wilt u deze nacht vermoorden? (U kan antwoorden met de nummer van de player) (voor een restart aan te vragen type %d)\n", aantalSpelers+1);
                scanf("%s", murderdByWeerwolf);
                while (stoi(murderdByWeerwolf) < 1 || stoi(murderdByWeerwolf) > aantalSpelers+1 || deadlist.contains(stoi(murderdByWeerwolf)))
                {
                    printf("Deze speler bestaat niet of is dood. Kies opnieuw!\n ");
                    scanf("%s", murderdByWeerwolf);
                }
                if  (stoi(murderdByWeerwolf) < aantalSpelers+1)
                {
                    push.append("murderdByWeerwolf >");
                    push.append(murderdByWeerwolf);
                }
                else if (stoi(murderdByWeerwolf) == aantalSpelers+1)
                {
                    push.append("restart >");
                    push.append(murderdByWeerwolf);
                }
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven? >";
            }
        }

        if (strcmp(command, "heks") == 0)
        {
            if (heks)
            {
                printf("De weerwolf gaat terug slapen en de heks wordt wakker.\n");
                if (role == 2)
                {
                    printf("Player%d is deze nacht vermoord door de weerwolf.\n", stoi(data));
                    printf("Wilt u deze player terug helen?(0) Wilt u niks doen?(1) Of wilt u iemand bijvermoorden?(2)\nWilt u een restart aanvragen? type 3\n");
                    scanf("%d", &hekscommand);
                    while(hekscommand > 3)
                    {
                        printf("Dit kan niet! Type het juiste command in.");
                        scanf("%d", &hekscommand);
                    }
                    if (hekscommand == 0)
                    {
                        push.append("heal");
                        strcpy(send, push.c_str());
                        zmq_send( pusher, send, strlen(send), 0 );
                        push = "weerwolven? >";
                    }
                    if (hekscommand == 1)
                    {
                        push.append("niks");
                        strcpy(send, push.c_str());
                        zmq_send( pusher, send, strlen(send), 0 );
                        push = "weerwolven? >";
                    }
                    if (hekscommand == 2)
                    {
                        printf("Wie wilt u bijvermoorden?\n");
                        scanf("%d", &murderdByHeks);
                        while (stoi(data) == murderdByHeks || murderdByHeks < 1 || murderdByHeks > 5 || deadlist.contains(murderdByHeks))
                        {
                            printf("Deze speler bestaat niet of is dood. Kies opnieuw!\n ");
                            scanf("%d", &murderdByHeks);
                        }
                        push.append("murderdByHeks >");
                        push.append(to_string(murderdByHeks));
                        strcpy(send, push.c_str());
                        zmq_send( pusher, send, strlen(send), 0 );
                        push = "weerwolven? >";
                    }
                    if (hekscommand == 3)
                    {
                        push.append("restart");
                        strcpy(send, push.c_str());
                        zmq_send( pusher, send, strlen(send), 0 );
                        push = "weerwolven? >";
                    }
                }
            }
            else
            {
                printf("De weerwolf gaat slapen.\n");
            }
        }

        if (strcmp(command, "wakker") == 0)
        {
            if (heks)
            {
                printf("De heks gaat terug slapen.\n");
            }

            printf("Iedereen mag wakker worden.\n");
            if (stoi(data) == 0)
            {
                printf("Er is niemand vermoord deze nacht.\n");
            }
            else if (stoi(data2) > 0)
            {
                printf("Player%d ", stoi(data));
                switch (stoi(data3))
                {
                case 0:
                    printf("burger) ");
                    break;
                case 1:
                    printf("weerwolf) ");
                    break;
                case 2:
                    printf("heks) ");
                    break;
                case 3:
                    printf("cupido) ");
                    break;
                }
                printf("en player%d (", stoi(data2));
                switch (stoi(data4))
                {
                case 0:
                    printf("burger) ");
                    break;
                case 1:
                    printf("weerwolf) ");
                    break;
                case 2:
                    printf("heks) ");
                    break;
                case 3:
                    printf("cupido) ");
                    break;
                }
                printf("zijn deze nacht vermoord.\n");
            }
            else if (stoi(data) > 0)
            {
                printf("Player%d (", stoi(data));
                switch (stoi(data3))
                {
                case 0:
                    printf("burger) is deze nacht vermoord.\n");
                    break;
                case 1:
                    printf("weerwolf) is deze nacht vermoord.\n");
                    break;
                case 2:
                    printf("heks) is deze nacht vermoord.\n");
                    break;
                case 3:
                    printf("cupido) is deze nacht vermoord.\n");
                    break;
                }
            }
            else
            {
                printf("Er is niemand deze nacht vermoord.\n");
            }
            printf("Wie denkt u dat de weerwolf is?(type de nummer van de player) (voor een restart aan te vragen type %d\n", aantalSpelers+1);
            scanf("%d", &verdachte);
            while (verdachte < 1 || verdachte > aantalSpelers + 1 || deadlist.contains(verdachte))
            {
                printf("Deze speler bestaat niet of is dood. Kies opnieuw!\n ");
                scanf("%d", &verdachte);
            }
            if (verdachte < aantalSpelers + 1)
            {
                push.append("vote >");
                push.append(to_string(verdachte));
            }
            else if(verdachte == aantalSpelers + 1)
            {
                push.append("restart >");
            }
            strcpy(send, push.c_str());
            zmq_send( pusher, send, strlen(send), 0 );
            push = "weerwolven? >";
        }

        if (strcmp(command, "result") == 0)
        {
            if (stoi(data) == 0)
            {
                printf("Er is niemand vermaard deze nacht.\n");
            }
            else
            {
                printf("Player%d wordt vermoord door het volk en was een ", stoi(data));
                switch (stoi(data2))
                {
                case 0:
                    printf("burger.\n");
                    break;
                case 1:
                    printf("weerwolf.\n");
                    break;
                case 2:
                    printf("heks.\n");
                    break;
                case 3:
                    printf("cupido.\n");
                    break;
                }
            }
        }

        if (strcmp(command, "cupido") == 0)
        {
            if (role == 3)
            {
                printf("U mag een koppel uitkiezen.\nType de nummer van de eerste persoon die u in het koppel wilt.");
                scanf("%d", &koppel1);
                printf("Type de nummer van de eerste persoon die u in het koppel wilt.");
                scanf("%d", &koppel2);
                while (koppel2 == koppel1)  {printf("Dit gaat niet. Type de nummer van de eerste persoon die u in het koppel wilt.");scanf("%d", &koppel2);}
                push.append("koppel >");
                push.append(to_string(koppel1));
                push.append(" >");
                push.append(to_string(koppel2));
                strcpy(send, push.c_str());
                zmq_send( pusher, send, strlen(send), 0 );
                push = "weerwolven? >";
            }
        }

        if (strcmp(command, "koppel") == 0)
        {
            sscanf(data, "%d", &koppel1);
            sscanf(data2, "%d", &koppel2);
            if (koppel1 == id)  {printf("U bent een koppel met player%d.\n", koppel2);}
            if (koppel2 == id)  {printf("U bent een koppel met player%d.\n", koppel1);}
        }

        if (strcmp(command, "restart") == 0)
        {
            printf("Iemand vraagt een restart aan.\nWilt u dit ook? Type 1 als u akkoord gaat en 0 als u niet akkoord gaat.\n");
            scanf("%d", &akkoord);
            while (akkoord > 1)
            {
                printf("dit antwoord kan niet. probeer opnieuw\n");
                scanf("%d", &akkoord);
            }
            push.append("restartVote >");
            push.append(to_string(akkoord));
            strcpy(send, push.c_str());
            zmq_send( pusher, send, strlen(send), 0 );
            push = "weerwolven? >";
        }

        if (strcmp(command, "restart!") == 0)
        {
            if (stoi(data) == 0)
            {
                printf("De meerderheid stemde tegen een restart.\n");
            }
            else if (stoi(data) == 1)
            {
                printf("de meerderheid stemde voor een restart.\n");
                restart = true;
            }
        }

        if (restart)
        {
            push.append("init >");
            push.append(name);
            strcpy(send, push.c_str());
            zmq_send( pusher, send, strlen(send), 0 );    //verzenden
            push = "weerwolven? >";
            init = false;
            restart = false;
        }

        if (strcmp(command, "offline") == 0)
        {
            printf("player%s heeft het spel verlaten.", data);
        }

        if (strcmp(command, "endGame") == 0)
        {
            game = false;
        }
    }
    return 0;
}
