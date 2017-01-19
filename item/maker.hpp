#pragma once
#include "item/item.h"
#include <memory>
#include "utility/raii.hpp"

namespace item
<%

using constructor = std::unique_ptr<item> (*) (item* parent);

inline QHash<QByteArray, constructor>& constructors ()
{
    static QHash<QByteArray, constructor> instance;
    return instance;
}



template<typename T>
void regester_class (QByteArray classname)
{
    constructors().insert(::move (classname), [] (item* parent){return std::make_unique<T> (new T (parent)); });
}

inline std::unique_ptr<item> make_item (const QByteArray& classname, item* parent = nullptr)
{
    auto constructor = constructors().value(classname);
    if (constructor == nullptr)
    {
        return {};
    }
    return constructor (parent);
}



%>
