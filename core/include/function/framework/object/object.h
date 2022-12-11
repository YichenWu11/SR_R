#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <function/framework/component/component.h>
#include <function/framework/object/object_id_allocator.h>

namespace SRR {
    class GObject : public std::enable_shared_from_this<GObject> {
    public:
        GObject(GObjectID id) :
            m_id{id} {}
        virtual ~GObject();

        virtual void tick(float delta_time);

        GObjectID getID() const { return m_id; }

        void               setName(const std::string& name) { m_name = name; }
        const std::string& getName() const { return m_name; }

        bool hasComponent(const std::string& compenent_name) const;

        std::vector<Component*> getComponents() { return m_components; }

        template <typename TComponent>
        std::optional<TComponent*> tryGetComponent(const std::string& compenent_name) {
            for (auto& component : m_components) {
                if (component->getComponentName() == compenent_name) {
                    return static_cast<TComponent*>(component);
                }
            }
            return {};
        }

        template <typename TComponent>
        std::optional<const TComponent*> tryGetComponentConst(const std::string& compenent_name) const {
            for (const auto& component : m_components) {
                if (component->getComponentName() == compenent_name) {
                    return static_cast<const TComponent*>(component);
                }
            }
            return {};
        }

#define tryGetComponent(COMPONENT_TYPE) tryGetComponent<COMPONENT_TYPE>(#COMPONENT_TYPE)
#define tryGetComponentConst(COMPONENT_TYPE) tryGetComponentConst<const COMPONENT_TYPE>(#COMPONENT_TYPE)
    protected:
        GObjectID   m_id{k_invalid_gobject_id};
        std::string m_name;

        std::vector<Component*> m_components;
    };
} // namespace SRR