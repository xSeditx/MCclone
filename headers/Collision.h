//                                                                                                                                           
//                                           OPENGL 2.0 Abstraction API
//                                                January 24 2018
//                                               -----------------                                                                           
//                                                                                                                                           
//                                        COLLISION AND SIMPLE PHYSICS LIB                                                                    
// 
//
// EFFICIENT DISTANCE COMPUTATION:  https://arxiv.org/ftp/arxiv/papers/1410/1410.4603.pdf
//==========================================================================================================================

#pragma once

#include<vector>
#include"Window.h"
#include"Core.h"
#include"QuadTree.h"

//class QT; class Node;


enum ColliderType
{
    ColliderUNKNOWN = 0,
    ColliderAABB,
    ColliderCOLLISIONSPHERE,
    ColliderPVP
};


class AABB;
class CollisionSphere;

class Mass
{

public:
        Mass(){}
        Mass(float weight, Vec3 pos);
        Mass(float weight,float x, float y, float z)
        {
            Mass(weight, Vec3(x,y,z));
        }
       ~Mass(){}
                
        
        Vec3   Velocity,
               Position, 
               Acceleration,
               Angular,
               Force;
        
        float  Kg;
        
        void Apply_Gravity  ();
        void Apply_Physics  ();
        void Set_Force      (float x, float y);
        void Set_Position   (float x, float y);
        
        Vec3 Get_Position();
        
        inline float Get_X(){return Position.x;}
        inline float Get_Y(){return Position.y;}
        inline float Get_Z(){return Position.z;}
        
        struct convert
        {
            inline float Pounds_to_Kg  (float lb) { return lb * .453; }
            inline float Newtons_to_Kg (float N)  { return N / 9.8;   }
            inline float Kg_to_Newtons (float Kg) { return Kg * 9.8;  }
        }Convert;
        
        static void  Set_Timestep(float time){Current_Timestep = time;}
        static void  Set_Gravity(float g){Gravity = g;}
        
        static float Get_Timestep(){return Current_Timestep;}
        static float Get_Gravity(){ return Gravity;}
private:
           
        static float Current_Timestep;
        static float Gravity; 
};


class Collider{
public:
        Collider(){}

        Vec3 Position;

        int ObjectID;
        Mesh *Object; // Mesh is similar in that its a collection of Spheres/Boxes/Models etc
        
        Mass Body;
        ColliderType Type;

        int ID;

    virtual bool IsCollision(Collider *other) const;
    virtual bool IsCollision(AABB *other) const;
    virtual bool IsCollision(CollisionSphere *other) const;
    
    virtual void Update();

// Static Methods and Variables

        static std::vector<Collider*> CollisionList;
        static int NumberOfObjects;
};

class CollisionSphere: public Collider 
{
public:
        CollisionSphere(Mesh *object, float radius);

        
        int ID;
        Mass Body;
        Vec3 Position;
        float Radius;
        
        
        void Update();
        
        bool IsCollision(CollisionSphere *other) const override;
        bool IsCollision(AABB *other);
        bool IsCollision(Collider *other);
        
        
        bool PointInsideSphere(Vec3 point);
        
        void DetectionCollision();
};

class AABB: public Collider
{
public:
    AABB();

    Vec3 Point1, Point2;

    float x1,x2,
          y1,y2,
          z1,z2;

    Mass Body;


    bool IsCollision(Collider *other);
    bool IsCollision(AABB *other);
    bool IsCollision(CollisionSphere *other);


    bool PointInsideAABB(Vec3 point);
    bool Intersect(AABB a, AABB b);
    void Update();
};









//class Collider
//{
//public:
//        Collider(){}
//        Collider(Vec3 pos, float radius, int parent);
//        Collider(const Collider &other);
//        
//        int ID;
//        int ParentID;
//        
//        Node *QuadTreeIndex;
//        
//        float  Radius;
//        
//        Mass Body;
//        
//        float  DeltaTime, 
//               PresentTime;
//        
////----------- Getters && Setters ------------------------
//// This might be tricky, I think this need be done on a per class basis instead of making it virtual
//
////       void SetPosition(Vec3 pos)
////       { 
////           Body.Position = pos;
////       }
////      
////       Vec3 GetPosition()
////       {
////           return Body.Position;
////       }
////       
////-------------------------------------------------------
//        
//        virtual float Is_Collision(int other);
//        virtual void  Update();
//
//        void   CollisionDetection();         
//
//// Static object list
//public:
//     static std::vector<Collider*> Collision_ObjectList;
//     static unsigned int  Collision_ObjectCount;
//
//};
//

//
//
//
//
//class CollisionSphere
//{
//public:
//        CollisionSphere(){}
//        CollisionSphere(Vec3 pos, float radius, int parent);
//        CollisionSphere(const CollisionSphere &other);
//        
//        int ID;
//        int ParentID;
//        
//        Node *QuadTreeIndex;
//        
//        float  Radius;
//        
//        Mass Body;
//        
//        float  DeltaTime, 
//               PresentTime;
//        
////----------- Getters && Setters ------------------------
//        void   SetPosition(Vec3 pos)   { Body.Position = pos;}
//        void   SetRadius(float radius) { Radius=radius; }
//        
//        Vec3   GetPosition(){return Body.Position;}
//        float  GetRadius(){return Radius;}
//        
////-------------------------------------------------------
//        
//        float  Is_Collision(int other);
//        void   CollisionDetection();
//        void   Update();
//         
//        struct convert
//        {
//            inline float Pounds_to_Kg  (float lb) { return lb * .453; }
//            inline float Newtons_to_Kg (float N)  { return N / 9.8;   }
//            inline float Kg_to_Newtons (float Kg) { return Kg * 9.8;  }
//        }Convert;
//
//// Static object list
//public:
//     static std::vector<CollisionSphere*> Collision_ObjectList;
//     static unsigned int  Collision_ObjectCount;
//
//};


//#include"Camera.h"
//extern CollisionSphere* MousePicker(Camera cam, int *dist);
//