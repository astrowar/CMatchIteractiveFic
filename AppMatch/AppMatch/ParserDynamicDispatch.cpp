// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <vector>
#include "Parser.hpp"
using namespace CBlocking;

using namespace NSTerm;
using namespace NSTerm::NSMatch;




NSParser::DispatchArguments NSParser::DynamicDispatch::parser_buildMatchBlock_actionInput(CParser *p, HTerm term) {
    if (CList *cterm = asCList(term.get())) {
        std::vector<HTerm> vterm(cterm->lst.begin(), cterm->lst.end());
        auto kv = parser_buildMatchBlock_actionInputList(p,vterm);
        return kv;
    }

    std::vector<HPred> replcList;
    replcList.push_back(mk_HPredLiteral(term->repr()));

    //return std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(term->repr()));
    return DispatchArguments(replcList, nullptr,
                             std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(term->repr())));
}



HBlockStaticDispatch NSParser::DynamicDispatch::getStaticDispatchResolve(CParser *p, HTerm term) //Determina se este termo esta na lista de dispatchs dynamicos
{


    //Verifica se ja tem a matchPhase
    int maxID = 0;
    for (auto it = p->sentenceDispatch.begin(); it != p->sentenceDispatch.end(); ++it) {
        MatchResult res = CMatch(term, it->matchPhase);
        if (res.result == Equals) {
            return std::make_shared<CBlockStaticDispatch>(it->entryId,
                                                          std::make_shared<CBlockNoum>(res.matchs["noum1"]->repr()),
                                                          std::make_shared<CBlockNoum>(res.matchs["noum2"]->repr()));
        }
    }
    return nullptr;


}

 

NSParser::DispatchArguments NSParser::DynamicDispatch::parser_buildMatchBlock_actionInputList(CParser *p, std::vector<HTerm>&  term) {

   // std::cout << "what:  " << get_repr(term) << std::endl;
    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{

			predList.push_back(mkHPredAny("verb"));
			//predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
			//predList.push_back(mk_HPredLiteral("]"));
			predList.push_back(mkHPredAny("with_word"));
			//predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind2"));
			//predList.push_back(mk_HPredLiteral("]"));
		}


        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind1"]);
            HBlockMatch c3 = std::make_shared<CBlockMatchNoum>(
                    std::make_shared<CBlockNoum>(res.matchs["with_word"]->repr()));
            HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            replcList.push_back(mk_HPredLiteral(res.matchs["with_word"]->repr()));
            replcList.push_back(mkHPredAny("noum2"));

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1, c3, arg2}));
            return NSParser::DispatchArguments(  replcList, mlist1, mlist2);

        }
    }
    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("verb"));
			//predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
		//	predList.push_back(mk_HPredLiteral("]"));
			predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind2"));
			//predList.push_back(mk_HPredLiteral("]"));
		}


        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
            HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind1"]);
          
            HBlockMatch c4 = NSParser::ExpressionMatch::parser_MatchArgument(p, res.matchs["kind2"]);
            HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
            HBlockMatch arg2 = std::make_shared<CBlockMatchNamed>("noum2", std::make_shared<CBlockMatchAny>());

            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            
            replcList.push_back(mkHPredAny("noum2"));

            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2, c4}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1,   arg2}));
            return NSParser::DispatchArguments(replcList, mlist1, mlist2);

        }
    }
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("verb"));
			predList.push_back(mkHPredAny("aux"));
		//	predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
		//	predList.push_back(mk_HPredLiteral("]"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
		 
			HBlockMatch c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));
			HBlockMatch c1a = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["aux"]->repr()));


			//HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p,res.matchs["kind1"]);
			
			std::vector<HPred> replcList;
			replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
			replcList.push_back(mk_HPredLiteral(res.matchs["aux"]->repr()));
			replcList.push_back(mkHPredAny("noum1"));
			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>());
			//return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
			auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c2 }));
			auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({ c1, c1a, arg1 }));
			return NSParser::DispatchArguments(replcList, mlist1, mlist2);
		}
	}


    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("verb"));
	//		predList.push_back(mk_HPredLiteral("["));
			predList.push_back(mkHPredAny("kind1"));
	//		predList.push_back(mk_HPredLiteral("]"));
		}
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) 
		{
		 
			HBlockMatch  c1 = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoum>(res.matchs["verb"]->repr()));


            //HBlockMatch c2 = std::make_shared<CBlockMatch>(std::make_shared<CBlockNoum>(res.matchs["kind1"]->repr()));
			HBlockMatch c2 = NSParser::ExpressionMatch::parser_MatchArgument(p,res.matchs["kind1"]);
			HBlockMatch arg1 = std::make_shared<CBlockMatchNamed>("noum1", std::make_shared<CBlockMatchAny>()); //este eh o match estatico .. ie .. aquele usado pelo parser para identificar as chamadas estaticas
						

            std::vector<HPred> replcList;
            replcList.push_back(mk_HPredLiteral(res.matchs["verb"]->repr()));
            replcList.push_back(mkHPredAny("noum1"));
            //return  DispatchArguments(replcList, std::make_shared<CBlockMatchList>({ c2 }), std::make_shared<CBlockMatchList>({ c1,c2 }));
            auto mlist1 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c2}));
            auto mlist2 = std::make_shared<CBlockMatchList>(std::list<HBlockMatch>({c1, arg1 }));
            return NSParser::DispatchArguments(replcList, mlist1, mlist2);
        }
    }

    return NSParser::DispatchArguments(std::vector<HPred>(), nullptr, nullptr);
}


