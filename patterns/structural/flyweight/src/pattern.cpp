#include "pattern.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace flyweight {

/** Heavy part of the item that should be shared between many items */
struct SharedItemPart {
    std::string model3d{};

    bool operator==(const SharedItemPart& other) const {
        return model3d == other.model3d;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const SharedItemPart& sharedItemPart) {
        return out << sharedItemPart.model3d;
    }
};

/** Light part of the item that is unique for each item */
struct UniqueItemPart {
    std::string name{};

    friend std::ostream& operator<<(std::ostream& out,
                                    const UniqueItemPart& uniqueItemPart) {
        return out << uniqueItemPart.name;
    }
};

/** An item itself containing flyweight part as a pointer and a unique part as a
 * copy */
struct Item {
    std::shared_ptr<SharedItemPart> sharedPartPtr;
    UniqueItemPart uniquePart{};

    friend std::ostream& operator<<(std::ostream& out, const Item& item) {
        return out << "{"
                   << (item.sharedPartPtr ? item.sharedPartPtr->model3d
                                          : "<null>")
                   << ", " << item.uniquePart.name << "}";
    }
};

/** A storage that uses separate container to store shared items' parts */
class FlyweightStorage {
public:
    void add(SharedItemPart&& sharedItemPart, UniqueItemPart&& uniqueItemPart) {
        std::cout << "Adding new item: shared part: " << sharedItemPart
                  << ", unique part: " << uniqueItemPart << "\n";
        Item item{};
        item.uniquePart = std::move(uniqueItemPart);
        const auto sharedPartIt = std::find_if(
            sharedPartPtrs.begin(), sharedPartPtrs.end(),
            [&sharedItemPart](const auto& sharedPartPtr) {
                return sharedPartPtr && *sharedPartPtr == sharedItemPart;
            });
        if (sharedPartIt != sharedPartPtrs.end()) {
            item.sharedPartPtr = *sharedPartIt;
        } else {
            sharedPartPtrs.push_back(
                std::make_shared<SharedItemPart>(std::move(sharedItemPart)));
            item.sharedPartPtr = sharedPartPtrs.back();
        }
        items.push_back(std::move(item));
    }

    void printItems() const {
        for (const auto& item : items) {
            std::cout << item << "\n";
        }
    }

    void printSharedParts() const {
        for (const auto& sharedPartPtr : sharedPartPtrs) {
            std::cout << (sharedPartPtr ? *sharedPartPtr : SharedItemPart{})
                      << "\n";
        }
    }

private:
    std::vector<std::shared_ptr<SharedItemPart>> sharedPartPtrs;
    std::vector<Item> items;
};

void run() {
    std::cout << "\n=== Flyweight ===\n";
    std::cout << "\nIn this example an array of items is passed to a storage "
                 "system. This system stores all items as a combination of "
                 "shared part (actual 3D model) that is equal for several item "
                 "and a unique part for each item (id and name)\n\n";

    auto flyweightStoragePtr = std::make_shared<FlyweightStorage>();
    flyweightStoragePtr->add({"<cube>"}, {"form1"});
    flyweightStoragePtr->add({"<sphere>"}, {"form2"});
    flyweightStoragePtr->add({"<cylinder>"}, {"form3"});
    flyweightStoragePtr->add({"<sphere>"}, {"form4"});
    flyweightStoragePtr->add({"<cube>"}, {"form5"});
    flyweightStoragePtr->add({"<sphere>"}, {"form6"});
    flyweightStoragePtr->add({"<cube>"}, {"form7"});
    flyweightStoragePtr->add({"<cylinder>"}, {"form8"});
    flyweightStoragePtr->add({"<cylinder>"}, {"form9"});

    std::cout << "\nAll items in storage:\n\n";
    flyweightStoragePtr->printItems();

    std::cout << "\nShared item parts in storage:\n\n";
    flyweightStoragePtr->printSharedParts();
}

}  // namespace flyweight
