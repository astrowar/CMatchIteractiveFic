// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "Parser/Parser.hpp"
#include "CBlockComposition.hpp"
#include "sharedCast.hpp"
 
using namespace CBlocking;
using namespace Interpreter;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;

HBlockKindAction NSParser::ParseAssertionSecondary::parse_AssertionAction_secondPart(CParser * p,  HTerm  term)
{
	
 

	{
		// action applying to [two things]
		// action applying to one visible thing
		// Advancing is an action applying to nothing

		//std::cout << term->repr() << std::endl;
		CPredSequence predList = undefinedArticle() <<pLiteral("action")	<<pLiteral("applying")  <<pLiteral("to")   <<pAny("ApplyRemainder");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockActionApply applyTO = ParseAssertion::parse_AssertionAction_ApplyngTo(p,res.matchs["ApplyRemainder"]);
		 	return std::make_shared<CBlockKindAction>( applyTO);

		}
	}

 
	{
		// and action applying to [one visible thing and requiring light]

		//std::cout << term->repr() << std::endl;
		CPredSequence predList = undefinedArticle()	<<pLiteral("action");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
 
			HBlockActionApply applyTO = std::make_shared<CBlockActionApply>(nullptr, nullptr);
			return std::make_shared<CBlockKindAction>(  applyTO);

		}
	}

	return nullptr;
}

 


HBlock NSParser::ParseAssertion::parse_ActionCompositionName(CParser * p, bool two_noums ,HTerm term)
{
	string s_it = " ";
	//if (two_noums) s_it = " it ";
	{

		CPredSequence predList_a = pWord("ActionName") << pPreposition("pred") << pOr("pred_aux", pLiteral("to"), pLiteral("of"));
		 
		{
			MatchResult res = CMatch(term, predList_a);
			if (res.result == Equals)
			{
				auto sActionName = CtoString(res.matchs["ActionName"]);
				auto sPred = CtoString(res.matchs["pred"]);
				auto sPredAux = CtoString(res.matchs["pred_aux"]);				
				HBlock _naction = std::make_shared<CBlockNoumCompose>(std::vector<HBlockNoum>{std::make_shared<CBlockNoumStr>(sActionName), std::make_shared<CBlockNoumStr>(sPred), std::make_shared<CBlockNoumStr>(sPredAux)});
				return _naction;
			}
		}
	}

	{
		 CPredSequence predList_b = pWord("ActionName") << pPreposition("pred");
		 
		{
			 

			MatchResult res = CMatch(term, predList_b);
			if (res.result == Equals)
			{
				auto sActionName = CtoString(res.matchs["ActionName"]);
				auto sPred = CtoString(res.matchs["pred"]);
				HBlock _naction = std::make_shared<CBlockNoumCompose>(std::vector<HBlockNoum>{ std::make_shared<CBlockNoumStr>(sActionName), std::make_shared<CBlockNoumStr>(sPred) });

				//HBlock _naction = std::make_shared<CBlockNoumStr>(sActionName + s_it + sPred  );
				return _naction;
			}
		}
	}


	{
		  CPredSequence predList_c( pWord("ActionName"));
		 
		{
			MatchResult res = CMatch(term, predList_c);
			if (res.result == Equals)
			{
				auto sActionName = CtoString(res.matchs["ActionName"]); 
				 
				HBlock _naction = std::make_shared<CBlockNoumStr>(sActionName );
				return _naction;
			}
		}
	}

	auto s = term->repr();
	printf("%s \n", s.c_str());
	return nullptr;
}

 
HBlock NSParser::ParseAssertion::parse_AssertionRulebook(CParser * p, std::vector<HTerm> term)
{

	auto an_  =  pOr("article", pLiteral("a"), pLiteral("an"));
	auto an_rulebook = pOr("ruleDefinition", pList("rulebookDefinition", { an_ , pLiteral("rulebook") }), pLiteral("rulebook"));


	{
		CPredSequence predList =  pAny("ruleBookName") << verb_IS() << pAny("kind") << pLiteral("based") <<  pLiteral("rulebook") <<  pLiteral("producing") << pAny("kind2");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockNoum rulebookName = Expression::parser_noum_expression(p, res.matchs["ruleBookName"]);
			if (rulebookName != nullptr)
			{
				HBlockKind dkind = Expression::parser_kind_specification(p, res.matchs["kind"]);
				if (dkind != nullptr)
				{
					HBlockKind dkind2 = Expression::parser_kind_specification(p, res.matchs["kind2"]);
					if (dkind2 != nullptr)
					{
						auto ruleKind = std::make_shared<CBlockCompositionRulebook>(dkind, dkind2);
						if (ruleKind != nullptr)
						{
							p->ruleList.push_back(res.matchs["ruleBookName"]);
							return std::make_shared<CBlockAssertion_isDirectAssign>(rulebookName, ruleKind);
						}
					}
				}
			}
		}
	}


	{  
  		 
		CPredSequence predList = pOptional(mk_HPredLiteral_OR("det", { "The","the" })) <<  pAny("ruleBookName") << pOptional( pLiteral("rules")) << verb_IS() << an_rulebook <<   pLiteral("producing") << pAny("kind2") ;

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockNoum rulebookName = Expression::parser_noum_expression(p, res.matchs["ruleBookName"]);
			if (rulebookName != nullptr)
			{				 
				{
					HBlockKind dkind2 = Expression::parser_kind_specification(p, res.matchs["kind2"]);
					if (dkind2 != nullptr)
					{
						auto ruleKind = std::make_shared<CBlockCompositionRulebook>(nullptr, dkind2);
						if (ruleKind != nullptr)
						{
							p->ruleList.push_back(res.matchs["ruleBookName"]);
							return std::make_shared<CBlockAssertion_isDirectAssign>(rulebookName, ruleKind);
						}
					}
				}
			}
		}
	}




	{
		CPredSequence predList = pAny("ruleBookName") << verb_IS() << pAny("kind") << pLiteral("based") << an_rulebook;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockNoum rulebookName = Expression::parser_noum_expression(p, res.matchs["ruleBookName"]);
			if (rulebookName != nullptr)
			{				
				HBlockKind dkind = Expression::parser_kind_specification(p, res.matchs["kind"]);
				if (dkind != nullptr)
				{
					auto ruleKind = std::make_shared<CBlockCompositionRulebook>(dkind,nullptr);
					if (ruleKind != nullptr)
					{
						p->ruleList.push_back(res.matchs["ruleBookName"]);
						return std::make_shared<CBlockAssertion_isDirectAssign>(rulebookName, ruleKind);
					}
				}
			}
		}
	}

	{
		CPredSequence predList = pAny("ruleBookName") << verb_IS()  << an_rulebook;
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockNoum rulebookName = Expression::parser_noum_expression(p, res.matchs["ruleBookName"]);
			if (rulebookName != nullptr)
			{				 
				{
					auto ruleKind = std::make_shared<CBlockCompositionRulebook>(nullptr, nullptr);
					if (ruleKind != nullptr)
					{
						p->ruleList.push_back(res.matchs["ruleBookName"]);
						return std::make_shared<CBlockAssertion_isDirectAssign>(rulebookName, ruleKind);
					}
				}
			}
		}
	}


	return nullptr;
}

