#include "gtest/gtest.h"

#include "tcpip_posix.h"
#include "tcpip_interface.h"
#include "posix_socket_mock.hpp"
#include "gmock/gmock.h"
#include "mock_socket_class.h"
using namespace testing;




class PosixSocket: public ::testing::Test {
public:
   PosixSocket( ) {
       // initialization code here


   }

   ~PosixSocket( ) {
       // initialization code here


   }

   void SetUp( ) {
       // code here will execute just before the test ensues

       mock_obj = new  (MockSocket);
       mock_obj_g=mock_obj;
       EXPECT_CALL(*mock_obj,close(_)).Times(AtLeast(1));

   }

   void TearDown( ) {
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be

        delete mock_obj;
        mock_obj_g=nullptr;
        mock_obj=nullptr;



   }
   MockSocket* mock_obj{nullptr};
};


TEST_F (PosixSocket, ITcpIpctor) {
   // testing::Mock::AllowLeak(static_cast<const void *>(&mock_obj_g));

    int sock_fd{1};



    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));
    TcpIPStack tcp(1,8888);
    ITcpIp& tcp_ref=tcp;
    ITcpIp::ip_t ip_Addr=tcp_ref.getip();
    ITcpIp::port_t port=tcp_ref.getport();
    ITcpIp::diag status=tcp_ref.get_status_err();


    EXPECT_EQ (1, ip_Addr);
    EXPECT_EQ (htons(8888), port);
    EXPECT_EQ (ITcpIp::status::TCPIP_INIT_SUCCESS, status.stat);

}



TEST_F(PosixSocket, TcpIPStackctorstring) {
    int sock_fd{1};
    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));




    TcpIPStack  tcp("192.168.1.1",9999);
    ITcpIp& tcp_ref=tcp;
    ITcpIp::ip_t ip_Addr=tcp_ref.getip();
    ITcpIp::port_t port=tcp_ref.getport();
    ITcpIp::diag status=tcp_ref.get_status_err();

    //192.168.1.1
    EXPECT_EQ (16885952, ip_Addr);
    EXPECT_EQ (htons(9999), port);
    EXPECT_EQ ( ITcpIp::status::TCPIP_INIT_SUCCESS, status.stat);
}








TEST_F(PosixSocket, bind) {

    int sock_fd{1};
    //Scenario 1 :all functios are returned with success
    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));

     TcpIPStack tcp("127.0.0.1",1111);


     EXPECT_CALL(*mock_obj,setsockopt(sock_fd,_,_,_,_)).Times(1).WillOnce(Return(0));
     EXPECT_CALL(*mock_obj,bind(_,_,_)).Times(1).WillOnce(Return(0));//ignore bind parameters

     EXPECT_EQ (true,  tcp.bind());
     EXPECT_EQ ( ITcpIp::status::TCPIP_BIND_SUCCESS, tcp.get_status_err().stat);



    //Scenario 2 : bind function fail
    EXPECT_CALL(*mock_obj,bind(_,_,_)).Times(1).WillOnce(Return(-1));//ignore bind parameters
    EXPECT_CALL(*mock_obj,setsockopt(sock_fd,_,_,_,_)).Times(1).WillOnce(Return(0));

    EXPECT_EQ (false,  tcp.bind());
    EXPECT_EQ ( ITcpIp::status::TCPIP_BIND_ERR, tcp.get_status_err().stat);

    //Scenario 3 : setsockopt error
    EXPECT_CALL(*mock_obj,setsockopt(sock_fd,_,_,_,_)).Times(1).WillOnce(Return(-1));

    EXPECT_EQ (false,  tcp.bind());
    EXPECT_EQ ( ITcpIp::status::TCPIP_SETSOCK_ERR, tcp.get_status_err().stat);


}


TEST_F(PosixSocket, listen) {

    int sock_fd{1};
    //Scenario 1 :all functios are returned with success
    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));

    TcpIPStack  tcp("127.0.0.1",1422);

    EXPECT_CALL(*mock_obj,listen(sock_fd,5)).Times(1).WillOnce(Return(0));
    EXPECT_EQ (true,  tcp.listen(5));
    EXPECT_EQ ( ITcpIp::status::TCPIP_LISTEN_SUCCESS, tcp.get_status_err().stat);


    //Scenario 2 : listen function fail
    EXPECT_CALL(*mock_obj,listen(sock_fd,6)).Times(1).WillOnce(Return(-1));


    EXPECT_EQ (false,  tcp.listen(6));
    EXPECT_EQ ( ITcpIp::status::TCPIP_LISTEN_ERR, tcp.get_status_err().stat);




}

TEST_F(PosixSocket, accept) {

    int sock_fd{1};
    //Scenario 1 :all functios are returned with success
    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));

    TcpIPStack tcp("127.0.0.1",5555);

    EXPECT_CALL(*mock_obj,accept(sock_fd,_,_)).Times(1).WillOnce(Return(1));

    EXPECT_EQ (1,  tcp.accept());
    EXPECT_EQ ( ITcpIp::status::TCPIP_ACCEPT_SUCCESS, tcp.get_status_err().stat);

     //Scenario 2 :accept returned error
    EXPECT_CALL(*mock_obj,accept(sock_fd,_,_)).Times(1).WillOnce(Return(-1));

    EXPECT_EQ (-1,  tcp.accept());
    EXPECT_EQ ( ITcpIp::status::TCPIP_ACCEPT_ERR, tcp.get_status_err().stat);
}


