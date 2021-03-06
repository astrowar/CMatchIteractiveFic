// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "Parser/Parser.hpp"
// PVS
// PVQ


 

#include <algorithm>


#include "CBlockMatch.hpp"
 
#include "CblockAssertion.hpp"
#include "CBlockUndestand.hpp"
#include "CBlockCommand.hpp"
#include "sharedCast.hpp"
#include "CBlockComposition.hpp"
#include <list>

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;



NSParser::CParser::CParser( LanguageModule *_lang ) {
    
   this->lang = _lang;
   this->phase_id = 0;

	blank_line = std::make_shared<CBlockNothing>("Blank Line");
    {
        std::list<HPred> alist;
        verbList = std::make_shared<CPredBooleanOr>("verbList", alist);
        //verbList->blist.push_back(pLiteral("contains"));
    }

    {
        std::list<HPred> alist;
        actionPredList = std::make_shared<CPredBooleanOr>("actionList", alist);
       // actionPredList->blist.push_back(pLiteral("getting"));
    }

	{
		
		verbList->blist.push_back(pList({ pLiteral("exactly"),  pLiteral("matches") }));
		//verbList->blist.push_back(pLiteral("relates"));
		verbList->blist.push_back(pLiteral("matches"));
		
		
	}

	{
		HBlockNoum nVerb = std::make_shared<CBlockNoumStr>("matches");
		HBlockNoum nPred = std::make_shared<CBlockNoumStr>("in");
		//HBlockMatchNamed marg1 = std::make_shared<CBlockMatchNamed>("RGX", std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("text")));
		//HBlockMatchNamed marg2 = std::make_shared<CBlockMatchNamed>("TXT", std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("text")));		


		HBlockMatch marg1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumStr>("matches"));
		HBlockMatch marg2 = std::make_shared<CBlockMatchNamed>("A1", std::make_shared<CBlockMatchAny>());
		HBlockMatch marg3 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumStr>("in"));
		HBlockMatch marg4 = std::make_shared<CBlockMatchNamed>("A2", std::make_shared<CBlockMatchAny>());		

		HBlockMatchList mPhaseEntry = std::make_shared<CBlockMatchList>( std::list<HBlockMatch>({ marg1 ,marg2 ,marg3 ,marg4 }));
		
		HBlockMatchNamed xarg1 = std::make_shared<CBlockMatchNamed>("RGX", std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("text")));
		HBlockMatchNamed xarg2 = std::make_shared<CBlockMatchNamed>("TXT", std::make_shared<CBlockMatchKind>(std::make_shared<CBlockKindValue>("text")));

		HBlockMatchList mPhaseArguments = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ xarg1 ,xarg2   }));

		HBlockPhraseHeader nheader = std::make_shared<CBlockPhraseHeader>(std::make_shared<CBlockNoumStr>("matches_in") , mPhaseEntry, mPhaseArguments);
		this->phrases.push_back(nheader);
	}



    {
        //std::list<HPred> alist;
        //actionDinamicDispatch = std::make_shared<CPredBooleanOr>("actionList", alist);
        //actionDinamicDispatch->blist.push_back(pLiteral("getting"));
    }
}

 

NSParser::CParser::~CParser()
{
}


// 
//HBlock NSParser::CParser::get_Noum(string named) const
//{
//	auto kv =  std::find_if(nregisters.begin(), nregisters.end(), [&](const NoumDefinition &a) {return   a.noum == named; });
// 
//	if (kv == nregisters.end()) return nullptr;
//	return kv->definition ;
//}

void NSParser::CParser::set_Noum(NoumDefinition ndef) {
    nregisters.push_back(ndef);
}

void NSParser::CParser::set_Noum(NoumDefinitions ndef) {
    nregisters.insert(nregisters.end(), ndef.begin(), ndef.end());
}



 


std::vector<HTerm> expandTerm( HTerm term)
{
    if (CList* clist =  asCList( term.get() ) )
    {
          return clist->asVector();
    }
    return {term};
}

HBlock NSParser::ParseAction::sys_say_action(CParser * p, std::vector<HTerm>&  term)
{
	CPredSequence predList = pLiteral("say")<<pAny("Body");

	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		//auto nterms = expandTerm(res.matchs["Body"]);
		//HBlock value = Expression::parser_expression_lst(p,nterms);	
		std::string ss =res.matchs["Body"]->repr();
		 

		HBlock value = Expression::parser_expression(p, res.matchs["Body"]);
		 
		HBlockActionNamed say_Action = std::make_shared<CBlockActionNamed>("say_text");
		return std::make_shared<CBlockActionCallNamed>(say_Action, value, nullptr);
	}
	return nullptr;
}

 

