/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#pragma once
#include "Interface.h"
#include "Entity.h"

/*
* @return: Pointer to Source Engine EntityList interface
*/
extern inline HInterface GetEntityList(void);

/*
 * @brief: Gets an entity from an index
 * @return: Pointer to entity at given index
 */
extern HEntity GetEntity(int index);