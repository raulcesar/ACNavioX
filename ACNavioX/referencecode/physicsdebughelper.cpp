//Just to help me understand!!!

DrawNode* _drawNode;
void PhysicsWorld::debugDraw()
{
    if (_debugDraw == nullptr)
    {
        _debugDraw = new (std::nothrow) PhysicsDebugDraw(*this);
    }
    
    if (_debugDraw && !_bodies.empty())
    {
        if (_debugDraw->begin())
        {
            if (_debugDrawMask & DEBUGDRAW_SHAPE)
            {
                for (Ref* obj : _bodies)
                {
                    PhysicsBody* body = dynamic_cast<PhysicsBody*>(obj);
                    
                    if (!body->isEnabled())
                    {
                        continue;
                    }
                    
                    for (auto& shape : body->getShapes())
                    {
                        _debugDraw->drawShape(*dynamic_cast<PhysicsShape*>(shape));
                    }
                }
            }
            
            if (_debugDrawMask & DEBUGDRAW_JOINT)
            {
                for (auto joint : _joints)
                {
                    _debugDraw->drawJoint(*joint);
                }
            }
            
            _debugDraw->end();
        }
    }
}
bool PhysicsDebugDraw::begin()
{
    _drawNode->clear();
    return true;
}

void PhysicsDebugDraw::end()
{
}

// actuao drawing code:
float radius = PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(subShape));
Vec2 centre = PhysicsHelper::cpv2point(cpBodyGetPos(cpShapeGetBody(subShape)))
+ PhysicsHelper::cpv2point(cpCircleShapeGetOffset(subShape));

static const int CIRCLE_SEG_NUM = 12;
Vec2 seg[CIRCLE_SEG_NUM] = {};

for (int i = 0; i < CIRCLE_SEG_NUM; ++i)
{
    float angle = (float)i * M_PI / (float)CIRCLE_SEG_NUM * 2.0f;
    Vec2 d(radius * cosf(angle), radius * sinf(angle));
    seg[i] = centre + d;
}
_drawNode->drawPolygon(seg, CIRCLE_SEG_NUM, fillColor, 1, outlineColor);
break;
