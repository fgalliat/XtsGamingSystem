cls()

function halt()
    print("Bye !")
    os.exit()
end



SPR_SIZE = 64
CHOICE = 1

CHOICES = {
    { title="Settings", items={ { lbl="WiFi",      items={  {lbl="UP",   script="wifiUp.lua"}, 
                                                            {lbl="DOWN", script="wifiDown.lua"}, 
                                                            {lbl="SHOW", script="wifiShow.lua"}, 
                                                            {lbl="+NEW", script="wifiNew.lua"} } },
                                { lbl="Halt",      code="halt()" } } },

    { title="Apps",     items={ { lbl="Console >", items={ {lbl="GB",  exec="../gb/xgb"}, 
                                                           {lbl="NES", exec="../nes/xnes ../nes/roms/Dr.\\ Mario\\ \\(E\\)\\ \\[\\!\\].nes"} } },
                                { lbl="Script >",  items={ {lbl="Demo",  script="test.lua"}, 
                                                           {lbl="Sound", script="sound.lua"} } },
                                { lbl="Native >",  items={} },
                                { lbl="Bash",      exec="/bin/bash" } } },

    { title="Zik",      items={ { lbl="Jukebox",   script="jukebox.lua" } } }
}

function razScreen()
    lcd.rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, 1, 3)
end

while true do

    --lcd.rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, 1, 3)
    razScreen()

    -- Settings
    lcd.sprite( "/SYSMENU.PCT", ((SCREEN_WIDTH-SPR_SIZE)/2), ((SCREEN_HEIGHT-SPR_SIZE)/2), SPR_SIZE, SPR_SIZE, SPR_SIZE, 0 )
    -- Apps
    lcd.sprite( nil, ((SCREEN_WIDTH-SPR_SIZE)/2)-SPR_SIZE-16, ((SCREEN_HEIGHT-SPR_SIZE)/2), SPR_SIZE, SPR_SIZE, 0, 0 )
    -- Zik
    lcd.sprite( nil, ((SCREEN_WIDTH-SPR_SIZE)/2)+SPR_SIZE+16, ((SCREEN_HEIGHT-SPR_SIZE)/2), SPR_SIZE, SPR_SIZE, 0, SPR_SIZE )

    function rectBorder(rectn, state)
        local clr = 3
        if (state) then clr = 4 end

        if ( rectn == 0 ) then
            lcd.rect(((SCREEN_WIDTH-SPR_SIZE)/2)-SPR_SIZE-16-4, ((SCREEN_HEIGHT-SPR_SIZE)/2)-4,SPR_SIZE+8, SPR_SIZE+8, 0, clr)
        elseif ( rectn == 1 ) then
            lcd.rect(((SCREEN_WIDTH-SPR_SIZE)/2)-4, ((SCREEN_HEIGHT-SPR_SIZE)/2)-4,SPR_SIZE+8, SPR_SIZE+8, 0, clr)
        elseif ( rectn == 2 ) then
            lcd.rect(((SCREEN_WIDTH-SPR_SIZE)/2)+SPR_SIZE+16-4, ((SCREEN_HEIGHT-SPR_SIZE)/2)-4,SPR_SIZE+8, SPR_SIZE+8, 0, clr)
        end
    end

    local doesQuit = false;

    local rState = true;

    while (true) do

        rectBorder(CHOICE, rState)

        local pads = pad.read()

        if ( pads.start ) then
            doesQuit = true
            break
        elseif ( pads.left and CHOICE > 0 ) then
            rectBorder(CHOICE, false)
            CHOICE = CHOICE-1
        elseif ( pads.right and CHOICE < 2 ) then
            rectBorder(CHOICE, false)
            CHOICE = CHOICE+1
        elseif ( pads.A ) then
            -- GOTO : subLevel
            break
        end

        delay(100)
        rState = not rState

    end

    function drawSubMenu(item)
        lcd.rect(20,20,SCREEN_WIDTH-40, SCREEN_HEIGHT-40, 1, 4) -- fill dark
        lcd.rect(24,24,SCREEN_WIDTH-48, SCREEN_HEIGHT-48, 0, 3) -- draw medium

        if ( item.title ~= nil ) then
            lcd.cursor(5,4); lcd.print( item.title );
        elseif ( item.lbl ~= nil ) then
            lcd.cursor(5,4); lcd.print( item.lbl );
        end
    end


    -- subLevel
    if ( not doesQuit ) then

        delay(100) -- release keyPad

        local megaItem = CHOICES[ CHOICE+1 ];
        local SUB_CHOICE = 1;

        local SUB_LEVEL = 1;
        local curParentItem = megaItem;

        drawSubMenu( curParentItem );

        while (not doesQuit) do

            local doesReturn = false;

            local nbItems = #(curParentItem.items)
            local i=1

            lcd.rect( (5+1) * 6, (4+2+1)*8, 6, 10*8, 1, 4 ); -- fill dark (hide cursor)

            for i = 1,nbItems do
                local subItem = curParentItem.items[i]
                lcd.cursor(5+3,4+2+i); lcd.print( subItem.lbl )

                lcd.cursor(5+1,4+2+i); 
                if ( i == SUB_CHOICE ) then
                    lcd.print(">")
                else
                    -- lcd.print("|")
                end
            end

            delay(100) -- to release keyPad
            while (true) do
                local pads = pad.read()

                if ( pads.start ) then
                    --doesQuit = true
                    --break
                elseif ( pads.up and SUB_CHOICE > 1 ) then
                    SUB_CHOICE = SUB_CHOICE - 1
                    break
                elseif ( pads.down and SUB_CHOICE < nbItems ) then
                    SUB_CHOICE = SUB_CHOICE + 1
                    break
                elseif ( pads.A ) then
                    local subItem = curParentItem.items[SUB_CHOICE]

                    if ( subItem.code ~= nil ) then
                        -- dostring( subItem.code );
                        local execFunc = assert( loadstring( subItem.code ) );
                        if ( execFunc ~= nil ) then execFunc() end

                    elseif ( subItem.items ~= nil ) then
                        -- dynamic tree construction
                        subItem.parent = curParentItem
                        SUB_CHOICE = 1;
                        SUB_LEVEL = SUB_LEVEL + 1;
                        curParentItem = subItem;
                        drawSubMenu( curParentItem );
                        break; -- enter in it....

                    elseif ( subItem.exec ~= nil ) then
                        -- print("try to sysexec: ".. subItem.exec)
                        -- !! BEWARE : each native will try to re-init console -> add a file flag
                        os.execute( subItem.exec );

                    elseif ( subItem.script ~= nil ) then
                        pcall( function() dofile( SCRIPT_PATH.. subItem.script ) end )

                    end

                    razScreen()
                    drawSubMenu( curParentItem );

                    break
                elseif ( pads.B ) then
                    SUB_LEVEL = SUB_LEVEL - 1;
                    if ( SUB_LEVEL < 1 ) then
                        doesReturn = true
                    else
                        curParentItem = curParentItem.parent;
                        SUB_CHOICE = 1;
                        drawSubMenu( curParentItem );
                    end
                    
                    break
                end

                delay(100)
            end
            delay(100)
            if ( doesReturn ) then break; end
        end
    end

if ( doesQuit ) then
    break
end

end