//parse a segunda parte do iterator
HBlockAssertion_is NSParser::ParseAssertion::parse_Loop_AssertionVerb(CParser * p, HTerm&  term , NoumLocation nlocation  )
{
 
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<verb_IS_NOT()	<<p->verbList <<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
		 
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
				}
			}
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<pLiteral("not")	<<p->verbList <<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			 
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
				}
			}

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<verb_IS()	<<p->verbList <<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			
			{
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsVerb>(vrepr, n1, n2);
				}
			}

		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("N1")	<<p->verbList	<<pAny("N2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			 
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				
				HBlock n2 = Expression::parser_expression(p,res.matchs["N2"]);
				if (n2 != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));
					return std::make_shared<CBlockIsVerb>(vrepr, n1, n2);
				}
			}

		}

	}



	{
		// is a kind definition ??
		  CPredSequence predList = pAny("N1")	<<verb_IS_NOT() <<pAny("Value");
		 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{
				 
				 
					HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
					if (value != nullptr)
					{
						if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
						return std::make_shared<CBlockAssertion_isNotDirectAssign>(n1, value);
					}
				 
			}
		}
	}

	{
		// is a kind definition ??
		  CPredSequence predList = pAny("N1")	<<verb_IS()	<<pAny("Value");
		 

		MatchResult res = CMatch(term, predList);

		if (res.result == Equals) {
			HBlock n1 = Expression::parser_expression(p,res.matchs["N1"]);
			if (n1 != nullptr)
			{ 
				HBlock value = Expression::parser_expression(p,res.matchs["Value"]);
				if (value != nullptr)
				{
					if (nlocation == FirstNoum) n1 = std::make_shared<CBlockEvery>(n1);
					return std::make_shared<CBlockAssertion_isDirectAssign>(n1, value);
				}

			}
		}
	}


	 

	return nullptr;


}

HBlock NSParser::ParseAssertion::sys_now_loop(CParser * p, std::vector<HTerm>&  term)
{
	
	// now every room is lighted
	// now every lamp is blazing	
	// now every good woman is in the Salon
	// now every thing carried by the player is in the impound


	// now the player carries every thing which is in the tomb
	// now the table supports every stripper who is in New Jersey
	// now Wilfred admires every woman

	  CPredSequence predList = pLiteral("now")	<<pLiteral("every")	<<pAny("Assertion");
		//<<verb_IS();
		//<<pAny("Seletor_B");
	 
	MatchResult res = CMatch(term, predList);
	if (res.result == Equals)
	{
		//auto nterms = expandTerm(res.matchs["Assertion"]);
		//parse_AssertionVerb
		//parse_AssertionDirectAssign

		{
			HBlockAssertion_is now_verb = parse_Loop_AssertionVerb(p,res.matchs["Assertion"],FirstNoum);
			if (now_verb != nullptr)
			{
			 
				return std::make_shared<CBlockNow >(now_verb);
			}
		}


		 
	}

	return nullptr;
}

CBlocking::HBlock NSParser::ParseAssertion::parse_decide_on(CParser * p, std::vector<std::shared_ptr<NSTerm::CTerm>> term)
{
	{
		CPredSequence predList = pLiteral("decide") << pLiteral("on") << pAny("ExpressionBody");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			logMessage((res.matchs["ExpressionBody"]->repr()));
			HBlock body = Expression::parser_expression(p, res.matchs["ExpressionBody"]);
			return std::make_shared<CBlockToDecideOn>(body);
		}
	}
	return nullptr;
}

