#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Circle.hpp"


namespace glimac {

    void Circle::build(float radius, int nbP, float fatness) {
        float angle = 360.0 / float(nbP);
        int nbiTriangles = nbP-2; // number of triangles without the last two

        std::vector<ShapeVertex> data;
        for(int i=0; i<nbP; i++) { // create all vertex
            ShapeVertex vertex;
            
            vertex.texCoords.x = float(i) * (1.0 / float(nbP));
            vertex.texCoords.y = 1.f - float(i) * (1.0 / float(nbP));

            vertex.normal.x = cos(glm::radians(angle*float(i)));
            vertex.normal.y = 0.0;
            vertex.normal.z = sin(glm::radians(angle*float(i)));
            
            vertex.position = radius * vertex.normal;
            
            data.push_back(vertex);
        }

        for(int i=0; i<nbiTriangles; i++) { // create nbiTriangles triangles
            m_Vertices.push_back(data[i]);
            m_Vertices.push_back(data[i+1]);
            m_Vertices.push_back(data[i+2]);
        }
        m_Vertices.push_back(data[nbiTriangles]); // add the last two triangles
        m_Vertices.push_back(data[nbiTriangles+1]);
        m_Vertices.push_back(data[0]);
        m_Vertices.push_back(data[nbiTriangles+1]);
        m_Vertices.push_back(data[0]);
        m_Vertices.push_back(data[1]);

        m_nVertexCount = m_Vertices.size();
    }

}