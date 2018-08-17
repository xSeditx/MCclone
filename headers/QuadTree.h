#pragma once
#include"Collision.h"
#include"Window.h"

enum Direction
{
    NE = 0,
    SE = 1,
    NW = 2,
    SW = 3,
};

class Collider;

class Node
{
public:
        Node(){}
       ~Node();
        Node(Vec2 Position, Vec2 size);
       
        Vec2 Position;
        Vec2 Size;
       
        Node *SubNodes[4];
       
        int Capacity;
        bool IsLeaf;
        Direction Facing;
       
        std::vector<Collider *> Entities;
       
        void Subdivide();
        void Render();
        Vec2 NewPos(Vec2 pos, Direction dir);
       
        bool PushDown   (Collider *Object);
        void Moveup     (Collider *Object);
       
        bool Insert     (Collider *object);
        bool IsContained(Collider *object);
        void Prune(Node *node);

        bool Node::Intersects(Vec2 position, Vec2 size);

std::vector<Collider*> Node::QueryRange(Vec2 position, Vec2 size);
};


class QT{
public:
        QT(){}
       ~QT(){}
        QT(Vec2 Position, Vec2 size);
        Vec2 Position;
        Vec2 Size;
        Node *RootNode;
        void Init();
        void Update();
};