

#include "posix_socket_mock.hpp"
#include "mock_socket_class.h"


MockSocket mock_obj_g;
int socket (int __domain, int __type, int __protocol)__THROW{

    std::cout<<"mock socket init\n";



    return mock_obj_g.mock_socket(__domain,__type,__protocol);

}



int inet_aton (const char *__cp, struct in_addr *__inp)__THROW{
    std::cout<<"mock inet_aton\n";
    return mock_obj_g.mock_inet_aton(__cp,__inp);
}

int fcntl (int __fd, int __cmd, ...){
     std::cout<<"mock fcntl\n";
    return mock_obj_g.mock_fcntl(__fd,__cmd);
}


int close (int __fd){
     std::cout<<"mock close\n";
    return mock_obj_g.mock_close(__fd);
}
