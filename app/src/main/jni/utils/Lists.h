/**
 * Copyright (c) 2014 Xavier Gouchet
 * 
 * This file is licensed under The MIT License (MIT). 
 * For more information, check the "LICENSE" file available in the root directory of this project.
 */
 

#ifndef LISTS_H
#define LISTS_H

#include <list>

using namespace std;

class Component;
class BehavioralObject;

typedef list<Component *>                           ComponentsList;
typedef list<Component *>::iterator                 ComponentsListIterator;
typedef list<Component *>::const_iterator           ComponentsListConstIterator;

typedef list<BehavioralObject *>                    BehavioralObjectsList;
typedef list<BehavioralObject *>::iterator          BehavioralObjectsListIterator;
typedef list<BehavioralObject *>::const_iterator    BehavioralObjectsListConstIterator;


#endif
