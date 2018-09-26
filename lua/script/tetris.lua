-- ------ --
-- TETRIS http://matthieu.besson.pagesperso-orange.fr/2008.12.07/Tetris%20Lua.html -- 
-- ------ --
-- TrapII 2008 -- modif by Xts @ 2013
-- Lua to C :
-- 3 Bindings CTBL:DrawRect, CTBL:Invalidate and CTBL:StartTimer
-- C to Lua :
-- 4 Globals function OnTimeout, OnPaint, OnKeyInput, OnInit

-- ////////////////////////////////////////

SCREEN_HEIGHT = 240
SCREEN_WIDTH = 320
_GLOBAL_isPC = false

ScreenHeight = SCREEN_HEIGHT
ScreenWidth = SCREEN_WIDTH

PAD_TIMER_VALUE = 100


--    X     |   /\    | UP   -> speed down the piece | START -> pause
--  Y   A   | []  ()  | DOWN -> nothing              | L1 change/next piece
--    B     |   XX    | A,B  -> rotate piece         

KEY = { PRESSED = 0, RELEASED = 3,
        LEFT = 37, SPEED_DOWN_PIECE = 40,
        RIGHT = 39, ROTATE_PIECE = 38 }


-- ////////////////////////////////////////

--Ext_Scheduler = luajava.newInstance( "com.xtase.lua.hardware.object.Ext_LuaScheduler" )
--schedule = Ext_Scheduler.new()
--schedule:setHook("OnTimeout()")

SYSTEM_SLEEP = 500
function CTBL_StartTimer(waitDelay)
  -- in reallity => not wait -> Thread.runSchedule
  --schedule:start( waitDelay )
  
  if ( _GLOBAL_isPC ) then
    --waitDelay = waitDelay * 0.8
    waitDelay = waitDelay * 0.2
  end
  
  
  SYSTEM_SLEEP = waitDelay
  --SYSTEM_SLEEP = 0
end

-- ////////////////////////////////////////

function CTBL_Invalidate()
  --screen:flip()
  
  OnPaint(ScreenWidth,ScreenHeight)
  --local _status, _err = pcall(function ()  OnPaint(ScreenWidth,ScreenHeight)  ; end)
  
  if ( not _GLOBAL_isPC ) then
    --screen:waitVblankStart()
  end
end

--[[
--gColors = { 0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0xFF00FF, 0x00FFFF, 0xFFFF00 }
gColors = { Color.new( 0xFF, 0xFF, 0xFF ), -- 1 white
            Color.new( 0xFF, 0x00, 0x00 ), -- 2 red
            Color.new( 0x00, 0xFF, 0x00 ), -- 3 green
            Color.new( 0x00, 0x00, 0xFF ), -- 4 blue
            Color.new( 0xFF, 0x00, 0xFF ), -- 5 pink
            Color.new( 0x00, 0xFF, 0xFF ), -- 6 cyan
            Color.new( 0xFF, 0xFF, 0x00 )  -- 7 yellow
             }
]]--

--[[
imgPath = "./imgs/"
borderImgPath = imgPath.."border.png"
borderImg = Image.load( borderImgPath )

bulletTextImg = Image.load( imgPath.."border_text.png" )

-- on PSP 480x272 -> 12x12 px buletts

bulletWhiteImg = Image.load( imgPath.."bulett_white.png" )
bulletRedImg = Image.load( imgPath.."bulett_red.png" )
bulletBlueImg = Image.load( imgPath.."bulett_blue.png" )
bulletGreenImg = Image.load( imgPath.."bulett_green.png" )
bulletPinkImg = Image.load( imgPath.."bulett_pink.png" )
bulletCyanImg = Image.load( imgPath.."bulett_cyan.png" )
bulletYellowImg = Image.load( imgPath.."bulett_yellow.png" )
]]

