/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef VECTOR_H
#define VECTOR_H

/**
 * Describes a standard 3D Vector
 */
class Vector {

public:

    /** Constructor*/
    Vector();
    Vector(float *data);

    /** Destructor */
    ~Vector();
    
    inline float x(){ return m_data[0]; }
    inline float y(){ return m_data[1]; }
    inline float z(){ return m_data[2]; }
    
    void normalize();
    float magnitude();
    float square_magnitude();
    
    static float dot_product(Vector *a, Vector *b);
    static void cross_product(Vector *a, Vector *b, Vector *out);
    
private:

    /** Data */
    float *m_data;

};

#endif
