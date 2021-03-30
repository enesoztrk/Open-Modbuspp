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

#include "../../port/tcpip_abstraction.h"
#include <iostream>
#include <string>

extern "C" {
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <errno.h>
}

namespace mb{
using sock_fd=int;
using sock_addr=struct sockaddr_in;
using ip_t=unsigned long;
using port_t=unsigned short;

//Abstract Factory
/*
 * See https://refactoring.guru/design-patterns/abstract-factory
*/
class ITcpIp: public AbsTcpipmngmt{

public:

    ITcpIp()=default;

    /**
     * @brief
     *
     *
     * @param none
     * @return
     * @note
     * @warning Warning.
     */
    ~ITcpIp(){

        if(this->close())
        {
             sock_desc=-1;
             addr={};
             ip_str="";
        }
        else{
            //exception
        }

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
    ITcpIp(ip_t ip,port_t port):addr{}{
       init_socket(ip,port);
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
    ITcpIp(std::string ip_str,port_t port):addr{}{

        std::cout<<__PRETTY_FUNCTION__<<"\n";
        struct in_addr addr_temp{};
        auto ret_val = ::inet_aton(ip_str.c_str(),&addr_temp);


        if(0==ret_val){
            //exception throw
            }
        else if(1==ret_val){
            init_socket(addr_temp.s_addr,port);

        }

    }

    //copy ctor deleted
    ITcpIp(const ITcpIp&)=delete;
    //copy assignment is deleted
    ITcpIp& operator=(const ITcpIp &other)=delete;

    /**
     * @brief  it creates socket instance.
     *
     *
     * @param none
     * @return int
     * @note
     * @warning Warning.
     */
    [[nodiscard]]sock_fd get_fd() override{
        sock_desc = ::socket(AF_INET , SOCK_STREAM , 0);
        if(sock_desc==-1){
            tcpip_diag.stat=diag::status::TCPIP_SOCKFD_ERR;
            tcpip_diag.err=errno;
        }
        else
            tcpip_diag.stat=diag::status::TCPIP_SOCKFD_INIT;


        return sock_desc;
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
    [[nodiscard]]bool connect()override{
        std::cout<<__PRETTY_FUNCTION__<<"\n";

        if(sock_desc<0)
            return false;
        else
            return true;


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
    [[nodiscard]] bool send()override{
        std::cout<<__PRETTY_FUNCTION__<<"\n";
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
     [[nodiscard]]bool receive()override{
        std::cout<<__PRETTY_FUNCTION__<<"\n";
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
    [[nodiscard]]bool bind()override{
        std::cout<<__PRETTY_FUNCTION__<<"\n";
        bool ret_val=false;



        set_sockopt(SOL_SOCKET,SO_REUSEADDR);


        if(0==(::bind(sock_desc, (struct sockaddr *)&addr, sizeof(addr)))){
               tcpip_diag.stat=diag::status::TCPIP_BIND_SUCCESS;
               ret_val=true;
        }
        else
        {     tcpip_diag.stat=diag::status::TCPIP_BIND_ERR;
              tcpip_diag.err=errno;

        }


            return ret_val;

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
    [[nodiscard]]bool listen(const unsigned int max_conn)override{
        std::cout<<__PRETTY_FUNCTION__<<"\n";

        bool ret_val=false;

        if(0==(::listen(sock_desc,max_conn))){
               tcpip_diag.stat=diag::status::TCPIP_LISTEN_SUCCESS;
               ret_val=true;
        }
        else
        {     tcpip_diag.stat=diag::status::TCPIP_LISTEN_ERR;
              tcpip_diag.err=errno;

        }


        return ret_val;
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
    [[nodiscard]]sock_fd accept()override{

        auto sock_size= static_cast<socklen_t>(sizeof(struct sockaddr_in));
        struct sockaddr_in client_sock{};
        sock_fd client_fd{-1};

        client_fd = ::accept(sock_desc,
                           (struct sockaddr*) &client_sock, &sock_size);

        if(client_fd==-1)
        {
           // TODO: tcpip_diag.stat=diag::status::TCPIP_
                tcpip_diag.err=errno;
        }
        std::cout<<__PRETTY_FUNCTION__<<"\n";
        return client_fd;
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
    [[nodiscard]]bool close()override{
        std::cout<<__PRETTY_FUNCTION__<<"\n";
        ::close(sock_desc);
        return true;
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
    [[nodiscard]]ip_t getip()const{

            return  addr.sin_addr.s_addr;
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
    [[nodiscard]]port_t getport()const{

            return  addr.sin_port;
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
    [[nodiscard]]diag::status getstatus()const{

            return tcpip_diag.stat;
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
    diag get_status_err()const override{return this->tcpip_diag;}
private:
    void init_socket(ip_t ip,port_t port){

        addr.sin_port=htons(port);
        addr.sin_family = AF_INET;
        tcpip_diag.stat=diag::status::TCPIP_INIT;
        addr.sin_addr.s_addr=ip;

    }

    void set_stat_err(diag::status stat,int err);

    void set_sockopt(int level,int optnum)override{
        auto optval = 1;

        if(0==(::setsockopt(sock_desc, level, optnum, &optval, sizeof(optval)))){
               tcpip_diag.stat=diag::status::TCPIP_SETSOCK_SUCCESS;

        }
        else
        {     tcpip_diag.stat=diag::status::TCPIP_SETSOCK_ERR;
              tcpip_diag.err=errno;

        }






    }
    sock_fd sock_desc{-1};
    sock_addr addr={};
    //TODO: ip_t getip()const will be converted template function
    std::string ip_str{""};
    diag tcpip_diag;
};

}
#endif//__TCPIP_POSIX_H__
