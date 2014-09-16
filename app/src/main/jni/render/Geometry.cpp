/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Geometry.h"

/** Constructor */
Geometry::Geometry() {
    m_vertex_buffer = 0;
}

/** Destructor */
Geometry::~Geometry() {
}

/**
 * Initializes the geometry with the given Vertices array. The vertices are drawn with a simple
 * mode (can be GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES, GL_TRIANGLE_STRIP,
 * GL_TRIANGLE_FAN).
 */
bool Geometry::init(Vertex *vertices, int vertices_count, GLenum mode) {

    // generate the buffer slot
    glGenBuffers(1, &m_vertex_buffer);

    // bind and fill the buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    m_vertices_count = vertices_count;
    m_indices = 0;
    m_indices_count = 0;

    // save the drawing mode
    m_array_mode = mode;
}

/**
 * Initializes the geometry with the given vertices and indices arrays.
 * The vertices are drawn as triangles, based on the given indices.
 */
bool Geometry::init(Vertex *vertices, int vertices_count, GLubyte *indices, int indices_count) {
    // generate the buffer slot
    glGenBuffers(1, &m_vertex_buffer);

    // bind and fill the buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    // save the vertices count
    m_vertices_count = vertices_count;

    m_indices = indices;
    m_indices_count = indices_count;

    // save the drawing mode
    m_array_mode = GL_TRIANGLES;
}

/**
 * Sets this geometry as active, and binds to the shader attributes
 */
void Geometry::set_active(GLint pos_attrib, GLint color_attrib) {

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);

    if (pos_attrib >= 0) {
        glVertexAttribPointer(pos_attrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, pos));
        glEnableVertexAttribArray(pos_attrib);
    }

    if (color_attrib) {
        glVertexAttribPointer(color_attrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, rgba));
        glEnableVertexAttribArray(color_attrib);
    }
}
