
#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "CBlockScope.hpp"
#include "interpreter/QueryStack.hpp"
#include "sharedCast.hpp"
#include <memory>
#include <algorithm>
using namespace std;
using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;


#include  "verb_en.hpp" 
#include "parser/ParserPlural.hpp"

namespace Auxiliar  {
	//bool  BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
	bool  BothAreSpaces(char lhs, char rhs) ;
	string complex_viewPoint(string person, string number, string gender)
	{
		string s = "";
		if (person == "first") s = s + "1";
		else if (person == "second ") s = s + "2";
		else  s = s + "3"; //default 

		if (number == "plural") s = s + "P";
		else  s = s + "S"; //singular

		return s;
	}
}

std::list<HBlockVerbConjugation> CBlockInterpreter::get_verb_conjugations(std::string verb) const
{
	static const VERBTABLE verb_eng = verb_table();
	int  n = verb_eng.numEntries;

	std::list<HBlockVerbConjugation> vlist;
	for (int i = 0; i < n; ++i)
	{
		if (verb_eng.verbs[i].verb == verb)
		{
			auto &ventry = verb_eng.verbs[i];
			int nk = ventry.n;
			for (int j = 0; j< nk;++j)
			{
				auto ve = ventry.tenses[j];
				auto vj = std::make_shared<CBlockVerbConjugation>(std::string(ve.world), std::string(ve.tense));
				vlist.push_back(vj);

			}
			break;
		}
	}
	return  vlist;
}


 

HBlockNoum CBlockInterpreter:: get_verbal_regarding(string verb, HRunLocalScope localsEntry, QueryStack *stk)
{
	
	if (verb == "are" || verb == "is")
	{
		verb = "be";
	}


	auto vc = get_verb_conjugations(verb);
	if (vc.empty()) return nullptr;


	auto r = localsEntry->resolve("viewPoint");
	if (auto nr = asHBlockNoum(r))
	{
		string viewPoint = nr->named();
		string conjugadet = "None";
		 
		 
		conjugadet = adapt_verb_inner(verb, "VBP", viewPoint, localsEntry);
		 
		 
		if (conjugadet != "None")
		{
			return   std::make_shared<CBlockNoumStr>(conjugadet);
		}

	}

	return std::make_shared<CBlockNoumStr>("[Missing ViewPoint]");

}

HBlockNoumSupl CBlockInterpreter::resolve_number_gender(string  n, HRunLocalScope localsEntry, QueryStack *stk)
{
	//static PLURALTABLE plural_tab = plura_table();
	auto pSingle = language->get_singular_of(n );
	if (pSingle != nullptr )
	{
		return std::make_shared<CBlockNoumSupl>(n , "plural", "neutral");
	}
	auto pPlural = language->get_plural_of(n  );
	if (pPlural != nullptr)
	{
		return std::make_shared<CBlockNoumSupl>(n , "singular", "neutral");
	}

	return std::make_shared<CBlockNoumSupl>(n , "", ""); //undefined 
}




