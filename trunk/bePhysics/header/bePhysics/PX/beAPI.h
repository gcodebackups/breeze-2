/*****************************************************/
/* breeze Engine Physics Module (c) Tobias Zirr 2011 */
/*****************************************************/

#ifndef BE_PHYSICS_API_PX
#define BE_PHYSICS_API_PX

#include "bePhysics.h"
#include <PxPhysicsAPI.h>
#include <PxExtensionsAPI.h>
#include <lean/smart/scoped_ptr.h>

namespace bePhysics
{

/// API types.
namespace API
{
	/// PhysX foundation interface.
	typedef physx::PxFoundation Foundation;
	/// PhysX interface.
	typedef physx::PxPhysics Physics;
	/// PhysX scene.
	typedef physx::PxScene Scene;

	/// PhysX actor.
	typedef physx::PxActor Actor;

	/// PhysX rigid actor.
	typedef physx::PxRigidActor RigidActor;
	/// PhysX rigid body.
	typedef physx::PxRigidBody RigidBody;
	/// PhysX static rigid actor.
	typedef physx::PxRigidStatic RigidStatic;
	/// PhysX dynamic rigid body.
	typedef physx::PxRigidDynamic RigidDynamic;

	/// PhysX material.
	typedef physx::PxMaterial Material;

} // namespace

/// Scoped PhysX pointer.
template <class PhysX>
struct scoped_pxptr_t
{
	/// Scoped pointer type.
	typedef lean::scoped_ptr< PhysX, lean::smart::release_ptr_policy<PhysX> > t;
};

} // namespace

#endif