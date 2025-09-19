#include "offloading-server.h"

namespace Offloading
{

NS_LOG_COMPONENT_DEFINE("OffloadingServerApplication");


OffloadingServerApplication::OffloadingServerApplication():
  port(5000),
  socket(0),
  address()
{
}

OffloadingServerApplication::~OffloadingServerApplication()
{
  socket = 0;
}


ns3::InetSocketAddress
OffloadingServerApplication::getAddressAssociateNode() const
{
  ns3::Ipv4Address addressAny = ns3::Ipv4Address::GetAny();
  
  NS_LOG_DEBUG("Server get address associate node " << addressAny);
  
  return ns3::InetSocketAddress(addressAny, port);
}

void
OffloadingServerApplication::StartApplication()
{

  socket = ns3::Socket::CreateSocket(
    this->GetNode(), 
    ns3::UdpSocketFactory::GetTypeId()
  );


  socket->Bind(this->getAddressAssociateNode());
  socket->SetAllowBroadcast(true);
  socket->SetRecvCallback(
    ns3::MakeCallback(&OffloadingServerApplication::handlerReceivedPacket, this)
  );

  NS_LOG_DEBUG("Server started and waiting by packets");
}

void
OffloadingServerApplication::StopApplication()
{
  NS_LOG_DEBUG("Server with address " << this->getAddressAssociateNode() << " stopped");

  if (socket)
  {
    NS_LOG_INFO("Server closed the socket");
    socket->Close();
  }
}



void
OffloadingServerApplication::printReceivedPacket(
  const ns3::Address& from,
  ns3::Ptr<ns3::Packet> packet
)
{
  if (!ns3::InetSocketAddress::IsMatchingType(from))
  {
    NS_LOG_DEBUG("Server received " << packet->GetSize() << " bytes");
    return;
  }

  ns3::Ipv4Address ipv4AddressFrom = ns3::InetSocketAddress::ConvertFrom(from).GetIpv4();
  NS_LOG_DEBUG("Server received " << packet->GetSize() << " bytes from " << ipv4AddressFrom);
}


void
OffloadingServerApplication::handlerReceivedPacket(ns3::Ptr<ns3::Socket> socket)
{
  NS_LOG_DEBUG("Server received packet on socket");

  ns3::Ptr<ns3::Packet> packet;
  ns3::Address from;

  while ((packet = socket->RecvFrom(from)))
  {
    // this->printReceivedPacket(from, packet);
  }
}


}; // namespace Offloading
