

#include "hotrod/impl/operations/ReplaceOperation.h"
#include "hotrod/sys/types.h"

namespace infinispan {
namespace hotrod {
namespace operations {

using infinispan::hotrod::protocol::Codec;
using namespace infinispan::hotrod::transport;

ReplaceOperation::ReplaceOperation(
    const Codec& _codec, HR_SHARED_PTR<transport::TransportFactory> _transportFactory, const hrbytes& _key,
    const hrbytes& _cacheName, uint32_t _topologyId, uint32_t _flags,
    const hrbytes& _value, uint32_t _lifespan, uint32_t _maxIdle) :
        AbstractKeyValueOperation<hrbytes>(
            _codec, _transportFactory, _key, _cacheName, _topologyId,
            _flags, _value, _lifespan, _maxIdle)
{}

hrbytes ReplaceOperation::executeOperation(Transport& transport)
{
    hrbytes previousValue;
    uint8_t status = sendPutOperation(
        transport, REPLACE_REQUEST, REPLACE_RESPONSE);
    if (status == NO_ERROR_STATUS || status == NOT_PUT_REMOVED_REPLACED_STATUS) {
        previousValue =
            AbstractKeyValueOperation<hrbytes>::returnPossiblePrevValue(transport);
    }
    return previousValue;
}


}}} // namespace infinispan::hotrod::operations
