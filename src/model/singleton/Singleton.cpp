//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include "Singleton.h"

template<class T>
T *Singleton<T>::getInstance() {
    if (instance == nullptr) {
        instance = new T();
    }
    return instance;
}