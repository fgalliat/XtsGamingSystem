dofile("./script/screenlib.lua")

lcd.sload(0, "/MARIOBK1.PCT")

local sprites = makeSprite( 2, "/DRMARIO.PCT", 12, 12 )
local sprites2 = makeSprite( 3, "/MARIOSP1.PCT", 16, 16, 0x7e0 )
local pill0L = SpriteGrabb.new(sprites, 0,0) -- left
local pill0R = SpriteGrabb.new(sprites, 1,0) -- right
local pill0D = SpriteGrabb.new(sprites, 2,0) -- down
local pill0U = SpriteGrabb.new(sprites, 3,0) -- up

-- _____________________________________
local mario0 = SpriteGrabb.new(sprites2, 0,0) 
local mario1 = SpriteGrabb.new(sprites2, 1,0)
local mario2 = SpriteGrabb.new(sprites2, 2,0) 

local mario3 = SpriteGrabb.new(sprites2, 19-0,0) 
local mario4 = SpriteGrabb.new(sprites2, 19-1,0)
local mario5 = SpriteGrabb.new(sprites2, 19-2,0) 

local mariosLR = { mario0, mario1, mario2 }
local mariosRL = { mario3, mario4, mario5 }

-- _____________________________________
local Mario = {}
Mario.__index = Mario

function Mario.new()
    local self = setmetatable({}, Mario)
    self.step = 0
    self.nbStep = 2
    self.dir = 1
    self.running = false
    self.jump = false
    self.jumpMod = 0

    self.x = 10
    self.y = LCD_HEIGHT-mario0.sprt.height - 2

	self.sprtG = mariosLR[0+1] 

    return self;
end

function Mario:isMoving()
	return self.jump or self.jumpMod ~= 0 or self.running
end

function Mario:run(_run, dir)
	local idx = 0
	self.dir = dir
    self.running = _run
	if ( self.running ) then idx = self.step end
    if ( self.dir == 1 ) then 
        self.sprtG = mariosLR[idx+1] 
    else
        self.sprtG = mariosRL[idx+1] 
    end	
end

function Mario:draw()
    if ( self.jump and self.jumpMod < 12 ) then
        self.jumpMod = self.jumpMod + 3*2
    elseif ( self.jump and self.jumpMod >= 12 ) then
    	self.jump = false
    	self.jumpMod = self.jumpMod - 4*2
    elseif ( not self.jump and self.jumpMod > 0 ) then
        self.jumpMod = self.jumpMod - 4*2
    end

    if self.jumpMod < 0 then
        self.jumpMod = 0 
    end

    if ( self.running and self.dir == 0 and self.x > 0 ) then
        self.x = self.x - 4*2
    elseif ( self.running and self.dir == 1 and self.x < LCD_WIDTH-16 ) then
        self.x = self.x + 4*2
    end

    self.sprtG:draw( self.x,self.y-self.jumpMod )
    self.step = self.step+1
    self.step = self.step%self.nbStep
end

-- -======= Level Drawing ===========-

function readLevel(lvl) 
    -- defines mario_lvl array
    dofile("./script/mario_lvl".. lvl ..".lua")
end

local mario_spErr = SpriteGrabb.new(sprites2, 1,5) 
local mario_spGround = SpriteGrabb.new(sprites2, 5,2) 
local mario_spCloud = SpriteGrabb.new(sprites2, 3,2) 
local mario_spBreakBr = SpriteGrabb.new(sprites2, 0,1) 
local mario_spTree = SpriteGrabb.new(sprites2, 4,1) 
local mario_spTreeHead = SpriteGrabb.new(sprites2, 4,0) 
local mario_spFence = SpriteGrabb.new(sprites2, 2,3) 
local mario_spMonoBr = SpriteGrabb.new(sprites2, 1,1) 
local mario_spItemBr = SpriteGrabb.new(sprites2, 0,3) 
local mario_spUnbreakBr = SpriteGrabb.new(sprites2, 1,2) 

local mario_spArmaEn = SpriteGrabb.new(sprites2, 0,5) 

function getLvlBloc(ch)
    if ( ch == ' ' ) then return nil; end
    if ( ch == 'g' ) then return mario_spGround; end
    if ( ch == 'C' ) then return mario_spCloud; end
    if ( ch == 'B' ) then return mario_spBreakBr; end
    if ( ch == 't' ) then return mario_spTree; end
    if ( ch == 'T' ) then return mario_spTreeHead; end
    if ( ch == '#' ) then return mario_spFence; end
    if ( ch == 'b' ) then return mario_spMonoBr; end
    if ( ch == '?' ) then return mario_spItemBr; end
    if ( ch == 'U' ) then return mario_spUnbreakBr; end
    if ( ch == '3' ) then return mario_spArmaEn; end
    return mario_spErr;
end

function drawLevel()
    local x,y,line,ch,sprt
    for y=1,15 do
        line = mario_lvl[y]
        for x=1,20 do
            ch = string.sub(line, x, x)
            sprt = getLvlBloc(ch)
            if ( sprt ~= nil ) then 
                sprt:draw( (x-1)*16, (y-1)*16 )
            end
        end
    end
end

-- -======= Game ===========-

local mario = Mario.new()
readLevel(1)

local screenDirty = true
local frameCounter = 0

lcd.sback( 0,0,0 )
drawLevel()

while(true) do
    
    local pads = pad.read()
        mario.running = false;
	    mario.jump = false;
	    
    -- if pads.atLeastOne then
        if pads.start then break end

        if pads.left then mario:run(true,0); 
        elseif pads.right then mario:run(true,1) 
        end
        if (pads.up or pads.A) then mario.jump = true; mario.running = false; end
    -- else
    --     mario.running = false;
    --     mario.jump = false;
    -- end
    if ( mario:isMoving() ) then
    	screenDirty = true
    else
    	mario:run(false, mario.dir);
    	lcd.delay(5)
    end

    if ( screenDirty and frameCounter%2 == 0) then
	    lcd.blitt(0)
	    --lcd.sback( 0,0,0 )
	    lcd.ssprite( 0, mario.x-4,mario.y-16, 20,32, mario.x-4,mario.y-16 )
	    
	    mario:draw()
	    lcd.blitt(2)
	    screenDirty = false
    end

	frameCounter = frameCounter + 1
  --lcd.delay(5)
end