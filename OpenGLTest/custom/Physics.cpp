#include "Physics.h"

    bool CheckCollision(std::shared_ptr <GameObject>& one, std::shared_ptr <GameObject>& two) // AABB - AABB collision
    {
        // collision x-axis?
        bool collisionX = one->GetX() + std::abs(one->GetXBorder()) *1 >= two->GetX() && // 50*2: one->GetXLength()
            two->GetX() + std::abs(two->GetXBorder())*1 >= one->GetX(); // 50*2: two->GetXLength()
        // collision y-axis?
        bool collisionY = one->GetY() + std::abs(one->GetYBorder()) >= two->GetY() && // 50: one->GetYLength()
            two->GetY() + std::abs(two->GetYBorder()) >= one->GetY(); // 50: two->GetYLength()
        // collision only if on both axes
        return collisionX && collisionY;
    }

    bool CheckIntersection(std::shared_ptr <GameObject>& one, std::shared_ptr <GameObject>& two) // AABB - AABB collision
    {
        // collision x-axis?
        bool collisionX1 = one->GetBottomLeft().x >= two->GetX() &&
            one->GetBottomLeft().y >= two->GetY();
        // collision y-axis?
        bool collisionY1 = one->GetBottomLeft().y <= two->GetY() + std::abs(two->GetXBorder()) &&
            one->GetBottomLeft().x <= two->GetX() + std::abs(two->GetXBorder());

        bool collisionX2 = one->GetBottomRight().x >= two->GetX() &&
            one->GetBottomRight().y >= two->GetY(); 
        // collision y-axis?
        bool collisionY2 = one->GetBottomRight().y <= two->GetY() + std::abs(two->GetXBorder()) &&
            one->GetBottomRight().x <= two->GetX() + std::abs(two->GetXBorder()); 

        bool collisionX3 = one->GetTopRight().x >= two->GetX() &&
            one->GetTopRight().y >= two->GetY();
        // collision y-axis?
        bool collisionY3 = one->GetTopRight().y <= two->GetY() + std::abs(two->GetXBorder()) &&
            one->GetTopRight().x <= two->GetX() + std::abs(two->GetXBorder());

        bool collisionX4 = one->GetTopLeft().x >= two->GetX() &&
            one->GetTopLeft().y >= two->GetY();
        // collision y-axis?
        bool collisionY4 = one->GetTopLeft().y <= two->GetY() + std::abs(two->GetXBorder()) &&
            one->GetTopLeft().x <= two->GetX() + std::abs(two->GetXBorder());

        return (collisionX1 && collisionY1) || (collisionX2 && collisionY2) || (collisionX3 && collisionY3) || (collisionX4 && collisionY4);
    }
    
    void Gravity(std::shared_ptr <GameObject>& Dashie, double velocity)
    {
        const double dt = 0.01;
        const double gravity = 428.8;
        Dashie->SetYVelocity(Dashie->GetYVelocity() - gravity * dt);
        Dashie->MoveUp(velocity * 0.01f);
    }