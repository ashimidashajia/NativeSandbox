/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */

#include "Model.h"
#include "../utils/Logs.h"

#define TAG "Model"

/** Constructor */
Model::Model() {
    mShader = new Shader();
    mGeometry = new Geometry();

    // TODO mTransform = NULL; 
    // for test purposes, lets assume we set it here, though we should never do that ! 
    mTransform = new Transform();
    mTransform->setPosition(0, 0, 5);
    mTransform->getMatrix()->log();
}

/** Destructor */
Model::~Model() {
    if (mShader) {
        delete mShader;
    }

    if (mGeometry) {
        delete mGeometry;
    }
    
}


/**
 * Called when this component is attached to an object. The parent object is accesible in the 
 * mObject field from now on. 
 */
void Model::onAttached(){
    // TODO mTransform = transform from object 
}

/**
 * Initialises the shader.
 * Returns true if the initialization was succesfully.
 */
bool Model::initShader(const char *vsSource, const char *fsSource) {

    if (!mShader->init(vsSource, fsSource)) {
        LogW(TAG, "   • Error while compiling shader");
        delete mShader;
        mShader = NULL;
        return false;
    }

    return true;
}

/**
 * Initializes the geometry with the given Vertices array. 
 * Returns true if the initialization was succesfully. 
 */
bool Model::initGeometry(GLfloat *vertices, int vtxCount, unsigned short vtxMask, 
                            GLubyte *indices, int idxCount, GLenum mode) {
    
    if (!mGeometry->initVertices(vertices, vtxCount, vtxMask)) {
        delete mGeometry;
        mGeometry = NULL;
        return false;
    }

    mGeometry->initIndices(indices, idxCount, mode);
    return true;
}

/** 
 * Renders the object
 */
void Model::render(Environment *env) {

    // Check that we have a shader
    if (mShader == NULL) {
        LogW(TAG, "   • can't draw a model with a NULL shader");
        return; 
    }
    
    // Check that we have a geometry
    if (mGeometry == NULL) {
        LogW(TAG, "   • can't draw a model with a NULL geometry");
        return; 
    }
    
    
    // set the shader active
    LogV(TAG, "   • Set shader active");
    mShader->setActive();
    
    // set the environment 
    LogV(TAG, "   • Set environment");
    env->setUniformValues(mShader);
    
    // set uniform values 
    LogV(TAG, "   • Set uniform values");
    glUniformMatrix4fv(mShader->getModelMatrixUniformHandle(), 1, false, mTransform->getMatrixData());

    // draw the geometry
    LogV(TAG, "   • Draw geometry");
    mGeometry->drawGeometry(mShader);

}
