#include "Collision.h"
#include "Camera.h"

/*~~~~~~~~~~~~~~~~~~ NOTES ~~~~~~~~~~~~~~~~~~~~*/ 

//  Young's modulus E = Stress / Strain
//                  k = E * (Area / Length)
// angle_deg = RADIANS(acos(Vec3::DotProduct(VectorA.Normalize(), VectorB.Normalize() ))
// Force =  Axis Displacement   * Spring Factor - Damping Factor
 
 
std::vector<Collider*> Collider::CollisionList;
int Collider::NumberOfObjects = 0;


// Set the default for the Static variables
float Mass::Current_Timestep = 2.0f;
float Mass::Gravity = 0.1f; 


extern QT *Tree;


Mass::Mass(float weight, Vec3 pos)
    : Force(0,0,0),
      Acceleration(0,0,0),
      Velocity(0,0,0),
      Kg(weight)
{
    Position = pos;
}



//=========================================================================================================================
//__________________________________    Collider Base Class   _____________________________________________________________
//-------------------------------------------------------------------------------------------------------------------------


bool Collider::IsCollision(const Collider *other) const
{
    return false;
}
bool Collider::IsCollision(const AABB *other) const
{
    return false;
}
bool Collider::IsCollision(const CollisionSphere *other) const
{
    return false;
}
void Collider::Update()
{
    Print("Wrong One");
}
void Collider::Render()
{
}



//=========================================================================================================================
//___________________________    BoundingSphere Collision Detector    _____________________________________________________
//-------------------------------------------------------------------------------------------------------------------------
CollisionSphere::CollisionSphere(Vec3 position, float radius)
    : 
      Radius(radius)

{
     Object = nullptr;

     Position = position;

     Body = Mass(radius, position);

     ID = NumberOfObjects++;

     Type = ColliderCOLLISIONSPHERE;

     CollisionList.push_back(this);  
}
CollisionSphere::CollisionSphere(Mesh *parent, float radius)
    : 
      Radius(radius) 
{
    ID = NumberOfObjects++;
    Object = parent;
    Position = parent->Position;
    Body = Mass(radius, parent->Position);
    Type = ColliderCOLLISIONSPHERE;
    CollisionList.push_back(this);  
}

//CollisionSphere::CollisionSphere(const CollisionSphere &other)
//{
//     std::memcpy(this, &other, sizeof(other));
//}
//

bool CollisionSphere::IsCollision(const CollisionSphere *other) const  // Use to return a float, might go back to doing that
{ 
    if(other->ID != this->ID)
    {
        return  GetDistance(Body.Position, other->Body.Position) < (Radius + other->Radius); 
    }
    return false;
}
bool CollisionSphere::IsCollision(const AABB *other) const 
{ 
    if(other->ID != this->ID)
    {
        return GetDistance(Vec3(
                           Max(other->MinPoint.x, Min(Position.x, other->MaxPoint.x)),
                           Max(other->MinPoint.y, Min(Position.y, other->MaxPoint.y)),
                           Max(other->MinPoint.z, Min(Position.z, other->MaxPoint.z)) 
                           ),Position) < Radius;
    }
  return false;
}
bool CollisionSphere::IsCollision(const Collider *other)  const
{ 
    if(other->ID != this->ID)
    {
        return other->IsCollision(this);
    }
  return false;
}
bool CollisionSphere::PointInsideSphere(Vec3 point) 
{
    float Distance = sqrt((point.x - Position.x) * (point.x - Position.x) +
                          (point.y - Position.y) * (point.y - Position.y) +
                          (point.z - Position.z) * (point.z - Position.z));
    return Distance < Radius;
}

void CollisionSphere::Update()
{
    Body.Velocity = Body.Velocity * .95f ;         

    Vec3  Last_Acceleration = Body.Acceleration;
          Body.Position += Body.Velocity *  Mass::Get_Timestep() + ( Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()) );
          Body.Acceleration = Body.Force / Body.Kg;

    Body.Force = Vec3(0.0f);

    Vec3  Avg_Acceleration = ( Last_Acceleration + Body.Acceleration ) / 2.0f;
          Body.Velocity += Avg_Acceleration * Mass::Get_Timestep();
    if(Object)Object->Position = Body.Position;
    Position = Body.Position;
    Render();
    TestAllCollisions();  // Horrible naming just Temp until I have everything in place. 
}
void CollisionSphere::Render()
{
    glBegin(GL_LINES);
        glVertex3f(Position.x, Position.y, Position.z);
        glVertex3f(Position.x + Radius,
                   Position.y + Radius, 
                   Position.z + Radius);
    glEnd();
}

void CollisionSphere::TestAllCollisions() 
{  
     std::vector<Collider*> results; // Checks the area around the object in the Quadtree and returns andthing in the same Sector
     results = Tree->RootNode->QueryRange(Vec2(Body.Position.x, Body.Position.z),Vec2(10,10));

     for(Collider *List: results)
     {
         if(List != this) // This is quite possible my Object->ID check, I think I am checking twice on accident.
         {
             if( IsCollision(List))
             {
                 Print("Sphere Collision:");// React to that Collision in some way by writing a Physics Module. 
             }
         }
     }
}


//=========================================================================================================================
//___________________________      AABB Collision Detector    _____________________________________________________________
//-------------------------------------------------------------------------------------------------------------------------

