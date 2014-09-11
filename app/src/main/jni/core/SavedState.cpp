/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 
#include "SavedState.h"

SavedState::SavedState() {
    m_x = 0;
    m_y = 0;
}

SavedState::~SavedState() {

}

void SavedState::set_position(int32_t x, int32_t y) {
    m_x = x;
    m_y = y;
}