HBlock NSParser::ParseAssertion::parse_AssertionAction(CParser * p, std::vector<HTerm> term) 
{
	 
	{
		// and action applying to [one visible thing and requiring light]

		//std::cout << get_repr(term) << std::endl;
		
		CPredSequence predList = p->lang->parse_AssertionAction("ActionName" ,"ApplyRemainder"  ); 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{	 
			HBlockActionApply applyTO = ParseAssertion::parse_AssertionAction_ApplyngTo(p, res.matchs["ApplyRemainder"]);			
			if (applyTO != nullptr)
			{
				bool two_noums = (applyTO->noum2 != nullptr);			 
				auto _naction = parse_ActionCompositionName(p, two_noums , res.matchs["ActionName"]);
				if (_naction != nullptr)
				{
					return std::make_shared<CBlockAssertion_isDirectAssign>(_naction, applyTO);
				}
			} 
		}
	}

	return nullptr;

}



 
HBlock NSParser::ParseAssertion::parse_AssertionIsLocalValue(CParser * p, std::vector<HTerm>& term)
{
	// is a default ??
	CPredSequence predList =pLiteral("let")<< pAny("VarName")<< pLiteral("be")<< pAny("VarValue");

	MatchResult res = CMatch(term, predList);
	
	if (res.result == Equals)
	{ 
		auto varName = Expression::parser_expression(p, res.matchs["VarName"]);
		if (HBlockNoum varNameNoum = DynamicCasting::asHBlockNoum(varName))
		{
			 auto varValue = Expression::parser_expression(p, res.matchs["VarValue"]);
			return std::make_shared<CBlockAssertion_isLocalVariable>(varNameNoum, varValue);
		}
	}


return nullptr;

}