HBlock NSParser::ParseAssertion::sys_now_action(CParser * p, std::vector<HTerm>&  term)
{

	if ( auto nloop = sys_now_loop(p,term ))
	{
		return nloop;
	}

    {

		    // now every room is lighted
			// now every lamp is blazing
			// now Wilfred admires every woman
			// now every good woman is in the Salon
			// now everything carried by the player is in the impound
			// now the player carries every thing which is in the tomb
			// now the table supports every stripper who is in New Jersey





        CPredSequence predList = pLiteral("now") <<pAny("Assertion");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto nterms = expandTerm(res.matchs["Assertion"]);
            //parse_AssertionVerb
            //parse_AssertionDirectAssign

            {
                HBlockAssertion_is now_verb = parse_AssertionVerb(p,nterms);
                if (now_verb != nullptr)
                {
                    return std::make_shared<CBlockNow >(now_verb);
                }
            }


            {
                HBlockAssertion_is now_is = parse_AssertionDirectAssign(p,nterms);
                if (now_is != nullptr)
                {
                    return std::make_shared<CBlockNow >(now_is);
                }
            }
        }
    }
    return nullptr;
}



//Processa os smtm que sao do sistema
HBlock NSParser::ParseAssertion::STMT_system_call(CParser * p, std::vector<HTerm>& term)
{
	auto d_say = (ParseAction::sys_say_action(p,term));
	if (d_say != nullptr) return d_say;


    auto d_now = (sys_now_action(p,term));
    if (d_now != nullptr) return d_now;

    return nullptr;
}

 



//Uma das rotinas mais importantes. Ela altera  o proprio parser
HBlock NSParser::ParseAssertion::STMT_understand_Assertion(CParser * p, std::vector<HTerm>&  term) {

    auto d_action = (DynamicDispatch::DynamicDispatch_action(p,term));
    if (d_action != nullptr) return d_action;
    

    auto p_action = DynamicDispatch::STMT_understand_Action_Assertion_static(p,term);
    if (p_action != nullptr) return p_action;

    return nullptr;
}


HBlock NSParser::ParseAssertion::parse_removeArticle(CParser * p, std::vector<HTerm>& term) {
    if (term.size() > 1) {

        if (pLiteral("the")->match(term.front()) == Equals)
		{
            auto gtail = get_tail(term);
            return Expression::parser_expression_lst(p,gtail);
        }
    }
    return nullptr;
}

 

HBlockNoum NSParser::ParseAssertion::parse_noum_single(CParser * p, std::vector<HTerm>& term)
{

	if (term.size() == 1)
	{
		if (CList *vlist = asCList(term[0].get()))
		{
			std::vector<HTerm> v = vlist->asVector();
			return parse_noum_single(p, v);
		}

		return Expression::parser_noum_expression(p, term[0]);
	}
	std::vector<HBlockNoum > nvector;
	for (auto t : term)
	{
		auto nterm = Expression::parser_noum_expression(p, t);
		if (nterm == nullptr) return nullptr;
		nvector.push_back(nterm);
	}
	 
	return std::make_shared<CBlockNoumCompose>(nvector);

	 
}

HBlockNoum NSParser::ParseAssertion::parse_noum(CParser * p, HTerm  term)
{ 
	std::vector<HTerm> vterm = { term };
	return parse_noumVec(p, vterm);
}

HBlockNoum NSParser::ParseAssertion::parse_noumVec(CParser * p, std::vector<HTerm>& term)
{
	if (term.size() == 1)
	{
		if (CList *vlist = asCList(term[0].get()))
		{
			std::vector<HTerm> v = vlist->asVector();
			return parse_noumVec(p, v);
		} 
	}

	{
		CPredSequence predList_det = mk_HPredLiteral_OR("det", { "A","a","An","an", "The","the" }) ;
		MatchResult res_det = CMatch(term, predList_det);
		if (res_det.result == Equals)
		{
			return nullptr;
		}
	}

	// anula se tiver uma palavra chave reservada	
	CPredSequence predList_det = mk_HPredLiteral_OR("det", {"A","a","An","an", "The","the" }) << pAny("Noum");
	MatchResult res_det = CMatch(term, predList_det);
	if (res_det.result == Equals)
	{
		HTerm rdet = res_det.matchs["det"];
		HTerm rnoum = res_det.matchs["Noum"];
		std::vector<HTerm> term_p = { rnoum };		 
		HBlockNoum noum_next=   parse_noum_single(p, term_p);
		if (noum_next != nullptr)
		{ 
			return  std::make_shared<CBlockNoumStrDet>(rdet->repr(), noum_next);
		}
	}

	{
		HBlockNoum nn = parse_noum_single(p, term);
		if (nn != nullptr) return nn;
		
	}

	return nullptr;
}

