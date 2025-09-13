
#include "offloading-fifo.h"


namespace Offloading 
{

namespace Algorithm {

    FIFOAlgorithm::FIFOAlgorithm()
    {}

    FIFOAlgorithm::~FIFOAlgorithm()
    {}


    ns3::InetSocketAddress
    FIFOAlgorithm::offloadingDecision()
    {
        return ns3::Ipv4Address::GetBroadcast();
    }
}

}
