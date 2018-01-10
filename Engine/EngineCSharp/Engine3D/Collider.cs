﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Collider : Component
    {
        public RigidBody rigiBody
        {
            get;
            private set;
        }

        public void CreateRigiBody(float mass)
        {
            rigiBody = new RigidBody(this, mass);
        }
    }

    public class BoxCollider : Collider
    {
        public Vector3 Size
        {
            get; set;
        }
    }

    public class SphereCollider : Collider
    {

    }
}