HBlockAssertion_isInstanceOf NSParser::CParser::parseAssertion_isInstanceOf(std::vector<HTerm>& term) {
    //Injstance is Alwares derivadefrom a Kind
    {
        // is a kind definition ??
        auto L_a_an_kind = pList("kindpart", {verb_IS(), undefinedArticle()});
        auto L_are_kinds = pList("kindpart", {verb_IS()});

        CPredSequence predList = pAny("Noum") << L_a_an_kind <<pAny("KindBase");

        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
      
        }
    }
    return nullptr;

}




HBlock NSParser::ParseAssertion::parseAssertionFirstTerm_Compose(CParser *p, HTerm term) {
    HBlockList c_list = std::make_shared<CBlockList>(std::list<HBlock>());
    c_list = ParseList::parseAssertionFirstTerm_COMMA_AND(p,term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        swap(rt, c_list->lista.front());
        //delete c_list;
        return rt;
    }
    return c_list;
}


HBlock NSParser::ParseAssertion::parseAssertionFirstTerm(CParser *p, HTerm term) {
    return parseAssertionFirstTerm_Compose(p,term);
}


HBlock NSParser::ParseAssertion::parseAssertionEnumSecondTerm(CParser *p, HTerm term) {
    HBlockList c_list = std::make_shared<CBlockList>(std::list<HBlock>());
    c_list = ParseList::parseAssertionFirstTerm_COMMA_OR(p,term, c_list);
    if (c_list->lista.size() == 1) {
        HBlock rt;
        swap(rt, c_list->lista.front());
        //delete c_list;
        return rt;
    }
    return c_list;
}

HBlock NSParser::ParseAssertion::STMT_Decide_Assertion(CParser * p, std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo *err)
{
    HBlock assert_decide = ParseDecide::parseAssertion_isDecide(p,lst,inner,err);
    if (assert_decide != nullptr) {
        return assert_decide;
    }

 

    return nullptr;

}

 
HBlock NSParser::ParseAssertion::parse_CompositionKindArgument(CParser * p, std::vector<HTerm>& term)
{
	 

	{
		CPredSequence predList = pOr("_", pList("_", { pLiteral("an") , pLiteral("action") }), pLiteral("action")) << pLiteral("applying") << pLiteral("to") << pAny("obj_d");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			HBlockActionApply applyTO = ParseAssertion::parse_AssertionAction_ApplyngTo(p, res.matchs["obj_d"]);
			if (applyTO != nullptr)
			{
				return applyTO;
			} 
			 
		}
	}
	return nullptr;
}

 
HBlock NSParser::ParseAssertion::parse_RelationArgument(CParser * p, std::vector<HTerm>& term)
{
	return nullptr;
	{
		CPredSequence predList = pAny("obj_s")<<pLiteral("to")	<<pAny("obj_d");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock a = Expression::parser_expression(p, res.matchs["obj_s"]);
			if (a != nullptr) {
				HBlock b = Expression::parser_expression(p, res.matchs["obj_d"]);
				if (b != nullptr)
				{
					return std::make_shared<CBlockRelationArguments>(a, b);
				}
			}
		}
	}
	return nullptr;


}



HBlock  NSParser::ParseAssertion::parse_PropertyOf(CParser * p, std::vector<HTerm>& term) {

	{
		CPredSequence predList = mk_HPredLiteral_OR("article", { "a", "an" }) <<pLiteral("list")<<pLiteral("of")<<pAny("kindBase");
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockKind nkind = Expression::parser_kind_specification(p, res.matchs["kindBase"]);
			if (nkind != nullptr)
			{
				return  std::make_shared<CBlockCompositionList>(nkind);
			}
		}
	}

	{
			CPredSequence predList = pLiteral("list")<<pLiteral("of")	<<pAny("kindBase");

			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockKind nkind = Expression::parser_kind_specification(p, res.matchs["kindBase"]);
				if (nkind != nullptr)
				{
					return  std::make_shared<CBlockCompositionList>(  nkind);
				}
			}
	}


	{

        CPredSequence predList = pAny("property") <<pLiteral("of") <<pAny("obj");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
            HBlock a = Expression::parser_expression(p,res.matchs["property"]);
            if (a != nullptr) {
                HBlock b = Expression::parser_expression(p,res.matchs["obj"]);
                if (b != nullptr) {
                     return std::make_shared<CBlockProperty>(a, b);
                }
            }
        }
    }




  
    return nullptr;
}


