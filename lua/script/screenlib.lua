--[[
 Xtase lua screen lib
]]--


LCD_WIDTH = 320
LCD_HEIGHT = 240

Sprite = {
    width=16,height=16,slot=0,
    transparent= 0
}
Sprite.__index = Sprite

function Sprite.new(slot, width, height, transparent)
  local self = setmetatable({}, Sprite)
  self.slot = slot
  self.width = width
  self.height = height
  self.transparent = transparent
  return self;
end

function Sprite:draw(x,y, xMat, yMat)
    lcd.ssprite(self.slot, x,y, self.width,self.height, (self.width*xMat), (self.height*yMat), self.transparent)
end

SpriteGrabb = {
    sprt=nil,xMat=16,yMat=0,
}
SpriteGrabb.__index = SpriteGrabb

function SpriteGrabb.new(sprt, xMat, yMat)
    local self = setmetatable({}, SpriteGrabb)
    self.sprt = sprt
    self.xMat = xMat
    self.yMat = yMat
    return self;
  end
  
  function SpriteGrabb:draw(x,y, transparent)
      self.sprt:draw( x,y, self.xMat, self.yMat )
  end


  function makeSprite(num, file, width, height, transparent)
    lcd.sload(num, file)
    return Sprite.new(num, width, height, transparent)
  end