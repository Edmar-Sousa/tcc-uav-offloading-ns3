#include "offloading-server.h"

namespace Offloading
{

NS_LOG_COMPONENT_DEFINE("OffloadingServerApplication");


OffloadingServerApplication::OffloadingServerApplication():
  port(5000),
  socket(0)
{
}

OffloadingServerApplication::~OffloadingServerApplication()
{
  socket = 0;
}


void
OffloadingServerApplication::StartApplication()
{

  socket = ns3::Socket::CreateSocket(
    this->GetNode(), 
    ns3::UdpSocketFactory::GetTypeId()
  );

  ns3::Ipv4Address addressAny = ns3::Ipv4Address::GetAny();

  socket->Bind(ns3::InetSocketAddress(addressAny, port));

  socket->SetAllowBroadcast(true);
  socket->SetRecvCallback(
    ns3::MakeCallback(&OffloadingServerApplication::handlerReceivedPacket, this)
  );

  NS_LOG_DEBUG("At time " << ns3::Simulator::Now().GetSeconds() << "s server started");
}

void
OffloadingServerApplication::StopApplication()
{
  NS_LOG_DEBUG("At time " << ns3::Simulator::Now().GetSeconds() << "s server stopped");

  if (socket)
  {
    NS_LOG_INFO("At time " << ns3::Simulator::Now().GetSeconds() << "s server socket closed");
    socket->Close();
  }
}




void
OffloadingServerApplication::handlerReceivedPacket(ns3::Ptr<ns3::Socket> socket)
{
  NS_LOG_INFO("At time " << ns3::Simulator::Now().GetSeconds() << "s server received packet");

  ns3::Ptr<ns3::Packet> packet;
  ns3::Address from;

  while ((packet = socket->RecvFrom(from)))
  {
    // this->printReceivedPacket(from, packet);
  }
}


}; // namespace Offloading