function CTBL_DrawRectDispText(x,y,w,h,color)
  --[[ if ( color == _WHITE ) then
    --screen:blit( x,y, bulletTextImg, 0, 0, BlockSize, BlockSize, false )
    screen:blit( x,y, bulletTextImg, 0, 0, w, h, false )
  else
    screen:fillRect(x, y, w, h, color)
  end
  ]]--
  
  lcd.rect(x, y, w, h, 1, color)
end

function CTBL_DrawRect(x,y,w,h,color)
--[[
  if ( color == BorderColor ) then
    --screen:blit( x,y, borderImg, 0, 0, BlockSize, BlockSize, false )
    screen:blit( x,y, borderImg, 0, 0, w, h, false )
  elseif ( color == gColors[1] and bulletWhiteImg ~= nil ) then
    screen:blit( x,y, bulletWhiteImg, 0, 0, w, h, false )
  elseif ( color == gColors[2] and bulletRedImg ~= nil ) then
    screen:blit( x,y, bulletRedImg, 0, 0, w, h, false )
  elseif ( color == gColors[3] and bulletGreenImg ~= nil ) then
    screen:blit( x,y, bulletGreenImg, 0, 0, w, h, false )
  elseif ( color == gColors[4] and bulletBlueImg ~= nil ) then
    screen:blit( x,y, bulletBlueImg, 0, 0, w, h, false )
  elseif ( color == gColors[5] and bulletPinkImg ~= nil ) then
    screen:blit( x,y, bulletPinkImg, 0, 0, w, h, false )
  elseif ( color == gColors[6] and bulletCyanImg ~= nil ) then
    screen:blit( x,y, bulletCyanImg, 0, 0, w, h, false )
  elseif ( color == gColors[7] and bulletYellowImg ~= nil ) then
    screen:blit( x,y, bulletYellowImg, 0, 0, w, h, false )
  else
    screen:fillRect(x, y, w, h, color)
  end

  --screen:fillRect(x, y, w, h, color)
  ]]--
  
  lcd.rect(x, y, w, h, 1, color)
end

--[[
_RED = Color.new(255, 0, 0)
_WHITE = Color.new(255, 255, 255)
_BLACK = Color.new(0, 0, 0)
]]--
_RED = 8
_WHITE = 1
_BLACK = 0

-- ////////////////////////////////////////
-- ////////////////////////////////////////


-- * ******* *
-- * Globals *
-- * ******* *

-- BlockSize is the size of a block that compose the pieces of the tetris
BlockSize = 14
CenterX = 36
CenterY = 6

gScoreOnePiece = 1 -- A piece placed on the board x point added to the score
gScore = { 10, 50, 100, 500 } -- Scores for eliminating 1,2,3 or 4 lines

gAllPieces = {
  { -- O
    { {-1,0}, {0,0}, {-1,1}, {0,1} }  -- Rotation 1
  },
  { -- I
    { {-2,0}, {-1,0}, {0,0}, {1,0} }, -- Rotation 1
    { {0,-1}, {0,0}, {0,1}, {0,2} }   -- Rotation 2
  },
  { -- S
    { {0,0}, {1,0}, {-1,1}, {0,1} },  -- Rotation 1
    { {0,-1}, {0,0}, {1,0}, {1,1} }   -- Rotation 2
  },
  { -- Z
    { {-1,0}, {0,0}, {0,1}, {1,1} },  -- Rotation 1
    { {1,-1}, {0,0}, {1,0}, {0,1} }   -- Rotation 2
  },
  { -- L
    { {-1,0}, {0,0}, {1,0}, {-1,1} }, -- Rotation 1
    { {0,-1}, {0,0}, {0,1}, {1,1} },  -- Rotation 2
    { {-1,0}, {0,0}, {1,0}, {1,-1} }, -- Rotation 3
    { {0,-1}, {0,0}, {0,1}, {-1,-1} } -- Rotation 2
  },
  { -- J
    { {-1,0}, {0,0}, {1,0}, {1,1} },  -- Rotation 1
    { {0,-1}, {0,0}, {0,1}, {1,-1} }, -- Rotation 2
    { {-1,0}, {0,0}, {1,0}, {-1,-1} },-- Rotation 3
    { {0,-1}, {0,0}, {0,1}, {-1,1} }  -- Rotation 2
  },
  { -- T 
    { {-1,0}, {0,0}, {1,0}, {0,1} },  -- Rotation 1
    { {0,-1}, {0,0}, {0,1}, {1,0} },  -- Rotation 2
    { {-1,0}, {0,0}, {1,0}, {0,-1} }, -- Rotation 3
    { {0,-1}, {0,0}, {0,1}, {-1,0} }  -- Rotation 4
  }
}


