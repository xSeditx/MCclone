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
        
        struct volume
        {
            inline float ofBox(Vec3 min, Vec3 max){return (max.x - min.x) * (max.y - min.y) * (max.z - min.z);}
            //inline float ofBox(AABB &box){return (box.MaxPoint.x - box.MinPoint.x) * (box.MaxPoint.y - box.MinPoint.y) * (box.MaxPoint.z - box.MinPoint.x);}
            inline float ofSphere(float radius){ return (4/3)*(M_PI * (radius*radius*radius));}
        }Volume;


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

        int ID;       

        Vec3 Position;

        Mesh *Object; 
        
        Mass Body;
        
        ColliderType Type;

        virtual bool IsCollision(const Collider        *other) const;
        virtual bool IsCollision(const AABB            *other) const;
        virtual bool IsCollision(const CollisionSphere *other) const;
        
        virtual void Update();
        virtual void Render();

// Static Methods and Variables
        static std::vector<Collider*> CollisionList;
        static int NumberOfObjects;
};

class CollisionSphere: public Collider 
{
public:
        CollisionSphere(Mesh  *object, float radius);
        CollisionSphere(Vec3 Position, float radius);

        float Radius;

        bool IsCollision(const CollisionSphere *other) const override;
        bool IsCollision(const AABB            *other) const override;
        bool IsCollision(const Collider        *other) const override;
        
        
        bool PointInsideSphere(Vec3 point);
        

        void Update();
        void Render();
        void TestAllCollisions();
};

class AABB: public Collider
{
public:
        AABB(){Type = ColliderAABB;}
        AABB::AABB(Vec3 min, Vec3 max);
        
        Vec3 MinPoint, 
             MaxPoint;
        
        float x1,x2,
              y1,y2,
              z1,z2;
        
        bool IsCollision(const AABB            *other) const override;     
        bool IsCollision(const CollisionSphere *other) const override;
        bool IsCollision(const Collider        *other) const override;


        bool PointInsideAABB(Vec3 point);
        bool Intersect(AABB a, AABB b);


        void Update();
        void Render();
        void TestAllCollisions();
};


//#include"Camera.h"
//extern CollisionSphere* MousePicker(Camera cam, int *dist);
//