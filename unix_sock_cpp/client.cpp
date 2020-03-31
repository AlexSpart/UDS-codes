//c++ client unix socket stream
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <cstdlib> 
#include <unistd.h>
#include <syscall.h>
#include <iostream> 

#include "quadkey.hpp"


//#include "my_class.h"

using namespace std; 
//using namespace N;
//using namespace tiles;

#define DATA "Half a league, half a league . . ."
#define NAME "/tmp/quad_socket"


//void my_class::do_something()
//{
//    cout << "Doing something!" << endl;
//}

main(int argc, char** argv)
 {
     bool alex;
     string str;
     int a;
     int b; 
     int c;
     double d;
     //my_class mc;
    // mc.do_something();
     TileSystem ts;
     ts.do_something();
     ts.LatLongToPixelXY(40,7,3,a,b);
     //ts.TileXYToQuadKey(40,7,2,true);
     //str = ts.TileXYToQuadKey(40,7,2,alex);


     int sock;
     struct sockaddr_un server;
     char buf[1024];
         
     printf("Input message: %s \n", argv[1]);

     sock = socket(AF_UNIX, SOCK_STREAM, 0);
     if (sock < 0) {
         perror("opening stream socket");
         exit(1);
     }
     server.sun_family = AF_UNIX;
     strcpy(server.sun_path, NAME);


     if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) {
         close(sock);
         perror("connecting stream socket");
         exit(1);
     }
     if (write(sock, argv[1], sizeof(argv[1])) < 0)
         perror("writing on stream socket");
     close(sock);
} 







