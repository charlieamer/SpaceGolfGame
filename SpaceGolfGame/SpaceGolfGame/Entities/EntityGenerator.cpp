#include "EntityGenerator.h"

#include "../Components/CircleRadiusComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MeshTransformCacheComponent.h"
#include "../Components/AABBCacheComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/PlanetCollisionComponent.h"
#include "../Components/ParticleEmitterComponent.h"
#include "../Components/GravityComponent.h"

#include "../utilities.h"
#include "../Rendering/MeshGenerators.h"

void loadComponents(entityx::Entity entity, GleedCircle & circle)
{
	entity.assign<CircleRadiusComponent>(circle.radius / 1000.0f);
	if (circle.properties.count("Mesh")) {
		int vertexCount = std::stoi(circle.properties["Mesh"]);
		entity.assign_from_copy<StaticMeshComponent>(
			generateCircleMesh<Pos2fColorVertex, StaticMeshComponent>
				(Utilities::abgr(circle.color.r, circle.color.g, circle.color.b, circle.color.a), vertexCount));
	}
	loadComponents(entity, (GleedBaseObject&)circle);
}

void loadComponents(entityx::Entity entity, GleedBaseObject & object)
{
	entity.assign<PositionComponent>(object.position.x / 1000.0f, object.position.y / 1000.0f);
	entity.assign<MeshTransformCacheComponent>();
	entity.assign<AABBCacheComponent>();
	if (object.properties.count("Mass")) {
		entity.assign<MassComponent>(std::stof(object.properties["Mass"]));
	}
	if (object.properties.count("PlanetCollision")) {
		entity.assign<PlanetCollisionComponent>(true, true, std::stof(object.properties["PlanetCollision"]));
	}
	if (object.properties.count("ParticleEmitter")) {
		std::vector<float> values;
		std::vector<std::string> params = Utilities::explode(object.properties["ParticleEmitter"], ' ');
		for (auto param : params) {
			values.push_back(std::stof(param));
		}
		bool active = true;
		if (object.properties["ParticleEmitterActive"] == "false") {
			active = false;
		}
		entity.assign<ParticleEmitterComponent>(ParticleEmitterComponent{(int)values[0], values[1], values[2], (int)values[3], values[4], active});
	}
	if (object.properties.count("Gravity")) {
		entity.assign<GravityComponent>();
	}
}
