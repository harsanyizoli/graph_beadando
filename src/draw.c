#include "draw.h"

#include <GL/glut.h>

#include <stdio.h>

void draw_triangles(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

	glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {

            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }    

    glEnd();
}

void draw_quads(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

	glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }    

    glEnd();
}

void draw_model(const struct Model* model)
{
    draw_triangles(model);
    draw_quads(model);
}

void draw_obj(const Object* obj){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(obj->scale, obj->scale, obj->scale);
    glRotatef(obj->rotatex, 1.0f, 0.0f, 0.0f);
    glRotatef(obj->rotatey, 0.0f, 1.0f, 0.0f);
    glRotatef(obj->rotatez, 0.0f, 0.0f, 1.0f);
    glTranslatef(obj->position.x, obj->position.y, obj->position.z);
    draw_triangles(obj->m);
    draw_quads(obj->m);
    glPopMatrix();
}