-- Colors
-- in RGB format each component over 8 bits
--BorderColor = 0x0077A0
--BorderColor = Color.new( 0x00, 0x77, 0xA0 )
BorderColor = 9 -- light blue




-- Font
-- gFontSize is in unit, each character is a set of rect x,y,w,h
gFontSize = 6
gFont = {
 ["G"] = { {1,0,3,1}, {0,1,1,4}, {1,5,3,1}, {4,4,1,1}, {3,3,2,1}, {4,1,1,1} },
 ["A"] = { {1,0,3,1}, {0,1,1,5}, {4,1,1,5}, {1,3,3,1} },
 ["M"] = { {0,1,1,5}, {4,1,1,5}, {2,1,1,2}, {1,0,1,1}, {3,0,1,1} },
 ["E"] = { {0,1,1,4}, {1,0,4,1}, {1,2,4,1}, {1,5,4,1} },
 ["R"] = { {0,0,1,6}, {1,0,3,1}, {4,1,1,1}, {3,2,1,1}, {1,3,2,1}, {3,4,1,1}, {4,5,1,1} },
 ["V"] = { {0,0,1,2}, {1,2,1,2}, {2,4,1,2}, {3,2,1,2}, {4,0,1,2} },
 ["O"] = { {1,0,3,1}, {0,1,1,4}, {1,5,3,1}, {4,1,1,4} },
 ["L"] = { {0,0,1,6}, {1,5,4,1} },
 ["C"] = { {1,0,4,1}, {1,5,4,1}, {0,1,1,4} },
 ["S"] = { {1,0,3,1}, {4,1,1,1}, {0,1,1,2}, {1,3,3,1}, {4,4,1,1}, {1,5,3,1} },
 ["T"] = { {0,0,5,1}, {2,1,1,5} },
 ["I"] = { {2,0,1,6} },
 [":"] = { {2,1,1,1}, {2,4,1,1} },
 ["0"] = { {2,0,2,1}, {1,1,1,4}, {4,1,1,4}, {2,5,2,1} },
 ["1"] = { {1,2,1,1}, {2,1,1,1}, {3,0,1,5}, {1,5,4,1} },
 ["2"] = { {1,1,1,1}, {2,0,2,1}, {4,1,1,2}, {3,3,1,1}, {2,4,1,1}, {1,5,4,1} },
 ["3"] = { {1,1,1,1}, {2,0,2,1}, {4,1,1,1}, {3,2,1,2}, {4,4,1,1}, {2,5,2,1}, {1,4,1,1} },
 ["4"] = { {4,0,1,6}, {3,1,1,1}, {2,2,1,1}, {1,3,1,2}, {2,4,2,1} },
 ["5"] = { {1,0,4,1}, {1,1,1,2}, {2,2,2,1}, {4,3,1,2}, {1,5,3,1} },
 ["6"] = { {2,0,3,1}, {1,1,1,4}, {2,2,2,1}, {4,3,1,2}, {2,5,2,1} },
 ["7"] = { {1,0,4,1}, {4,1,1,2}, {3,3,1,3} },
 ["8"] = { {2,0,2,1}, {2,2,2,1}, {2,5,2,1}, {1,1,1,1}, {4,1,1,1}, {1,3,1,2}, {4,3,1,2} },
 ["9"] = { {1,1,1,1}, {2,0,2,1}, {2,2,2,1}, {2,5,2,1}, {4,1,1,4} }
}



