stopped = true

consoleStartTime = os.clock()
timer = {
   -- consoleStartTime = os.clock(),

   getMilliSecCounter = function()
     return os.clock() - consoleStartTime;
   end
}





function start()
  lastKeyDown = 0
  stopped = false
  engineInit() 
--[[ 
  on.timer = tick 
  quit = function() 
    stopped = true 
    timer.stop() 
  end 
  -- 50ms period in seconds 
  timer.start(0.015) 
]]--
  
end 

roadCpt = 0
steering = 0
camera = { x=0, y = 0, z = 0 };

--local xRoad = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,3,4,4,5,6,6,7,8,9,9,10,10,11,12,12,12,13,14,14,15,15,15,15,15,15,15,15,15,15,15,12,14,9,10,3,4,-1,1,-3,-1,-5,-3,-7,-5,-8,-6,-9,-7,-7,-7,-7,-10,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-7,-7,-7,-7,-7,-4,-4,-2,-1,0,1,3,4,5,6,6,6,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,5,7,7,3,5,5,2,4,0,2,-3,-1,-4,-3,-8,-6,-9,-8,-12,-11,-16,-14,-14,-20,-18,-23,-21,-21,-26,-24,-27,-26,-29,-28,-31,-29,-32,-30,-30,-30,-30,-30,-33,-31,-31,-34,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-29,-28,-28,-28,-27,-25,-24,-23,-22,-22,-21,-20,-19,-18,-17,-16,-16,-15,-14,-14,-13,-12,-11,-10,-8,-8,-6,-4,-3,-2,-1,-1,-1,0,1,1,1,1,2,2,2,2,2,2,2,3,0,2,2,-2,0,0,-3,-1,-4,-3,-6,-4,-7,-6,-9,-7,-7,-12,-10,-10,-13,-12,-12,-12,-15,-13,-13,-13,-16,-14,-14,-14,-14,-14,-14,-14,-14,-14,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-12,-12,-11,-11,-11,-11,-14,-12,-12,-16,-14,-21,-19,-24,-22,-25,-23,-26,-24,-27,-25,-25,-28,-26,-26,-29,-27,-27,-27,-26,-26,-25,-24,-23,-22,-20,-18,-16,-13,-12,-11,-11,-11,-11,-10,-10,-10,-10,-10,-9,-9,-9,-9,-9,-9,-9,-9,-13,-11,-18,-16,-20,-18,-21,-19,-19,-19,-19,-22,-20,-19,-19,-19,-17,-17,-16,-16,-16,-16,-16,-16,-16}
local xRoad = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,5,5,6,7,8,8,9,9,10,11,11,11,12,13,13,14,14,14,14,14,14,14,14,14,14,14,13,13,12,5,5,2,1,0,-1,-2,-4,-4,-5,-6,-7,-7,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-8,-8,-5,-5,-3,-2,-1,0,2,3,4,5,5,5,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,6,5,4,4,3,3,1,1,0,-2,-3,-4,-7,-7,-8,-9,-11,-12,-13,-15,-15,-19,-19,-22,-22,-22,-25,-25,-26,-27,-28,-29,-30,-30,-31,-31,-31,-31,-31,-31,-32,-32,-32,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-32,-32,-32,-32,-32,-32,-32,-32,-32,-32,-30,-29,-29,-29,-28,-26,-25,-24,-23,-23,-22,-21,-20,-19,-18,-17,-17,-16,-15,-15,-14,-13,-12,-11,-9,-9,-7,-5,-4,-3,-2,-2,-2,-1,0,0,0,0,1,1,1,1,1,1,1,2,1,1,1,0,-1,-1,-2,-2,-3,-4,-5,-5,-6,-7,-8,-8,-8,-11,-11,-11,-12,-13,-13,-13,-14,-14,-14,-14,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-13,-13,-12,-12,-12,-12,-13,-13,-13,-14,-15,-20,-20,-23,-23,-24,-24,-25,-25,-26,-26,-26,-27,-27,-27,-28,-28,-28,-28,-27,-27,-26,-25,-24,-23,-21,-19,-17,-14,-13,-12,-12,-12,-12,-11,-11,-11,-11,-11,-10,-10,-10,-10,-10,-10,-10,-10,-11,-12,-17,-17,-19,-19,-20,-20,-20,-20,-20,-21,-21,-20,-20,-20,-18,-18,-17,-17,-17,-17,-17,-17,-17}
local yRoad = {0,0,0,0,0,2,4,7,10,14,18,21,26,95,91,79,77,54,76,105,114,121,141,176,194,210,232,245,252,254,254,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,247,233,209,163,141,106,77,54,45,35,32,28,25,23,17,14,11,7,6,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,18,37,79,124,166,199,223,239,247,245,247,249,248,249,249,251,252,253,251,247,243,239,232,224,211,200,193,172,157,152,134,120,91,71,47,18,8,16,54,77,114,158,187,201,198,152,152,41,38,39,52,65,151,173,210,228,218,178,125,95,50,29,17,10,7,6,6,10,17,31,53,84,120,157,186,213,231,247,254,254,254,254,253,253,253,250,242,233,217,201,178,151,126,101,80,61,44,31,23,16,7,2,1,0,0,0,0,0,0,0,0,0,1,7,13,26,33,60,98,119,163,202,216,217,214,208,192,166,141,115,88,70,50,32,19,11,6,4,3,3,4,7,11,17,27,45,60,86,112,134,154,184,204,223,237,246,252,255,255,255,255,255,255,255,255,255,253,250,245,237,231,219,207,193,190,179,170,163,160,159,160,160,157,148,107,88,68,46,29,18,7,3,0,0,1,4,10,20,33,50,66,81,99,113,124,131,135,138,140,149,158,168,177,182,185,197,192,184,179,164,137,137,134,134,131,130,121,115,95,84,71,48,35,22,9,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,6,17,41,120,131,140,154,174,199,222,240,251,255,255,255,255,255,255,255,255,255,255,255,254,253,247}

