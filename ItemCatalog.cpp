#include "ItemCatalog.hpp"
#include <algorithm>
#include <iterator>
#include <vector>
#include <fmt/base.h>

int main(int argc, char* argv[])
{
    std::vector<SomeObject> database = std::initializer_list<SomeObject>{
        "Berlin",
        "Madrid",
        "Rome",
        "Paris",
        "Vienna",
        "Warsaw",
        "Hamburg",
        "Bucharest",
        "Barcelona",
        "Budapest",
        "Munich",
        "Prague",
        "Milan",
        "Sofia",
        "Cologne",
        "Stockholm",
        "Amsterdam",
        "Naples",
        "Marseille",
        "Turin"
    };

    using EntryType = ElementQuery<NameLengthProperty, ShortNameProperty>;

    std::vector<EntryType> entries;
    std::transform(
        database.begin(),
        database.end(),
        std::back_inserter(entries),
        [](SomeObject& obj)
        {
            return EntryType{obj};
        });

    auto print = [&](std::string_view header)
    {
        fmt::println(header);
        for (const auto& entry : entries)
        {
            fmt::println("Entry: {} prop1: {} prop2: {}", entry.m_Object->m_Name, entry.GetProperty<NameLengthProperty>(),
                         entry.GetProperty<ShortNameProperty>());
        }
    };

    std::sort(entries.begin(), entries.end(), Comparer<EntryType, ShortNameProperty>());
    print("Sorted by ShortNameProperty:");

    std::sort(entries.begin(), entries.end(), Comparer<EntryType, NameLengthProperty>());
    print("\nSorted by NameLengthProperty:");

    entries.erase(std::remove_if(entries.begin(), entries.end(), [](const EntryType& entry)
    {
        return entry.GetProperty<NameLengthProperty>() < 6;
    }), entries.end());
    print("\nFiltered:");

    return 0;
}
