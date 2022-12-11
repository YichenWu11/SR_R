#include <function/framework/object/object.h>

namespace SRR {
    GObject::~GObject() {
        m_components.clear();
    }

    void GObject::tick(float delta_time) {
        for (auto& component : m_components) {
            component->tick(delta_time);
        }
    }

    bool GObject::hasComponent(const std::string& compenent_name) const {
        for (const auto& component : m_components) {
            if (component->getComponentName() == compenent_name)
                return true;
        }

        return false;
    }

} // namespace SRR