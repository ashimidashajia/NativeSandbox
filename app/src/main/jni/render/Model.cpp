/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Model.h"

/** Constructor */
Model::Model() {
    m_shader = 0;
    m_geometry = 0;

    m_pos_attrib = -1;
    m_color_attrib = -1;
}

/** Destructor */
Model::~Model() {
    if (m_shader) {
        delete m_shader;
    }

    if (m_geometry) {
        delete m_geometry;
    }
}

/**
 * Initialises the shader.
 * Returns true if the initialization was succesfully.
 */
bool Model::init_shader(const char *vs_source, const char *fs_source) {

    m_shader = new Shader();

    if (!m_shader->init(vs_source, fs_source)) {
        delete m_shader;
        m_shader = NULL;
        return false;
    }

    // shader is ok, let's get its (common) attributes 
    m_pos_attrib = m_shader->get_position_attrib();
    m_color_attrib = m_shader->get_color_attrib();

    return true;
}

/**
 * Initializes the geometry with the given Vertices array. 
 * Returns true if the initialization was succesfully. 
 */
bool Model::init_geometry(Vertex *vertices, int vertices_count, GLenum mode) {

    m_geometry = new Geometry();

    if (!m_geometry->init(vertices, vertices_count, mode)) {
        delete m_geometry;
        m_geometry = NULL;
        return false;
    }

    return true;
}

/** 
 * Renders the object
 */
void Model::render() {

    // sets the shader as active 
    if (m_shader) {
        m_shader->set_active();
    }

    // sets the geometry active 
    if (m_geometry) {
        m_geometry->set_active(m_pos_attrib, m_color_attrib);
    }

    // TODO set uniform values 
    // glUniformMatrix2fv(mScaleRotUniform, 1, GL_FALSE, mScaleRot + 4*i);
    // glUniform2fv(mOffsetUniform, 1, mOffsets + 2*i);

    // draw the geometry
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
