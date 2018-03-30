//
// Created by Grégoire GUEMAS on 18-03-22.
//
//#include    <gl/glew.h>                            // Header File For The GLu32 Library
#include "Portal.h"

Portal::Portal(const ofVec3f &start, const ofVec3f &end) : start(start), end(end) {
}

void Portal::draw() {
/*    Mesh s;
    *//* init_resources() *//*
    ofVec3f portal_vertices[] = {
            ofVec3f(-1, -1, 0),
            ofVec3f(1, -1, 0),
            ofVec3f(-1, 1, 0),
            ofVec3f(1, 1, 0),
    };
    for (unsigned int i = 0; i < sizeof(portal_vertices) / sizeof(portal_vertices[0]); i++) {
        portals[0].addVertex(portal_vertices[i]);
        portals[1].addVertex(portal_vertices[i]);
    }

    GLushort portal_elements[] = {
            0, 1, 2, 2, 1, 3,
    };
    for (unsigned int i = 0; i < sizeof(portal_elements) / sizeof(portal_elements[0]); i++) {
        portals[0].addIndex(portal_elements[i]);
        portals[1].addIndex(portal_elements[i]);
    }

    // 90° angle + slightly higher
    portals[0].object2world = glm::translate(glm::mat4(1), glm::vec3(0, 1, -2));
    portals[1].object2world = glm::rotate(glm::mat4(1), -90.0f, glm::vec3(0, 1, 0))
            * glm::translate(glm::mat4(1), glm::vec3(0, 1.2, -2));

    portals[0].upload();
    portals[1].upload();*/
}
