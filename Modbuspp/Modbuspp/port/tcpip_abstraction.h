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
     struct diag;
     [[nodiscard]]virtual int get_fd()=0;
     [[nodiscard]]virtual bool connect()=0;
     [[nodiscard]]virtual bool send()=0;
     [[nodiscard]]virtual bool receive()=0;
     [[nodiscard]]virtual bool bind()=0;
     [[nodiscard]]virtual bool listen(const unsigned int max_conn)=0;
     [[nodiscard]]virtual int accept()=0;
     [[nodiscard]]virtual bool close()=0;
     [[nodiscard]]virtual diag get_status_err()const =0;
struct diag{
     enum class status{ TCPIP_INIT,
                        TCPIP_DEINIT,
                        TCPIP_SOCKFD_ERR,
                        TCPIP_SOCKFD_INIT,
                        TCPIP_NOT_CONNECTED,
                        TCPIP_CONNECTED,
                        TCPIP_RECV_ERR,
                        TCPIP_RECV_SUCCESS,
                        TCPIP_BIND_ERR,
                        TCPIP_BIND_SUCCESS,
                        TCPIP_LISTEN_ERR,
                        TCPIP_LISTEN_SUCCESS,
                        TCPIP_ACCEPT_SUCCESS,
                        TCPIP_SETSOCK_ERR,
                        TCPIP_SETSOCK_SUCCESS

                      };
     status stat{status::TCPIP_DEINIT};
     int err{};
};

protected:
    virtual void set_sockopt(int level,int optnum)=0;

};

#endif
