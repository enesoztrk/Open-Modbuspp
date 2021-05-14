#include "gtest/gtest.h"

#include "tcpip_posix.h"
#include "tcpip_interface.h"


TEST(Socket, ITcpIpctor) {

    TcpIPStack tcp(1,8888);
    ITcpIp& tcp_ref=tcp;
    ITcpIp::ip_t ip_Addr=tcp_ref.getip();
    ITcpIp::port_t port=tcp_ref.getport();
    ITcpIp::diag status=tcp_ref.get_status_err();


    EXPECT_EQ (1, ip_Addr);
    EXPECT_EQ (htons(8888), port);
    EXPECT_EQ (ITcpIp::status::TCPIP_SOCKFD_INIT, status.stat);
}



TEST(Socket, TcpIPStackctorstring) {

//    TcpIPStack  tcp("192.168.1.1",9999);
//    ITcpIp& tcp_ref=tcp;
//    ITcpIp::ip_t ip_Addr=tcp_ref.getip();
//    ITcpIp::port_t port=tcp_ref.getport();
//    ITcpIp::diag status=tcp_ref.get_status_err();

//    //192.168.1.1
//    EXPECT_EQ (16885952, ip_Addr);
//    EXPECT_EQ (htons(9999), port);
//    EXPECT_EQ ( ITcpIp::status::TCPIP_SOCKFD_INIT, status.stat);
}




TEST(Socket, get_socket_fd) {

//   TcpIPStack  tcp("192.168.1.1",9999);

    //EXPECT_EQ (1,  tcp.get_fd()!=-1);

}



TEST(Socket, bind) {

//   TcpIPStack tcp("127.0.0.1",1111);

//   // EXPECT_EQ (true,  tcp.get_fd()>0);
//    EXPECT_EQ (true,  tcp.bind());
//    //second bind call in row and error is returned
//    EXPECT_EQ (false,  tcp.bind());

}


TEST(Socket, listen) {

//    TcpIPStack  tcp("127.0.0.1",1422);

//    //EXPECT_EQ (true,  tcp.get_fd()>0);
//    EXPECT_EQ (true,  tcp.bind());

//    //second bind call in row and error is returned
//    EXPECT_EQ (true,  tcp.listen(5));
//     EXPECT_EQ (-1,  tcp.accept());
}

TEST(Socket, accept) {

//    TcpIPStack tcp("127.0.0.1",5555);

//    //EXPECT_EQ (true,  tcp.get_fd()>0);
//    EXPECT_EQ (true,  tcp.bind());
//    //second bind call in row and error is returned
//    EXPECT_EQ (-1,  tcp.accept());

}


TEST(Socket, connect) {

//    TcpIPStack tcp("127.0.0.2",5555);

//    ITcpIp& tcp_ref=tcp;
//    //bool ret_val = tcp_ref.connect("127.0.0.1",4444);

//    EXPECT_EQ (true,  tcp_ref.connect("127.0.0.1",4444));



//     EXPECT_EQ (false,  tcp_ref.connect("127.1.1.1",4444));

}

uint32_t enes_send(std::vector<int8_t>& out_data){

    std::cout<<"Size of vector : "<<out_data.size()<<"\n";
    return 5;


}
TEST(Socket, send) {

//    TcpIPStack tcp("192.168.1.114",5555);
//    ITcpIp& tcp_ref=tcp;
//    std::vector<int8_t> test_out_Data{1,2,3,4,5,6,7};

//   bool con= tcp_ref.connect("192.168.1.104",4444);
//    EXPECT_EQ (true,  tcp_ref.send(test_out_Data)>0);



}


TEST(Socket, test) {


// TcpIPStack tcp("127.0.0.1",5555);
// ITcpIp& tcp_ref=tcp;
//  std::vector<int8_t> out_data{1,2,3,4,5,6,7,8,9};
 //tcp_ref.send(out_data);


}

TEST(Socket, vector_queue) {

    using data_packet= std::vector<uint8_t>;

    std::vector<uint8_t> data_packet_test{};
    for(auto i=0;i<10;++i)
    data_packet_test.push_back(i);

    //queues will be created for incoming and outgoing packets
    std::queue<data_packet> m_in_data{};
    std::queue<data_packet> m_out_data{};

    m_in_data.push(data_packet_test);

    std::cout<<"m_in queue empty: "<<m_in_data.empty()<<"\n";
    std::cout<<"m_in queue size: "<<m_in_data.size()<<"\n";

    data_packet& get_data=m_in_data.front();
    uint8_t test;
     for (int i = 0; i < 10; i++) {
           // std::cout << get_data.at(i) << ' ';
             test=get_data.at(i);
             std::cout<<static_cast<int>(get_data.at(i))<<" ";
        }
        std::cout<<"\n";



}