HBlock NSParser::ParseAssertion::parse_AssertionIsVariable(CParser * p, std::vector<HTerm>& term) {
	 


	{
		// is a kind definition ??
		auto L_a_an_kind = pList("kindpart", { verb_IS(), undefinedArticle() });
		auto L_are_kinds = pList("kindpart", { verb_IS() });

		CPredSequence predList = 
			   pAny("VariableNoum")
			<< (pOr("kindpart", L_a_an_kind, L_are_kinds))
			<< pAny("KindBase")
			<< (pList("variable", { pLiteral("that"), pLiteral("varies") }));

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlock noumVariable = Expression::parser_expression(p,res.matchs["VariableNoum"]);
			HBlock baseKind = Expression::parser_kind(p,res.matchs["KindBase"]);
			return std::make_shared<CBlockAssertion_isVariable>(noumVariable, baseKind);
		}
	}
	return nullptr;

}

HBlockKindOfName NSParser::ParseAssertion::parse_KindOf(CParser * p, HTerm  term)
{
	{
		auto a_1 = pList("kindDef", { undefinedArticle(), pLiteral("kind"), pLiteral("of") });;
		auto a_2 = pList("kindDef", { pLiteral("kind"), pLiteral("of") });
		auto a_3 = pList("kindDef", { pLiteral("kinds"), pLiteral("of") });
		CPredSequence predList = (pOr("kindBase_l", a_1, a_2, a_3))	<<pAny("kindBase");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{	 
			//auto nn =   CtoString(res.matchs["kindBase"]->removeArticle());	

			auto nn  =Expression::parser_noum_expression(p,res.matchs["kindBase"] );
			return std::make_shared<CBlockKindOfName>(nn);
		}
	}

	{
		CPredSequence predList = (pList("kindDef", { undefinedArticle(), pLiteral("kind") }));
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			logError("undefined Kind");
			//return std::make_shared<CBlockKindOfName>(""); // no Base

		}
	} 
	return nullptr; 
}
 


 
 

HBlockKind   NSParser::Expression::parse_CompositionOf(CParser * p, HTerm  term)
{
  
	{
		CPredSequence predList = pLiteral("phrase")	<<pAny("kindBase")<<pLiteral("->")	<<pAny("kindDst");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockKind nkind =  parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				HBlockKind dkind = Expression::parser_kind_specification(p, res.matchs["kindDst"]);
				if (dkind != nullptr)
				{
					return  std::make_shared<CBlockCompositionPhrase>(nkind, dkind);
				}
			} 
		}
	}



	{
		CPredSequence predList = pLiteral("relation") <<pLiteral("of")  <<pAny("kindBase") <<pLiteral("to")  <<pAny("kindDst");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto nkind = parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				auto dkind = Expression::parser_kind_specification(p, res.matchs["kindDst"]);
				if (dkind != nullptr)
				{
					return  std::make_shared<CBlockCompositionRelation>(  nkind, dkind);
				}
			}
		}
	}

	 



	{
		CPredSequence predList = pLiteral("list") <<pLiteral("of")   <<pAny("kindBase");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockKind nkind = parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				return  std::make_shared<CBlockCompositionList>(  nkind);
			}
		}
	}

	 
	return nullptr;
}



HBlock NSParser::ParseAssertion::parse_AssertionIsCompositionOf(CParser * p, std::vector<HTerm>& term) {
	{
		// is a default ??
		CPredSequence predList = pAny("Noum") 	<<verb_IS()	<<pAny("CompDef");

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			auto value = Expression::parse_CompositionOf(p, res.matchs["CompDef"]);
			if (value == nullptr) return nullptr;
			HBlock noum = Expression::parser_assertionTarger(p, res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
		}
	}
	return nullptr;
}


HBlock NSParser::ParseAssertion::parse_AssertionIsKindOf(CParser * p, std::vector<HTerm>& term) {
	{
		// is a default ??
		CPredSequence predList = pAny("Noum") 	<<verb_IS()   <<pAny("KindDef");

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlock value = parse_KindOf(p,res.matchs["KindDef"]);
			if (value == nullptr) return nullptr;
			HBlock target = Expression::parser_assertionTarger(p,res.matchs["Noum"]);

			if (HBlockMatch m = DynamicCasting::asHBlockMatch(target))
			{
				// converte para uma lista de noums ?
				 target = Expression::parser_noumList(p, res.matchs["Noum"]);
			}

			if (target == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isDirectAssign>(target, value);
		}
	}
	return nullptr;
}