HBlockEnums NSParser::ParseAssertion::parseAssertion_EnumTerms(CParser * p, HTerm enumList) {

    HBlockList elist = std::make_shared<CBlockList>(std::list<HBlock>());
    elist = ParseList::parseAssertionFirstTerm_COMMA_OR(p,enumList, elist);
    if (elist->lista.empty()) {
        return nullptr;
    }

    std::vector<HBlockNoum> nlist;
    std::for_each(elist->lista.begin(), elist->lista.end(),
                  [&nlist](HBlock c) { nlist.push_back(DynamicCasting::asHBlockNoum(c)); });
    return std::make_shared<CBlockEnums>(nlist);

}


HBlock NSParser::ParseAssertion::STMT_canBe_Assertion(CParser * p, std::vector<HTerm>& lst) {
    
	CPredSequence predList =pAny("Target") <<pLiteral("can") <<pLiteral("be") <<pAny("EnumValues");

    MatchResult res = CMatch(lst, predList);

    if (res.result != Equals) return nullptr;

    HBlockEnums definitionSecond = parseAssertion_EnumTerms(p,res.matchs["EnumValues"]);
    if (definitionSecond == nullptr) {
        return nullptr;
    }

    

    HBlock defintionFirst_Noum = Expression::parser_assertionTarger(p,res.matchs["Target"]);
    if (defintionFirst_Noum != nullptr) {
        return std::make_shared<CBlockAssertion_canBe>(defintionFirst_Noum, definitionSecond);
    }

    return nullptr;
}

HBlockInstanceVariable NSParser::ParseAssertion::CProperty_called(CParser * p, HTerm term) {
    {
        // the torch has a brightness called brightnessLevel ;
        CPredSequence predList = pAny("kindName") <<pLiteral("called") <<pAny("propName");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {

			//auto propName = CtoString(expandBract(res.matchs["propName"]));

			HBlockNoum a = Expression::parser_noum_expression(p, res.matchs["kindName"]);
			HBlockNoum b = Expression::parser_noum_expression(p, res.matchs["propName"]);
            

            return std::make_shared<CBlockInstanceVariable>(a, b);
        }

    }

    {
        // the torch has a brightness   ;  -> called brightness
		HBlockNoum a = Expression::parser_noum_expression(p, term);
		HBlockNoum b = Expression::parser_noum_expression(p, term); 
        return std::make_shared<CBlockInstanceVariable>(a, b);
    }

}


HBlock NSParser::ParseAssertion::STMT_hasAn_Assertion(CParser * p, std::vector<HTerm>& lst) {
	CPredSequence predList = pAny("Target") << pLiteral("has") << undefinedArticle() << pAny("KindAndName");
	MatchResult res = CMatch(lst, predList);

	if (res.result == Equals)
	{

		HBlockInstanceVariable definitionProperty_kindAndName = CProperty_called(p, res.matchs["KindAndName"]);
		if (definitionProperty_kindAndName == nullptr) {
			return nullptr;
		}

		 
		HBlock defintionFirst_KindOrInstance = Expression::parser_kind_or_instance(p, res.matchs["Target"]);

		return std::make_shared<CBlockAssertion_InstanceVariable>(defintionFirst_KindOrInstance,
			definitionProperty_kindAndName);
	}
	return nullptr;
}



HBlock NSParser::Statement::parser_stmt(CParser * p, HTerm term, HGroupLines inner, ErrorInfo *err) {
    if (CList *vlist = asCList(term.get())) {
        auto v = vlist->asVector();
        auto r = parser_stmt_inner(p,v,inner,err);
        /*if (r == nullptr)
            std::cout << term->repr() << std::endl;*/

        return r;
    }
	return Expression::parser_noum_expression(p, term);
     
}


 







HBlock NSParser::Statement::parser_stmt_str(CParser * p, string str, HGroupLines inner, ErrorInfo *err) {
 //   str = decompose_bracket(str, "(");
 //   str = decompose_bracket(str, ")");
 //   str = decompose_bracket(str, ",");
	//str = decompose_bracket(str, "\"");
    std::vector<HTerm> lst = decompose_syntax(str);
    return Statement::parser_stmt_inner(p,lst,inner,err);
}


HBlock NSParser::Statement::Parser_Stmt(CParser * p, string str, bool dump )
{
	ErrorInfo err;
		return Statement::parser_stmt(p,str, dump, &err);
}

 


