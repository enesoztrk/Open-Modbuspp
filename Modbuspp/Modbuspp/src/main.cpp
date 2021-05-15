#include <iostream>
#include <tcpip_interface.h>
#include <tcpip_posix.h>
#include <string>
using namespace std;

int confd=0;

int main()
{
    TcpIPStack a("192.168.1.114",4444);
    TcpIPStack b("192.168.1.114",8888);
    if(a.bind())
        std::cout<<"bind is successfull\n";
    else
        std::cout<<"bind errno "<<a.get_status_err().err;


    if(a.listen(5))
        std::cout<<"listen is successfull\n";
    else
        std::cout<<"listen errno "<<a.get_status_err().err;

    if(b.connect("192.168.1.104",4343)){
         std::cout<<"connect is successfull\n";
         std::vector<int8_t> out_data{1,2,35,6,6,2};
         if(b.send(out_data)){
              std::cout<<"send is successfull\n";
         }
    }
     else
        std::cout<<"connect errno "<<a.get_status_err().err;



    while (1) {

        confd=a.accept();

        if(confd!=-1){
            std::cout<<"client connected : "<<confd<<"\n";
        }

    }


    return 0;
}
