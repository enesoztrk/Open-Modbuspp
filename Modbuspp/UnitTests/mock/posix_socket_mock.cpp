/**
 * ============================================================================
 * @file posix_socket_mock.cpp
 * @author Enes OZTURK
 * @brief
 * @date 2021-05-14
 *
 * @copyright:  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ============================================================================
 */

#include "posix_socket_mock.hpp"
#include "mock_socket_class.h"
#include <cstdarg>

MockSocket* mock_obj_g;
int socket (int __domain, int __type, int __protocol)__THROW{

    std::cout<<"mock socket init\n";



    return mock_obj_g->socket(__domain,__type,__protocol);

}



/*int inet_aton (const char *__cp, struct in_addr *__inp)__THROW{
    std::cout<<"mock inet_aton\n";
    return mock_obj_g->inet_aton(__cp,__inp);
}*/

int fcntl (int __fd, int __cmd, ...){
     std::cout<<"mock fcntl\n";
     if(mock_obj_g!=nullptr){
     uint32_t flag;
     va_list args;
       va_start(args, __cmd);
        for( int i = 0; i < 1; i++ )
           flag= va_arg( args, uint32_t );
      va_end( args );
    return mock_obj_g->fcntl(__fd,__cmd,flag);
     }
     else
         return 0;
}


int close (int __fd){
     std::cout<<"mock close\n";
    return mock_obj_g->close(__fd);
}

in_addr_t inet_addr (const char *__cp)__THROW {

      std::cout<<"mock inet_addr\n";
      return mock_obj_g->inet_addr(__cp);

}
 int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len){

    std::cout<<"mock connect\n";
    return mock_obj_g->connect(__fd,__addr,__len);

}

 int poll (struct pollfd *__fds, nfds_t __nfds, int __timeout){
    std::cout<<"mock poll\n";

    __fds->revents=POLLOUT;

    return mock_obj_g->poll(__fds,__nfds,__timeout);
}


 ssize_t send (int __fd, const void *__buf, size_t __n, int __flags){
     std::cout<<"mock send\n";
    return mock_obj_g->send(__fd,__buf,__n,__flags);
}


inline ssize_t recv (int __fd, void *__buf, size_t __n, int __flags){
     std::cout<<"mock receive\n";
    return mock_obj_g->recv(__fd,__buf,__n,__flags);
}


 int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)__THROW{
     std::cout<<"mock bind\n";
    return mock_obj_g->bind(__fd,__addr,__len);

}

 int listen (int __fd, int __n)__THROW{


    std::cout<<"mock listen\n";
   return mock_obj_g->listen(__fd,__n);

}
 int accept (int __fd, __SOCKADDR_ARG __addr,
            socklen_t *__restrict __addr_len){
    std::cout<<"mock accept\n";
   return mock_obj_g->accept(__fd,__addr,__addr_len);

}
 int setsockopt (int __fd, int __level, int __optname,
                const void *__optval, socklen_t __optlen)__THROW{

    std::cout<<"mock accept\n";
    return mock_obj_g->setsockopt(__fd,__level,__optname,__optval,__optlen);

}
