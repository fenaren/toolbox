#include "NoopSignalManagerImpl.hpp"

//==============================================================================
NoopSignalManagerImpl::NoopSignalManagerImpl()
{
}

//==============================================================================
NoopSignalManagerImpl::~NoopSignalManagerImpl()
{
}

//==============================================================================
bool NoopSignalManagerImpl::registerSignal(int sig)
{
    return false;
}

//==============================================================================
void NoopSignalManagerImpl::signal(int sig)
{
}

//==============================================================================
bool NoopSignalManagerImpl::isSignalDelivered(int sig)
{
    return false;
}

//==============================================================================
void NoopSignalManagerImpl::getSupportedSignals(
    std::unordered_set<int>& supported_signals)
{
}

//==============================================================================
void NoopSignalManagerImpl::getSignalName(int sig, std::string& signal_name)
{
}
