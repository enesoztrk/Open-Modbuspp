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

}

namespace mb{

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
    ITcpIp(ip_t ip,port_t port){
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
    ITcpIp(std::string ip_str,port_t port){

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
    [[nodiscard]]int get_socket_fd() override{
        sock_desc = ::socket(AF_INET , SOCK_STREAM , 0);
        if(sock_desc!=-1)
            tcpip_stat=status::TCPIP_SOCKFD_ERR;
        else
            tcpip_stat=status::TCPIP_SOCKFD_INIT;
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
        if(::bind(sock_desc, (struct sockaddr *)&addr, sizeof(addr))<0)
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
    [[nodiscard]]bool listen()override{
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
    [[nodiscard]]bool accept()override{
        std::cout<<__PRETTY_FUNCTION__<<"\n";
       // std::cout<<"ip: "<<ip<<" port: "<<port<<"\n";
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
    [[nodiscard]]status getstatus()const{

            return tcpip_stat;
    }
private:
    void init_socket(ip_t ip,port_t port){
        addr.sin_port=htons(port);
        addr.sin_family = AF_INET;
        tcpip_stat=status::TCPIP_INIT;
        addr.sin_addr.s_addr=ip;

    }
    int sock_desc{-1};
    sock_addr addr{0};
    //TODO: ip_t getip()const will be converted template function
    std::string ip_str{""};
    status tcpip_stat{status::TCPIP_DEINIT};
};

}
#endif//__TCPIP_POSIX_H__
