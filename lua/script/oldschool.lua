--
-- Star Field Sample
--

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

local textStr  = "...Hello : here is my XtreamLua Like PLAYER for >PC >PSP >ANDROID..."
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
ALPHABET = "ABCDEFGHIJKMNOPQRSTUVWXYZ 0123456789<$>._:"
function findChar(ch)
	local n = string.find( ALPHABET, ""..ch, 1, true )
	if ( n == nil ) then return -1 end
	return n
end

function parseText(str)
	local st2 = ""
	local stc= {}
	local i
	for i=1, str:len() do
		local ch = string.sub(str, i,i) -- get one char
		ch = string.upper(ch)
		-- print( ch )
		local nn = findChar( ch )
		if ( nn == -1 ) then nn = 42 end -- replace by '...' ('_')
		st2 = st2.. string.sub(ALPHABET, nn,nn)
		stc[i] = nn
	end
	return st2, stc
end

while true do
	lcd.cls() -- NIT YET done by NFX
 	
 	-- ===== Music Playback ========
 	if ( playMusic ) then
 		--   if not luaAndro then
		 -- 	Mp3me.play()
			-- 	if Mp3me.percent() >= 99 then
			-- 		Mp3me.stop()
			-- 		Mp3me.load(music)
					
			-- 		-- with that direct play ... ? still fails for percent() ?
			-- 		Mp3me.play()
			--  	end
	
		 -- 	--if Controls_read_cross() then
		 --  	--	Mp3me.stop()
		 --  	--end
			-- 	----  ".. Mp3me.percent() will fail if cross_pessed cf inconsistent function....
			-- 	---- fails also when 1st song stops
			--   ----_print(5, "mp3 : ".. Mp3me.percent() .."%" )
			-- else
			--   -- lua android mode
			  
			--   -- will loop .....
			--   if ( not Mp3Player:isHackedLocalFsMusicPlaying(music) ) then
			--     Mp3Player:playHackedLocalFsMusic(music)
			--   end
			  
		 -- end
	 if (not yetPlayingMusic) then
		 snd.play(music)
		 -- TODO : loop
		 yetPlayingMusic = true
	 end
   end
 	-- =============================
 	
 	
 	-- drawStarFieldFrame(screenIter)
 	lcd.fx(1)
 	
 	-- lcd.sprite( "/.PCT", (320-160)/2, (240-128)/2, 16, 16, 0,0 )
 	lcd.sprite( nil, (320-160)/2, (240-128)/2, 16, 16, 0,0 )
 	lcd.sprite( nil, ((320-160)/2)+16+1, (240-128)/2, 16, 16, 17,17 )
 	
 	
 	local str,stc = parseText( "abCf4#67<.:" )
 	lcd.dispStr( str, 10, 120, white )
 	
 	-- lcd.dispStr( parseText( "abCf4#67<.:" ), 10, 120, white )
 	-- print( #stc )
 	local i
 	local x=10
 	local y=180
 	local xx = 0
 	local yy = 0
 	for i = 1, #stc do
 		xx = math.fmod( (stc[i]-1), 9 )
 		yy = math.floor( (stc[i]-1) / 9 )
 		lcd.sprite( nil, x+( (i-1)*17 ), y, 16, 16, xx*17,yy*17 )
 	end
 	
 	lcd.dispStr( "Starfield for PSP by Shine", 10, 222, white)
 	lcd.dispStr( "Modififed for YOU by Xtase", 10, 232, white)
	
-- --drawBigLetterString(textStr, textX, 100, function(i)
-- drawBigLetterCompiledString(textComp, textX, 100, function(i)
--   if ( i % 2 == 0 ) then return 100 + (math.cos( ( screenIter/2 ) % 360 ) * 3.0)
--   else                   return 100 + (math.cos( ( ( screenIter/2) + 5 ) % 360 ) * 3.0) 
--   end
-- end )

-- drawSmallLetterCompiledString(textComp2, textX2, 100, function(i)
--   return SCREEN_HEIGHT - 30
-- end )


	textX = textX - 5
	if ( textX <= -(textStr:len() * _BIGCHAR_WIDTH_REAL ) ) then
	  textX = SCREEN_WIDTH
	end
	
	textX2 = textX2 + 5
	if ( textX2 >= SCREEN_WIDTH ) then
	  textX2 = -(textStr2:len() * _SMALLCHAR_WIDTH_REAL )
	end
	
	
	-- screen:waitVblankStart()
	-- screen:flip()
	screenIter = screenIter + 1
	
	local pads = pad.read()
	
	if pads.start then break end
	if pads.A then break end
end

snd.stop()

-- __restart()