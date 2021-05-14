/****************************************************************************
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#ifndef __MOCK_SOCKET_CLASS_H__
#define __MOCK_SOCKET_CLASS_H__

#include "gmock/gmock.h"
class IMockSocket{
public:
    virtual ~IMockSocket() {}
    virtual int mock_socket(int __domain, int __type, int __protocol)=0;
    virtual int mock_inet_aton (const char *__cp, void *__inp)=0;
    virtual int mock_fcntl (int __fd, int __cmd)=0;
    virtual int mock_close (int __fd)=0;
};
class MockSocket:public IMockSocket{

public:
       MOCK_METHOD(int,mock_socket,(int __domain, int __type, int __protocol),(override));
       MOCK_METHOD(int,mock_inet_aton,(const char *__cp, void *__inp),(override));
       MOCK_METHOD(int,mock_fcntl,(int __fd, int __cmd),(override));
       MOCK_METHOD(int,mock_close,(int __fd),(override));
};

extern MockSocket mock_obj_g;

#endif
