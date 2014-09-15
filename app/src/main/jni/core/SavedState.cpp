/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#include "SavedState.h"

/** Constructor */
SavedState::SavedState() {
}

/** Destructor */
SavedState::~SavedState() {
}

/**
 * Gets the size to allocate for the saved state.
 */
size_t SavedState::get_saved_state_size() {
    return 0;
}

/**
 * Reads the saved data from the given pointer.
 */
void SavedState::read_saved_state_data(void *saved_data, size_t saved_data_size) {
}

/**
 * Writes the saved data into the given pointer.
 * The memory has already been allocated according to get_saved_state_size().
 */
void SavedState::write_saved_state_data(void *saved_data) {
}
