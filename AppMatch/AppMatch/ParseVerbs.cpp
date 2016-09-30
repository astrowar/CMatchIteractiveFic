#include "Parser.h"
 
#include <iostream>


HBlockAssertion_is CParser::parse_AssertionVerb(std::vector<HTerm> term) {
    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(verb_IS_NOT());
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_assertionTarger(res.matchs["N1"]);
            HBlock n2 = parser_expression(res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
            return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);
        }
    }

    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_assertionTarger(res.matchs["N1"]);
            HBlock n2 = parser_expression(res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
            return std::make_shared<CBlockIsNotVerb>(vrepr, n1, n2);

        }
    }

    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(verb_IS());
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_assertionTarger(res.matchs["N1"]);
            HBlock n2 = parser_expression(res.matchs["N2"]);
			auto vrepr = CtoString( expandBract(res.matchs[verbList->named]) );
	        
            return std::make_shared<CBlockIsVerb>(vrepr, n1, n2);

        }
    }

    {
        // and action applying to [one visible thing and requiring light]
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("N1"));
        predList.push_back(verbList);
        predList.push_back(mkHPredAny("N2"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock n1 = parser_assertionTarger(res.matchs["N1"]);
            HBlock n2 = parser_expression(res.matchs["N2"]);
			auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
            return std::make_shared<CBlockIsVerb>(vrepr, n1, n2);

        }
    }

    return nullptr;
}



HBlockMatchIsVerb CParser::parserMatchIsConditionVerb(HTerm term)
{
	//Tambem pode ser um verbo definido
	{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("MatchBody"));
		predList.push_back(verb_IS());
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("valueToCheck"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch body = parser_MatchArgument(res.matchs["MatchBody"]);
			HBlockMatch value = parser_MatchArgument(res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
				return std::make_shared<CBlockMatchIsVerb>(vrepr, body, value);
				//return std::make_shared<CBlockAssertion_isDirectAssign>(body, value);
			}
		}
	}

{
		std::vector<HPred> predList;
		predList.push_back(mkHPredAny("MatchBody"));		
		predList.push_back(verbList);
		predList.push_back(mkHPredAny("valueToCheck"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {
			HBlockMatch body = parser_MatchArgument(res.matchs["MatchBody"]);
			HBlockMatch value = parser_MatchArgument(res.matchs["valueToCheck"]);
			if (body != nullptr && value != nullptr) {
				auto vrepr = CtoString(expandBract(res.matchs[verbList->named]));
				return std::make_shared<CBlockMatchIsVerb>(vrepr, body, value);
			}
		}
	}
return nullptr;
}



 
HBlock CParser::STMT_verb_Assertion_N(std::vector<HTerm> term) {
    auto L_the_verb = mkHPredList("vinitial", {mk_HPredLiteral("the"), mk_HPredLiteral("verb")});
    auto L_verb = mk_HPredLiteral("verb");
    {

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("VerbList"));
        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});
        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            HPred verbMatch;
            HBlock a_verb;
            HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

            if (CList *plist = asCList(res.matchs["VerbList"].get())) {
                //eh uma lista

				HTerm listExpand =  expandBract(res.matchs["VerbList"]);
				plist = asCList(listExpand.get());


                HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());

                verbMatch = mkHPredList("VerbMatch", {});
                CPredList *cpList = reinterpret_cast<CPredList *>(verbMatch.get());

                for (auto ip : plist->lst) {
                    clist->push_back(std::make_shared<CBlockNoum>(ip->repr()));
                    cpList->plist.push_back(mk_HPredLiteral(ip->repr()));
                }
                a_verb = clist;

                verbList->blist.push_back(verbMatch);
                return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

            } else {
                //nao eh uma lista :-(
                return nullptr;
            }
        }

    }
    return nullptr;

}

