//Source code dump of Box2D scene: Navio.rube
//
//  Created by R.U.B.E 1.7.2
//  Using Box2D version 2.3.0
//  Wed April 15 2015 20:29:43
//
//  This code is originally intended for use in the Box2D testbed,
//  but you can easily use it in other applications by providing
//  a b2World for use as the 'm_world' variable in the code below.

b2Vec2 g(0.000000000000000e+00f, -1.000000000000000e+01f);
m_world->SetGravity(g);
b2Body** bodies = (b2Body**)b2Alloc(4 * sizeof(b2Body*));
b2Joint** joints = (b2Joint**)b2Alloc(1 * sizeof(b2Joint*));
{
  b2BodyDef bd;
  bd.type = b2BodyType(0);
  bd.position.Set(4.383293151855469e+00f, 8.616516113281250e+00f);
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

}
{
  b2BodyDef bd;
  bd.type = b2BodyType(1);
  bd.position.Set(1.346669960021973e+01f, 2.637969970703125e+00f);
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
  bodies[1] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 2.000000000000000e+00f;
    fd.isSensor = bool(1);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(8.962917327880859e-01f, -8.962926864624023e-01f);
    vs[1].Set(8.962917327880859e-01f, 8.962922096252441e-01f);
    vs[2].Set(-8.962936401367188e-01f, 8.962922096252441e-01f);
    vs[3].Set(-8.962936401367188e-01f, -8.962926864624023e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[1]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(0);
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
  bodies[2] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 2.000000000000000e+00f;
    fd.isSensor = bool(1);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.437820053100586e+01f, -3.821042299270630e+00f);
    vs[1].Set(2.437820053100586e+01f, 3.821042299270630e+00f);
    vs[2].Set(-2.437820053100586e+01f, 3.821042299270630e+00f);
    vs[3].Set(-2.437820053100586e+01f, -3.821042299270630e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[2]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-1.029551506042480e+00f, 4.058958053588867e+00f);
  bd.angle = 7.462751865386963e-02f;
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
  bodies[3] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 3.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(-1.264570832252502e+00f, -7.456960678100586e-01f);
    vs[1].Set(-1.264570832252502e+00f, 2.543039321899414e-01f);
    vs[2].Set(-2.264570713043213e+00f, 2.543039321899414e-01f);
    vs[3].Set(-2.264570713043213e+00f, -7.456960678100586e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[3]->CreateFixture(&fd);
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
    vs[0].Set(2.724809885025024e+00f, 6.040369868278503e-01f);
    vs[1].Set(-1.765849947929382e+00f, 7.905179858207703e-01f);
    vs[2].Set(-4.379140138626099e-01f, -1.485769987106323e+00f);
    vs[3].Set(2.597590088844299e-01f, -1.364120006561279e+00f);
    vs[4].Set(9.162529706954956e-01f, -1.143429994583130e+00f);
    vs[5].Set(1.717890024185181e+00f, -6.653280258178711e-01f);
    vs[6].Set(2.416640043258667e+00f, -9.324049949645996e-02f);
    shape.Set(vs, 7);

    fd.shape = &shape;

    bodies[3]->CreateFixture(&fd);
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
    vs[0].Set(-4.379140138626099e-01f, -1.485769987106323e+00f);
    vs[1].Set(-1.765849947929382e+00f, 7.905179858207703e-01f);
    vs[2].Set(-2.207819938659668e+00f, 7.986260056495667e-01f);
    vs[3].Set(-2.674119949340820e+00f, 7.743020057678223e-01f);
    vs[4].Set(-2.749130010604858e+00f, -3.445850014686584e-01f);
    vs[5].Set(-2.456049919128418e+00f, -1.279360055923462e+00f);
    vs[6].Set(-1.564059972763062e+00f, -1.481109976768494e+00f);
    shape.Set(vs, 7);

    fd.shape = &shape;

    bodies[3]->CreateFixture(&fd);
  }
}
{
  b2DistanceJointDef jd;
  jd.bodyA = bodies[0];
  jd.bodyB = bodies[3];
  jd.collideConnected = bool(0);
  jd.localAnchorA.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
  jd.localAnchorB.Set(-7.431560158729553e-01f, 2.120650053024292e+00f);
  jd.length = 6.605120182037354e+00f;
  jd.frequencyHz = 0.000000000000000e+00f;
  jd.dampingRatio = 0.000000000000000e+00f;
  joints[0] = m_world->CreateJoint(&jd);
}
b2Free(joints);
b2Free(bodies);
joints = NULL;
bodies = NULL;

