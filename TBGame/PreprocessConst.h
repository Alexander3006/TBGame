#pragma once

//phisics
#define gravitation					0.0005

//player options
#define player1_start_position_x	1470 
#define player1_start_position_y	515

#define player2_start_position_x	70
#define player2_start_position_y	515

#define player_width				43  
#define player_height				40
#define player_texture_x			4
#define player_texture_y			51
#define player_amount_animation		6
#define player_animation_speed		0.005
#define player_jump_speed			-0.4
#define player_run_speed			0.3

#define isPlayer1					1
#define isPlayer2					2
#define player_texture_die_x		185
#define player_texture_die_y		388
#define player_die_width			50
#define player_die_height			20


//enemy options
#define enemy_speed					0.3
#define enemy_animation_speed		0.009
#define enemy_amount_animation		5

#define enemy_ground_width			32
#define enemy_ground_height			34
#define enemy_ground_texture_x		0
#define enemy_ground_texture_y		96
#define enemy_ground_texture_die_x	223
#define enemy_ground_texture_die_y	128



#define enemy_fly_width				32
#define enemy_fly_height			32
#define enemy_fly_texture_x			0
#define enemy_fly_texture_y			65
#define enemy_fly_texture_die_x		193
#define enemy_fly_texture_die_y		63




//bullet options
#define bullet_speed				0.7
#define bullet_animation_speed		0.02
#define bullet_amount_animation		3
#define bullet_width				30
#define bullet_height				19
#define bullet_texture_x			0
#define bullet_texture_y			0


//map options
#define block_size					32
#define block_ground_grass			'1'
#define block_no					' '
#define block_ground				'0'

#define texture_block_size			34

#define texture_ground_gress_x		4
#define texture_ground_gress_y		83

#define texture_ground_x			8	
#define texture_ground_y			94

#define platform_speed				0.3
#define platform_texture_x			6
#define platform_texture_y			85

//const
#define direction_left				0
#define direction_right				1

//window options
#define window_width				1600
#define window_height				960