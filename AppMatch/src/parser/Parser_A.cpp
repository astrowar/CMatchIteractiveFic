// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "parser/Parser.hpp"
 
 

 
#include "CBlockMatch.hpp"
#include "CBlockBoolean.hpp"
#include "CblockAssertion.hpp"

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;


HBlock NSParser::Statement::parserBoolean(CParser * p, HTerm term) {
    if (CList *vlist = asCList(term.get())) {
        auto v = vlist->asVector();
        auto r = parserBoolean(p,v);
        if (r != nullptr) {
            return r;
        } else {
            //	std::cout << term->repr() << std::endl;
        }

    }
    return Expression::parser_expression(p,term);
}


HBlock NSParser::Statement::parserBoolean(CParser * p, std::vector<HTerm>& term)
{
    {
        CPredSequence predList = pLiteral("not") <<pAny("N2");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n2 = parserBoolean(p,res.matchs["N2"]);
            return std::make_shared<CBlockBooleanNOT>(n2);
        }
    }

    {
        CPredSequence predList = pAny("N1") <<pLiteral("and") <<pAny("N2");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parserBoolean(p,res.matchs["N1"]);
            HBlock n2 = parserBoolean(p, res.matchs["N2"]);
            return std::make_shared<CBlockBooleanAND>(n1, n2);
        }
    }

    {
        CPredSequence predList = pAny("N1") <<pLiteral("or") <<pAny("N2");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parserBoolean(p, res.matchs["N1"]);
            HBlock n2 = parserBoolean(p, res.matchs["N2"]);
            return std::make_shared<CBlockBooleanOR>(n1, n2);
        }
    }

    return nullptr;
}


NSParser::ParserResult NSParser::ParseAssertion::parser_AssertionKind(CParser * p, std::vector<HTerm>& lst) {
    CPredSequence predList = pAny("Object")  << mk_HPredLiteral_OR("Verb", {"is", "are"}) <<pList("kindpart", {pLiteral("a"), pLiteral("kind"), pLiteral("of")}) <<pAny("Kind");

    MatchResult res = CMatch(lst, predList);
    if (res.result != Equals) {
        return ParserResult(res);
    }
    //HBlock b = new CBlockAssertion(res.matchs["Object"], res.matchs["Kind"]);
    return std::move(ParserResult(res));
}

 


HBlockActionApply NSParser::ParseAssertion::parse_AssertionAction_ApplyngTo(CParser * p, HTerm term) 
{
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pLiteral("nothing");		
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			//HBlock n1 = Expression::parser_kind(p, res.matchs["kind1"]);
			//HBlock n2 = Expression::parser_kind(p, res.matchs["kind2"]);
			return std::make_shared<CBlockActionApply>(nullptr,nullptr);
		}
	}
	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pAny("kind1")<<pLiteral("and")	<<pAny("kind2");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock n1 = Expression::parser_kind(p, res.matchs["kind1"]);
			HBlock n2 = Expression::parser_kind(p, res.matchs["kind2"]);
			return std::make_shared<CBlockActionApply>(n1, n2);
		}
	}

	{
		// and action applying to [one visible thing and requiring light]
		CPredSequence predList = pLiteral("two")	<<pAny("kind1");

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlock n1 = Expression::parser_kind(p, res.matchs["kind1"]);
			return std::make_shared<CBlockActionApply>(n1, n1);
		}
	}


    {
        // and action applying to [one visible thing and requiring light]
        CPredSequence predList = pAny("kind1");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = Expression::parser_kind(p,res.matchs["kind1"]);
            return std::make_shared<CBlockActionApply>(n1, nullptr );
        }
    }

    return nullptr;
}


//HBlock NSParser::CParser::parseAssertion_DecideWhat(HTerm term) {
//    return std::make_shared<CBlockNoumStr>(term->removeArticle()->repr());
//}


