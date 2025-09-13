#include "offloading-client.h"
#include "offloading-decision.h"
#include <memory>

namespace Offloading
{

NS_LOG_COMPONENT_DEFINE("OffloadingClientApplication");

OffloadingClientApplication::OffloadingClientApplication(): 
  isRunning(false),
  port(5000),
  packetSize(1024),
  address(),
  intervalSendPacket(ns3::Seconds(1.0)),
  socket(0)
{
}

OffloadingClientApplication::~OffloadingClientApplication()
{
  socket = 0;
}


// TODO: change this function to using on server and client
ns3::Address
OffloadingClientApplication::getAddressAssociateNode()
{
  ns3::Ptr<ns3::Ipv4> ipv4 = this->GetNode()->GetObject<ns3::Ipv4>();
  ns3::Ipv4Address ipv4Address = ipv4->GetAddress(1, 0).GetLocal();

  NS_LOG_DEBUG("Client get address associate node " << ipv4Address);

  return ns3::InetSocketAddress(ipv4Address, port);
}

void
OffloadingClientApplication::StartApplication()
{
  isRunning = true;

  socket = ns3::Socket::CreateSocket(
    this->GetNode(), 
    ns3::UdpSocketFactory::GetTypeId()
  );

  address = this->getAddressAssociateNode();

  socket->Bind();
  SendPacket();
}

void
OffloadingClientApplication::StopApplication()
{
    NS_LOG_DEBUG("Client stopped application");
    isRunning = false;

    if (eventSendPacket.IsPending())
      ns3::Simulator::Cancel(eventSendPacket);

    if (socket)
    {
      NS_LOG_INFO("Client closed the socket");
      socket->Close();
    }
}

void 
OffloadingClientApplication::SetDecisionAlgorithm(std::shared_ptr<IOffloadingDecision> algorithm)
{
  this->algorithm = algorithm;
}

void
OffloadingClientApplication::ScheduleTx() 
{
  NS_LOG_INFO(
    "Schedule transmission packets"
  );

  if (isRunning)
    eventSendPacket = ns3::Simulator::Schedule(intervalSendPacket, &OffloadingClientApplication::SendPacket, this);
}

void
OffloadingClientApplication::SendPacket()
{
  ns3::InetSocketAddress to = this->algorithm->offloadingDecision();

  NS_LOG_INFO(
    "Client send packet with size of " << packetSize << " to " << ns3::InetSocketAddress::ConvertFrom(to).GetIpv4()
  );

  ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet>(packetSize);
  socket->SendTo(packet, 0, to);

  ScheduleTx();
}

}; // namespace Offloading
