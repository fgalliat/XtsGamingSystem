--
-- OldSchool like Demo
-- Xtase - fgalliat @Dec 2018

LCD_WIDTH = 320
LCD_HEIGHT = 240

-- local luaAndro = false
-- local Mp3Player = nil
-- if pcall( function() Mp3Player = luajava.newInstance( "com.xtase.graphicActivity.mplayer.MusicMediaPlayer" ) end  ) then
--   luaAndro = true
-- end

-- !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-- dofile("../../data/bigLetters.lua")
--  -- defines drawBigLetterString(), initBigLetter()
-- initBigLetter("../../data")

-- dofile("../../data/smallLetters.lua")
-- initSmallLetter("../../data")
-- !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

-- Cf called from script dir
-- dofile("../../routines/FX/starfieldFX.lua")
 -- defines : drawStarFieldFrame
 
-- ==========={ Music Preparing }=======
print("Let's go !")
  -- lcd.rect(0,0,320,240,1,8)
  lcd.cls()
  lcd.pct( "/GODSFNT.PCT", (320-160)/2, (240-128)/2 )
  
  snd.stop() 
  -- snd.setvolume(40)
  lcd.delay(100)
  --snd.pause()
  snd.setvolume(15)
  lcd.delay(1000) -- need a long pause after setvolume
  
-- local music = "./MUSIC/Automation_CD_Menu_186_Music_Atari_ST.mp3"
local music = 22

local rndZik = math.random(2000)/1000

if ( rndZik >= 1) then
  --music = "./MUSIC/MGR_EmpireMenuIntro.mp3"
  music = 23
end


local playMusic = true

-- if not luaAndro then
-- 	Mp3me.load(music)
-- end
-- =====================================

local textStr  = "...Hello : here is my Xts Sliding Demo for >Handheld< ..."
local textStr2 = "} brought to you by Xtase {"

--local textComp = compileBigLetterString( textStr )
--local textComp2 = compileSmallLetterString( textStr2 )

SCREEN_WIDTH = 320
_BIGCHAR_WIDTH_REAL = 16
_SMALLCHAR_WIDTH_REAL = 8

local textX = SCREEN_WIDTH
local textX2 = -( textStr2:len() * _SMALLCHAR_WIDTH_REAL )

local screenIter = 0

local yetPlayingMusic = false

white = 1

-- prepare font
lcd.sprite( "/GODSFNT.PCT", (320-160)/2, (240-128)/2, 16, 16, 0,0 )
--          0        1         2         3         4
--          1234567890123456789012345678901234567890123
ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789<$>._:"
function findChar(ch)
	local n = string.find( ALPHABET, ""..ch, 1, true )
	if ( n == nil ) then return -1 end
	return n
end

function parseText(str)
	local st2 = ""
	local stc = {}
	local sts = {}
	local i
	for i=1, str:len() do
		local ch = string.sub(str, i,i) -- get one char
		ch = string.upper(ch)
		-- print( ch )
		local nn = findChar( ch )
		if ( nn == -1 ) then nn = 42 end -- replace by '...' ('_')
		st2 = st2.. string.sub(ALPHABET, nn,nn)
		stc[i] = nn
		
		xx = math.fmod( (stc[i]-1), 9 )
 		yy = math.floor( (stc[i]-1) / 9 )
 		
 		sts[i] = { x=xx, y=yy }
	end
	return st2, stc, sts
end

function drawBigChar(stsVal, x, y)
	if ( x < 0 or x > LCD_WIDTH or y < 0 or y > LCD_HEIGHT ) then
		return
	end
	local xx = stsVal.x
	local yy = stsVal.y
	lcd.sprite( nil, x, y, 16, 16, xx*17,yy*17 )
end

local first = true
local loopCpt = 0

-- local str,stc,sts = parseText( "abCf4#67<.: ij" )
local str,stc,sts = parseText( textStr.."    " )
local str_t,stc_t,sts_t = parseText( "Xtase" )

local title = "-Xtase- is proud to present its new handheld XtsGamingConsole ...          "

local MAX_BIG_CHARS = 18
local MAX_SML_CHARS = 52
local txtCursor = 0
local txtCursor_t = 0

lcd.cls()
while true do
	--lcd.cls() -- done by NFX
 	
 	-- ===== Music Playback ========
 	if ( playMusic ) then
	 if (not yetPlayingMusic) then
		 snd.play(music)
		 -- TODO : loop
		 yetPlayingMusic = true
	 end
    end
 	-- =============================
 	
 	
	 -- drawStarFieldFrame(screenIter)
	lcd.blitt(0);
 	lcd.fx(1,1)
 	
 	-- lcd.sprite( "/.PCT", (320-160)/2, (240-128)/2, 16, 16, 0,0 )
 	-- lcd.sprite( nil, (320-160)/2, (240-128)/2, 16, 16, 0,0 )
 	-- lcd.dispStr( str, 10, 120, white )
 	
 	local i
 	local x=10
 	local y=100
 	
 	y = 16+4
 	lcd.dispStr( string.sub( title, txtCursor_t+1, txtCursor_t+1+MAX_SML_CHARS ), x, y, white)
	txtCursor_t = txtCursor_t + 1
	if ( txtCursor_t+MAX_SML_CHARS > title:len() ) then
		txtCursor_t = 0
	end
 	
 	for i = 1, MAX_BIG_CHARS do
 		if ( i + txtCursor <= #stc ) then
 			if ( i % 2 == 0 ) then y= math.floor(100 + (math.cos( ( screenIter/2 ) % 360 ) * 3.0) )
			else                   y= math.floor(100 + (math.cos( ( ( screenIter/2) + 5 ) % 360 ) * 3.0) )
			end
 			
 			
 			drawBigChar(sts[i + txtCursor], x+( (i-1)*17 ), y)
 		else
 			txtCursor = 0
 		end
	end
	if ( math.fmod(loopCpt, 2) == 0 ) then
		txtCursor = txtCursor + 1
	end
	
 	first = false
 	
 	local baseLine = "Demo by Xtase @Dec 2018"
 	lcd.dispStr( baseLine, (LCD_WIDTH-(baseLine:len()*7)), 232, white)
	
	lcd.blitt(2);
	
	if ( math.fmod(loopCpt, 2) == 0 ) then
		local pads = pad.read()
		
		if pads.start then break end
		if pads.A then break end
	end
	
	loopCpt = loopCpt + 1
	
	lcd.delay(5)
end

snd.stop()

-- __restart()