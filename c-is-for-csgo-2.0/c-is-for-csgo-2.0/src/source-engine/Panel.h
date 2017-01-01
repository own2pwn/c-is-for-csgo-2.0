#pragma once

typedef unsigned int VPANEL;

/*
 * @return: Pointer to Source Engine Panel interface
 */
extern void *GetPanel();

/*
 * @return: Name of the given panel
 */
extern const char *Panel_GetName(VPANEL vpanel);