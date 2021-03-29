/**
 * ============================================================================
 * @file tcpip_abstraction.h
 * @author Enes OZTURK
 * @brief
 * @date 2021-03-28
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

#ifndef __TCPIP_ABSTRACTION_H__
#define __TCPIP_ABSTRACTION_H__


//Abstract class
class AbsTcpipmngmt{

public:
     [[nodiscard]]virtual int get_socket_fd()=0;
     [[nodiscard]]virtual bool connect()=0;
     [[nodiscard]]virtual bool send()=0;
     [[nodiscard]]virtual bool receive()=0;
     [[nodiscard]]virtual bool bind()=0;
     [[nodiscard]]virtual bool listen()=0;
     [[nodiscard]]virtual bool accept()=0;
     [[nodiscard]]virtual bool close()=0;

     enum class status{TCPIP_NOT_CONNECTED,TCPIP_CONNECTED,TCPIP_INIT,TCPIP_DEINIT,TCPIP_SOCKFD_ERR,TCPIP_SOCKFD_INIT};


};

#endif
