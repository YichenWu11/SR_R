#pragma once

#include <any>
#include <memory>
#include <string>

namespace SRR {
    class GObject;
    class Component {
    protected:
        std::weak_ptr<GObject> m_parent_object;
        bool                   m_is_dirty{false};
        std::string            m_name;

    public:
        Component(const std::string& n) :
            m_name(n) {}
        virtual ~Component() {}

        virtual void tick(float delta_time){};

        void mountToGObject(std::weak_ptr<GObject> parent_object) { m_parent_object = parent_object; }
        bool isDirty() const { return m_is_dirty; }
        void setDirtyFlag(bool is_dirty) { m_is_dirty = is_dirty; }

        virtual std::any getImpl() { return {}; }

        std::string& getComponentName() { return m_name; }
        std::string  getComponentName() const { return m_name; }
    };
} // namespace SRR
