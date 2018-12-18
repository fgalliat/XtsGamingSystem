dofile("./script/screenlib.lua")

lcd.sload(0, "/MARIOBK1.PCT")

local sprites = makeSprite( 2, "/DRMARIO.PCT", 12, 12 )
local sprites2 = makeSprite( 3, "/MARIOSP1.PCT", 16, 16, 0x7e0 )
local pill0L = SpriteGrabb.new(sprites, 0,0) -- left
local pill0R = SpriteGrabb.new(sprites, 1,0) -- right
local pill0D = SpriteGrabb.new(sprites, 2,0) -- down
local pill0U = SpriteGrabb.new(sprites, 3,0) -- up

local mario0 = SpriteGrabb.new(sprites2, 0,0) 
local mario1 = SpriteGrabb.new(sprites2, 1,0)
local mario2 = SpriteGrabb.new(sprites2, 2,0) 


lcd.blitt(0)

  lcd.sback( 0,0,0 )
  mario0:draw( 10, LCD_HEIGHT-mario0.sprt.height - 2 )
  mario1:draw( 30, LCD_HEIGHT-mario0.sprt.height - 2 )
  mario2:draw( 50, LCD_HEIGHT-mario0.sprt.height - 2 )

lcd.blitt(2)

while(true) do
    if pad.read().start then break end
  lcd.delay(50)
end