/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef MODEL_H
#define MODEL_H

#include <GLES2/gl2.h>
#include "Renderable.h"
#include "Geometry.h"
#include "Shader.h"


/**
 * The Model class holds a Geometry, as well as a Shader program
 */
class Model : public Renderable {

public:

    /** Constructor */
    Model();

    /** Destructor */
    ~Model();

    /**
     * Initialises the shader.
     * Returns true if the initialization was succesfully.
     */
    bool init_shader(const char *vs_source, const char *fs_source);

    /**
     * Initializes the geometry with the given Vertices array.
     * Returns true if the initialization was succesfully.
     */
    bool init_geometry(Vertex *vertices, int vertices_count, GLenum mode);

    /**
     * Renders the object
     */
    virtual void render();

private:

    /** the geometry */
    Geometry *m_geometry;

    /** the shader */
    Shader *m_shader;

    /** the shader attributes */
    GLint m_pos_attrib;
    GLint m_color_attrib;
};

#endif
