#include "BlockInterpreter.h"
#include <iostream>
#include "CblockAssertion.h"
#include "CBlockMatch.h"
#include "CBlockDumpValues.h"

using namespace std;

NoumDefinitions noum_nothing()
{
	return NoumDefinitions();
}

 

NoumDefinitions single_definitions(string noun, UBlock block)
{
	return 	NoumDefinitions({ NoumDefinition(noun, block) });
}

NoumDefinitions join_definitions(NoumDefinitions a, NoumDefinitions b)
{
	NoumDefinitions ab(a.begin(), a.end());
	ab.insert(ab.end(), b.begin(), b.end());
	return ab;
}

void* CBlock::operator new(size_t size)
{
		 
	std::cout << "    New Block: " <<   '\n';
	return malloc(size);
		 
}

CUnresolved::CUnresolved(string _contents): contents(_contents)
{
}

CBlockNoum::CBlockNoum(std::string _value)
{
	named = _value;
	//assert(named[0] != '[');
}


CBlockEnums::CBlockEnums(std::vector<CBlockNoum*> _values): values(_values)
{

}

bool CBlockEnums::contains(string cs)
{
	for(auto &n : values)
	{
		if (n->named == cs) return true;
	}
	return false;
}


CBlockNamedValue::CBlockNamedValue(string _named) : named(_named)
{
	assert(_named[0] != '[');
}

CBlockVariable::CBlockVariable(string _named) : named(_named)
{
	assert(_named[0] != '[');
}


CBlockProperty::CBlockProperty(UBlock _prop, UBlock _obj): prop(( _prop)), obj(( _obj))
{

}

CBlockInstanceVariable::CBlockInstanceVariable(CBlockNoum* _kind_name, CBlockNoum* _called) : property_name( _called), kind_name( (_kind_name))
{
}


void CBlockList::push_back(UBlock c_block_value)
{
	lista.push_back( (c_block_value));
}

NoumDefinitions CBlockList::noumDefinitions()
{
	NoumDefinitions nd = noum_nothing();
	for(auto &i : lista)
	{
		nd = join_definitions(nd, i->noumDefinitions());
	}
	return nd;
}


bool CBlockMatchNamed::match()
{ return matchInner->match(); }

CBlockActionApply::CBlockActionApply(UBlock   _noum1, UBlock  _noum2): noum1((_noum1)), noum2((_noum2))
{
}



//  define  ((Person:A) eat (thing:B)) is a Action.  -> first noum, second noum
//  define ((action:A) is in the presence of (other:B) ) if (( location of (first noum of A) ) is same (location B)).
//  eating something in the presence of Lady Bracknell

void eatExample()
{
	/*CBlockAssertion(CBlockAction( CBlockNoum("Person"), "eat", CBlockNoum("Thing")));

	CBlockAssertionCond(CBlockAssertion(CBlockAction("Action","A"), "in presence of", CBlockNoum("Person", "other")),
	CBlockSame(CBlockProp(CBlockNoum("location"), CBlockProp(CBlockNoum("first noum"), CBlockNoum("A")),
	CBlockProp(CBlockNoum("location"), CBlockNoum("other")))));

	CBlockMatchAction((CBlockAction("eat"), CBlockNoum("something")), "in presence of", CBlockNoum("Lady Bracknell"));
	*/


}


CBlock* CBlockAssertion_canBe::get_obj()
{
	return obj;
}


CBlockAssertion_canBe::CBlockAssertion_canBe(UBlock _obj, CBlockEnums* _definition) :   definition(_definition) , obj(_obj)
{
}

CBlock* CBlockAssertion_isKindOf::get_obj()
{
	return noum;
}

NoumDefinitions CBlockAssertion_isKindOf::noumDefinitions()
{
	return  single_definitions(this->noum->named, this->get_definition() );
}

CBlock* CBlockAssertion_isKindOf::get_definition()
{ return baseKind ; }

CBlock* CBlockAssertion_isInstanceOf::get_obj()
{
	return noum;
}

CBlock* CBlockAssertion_isInstanceOf::get_definition()
{
	return baseKind;
}

UBlock CBlockAssertion_isNamedValueOf::get_obj()
{
	return this->noum;
}

UBlock CBlockAssertion_isNamedValueOf::get_definition()
{
	return this->baseKind ;
}

UBlock CBlockAssertion_isVariable::get_obj()
{
	return variable;
}

UBlock CBlockAssertion_isVariable::get_definition()
{
	return baseKind;
}

CBlock* CBlockAssertion_isDefaultAssign::get_obj()
{
	return variable;
}

CBlock* CBlockAssertion_isDefaultAssign::get_definition()
{
	return value;
}

CBlock* CBlockAssertion_isConstantAssign::get_obj()
{
	return variable;
}

CBlock* CBlockAssertion_isConstantAssign::get_definition()
{
	return value;
}

CBlock* CBlockAssertion_isForbiddenAssign::get_obj()
{
	return value;
}

CBlock* CBlockAssertion_isForbiddenAssign::get_definition()
{
	return variable;
}

UBlock CBlockAssertion_isDirectAssign::get_obj()
{
	return variable;
}

UBlock CBlockAssertion_isDirectAssign::get_definition()
{
	return value;
}

CBlock* CBlockAssertion_isNotDirectAssign::get_obj()
{
	return variable;
}

CBlock* CBlockAssertion_isNotDirectAssign::get_definition()
{
	return value;
}

