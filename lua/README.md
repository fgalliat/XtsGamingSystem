# XtsGamingSystem (lua)

- add PCT bigger than 160x128 (**PCT format already allows 16b bounds**)

- add BCK

- add more Sprites (PCT & PCTSprite shares same mem. seg)

- **ideas** :

  - allocate 4x 320x240px Slots for **backgrounds** (w/o transparency)

    - 4x 153600bytes => 614400bytes => 600KB
    - using memset() in this case
  - for **sprites** => could use palettes color to reduce 1Slot size ?
  - use a copy of drawRGB16 that copies each pixels & check for transparency color

    - so, not using memset() in this case
  - loadPCTSlot("/BOOT.PCT", 0) 0 is the slotNum ( 0->1 BCK / 2->5 Sprites -- but just a convention )
  - drawSlotBack( 0, 0, 0 ) // slotNum, x, y (w,h inside PCT file/slot )
  - drawSlotSprite( 2, 0,0, 16,16, 0,0, 0x1020 ) // slotNum, x, y , spW,spH,spX,spY, transparencyColor
  - class GfxSlot() { u8 slotNum; u16 w,h; u16 raster[320x240]; }
  - **lcd.clip() => may be usefull, but** may need to draw in whole screen finally...
    - & for arm : maybe slowly than memcpy...