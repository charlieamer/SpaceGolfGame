#pragma once

#include "../Rendering/RenderingBackend.h"
#include <memory>

struct MeshComponent {
	bool visible;
    std::shared_ptr<RenderingBackendBase> backend;
    MeshComponent(RenderingBackendBase* rBackend) {
        backend = std::shared_ptr<RenderingBackendBase>(rBackend);
    }
    RenderingBackendBase* getBackend() {
        return backend.get();
    }
};