HBlock NSParser::ParseAssertion::parse_AssertionValuesOf(CParser * p, std::vector<HTerm>& term) {

	// The colors are blue, green, yellow, and red.
	// The textures are rough, stubbly and smooth.
	// Price is a kind of value.  $1.99 specifies a price.
	{

	}


	// $1.99 specifies a price.
	{
		
		auto L_single = pList("spc", {pLiteral("specifies"), undefinedArticle()});
		auto L_plural = pList("spc", {pLiteral("specifies")});

		CPredSequence predList = pAny("valueName")     <<(pOr("spc_part", L_single, L_plural)) <<pAny("valueKind");
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			//KindValue must exist 

			HBlock valueName = Expression::parser_expression(p,res.matchs["valueName"]);
			HBlock valueKind = Expression::parser_kind(p,res.matchs["valueKind"]);
			return std::make_shared<CBlockAssertion_isNamedValueOf>(valueName, valueKind);


		}
	}
	return nullptr;
}


HBlock NSParser::ParseAssertion::parse_AssertionDefaultAssign(CParser *p, std::vector<HTerm>& term) {

	{
		// is a default ??
		CPredSequence predList = pAny("Noum")       <<verb_IS() <<pLiteral("usually") <<pAny("Value");

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isDefaultAssign>(noum, value);
		}
	}

	{
		// is a always ??
		CPredSequence predList = pAny("Noum") <<verb_IS() <<pLiteral("always") <<pAny("Value");

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isConstantAssign>(noum, value);
		}
	}

	{
		// is never  ??
		CPredSequence predList = pAny("Noum")       <<verb_IS() <<pLiteral("never") <<pAny("Value");

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isForbiddenAssign>(noum, value);
		}
	}

	return nullptr;

}



HBlockAssertion_is NSParser::ParseAssertion::parse_AssertionDirectAssign(CParser * p, std::vector<HTerm>& term) {
	{
		// is a kind definition ??
		  CPredSequence predList = 	 pAny("Noum")	<<verb_IS_NOT()	  <<pAny("Value");
		

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
			if (noum == nullptr) return nullptr;
			HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
			if (value == nullptr) return nullptr;
			return std::make_shared<CBlockAssertion_isNotDirectAssign>(noum, value);
		}
	}

 


	{
		// is a kind definition ??
		 
		CPredSequence predList  = pAny("Noum")	<<verb_IS()  <<pAny("Value"); 
		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {

			HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
			if (value == nullptr) return nullptr;

			if (HBlockKindAction action = DynamicCasting::asHBlockKindAction(value)) 
			{
				auto sterm = expandBract(res.matchs["Noum"]);
				//HBlock _naction = std::make_shared<CBlockActionNamed>( (sterm->repr()));
				HBlock _naction = Expression::parser_noum_expression(p,sterm);

				HPred actionMatch = convert_to_predicate(sterm.get());
				//	std::cout << "found " << actionMatch->repr()  << std::endl;
				p->actionPredList->blist.push_back(actionMatch);

				return std::make_shared<CBlockAssertion_isDirectAssign>(_naction, value);

			} else {
				HBlock noum = Expression::parser_assertionTarger(p,res.matchs["Noum"]);
				if (noum == nullptr) return nullptr;
				return std::make_shared<CBlockAssertion_isDirectAssign>(noum, value);
			}

		}
	}

	return nullptr;

}




HBlock NSParser::ParseAssertion::parser_Declaration_Assertion(CParser * p, std::vector<HTerm>& lst)
{

	HBlock verb_Assign = parse_AssertionVerb(p,lst);
	if (verb_Assign != nullptr) {
		return verb_Assign;
	}

	HBlock action_Assign = parse_AssertionAction(p,lst);
	if (action_Assign != nullptr) {
		return action_Assign;
	}

	HBlock rulebook_Assign = parse_AssertionRulebook(p, lst);
	if (rulebook_Assign != nullptr) {
		return rulebook_Assign;
	}

	HBlock assert_variable = parse_AssertionIsVariable(p,lst);
	if (assert_variable != nullptr) {
		return assert_variable;
	}

	HBlock assert_local_value = parse_AssertionIsLocalValue(p, lst);
	if (assert_local_value != nullptr) {
		return assert_local_value;
	}

	HBlock assert_compostionOf = parse_AssertionIsCompositionOf(p, lst);
	if (assert_compostionOf != nullptr) {
		return assert_compostionOf;
	}

	HBlock assert_kindof = parse_AssertionIsKindOf(p,lst);
	if (assert_kindof != nullptr) {
		return assert_kindof;
	}

	HBlock assert_values = parse_AssertionValuesOf(p,lst);
	if (assert_values != nullptr) {
		return assert_values;
	}

	HBlock assert_DefaultAssign = parse_AssertionDefaultAssign(p,lst);
	if (assert_DefaultAssign != nullptr) {
		return assert_DefaultAssign;
	}

 

	HBlock assert_Assign = parse_AssertionDirectAssign(p,lst);
	if (assert_Assign != nullptr) {
		return assert_Assign;
	}

	return nullptr;

}
