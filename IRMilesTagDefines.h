// This is in a separate file from IRMilesTag.h so that I can test it with milestag_test.c
// by compiling a regular binary on my pc, without the arduino libraries.
// (although, the test should really run in that environment too, what with the 8bit processor
//  and all. There is a chance that there will be integer overflows that I don't see in the
//  tests because my laptop is 64bit).

#ifndef _IR_MILES_TAG_DEFINES_H_
#define _IR_MILES_TAG_DEFINES_H_

#define MT_SIGNAL_SHOT_BITS 14
#define MT_SIGNAL_MESSAGE_BITS 24

#define MT_SIGNAL_HEADER 2400
#define MT_SIGNAL_SPACE 600
#define MT_SIGNAL_ONE 1200
#define MT_SIGNAL_ZERO 600

#define MT_SHOT(player, team, damage) (unsigned long)( \
  ((player & 127) << 6) | \
  ((team   & 3  ) << 2) | \
   (damage & 15 )         \
)

#define MT_PLAYER_VALUE(shot_data) (unsigned int)((shot_data >> 6) & 127)
#define MT_TEAM_VALUE(shot_data)   (unsigned short)((shot_data >> 2) & 3)
#define MT_DAMAGE_VALUE(shot_data) (unsigned short)(shot_data & 15)

#define MT_MSG_BYTE_1(msg) (msg >> 16) & 0xFF
#define MT_MSG_BYTE_2(msg) (msg >> 8 ) & 0xFF
#define MT_MSG_BYTE_3(msg)  msg        & 0xFF

#define MT_MSG_FOOTER 0xE8
#define MT_CMD_HEADER 0x83

#define MT_MASK_MSG MT_MSG_FOOTER
#define MT_MASK_CMD (MT_CMD_HEADER << 16) | MT_MSG_FOOTER

#define MT_MSG(byte1, byte2) ( \
	(byte1 << 16) | \
	(byte2 << 8 ) | \
	 MT_MSG_FOOTER   \
)

#define MT_CMD(command) MT_MSG(MT_CMD_HEADER, command)

#define MT_IS_MSG(msg) ((msg & MT_MASK_MSG) == MT_MASK_MSG)
#define MT_IS_CMD(cmd) ((cmd & MT_MASK_CMD) == MT_MASK_CMD)
#define MT_IS_SHOT(shot) (((shot >> 14) & 1) == 0)

#define MT_CMD_VALUE(cmd) MT_MSG_BYTE_2(cmd)
#define MT_MSG_VALUE(cmd) MT_MSG_BYTE_1(cmd)
#define MT_MSG_PARAM_VALUE(cmd) MT_MSG_BYTE_2(cmd)

#define MT_MSG_ADD_HEALTH    0x80
#define MT_MSG_ADD_ROUNDS    0x81
#define MT_MSG_CMD           0x83
#define MT_MSG_PICKUP_CLIPS  0x8A
#define MT_MSG_PICKUP_HEALTH 0x8B
#define MT_MSG_PICKUP_FLAG   0x8C

#define MT_CMD_ADMIN_KILL       0x00
#define MT_CMD_PAUSE_PLAY       0x01
#define MT_CMD_START_GAME       0x02
#define MT_CMD_RESTORE_DEFAULTS 0x03
#define MT_CMD_RESPAWN          0x04
#define MT_CMD_NEW_GAME_NOW     0x05
#define MT_CMD_FULL_AMMO        0x06
#define MT_CMD_END_GAME         0x07
#define MT_CMD_RESET_CLOCK      0x08
#define MT_CMD_INIT_PLAYER      0x0A
#define MT_CMD_EXPLODE_PLAYER   0x0B
#define MT_CMD_NEW_GAME_READY   0x0C
#define MT_CMD_FULL_HEALTH      0x0D
#define MT_CMD_FULL_ARMOUR      0x0F
#define MT_CMD_CLEAR_SCORES     0x14
#define MT_CMD_TEST_SCORES      0x15
#define MT_CMD_STUN_PLAYER      0x16
#define MT_CMD_DISARM_PLAYER    0x17

#define MT_DAMAGE_1   0x0
#define MT_DAMAGE_2   0x1
#define MT_DAMAGE_4   0x2
#define MT_DAMAGE_5   0x3
#define MT_DAMAGE_7   0x4
#define MT_DAMAGE_10  0x5
#define MT_DAMAGE_15  0x6
#define MT_DAMAGE_17  0x7
#define MT_DAMAGE_20  0x8
#define MT_DAMAGE_25  0x9
#define MT_DAMAGE_30  0xA
#define MT_DAMAGE_35  0xB
#define MT_DAMAGE_40  0xC
#define MT_DAMAGE_50  0xD
#define MT_DAMAGE_75  0xE
#define MT_DAMAGE_100 0xF

#endif
