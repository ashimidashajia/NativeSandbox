/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef SAVED_STATE_H
#define SAVED_STATE_H

#include <stdint.h>

/**
 * This class handles the saving of the game state, to let the user come back to where he had left off. 
 */
class SavedState {


public:

    /** Constructor */
    SavedState();

    /** Destructor */
    ~SavedState();

    /**
     * Gets the size to allocate for the saved state.
     */
    size_t get_saved_state_size();

    /**
     * Reads the saved data from the given pointer. 
     */
    void read_saved_state_data(void *saved_data, size_t saved_data_size);

    /**
     * Writes the saved data into the given pointer. 
     * The memory has already been allocated according to get_saved_state_size(). 
     */
    void write_saved_state_data(void *saved_data);

private :

};

#endif
