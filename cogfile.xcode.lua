local project = workspace:new'freestick'

--------------------------------------------------------------------------------
-- Generating for Visual Studio 2019.
--------------------------------------------------------------------------------

print'Generating for Xcode 11'

--------------------------------------------------------------------------------
-- Create a new project under workspace to compile freestick.
--------------------------------------------------------------------------------

local freestick = project:new'freestick'
  : disable'arc'
  : defines(
    'TARGET_OS_OSX, _DEBUG=1, DEBUG=1'
  , 'TARGET_OS_OSX, NDEBUG=1' )
  : set_include_paths'usr/share/freestick/inc'
  : find_includes'usr/share/freestick/inc'
  : find_sources[[
    usr/share/freestick/src/USB/platform/MacOSX,
    usr/share/freestick/src/USB/platform/iOS,
    usr/share/freestick/src/USB/common,
    usr/share/freestick/src/baseClasses,
    usr/share/freestick/src/3rdParty/EELog,
    usr/share/freestick/src/3rdParty/Mac,
    usr/share/freestick/src/FSDeviceInputEvent.cpp]]
  : target'static'

--------------------------------------------------------------------------------
-- Save out the project for this platform.
--------------------------------------------------------------------------------

platform.save( project )