TEST_F(PosixSocket, connect) {



    int sock_fd{1};

    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));

    TcpIPStack tcp("127.0.0.2",5555);
    ITcpIp& tcp_ref=tcp;

    //Scenario 1 : First connect function returned error. Second one returns 0
    EXPECT_CALL(*mock_obj,connect(sock_fd,_,_)).Times(2).WillOnce(Return(-1)).WillOnce(Return(0));


    EXPECT_CALL(*mock_obj,poll(_,1,500)).Times(1).WillOnce(Return(0));
    errno=EINPROGRESS;

    EXPECT_EQ (true,  tcp_ref.connect("127.1.1.1",4444));
    EXPECT_EQ ( ITcpIp::status::TCPIP_CONNECTED, tcp.get_status_err().stat);

    EXPECT_EQ (true,tcp_ref.close());
    //Scenario 2 :all functios are returned with success
    EXPECT_CALL(*mock_obj,connect(sock_fd,_,_)).Times(1).WillOnce(Return(0));


    EXPECT_EQ (true,  tcp_ref.connect("127.0.0.1",4444));
    EXPECT_EQ ( ITcpIp::status::TCPIP_CONNECTED, tcp.get_status_err().stat);

    EXPECT_EQ (true,tcp_ref.close());
    //Scenario 3 : connect functions return error
    EXPECT_CALL(*mock_obj,connect(sock_fd,_,_)).Times(2).WillOnce(Return(-1)).WillOnce(Return(-1));


    EXPECT_CALL(*mock_obj,poll(_,1,500)).Times(1).WillOnce(Return(0));
    errno=EINPROGRESS;

    EXPECT_EQ (false,  tcp_ref.connect("127.1.1.1",4444));
    EXPECT_EQ ( ITcpIp::status::TCPIP_NOT_CONNECTED, tcp.get_status_err().stat);

    //Scenario 4 : connect function return error and errno is not EINPROGRESS
    EXPECT_CALL(*mock_obj,connect(sock_fd,_,_)).Times(1).WillOnce(Return(-1));
    errno=ECONNREFUSED;

    EXPECT_EQ (false,  tcp_ref.connect("127.1.1.1",4444));
    EXPECT_EQ ( ITcpIp::status::TCPIP_NOT_CONNECTED, tcp.get_status_err().stat);

}


TEST_F(PosixSocket, send) {
    int sock_fd{1};

    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));

    TcpIPStack tcp("127.0.0.2",5555);
    ITcpIp& tcp_ref=tcp;

    std::vector<int8_t> test_out_Data{1,2,3,4,5,6,7};

    //Scenario 1 :all functios are returned with success
   EXPECT_CALL(*mock_obj,send(sock_fd,(char *)(&test_out_Data[0]), test_out_Data.size(), 0)).
           Times(1).WillOnce(Return(3));

   EXPECT_CALL(*mock_obj,connect(sock_fd,_,_)).Times(1).WillOnce(Return(0));

   EXPECT_EQ (true,  tcp_ref.connect("127.0.0.1",4444));
   EXPECT_EQ (3,  tcp_ref.send(test_out_Data));
   EXPECT_EQ ( ITcpIp::status::TCPIP_SEND_SUCCESS, tcp.get_status_err().stat);

   //Scenario 2 :send function returns error
   EXPECT_CALL(*mock_obj,send(sock_fd,(char *)(&test_out_Data[0]), test_out_Data.size(), 0)).
           Times(1).WillOnce(Return(-1));
   EXPECT_EQ (0,  tcp_ref.send(test_out_Data));
   EXPECT_EQ ( ITcpIp::status::TCPIP_SEND_ERR, tcp.get_status_err().stat);



}


TEST_F(PosixSocket, receive) {
    int sock_fd{1};

    EXPECT_CALL(*mock_obj,socket(AF_INET , SOCK_STREAM , 0)).Times(1).WillOnce(Return(sock_fd));
    EXPECT_CALL(*mock_obj,fcntl(sock_fd , F_SETFL, O_NONBLOCK)).Times(1).WillOnce(Return(0));

    TcpIPStack tcp("127.0.0.2",5555);
    ITcpIp& tcp_ref=tcp;



}

//TEST(Socket, vector_queue) {

//    using data_packet= std::vector<uint8_t>;

//    std::vector<uint8_t> data_packet_test{};
//    for(auto i=0;i<10;++i)
//    data_packet_test.push_back(i);

//    //queues will be created for incoming and outgoing packets
//    std::queue<data_packet> m_in_data{};
//    std::queue<data_packet> m_out_data{};

//    m_in_data.push(data_packet_test);

//    std::cout<<"m_in queue empty: "<<m_in_data.empty()<<"\n";
//    std::cout<<"m_in queue size: "<<m_in_data.size()<<"\n";

//    data_packet& get_data=m_in_data.front();
//    uint8_t test;
//     for (int i = 0; i < 10; i++) {
//           // std::cout << get_data.at(i) << ' ';
//             test=get_data.at(i);
//             std::cout<<static_cast<int>(get_data.at(i))<<" ";
//        }
//        std::cout<<"\n";



//}


