function delay(time)
    lcd.delay(time)
end

function cls()
    lcd.cls()
end

function echo(str)
    lcd.print(str.."\n")
end

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


console = {
    screen=lcd,
    wifi=wifi,
    snd=snd,
    pad=pad,
    pwr=pwr
}

SCRIPT_PATH = "./script/"

SCREEN_WIDTH = 320
SCREEN_HEIGHT = 240

cls()
echo("Hello World !!")

while true do
  
  dofile(SCRIPT_PATH.."sysmenu.lua")
  echo("Restart !")
  delay( 3000 )

end


