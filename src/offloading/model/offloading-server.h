#ifndef __OFFLOADING_SERVER_H__
#define __OFFLOADING_SERVER_H__

#include "ns3/core-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include <cstdint>


namespace Offloading 
{

class OffloadingServerApplication : public ns3::Application
{
private:
  uint16_t port;

  ns3::Ptr<ns3::Socket> socket;
  ns3::Address address;

  void StartApplication() override;
  void StopApplication() override;

  void handlerReceivedPacket(ns3::Ptr<ns3::Socket> socket);
  void printReceivedPacket(const ns3::Address & from, ns3::Ptr<ns3::Packet> packet);


  ns3::InetSocketAddress getAddressAssociateNode() const;

public:

  OffloadingServerApplication();
  virtual ~OffloadingServerApplication();

};


}


#endif
