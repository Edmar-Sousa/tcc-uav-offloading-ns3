#ifndef  __OFFLOADING_DECISION_H__
#define  __OFFLOADING_DECISION_H__

#include "ns3/core-module.h"
#include "ns3/internet-module.h"


namespace Offloading 
{

class IOffloadingDecision 
{

  public:
    virtual ~IOffloadingDecision() {};
    virtual ns3::InetSocketAddress offloadingDecision() = 0;
};

};


#endif