#ifndef _SERVICE_PLATFORM_HPP_
#define _SERVICE_PLATFORM_HPP_

#include <string>
#include <iostream>

class ServicePlatform {
public:
    void setType(std::string type) {
        _type = type;
        std::cout << "Setting type: " << type << std::endl;
    }

    void setMaintainer(std::string maintainer) {
        _maintainer = maintainer;
        std::cout << "Setting maintainer: " << maintainer << std::endl;
    }

    void setHelper(std::string helper) {
        _helper = helper;
        std::cout << "Setting helper: " << helper << std::endl;
    }

private:
    std::string _type;
    std::string _maintainer;
    std::string _helper;
};

class Builder {
public:
    virtual void configureType() = 0;
    virtual void configureMaintainer() = 0;
    virtual void configureHelper() = 0;

    ServicePlatform &getServicePlatform() {
        return servicePlatform;
    }

private:
    ServicePlatform servicePlatform;
};

class BenzServicePlatformBuilder : public Builder {
public:
    void configureType() {
        getServicePlatform().setType(std::string("BenzServicePlatform"));
    }

    void configureMaintainer() {
        getServicePlatform().setMaintainer(std::string("BenzMaintainer"));
    }

    void configureHelper() {
        getServicePlatform().setHelper(std::string("BenzHelper"));
    }
};

class BmwServicePlatformBuilder : public Builder {
public:
    void configureType() {
        getServicePlatform().setType(std::string("BmwServicePlatform"));
    }

    void configureMaintainer() {
        getServicePlatform().setMaintainer(std::string("BmwMaintainer"));
    }

    void configureHelper() {
        getServicePlatform().setHelper(std::string("BmwHelper"));
    }
};

class AudiServicePlatformBuilder : public Builder {
public:
    void configureType() {
        getServicePlatform().setType(std::string("AudiServicePlatform"));
    }

    void configureMaintainer() {
        getServicePlatform().setMaintainer(std::string("AudiMaintainer"));
    }

    void configureHelper() {
        getServicePlatform().setHelper(std::string("AudiHelper"));
    }
};

class ServicePlatformDirector {
public:
    ServicePlatform getServicePlatform() {
        return _builder->getServicePlatform();
    }

    void setBuilder(Builder *builder) {
        _builder = builder;
    }

    void construct() {
        _builder->configureType();
        _builder->configureMaintainer();
        _builder->configureHelper();
    }

private:
    Builder *_builder;
};

#endif