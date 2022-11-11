#include "pattern.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace proxy {

namespace {

/** Base interface for both real and proxy objects */
class ObjectBase {
public:
    virtual std::string getData() const = 0;
    virtual void setData(const std::string& newData) = 0;
};

/** Real object that stores some data */
class ObjectReal : public ObjectBase {
public:
    /** returns a copy of some big data */
    virtual std::string getData() const override {
        std::cout << "ObjectReal: retrieving data\n";
        didDataUpdated = false;
        return data;
    }
    virtual void setData(const std::string& newData) override {
        std::cout << "ObjectReal: setting new data\n";
        didDataUpdated = true;
        data = newData;
    }
    bool hasChanges() const { return didDataUpdated; }

private:
    std::string data;
    mutable bool didDataUpdated = false;
};

/** Proxy object that caches data from the real object */
class ObjectProxy : public ObjectBase {
public:
    ObjectProxy(const std::shared_ptr<ObjectReal>& newObjectRealPtr)
        : objectRealPtr(newObjectRealPtr) {}
    /** return a cached copy of data stored in proxy object. The call doesn't
     * obtain data from real object */
    virtual std::string getData() const override {
        if (objectRealPtr && objectRealPtr->hasChanges()) {
            cachedData = objectRealPtr->getData();
        } else {
            std::cout << "ObjectProxy: retrieving cached data\n";
        }
        return cachedData;
    };
    virtual void setData(const std::string& newData) override {
        if (objectRealPtr) {
            objectRealPtr->setData(newData);
        }
    }

private:
    std::shared_ptr<ObjectReal> objectRealPtr;
    mutable std::string cachedData;
};

void clientCode(const std::shared_ptr<ObjectBase>& objectPtr) {
    if (!objectPtr) {
        return;
    }
    objectPtr->setData("data1");
    std::cout << objectPtr->getData() << "\n";
    std::cout << objectPtr->getData() << "\n";
    std::cout << objectPtr->getData() << "\n";
    objectPtr->setData("data2");
    std::cout << objectPtr->getData() << "\n";
    std::cout << objectPtr->getData() << "\n";
    std::cout << objectPtr->getData() << "\n";
}

}  // namespace

void run() {
    std::cout << "\n=== Proxy ===\n";
    std::cout << "\nIn this example user retrieves data from real object. "
                 "Every call is expensive.\n\n";
    auto objectRealPtr = std::make_shared<ObjectReal>();
    clientCode(objectRealPtr);
    std::cout << "\nIn this example user uses proxy object to obtain data. If "
                 "data didn't change from the previous call proxy object "
                 "returns cached value of the data.\n\n";
    auto objectProxyPtr = std::make_shared<ObjectProxy>(objectRealPtr);
    clientCode(objectProxyPtr);
}

}  // namespace proxy
