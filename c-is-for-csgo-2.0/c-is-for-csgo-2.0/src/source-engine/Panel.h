/* ===============================================
   Creator: Szwagi
   Notice: Copyright (C) 2017. All Rights Reserved.
   =============================================== */
   
#pragma once
#include "Interface.h"

typedef unsigned int VPANEL;

/*
 * @return: Pointer to Source Engine Panel interface
 */
extern inline HInterface GetPanel(void);

/*
 * @return: Name of the given panel
 */
extern const char *Panel_GetName(VPANEL vpanel);