HBlock NSParser::DynamicDispatch::STMT_understand_generic_redirect(CParser *p, HTerm  term, HBlock  output_term) {

	DispatchArguments match_predicate = parser_buildMatchBlock_actionInput(p, term);
	if (match_predicate.sentenceMatch == nullptr) return nullptr;
	HBlockUnderstandDynamic  retBlock = std::make_shared<CBlockUnderstandDynamic >(  match_predicate.sentenceMatch, match_predicate.staticArgumentMatch, output_term);
	int entryID = p->registerDynamicDispatch(match_predicate.staticPredicade,	match_predicate.sentenceMatch, output_term);


	return retBlock;
}





HBlock NSParser::DynamicDispatch::STMT_understand_Action_Assertion_static(CParser *p, std::vector<HTerm>&  term) {

    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList = { mk_HPredLiteral("understand") , mk_HPredLiteral(":") ,mkHPredAny("What") ,mk_HPredLiteral("as") ,mkHPredAny("Subst") };

		/*	predList.push_back(mk_HPredLiteral("understand"));
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("What"));
			predList.push_back(mk_HPredLiteral("as"));
			predList.push_back(mkHPredAny("Subst"));*/
		}

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {


			 

            //auto input_noum =  std::make_shared<CBlockNoum>(res.matchs["What"]->repr());

            // existe uma action que Match com o Subst ???
            HBlock output_noum = nullptr;
            HBlockMatch sentence_match = nullptr;
            {

               auto sTerm = res.matchs["Subst"];
                {
                    sTerm = expandBract(sTerm);
                }

				//Rh um action !!
				std::vector<HPred> actionList;
				actionList.push_back(p->actionPredList);
				MatchResult res_action = CMatch(sTerm, actionList);
				if (res_action.result == Equals) {

					output_noum = std::make_shared<CBlockAction>( ((sTerm)->repr())); //An Action !!!
				}
				else
				{
					output_noum = Expression::parser_expression(p,res.matchs["Subst"]);

					//Interpretei 
					logMessage("Interpretei " + sTerm->repr());
					logMessage("Como ");
					output_noum->dump("          ");
					logMessage("---");

				}


				//Nao eh um action               
				//HBlock value = parser_expression( res.matchs["Subst"]);

				if (output_noum == nullptr) return nullptr;
				 
				return STMT_understand_generic_redirect(p,res.matchs["What"], output_noum);

                //std::cout << "try " << sTerm->repr() << "  N:" << sTerm->nterms() << std::endl;

				// Verifica se tem alguma Acao que corresponde ao termo de saida

                //std::vector<HPred> actionList;
               // actionList.push_back(actionPredList);
                //MatchResult res_action = CMatch(sTerm, actionList);
				 

				//Ok .. nao tem registro de nada analise o que esta na saida


            }
        }
    }
    return nullptr;
}