local roadLen = #xRoad

-- ====================={ Engine initialization }===============================
WIDTH = 320
HEIGHT = 240
roadPart = {}
inited = false

function engineInit() 
  inited = false
  local height = HEIGHT

  speed = 0
  roadCpt = 0
  steering = 0

  lastRoadWidth = 100
  firstRoadWidth = WIDTH*1.5
  firstRoadBorderWidth = 20
  lastRoadBorderWidth = firstRoadBorderWidth * (  lastRoadWidth / firstRoadWidth)
			
  distanceOfView = 150
  distMin = 10 -- --> plus proche de 0 -> plus equation Caro est juste
  distMax = distanceOfView+distMin;

  horizonLine = height - ( distMax );
  
  dd = distMax
  oldDD = distMax
  
  roadPart = {} -- array
  oldRoadWidth = firstRoadWidth
  oldZ = distMax
  
  roadSidePart = {} -- array
  oldRoadSideWidth = firstRoadBorderWidth
  
  computeTrapezes()
  inited = true
end
 
function computeSegment(z)
  local initZ = z
  local h = z
  z = ( distanceOfView - z )
  
  local roadWidth = (firstRoadWidth / 2) + (( ( lastRoadWidth - firstRoadWidth ) / ( 2 * distanceOfView ) ) * z)
  local roadBorderWidth = (firstRoadBorderWidth / 2) + (( (lastRoadBorderWidth - firstRoadBorderWidth) / ( 2 * distanceOfView ) ) * z)
  
  local x = (WIDTH - roadWidth ) / 2
  h = h + horizonLine
  
  local lineOne = false
  local strictLineOn = false
  
  if ( initZ == dd ) then  
  	oldDD = dd
  	dd = math.floor( dd / 1.2 )
  	strictLineOn = true
  
  	-- ============ main road part ===========
  	-- instanciate a 'Trapeze' via init(...)
  	local t = Trapeze.new( oldRoadWidth, oldZ+horizonLine, roadWidth, initZ+horizonLine, #roadPart  )
  	roadPart[#roadPart+1] = t
  	oldRoadWidth = roadWidth
  				
  	-- ============ side road part ===========
  	--roadSidePart[#roadSidePart] = Trapeze( oldRoadSideWidth, oldZ+horizonLine, roadBorderWidth, initZ+horizonLine, #roadSidePart )
  	--oldRoadSideWidth = roadBorderWidth
  				
  	oldZ = initZ;
  end
  
  if ( strictLineOn ) then
    -- ...
  end
  
end

function computeTrapezes()
 for i=distMax, distMin, -1 do
   local h = i
   computeSegment(h)
 end
end

 
-- ====================={ Trapeze class }===============================
function drawTrapeze(gc, top,bottom,leftT,rightT,leftB,rightB) 
  gc:fillPolygon( { leftB, bottom, rightB, bottom, rightT, top, leftT, top } ) 
end 

-- for class() ==>> constructor must been called init(...)
--Trapeze = class()
Trapeze = {}
Trapeze.__index = Trapeze


function Trapeze.new(bottomBase, bottomHeight, upperBase, upperHeight, idx)
  local self = setmetatable({}, Trapeze)

-- function Trapeze:init(bottomBase, bottomHeight, upperBase, upperHeight, idx)
  self.bottomBase = bottomBase
  self.bottomHeight = bottomHeight
  self.upperBase = upperBase
  self.upperHeight = upperHeight
  self.idx = idx
  
return self;
end

 function Trapeze:draw(gc, middle, middle2, drawIdx)
 
       -- if too slow : change color / draw all odd seg. // change color / draw all even
       if (math.fmod(drawIdx,2)==1) then 
         gc:setColorRGB(150, 150, 150) 
       else 
         gc:setColorRGB(120, 120, 120) 
       end 

       local xb1 = middle - self.bottomBase/2 
       local xb2 = xb1 + self.bottomBase 
       local xu1 = middle2 - self.upperBase/2
       local xu2 = xu1 + self.upperBase

       local ylMod = 0
       if ( camera.y > 0 ) then
         if ( self.idx == 0 ) then
           ylMod = 0
         else
           ylMod = camera.y * self.idx
         end 
       end
       local yuMod = camera.y * self.idx;

       drawTrapeze(gc, self.upperHeight+yuMod,self.bottomHeight+ylMod,xu1,xu2,xb1,xb2)
       

 end
  


-- ====================={ Paint Event }===============================

KUP    = false
KDOWN  = false
KLEFT  = false
KRIGHT = false

lastYr = 0

function renderRoad(gc, delta)
  camera.y = 0
  --[[ if ( KUP ) then 
    camera.y = 2 
  elseif ( KDOWN ) then 
    camera.y = -2 
  end ]]
  local yr = yRoad[delta+1]
  if ( delta < roadLen ) then

    camera.y = - ( yr - lastYr )/256*8
    lastYr = yr

  end
  
  local lastTrap = roadPart[ #roadPart - 0 ];
  local yuMod = camera.y * lastTrap.idx;
  horizonLine = lastTrap.upperHeight + yuMod;
  
  if ( horizonLine < 0 ) then horizonLine = 0 end
  if ( horizonLine >= HEIGHT ) then horizonLine = HEIGHT-1 end 
  
  gc:setColorRGB(170,170,255)
  gc:fillRect( 0, 0, WIDTH, horizonLine)
  
  gc:setColorRGB(0,255,0)
  gc:fillRect( 0, horizonLine, WIDTH, HEIGHT-horizonLine)

  INVIS_LIMIT = 3

  local m = WIDTH / 2
  local lastM = m
  
  for i=#roadPart,INVIS_LIMIT,-1 do
        if ( i+delta >= roadLen ) then
          m = WIDTH / 2
          lastM = m
        end
        
        --print( roadPart[i].draw )
        
        if ( roadPart == nil or roadPart[i] == nil ) then
          print("Road #"..i.. " is null" )
        else
          roadPart[i]:draw( gc, lastM, m, i+delta)
        end
        
        
        -- draw sides
        m = lastM
    
        if ( i+delta < roadLen ) then
          local rp = xRoad[ (i+delta)+1 ]
          lastM = lastM - rp

           -- 0.5 est fonction de la maniabilite du vehicule
           lastM = lastM - steering*0.5

        end
        
    end
end

function on_paint(gc)
  if ( not inited ) then return end
   
  renderRoad(gc, roadCpt)
  --roadCpt = roadCpt + 1 
  
  gc:setColorRGB(0,0,0)
  gc:drawString("speed : "..math.floor(speed), 0, 0)
  gc:drawString("dist : "..roadCpt, 0, 16)
  gc:drawString("steering : "..steering, 0, 32)
 
  if stopped then
    gc:drawString("== STOPPED ==", 40, 70)
  end


end 


lastKeyDown = -1
firstKey = false
function on_arrowKey(key) 

if ( lastKeyDown == 0 and not firstKey ) then
  firstKey = true
end 


  -- in key routine -> -1 till end
  lastKeyDown = -1

 if key == "left" then 
  KLEFT  = true
  steering = steering -1 
 elseif key == "right" then 
  KRIGHT = true
  steering = steering +1
 elseif key == "up" then 
  KUP    = true
 elseif key == "down" then 
  KDOWN  = true
 else
  --lastKeyDown = timer.getMilliSecCounter()
  --return 
 end 

 if ( steering < -30 ) then steering = -30 end
 if ( steering >  30 ) then steering =  30 end
 lastKeyDown = timer.getMilliSecCounter()
 
end 

function on_escapeKey() 
  if ( not stopped ) then
    quit() 
  else
    start()
  end
  platform.window:invalidate()
end 

-- -------------------------- 
SPEEDMAX = 10
--speed = SPEEDMAX-1
speed = 0

function on_charIn(char)
  if ( char == "+" and speed < SPEEDMAX ) then
    speed = speed + 1
  elseif ( char == "-" and speed > 0 ) then
    speed = speed - 1
  end
  
  lastKeyDown = timer.getMilliSecCounter()
  
end

function tick() 
  local now = timer.getMilliSecCounter()
  
  -- not INSIDE keyDown // not timeout
  -- must set higher than tick period but takes long to released key... ;( 
  if (lastKeyDown > 0 and now > lastKeyDown+300) then
    if not firstKey then
      KUP    = false
      KDOWN  = false
      KLEFT  = false
      KRIGHT = false
      
      if ( steering > 0 ) then steering = steering -1 
      elseif ( steering < 0 ) then steering = steering +1 
      end 
      
      if ( speed > 5.2 ) then speed = speed -0.1 end
      
      --lastKeyDown = 0
    else
     lastKeyDown = now
     firstKey = false
    end
  end
  
  local iSpeed = math.floor(speed)
  if ( iSpeed < 0 ) then iSpeed = 0 end
  if ( iSpeed > SPEEDMAX ) then iSpeed = SPEEDMAX end 
  
  if ( iSpeed > 0 and (iSpeed == SPEEDMAX or math.fmod( now, SPEEDMAX-iSpeed ) == 0) ) then
      roadCpt = roadCpt + 1
      if ( roadCpt >= roadLen ) then
        speed = 0
      end
  end 
  
  -- platform.window:invalidate()
end 

-- do not start() in IDE mode 
-- tick() will be called instead 
-- start() 
--[[
function on.activate()
  start()
end

function on.desactivate()
  quit()
end
]]--


gc = {
  __innerColor = 0,

  setColorRGB = function(self, r,g,b)
    self.__innerColor  = lcd.rgb(r,g,b)
  end , 
  
  fillRect = function(self, x,y,w,h)
    lcd.rect(math.floor(x),math.floor(y),math.floor(w),math.floor(h),1,self.__innerColor)
  end , 
  
  fillPolygon = function(self,  pts_arry )
    lcd.line( math.floor(pts_arry[1]), math.floor(pts_arry[2]), math.floor(pts_arry[3]), math.floor(pts_arry[4]),  self.__innerColor );
    lcd.line( math.floor(pts_arry[3]), math.floor(pts_arry[4]), math.floor(pts_arry[5]), math.floor(pts_arry[6]),  self.__innerColor );
    lcd.line( math.floor(pts_arry[7]), math.floor(pts_arry[8]), math.floor(pts_arry[1]), math.floor(pts_arry[2]),  self.__innerColor );
  end , 
  
  drawString = function(self,  str, x, y )
    --lcd.cursor( math.floor(x), math.floor(y) );
    --lcd.print( str );
  end
}



function main()
  print("Let's go !")
  lcd.rect(0,0,320,240,1,8)
  
  snd.stop() 
  -- snd.setvolume(40)
  lcd.delay(100)
  --snd.pause()
  snd.setvolume(20)
  lcd.delay(1000) -- need a long pause after setvolume
  
  snd.play(58) -- MotorHead Theme
  --snd.pause() -- else music don't starts
  
  start()
  
  while( true ) do
    local pads = pad.read()
    
    if ( pads.start ) then
      -- on_escapeKey
      break
    elseif ( pads.A ) then
      on_charIn('+')
    elseif ( pads.B ) then
      on_charIn('-')
    end

    if ( pads.left ) then
      on_arrowKey("left")
    elseif ( pads.right ) then
      on_arrowKey("right")  
    end
      
    if ( pads.up ) then
      on_arrowKey("up")
    elseif ( pads.down ) then
      on_arrowKey("down")        
    end
      
    tick()
    
      -- platform.window:invalidate()
      -- reaquests for on_paint
on_paint( gc )

    
    lcd.delay(30)
  end
  
  snd.stop()
  
end


main()


