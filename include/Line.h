#pragma once

#include "Object.h"

/*
struct ObjectInfo{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoord;
    std::vector<glm::vec3> normal;
    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> textureIndices;
    std::vector<unsigned int> normalIndices;
    size_t vertexSize;
    size_t textureSize;
    size_t normalSize;
    size_t vertIndicesSize;
    size_t texIndicesSize;
    size_t normIndicesSize;
};
*/

struct Line {
    Line(float _start = 0, float _end = 0, float _n = 0);
    Line(std::vector< std::pair<int, double> > data);
    void setLine(float _start, float _end, float _n);
    float start, end, n;
    struct ObjectInfo info;
    void setUp();
    void setUpData(std::vector< std::pair<int, double> > &data);
    void draw() const;
    GLuint vao, vbo, ebo;
};