HBlock NSParser::Expression::Parser_Expression(CParser * p, string str, bool dump)
{
	ErrorInfo err;
	//str = decompose_bracket(str, "(");
	//str = decompose_bracket(str, ")");
	//str = decompose_bracket(str, ",");
	//str = decompose_bracket(str, "\"");
	//str = decompose_bracket(str, ";");

	std::vector<HTerm> lst = decompose_syntax(str);
	auto term = convertToTerm(lst);
	auto b = Expression::parser_expression(p,term);
	if (dump)
	{
		b->dump(" ");
		printf("\n");
	}
	return b;
}



HBlock NSParser::CParser::Parser_Condition(string str, bool dump)
{
	ErrorInfo err;
	
	//str = decompose_bracket(str, "(");
	//str = decompose_bracket(str, ")");
	//str = decompose_bracket(str, ",");
	std::vector<HTerm> lst = decompose_syntax(str);
	auto term = convertToTerm(lst);
	auto b = ControlFlux::parser_if_condition(this,term);
	if (dump)
	{
		b->dump(" ");
		printf("\n");
	}
	return b;
}


HBlock NSParser::Statement::parser_stmt(CParser *p, string str,bool dump,ErrorInfo *err)
{
    HBlock b = Statement::parser_stmt_str(p,str,nullptr, err); //nao tem inner
    if (dump)
    {		
        b->dump("");  
        printf("\n");
    }
    return b;
}

std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
{
	std::vector<std::string> strings;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = str.find(delimiter, prev)) != std::string::npos)
	{
		strings.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}

	// To get the last substring (or only, if delimiter is not found)
	strings.push_back(str.substr(prev));

	return strings;
}



std::vector<string>  split_new_lines(const string &str)   {

	return  split_string(str, "\n");
	 

    auto p1 = str.begin();
    auto p2 = str.begin();
    std::vector<string> sentences;
    while (p2 != str.end())
    {
        if (*p2 =='\n')
        {
            sentences.emplace_back(p1,p2);
            printf("%s\n", sentences.back().c_str());
            p1 = p2;
            ++p1;
            p2 = p1;
            if (p2 == str.end()) break;
        }
        ++p2;
    }
    if(p1 != p2 )
    {
        sentences.emplace_back(p1,p2);
        printf("%s\n", sentences.back().c_str());
    }
   return sentences;
}
 



 HBlock  NSParser::Statement::parser_GroupLine(CParser * p, string v ,bool top_level, HGroupLines inner, ErrorInfo *err)
{
    v.erase(std::remove(v.begin(), v.end(), '\r'), v.end());

	while (v.empty()==false && v.back() == ' ') v.pop_back();
	while (v.empty() == false && v.back() == '.') v.pop_back();
	
	if (v.empty()) return p->blank_line; 

	//auto vstr = decompose_bracket(v, "(");
	//vstr = decompose_bracket(vstr, ")");
	//vstr = decompose_bracket(vstr, "\"");
	//vstr = decompose_bracket(vstr, ",");
	//vstr = decompose_bracket(vstr, ":");
	std::vector<HTerm> lst = decompose_syntax(v);

	if (lst.empty())
	{
		return p->blank_line;
	}
	 
	if (top_level)
	{
		HBlock  rblock_stmt = parser_stmt_top(p, lst, inner, err);
		if (err->hasError)
		{
			logError("parser Error :" + v);
			return nullptr;
		}
		if (rblock_stmt == nullptr)
		{
			//err->setError("parser Error :" + v);
			return nullptr;

		}
		if (HBlockPhraseDefine pdef =  DynamicCasting::asHBlockPhraseDefine(rblock_stmt))
		{
			p->phrases.push_back(pdef->header);
		}

		return rblock_stmt;
	}
	else
	{
		HBlock  rblock_stmt_i = parser_stmt_inner(p, lst, inner, err);

		if (err->hasError)
		{
			logError("parser Error :" + v);
			return nullptr;
		}
		if (rblock_stmt_i == nullptr)
		{
			//err->setError("parser Error :" + v);
			return nullptr;

		}
		return rblock_stmt_i;
	}
	return nullptr;
}

 HBlockComandList NSParser::Statement::parser_stmt_list( CParser * p, bool toplevel, HGroupLines inner, ErrorInfo *err)
{
	std::list<HBlock> retBlocks;
	if (inner == nullptr)
	{
		return nullptr;
	}

	while (inner != nullptr)
	{
		for (auto it = inner->lines.begin(); it != inner->lines.end(); ++it)
		{
			HBlock blk;
			std::string rawLine = it->line;
			auto inext = std::next(it);
			HGroupLines _inner = nullptr;
			if (inext == inner->lines.end()) _inner = inner->inner;
			 
			
			blk = parser_GroupLine(p,rawLine, toplevel, _inner, err);
			if (blk == p->blank_line) continue;
			if (blk == nullptr && err->hasError ==false )
			{			
				logError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
				err->setError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
				return nullptr;
			}
			else if (err->hasError)
			{
				 
				logError(err->msg + " at line " + std::to_string(inner->lines.front().linenumber));
				return nullptr;
			}
			if (toplevel == true)
			{
				blk->dump("");
				retBlocks.push_back(blk);
			}
			else
			{
				retBlocks.push_back(blk);
			}

		}
		inner = inner->next;
		if (inner == nullptr) break;
	}

	retBlocks = ControlFlux::post_process_tokens(p,retBlocks ,  err );
	if (retBlocks.empty())
	{	 
		
			logError("Parser Error at " + std::to_string(inner->lines.front().linenumber));
			err->msg = err->msg + "at line " + std::to_string(inner->lines.front().linenumber);
		
	 
		if (err->hasError)
		{
			logError(err->msg + " at line " + std::to_string(inner->lines.front().linenumber));
			return nullptr;
		}
	}

	return  std::make_shared< CBlockComandList >(retBlocks);

}
 
