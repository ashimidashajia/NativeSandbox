#ifndef SAVED_STATE_H
#define SAVED_STATE_H


class SavedState {

private :

    int32_t m_x;
    int32_t m_y;

public:

    SavedState();

    ~SavedState();

    void set_position(int32_t x, int32_t y);

    /**
     * the size to allocate for the saved state
     */
    size_t get_saved_state_size();

    void get_saved_state_data(void *saved_data);

    void load_saved_state_data(void *saved_data);
};

#endif