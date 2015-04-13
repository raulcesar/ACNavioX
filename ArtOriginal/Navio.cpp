//Source code dump of Box2D scene: Navio.rube
//
//  Created by R.U.B.E 1.7.2
//  Using Box2D version 2.3.0
//  Mon April 13 2015 09:22:30
//
//  This code is originally intended for use in the Box2D testbed,
//  but you can easily use it in other applications by providing
//  a b2World for use as the 'm_world' variable in the code below.

b2Vec2 g(0.000000000000000e+00f, -1.000000000000000e+01f);
m_world->SetGravity(g);
b2Body** bodies = (b2Body**)b2Alloc(1 * sizeof(b2Body*));
b2Joint** joints = (b2Joint**)b2Alloc(0 * sizeof(b2Joint*));
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
  bd.angle = 0.000000000000000e+00f;
  bd.linearVelocity.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
  bd.angularVelocity = 0.000000000000000e+00f;
  bd.linearDamping = 0.000000000000000e+00f;
  bd.angularDamping = 0.000000000000000e+00f;
  bd.allowSleep = bool(4);
  bd.awake = bool(2);
  bd.fixedRotation = bool(0);
  bd.bullet = bool(0);
  bd.active = bool(32);
  bd.gravityScale = 1.000000000000000e+00f;
  bodies[0] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.748569965362549e+00f, -3.445850014686584e-01f);
    vs[1].Set(2.673569917678833e+00f, 7.743020057678223e-01f);
    vs[2].Set(2.207370042800903e+00f, 7.986260056495667e-01f);
    vs[3].Set(1.765490055084229e+00f, 7.905179858207703e-01f);
    vs[4].Set(-2.724250078201294e+00f, 6.040369868278503e-01f);
    vs[5].Set(1.563736677169800e+00f, -1.481109738349915e+00f);
    vs[6].Set(2.455551385879517e+00f, -1.279355287551880e+00f);
    shape.Set(vs, 7);

    fd.shape = &shape;

    bodies[0]->CreateFixture(&fd);
  }
  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(1.563736677169800e+00f, -1.481109738349915e+00f);
    vs[1].Set(-2.724250078201294e+00f, 6.040369868278503e-01f);
    vs[2].Set(-2.416150093078613e+00f, -9.324059635400772e-02f);
    vs[3].Set(-1.717536687850952e+00f, -6.653277873992920e-01f);
    vs[4].Set(-9.160659909248352e-01f, -1.143429994583130e+00f);
    vs[5].Set(-2.597055435180664e-01f, -1.364122867584229e+00f);
    vs[6].Set(4.378249943256378e-01f, -1.485769987106323e+00f);
    shape.Set(vs, 7);

    fd.shape = &shape;

    bodies[0]->CreateFixture(&fd);
  }
}
b2Free(joints);
b2Free(bodies);
joints = NULL;
bodies = NULL;

