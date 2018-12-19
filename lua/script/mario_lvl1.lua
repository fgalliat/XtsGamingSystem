
-- ; Opcodes
-- ; -------
-- ; I = Mario Start Point (Initial Position)
-- ; E = Level Termination (*** ALWAYS REQUIRED ***)
-- ;
-- ; Objectives
-- ; ----------
-- ; G = Goal
-- ;
-- ; Scenery
-- ; -------
-- ; Space = Air
-- ; C = Cloud
-- ; # = Fence
-- ; . = Dungeon Background
-- ; g = Ground (Nes Super Mario)
-- ; b = Mono Brick
-- ; B = Breakable Brick
-- ; U = Unbreakable Brick
-- ; P = Platform
-- ; ? = Item Brick
-- ; w = Water (waves)
-- ; W = Water (indepth)
-- ; l = Lave (waves, kill)
-- ; L = Lave (indepth, kill)
-- ; S = Spikes (kill)
-- ; t = Tree
-- ; T = Tree head MOA
-- ; v = Small vegetation
-- ;
-- ; Items/Enemies
-- ; -------------
-- ; 0 - Princess
-- ; 1 - Coin
-- ; 2 - Armaggedom
-- ; 3 - Wikiflaki
-- ; 4 - Mole
-- ; 5 - Minibomb

mario_lvl = {
"g                                                                                                                                       ",
"g                                                                                                                                       ",
"g                                                                                                                                       ",
"g                                                        BBBB                                                                           ",
"g      C                                       C                            C                                                           ",
"g                                                                                                                                       ",
"g                                                   BBBBBBBBBBBBBB                                                 C         BBBBBBBBBBB",
"g      C b            111111111111             1                   1                                                         BB        B",
"g                    UBBBBBBBBBBBBB            B  1  1 1 1 1 1 1 1 B            C                       C                    BB        B",
"g       bbb   ?     UUBBBBBBBBBBBBB          PPPPPPPPPPPPPPPPPPPPPPPPPPPP            ?                                       BB      BBB",
"gBBBBB             UUUBBB               T                         BB                       UU                                BBB       B",
"gT   B       B    UUUUBBBwwwwwwBBB      t                         BB                       BB                                BB        B",
"gt I B  #### B 3 UUUUUBBBWWWWWWBBB    3 t B vvvv  2  #######   5  BB         B     2       BB             ?          ?       BB  C     B",                
"gggggggggggg ggggggggggggggggggggggggggggggggggggggggggggggggggggggg        ggggggggggggggggg      UU                        BB        B",
"gggggg ggggg gBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBgwwwwwwwwgBBBBBBBBBBBBBBBg      BB                        BB        B",
}