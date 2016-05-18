/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of REDHAWK core.
 * 
 * REDHAWK core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#include "ApplicationProfile.h"

using namespace ossie;

SinglePlacement::SinglePlacement(const ComponentInstantiation* instantiation) :
    instantiation(instantiation)
{
}

void SinglePlacement::accept(ApplicationVisitor* visitor)
{
    visitor->visitComponentPlacement(this);
}

const ComponentInstantiation* SinglePlacement::getComponentInstantiation() const
{
    return instantiation;
}


CollocationPlacement::CollocationPlacement(const std::string& id, const std::string& name) :
    id(id),
    name(name)
{
}

void CollocationPlacement::accept(ApplicationVisitor* visitor)
{
    visitor->visitHostCollocation(this);
}

const std::string& CollocationPlacement::getId() const
{
    return id;
}

const std::string& CollocationPlacement::getName() const
{
    return name;
}

const CollocationPlacement::PlacementList& CollocationPlacement::getPlacements() const
{
    return placements;
}

void CollocationPlacement::addPlacement(SinglePlacement* placement)
{
    placements.push_back(placement);
}

////////////////////////////////////////////////////
/*
 * ApplicationProfile member function definitions
 */
PREPARE_LOGGING(ApplicationProfile);

ApplicationProfile::ApplicationProfile()
{
}

ApplicationProfile::~ApplicationProfile()
{
    for (PlacementList::iterator placement = placements.begin(); placement != placements.end(); ++placement) {
        delete *placement;
    }
}

void ApplicationProfile::accept(ApplicationVisitor* visitor)
{
    visitor->visitApplication(this);
}

void ApplicationProfile::populateApplicationProfile(const SoftwareAssembly& sad)
{
    // Gets uses device relationships
    const std::vector<SoftwareAssembly::UsesDevice>& usesDevice = sad.getUsesDevices();
    for (std::vector<SoftwareAssembly::UsesDevice>::const_iterator use = usesDevice.begin(); use != usesDevice.end(); ++use) {
        UsesDeviceInfo* useDev = new UsesDeviceInfo(use->getId(), use->getType(), use->getDependencies());
        addUsesDevice(useDev);
    }

    // Walk through the host collocations first
    const std::vector<SoftwareAssembly::HostCollocation>& collocations = sad.getHostCollocations();
    for (size_t index = 0; index < collocations.size(); ++index) {
        const SoftwareAssembly::HostCollocation& collocation = collocations[index];
        LOG_TRACE(ApplicationProfile, "Building component info for host collocation "
                  << collocation.getID());
        CollocationPlacement* placement = new CollocationPlacement(collocation.getID(), collocation.getName());
        placements.push_back(placement);

        const std::vector<ComponentPlacement>& components = collocations[index].getComponents();
        for (unsigned int i = 0; i < components.size(); i++) {
            SinglePlacement* component = buildComponentPlacement(components[i]);
            placement->addPlacement(component);
        }
    }

    // Then, walk through the remaining non-collocated components
    const std::vector<ComponentPlacement>& components = sad.getComponentPlacements();
    for (unsigned int i = 0; i < components.size(); i++) {
        // ossie::ComponentInfo* component = buildComponentInfo(fileSys, sadParser, componentsFromSAD[i]);
        // if (component->getInstantiationIdentifier() == assemblyControllerRefId) {
        //     component->setIsAssemblyController(true);
        // }
        SinglePlacement* placement = buildComponentPlacement(components[i]);
        placements.push_back(placement);
    }
}

SinglePlacement* ApplicationProfile::buildComponentPlacement(const ComponentPlacement& placement)
{
    // Even though it is possible for there to be more than one instantiation
    // per component, the tooling doesn't support that, so supporting this at a
    // framework level would add substantial complexity without providing any
    // appreciable improvements. It is far easier to have multiple placements
    // rather than multiple instantiations.
    const std::vector<ComponentInstantiation>& instantiations = placement.getInstantiations();
    const ComponentInstantiation& instance = instantiations[0];

    return new SinglePlacement(&instance);
}

const ApplicationProfile::PlacementList& ApplicationProfile::getPlacements() const
{
    return placements;
}
