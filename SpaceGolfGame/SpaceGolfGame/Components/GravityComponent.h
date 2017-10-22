#pragma once

struct GravityComponent {
    GravityComponent(bool useFastUpdate = false) {
        fast = useFastUpdate;
    }
    bool fast;
};