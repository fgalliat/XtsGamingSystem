dofile("./script/screenlib.lua")

local pads

snd.stop()

lcd.sload(0, "/FF1SHEET.PCT")
lcd.sload(1, "/MECHS.PCT")
lcd.sload(2, "/DRMARIO.PCT")

local sFF1  = 0
local sMECH = 1
local sMARI = 2
-- // -====================================-
-- // -====================================-

local drmario = Sprite.new(sMARI, 12, 12);
local pill00 = SpriteGrabb.new(drmario, 0,0)
local pill01 = SpriteGrabb.new(drmario, 1,0)
local pill02 = SpriteGrabb.new(drmario, 2,0)
local pill03 = SpriteGrabb.new(drmario, 3,0)

local pill0 = { pill00, pill01, pill02, pill03 }

local frameCpt = 0

while(true) do
    lcd.blitt(0)
        lcd.fx(1,1)
        lcd.cursor(1,1)

        lcd.sback(sMECH, (320-160)/2, (240-128)/2)

        for i=1,4 do
            lcd.ssprite(sFF1, 2+(16*(i*2)),2, 16,16, (16*i),0)
        end

        for i=1,4 do
            drmario:draw(2+(12*(i*2)),16+4, i-1, 0)
            drmario:draw(2+(12*(i*2)),16+4+20, (i-1)+6, 0)
        end

        pill0[ (frameCpt%4)+1 ]:draw( 100,100 )

		-- if ( frameCpt % 3 == 0 ) then
        pads = pad.read()
        -- end

        if ( snd.isPlaying() ) then
            lcd.print("[MP3] ")
        end

        if ( pads.changed ) then

            if ( pads.A ) then lcd.print("[1] "); end
            if ( pads.B ) then lcd.print("[2] "); end
            if ( pads.start ) then lcd.print("[Start] "); break; end

            if ( pads.up    ) then lcd.print("Up "); end
            if ( pads.down  ) then lcd.print("Down "); end
            if ( pads.left  ) then lcd.print("Left "); end
            if ( pads.right ) then lcd.print("Right "); end

            -- if ( pads.down and (pads.A or pads.B) ) then
                if ( pads.down ) then
                    snd.play(22)
                end

                if ( pads.up ) then
                    snd.stop()
                end

            lcd.blitt(2)


            while( pad.read().atLeastOne ) do
                lcd.delay(10);
            end
        end
    lcd.blitt(2)
    lcd.delay(10);

    frameCpt = frameCpt + 1
end