#pragma once

#include <string>
#include <optional>

struct IntProperty
{
    mutable std::optional<int> value;

    int operator()(const std::string& str) const
    {
        if (!value.has_value())
        {
            value = str.size();
        }
        return value.value();
    }
};

struct MyStringProperty
{
    mutable std::optional<std::string> value;

    const std::string& operator()(const std::string& str) const
    {
        if (!value.has_value())
        {
            value = str.substr(0, 3);
        }
        return value.value();
    }
};

template <class... Types>
struct MyEntry
{
    using PropertiesType = std::tuple<Types...>;
    PropertiesType data;

    std::string m_Element;

    explicit MyEntry(std::string_view element)
        : m_Element(element)
    {
    }

    template <class T>
    auto GetProperty() const
    {
        return std::get<T>(data)(m_Element);
    }
};

template <class TEntry, class TProp>
struct Comparer
{
    bool operator()(const TEntry& lhs, const TEntry& rhs) const
    {
        return lhs.template GetProperty<TProp>() < rhs.template GetProperty<TProp>();
    }
};
