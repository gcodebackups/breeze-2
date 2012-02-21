/*****************************************************/
/* breeze Engine Physics Module (c) Tobias Zirr 2011 */
/*****************************************************/

#ifndef BE_PHYSICS_CHARACTER_PX
#define BE_PHYSICS_CHARACTER_PX

#include "bePhysics.h"
#include "../beCharacter.h"
#include <beCore/beWrapper.h>
#include <lean/tags/noncopyable.h>
#include "beCharactersAPI.h"

namespace bePhysics
{

// Creates a character.
BE_PHYSICS_PX_API physx::PxCapsuleController* CreateCharacter(physx::PxControllerManager &manager, physx::PxScene *pScene,
	const physx::PxCapsuleControllerDesc &desc);
// Creates a character.
BE_PHYSICS_PX_API physx::PxCapsuleController* CreateCharacter(physx::PxControllerManager &manager, physx::PxScene *pScene,
	const CharacterDesc &desc, const physx::PxMaterial *pMaterial);

// Prototypes
class Scene;
class Material;
class CharacterScene;

// Character callback interface.
class CharacterCallback : public physx::PxUserControllerHitReport
{
protected:
	~CharacterCallback() throw() { }
};

/// Dynamic rigid body implementation.
class CharacterPX : public lean::noncopyable_chain< beCore::TransitiveWrapper<physx::PxCapsuleController, CharacterPX> >, public Character
{
private:
	scoped_pxptr_t<physx::PxCapsuleController>::t m_pController;

public:
	/// Constructor.
	BE_PHYSICS_PX_API CharacterPX(CharacterScene &charScene, Scene &scene, const CharacterDesc &desc, const Material &material, CharacterCallback *pCallback);
	/// Constructor.
	BE_PHYSICS_PX_API CharacterPX(physx::PxCapsuleController *pController);
	/// Destructor.
	BE_PHYSICS_PX_API ~CharacterPX();

	/// Moves the character by the given amount.
	BE_PHYSICS_PX_API CharacterCollisionFlags Move(const beMath::fvec3 &move, float minDist = 0.00001f);

	/// Checks if the given shape would currently overlap.
	BE_PHYSICS_PX_API bool CheckShape(float radius, float height) const;
	/// Checks if the given shape would currently overlap.
	BE_PHYSICS_PX_API bool CheckShape(const beMath::fvec3 &pos, float radius, float height) const;

	/// Changes the shape.
	BE_PHYSICS_PX_API void SetShape(float radius, float height);
	/// Gets the current radius.
	BE_PHYSICS_PX_API float GetRadius() const;
	/// Gets the current height.
	BE_PHYSICS_PX_API float GetHeight() const;

	// Sets the position.
	BE_PHYSICS_PX_API void SetPosition(const beMath::fvec3 &pos);
	// Gets the current position.
	BE_PHYSICS_PX_API beMath::fvec3 GetPosition() const;

	/// Gets the current slope limit.
	BE_PHYSICS_PX_API float GetSlopeLimit() const;

	/// Sets the step offset.
	BE_PHYSICS_PX_API void SetStepOffset(float offset);
	/// Gets the current step offset.
	BE_PHYSICS_PX_API float GetStepOffset() const;

	/// Gets the implementation identifier.
	LEAN_INLINE ImplementationID GetImplementationID() const { return PXImplementation; }

	/// Gets the PhysX interface.
	LEAN_INLINE physx::PxCapsuleController*const& GetInterface() { return m_pController.get(); }
	/// Gets the PhysX interface.
	LEAN_INLINE const physx::PxCapsuleController*const& GetInterface() const { return m_pController.get(); }
	/// Gets the PhysX interface.
	LEAN_INLINE physx::PxCapsuleController*const& GetController() { return m_pController.get(); }
};

template <> struct ToImplementationPX<Character> { typedef CharacterPX Type; };

} // namespace

#endif