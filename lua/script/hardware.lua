LCD_WIDTH = 320
LCD_HEIGTH = 240

local pads

snd.stop()

lcd.sload(0, "/FF1SHEET.PCT")
lcd.sload(1, "/MECHS.PCT")

while(true) do
    lcd.blitt(0)
        lcd.fx(1,1)
        lcd.cursor(1,1)

        lcd.sback(1, (320-160)/2, (240-128)/2)

        for i=1,4 do
            lcd.ssprite(0, 2+(16*(i*2)),2, 16,16, (16*i),0)
        end

        pads = pad.read()

        if ( snd.isPlaying() ) then
            lcd.print("[MP3] ")
        end

        if ( pads.changed ) then

            if ( pads.A ) then lcd.print("[1] "); end
            if ( pads.B ) then lcd.print("[2] "); end
            if ( pads.start ) then lcd.print("[Start] "); end

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
end