HBlock NSParser::ParseText::parser_text(CParser *p, string str , ErrorInfo *err)
{
	 
    // quebra o text  em linhas e processa as linhas separadamente
    std::vector<string> vlist = split_new_lines(str);
	HGroupLines pivot =  get_identation_groups(p,"__FILE__",vlist,err);
	if (err->hasError)
	{
		return nullptr;
	}
	if (pivot == nullptr)
	{
		return nullptr;
	}
	 
    auto blist  = Statement::parser_stmt_list(p,true,pivot,err); 
	if (err->hasError) return nullptr;
	return  blist;

	 

}


bool  NSParser::ParseText::process_later_binds(CParser *p)
{
	bool b = false;
	ErrorInfo err;
	
	while  ( p->lateEvaluations.empty() ==false )
	{
		auto h = p->lateEvaluations.front();
		p->lateEvaluations.pop_front();


		auto hinner = h->inner();
		if (hinner->type() == BlockLateTerm)
		{
			CBlockLateTerm*   hterm_inner = (CBlockLateTerm*)hinner.get();
			HTerm t = hterm_inner->inner;

			HBlock body = Expression::parser_expression(p, t);
			h->replace(body);
			b = true;
		}
		else if (hinner->type() == BlockLateInner)
		{
			CBlockLateInner*   hcmd_inner = (CBlockLateInner*)hinner.get();
			auto  inner_group = hcmd_inner->inner;
			HBlockComandList executeBlock = Statement::parser_stmt_list(p, false, inner_group, &err);
			h->replace(executeBlock);
			b = true;
		}
		else
		{
			err.setError("ndefined Later");
		}

	 }
	return b;

}

//interprete varias linhas de texto
HBlock NSParser::ParseText::parser_text(CParser *p, string str, bool dump )
{
	ErrorInfo err;
    HBlock b =  parser_text(p,str,&err);
    if (b) {
        if (dump) {
            b->dump("");
            printf("\n");
        }
    }
    else
    {
        printf("File Error\n");

    }
    return b;
}








CBlocking::HBlock NSParser::Statement::parser_stmt_list_later(CParser * p,  HGroupLines inner)
{	
	 
	HBlockLateInner binner = std::make_shared<CBlockLateInner>(inner);
	HBlockBody b = std::make_shared<CBlockBody>(binner);

	p->lateEvaluations.push_back(b);
	return b;
}



CBlocking::HBlock NSParser::Expression::parser_expression_later(CParser * p, NSTerm::HTerm term)
{
	HBlockLateTerm binner = std::make_shared<CBlockLateTerm>(term);
	HBlockBody b = std::make_shared<CBlockBody>(binner);
	p->lateEvaluations.push_back(b);
	return b;
}