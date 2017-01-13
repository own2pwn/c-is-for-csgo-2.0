#pragma once
#include <Windows.h>

typedef void* HEntity;

/*
 * @return: Weather the entity is in Dormant state
 */
extern BOOL IsDormant(HEntity entity);

/*
 * @return: Team number of the entity
 */
extern int GetTeamNum(HEntity entity);

/*
 * @return: Class id of the entity
 */
extern int GetClassId(HEntity entity);