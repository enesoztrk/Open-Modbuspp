/**
 * ============================================================================
 * @file mock_socket_class.h
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
#ifndef __MOCK_SOCKET_CLASS_H__
#define __MOCK_SOCKET_CLASS_H__

#include "gmock/gmock.h"
class IMockSocket{
public:
    using in_addr_t=int;
    using nfds_t=unsigned long int;
    virtual ~IMockSocket() {}
    virtual int socket(int __domain, int __type, int __protocol)=0;
    virtual int inet_aton (const char *__cp, void *__inp)=0;
    virtual int fcntl (int __fd, int __cmd,uint32_t flag)=0;
    virtual int close (int __fd)=0;
    virtual in_addr_t inet_addr (const char *__cp)=0;
    virtual int connect (int __fd, const void*  __addr, socklen_t __len)=0;
    virtual int poll (void *__fds, nfds_t __nfds, int __timeout)=0;
    virtual ssize_t send (int __fd, const void *__buf, size_t __n, int __flags)=0;
    virtual ssize_t recv (int __fd, void *__buf, size_t __n, int __flags)=0;
    virtual int bind (int __fd, const void* __addr, socklen_t __len)=0;
    virtual int listen (int __fd, int __n)=0;
    virtual int accept (int __fd, void* __addr,socklen_t * __addr_len)=0;
    virtual int setsockopt (int __fd, int __level, int __optname,
                    const void *__optval, socklen_t __optlen)=0;
};
class MockSocket:public IMockSocket{

public:

       MOCK_METHOD(int,socket,(int __domain, int __type, int __protocol),(override));
       MOCK_METHOD(int,inet_aton,(const char *__cp, void *__inp),(override));
       MOCK_METHOD(int,fcntl,(int __fd, int __cmd,uint32_t flag),(override));
       MOCK_METHOD(int,close,(int __fd),(override));
       MOCK_METHOD(in_addr_t,inet_addr,(const char *__cp),(override));
       MOCK_METHOD(int,connect,(int __fd, const void*  __addr, socklen_t __len),(override));
       MOCK_METHOD(int,poll,(void *__fds, nfds_t __nfds, int __timeout),(override));
       MOCK_METHOD(ssize_t,send,(int __fd, const void *__buf, size_t __n, int __flags),(override));
       MOCK_METHOD(ssize_t,recv,(int __fd, void *__buf, size_t __n, int __flags),(override));
       MOCK_METHOD(int,bind,(int __fd, const void* __addr, socklen_t __len),(override));
       MOCK_METHOD(int,listen,(int __fd, int __n),(override));
       MOCK_METHOD(int,accept,(int __fd, void* __addr,socklen_t * __addr_len),(override));
       MOCK_METHOD(int,setsockopt,(int __fd, int __level, int __optname,
                                    const void *__optval, socklen_t __optlen),(override));
};

extern MockSocket* mock_obj_g;

#endif
