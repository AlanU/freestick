local project = workspace:new'freestick'
local WIN_SDK = '10.0.18362.0'

--------------------------------------------------------------------------------
-- Generating for Visual Studio 2019.
--------------------------------------------------------------------------------

print'Generating for Visual Studio 2019.'

--------------------------------------------------------------------------------
-- Create a new project under workspace to compile freestick.
--------------------------------------------------------------------------------

local freestick = project:new'freestick'
  : winsdk( WIN_SDK )
  : defines(
    'TARGET_OS_WIN32, _DEBUG=1, DEBUG=1'
  , 'TARGET_OS_WIN32, NDEBUG=1' )
  : set_include_paths'inc'
  : find_includes'inc'
  : find_sources[[
    src/USB/platform/Windows,
    src/USB/common,
    src/baseClasses,
    src/3rdParty/EELog,
    src/FSDeviceInputEvent.cpp]]
  : target'static'

--------------------------------------------------------------------------------
-- Save out the project for this platform.
--------------------------------------------------------------------------------

platform.save( project )
