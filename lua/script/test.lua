function delay(ms)
  lcd.delay(ms)
end


print( "coucou " .. 3.14 )



lcd.cls()

lcd.blitt(2)

--delay()


--lcd.bpp( "/BLAST.BPP" )

lcd.pct( "/CARO.PCT", 0, 0 )

lcd.print("Hello World !")

lcd.rect(20, 20, 160, 80, 1, 8) -- pink flat rect

lcd.circle(20, 20, 80, 0, 6) -- green outlined circle

lcd.line(20, 20, 160, 80, 1) -- white line


lcd.pct( "", 160, 0 )
lcd.pct( "/FF1SHEET.PCT", 0, 128 )
lcd.pct( "/MECHS.PCT", 160, 128 )

lcd.sprite( "/CARO.PCT", 160-32, 120-32, 64, 64, 30, 50 )

delay(700)
for i=1, 45 do
  lcd.fx( 1, 45+i, 90, 45, 9 ) -- light blue balls
  delay(1)
end

delay(700)
for i=1, 50 do
  lcd.fx( 2, 50, 100, 1, 8 ) -- pink stars
end

delay(700)

-- height 0..240 // attr 0..3
function itrsf(height, attr)
  hh = math.floor( height / 3.80 )
  val= (hh * 4) + attr
  
  if ( val == 0 ) then val = 1 end
  
  return val
end


arry = { 1,2,3,4,5,6,7,8,9,10,
         1,2,3,4,5,6,7,8,9,10,
         1,2,3,4,5,6,7,8,9,10,
         1,2 } -- 32 long

for i=1, 32 do
  arry[i] = itrsf( math.random(240), 2 )  
end


lcd.fx( 3, arry )





