if platform.is'apple'then
  require'cogfile.xcode.lua'
elseif platform.is'microsoft'then
  require'cogfile.vs2019.lua'
end
