snd.stop()

local trckNum = 1

lcd.cls()

snd.play( trckNum )

lcd.print("Playing ".. trckNum .." ".. snd.getTrackName().."\n" )

--lcd.delay( 5000 );

while( true ) do
  local pads = pad.read();

  if ( pads.start ) then
    break
  elseif ( pads.A ) then
    snd.next()
    lcd.print("Playing ".. snd.getTrackNum() .." ".. snd.getTrackName().."\n" )
    -- print("Playing ".. trckNum .." ".. snd.getTrackName() )
  end

  lcd.delay(100)

end



snd.stop()