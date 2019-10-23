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
// Not copyrighted - public domain.
//
// This sample parser implementation was generated by CodeSynthesis XSD,
// an XML Schema to C++ data binding compiler. You may use it in your
// programs without any restrictions.
//

#ifndef CXX______XML_XSD_SPD_PIMPL_H
#define CXX______XML_XSD_SPD_PIMPL_H

#include "spd-pskel.h"
#include <ossie/logging/rh_logger.h>

namespace spd
{
  extern rh_logger::LoggerPtr parserLog;

  class softPkg_pimpl: public virtual softPkg_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    title (const ::std::string&);

    virtual void
    author (const ossie::SPD::Author&);

    virtual void
    description (const ::std::string&);

    virtual void
    propertyfile (const ::std::string&);

    virtual void
    descriptor (const ::std::string&);

    virtual void
    implementation (const ossie::SPD::Implementation&);

    virtual void
    usesdevice (const ossie::UsesDevice&);

    virtual void
    child ();

    virtual void
    id (const ::std::string&);

    virtual void
    name (const ::std::string&);

    virtual void
    type (const ::std::string&);

    virtual void
    version (const ::std::string&);

    virtual std::auto_ptr<ossie::SPD>
    post_softPkg ();

    private:
    std::auto_ptr<ossie::SPD> _spd;
  };

  class localFile_pimpl: public virtual localFile_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual ::std::string
    post_localFile ();

    public:
    std::string localfile;
  };

  class propertyFile_pimpl: public virtual propertyFile_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    localfile (const ::std::string&);

    virtual void
    type (const ::std::string&);

    virtual ::std::string
    post_propertyFile ();
    
    private:
    std::string propertyfile;
  };

  class author_pimpl: public virtual author_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual void
    company (const ::std::string&);

    virtual void
    webpage (const ::std::string&);

    virtual ossie::SPD::Author
    post_author ();

    private:
    std::auto_ptr<ossie::SPD::Author> author;
  };

  class descriptor_pimpl: public virtual descriptor_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    localfile (const ::std::string&);

    virtual void
    name (const ::std::string&);

    virtual ::std::string
    post_descriptor ();
    
    private:
    std::string _localfile;
  };

  class implementation_pimpl: public virtual implementation_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    description (const ::std::string&);

    virtual void
    propertyfile (const ::std::string&);

    virtual void
    code (const ossie::SPD::Code&);

    virtual void
    compiler (const ossie::SPD::NameVersionPair&);

    virtual void
    programminglanguage ();

    virtual void
    humanlanguage ();

    virtual void
    runtime (const ossie::SPD::NameVersionPair&);

    virtual void
    os (const ossie::SPD::NameVersionPair&);

    virtual void
    processor (const ::std::string&);

    virtual void
    dependency (ossie::DependencyRef*);

    virtual void
    usesdevice (const ossie::UsesDevice&);

    virtual void
    id (const ::std::string&);

    virtual void
    aepcompliance ();

    virtual ossie::SPD::Implementation
    post_implementation ();

    private:
    std::auto_ptr<ossie::SPD::Implementation> implementation;
  };

  class code_pimpl: public virtual code_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    localfile (const ::std::string&);

    virtual void
    entrypoint (const ::std::string&);

    virtual void
    stacksize (unsigned long long);

    virtual void
    priority (unsigned long long);

    virtual void
    type (::ossie::SPD::Code::CodeType);

    virtual ossie::SPD::Code
    post_code ();

    private:
    std::auto_ptr<ossie::SPD::Code> code;
  };

  class codeFileType_pimpl: public virtual codeFileType_pskel,
    public ::xml_schema::nmtoken_pimpl
  {
    public:
    virtual void
    pre ();

    virtual ::ossie::SPD::Code::CodeType
    post_codeFileType ();
  };

  class compiler_pimpl: public virtual compiler_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual void
    version (const ::std::string&);

    virtual ossie::SPD::NameVersionPair
    post_compiler ();

    private:
    ossie::SPD::NameVersionPair compiler;
  };

  class programmingLanguage_pimpl: public virtual programmingLanguage_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual void
    version (const ::std::string&);

    virtual void
    post_programmingLanguage ();
  };

  class humanLanguage_pimpl: public virtual humanLanguage_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual void
    post_humanLanguage ();
  };

  class os_pimpl: public virtual os_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual void
    version (const ::std::string&);

    virtual ossie::SPD::NameVersionPair
    post_os ();
    
    private:
    ossie::SPD::NameVersionPair os;
  };

  class processor_pimpl: public virtual processor_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual ::std::string
    post_processor ();

    private:
    std::string processor;
  };

  class dependency_pimpl: public virtual dependency_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    softpkgref (const ossie::SPD::SoftPkgRef& ref);

    virtual void
    propertyref (const ossie::PropertyRef&);

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual void
    structref (const ossie::StructPropertyRef&);

    virtual void
    structsequenceref (const ossie::StructSequencePropertyRef&);

    virtual void
    type (const ::std::string&);

    virtual ossie::DependencyRef*
    post_dependency ();

    private:
    std::auto_ptr<ossie::DependencyRef> _ref;
  };

  class runtime_pimpl: public virtual runtime_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    name (const ::std::string&);

    virtual void
    version (const ::std::string&);

    virtual ossie::SPD::NameVersionPair
    post_runtime ();

    private:
    ossie::SPD::NameVersionPair runtime;
  };

  class propertyRef_pimpl: public virtual propertyRef_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual void
    value (const ::std::string&);

    virtual ossie::PropertyRef
    post_propertyRef ();

    private:
    ossie::SimplePropertyRef _ref;
  };

  class softPkgRef_pimpl: public virtual softPkgRef_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    localfile (const ::std::string&);

    /*virtual void
    implref ();*/
    virtual void
    implref (const ::std::string&);

    virtual ossie::SPD::SoftPkgRef
    post_softPkgRef ();

    private:
    ossie::SPD::SoftPkgRef _ref;
  };

  class implRef_pimpl: public virtual implRef_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual ::std::string
    post_implRef ();

    private:
    ::std::string _refid;
  };

  class usesDevice_pimpl: public virtual usesDevice_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    propertyref (const ossie::PropertyRef&);

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual void
    structref (const ossie::StructPropertyRef&);

    virtual void
    structsequenceref (const ossie::StructSequencePropertyRef&);

    virtual void
    id (const ::std::string&);

    virtual void
    type (const ::std::string&);

    virtual ossie::UsesDevice
    post_usesDevice ();

    private:
    std::auto_ptr<ossie::UsesDevice> _uses;
  };

  class aepcompliance_pimpl: public virtual aepcompliance_pskel,
    public ::xml_schema::nmtoken_pimpl
  {
    public:
    virtual void
    pre ();

    virtual void
    post_aepcompliance ();
  };

  class simpleref_pimpl: public virtual simpleref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    refid (const ::std::string&);

    virtual void
    value (const ::std::string&);

    virtual const ossie::SimplePropertyRef&
    post_simpleref ();
    
    private:
    ossie::SimplePropertyRef simple;
  };

  class simplesequenceref_pimpl: public virtual simplesequenceref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    values (const ::std::vector<std::string>&);

    virtual void
    refid (const ::std::string&);

    virtual const ossie::SimpleSequencePropertyRef&
    post_simplesequenceref ();
    private:
    ossie::SimpleSequencePropertyRef simpleseq;
  };

  class structref_pimpl: public virtual structref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual void
    refid (const ::std::string&);

    virtual const ossie::StructPropertyRef &
    post_structref ();

    private:
    ossie::StructPropertyRef structref;
  };

  class structsequenceref_pimpl: public virtual structsequenceref_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    structvalue (const ossie::ComponentPropertyMap&);

    virtual void
    refid (const ::std::string&);

    virtual const ossie::StructSequencePropertyRef&
    post_structsequenceref ();

    private:
    ossie::StructSequencePropertyRef structsequenceref;
  };

  class structvalue_pimpl: public virtual structvalue_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    simpleref (const ossie::SimplePropertyRef&);

    virtual void
    simplesequenceref (const ossie::SimpleSequencePropertyRef&);

    virtual const ossie::ComponentPropertyMap&
    post_structvalue ();

    private:
    ossie::ComponentPropertyMap values;
  };

  class values_pimpl: public virtual values_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    value (const ::std::string&);

    virtual ::std::vector<std::string>
    post_values ();

    private:
    ::std::vector<std::string> values;
  };

  class childPropertyFile_pimpl: public virtual childPropertyFile_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    localfile (const ::std::string&);

    virtual void
    post_childPropertyFile ();
  };

  class childDescriptorFile_pimpl: public virtual childDescriptorFile_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    localfile (const ::std::string&);

    virtual void
    post_childDescriptorFile ();
  };

  class child_pimpl: public virtual child_pskel
  {
    public:
    virtual void
    pre ();

    virtual void
    childPropertyFile ();

    virtual void
    childDescriptorFile ();

    virtual void
    name (const ::std::string&);

    virtual void
    post_child ();
  };
}

#endif // CXX______XML_XSD_SPD_PIMPL_H
