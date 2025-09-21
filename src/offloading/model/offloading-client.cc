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
  intervalSendPacket(ns3::Seconds(1.0)),
  socket(0)
{
}

OffloadingClientApplication::~OffloadingClientApplication()
{
  socket = 0;
}

void
OffloadingClientApplication::StartApplication()
{
  isRunning = true;

  socket = ns3::Socket::CreateSocket(
    this->GetNode(), 
    ns3::UdpSocketFactory::GetTypeId()
  );

  socket->Bind();
  SendPacket();
}

void
OffloadingClientApplication::StopApplication()
{
    NS_LOG_DEBUG("At time " << ns3::Simulator::Now().GetSeconds() << "s client stop the application");
    isRunning = false;

    if (eventSendPacket.IsPending())
      ns3::Simulator::Cancel(eventSendPacket);

    if (socket)
    {
      NS_LOG_INFO("At time " << ns3::Simulator::Now().GetSeconds() << "s client close socket");
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
  NS_LOG_DEBUG("At time " << ns3::Simulator::Now().GetSeconds() << "s client schedule transmission packet");

  if (isRunning)
    eventSendPacket = ns3::Simulator::Schedule(intervalSendPacket, &OffloadingClientApplication::SendPacket, this);
}

void
OffloadingClientApplication::SendPacket()
{
  ns3::Ipv4Address address = this->algorithm->offloadingDecision();
  ns3::InetSocketAddress addressToSend = ns3::InetSocketAddress(address, port);

  NS_LOG_INFO(
    "Client send packet with size of " << packetSize << " to " << ns3::InetSocketAddress::ConvertFrom(addressToSend).GetIpv4()
  );

  ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet>(packetSize);
  socket->SendTo(packet, 0, addressToSend);

  ScheduleTx();
}

}; // namespace Offloading
