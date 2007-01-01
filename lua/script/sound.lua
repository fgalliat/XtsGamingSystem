-- snd.stop()

local trckNum = 1

lcd.cls()

vol = 30
--snd.setvolume( vol )

snd.play( trckNum )
--snd.pause() -- else music don't starts
lcd.print("Playing ".. trckNum .." ".. snd.getTrackName().."\n" )


function waitPadReleased()
  local lpads = pad.read();
  while( true ) do
    lpads = pad.read()
    if ( lpads.A or lpads.B or lpads.up or lpads.down or lpads.left or lpads.right ) then
    else
     break
    end
  end
end


while( true ) do
  local pads = pad.read();
  waitPadReleased()

  if ( pads.start ) then
    break
  elseif ( pads.A ) then
    snd.next()
    trckNum = snd.getTrackNum()
    lcd.print("Playing ".. snd.getTrackNum() .." ".. snd.getTrackName().."\n" )
  elseif ( pads.right ) then
    trckNum = trckNum + 10
	snd.play( trckNum )
	lcd.print("Playing ".. trckNum .." ".. snd.getTrackName().."\n" )
  elseif ( pads.down ) then
    vol = vol - 5
    snd.setvolume( vol )
  elseif ( pads.up ) then
    vol = vol + 5
    snd.setvolume( vol )
  end

  lcd.delay(30)

end



snd.stop()