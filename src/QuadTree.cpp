#include"QuadTree.h"

//int  QuadTree::NumberOfNodes = 0;
//std::vector < Node* > NodeList;


Node::~Node()
{
}
Node::Node(Vec2 pos, Vec2 size)
    : Position(pos),
      Size(size),
      Capacity(5),
      IsLeaf(true),
      Facing(NE)
{
    SubNodes[NW] =
    SubNodes[NE] =
    SubNodes[SW] =
    SubNodes[SE] = nullptr;
    Entities.reserve(40);
}


void  Node::Subdivide()
{
    for_loop(Index, 4)
    {
        SubNodes[Index] = new  Node( NewPos(Position, (Direction)Index), Vec2( Size.x * 0.5f, 
                                                                               Size.y * 0.5f));
        SubNodes[Index]->Facing = (Direction)Index;
    }
}

bool  Node::Insert(Collider *object)
{
    if(IsContained(object))               // If the Object Fits in this Square
    {
        if(IsLeaf == true)                // And its a Leaf Node
        {
            if(Entities.size() < Capacity)     // And the Capacity of the Square is not full 
            {
                Entities.push_back(object);   // Than add this Object to the Current Object list and exit the function
                return true;
            }
            else                       // Else If its full than make the Node a Branch
            {
                IsLeaf = false;  
                Subdivide();           // And Subdivide it

                for(Collider *object: Entities)  // Put the Particles that were in this Node in their respective SubNodes
                {
                   PushDown(object);
                }
            
                Entities.clear();             // And Delete the particles from this Now branch node
                if(SubNodes[NE]->Insert(object) == true) return true; // Attempt to place the Particle in one of the newly
                if(SubNodes[SE]->Insert(object) == true) return true; // Created Subnodes
                if(SubNodes[NW]->Insert(object) == true) return true; 
                if(SubNodes[SW]->Insert(object) == true) return true;
                
            }
        }
        else                        // If this node is a Branch and not a leaf than try the Subnodes and see if any of them are leaves
        {
            if(SubNodes[NE]->Insert(object) == true) return true;
            if(SubNodes[SE]->Insert(object) == true) return true;
            if(SubNodes[NW]->Insert(object) == true) return true;
            if(SubNodes[SW]->Insert(object) == true) return true;
        }
    }
    else   // Finally if the Particle is not in this quadrent at all just return false
    {      // This is done for completeness as it would fall through to a false return anyway by default
        return false;
    }
  return false;
}


bool  Node::IsContained(Collider *object){
    return( object->Body.Position.x >= (Position.x - Size.x) && object->Body.Position.x <= (Position.x + Size.x) &&
            object->Body.Position.z >= (Position.y - Size.y) && object->Body.Position.z <= (Position.y + Size.y));
}


bool  Node::PushDown(Collider *object)
{
    if(SubNodes[NE]->Insert(object) == true) return true;
    if(SubNodes[SE]->Insert(object) == true) return true;
    if(SubNodes[NW]->Insert(object) == true) return true;
    if(SubNodes[SW]->Insert(object) == true) return true;
  return false;
}


void  Node::Moveup(Collider *Object)
{
// Needs work and possibly is not needed at all
}


void  Node::Prune (Node *node)
{
    if( node != nullptr )
    {
        for_loop( i, 4 )
        {
            if(node->IsLeaf == false)
            {
                Prune(node->SubNodes[i]);
            }
            delete node->SubNodes[i];
            *node->SubNodes = nullptr;
        }

           
        node->IsLeaf =true;
        //node->Entities.empty();
    }

}



void  Node::Render(){
    float X1 = (Position.x - (Size.x ));
    float Y1 = (Position.y - (Size.y ));
    float X2 = (Position.x + (Size.x ));
    float Y2 = (Position.y + (Size.y ));

   // SCREEN->BOX(X1,Y1,X2,Y2);
    glBegin( GL_LINES);
        glVertex3f( X1, -1, Y1); 
        glVertex3f( X1, -1, Y2); 

        glVertex3f( X1, -1, Y2);
        glVertex3f( X2, -1, Y2);
      
        glVertex3f( X2, -1, Y2);
        glVertex3f( X2, -1, Y1);
      
        glVertex3f( X2, -1, Y1);
        glVertex3f( X1, -1, Y1);
    glEnd();

    if(IsLeaf == false)
    {
        for_loop(Index,4)
        {
            SubNodes[Index]->Render();
        }
    }
}




Vec2  Node::NewPos(Vec2 pos, Direction direction){
    Vec2 NewPos = pos;
    if(direction == NE)
    {
        NewPos.x += (Size.x * .5);
        NewPos.y -= (Size.y * .5);
    }                     
    if(direction == SE)   
    {                     
        NewPos.x += (Size.x * .5);
        NewPos.y += (Size.y * .5);
    }                      
    if(direction == NW)   
    {                     
        NewPos.x -= (Size.x * .5);
        NewPos.y -= (Size.y * .5);
    }                     
    if(direction == SW)   
    {                     
        NewPos.x -= (Size.x * .5);
        NewPos.y += (Size.y * .5);
    }
    return NewPos;
}



QT::QT(Vec2 position, Vec2 size)
  : Position(position),
    Size(size)
{
}


void QT::Init()
{
    RootNode = new Node(Position,Size);
   for_loop(Index , Collider::NumberOfObjects)
   {
       RootNode->Insert(Collider::CollisionList[Index]);
   }
}
 
void QT::Update()
{
    RootNode->Prune(RootNode);
    
    for_loop(Index , Collider::NumberOfObjects)
    {
        RootNode->Insert(Collider::CollisionList[Index]);
    }
    
    RootNode->Render();
}


bool  Node::Intersects(Vec2 position, Vec2 size)
{
   return !(position.x - size.x > Position.x + Size.x ||
            position.x + size.x < Position.x - Size.x ||
            position.y - size.y > Position.y + Size.y ||
            position.y + size.y < Position.y - Size.y);
            
}


std::vector<Collider*> Node::QueryRange(Vec2 position, Vec2 size)
{

std::vector<Collider *> results;

    if (!(Intersects(position,size)))
    {
        return results; 
    }
    for_loop (Index, Entities.size())
    {
        if (IsContained(Entities[Index]))
        {
             results.push_back(Entities[Index]);
        }
    }

    if (IsLeaf == true)
    {
        return results;
    }
    
    for_loop(SubIndex, 4)
    {
       std::vector<Collider*> S; 
       S = SubNodes[SubIndex]->QueryRange(position,size);
       if (S.size() > 0) 
       {
          results.insert(results.end(), S.begin(), S.end());
       }
    }

  // SCREEN->SET_DRAW_COLOR(RGB(0,255,0));
  // SCREEN->BOX(position.x - size.x, position.y - size.y,
  //             position.x + size.x, position.y + size.y);
  //
return results;
}
