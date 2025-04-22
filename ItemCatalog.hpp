#pragma once

#include <string>
#include <optional>
#include <fmt/base.h>
#include <fmt/format.h>

enum class ECountry
{
    Austria,
    Bulgaria,
    Czechia,
    France,
    Germany,
    Italy,
    Netherlands,
    Poland,
    Romania,
    Spain,
    Sweden
};

template <> struct fmt::formatter<ECountry> : fmt::formatter<std::string_view>
{
    auto format(const ECountry& country, fmt::format_context& ctx) const -> format_context::iterator
    {
        std::string_view output = "Unknown";
        switch (country)
        {
        case ECountry::Austria:
            output = "Austria";
            break;
        case ECountry::Bulgaria:
            output = "Bulgaria";
            break;
        case ECountry::Czechia:
            output = "Czechia";
            break;
        case ECountry::France:
            output = "France";
            break;
        case ECountry::Germany:
            output = "Germany";
            break;
        case ECountry::Italy:
            output = "Italy";
            break;
        case ECountry::Netherlands:
            output = "Netherlands";
            break;
        case ECountry::Poland:
            output = "Poland";
            break;
        case ECountry::Romania:
            output = "Romania";
            break;
        case ECountry::Spain:
            output = "Spain";
            break;
        case ECountry::Sweden:
            output = "Sweden";
            break;
        }

        return formatter<string_view>::format(output, ctx);
    }
};

struct SomeObject
{
    std::string m_Name;
    ECountry m_Country;

    SomeObject(const char* name, ECountry country) : m_Name(name), m_Country(country) {}
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

struct CountryProperty
{
    mutable std::optional<ECountry> value;

    ECountry operator()(const SomeObject& obj) const
    {
        if (!value.has_value())
        {
            value = obj.m_Country;
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
