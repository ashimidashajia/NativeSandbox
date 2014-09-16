/**
 * Copyright (c) 2014 Xavier Gouchet
 *
 * This file is licensed under The MIT License (MIT).
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <GLES2/gl2.h>

// defines a Vertex structure 
struct Vertex {
    GLfloat pos[2];
    GLubyte rgba[4];
};

// a simple square 
const Vertex QUAD[4] = {
        {{-0.7f, -0.7f}, {0x00, 0xFF, 0x00}},
        {{ 0.7f, -0.7f}, {0x00, 0x00, 0xFF}},
        {{-0.7f,  0.7f}, {0xFF, 0x00, 0x00}},
        {{ 0.7f,  0.7f}, {0xFF, 0xFF, 0xFF}},
};


/**
 * The Geometry class holds a vertex buffer 
 */
class Geometry {

public:

    /** Constructor */
    Geometry();

    /** Destructor */
    ~Geometry();

    /**
     * Initializes the geometry with the given Vertices array. The vertices are drawn with a simple 
     * mode (can be GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES, 
     * GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN).
     */
    bool init(Vertex *vertices, int vertices_count, GLenum mode);

    /**
     * Initializes the geometry with the given vertices and indices arrays. 
     * The vertices are drawn as triangles, based on the given indices. 
     */
    bool init(Vertex *vertices, int vertices_count, GLubyte *indices, int indices_count);

    /**
     * Sets this geometry as active, and binds to the shader attributes
     */
    void set_active(GLint pos_attrib, GLint color_attrib);


    /**
     * 
     */
    void draw_geometry();

private:

    /** the vertex buffer */
    GLuint m_vertex_buffer;
    int m_vertices_count;

    /** the index buffer */
    GLubyte *m_indices;
    int m_indices_count;

    /** the basic array mode */
    GLenum m_array_mode;

};

#endif
