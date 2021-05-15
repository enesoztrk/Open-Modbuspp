/**
 * ============================================================================
 * @file tcpip_posix.h
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

#ifndef __TCPIP_POSIX_H__
#define __TCPIP_POSIX_H__



#include <iostream>
#include <string>
#include <vector>
#include<cstdint>
#include <queue>

#ifndef MOCK_SUPPORT
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



#else

#include "../../UnitTests/mock/posix_socket_mock.hpp"
#endif




#include "tcpip_interface.h"

namespace port{
using sock_fd=int;
using sock_addr=struct sockaddr_in;


//Abstract Factory
/*
 * See https://refactoring.guru/design-patterns/abstract-factory
 * Convention Rules -> https://google.github.io/styleguide/cppguide.html
 * https://r4nd0m6uy.ch/event-driven-programming-with-the-reactor-pattern.html
*/
class LinuxTcpIPStack: public ITcpIp{

public:

    LinuxTcpIPStack()=delete;

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    ~LinuxTcpIPStack();

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    LinuxTcpIPStack(ip_t ip,port_t port);


    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
     LinuxTcpIPStack(std::string ip_str,port_t port);

    // Class is moveable
    LinuxTcpIPStack(LinuxTcpIPStack&& other)               noexcept;
    LinuxTcpIPStack& operator=(LinuxTcpIPStack&& other)    noexcept;


    //Class is not copyable
    LinuxTcpIPStack(const LinuxTcpIPStack&)=delete;
    LinuxTcpIPStack& operator=(const LinuxTcpIPStack &other)=delete;



private:
    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    sock_fd vget_fd() override;





    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */

    bool vis_cnxn_on()const override;
    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    bool vconnect(std::string ip_str,port_t port)override;

    /**
     * @brief operator<< calls send function
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    ITcpIp& voperator(const std::vector<int8_t>& data_vec)override
    {
            vsend(data_vec);
            return *this;
    }

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */

    uint32_t vsend(const std::vector<int8_t>&) override;

    uint32_t vsend(const std::vector<int8_t>&&) override{
    }

     /**
      * @brief operator>> calls receive function
      *
      *
      * @param none
      * @return
      * @note
      * @warning Warning.
      */
      bool operator>>(std::vector<int8_t>& data_vec);

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
     bool vreceive()override;
    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
     bool vbind()override;


    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    bool vlisten(const unsigned int max_conn)override;

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    sock_fd vaccept()override;


    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    bool vclose()override;


    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    ip_t vgetip()const override;
    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
   port_t vgetport()const override;

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    status vgetstatus()const{

            return tcpip_diag.stat;
    }

    diag vget_status_err()const override;

    void init_socket(ip_t ip,port_t port);

    void set_stat_err(status stat,int err);

    void set_sockopt(int level,int optnum)override;

   //Variables

    sock_fd sock_desc{-1};
    sock_addr addr={};
    //TODO: ip_t getip()const will be converted template function
    std::string ip_str{""};
    diag tcpip_diag;
    bool b_is_connection_on{false};
    using data_packet= std::vector<uint8_t>;


    //queues will be created for incoming and outgoing packets
    std::queue<data_packet> m_in_data{};
    std::queue<data_packet> m_out_data{};


};








}//Port namespacet






#endif//__TCPIP_POSIX_H__
