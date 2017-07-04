#pragma once
struct ParticleComponent {
	ParticleComponent(int updates, int maxUpdates) : remainingUpdates(updates), maxUpdates(maxUpdates) {};
	int remainingUpdates;
	int maxUpdates;
};