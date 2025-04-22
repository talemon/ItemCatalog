#include "ItemCatalog.hpp"
#include <algorithm>
#include <iterator>
#include <vector>
#include <fmt/base.h>

int main(int argc, char* argv[])
{
    std::vector<SomeObject> database = std::initializer_list<SomeObject>{
        {"Berlin", ECountry::Germany},
        {"Madrid", ECountry::Italy},
        {"Rome", ECountry::Italy},
        {"Paris", ECountry::France},
        {"Vienna", ECountry::Austria},
        {"Warsaw", ECountry::Poland},
        {"Hamburg", ECountry::Germany},
        {"Bucharest", ECountry::Romania},
        {"Barcelona", ECountry::Spain},
        {"Budapest", ECountry::Romania},
        {"Munich", ECountry::Germany},
        {"Prague", ECountry::Czechia},
        {"Milan", ECountry::Italy},
        {"Sofia", ECountry::Bulgaria},
        {"Cologne", ECountry::Germany},
        {"Stockholm", ECountry::Sweden},
        {"Amsterdam", ECountry::Netherlands},
        {"Naples", ECountry::Italy},
        {"Marseille", ECountry::France},
        {"Turin", ECountry::Italy}
    };

    using EntryType = ElementQuery<NameLengthProperty, ShortNameProperty, CountryProperty>;

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
            fmt::println("Entry: {} Len: {} Short: {} Country: {}", entry.m_Object->m_Name, entry.GetProperty<NameLengthProperty>(),
                         entry.GetProperty<ShortNameProperty>(), entry.GetProperty<CountryProperty>());
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

    std::stable_sort(entries.begin(), entries.end(), Comparer<EntryType, CountryProperty>());
    print("\nGrouped by country:");

    return 0;
}
