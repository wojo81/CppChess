#pragma once

#include <memory>
#include <vector>

namespace chess {
    template <typename Base, typename Derived>
    struct Cloner : Base {
        template <typename ... Args>
        explicit Cloner(Args && ... args) : 
            Base{std::forward<Args>(args)...} {}

        auto Clone() const -> std::unique_ptr<Base> override {
            return std::make_unique<Derived>(*dynamic_cast<Derived const*>(this));
        }
    };

    template <typename Base>
    auto CloneAll(std::vector<std::unique_ptr<Base>> const& cloneables) -> std::vector<std::unique_ptr<Base>> {
        std::vector<std::unique_ptr<Base>> newCloneables;
        newCloneables.reserve(cloneables.size());
        for (auto const& cloneable : cloneables)
            newCloneables.push_back(cloneable);
        return newCloneables;
    }
}