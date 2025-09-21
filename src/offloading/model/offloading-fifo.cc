
#include "offloading-fifo.h"


namespace Offloading 
{

namespace Algorithm {

    FIFOAlgorithm::FIFOAlgorithm()
    {}

    FIFOAlgorithm::~FIFOAlgorithm()
    {}


    ns3::Ipv4Address
    FIFOAlgorithm::offloadingDecision()
    {
        // return ns3::Ipv4Address::GetBroadcast();
        return ns3::Ipv4Address("10.0.0.1");
    }
}

}
