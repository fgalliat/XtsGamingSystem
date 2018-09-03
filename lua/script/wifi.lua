print( wifi.up() ); 

print( wifi.down() ); 

print( wifi.restart() ); 

print( wifi.info() );

print( wifi.down() ); 

print( wifi.info() );

print( wifi.list() );

print( wifi.new("MyBox", "mySecret") );

print( wifi.rm("MyBox") );

-- Compatibility: Lua-5.1
function split(str, pat)
    local t = {}  -- NOTE: use {n = 0} in Lua-5.0
    local fpat = "(.-)" .. pat
    local last_end = 1
    local s, e, cap = str:find(fpat, 1)
    while s do
       if s ~= 1 or cap ~= "" then
          table.insert(t,cap)
       end
       last_end = e+1
       s, e, cap = str:find(fpat, last_end)
    end
    if last_end <= #str then
       cap = str:sub(last_end)
       table.insert(t, cap)
    end
    return t
 end

wifi.up();

local connInfos = split( wifi.info(), ':' );
local wifiConnected = connInfos[1];
local wifiESSID = connInfos[2];
local wifiIP = connInfos[3];
print( "Connected > ".. wifiConnected );
print( "ESSID     > ".. wifiESSID );
print( "IP        > ".. wifiIP );