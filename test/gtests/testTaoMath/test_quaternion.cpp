#include <TaoMath/TaoMath>
#include <gtest/gtest.h>

using namespace TaoMath;

TEST(test_quaternion, test1)
{
    Quaternion q1;
    ASSERT_TRUE(q1.isNull());
    Quaternion q2(2.0, 1, 3, 4);
    ASSERT_EQ(2.0, q2.scalar());
    ASSERT_EQ(1.0, q2.x());
    ASSERT_EQ(3.0, q2.y());
    ASSERT_EQ(4.0, q2.z());
    ASSERT_EQ(Vector3D(1, 3, 4), q2.vector());
    q2.setVector(Vector3D(2, 3, 1));
    ASSERT_EQ(2.0, q2.x());
    ASSERT_EQ(3.0, q2.y());
    ASSERT_EQ(1.0, q2.z());
    q2.setScalar(21);
    ASSERT_EQ(21, q2.scalar());

    Quaternion q3(1.3, Vector3D(2, 3, 1));
    ASSERT_EQ(1.3f, q3.scalar());
    ASSERT_EQ(2.0, q3.x());
    ASSERT_EQ(3.0, q3.y());
    ASSERT_EQ(1.0, q3.z());

    Quaternion q4(Vector4D(2, 3, 1, 1.3));
    ASSERT_EQ(1.3f, q4.scalar());
    ASSERT_EQ(2.0, q4.x());
    ASSERT_EQ(3.0, q4.y());
    ASSERT_EQ(1.0, q4.z());

    q4.setVector(1, 2, 3);
    ASSERT_EQ(1.0, q4.x());
    ASSERT_EQ(2.0, q4.y());
    ASSERT_EQ(3.0, q4.z());
    auto v = q4.toVector4D();
    ASSERT_EQ(Vector4D(1, 2, 3, 1.3), v);

    Quaternion q5;
    q5.setToIdentity();
    ASSERT_TRUE(q5.isIdentity());

    Quaternion q6;
    q6.setX(4);
    q6.setY(5);
    q6.setZ(7.);
    ASSERT_EQ(4, q6.x());
    ASSERT_EQ(5, q6.y());
    ASSERT_EQ(7, q6.z());
}
TEST(test_quaternion, test2)
{
    Quaternion q(0.7, 1, 1, 1);
    real angle;
    Vector3D axis;
    q.getAxisAndAngle(axis, angle);
    ASSERT_EQ(angle, 91.1459961f);
    ASSERT_EQ(axis, Vector3D(0.535287738, 0.535287738, 0.535287738));
    auto v3 = q.toEulerAngles();
    ASSERT_EQ(v3, Vector3D(-9.89945698, 98.5307693f, 98.5307693f));
    real pitch, yaw, roll;
    q.getEulerAngles(pitch, yaw, roll);
    ASSERT_EQ(pitch, -9.89945698f);
    ASSERT_EQ(yaw, 98.5307693f);
    ASSERT_EQ(roll, 98.5307693f);

    {
        Quaternion q(0, 0, 0, 0);
        real x, y, z, angle;
        q.getAxisAndAngle(x, y, z, angle);
        ASSERT_EQ(x, 0);
        ASSERT_EQ(y, 0);
        ASSERT_EQ(z, 0);
        ASSERT_EQ(angle, 0);
    }
    {
        auto p = Quaternion::fromAxisAndAngle(Vector3D(1, 1, 1), 120);
        real x, y, z, angle;
        q.getAxisAndAngle(x, y, z, angle);
        ASSERT_TRUE(fuzzyCompare(x, 0.535287738f));
        ASSERT_TRUE(fuzzyCompare(y, 0.535287738f));
        ASSERT_TRUE(fuzzyCompare(z, 0.535287738f));
        ASSERT_TRUE(fuzzyCompare(angle, 91.1459961f));
    }
    {
        auto p = Quaternion::fromAxisAndAngle(Vector3D(1, 1, 1), 60);
        real x, y, z, angle;
        q.getAxisAndAngle(x, y, z, angle);
        ASSERT_TRUE (fuzzyCompare (x, 0.535287738f));
        ASSERT_TRUE (fuzzyCompare (y, 0.535287738f));
        ASSERT_TRUE (fuzzyCompare (z, 0.535287738f));
        ASSERT_TRUE (fuzzyCompare (angle, 91.1459961f));
    }
}
TEST(test_quaternion, test3)
{

    {
        Quaternion q(0.7, 1, 1, 1);
        ASSERT_EQ(1.86815416922694f, q.length());
        auto vq = q.normalized();
        q.normalize();
        ASSERT_EQ(q, vq);
    }
    {

        Quaternion q(0.7, 1, 1, 1);
        auto iq = q.inverted();
        ASSERT_TRUE(fuzzyCompare(Quaternion(0.7 / q.lengthSquared(),
                                     1 / q.lengthSquared(),
                                     1 / q.lengthSquared(),
                                     1 / q.lengthSquared()),
            iq));
    }
    {
        Quaternion q(0.7, 1, 1, 1);
        auto cq = q.conjugated();
        ASSERT_EQ(cq, Quaternion(0.7, -1, -1, -1));
    }

    {
        Quaternion q(0.7, 1, 1, 1);
        auto rv = q.rotatedVector(Vector3D(1, 1, 1));
        ASSERT_EQ(rv, Vector3D(-1, -1, -1));
    }
    {

        auto fq = Quaternion::fromAxisAndAngle(1, 1, 1, 30);
        ASSERT_EQ(fq, Quaternion(0.965925872, 0.149429262, 0.149429262, 0.149429262));
    }
    {
        Vector3D axis(1, 1, 1);
        real angle = 30;
        auto fq = Quaternion::fromAxisAndAngle(axis, angle);

        ASSERT_EQ(fq, Quaternion(0.965925872, 0.149429262, 0.149429262, 0.149429262));
    }
    {
        auto q = Quaternion::fromEulerAngles(10, 10, 10);
        ASSERT_EQ(q, Quaternion(0.989289582, 0.0940609127, 0.0789264739, 0.0789264739));
    }
    {
        auto q = Quaternion::fromEulerAngles(Vector3D(10, 10, 10));
        ASSERT_EQ(q, Quaternion(0.989289582, 0.0940609127, 0.0789264739, 0.0789264739));
    }
    {
        Quaternion q(0.7, 1, 1, 1);
        Vector3D v1, v2, v3;
        q.getAxes(v1, v2, v3);
        ASSERT_EQ(Vector3D(-3, 3.4, 0.6), v1);
        ASSERT_EQ(Vector3D(0.6, -3.0, 3.4), v2);
        ASSERT_EQ(Vector3D(3.4, 0.6, -3.0), v3);

        auto p = Quaternion::fromAxes(v1, v2, v3);
        ASSERT_TRUE(fuzzyCompare(p, q));
    }
    {
        auto q = Quaternion::fromDirection(Vector3D(1, 1, 1), Vector3D(0, 1, 0));
        ASSERT_EQ(q, Quaternion(0.880476236, -0.279848158, 0.364705175, 0.115916893));
    }
    {
        auto q = Quaternion::rotationTo(Vector3D(1, 1, 1), Vector3D(1, 3, 2));
        ASSERT_EQ(q, Quaternion(0.981279790, -0.0786235183, -0.0786235183, 0.157247037));
    }
    {
        auto q = Quaternion::slerp(Quaternion(1, 1, 1, 1), Quaternion(1, 0.1, 0.1, 0.1), 0.5);
        ASSERT_EQ(q, Quaternion(1, 0.55, 0.55, 0.55));
    }
    {
        auto q = Quaternion::nlerp(Quaternion(1, 1, 1, 1), Quaternion(1, 0.1, 0.1, 0.1), 0.5);
        ASSERT_EQ(q, Quaternion(0.724048615, 0.398226768, 0.398226768, 0.398226768));
    }
    {
        Quaternion p1(1, 1, 1, 1);
        Quaternion p2(1, 1, 1, 1);
        real v = Quaternion::dotProduct(p1, p2);
        ASSERT_EQ(4, v);

        p1 += p2;
        ASSERT_EQ(p1, Quaternion(2, 2, 2, 2));
        p1 -= p2;
        ASSERT_EQ(p1, p2);

        p1 *= p2;
        ASSERT_EQ(p1, Quaternion(1, 1, 1, 1));

        p1 *= 2;
        ASSERT_EQ(p1, Quaternion(2, 2, 2, 2));
        p1 /= 2;
        ASSERT_EQ(p1, Quaternion(1, 1, 1, 1));
        p1 /= 0.5;
        ASSERT_EQ(p1, Quaternion(2, 2, 2, 2));

        ASSERT_TRUE(p1 != p2);
        ASSERT_FALSE(p1 == p2);
        ASSERT_FALSE(fuzzyCompare(p1, p2));
    }
    {
        Quaternion p1(1, 1, 1, 1);
        Quaternion p2(1, 1, 1, 1);

        auto p = p1 + p2;
        ASSERT_EQ(Quaternion(2, 2, 2, 2), p);

        auto p3 = p - p1;
        ASSERT_EQ(p3, p2);

        auto p4 = p1 * p2;
        ASSERT_EQ(p4, p1);
        auto p5 = -p1;
        ASSERT_EQ(p5, Quaternion(-1, -1, -1, -1));

        auto p6 = p1 * 2;
        ASSERT_EQ(p6, Quaternion(2, 2, 2, 2));
        auto p7 = p1 * 2.0;
        ASSERT_EQ(p7, Quaternion(2, 2, 2, 2));

        auto p8 = p6 / 2;
        ASSERT_EQ(p8, p1);
        auto p9 = p7 / 2.0;
        ASSERT_EQ(p9, p1);
    }
}
