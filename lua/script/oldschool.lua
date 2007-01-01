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
-- local music = "./MUSIC/Automation_CD_Menu_186_Music_Atari_ST.mp3"
local music = "022"

local rndZik = math.random(2000)/1000

if ( rndZik >= 1) then
  --music = "./MUSIC/MGR_EmpireMenuIntro.mp3"
  music = "023"
end


local playMusic = true

-- if not luaAndro then
-- 	Mp3me.load(music)
-- end
-- =====================================

local textStr  = "...Hello : here is my XtreamLua Like PLAYER for >PC >PSP >ANDROID..."
local textStr2 = "} brought to you by Xtase {"

local textComp = compileBigLetterString( textStr )
local textComp2 = compileSmallLetterString( textStr2 )

local textX = SCREEN_WIDTH
local textX2 = -( textStr2:len() * _SMALLCHAR_WIDTH_REAL )

local screenIter = 0

local yetPlayingMusic = false

while true do
	-- screen:clear(black)
	lcd.cls()
 	
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
 	
 	
 	screen:print(272, 242, "Starfield for PSP by Shine", white)
 	screen:print(272, 254, "Modififed for YOU by Xtase", white)
	
--drawBigLetterString(textStr, textX, 100, function(i)
drawBigLetterCompiledString(textComp, textX, 100, function(i)
  if ( i % 2 == 0 ) then return 100 + (math.cos( ( screenIter/2 ) % 360 ) * 3.0)
  else                   return 100 + (math.cos( ( ( screenIter/2) + 5 ) % 360 ) * 3.0) 
  end
end )

--[[
--]]
drawSmallLetterCompiledString(textComp2, textX2, 100, function(i)
  --[[if ( i % 2 == 0 ) then return SCREEN_HEIGHT - 30 -- + (math.cos( ( screenIter/2 ) % 360 ) * 3.0)
  else                   return 130 -- + (math.cos( ( ( screenIter/2) + 5 ) % 360 ) * 3.0) 
  end --]]
  
  return SCREEN_HEIGHT - 30
  
end )


	textX = textX - 5
	if ( textX <= -(textStr:len() * _BIGCHAR_WIDTH_REAL ) ) then
	  textX = SCREEN_WIDTH
	end
	
	textX2 = textX2 + 5
	if ( textX2 >= SCREEN_WIDTH ) then
	  textX2 = -(textStr2:len() * _SMALLCHAR_WIDTH_REAL )
	end
	
	
	screen:waitVblankStart()
	screen:flip()
	screenIter = screenIter + 1
	
	if Controls.read():start() then break end
	if Controls.read():triangle() then break end
end

Mp3me.stop()

__restart()