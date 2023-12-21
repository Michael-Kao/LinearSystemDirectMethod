#include "Line.h"

Line::Line(float _start, float _end, float _n) 
    : start(_start), end(_end), n(_n) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    setUp();
}

Line::Line(std::vector< std::pair<int, double> > data) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    setUpData(data);
}

void Line::setUpData(std::vector< std::pair<int, double> > &data) {
    for(int i = 0; i < data.size(); ++i) {
        info.vertices.push_back( { data[i].first, data[i].second, 0 } );
    }
    for(int i = 0; i < info.vertices.size() - 1; ++i) {
        info.vertexIndices.push_back(i);
        info.vertexIndices.push_back(i + 1);
    }

    info.vertexSize = info.vertices.size() * sizeof(glm::vec3);
    info.vertIndicesSize = info.vertexIndices.size() * sizeof(unsigned int);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, info.vertexSize, info.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.vertIndicesSize, info.vertexIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
}

void Line::setUp() {
    float gap = 1.0 * (end - start) / n;
    for(int i = 0; i < n; ++i) {
        float offset = i * gap;
        info.vertices.push_back( { start + offset, 0, 0 } );
        info.vertices.push_back( { start + offset + gap, 0, 0 } );
    }
    for(int i = 0; i < info.vertices.size() - 1; ++i) {
        info.vertexIndices.push_back(i);
        info.vertexIndices.push_back(i + 1);
    }

    info.vertexSize = info.vertices.size() * sizeof(glm::vec3);
    info.vertIndicesSize = info.vertexIndices.size() * sizeof(unsigned int);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, info.vertexSize, info.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.vertIndicesSize, info.vertexIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
}

void Line::setLine(float _start, float _end, float _n) {
    start = _start;
    end = _end;
    n = _n;
    setUp();
}

void Line::draw() const {
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBindVertexArray(vao);
    glDrawElements(GL_POINTS, info.vertexIndices.size(), GL_UNSIGNED_INT, 0);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDrawElements(GL_LINES, info.vertexIndices.size(), GL_UNSIGNED_INT, 0);
}