HBlock CParser::STMT_verb_Assertion(std::vector<HTerm> term) {

    auto L_the_verb = mkHPredList("vinitial", {mk_HPredLiteral("the"), mk_HPredLiteral("verb")});
    auto L_verb = mk_HPredLiteral("verb");
    {

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        predList.push_back(mkHPredAny("Aux"));

        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});
        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

            auto verbMatch = (mkHPredList("VerbMatch", {
                    mk_HPredLiteral(res.matchs["Verb"]->repr()),
                    mk_HPredLiteral(res.matchs["Aux"]->repr()),
            }));

            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
        }

    }

    {

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        predList.push_back(mkHPredAny("Aux"));
        predList.push_back(mk_HPredLiteral("implies"));
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

            HBlock a_verb = clist;
            HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());

            auto verbMatch = (mkHPredList("VerbMatch", {
                    mk_HPredLiteral(res.matchs["Verb"]->repr()),
                    mk_HPredLiteral(res.matchs["Aux"]->repr()),
            }));

            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
        }

    }

    {
        //Teste de carga

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});

        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            auto vaux = getVerbAndAux(res.matchs["Verb"]);
            HBlock a_verb = vaux.first;
            HPred verbMatch = vaux.second;
            HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

        }

    }

    {
        //Teste de carga

        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        predList.push_back(mk_HPredLiteral("implies"));
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {

            auto vaux = getVerbAndAux(res.matchs["Verb"]);
            HBlock a_verb = vaux.first;
            HPred verbMatch = vaux.second;
            HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
            verbList->blist.push_back(verbMatch);
            return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);

        }

    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        auto L_the_verb_1 = mkHPredList("implies_a", {mk_HPredLiteral("implies"),
                                                      mkHPredBooleanOr("article", mk_HPredLiteral("a"),
                                                                       mk_HPredLiteral("an"), mk_HPredLiteral("the"))});

        predList.push_back(L_the_verb_1);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = asCList(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
                    clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (mkHPredList("VerbMatch", {
                            mk_HPredLiteral(inList.front()->repr()),
                            mk_HPredLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
                    verbMatch = mk_HPredLiteral(inList.front()->repr());
                }

                int nv = inList.size();

                //std::cout << res.matchs["Verb"]->repr() << std::endl;
                if (a_verb != nullptr) {

                    HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                    verbList->blist.push_back(verbMatch);
                    return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                }
            } else {

                HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
                HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
                return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            }
        }

    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredBooleanOr("kindpart", L_the_verb, L_verb));
        predList.push_back(mkHPredAny("Verb"));
        auto L_the_verb_4 = mk_HPredLiteral("implies");
        predList.push_back(L_the_verb_4);
        predList.push_back(mkHPredAny("Relation"));
        predList.push_back(mk_HPredLiteral("relation"));
        MatchResult res = CMatch(term, predList);

        if (res.result == Equals) {
            if (CList *cverb = asCList(res.matchs["Verb"].get())) {
                HBlock a_verb = nullptr;
                HPred verbMatch = nullptr;
                MTermSet inList(cverb->lst.begin(), cverb->lst.end());
                inList = remove_boundaryListMark(inList);
                if (inList.size() == 2) {
                    HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
                    clist->push_back(std::make_shared<CBlockNoum>(inList.front()->repr()));
                    clist->push_back(std::make_shared<CBlockNoum>(inList.back()->repr()));
                    a_verb = clist;

                    verbMatch = (mkHPredList("VerbMatch", {
                            mk_HPredLiteral(inList.front()->repr()),
                            mk_HPredLiteral(inList.back()->repr()),
                    }));


                } else if (inList.size() == 1) {
                    a_verb = std::make_shared<CBlockNoum>(inList.front()->repr());
                    verbMatch = mk_HPredLiteral(inList.front()->repr());
                }

                if (a_verb != nullptr) {
                    HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                    verbList->blist.push_back(verbMatch);
                    return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
                }
            } else {
                HBlock a_verb = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
                HBlockNoum a_relation = std::make_shared<CBlockNoum>(res.matchs["Relation"]->repr());
                verbList->blist.push_back(mk_HPredLiteral(res.matchs["Verb"]->repr()));
                return std::make_shared<CBlockVerbRelation>(a_verb, a_relation);
            }
        }

    }

    return nullptr;

}










