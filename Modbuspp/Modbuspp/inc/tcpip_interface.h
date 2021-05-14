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

#include<iostream>
#include<vector>
#define TCPIP_POSIX
#if defined(TCPIP_POSIX)
#warning "POSIX is selected as TCP/IP Stack"
namespace port{
class LinuxTcpIPStack;
};
using TcpIPStack= port::LinuxTcpIPStack;
#elif defined(TCPIP_WINDOWS)
#warning "WINSOCK is selected as TCP/IP Stack"
#elif defined(TCPIP_LWIP)
#warning "LWIP is selected as TCP/IP Stack"
#else
#error "Please select TCP/IP Stack"
#endif




//Non virtual interface
class ITcpIp{
public:
    using ip_t=unsigned long;
    using port_t=unsigned short;
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
                       TCPIP_ACCEPT_ERR,
                       TCPIP_SETSOCK_ERR,
                       TCPIP_SETSOCK_SUCCESS,
                       TCPIP_SEND_ERR,
                       TCPIP_SEND_SUCCESS
                     };

    struct diag{

          status stat{status::TCPIP_DEINIT};
          int err{};
     };

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    [[nodiscard]] bool connect(std::string ip_str,port_t port){

        return vconnect(ip_str,port);
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
    [[nodiscard]] uint32_t send(std::vector<int8_t>& vec_out_data){
            return vsend(vec_out_data);
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
    [[nodiscard]] bool receive(){
            return vreceive();
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
    [[nodiscard]] bool bind(){
        return vbind();
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
    [[nodiscard]] bool listen(const unsigned int max_conn){
        return vlisten(max_conn);
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
    [[nodiscard]] int accept(){
        return vaccept();
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
    [[nodiscard]] bool close(){
        return vclose();
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
    [[nodiscard]] diag get_status_err()const {
        return vget_status_err();
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
    [[nodiscard]] ip_t getip()const{
        return vgetip();
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
    [[nodiscard]] port_t getport()const{
        return vgetport();
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
    [[nodiscard]] bool is_cnxn_on()const{
        return vis_cnxn_on();
    }

    virtual ~ITcpIp(){}
private:

     virtual int vget_fd()=0;
     virtual bool vconnect(std::string ,port_t )=0;
     virtual uint32_t vsend(std::vector<int8_t>&)=0;
     virtual bool vreceive()=0;
     virtual bool vbind()=0;
     virtual bool vlisten(const unsigned int max_conn)=0;
     virtual int vaccept()=0;
     virtual bool vclose()=0;
     virtual diag vget_status_err()const =0;
     virtual ip_t vgetip()const=0;
     virtual port_t vgetport()const=0;
     virtual bool vis_cnxn_on()const=0;
     virtual void set_sockopt(int level,int optnum)=0;





};

#endif//__TCPIP_INTERFACE_H__
