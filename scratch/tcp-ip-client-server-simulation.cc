#include "ns3/core-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"


#include "ns3/offloading-server.h"
#include "ns3/offloading-client.h"
#include "ns3/offloading-fifo.h"
#include "ns3/offloading-decision.h"

#include <memory>


#define PACKET_SIZE         1024


NS_LOG_COMPONENT_DEFINE("TcpIpClientServerSimulation");




int main() 
{
    const int number_nodes = 2;

    ns3::LogComponentEnable("OffloadingServerApplication", ns3::LOG_LEVEL_ALL);
    ns3::LogComponentEnable("OffloadingClientApplication", ns3::LOG_LEVEL_ALL);

    ns3::NodeContainer nodes;
    nodes.Create(number_nodes);

    ns3::CsmaHelper csma;
    ns3::NetDeviceContainer devices = csma.Install(nodes);


    ns3::InternetStackHelper stack;
    stack.Install(nodes);

    ns3::Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.0.0.0", "255.255.255.0");

    ns3::Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);


    
    ns3::Ptr<Offloading::OffloadingServerApplication> serverApp = ns3::CreateObject<Offloading::OffloadingServerApplication>();
    nodes.Get(0)->AddApplication(serverApp);
    
    
    std::shared_ptr<Offloading::Algorithm::FIFOAlgorithm> fifoAlgorithm = std::make_shared<Offloading::Algorithm::FIFOAlgorithm>();
    ns3::Ptr<Offloading::OffloadingClientApplication> clientApp = ns3::CreateObject<Offloading::OffloadingClientApplication>();

    clientApp->SetDecisionAlgorithm(
        std::static_pointer_cast<Offloading::IOffloadingDecision>(fifoAlgorithm)
    );

    nodes.Get(1)->AddApplication(clientApp);


    serverApp->SetStartTime(ns3::Seconds(1.0));
    clientApp->SetStartTime(ns3::Seconds(1.0));

    serverApp->SetStopTime(ns3::Seconds(10.0));
    clientApp->SetStopTime(ns3::Seconds(10.0));


    ns3::Simulator::Run();
    ns3::Simulator::Stop();

    return 0;
}

