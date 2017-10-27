#ifndef _SERVICE_PLATFORM_HPP_
#define _SERVICE_PLATFORM_HPP_

#include "toolbox.hpp"

#include <memory>
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

    void setToolbox(std::shared_ptr<Tool> toolbox) {
        _toolbox = std::move(toolbox);
        std::cout << "Setting toolbox..." << std::endl;
    }

    std::shared_ptr<Tool> getToolbox() {
        return _toolbox;
    }

private:
    std::string _type;
    std::string _maintainer;
    std::string _helper;
    std::shared_ptr<Tool> _toolbox;
};

class Builder {
public:
    virtual void configureType() = 0;
    virtual void configureMaintainer() = 0;
    virtual void configureHelper() = 0;
    virtual void configureToolbox() = 0;

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

    void configureToolbox() {
        std::shared_ptr<Tool> spanner(new Spanner());
        std::shared_ptr<Tool> screwdriver(new Screwdriver());
        std::shared_ptr<Tool> pincher(new Pincher());
        std::shared_ptr<Tool> smallToolbox(new Toolbox());
    
        std::dynamic_pointer_cast<Toolbox>(smallToolbox)->add(spanner);
        std::dynamic_pointer_cast<Toolbox>(smallToolbox)->add(screwdriver);
    
        std::shared_ptr<Tool> largeToolbox(new Toolbox());
        std::dynamic_pointer_cast<Toolbox>(largeToolbox)->add(pincher);
        std::dynamic_pointer_cast<Toolbox>(largeToolbox)->add(smallToolbox);
    
        getServicePlatform().setToolbox(largeToolbox);
        getServicePlatform().getToolbox()->exert();
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

    void configureToolbox() {
        std::shared_ptr<Tool> spanner(new Spanner());
        std::shared_ptr<Tool> screwdriver(new Screwdriver());
        std::shared_ptr<Tool> pincher(new Pincher());
        std::shared_ptr<Tool> smallToolbox1(new Toolbox());
        std::shared_ptr<Tool> smallToolbox2(new Toolbox());
    
        std::dynamic_pointer_cast<Toolbox>(smallToolbox1)->add(screwdriver);
        std::dynamic_pointer_cast<Toolbox>(smallToolbox1)->add(pincher);
        std::dynamic_pointer_cast<Toolbox>(smallToolbox2)->add(pincher);
        std::dynamic_pointer_cast<Toolbox>(smallToolbox2)->add(spanner);
    
        std::shared_ptr<Tool> largeToolbox(new Toolbox());
        std::dynamic_pointer_cast<Toolbox>(largeToolbox)->add(smallToolbox1);
        std::dynamic_pointer_cast<Toolbox>(largeToolbox)->add(smallToolbox2);
        std::dynamic_pointer_cast<Toolbox>(largeToolbox)->add(spanner);
    
        getServicePlatform().setToolbox(largeToolbox);
        getServicePlatform().getToolbox()->exert();
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

    void configureToolbox() {
        std::shared_ptr<Tool> spanner(new Spanner());
        std::shared_ptr<Tool> screwdriver(new Screwdriver());
        std::shared_ptr<Tool> pincher(new Pincher());
        std::shared_ptr<Tool> toolbox(new Toolbox());
    
        std::dynamic_pointer_cast<Toolbox>(toolbox)->add(screwdriver);
        std::dynamic_pointer_cast<Toolbox>(toolbox)->add(pincher);
        std::dynamic_pointer_cast<Toolbox>(toolbox)->add(spanner);
    
        getServicePlatform().setToolbox(toolbox);
        getServicePlatform().getToolbox()->exert();
    }
};

class ServicePlatformDirector {
public:
    ServicePlatform getServicePlatform() {
        return _builder->getServicePlatform();
    }

    void setBuilder(std::unique_ptr<Builder> builder) {
        _builder = std::move(builder);
    }

    void construct() {
        _builder->configureType();
        _builder->configureMaintainer();
        _builder->configureHelper();
        _builder->configureToolbox();
    }

private:
    std::unique_ptr<Builder> _builder;
};

#endif