std::list<HBlock> NSParser::DynamicDispatch::ToMatchList(CParser *p, std::vector<HPred> pvector, MatchResult result)
{
	std::list<HBlock> vlist;
	for(size_t j = 0; j< pvector.size();++j)
	{
		if (CPredAtom* vAtom = asPredAtom(pvector[j].get()))
		{
			vlist.push_back(std::make_shared<CBlockNoum>(vAtom->h->repr()));
		}
		else if (CPredAny * vAny =asPredAny(pvector[j].get()))
		{
			HBlock n1 = Expression::parser_expression(p,result.matchs[vAny->named]);
			vlist.push_back(n1);
		}
		else
		{
			logError("error" );
		}
	}
	return vlist;
}

HBlock NSParser::DynamicDispatch::TryDispatch_action(CParser *p, std::vector<HTerm>&  term)
{

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("try"));			
			predList.push_back(mkHPredAny("Action"));						
			predList.push_back(mkHPredAny("noum1"));
			predList.push_back(mkHPredAny("noum2"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{
			auto actionDesc = std::make_shared<CBlockAction>((res.matchs["Action"]->repr())); //An Action !!!			
			auto nn1 = std::make_shared<CBlockNoum>(res.matchs["noum1"]->repr());
			auto nn2 = std::make_shared<CBlockNoum>(res.matchs["noum2"]->repr());

			auto actionCall = std::make_shared<CBlockActionCall>(actionDesc , nn1, nn2  ); //An Action !!!
			return actionCall;
		}
	}
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("try"));
			predList.push_back(mkHPredAny("Action"));
			predList.push_back(mkHPredAny("noum1")); 
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto actionDesc = std::make_shared<CBlockAction>((res.matchs["Action"]->repr())); //An Action !!!			
			auto nn1 = std::make_shared<CBlockNoum>(res.matchs["noum1"]->repr()); 
			auto actionCall = std::make_shared<CBlockActionCall>(actionDesc, nn1, nullptr); //An Action !!!
			return actionCall;
		}
	}
	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("try"));
			predList.push_back(mkHPredAny("Action")); 
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto actionDesc = std::make_shared<CBlockAction>((res.matchs["Action"]->repr())); //An Action !!!		 
			auto actionCall = std::make_shared<CBlockActionCall>(actionDesc, nullptr, nullptr); //An Action !!!
			return actionCall;
		}
	}
	return nullptr;
}

HBlock NSParser::DynamicDispatch::DynamicDispatch_action(CParser *p, std::vector<HTerm>&  term) {

	for (auto it = p->sentenceDispatch.begin(); it != p->sentenceDispatch.end(); ++it)
	{

		MatchResult res_action = CMatch(term, it->matchPhase);
		if (res_action.result == Equals)
		{
			HBlock n1 = Expression::parser_expression(p,res_action.matchs["noum1"]);
			HBlock n2 = nullptr;
			if (res_action.matchs.find("noum2") != res_action.matchs.end()) {
				n2 = Expression::parser_expression(p, res_action.matchs["noum2"]);
			}
			else {
				n2 = std::make_shared<CBlockNoum>("Nothing");
			}
			n1->dump("   ");
			n2->dump("   ");


			//if (HBlockAction vAction = std::asHBlockAction(it->output))
			//{
			//	return std::make_shared<CBlockActionCall>(vAction, n1, n2);
			//}
			std::list<HBlock> resList = ToMatchList(p, it->matchPhase, res_action);
			auto clistResults = std::make_shared<CBlockList>(resList);

			return 	  std::make_shared<CBlockDinamicDispatch>(clistResults); // it->output;
			return std::make_shared<CBlockStaticDispatch>(it->entryId, n1, n2);
		}

	}
	return nullptr;
}
