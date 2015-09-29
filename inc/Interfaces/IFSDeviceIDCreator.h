#pragma once

namespace freestick {
    class IFSDeviceIDCreator
    {
    public:
        virtual DeviceID getNextID() = 0;
    };
}
