#pragma once
#ifndef CBLOCKASSERTATION_H
#define CBLOCKASSERTATION_H

#include "BlockInterpreter.hpp"
#include "BlockInstance.hpp"
#include "CBlockAction.hpp"


class CBlockAssertionBase : public CBlock //retorna uma declaracao
{
public:
    virtual HBlock get_obj() = 0; 
    CBlockAssertionBase() {}
  
};

using HBlockAssertionBase = std::shared_ptr<CBlockAssertionBase>;

class CBlockAssertion_is : public CBlockAssertionBase //retorna uma declaracao
{
public:
    void dump(string ident) override;


    virtual HBlock get_definition() = 0;

    //CBlockAssertion(HTerm obj, HTerm thing){};
    CBlockAssertion_is() {};

};

using HCBlockAssertion_is = std::shared_ptr<CBlockAssertion_is>;

//class CBlockAssertion_property_canBe : public CBlockAssertionBase //retorna uma declaracao
//{
//public:
//	void dump(std::string ident) override;
//
//	HBlockEnums definition;
//	//CBlockAssertion(HTerm obj, HTerm thing){};
//	CBlockAssertion_property_canBe(HBlockProperty _obj, HBlockEnums _definition) :CBlockAssertionBase(_obj), definition(_definition) {};
//	virtual NoumDefinitions noumDefinitions() override { return obj->noumDefinitions(); };
//};


class CBlockAssertion_canBe : public CBlockAssertionBase //retorna uma declaracao
{
public:
    virtual HBlock get_obj() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_canBe; }
    HBlockEnums definition;
    HBlock obj;

    //CBlockAssertion(HTerm obj, HTerm thing){};
    CBlockAssertion_canBe(HBlock _obj, HBlockEnums _definition);;
};

using HBlockAssertion_canBe = std::shared_ptr<CBlockAssertion_canBe>;

class CBlockAssertion_isKindOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    NoumDefinitions noumDefinitions() override;

    void dump(string ident) override;

    virtual HBlock get_definition() override;;

    HBlockKind noum;
    HBlockKind baseKind;

    CBlockAssertion_isKindOf(HBlockKind _noum, HBlockKind _baseKind) : noum(_noum), baseKind(_baseKind) {};
};

using HBlockAssertion_isKindOf = std::shared_ptr<CBlockAssertion_isKindOf>;

class CBlockAssertion_isInstanceOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isInstanceOf; }

    HBlockInstance noum;
    HBlockKind baseKind;

    CBlockAssertion_isInstanceOf(HBlockInstance _noum, HBlockKind _baseKind) : noum(_noum), baseKind(_baseKind) {};
};

using HBlockAssertion_isInstanceOf = std::shared_ptr<CBlockAssertion_isInstanceOf>;

class CBlockAssertion_isNamedValueOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isNamedValueOf; }

    HBlock noum;
    HBlock baseKind;

    CBlockAssertion_isNamedValueOf(HBlock _noum, HBlock _baseKind) : noum( (_noum)),
                                                                     baseKind( (_baseKind)) {};
};

using HBlockAssertion_isNamedValueOf = std::shared_ptr<CBlockAssertion_isNamedValueOf>;

class CBlockAssertion_isVariable : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isVariable; }

    HBlock variable;
    HBlock baseKind;

    CBlockAssertion_isVariable(HBlock _variable, HBlock _baseKind) : variable( (_variable)),
                                                                     baseKind( (_baseKind)) {};
};
using HBlockAssertion_isVariable = std::shared_ptr<CBlockAssertion_isVariable>;



class CBlockAssertion_isDefaultAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isDefaultAssign; }
    HBlock variable;
    HBlock value;

    CBlockAssertion_isDefaultAssign(HBlock _variable, HBlock _value) : variable( (_variable)),
                                                                       value( (_value)) {};
};

using HBlockAssertion_isDefaultAssign = std::shared_ptr<CBlockAssertion_isDefaultAssign>;

class CBlockAssertion_isConstantAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isConstantAssign; }

    HBlock variable;
    HBlock value;

    CBlockAssertion_isConstantAssign(HBlock _variable, HBlock _value) : variable( (_variable)),
                                                                        value( (_value)) {};
};

using HBlockAssertion_isConstantAssign = std::shared_ptr<CBlockAssertion_isConstantAssign>;

class CBlockAssertion_isForbiddenAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isForbiddenAssign; }

    HBlock variable;
    HBlock value;

    CBlockAssertion_isForbiddenAssign(HBlock _variable, HBlock _value) : variable( (_variable)),
                                                                         value( (_value)) {};
};
using HBlockAssertion_isForbiddenAssign = std::shared_ptr<CBlockAssertion_isForbiddenAssign>;



class CBlockAssertion_isDirectAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isDirectAssign; }


	HBlock variable;
    HBlock value;

    CBlockAssertion_isDirectAssign(HBlock _variable, HBlock _value) : variable( (_variable)),
                                                                      value( (_value)) {};
};

using HBlockAssertion_isDirectAssign = std::shared_ptr<CBlockAssertion_isDirectAssign>;

class CBlockAssertion_isNotDirectAssign : public CBlockAssertion_is //retorna uma declaracao
{
public:
    HBlock get_obj() override;

    HBlock get_definition() override;

    virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isNotDirectAssign; }

    HBlock variable;
    HBlock value;

    CBlockAssertion_isNotDirectAssign(HBlock _variable, HBlock _value) : variable( (_variable)),
                                                                         value( (_value)) {};
};

using HBlockAssertion_isNotDirectAssign = std::shared_ptr<CBlockAssertion_isNotDirectAssign>;

class CBlockAssertion_isActionOf : public CBlockAssertion_is //retorna uma declaracao
{
public:
    void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockAssertion_isActionOf; }
    HBlockNoum noum;
    HBlockAction action;
    HBlockActionApply application;

    CBlockAssertion_isActionOf(HBlockNoum _noum, HBlockAction _action, HBlockActionApply _application) : noum(_noum),
                                                                                                         action(_action),
                                                                                                         application(
                                                                                                                 _application) {};
};

using HBlockAssertion_isActionOf = std::shared_ptr<CBlockAssertion_isActionOf>;

class CBlockIsVerb : public CBlockAssertion_is    //retorna uma declaracao
{
public:
	HBlock get_obj() override;
	HBlock get_definition() override;
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockIsVerb; }


	string verb;
	HBlock n1;
	HBlock n2;

	CBlockIsVerb(string _verb, HBlock _n1, HBlock _n2) : verb((_verb)), n1((_n1)), n2((_n2)) {};
};
using HBlockIsVerb = std::shared_ptr<CBlockIsVerb>;


class CBlockIsNotVerb : public CBlockAssertion_is    //retorna uma declaracao
{
public:
	HBlock get_obj() override;
	HBlock get_definition() override;
	virtual void dump(string ident) override;
	virtual BlockType type() override { return BlockType::BlockIsNotVerb; }

	string verb;
	HBlock n1;
	HBlock n2;

	CBlockIsNotVerb(string _verb, HBlock _n1, HBlock _n2) : verb(_verb), n1((_n1)), n2((_n2)) {};
};
using HBlockIsNotVerb = std::shared_ptr<CBlockIsNotVerb>;

#endif //CBLOCKMATCH_H