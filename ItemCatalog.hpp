#pragma once

#include <string>
#include <optional>

struct SomeObject
{
    std::string m_Name;

    SomeObject(const char* name) : m_Name(name) {}
};

///

struct NameLengthProperty
{
    mutable std::optional<int> value;

    int operator()(const SomeObject& obj) const
    {
        if (!value.has_value())
        {
            value = obj.m_Name.size();
        }
        return value.value();
    }
};

struct ShortNameProperty
{
    mutable std::optional<std::string> value;

    const std::string& operator()(const SomeObject& obj) const
    {
        if (!value.has_value())
        {
            value = obj.m_Name.substr(0, 3);
        }
        return value.value();
    }
};

template <class... Types>
struct ElementQuery
{
    using PropertiesType = std::tuple<Types...>;
    PropertiesType data;

    SomeObject* m_Object;

    explicit ElementQuery(SomeObject& obj)
        : m_Object(&obj)
    {
    }

    template <class T>
    auto GetProperty() const
    {
        return std::get<T>(data)(*m_Object);
    }
};

template <class TElem, class TProp>
struct Comparer
{
    bool operator()(const TElem& lhs, const TElem& rhs) const
    {
        return lhs.template GetProperty<TProp>() < rhs.template GetProperty<TProp>();
    }
};
