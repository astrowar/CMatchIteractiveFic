// PVS
// PVQ
//
// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


//
#include "Parser\Parser.hpp"
 
#include <algorithm>
#include <sstream>
#include <cassert>

using namespace CBlocking;
 
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;

bool is_empty_string(std::string s)
{
	if (s.size() == 0) return true;
	if (s.find_first_not_of(' ') == std::string::npos)
	{
		return true;
	}
	return false;
}

std::string  decompose_bracket(std::string phase, std::string dlm) {

	size_t b = phase.find(dlm);
	if (b != std::string::npos) {
		std::string sa = phase.substr(0, b);
		std::string sb = phase.substr(b + 1, phase.size() - b - 1);
		sb = decompose_bracket(sb, dlm);
		if (is_empty_string(sb))
		{
			return sa + " " + dlm;
		}
		if (is_empty_string(sa))
		{
			return dlm + " " + sb;
		}
		return sa + " " + dlm + " " + sb;
	}
	return phase;
}

std::vector<HTerm> decompose(std::string phase) {
	std::stringstream test(phase);
	std::string segment;
	std::vector<HTerm> seglist;
	while (getline(test, segment, ' ')) 
	{
		if (segment.length() > 0) 
		{
			if (segment[0] != ' ' && segment[0] != '\t' && segment[0] != '\r')
			{
				 
				seglist.push_back(make_string(segment));
			}
		}
	}
	
	return seglist;
}

HPred pLiteral(string str) 
{
    return pAtom("_", make_string(str));
}

 



string get_repr(std::vector<HPred> plist) {
    string ret = "";
    for (auto p : plist) {
        ret += p->repr();
    }
    return ret;
}

 
string CtoString(CList * lst)
{
	if (lst->lst.empty()) return "";
	if (lst->lst.size() == 1) return CtoString(lst->lst.front());
	std::string vstr = "";
	bool fronti = true;
	for (auto &v : lst->lst)
	{
		if (!fronti) vstr += " ";
		vstr += CtoString(v);
		fronti = false;
	}
	return vstr;

}
string CtoString(HTerm  value)
{
	return CtoString(value.get());
}

string CtoString(CTerm  *value)
{
	if (CString* lstr = asCString(value)) {
		return lstr->s;
	}
	if (CList* lst = asCList(value)) {
		{
			return CtoString(lst);
		}
	}

    assert(false);
    return "";

}


HTerm expandBract(HTerm term) {
    if (CList *clist = asCList(term.get())) {
        if (clist->lst.front()->is_openBracket() && clist->lst.back()->is_closeBracket()) {
            auto vlist = clist->asVector();
            vlist = remove_boundaryListMark(vlist);
            CList *cnew = new CList();
            cnew->lst = std::list<HTerm>(vlist.begin(), vlist.end());
            return std::shared_ptr<CList>(cnew);
        } else {
            return term;
        }
    }
    return term;
}

std::vector<HTerm> get_tail(std::vector<HTerm> &qlist) {
    std::vector<HTerm> v;
    bool front = true;
    for (auto it = qlist.begin(); it != qlist.end(); ++it) {
        if (!front) { v.push_back(*it); }
        front = false;
    }
    return v;
}

HPred mk_HPredLiteral_OR(string _named, std::initializer_list<string> alist) {
    std::list<string> strList(alist);
    std::list<std::shared_ptr<CPred> > predlist;
    for (auto it = strList.begin(); it != strList.end(); ++it) {
        predlist.push_back(pAtom("_", make_string(*it)));
    }
    return std::make_shared<CPredBooleanOr>(_named, predlist);
}

CList *mk_CList_Literal(std::vector<HTerm> strList) {
    auto clist = new CList();
     
    for (auto it = strList.begin(); it != strList.end(); ++it) {
        clist->push_back(*it);
    }
    return clist;
}

HPred undefinedArticle() {
    return pOr("_", pLiteral("a"), pLiteral("an"));
}

HPred verb_IS() {
    return pOr("is", pLiteral("are"), pLiteral("is"));
}

HPred verb_IS_NOT() {
    return pOr("isnot", pList("isNotList", {pLiteral("is"), pLiteral("not")}),
                            pLiteral("arent"));
}

HPred mk_What_Which() {
    return pOr("what_TERM", pLiteral("what"), pLiteral("which"), pLiteral("whether"));
}

std::pair<HBlock, HPred> getVerbAndAux(HTerm term) {

    {
		  CPredSequence predList = pAny("Verb") <<pAny("Aux");
		 
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoumStr>(res.matchs["Aux"]->repr()));

            HPred verbMatch = (pList("VerbMatch", {
                    pLiteral(res.matchs["Verb"]->repr()),
                    pLiteral(res.matchs["Aux"]->repr()),
            }));
            return std::pair<HBlock, HPred>(clist, verbMatch);
        }
    }

    {
        CPredSequence predList =pAny("Verb");

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock clist = std::make_shared<CBlockNoumStr>(res.matchs["Verb"]->repr());
            HPred verbMatch = pLiteral(res.matchs["Verb"]->repr());

            return std::pair<HBlock, HPred>(clist, verbMatch);
        }

    }
    return std::pair<HBlock, HPred>(nullptr, nullptr);
}



HPred convert_to_predicate(CTerm *termo) {

	if (CList *clist = asCList(termo)) {
		auto vlist = clist->asVector();
		vlist = remove_boundaryListMark(vlist);

		auto hpr = pList("predListing", {});
		CPredList *predList = asPredList (hpr.get());

		for (auto k : vlist) {
			predList->plist.push_back(convert_to_predicate(k.get()));
		}
		return hpr;
	}
	else {
		if (CString *css = asCString(termo)) {

			return pLiteral(css->s);
		}

	}

	return pLiteral(termo->repr());
}
