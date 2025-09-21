#ifndef __OFFLOADING_CLIENT_H__
#define __OFFLOADING_CLIENT_H__

#include "offloading-decision.h"
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"

#include <memory>

namespace Offloading
{

class OffloadingClientApplication : public ns3::Application
{
  
  private:
    bool isRunning;

    uint16_t port;
    uint32_t packetSize;

    std::shared_ptr<IOffloadingDecision> algorithm;

    ns3::Time intervalSendPacket;
    ns3::EventId eventSendPacket;
    ns3::Ptr<ns3::Socket> socket;


    void StartApplication() override;
    void StopApplication() override;

    ns3::Address getAddressAssociateNode();

    void SendPacket();
    void ScheduleTx();

  public:
    OffloadingClientApplication();
    virtual ~OffloadingClientApplication();

    void SetDecisionAlgorithm(std::shared_ptr<IOffloadingDecision> algorithm);
};
} // namespace Offloading

#endif