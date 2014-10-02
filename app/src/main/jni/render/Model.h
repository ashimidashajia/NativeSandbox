/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef MODEL_H
#define MODEL_H

#include <GLES2/gl2.h>
#include "../component/Transform.h"
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
     * Initializes the object
     */
    virtual void init() = 0;
    
    /**
     * Renders the object
     */
    virtual void render(Environment *env);
    
    /**
     * Called when this component is attached to an object. The parent object is accesible in the 
     * mObject field from now on. 
     */
    virtual void onAttached();
    
    
protected:

    /**
     * Initialises the shader.
     * Returns true if the initialization was succesfully.
     */
    bool initShader(const char *vsSource, const char *fsSource);
    
    
    /**
     * Initializes the geometry with the given vertex array.
     * Returns true if the initialization was succesfully.
     */
    bool initGeometry(GLfloat *vertices, int vtxCount, unsigned short vtxMask, GLubyte *indices, int idxCount, GLenum mode);

private:

    /** the Transform */
    Transform *mTransform;

    /** the geometry */
    Geometry *mGeometry;

    /** the shader */
    Shader *mShader;
};

#endif
