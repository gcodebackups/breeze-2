/****************************************************/
/* breeze Engine Scene Module  (c) Tobias Zirr 2011 */
/****************************************************/

#ifndef BE_SCENE_LIGHT_CONTROLLER_SERIALIZER
#define BE_SCENE_LIGHT_CONTROLLER_SERIALIZER

#include "beScene.h"
#include <beEntitySystem/beControllerSerializer.h>

namespace beScene
{

/// Serializes light controllers.
template <class LightController>
class LightControllerSerializer : public beEntitySystem::ControllerSerializer
{
public:
	typedef beEntitySystem::ControllerSerializer ControllerSerializer;
	typedef LightController LightController;

	/// Constructor.
	BE_SCENE_API LightControllerSerializer();
	/// Destructor.
	BE_SCENE_API ~LightControllerSerializer();

	/// Creates a serializable object from the given parameters.
	BE_SCENE_API virtual lean::resource_ptr<Serializable, true> Create(const beCore::Parameters &creationParameters, const beCore::ParameterSet &parameters) const;

	/// Loads a mesh controller from the given xml node.
	BE_SCENE_API virtual lean::resource_ptr<beEntitySystem::Controller, true> Load(const rapidxml::xml_node<lean::utf8_t> &node,
		beCore::ParameterSet &parameters, beEntitySystem::SerializationQueue<beEntitySystem::LoadJob> &queue) const;
	/// Saves the given mesh controller to the given XML node.
	BE_SCENE_API virtual void Save(const beEntitySystem::Controller *pSerializable, rapidxml::xml_node<lean::utf8_t> &node,
		beCore::ParameterSet &parameters, beEntitySystem::SerializationQueue<beEntitySystem::SaveJob> &queue) const;
};

class DirectionalLightController;
class PointLightController;
class SpotLightController;

/// Directional light controller serializer class.
typedef LightControllerSerializer<DirectionalLightController> DirectionalLightControllerSerializer;
/// Point light controller serializer class.
typedef LightControllerSerializer<PointLightController> PointLightControllerSerializer;
/// Spot light controller serializer class.
typedef LightControllerSerializer<SpotLightController> SpotLightControllerSerializer;

} // namespace

#endif