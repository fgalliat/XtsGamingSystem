function delay(time)
    lcd.delay(time)
end

function cls()
    lcd.cls()
end

function echo(str)
    lcd.print(str.."\n")
end

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