HBlockNoumSupl CBlockInterpreter::textual_representation(HBlock  x, string person,   string number, string gender, HRunLocalScope localsEntry, QueryStack *stk)
{
	//static PLURALTABLE plural_tab = plura_table();
	
	  std::map<string, CBlocking::HBlock> nextVarSet = { { "viewPoint" , std::make_shared<CBlockNoumStr>(Auxiliar::complex_viewPoint(person, number, gender))  },{ "tense" , std::make_shared<CBlockNoumStr>("present tense") } };


	 auto localsNext = std::make_shared< CRunLocalScope >(localsEntry, nextVarSet);


	{

		 

		// Existe algum "To Say" associado com esse X
		//HBlockPhraseHeader say_callheader = std::make_shared<CBlockPhraseHeader>(std::make_shared<CBlockNoumStr>("say"),   nullptr, nullptr);
		
		auto ax = resolve_argument(x, localsEntry, stk);
		if (ax != nullptr) x = ax;
		//HBlockPhraseInvoke to_say = std::make_shared<CBlockPhraseInvoke>(say_callheader, x, nullptr);

		std::list<HBlock> xlist;
		xlist.push_back(x);
		HBlockPhraseInvoke to_say = std::make_shared<CBlockPhraseInvoke>(std::make_shared<CBlockNoumStr>("say"), std::make_shared< CBlockList >(xlist));

		string xs = "";
		bool has_call = false;
		auto prev_hook = this->say_output;
		this->say_output = [&](std::string a) { xs = xs + a; has_call = true;  return true; };
		 
		this->exec_eval(to_say, localsNext, stk);
		this->say_output = prev_hook;
		if (has_call)
		{
			return std::make_shared<CBlockNoumSupl>( xs , "singular", "neutral");
		}
	}

	auto y = exec_eval(x, localsNext, stk);

	// o verbo que vem a seguir concorda com o noum atual
	if (auto n = asHBlockNoumSupl(y)) return n ;
	if (auto n = asHBlockNamedValue(y)) return resolve_number_gender(n->named   , localsNext, stk);
	if (auto n = asHBlockInstanceNamed(y)) return resolve_number_gender(n->named, localsNext, stk);
	

	if (auto n = asHBlockList(y))
	{
		if (n->lista.empty())   return std::make_shared<CBlockNoumSupl>("{}", "singular", "neutral");

		if (n->lista.size() == 1)
		{
			return  textual_representation(n->lista.front(), person, number, gender, localsNext, stk);			
		}
		std::list<string> slist ;
		for(auto ni : n->lista)
		{
			HBlockNoumSupl nni = textual_representation(ni, person, number, gender, localsNext, stk);			
			slist.push_back(nni->named());
			slist.push_back(", ");
		}
		//remove last comma
		slist.pop_back();
		if (slist.size() >1)
		{
			//replace last comma by "and"
			auto it = slist.rbegin();
			++it;//last word
			*it = " and ";
		}
		
		string snoum =""; 
		for (auto si : slist)  snoum = snoum + si;
		return std::make_shared<CBlockNoumSupl>(snoum, "plural", "neutral");		
		
	}


    if (auto n = asHBlockNoum(y))
		{
		 
		auto vreg = get_verbal_regarding(n->named(), localsNext, stk);
		if (vreg != nullptr) return std::make_shared<CBlockNoumSupl>(vreg->named(), number, gender);

		return resolve_number_gender(n->named(), localsNext, stk);
			 
		} 
 
	 
	// eh um verbo ?
	if (y == nullptr)
	{
		if (auto n = asHBlockNoum(x))
		{
			auto vreg = get_verbal_regarding(n->named(), localsNext, stk);
			if (vreg != nullptr) return std::make_shared<CBlockNoumSupl>(vreg->named(), number, gender);

			//return resolve_number_gender(n->named, localsNext, stk);
		}

	}

	if (auto ntxt = asHBlockText(x))
	{
		return std::make_shared<CBlockNoumSupl>(ntxt->contents, "singular", "neutral");
	}
	if (HBlockTextSentence nstxt = asHBlockTextSentence(x))
	{
		HBlockText ntxt = adapt_text(nstxt, localsEntry, stk);
		return std::make_shared<CBlockNoumSupl>(ntxt->contents, "singular", "neutral");
	}

	return std::make_shared<CBlockNoumSupl>( "###", "singular", "neutral");
}

 

HBlockText CBlockInterpreter::adapt_text(HBlockTextSentence texts, HRunLocalScope localsEntry, QueryStack *stk)
{
	
	std::string s = "";

	std::string number = "singular";
	std::string gender = "neutral";
	std::string person = "3S";

	bool starting = true;
	for(auto t : texts->contents)
	{
		if (HBlockText tx = asHBlockText(t))
		{
			s = s + tx->contents;
		}
		else
		{
			auto nx = textual_representation(t,person, number , gender,  localsEntry, stk);
			 

			//nx->dump("+ ");
			if (starting == false) s = s + " ";
			s = s +  nx->named();
			if (nx->gender != "") gender = nx->gender;
			if (nx->number != "") number = nx->number;

			starting = false;
		}
	}

 

	std::string::iterator new_end = std::unique(s.begin(), s.end(), Auxiliar::BothAreSpaces);
	s.erase(new_end, s.end());
	 
	return std::make_shared<CBlockText>(s);
}
 