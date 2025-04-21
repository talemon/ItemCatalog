
#include "ItemCatalog.hpp"
#include <algorithm>
#include <vector>
#include <fmt/base.h>

int main(int argc, char* argv[])
{
    using EntryType = MyEntry<IntProperty, MyStringProperty>;

    std::vector<EntryType> entries;
    entries.emplace_back("Patates");
    entries.emplace_back("Osmancik");
    entries.emplace_back("Portakal");
    entries.emplace_back("Cilek");
    entries.emplace_back("Portal");
    entries.emplace_back("Kimchi");
    entries.emplace_back("Headphones");
    entries.emplace_back("Speaker");
    entries.emplace_back("Roshan");
    entries.emplace_back("Donuts");
    entries.emplace_back("Egg");
    entries.emplace_back("Menemen");
    entries.emplace_back("Inigo Montoya");

    auto print = [&](std::string_view header)
    {
        fmt::println(header);
        for (const auto& entry : entries)
        {
            fmt::println("Entry: {} prop1: {} prop2: {}", entry.m_Element, entry.GetProperty<IntProperty>(), entry.GetProperty<MyStringProperty>());
        }
    };

    std::sort(entries.begin(), entries.end(), Comparer<EntryType, MyStringProperty>());
    print("Sorted by string property:");
    
    std::sort(entries.begin(), entries.end(), Comparer<EntryType, IntProperty>());
    print("\nSorted by IntProperty:");

    entries.erase(std::remove_if(entries.begin(), entries.end(), [](const EntryType& entry)
    {
        return entry.GetProperty<IntProperty>() < 6; 
    }), entries.end());
    print("\nFiltered:");
    
    return 0;
}
