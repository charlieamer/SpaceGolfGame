#pragma once

struct PlanetCollisionComponent {
	PlanetCollisionComponent(bool generateEvent, bool calculatePointOfEntry, float damping = 1.0f)
		: generateEvent(generateEvent),
		  calculatePointOfEntry(calculatePointOfEntry),
		  damping(damping) {}
	bool generateEvent;
	bool calculatePointOfEntry;
	float damping;
};