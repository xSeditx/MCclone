#include "Collision.h"
#include "Camera.h"

/*~~~~~~~~~~~~~~~~~~ NOTES ~~~~~~~~~~~~~~~~~~~~*/ 

//  Young's modulus E = Stress / Strain
//                  k = E * (Area / Length)
// angle_deg = RADIANS(acos(Vec3::DotProduct(VectorA.Normalize(), VectorB.Normalize() ))
// Force =  Axis Displacement   * Spring Factor - Damping Factor
 

//std::vector<CollisionSphere*> Collider;
//unsigned int CollisionSphere::Collision_ObjectCount = 0;



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
}






bool Collider::IsCollision(Collider *other) const
{
    return false;
}
bool Collider::IsCollision(AABB *other) const
{
    return false;
}
bool Collider::IsCollision(CollisionSphere *other) const
{
    return false;
}
void Collider::Update()
{
}





CollisionSphere::CollisionSphere(Mesh *parent, float radius)
    : 
      Radius(radius), 
      ID(NumberOfObjects++),
      Body(radius, parent->Position)
{
     CollisionList.push_back((Collider*)this);    //Collision_ObjectList.push_back(this); // This below might work, idk, Casting it to its base class 
}

bool CollisionSphere::IsCollision(CollisionSphere *other) const  // Use to return a float, might go back to doing that
{ 
    if(other->ID != this->ID)
    {
    float dist = GetDistance(Body.Position, other->Body.Position); 

        if(dist  < (Radius + other->Radius))
        {
            return true; //return dist; // Consider going back to returning Dist so that it returns useful information about the collision;
        }
    }
    return false;
}
bool CollisionSphere::IsCollision(AABB *other)  
{ 
    if(other->ID != this->ID)
    {
        if(float CollisionTestResults = true) // Condition is just a placeholder for the Test that checks if a Collision takes place
        {
            return true; 
        }
    }
  return false;
}
bool CollisionSphere::IsCollision(Collider *other)  
{ 
    if(other->ID != this->ID)
    {
        if(float CollisionTestResults = true) // Condition is just a placeholder for the Test that checks if a Collision takes place
        {
            return true; 
        }
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

//CollisionSphere::CollisionSphere(const CollisionSphere &other)
//{
//     std::memcpy(this, &other, sizeof(other));
//}
//


void  CollisionSphere::DetectionCollision() // Just temp function its goal is to run through all possible Collisions in the system by testing the QuadTree and all Collider objects will test again the given object
 {  
     //for(CollisionSphere *List: CollisionLIST) //this->QuadTreeIndex->Entities)

     std::vector<Collider*> results;

   //****  Fix this to work with a 3D position and Fix the QuadTree to handle Collider Objects ******
     //results = Tree->RootNode->QueryRange(Vec2(Body.Position.x, Body.Position.z),Vec2(10,10));

     for(Collider *List: results)
     {

         if(List != this)
         {
            // float CollisionDist = IsCollision(List); // Returns False if Same Object or No Collision
             if( IsCollision(List))
             {
                 // React to that Collision in some way by writing a Physics Module. 
             }
         }
     }
}
void  CollisionSphere::Update()
{
    Body.Velocity = Body.Velocity * .95f ;         

    Vec3  Last_Acceleration = Body.Acceleration;
          Body.Position += Body.Velocity *  Mass::Get_Timestep() + ( Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()) );
          Body.Acceleration = Body.Force / Body.Kg;

    Body.Force = Vec3(0.0f);

    Vec3  Avg_Acceleration = ( Last_Acceleration + Body.Acceleration ) / 2.0f;
          Body.Velocity += Avg_Acceleration * Mass::Get_Timestep();
   
    DetectionCollision();  // Horrible naming just Temp until I have everything in place. 
}



AABB::AABB()
{
}

bool AABB::IsCollision(Collider *other)  
{ 
    if(other->ID != this->ID)
    {
        if(float CollisionTestResults = true) // Condition is just a placeholder for the Test that checks if a Collision takes place
        {
            return true; 
        }
    }
  return false;
}
bool AABB::IsCollision(AABB *other)  
{ 
    if(other->ID != this->ID)
    {
        if(float CollisionTestResults = true) // Condition is just a placeholder for the Test that checks if a Collision takes place
        {
            return true; 
        }
    }
  return false;
}
bool AABB::IsCollision(CollisionSphere *other)  
{ 
    if(other->ID != this->ID)
    {
        if(float CollisionTestResults = true) // Condition is just a placeholder for the Test that checks if a Collision takes place
        {
            return true; 
        }
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
    // Perform Physics Calculations and than do a broadphase collisionSweep of all other Colliders in the System
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