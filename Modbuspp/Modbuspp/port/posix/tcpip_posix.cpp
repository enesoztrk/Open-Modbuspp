/**
* ============================================================================
* @file tcpip_posix.cpp
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

#include "tcpip_posix.h"

using namespace port;
/**
 * @brief
 *
 *
 * @param none
 * @return
 * @note
 * @warning Warning.
 */
LinuxTcpIPStack::~LinuxTcpIPStack()
{
        std::cout<<__PRETTY_FUNCTION__<<"\n";
            if(sock_desc>0 && this->close())
            {
                 sock_desc=-1;
                 addr={};
                 ip_str="";
                 b_is_connection_on=false;
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
LinuxTcpIPStack::LinuxTcpIPStack(ip_t ip,port_t port):addr{}{
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
 LinuxTcpIPStack::LinuxTcpIPStack(std::string ip_str,port_t port):addr{}{

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


/**
 * @brief
 *
 *
 * @param none
 * @return
 * @note
 * @warning Warning.
 */
sock_fd LinuxTcpIPStack::vget_fd() {
    sock_desc = ::socket(AF_INET , SOCK_STREAM , 0);
    auto ret_val{-1};

    if(sock_desc==-1){
        tcpip_diag.stat=status::TCPIP_SOCKFD_ERR;
        tcpip_diag.err=errno;
    }
    else{
     tcpip_diag.stat=status::TCPIP_SOCKFD_INIT;
     tcpip_diag.err=0;
        /*set file descriptor is set as non-blocking file */
        ret_val= ::fcntl(sock_desc,F_SETFL, O_NONBLOCK);

    }
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

bool LinuxTcpIPStack::vis_cnxn_on()const{

    return b_is_connection_on;

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
bool LinuxTcpIPStack::vconnect(std::string ip_str,port_t port){
    std::cout<<__PRETTY_FUNCTION__<<"\n";
    bool b_ret_val{false};

    struct pollfd cnxn_pollfd{0};
    struct sockaddr_in server_s{};

    /*server struct definition*/
    server_s.sin_addr.s_addr = ::inet_addr(ip_str.c_str());
    server_s.sin_family = AF_INET;
    server_s.sin_port = htons( port );

    if(sock_desc>0 && false==vis_cnxn_on()){



            if(0==(::connect(sock_desc , (struct sockaddr *)&server_s , sizeof(server_s)))){
                std::cout<<"Connected\n";
                b_ret_val=true;
                b_is_connection_on=true;

            }

            /*it is ok for non-blocking I/O*/
             if ( errno == EINPROGRESS)
              {

                 cnxn_pollfd.fd = sock_desc;
                 cnxn_pollfd.events = POLLOUT;
                 int16_t i16_ret_val=::poll(&cnxn_pollfd, 1, 500);

                 if ((i16_ret_val>=0) && (cnxn_pollfd.revents & POLLOUT)) {


                     /*retry to connect*/
                     if(0==(::connect(sock_desc , (struct sockaddr *)&server_s , sizeof(server_s)))){
                         std::cout<<"Connected EINPROGRESS\n";
                         b_ret_val=true;
                         b_is_connection_on=true;
                     }
                     else{
                        tcpip_diag.stat=status::TCPIP_NOT_CONNECTED;
                        tcpip_diag.err=errno;
                     }

                      }


              }
             else{

                 tcpip_diag.stat=status::TCPIP_NOT_CONNECTED;
                 tcpip_diag.err=errno;

             }


    }

    return b_ret_val;

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

uint32_t LinuxTcpIPStack::vsend(std::vector<int8_t>& vec_out_data){
    std::cout<<__PRETTY_FUNCTION__<<"\n";
    ssize_t ss_ret_val{0};


        if((vec_out_data.size()>0) && (true==vis_cnxn_on()))
        {
                ss_ret_val = ::send(sock_desc, (char *)(&vec_out_data[0]), vec_out_data.size(), 0);

                if(ss_ret_val!=-1){
                     tcpip_diag.stat=status::TCPIP_SEND_SUCCESS;
                     tcpip_diag.err=0;
                }
                else{
                    tcpip_diag.stat=status::TCPIP_SEND_ERR;
                     tcpip_diag.err=errno;
                     ss_ret_val=0;/*0 bytes sent*/
                }

        }

    return ss_ret_val;
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
 bool LinuxTcpIPStack::vreceive(){
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
bool LinuxTcpIPStack::vbind(){
     std::cout<<__PRETTY_FUNCTION__<<"\n";
     bool ret_val=false;



     set_sockopt(SOL_SOCKET,SO_REUSEADDR);


     if(0==(::bind(sock_desc, (struct sockaddr *)&addr, sizeof(addr)))){
            tcpip_diag.stat=status::TCPIP_BIND_SUCCESS;
            ret_val=true;
     }
     else
     {     tcpip_diag.stat=status::TCPIP_BIND_ERR;
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
bool LinuxTcpIPStack::vlisten(const unsigned int max_conn){
    std::cout<<__PRETTY_FUNCTION__<<"\n";

    bool ret_val=false;

    if(0==(::listen(sock_desc,max_conn))){
           tcpip_diag.stat=status::TCPIP_LISTEN_SUCCESS;
           ret_val=true;
    }
    else
    {     tcpip_diag.stat=status::TCPIP_LISTEN_ERR;
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
sock_fd LinuxTcpIPStack::vaccept(){

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
bool LinuxTcpIPStack::vclose(){
    std::cout<<__PRETTY_FUNCTION__<<"\n";
    if(sock_desc>0)
    {
        ::close(sock_desc);
         b_is_connection_on=false;
    }
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
ITcpIp::ip_t LinuxTcpIPStack::vgetip()const{

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
ITcpIp::port_t LinuxTcpIPStack::vgetport()const {

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
ITcpIp::diag LinuxTcpIPStack::vget_status_err()const {
    return this->tcpip_diag;
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
void LinuxTcpIPStack::init_socket(ip_t ip,port_t port){

    addr.sin_port=htons(port);
    addr.sin_family = AF_INET;
    tcpip_diag.stat=status::TCPIP_INIT;
    addr.sin_addr.s_addr=ip;
    sock_desc=vget_fd();
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
void LinuxTcpIPStack::set_sockopt(int level,int optnum){
    auto optval = 1;

    if(0==(::setsockopt(sock_desc, level, optnum, &optval, sizeof(optval)))){
           tcpip_diag.stat=status::TCPIP_SETSOCK_SUCCESS;

    }
    else
    {     tcpip_diag.stat=status::TCPIP_SETSOCK_ERR;
          tcpip_diag.err=errno;

    }

}
