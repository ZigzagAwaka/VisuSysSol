#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Circle.hpp"


namespace glimac {

    void Circle::build(float radius, int nbP, float fatness) {
        float angle = 360.0 / float(nbP);
        int nbTriangles = nbP-2;

        std::vector<ShapeVertex> data;
        for(int i=0; i<nbP; i++) {
            ShapeVertex vertex;
            
            vertex.texCoords.x = float(i) * (1.0 / float(nbP));
            vertex.texCoords.y = 1.f - float(i) * (1.0 / float(nbP));

            vertex.normal.x = cos(glm::radians(angle*float(i)));
            vertex.normal.y = sin(glm::radians(angle*float(i)));;
            vertex.normal.z = 0.0;
            
            vertex.position = radius * vertex.normal;
            
            data.push_back(vertex);
        }

        for(int i=0; i<nbTriangles; i++) {
            m_Vertices.push_back(data[0]);
            m_Vertices.push_back(data[i+1]);
            m_Vertices.push_back(data[i+2]);
        }

        m_nVertexCount = m_Vertices.size();
    }

}
