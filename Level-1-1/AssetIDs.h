#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_SHROOM 6
#define OBJECT_TYPE_MYSTERY_BLOCK 7
#define OBJECT_TYPE_LEAF 8
#define OBJECT_TYPE_TILE 9
#define OBJECT_TYPE_BLOCK 10
#define OBJECT_TYPE_FIRE_PLANT 11
#define OBJECT_TYPE_FIRE_BALL 12
#define OBJECT_TYPE_KOOPA 13
#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_RACCOON (ID_SPRITE_MARIO + 4000)
#define ID_SPRITE_MARIO_RACCOON_IDLE (ID_SPRITE_MARIO_RACCOON + 100)
#define ID_SPRITE_MARIO_RACCOON_IDLE_LEFT (ID_SPRITE_MARIO_RACCOON_IDLE + 10)
#define ID_SPRITE_MARIO_RACCOON_IDLE_RIGHT (ID_SPRITE_MARIO_RACCOON_IDLE + 20)

#define ID_SPRITE_MARIO_RACCOON_WALKING (ID_SPRITE_MARIO_RACCOON + 200)
#define ID_SPRITE_MARIO_RACCOON_WALKING_LEFT (ID_SPRITE_MARIO_RACCOON_WALKING + 10)
#define ID_SPRITE_MARIO_RACCOON_WALKING_RIGHT (ID_SPRITE_MARIO_RACCOON_WALKING + 20)
#define ID_SPRITE_MARIO_RACCOON_RUNNING (ID_SPRITE_MARIO_RACCOON + 300)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_LEFT (ID_SPRITE_MARIO_RACCOON_RUNNING + 10)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_RIGHT (ID_SPRITE_MARIO_RACCOON_RUNNING + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP (ID_SPRITE_MARIO_RACCOON + 400)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK (ID_SPRITE_MARIO_RACCOON_JUMP + 10)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN (ID_SPRITE_MARIO_RACCOON_JUMP + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_RACCOON_SIT (ID_SPRITE_MARIO_RACCOON + 500)
#define ID_SPRITE_MARIO_RACCOON_SIT_LEFT (ID_SPRITE_MARIO_RACCOON_SIT + 10)
#define ID_SPRITE_MARIO_RACCOON_SIT_RIGHT (ID_SPRITE_MARIO_RACCOON_SIT + 20)
#define ID_SPRITE_MARIO_RACCOON_BRACE (ID_SPRITE_MARIO_RACCOON + 600)
#define ID_SPRITE_MARIO_RACCOON_BRACE_LEFT (ID_SPRITE_MARIO_RACCOON_BRACE + 10)
#define ID_SPRITE_MARIO_RACCOON_BRACE_RIGHT (ID_SPRITE_MARIO_RACCOON_BRACE + 20)
#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_PIPE_MOUTH_LEFT 25000
#define ID_SPRITE_PIPE_MOUTH_RIGHT 25100
#define ID_SPRITE_PIPE_STEM_LEFT 25200
#define ID_SPRITE_PIPE_STEM_RIGHT 25300

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_PLANT_VINE 31100
#define ID_SPRITE_PLANT_HEAD_RED_BOTTOM_LEFT_OPEN 31400
#define ID_SPRITE_PLANT_HEAD_RED_BOTTOM_LEFT_CLOSE 31410
#define ID_SPRITE_PLANT_HEAD_RED_TOP_LEFT_OPEN 31420
#define ID_SPRITE_PLANT_HEAD_RED_TOP_LEFT_CLOSE 31430
#define ID_SPRITE_PLANT_HEAD_RED_TOP_RIGHT_OPEN 31440
#define ID_SPRITE_PLANT_HEAD_RED_TOP_RIGHT_CLOSE 31450
#define ID_SPRITE_PLANT_HEAD_RED_BOTTOM_RIGHT_OPEN 31460
#define ID_SPRITE_PLANT_HEAD_RED_BOTTOM_RIGHT_CLOSE 31470

#define ID_SPRITE_FIRE_BALL 32000
#define ID_SPRITE_FIRE_BALL_2 32100
#define ID_SPRITE_FIRE_BALL_3 32200
#define ID_SPRITE_FIRE_BALL_4 32300

#define ID_SPRITE_KOOPA_IDLE_LEFT 33100
#define ID_SPRITE_KOOPA_WALK_LEFT 33110
#define ID_SPRITE_KOOPA_IDLE_RIGHT 33200
#define ID_SPRITE_KOOPA_WALK_RIGHT 33210

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_SHROOM 60000

#define ID_SPRITE_GROUND 70000
#define ID_SPRITE_GROUND_BEGIN (ID_SPRITE_GROUND+1000)
#define ID_SPRITE_GROUND_MIDDLE (ID_SPRITE_GROUND+2000)
#define ID_SPRITE_GROUND_END (ID_SPRITE_GROUND+3000)

