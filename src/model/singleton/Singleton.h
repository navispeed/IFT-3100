//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_SINGLETON_H
#define IFT_3100_SINGLETON_H

template<class T>
class Singleton {
private:
    static T* instance;
public:
    static T* getInstance();
};


#endif //IFT_3100_SINGLETON_H
