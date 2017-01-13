#pragma once

typedef void* HBasePlayer;

/*
 * @return: Health of the base player
 */
extern int GetHealth(HBasePlayer basePlayer);

/*
 * @return: Flags of the base player
 */
extern unsigned int GetFlags(HBasePlayer basePlayer);