/**
 * ============================================================================
 * @file posix_socket_mock.hpp
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
#ifndef __POSIX_SOCKET_MOCK_H__
#define __POSIX_SOCKET_MOCK_H__
#include<cstdint>
#include<iostream>
extern "C" {
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/poll.h>
}





int socket (int __domain, int __type, int __protocol)__THROW;
int inet_aton (const char *__cp, struct in_addr *__inp)__THROW;
int fcntl (int __fd, int __cmd, ...);
int close (int __fd);

 in_addr_t inet_addr (const char *__cp)__THROW;
 int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
 int poll (struct pollfd *__fds, nfds_t __nfds, int __timeout);

 ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);

 ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);


 int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)__THROW;

 int listen (int __fd, int __n)__THROW;
 int accept (int __fd, __SOCKADDR_ARG __addr,
            socklen_t *__restrict __addr_len);

 int setsockopt (int __fd, int __level, int __optname,
                const void *__optval, socklen_t __optlen)__THROW;
#endif //__POSIX_SOCKET_MOCK_H__
