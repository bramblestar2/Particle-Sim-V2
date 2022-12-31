#include "Particle.h"
#include <iostream>

Particle::Particle(const Vec2i _Position, const float _Size)
{
    size = _Size;
    type = ParticleType::AIR;
    weight = 0;
    lifetime = 0;
    color = Vec4f(0,0,0,0);
    movable = true;
    destructable = true;
    pos = _Position;
}

Particle::Data Particle::getData()
{
    Data data;
    data.type = type;
    data.movement = movement;
    data.color = color;
    data.position = pos;
    data.weight = weight;
    data.lifetime = lifetime;
    data.movable = movable;
    data.destructable = destructable;
    data.expired = expired();

    return data;
}

void Particle::setPosition(const Vec2i _Position)
{
    pos = _Position;
}

void Particle::addLifetime(const int _Amount)
{
    lifetime += _Amount;
}

bool Particle::expired() const
{
    return lifetime <= 0;
}

void Particle::render()
{
    GLfloat square[]
    {
        //Position                       //Color
        pos.x * size       , pos.y * size       ,      color.x, color.y, color.z, color.w,                //Top left
        pos.x * size + size, pos.y * size       ,      color.x, color.y, color.z, color.w,                //Top right
        pos.x * size + size, pos.y * size + size,      color.x, color.y, color.z, color.w,                //Bottom right
        pos.x * size       , pos.y * size + size,      color.x, color.y, color.z, color.w,                //Bottom left
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, 6 * sizeof(GLfloat), square);
    glColorPointer(4, GL_FLOAT, 6 * sizeof(GLfloat), square + 2);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glDrawArrays(GL_QUADS, 0, 4);
}

bool Particle::operator>(const Particle& _Right)
{
    return this->weight > _Right.weight;
}

bool Particle::operator<(const Particle& _Right)
{
    return this->weight < _Right.weight;
}
