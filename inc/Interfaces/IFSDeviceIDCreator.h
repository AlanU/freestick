#pragma once

namespace freestick {
    class IFSDeviceIDCreator
    {
    public:
        virtual elementID getNextID() = 0;
    };
}