AABB::AABB(Vec3 min, Vec3 max)
{
    Position = (min + max) * 0.5f;

    Body = Mass(10, Position);

    ID = NumberOfObjects++;

    MaxPoint = max; 
    MinPoint = min;

    x1 = min.x; y1 = min.y; z1 = min.z;
    x2 = min.x; y2 = min.y; z2 = min.z;

    Type = ColliderAABB;

    CollisionList.push_back(this);
}

bool AABB::IsCollision(const Collider *other) const 
{ 
    if(other->ID != this->ID)
    {
        return other->IsCollision(this);
    }
  return false;
}
bool AABB::IsCollision(const AABB *other)  const
{ 
    if(other->ID != this->ID)
    {
        return (Min(x1, x2) <= Max(other->x1,other->x2) && Max( x1, x2) >= Min(other->x1, other->x2)) &&
               (Min(y1, y2) <= Max(other->y1,other->y2) && Max( y1, y2) >= Min(other->y1, other->y2)) &&
               (Min(z1, z2) <= Max(other->z1,other->z2) && Max( z1, z2) >= Min(other->z1, other->z2));                   //Intersect(*this, *other);
    }
  return false;
}
bool AABB::IsCollision(const CollisionSphere *other)  const
{ 
    if(other->ID != this->ID)
    {
        return other->IsCollision(this);
    }
  return false;
}
bool AABB::PointInsideAABB(Vec3 point)
{
  return (point.x >=  Min(x1,x2) && point.x <= Max(x1,x2)) &&
         (point.y >=  Min(y1,y2) && point.y <= Max(y1,y2)) &&
         (point.z >=  Min(z1,z2) && point.z <= Max(z1,z2));
}

bool AABB::Intersect(AABB a, AABB b) 
{
    return (
               (Min(a.x1,a.x2) <= Max(b.x1,b.x2) && Max(a.x1,a.x2) >= Min(b.x1, b.x2)) &&
               (Min(a.y1,a.y2) <= Max(b.y1,b.y2) && Max(a.y1,a.y2) >= Min(b.y1, b.y2)) &&
               (Min(a.z1,a.z2) <= Max(b.z1,b.z2) && Max(a.z1,a.z2) >= Min(b.z1, b.z2))
           );
}   

void AABB::Update()
{
    MaxPoint = Vec3(Max(x1,x2),Max(y1,y2),Max(z1,z2));
    MinPoint = Vec3(Min(x1,x2),Min(y1,y2),Min(z1,z2));
    Position = (MinPoint + MaxPoint) / 2.0f;
    // Perform Physics Calculations and than do a broadphase collisionSweep of all other Colliders in the System
    Body.Velocity = Body.Velocity * .95f ;         

    Vec3  Last_Acceleration = Body.Acceleration;
          Body.Position += Body.Velocity *  Mass::Get_Timestep() + ( Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()) );
          Body.Acceleration = Body.Force / Body.Kg;

    Body.Force = Vec3(0.0f);

    Vec3  Avg_Acceleration = ( Last_Acceleration + Body.Acceleration ) / 2.0f;
          Body.Velocity += Avg_Acceleration * Mass::Get_Timestep();

}
void AABB::Render()
{
    glBegin(GL_LINES);
        glVertex3f(MinPoint.x, MinPoint.y, MinPoint.z);
        glVertex3f(MaxPoint.x, MaxPoint.y, MaxPoint.z);
    glEnd();
}

void AABB::TestAllCollisions() // Just temp function its goal is to run through all possible Collisions in the system by testing the QuadTree and all Collider objects will test again the given object
 {  
    std::vector<Collider*> results;
    results = Tree->RootNode->QueryRange(Vec2(Body.Position.x, Body.Position.z),Vec2(10,10));
    
    for(Collider *List: results)
    {
        if(List != this)
        { 
            if( IsCollision(List))
            {
                Print("AABB Collision");// React to that Collision in some way by writing a Physics Module. 
            }
        }
    }
}






// ATTENTION: MOUSE PICKER NEEDS TO BE FIXED HERE TO WORK WITH MATRICES

//   CollisionSphere* MousePicker(Camera cam, int *distance)
//   {
//     Vec3  EndPosition, 
//           StartPosition = cam.Position;
//   
//           for_loop(dist, 200)
//           {
//               EndPosition = Vec3::RayCast(StartPosition, cam.Rotation, dist);
//               for_loop(i, CollisionSphere::Collision_ObjectCount)
//               {
//                       if(Collider[i]->Body.Position.x < EndPosition.x +  Collider[i]->Radius && Collider[i]->Body.Position.x > EndPosition.x - Collider[i]->Radius &&
//                          Collider[i]->Body.Position.y < EndPosition.y +  Collider[i]->Radius && Collider[i]->Body.Position.y > EndPosition.y - Collider[i]->Radius &&
//                          Collider[i]->Body.Position.z < EndPosition.z +  Collider[i]->Radius && Collider[i]->Body.Position.z > EndPosition.z - Collider[i]->Radius)
//                       {
//                          *distance = dist;
//                          return Collider[i];
//                       }
//                       
//               }
//   
//           }
//   return false;
//   }


//  Acceleration = Force / Mass;
//  Velocity += Acceleration;
//  Position += Velocity;
//  Force = 0.0;


//if(dist  < (Radius + other->Radius))
//{
//    return true; //return dist; // Consider going back to returning Dist so that it returns useful information about the collision;
//}