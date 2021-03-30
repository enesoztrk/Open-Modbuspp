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

#ifndef __TCPIP_INTERFACE_H__
#define __TCPIP_INTERFACE_H__


#define TCPIP_POSIX
#if defined(TCPIP_POSIX)
#warning "POSIX is selected as TCP/IP Stack"
#include "../port/posix/tcpip_posix.h"

#elif defined(TCPIP_WINDOWS)
#warning "WINSOCK is selected as TCP/IP Stack"
#elif defined(TCPIP_LWIP)
#warning "LWIP is selected as TCP/IP Stack"
#else
#error "Please select TCP/IP Stack"
#endif



#endif//__TCPIP_INTERFACE_H__
