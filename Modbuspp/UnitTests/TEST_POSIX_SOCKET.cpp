#include "gtest/gtest.h"
#include "../Modbuspp/inc/tcpip_interface.h"


TEST(Socket, ITcpIpctor) {

    mb::ITcpIp tcp(1,8888);

    mb::ip_t ip_Addr=tcp.getip();
    mb::port_t port=tcp.getport();
    AbsTcpipmngmt::diag::status status=tcp.getstatus();


    EXPECT_EQ (1, ip_Addr);
    EXPECT_EQ (htons(8888), port);
    EXPECT_EQ (AbsTcpipmngmt::diag::status::TCPIP_INIT, status);
}



TEST(Socket, ITcpIpctorstring) {

    mb::ITcpIp tcp("192.168.1.1",9999);

    mb::ip_t ip_Addr=tcp.getip();
    mb::port_t port=tcp.getport();
    AbsTcpipmngmt::diag::status status=tcp.getstatus();

    //192.168.1.1
    EXPECT_EQ (16885952, ip_Addr);
    EXPECT_EQ (htons(9999), port);
    EXPECT_EQ (AbsTcpipmngmt::diag::status::TCPIP_INIT, status);
}




TEST(Socket, get_socket_fd) {

    mb::ITcpIp tcp("192.168.1.1",9999);

    EXPECT_EQ (1,  tcp.get_fd()!=-1);

}



TEST(Socket, bind) {

    mb::ITcpIp tcp("127.0.0.1",1111);

    EXPECT_EQ (true,  tcp.get_fd()>0);
    EXPECT_EQ (true,  tcp.bind());
    //second bind call in row and error is returned
    EXPECT_EQ (false,  tcp.bind());

}


TEST(Socket, listen) {

    mb::ITcpIp tcp("127.0.0.1",1422);

    EXPECT_EQ (true,  tcp.get_fd()>0);
    EXPECT_EQ (true,  tcp.bind());

    //second bind call in row and error is returned
    EXPECT_EQ (true,  tcp.listen(5));
     EXPECT_EQ (-1,  tcp.accept());
}

TEST(Socket, accept) {

    mb::ITcpIp tcp("127.0.0.1",5555);

    EXPECT_EQ (true,  tcp.get_fd()>0);
    EXPECT_EQ (true,  tcp.bind());
    //second bind call in row and error is returned
    EXPECT_EQ (-1,  tcp.accept());

}

