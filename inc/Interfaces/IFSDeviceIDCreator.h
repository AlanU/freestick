#pragma once

namespace freestick {
    class IFSDeviceIDCreator
    {
    public:
        virtual ElementID getNextID() = 0;
    };
}