#define ID_SPRITE_UNDERGROUND 70100
#define ID_SPRITE_UNDERGROUND_BEGIN (ID_SPRITE_UNDERGROUND+1000)
#define ID_SPRITE_UNDERGROUND_MIDDLE (ID_SPRITE_UNDERGROUND+2000)
#define ID_SPRITE_UNDERGROUND_END (ID_SPRITE_UNDERGROUND+3000)

#define ID_SPRITE_MYSTERY_BLOCK 80000
#define ID_SPRITE_MYSTERY_BLOCK_2 81000
#define ID_SPRITE_MYSTERY_BLOCK_3 82000
#define ID_SPRITE_MYSTERY_BLOCK_4 83000
#define ID_SPRITE_MYSTERY_BLOCK_5 84000

#define ID_SPRITE_LEAF 90000

#define ID_SPRITE_SMALL_BUSH 95000

#define ID_SPRITE_BIG_BUSH_TOP_LEFT 96000
#define ID_SPRITE_BIG_BUSH_TOP_RIGHT 96100
#define ID_SPRITE_BIG_BUSH_MIDDLE_LEFT 96200
#define ID_SPRITE_BIG_BUSH_MIDDLE_RIGHT 96300
#define ID_SPRITE_BIG_BUSH_TOP_LEFT_2 96400
#define ID_SPRITE_BIG_BUSH_TOP_RIGHT_2 96500
#define ID_SPRITE_BIG_BUSH_MIDDLE 96600

#define ID_SPRITE_CLOUD_TOP_LEFT 97000
#define ID_SPRITE_CLOUD_TOP_MIDDLE 97100
#define ID_SPRITE_CLOUD_TOP_RIGHT 97200
#define ID_SPRITE_CLOUD_BOTTOM_LEFT 97300
#define ID_SPRITE_CLOUD_BOTTOM_MIDDLE 97400
#define ID_SPRITE_CLOUD_BOTTOM_RIGHT 97500

#define ID_SPRITE_BOX_TOP_LEFT_PINK 98100
#define ID_SPRITE_BOX_TOP_MIDDLE_PINK 98110
#define ID_SPRITE_BOX_TOP_RIGHT_PINK 98120
#define ID_SPRITE_BOX_MIDDLE_LEFT_PINK 98130
#define ID_SPRITE_BOX_MIDDLE_PINK 98140
#define ID_SPRITE_BOX_MIDDLE_RIGHT_PINK 98150
#define ID_SPRITE_BOX_BOTTOM_LEFT_PINK 98160
#define ID_SPRITE_BOX_BOTTOM_MIDDLE_PINK 98170
#define ID_SPRITE_BOX_BOTTOM_RIGHT_PINK 98180

#define ID_SPRITE_BOX_TOP_LEFT_BLUE 98200
#define ID_SPRITE_BOX_TOP_MIDDLE_BLUE 98210
#define ID_SPRITE_BOX_TOP_RIGHT_BLUE 98220
#define ID_SPRITE_BOX_MIDDLE_LEFT_BLUE 98230
#define ID_SPRITE_BOX_MIDDLE_BLUE 98240
#define ID_SPRITE_BOX_MIDDLE_RIGHT_BLUE 98250
#define ID_SPRITE_BOX_BOTTOM_LEFT_BLUE 98260
#define ID_SPRITE_BOX_BOTTOM_MIDDLE_BLUE 98270
#define ID_SPRITE_BOX_BOTTOM_RIGHT_BLUE 98280

#define ID_SPRITE_BOX_TOP_LEFT_GREEN 98300
#define ID_SPRITE_BOX_TOP_MIDDLE_GREEN 98310
#define ID_SPRITE_BOX_TOP_RIGHT_GREEN 98320
#define ID_SPRITE_BOX_MIDDLE_LEFT_GREEN 98330
#define ID_SPRITE_BOX_MIDDLE_GREEN 98340
#define ID_SPRITE_BOX_MIDDLE_RIGHT_GREEN 98350
#define ID_SPRITE_BOX_BOTTOM_LEFT_GREEN 98360
#define ID_SPRITE_BOX_BOTTOM_MIDDLE_GREEN 98370
#define ID_SPRITE_BOX_BOTTOM_RIGHT_GREEN 98380

#define ID_SPRITE_BOX_TOP_LEFT_WHITE 98400
#define ID_SPRITE_BOX_TOP_MIDDLE_WHITE 98410
#define ID_SPRITE_BOX_TOP_RIGHT_WHITE 98420
#define ID_SPRITE_BOX_MIDDLE_LEFT_WHITE 98430
#define ID_SPRITE_BOX_MIDDLE_WHITE 98440
#define ID_SPRITE_BOX_MIDDLE_RIGHT_WHITE 98450
#define ID_SPRITE_BOX_BOTTOM_LEFT_WHITE 98460
#define ID_SPRITE_BOX_BOTTOM_MIDDLE_WHITE 98470
#define ID_SPRITE_BOX_BOTTOM_RIGHT_WHITE 98480

#define ID_SPRITE_BOX_SHADOW_HALF 98500
#define ID_SPRITE_BOX_SHADOW_FULL 98510

#define ID_SPRITE_HIDDEN 100000