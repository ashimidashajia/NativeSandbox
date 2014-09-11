
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