-- dispText
-- use the gFont to display a text str at pos x,y with a pixel per unit of s
-- character is of size gFontSize * s
function dispText(x,y,str,s)

  local i, j, xd, yd, w, h
  for i=1,string.len(str) do
    local ch = string.sub(str,i,i)
    local letter = gFont[ ch ]
    
    --local tmp = i
    --print( 10, 10+tmp, i.." - "..ch, _WHITE )
    
    if letter ~= nil then
      --print( 17, 10+tmp, "OK "..#letter, _WHITE )
    
      for j=1,#letter do
        xd = (letter[j][1] + (i-1)*6) * s + x
        yd = letter[j][2] * s + y
        w = letter[j][3] * s
        h = letter[j][4] * s
        --CTBL:DrawRect(xd, yd, w, h, 0xFFFFFF)
        --CTBL_DrawRect(xd, yd, w, h, _WHITE)
        CTBL_DrawRectDispText(xd, yd, w, h, _WHITE)
      end
    end
    
  end

end


-- * ****** *
-- * CPiece *
-- * ****** *

CPiece_mt = {}
CPiece_mt.__index = CPiece_mt

--
-- getNbRot
-- get number of rotation of the piece
--
function CPiece_mt.getNbRot(self)
  return #gAllPieces[self.ptype]
end

--
-- getCases
-- get cases of the current piece with good rot and pos
--
function CPiece_mt.getCases(self)
  local i
  local rCases = gAllPieces[self.ptype][self.rot]
  local cases = {}
  -- copy the table from the global one
  for i=1,#rCases do
   cases[i] = {}
   cases[i][1] = rCases[i][1]
   cases[i][2] = rCases[i][2]
  end
  -- add the offset
  for i=1,#cases do
    cases[i][1] = cases[i][1] + self.x
    cases[i][2] = cases[i][2] + self.y
  end
  return cases
end

function CPiece_mt.disp(self, x, y)
  local i,j
local i
  local rCases = gAllPieces[self.ptype][self.rot]
  -- add the offset
  for i=1,#rCases do
    local xp = rCases[i][1] + 2
    local yp = rCases[i][2] + 2
    --CTBL:DrawRect(x+xp*BlockSize, y+yp*BlockSize, BlockSize, BlockSize, gColors[self.ptype])
    --CTBL_DrawRect(x+xp*BlockSize, y+yp*BlockSize, BlockSize, BlockSize, gColors[self.ptype])
    
    CTBL_DrawRect(x+xp*BlockSize, y+yp*BlockSize, BlockSize, BlockSize, self.ptype)
  end
end


--
-- Create a new CPiece object
--
function newCPiece()
  local v = { x = 6, y = 1, rot = 1 }
  v.ptype = math.random(#gAllPieces) -- piece type from 1 to number of pieces (7)
  setmetatable(v, CPiece_mt)
  return v
end


-- * ****** *
-- * CBoard *
-- * ****** *

CBoard_mt = {}
CBoard_mt.__index = CBoard_mt

--
-- CBoard::disp
-- Display the board at a given position (from top left)
--
function CBoard_mt.disp(self, x, y)
  local i,j

  --CTBL:DrawRect(x, y, BlockSize, (self.h+2)*BlockSize, BorderColor) -- Left
  CTBL_DrawRect(x, y, BlockSize, (self.h+2)*BlockSize, BorderColor) -- Left
  CTBL_DrawRect(x+(self.w+1)*BlockSize, y, BlockSize, (self.h+2)*BlockSize, BorderColor) -- Right
  CTBL_DrawRect(x+BlockSize, y, self.w*BlockSize, BlockSize, BorderColor) -- Top
  CTBL_DrawRect(x+BlockSize, y+(self.h+1)*BlockSize, self.w*BlockSize, BlockSize, BorderColor) -- Bottom

  for j=1,self.h do
    for i=1,self.w do
      if self.cases[i][j] ~= 0 then
        --CTBL:DrawRect(x+i*BlockSize, y+j*BlockSize, BlockSize, BlockSize, gColors[self.cases[i][j]])
        --CTBL_DrawRect(x+i*BlockSize, y+j*BlockSize, BlockSize, BlockSize, gColors[self.cases[i][j]])
        
        CTBL_DrawRect(x+i*BlockSize, y+j*BlockSize, BlockSize, BlockSize, self.cases[i][j] )
      end
    end
  end
end



--
-- CBoard::place
-- Place a CPiece
--
function CBoard_mt.place(self, p)
  local i
  local piececases = p:getCases()
  
  for i=1,#piececases do
    local x = piececases[i][1]
    local y = piececases[i][2]
    self.cases[x][y] = p.ptype
  end
end

--
-- CBoard::remove
-- Remove a CPiece
--
function CBoard_mt.remove(self, p)
  local i
  local piececases = p:getCases()
  
  for i=1,#piececases do
    local x = piececases[i][1]
    local y = piececases[i][2]
    self.cases[x][y] = 0
  end
end



--
-- CBoard::canPlace
-- return true if the board can place the piece
--
function CBoard_mt.canPlace(self, p)
  local i
  local piececases = p:getCases()
  
  for i=1,#piececases do
    local x = piececases[i][1]
    local y = piececases[i][2]
    if x <= 0 or x > self.w or y <= 0 or y > self.h then
      return false
    end
    if self.cases[x][y] ~= 0 then
      return false
    end
  end
  return true
end

--
-- CBoard::removeFullLines
-- remove all lines full
--
function CBoard_mt.removeFullLines(self)
  local nbfull = 0
  local j = 1
  
  while j <= self.h do
    local full = true
    for i=1,self.w do
      if self.cases[i][j] == 0 then
        full = false
        break
      end
    end
    if full then
      -- remove line at j
      nbfull = nbfull + 1
      for i=1,self.w do
        table.remove(self.cases[i], j)
        table.insert(self.cases[i], 1, 0)
      end
      j = 1
    else
      j = j + 1
    end
  end
  return nbfull
end



--
-- Create a new CBoard object
--
function newCBoard()
  local i,j
  local v = { w = 10, h = 20 }
  v.cases = {}
  for i=1,v.w do
    v.cases[i]={}
    for j=1,v.h do
      v.cases[i][j] = 0
    end
  end
  setmetatable(v, CBoard_mt)
  return v
end

-- * ***** *
-- * CGame *
-- * ***** *

CGame_mt = {}
CGame_mt.__index = CGame_mt

--
-- CGame::step
--

_async_in_step = false

function CGame_mt.step(self)

if _async_in_step then
  return
end

_async_in_step = true

  if self.gameover or self.title then 
  
    _async_in_step = false
  
    return
  end
  
  if self.newpiece then -- a new piece as been requested
    self.newpiece = false
    self.timerDT = (11 - self.level) * 50
    self.curpiece = self.nextpiece
    self.nextpiece = newCPiece()
    if self.board:canPlace(self.curpiece) then
      self.board:place(self.curpiece)
    else -- we cant place the new piece so game is over
      self.gameover = true
      self.title = false
      self.timerDT = 5000
    end
  else -- advance current piece
    self.board:remove(self.curpiece)
    self.curpiece.y = self.curpiece.y + 1
    -- can the piece move down ?
    if self.board:canPlace(self.curpiece) then
      -- yes move it down
      self.board:place(self.curpiece)
    else
      -- no stop it and ask for a new piece
      self.curpiece.y = self.curpiece.y - 1
      self.board:place(self.curpiece)
      self.newpiece = true
      -- check if we can remove full lines
      local newnbline = self.board:removeFullLines()
      self.nbline = self.nbline + newnbline
      self.score = self.score + gScoreOnePiece
      if newnbline > 0 then
        self.score = self.score + gScore[newnbline]
      end
      self.level = math.min(1 + math.floor(self.nbline / 10), 10)
    end
  end
  
_async_in_step = false
  
end

--
-- CGame::moveX
-- move the current piece in the x coordinate
--
function CGame_mt.moveX(self, dx)
  if self.gameover or self.title or self.newpiece then 
    return
  end

  self.board:remove(self.curpiece)
  self.curpiece.x = self.curpiece.x + dx
  if self.board:canPlace(self.curpiece) then
    self.board:place(self.curpiece)
    -- -- CTBL:Invalidate()
    -- CTBL_Invalidate()
  else
    self.curpiece.x = self.curpiece.x - dx
    self.board:place(self.curpiece)
  end
end

--
-- CGame::rotate
-- rotate the current piece (if possible)
--
function CGame_mt.rotate(self)
  if self.gameover or self.title or self.newpiece then 
    return
  end
  local lastrot = self.curpiece.rot
  self.board:remove(self.curpiece)
  self.curpiece.rot = self.curpiece.rot + 1
  if self.curpiece.rot > self.curpiece:getNbRot() then
    self.curpiece.rot = 1
  end
  if self.board:canPlace(self.curpiece) then
    self.board:place(self.curpiece)
    -- -- CTBL:Invalidate()
    -- CTBL_Invalidate()
  else
    self.curpiece.rot = lastrot
    self.board:place(self.curpiece)
  end
end

--
-- CGame::down
-- down the current piece as much as possible
--
function CGame_mt.down(self)
  if self.gameover or self.title or self.newpiece then 
    return
  end
  self.timerDT = 50
  --CTBL:StartTimer(self.timerDT)
  CTBL_StartTimer(self.timerDT)
  
--  while not self.newpiece do
--    self:step()
--  end
end


--
-- OnPaint is called when the window has to redraw
--

_async_in_paint = false

-- .............
backgroundBmp = nil
local _status, _err = pcall(function () backgroundBmp = Image.load(imgPath.."smm_bkg_2.png"); end)
local xBck,yBck = 0,0
-- .............


function OnPaint(w,h)
lcd.blitt(0)


if ( _async_in_paint or _async_in_step ) then
--if _async_in_paint then

lcd.blitt(2)
  return
end

_async_in_paint = true

  local x,y,ppc,str

  ScreenWidth = w
  ScreenHeight = h	
  BlockSize = math.floor(math.min(ScreenWidth/16, ScreenHeight/22))
  CenterX = math.floor(ScreenWidth - BlockSize*16)/2
  CenterY = math.floor(ScreenHeight - BlockSize*22)/2
  
-- .............
--[[
if ( backgroundBmp == nil ) then
  --CTBL:DrawRect(0, 0, ScreenWidth, ScreenHeight, 0x000000) -- Background is black
  CTBL_DrawRect(0, 0, ScreenWidth, ScreenHeight, _BLACK) -- Background is black
else
  screen:blit( xBck,yBck, backgroundBmp )
end
]]--

--CTBL_DrawRect(0, 0, ScreenWidth, ScreenHeight, _BLACK) -- Background is black
lcd.cls()
-- .............
  
  gGame.board:disp(CenterX+4*BlockSize, CenterY)
  gGame.nextpiece:disp(CenterX, CenterY)
  if gGame.title or gGame.gameover then
    if gGame.title then
      str = "TETRIS"
    end
    if gGame.gameover then
      str = "GAME OVER"
    end
    ppc = math.max(1, math.floor(ScreenWidth / ((string.len(str)+1)*gFontSize)))
    x = math.floor((ScreenWidth - ppc*string.len(str)*gFontSize)/2)
    y = math.floor((ScreenHeight - ppc*gFontSize)/2)
    dispText(x, y, str, ppc)
  end
  
  ppc = math.max(1, math.floor(BlockSize / gFontSize))
  y = CenterY+BlockSize-(gFontSize*ppc)
  -- dispText(CenterX, y, "SCORE:"..tostring(gGame.score), ppc)
  lcd.cursor( math.floor(CenterX/6), math.floor(y/8) ); lcd.print( "SCORE:"..tostring(gGame.score) )
  
  
  y = y + BlockSize*(gGame.board.h+1)
  -- dispText(CenterX, y, "LEVEL:"..tostring(gGame.level), ppc)
  lcd.cursor( math.floor(CenterX/6), math.floor(y/8) ); lcd.print( "LEVEL:"..tostring(gGame.level) )
  
_async_in_paint = false
  
  
  lcd.blitt(2)
  
end



--
-- OnKeyInput is called when the user press/release a key
-- 
function OnKeyInput(action, logicalkey)
  --__print("OnKeyInput in lua called with ACTION=".. action .." KEY=".. logicalkey)
  
  --infiniteLoop("keyInput 1")
  
  if action == KEY.PRESSED then    
    if logicalkey == KEY.LEFT then
      gGame:moveX(-1)
    end
    if logicalkey == KEY.RIGHT then
      gGame:moveX(1)
    end
    if logicalkey == KEY.ROTATE_PIECE then
      gGame:rotate()
    end
    if logicalkey == KEY.SPEED_DOWN_PIECE then
      gGame:down()
    end
    
    --infiniteLoop("keyInput 2")
    
    --__print("gameover="..gGame.gameover)
    --__print("title="..gGame.title)
    
    if gGame.gameover then      
      gGame = newCGame()
    else
      if gGame.title then
        gGame.title = false
        --CTBL:StartTimer(gGame.timerDT)
        CTBL_StartTimer(gGame.timerDT)
      end
    end
    
  end
end

--
-- OnInit called when application starts
-- 
function OnInit()
  __print("OnInit in lua called")
  math.randomseed(os.time())
  gGame = newCGame()
  
  -- moa: moved from newCGame() for security
  CTBL_StartTimer(gGame.timerDT)
  
  return true
end


-- 
-- OnTimeout is called when timer expires
--
function OnTimeout()

----if ( _async_in_paint or _async_in_step ) then
--if ( _async_in_paint ) then
--  return
--end

  gGame:step()
  
  -- moa : removed
  -- -- CTBL:Invalidate()
  -- CTBL_Invalidate() -- To launch a OnPaint event
  
  if gGame.gameover == false and gGame.title == false then
    --CTBL:StartTimer(gGame.timerDT)
    CTBL_StartTimer(gGame.timerDT)
  end
end


--
-- newCGame
--
function newCGame()
  local self = { board = newCBoard(), 
                 curpiece = {},                 
                 newpiece = true,
                 gameover = false,
                 title = true,
                 nbline = 0, -- number of line removed
                 score = 0,
                 level = 1 }
                 
  self.nextpiece = newCPiece()
  self.timerDT = 500
  
  -- moa : moved outside
  -- --CTBL:StartTimer(self.timerDT)
  -- CTBL_StartTimer(self.timerDT)
  
  setmetatable(self, CGame_mt)
  return self
end



-- ////////////////////////////////////////

function infiniteLoop(str)
while true do
 --screen:clear()
 print( 1, 1, "".."INFINITE LOOP : "..str, _RED )
 CTBL_Invalidate()
end
end

__i=3
function __print(str) 
  print( 10, __i, ""..str, _WHITE )
  __i = __i + 1
end


--[[


package com.xtase.lua.hardware.object;

public class LuaTimer {
    long start = 0L;
    static long consoleStartTime = -1L;

    static {
        consoleStartTime = now();
    }

    public LuaTimer() {
    }

    public void reset() {
        consoleStartTime = now();
    }

    public void reset(int ignored) {
        consoleStartTime = now();
    }

    public void start() {
        this.start = now();
    }

    public long time() {
        return now() - consoleStartTime;
    }

    static long now() {
        return System.currentTimeMillis();
    }
}


]]--

Timer = {

  now = function()
    return os.clock()
  end,
  
  _start=0,
  consoleStartTime = os.clock(),
  
  reset = function()
    consoleStartTime = os.clock()
  end,
  
  --start = function()
  --  _start = os.clock()
  --end,
  
  --time = function()
  --  return os.clock() - consoleStartTime
  --end,
  
  -- =====================
  new = function() 
    return self
  end

}

function Timer:start()
  self._start = os.clock()
end

function Timer:time()
  return os.clock() - self.consoleStartTime
end



_Controller = {
  cross = function()
    return false
  end,
  triangle = function()
    return false
  end,
  square = function()
    return false
  end,
  circle = function()
    return false
  end,
  up = function()
    return false
  end,
  down = function()
    return false
  end,
  left = function()
    return false
  end,
  right = function()
    return false
  end
}


Controls = {
  read = function()
    return _Controller
  end
}

-- ////////////////////////////////////////
-- screen:clear()
lcd.cls()

oldPad = Controls.read()

-- padTimer = Timer.new();
padTimer = Timer

padTimerTime = 0
padTimer:start()

-- ontimeoutTimer = Timer.new();
ontimeoutTimer = Timer;


ontimeoutTimerTime = 0
if ( not _GLOBAL_isPC ) then
  ontimeoutTimer:start()
  -- on PSP : return currentTime / NOT time since start()
  ontimeoutTimerTime = ontimeoutTimer:time()
end

OnInit()


locked = false
while true do

  pad = Controls.read()
  
  -- BEWARE : PSP version "ignore" that Timer cf currentTimeMills... 
  -- Lua Timer fixed
  
  -- and it's smoother !
	if padTimer:time() >= padTimerTime+PAD_TIMER_VALUE and pad ~= oldPad then
	--if pad ~= oldPad then

		if pad:triangle() then
		  __restart()
	  --elseif not locked and ( pad:cross() or pad:circle() ) then
	  --  OnKeyInput(KEY.PRESSED, KEY.ROTATE_PIECE)
	  elseif not locked and ( pad:up() ) then
	    OnKeyInput(KEY.PRESSED, KEY.SPEED_DOWN_PIECE)
    elseif pad:left() then
	    OnKeyInput(KEY.PRESSED, KEY.LEFT)
    elseif pad:right() then
	    OnKeyInput(KEY.PRESSED, KEY.RIGHT)
		end
		
		if not locked and ( pad:cross() or pad:circle() ) then
	    OnKeyInput(KEY.PRESSED, KEY.ROTATE_PIECE)
		end
		
    --oldPad = pad
    padTimer:start();
    padTimerTime = padTimer:time()
  end

		if pad:cross() or pad:circle() or pad:up() then
		  locked = true
		else
		  locked = false
		end


-- moa : later : async thread ?  -> no : concurent acces enormous PBMs
-- moa : genre Ext_Scheduler = luajava.newInstance( "com.xtase.lua.hardware.object.Ext_LuaScheduler" )
--System.sleep( SYSTEM_SLEEP )
--OnTimeout()
 -- replaced by 
 
 local okTimeOut = false
 --[[if ( _GLOBAL_isPC ) then
   if ( ontimeoutTimer:time() >= SYSTEM_SLEEP ) then
     okTimeOut = true
   end
 else]]
   -- on PSP : return currentTime / NOT time since start()
   if ( ontimeoutTimer:time() >= ontimeoutTimerTime + SYSTEM_SLEEP ) then
     ontimeoutTimerTime = ontimeoutTimer:time()
     okTimeOut = true
   end
 --[[end]]
 
 if ( okTimeOut ) then
   OnTimeout()
   ontimeoutTimer:start()
 end
 
 
 CTBL_Invalidate()
end
-- //////////////////////////////////////// 